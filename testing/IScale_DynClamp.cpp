/*
 * Copyright (C) 2011 Weill Medical College of Cornell University
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*** INTRO
 * Current Scaling Dynamic Clamp
 * 
 * IScale_DynClamp.cpp, v1.0
 *
 * Author: Francis A. Ortega (2011)
 *
 * Notes in header
 *
 ***/

/* Include */
#include <IScale_DynClamp.h>
#include <iostream>
#include <math.h>
#include <main_window.h>

#include <QtGui>

//#include "/usr/local/rtxi/plugins/data_recorder/data_recorder.h"
#include "/home/ansel/Projects/rtxi/plugins/data_recorder/data_recorder.h"

using namespace std;

// Create Module Instance
extern "C" Plugin::Object *createRTXIPlugin(void) {
    return new IScale_DynClamp::Module();
}

// Inputs, Outputs, and Parameters
static Workspace::variable_t vars[] = {
    {
        "Input Voltage (V)", "Input Voltage (V)", Workspace::INPUT, }, // Voltage of target cell, from amplifier, input(0)
    {
        "Output Current (A)", "Output Current (A)", Workspace::OUTPUT, }, //  Current sent to target cell, to internal input, output(0)
    // States
    {
        "Time (ms)", "Time Elapsed (ms)", Workspace::STATE, }, 
    {
        "Voltage (mv)", "Membrane voltage of target cell (mv)", Workspace::STATE, }, // Voltage in mV, converted from amplifier input
    {
        "Beat Number", "Number of beats", Workspace::STATE, },
    {
        "APD (ms)", "Action Potential Duration of cell (ms)", Workspace::STATE, },
    // Hidden States
    {
        "Target Curent (A/F)", "Value of model current targeted for scaling (A/F)", Workspace::STATE, },
    {
        "Scaled Target Current (A/F)", "Value of model current after scaling (A/F)", Workspace::STATE, },
    // Parameters
    {
        "APD Repolarization %", "APD Repolarization %", Workspace::PARAMETER, },
    {
        "Minimum APD (ms)", "Minimum depolarization duration considered to be an action potential (ms)", Workspace::PARAMETER, },
    {
        "Stim Window (ms)", "Window of time after stimulus that is ignored by APD calculation", Workspace::PARAMETER, }, 
    {
        "Number of Trials", "Number of times the protocol will be repeated", Workspace::PARAMETER, }, 
    {
        "Interval Time (ms)", "Amont of time between each trial", Workspace::PARAMETER, }, 
    {
        "BCL (ms)", "Basic Cycle Length", Workspace::PARAMETER, }, 
    {
        "Stim Mag (nA)", "Amplitude of stimulation pulse (nA)", Workspace::PARAMETER, }, 
    {
        "Stim Length (ms)", "Duration of stimulation pulse (nA", Workspace::PARAMETER, }, 
    {
        "Cm (pF)", "Membrane capacitance of target cell (pF)", Workspace::PARAMETER, },
    {
        "LJP (mv)", "Liquid Junction Potential (mV)", Workspace::PARAMETER, },    
};

// Number of variables in vars
static size_t num_vars = sizeof(vars) / sizeof(Workspace::variable_t);

IScale_DynClamp::Module::Module(void) : QWidget( MainWindow::getInstance()->centralWidget() ), RT::Thread( 0 ), Workspace::Instance( "Current-scaling Dynamic Clamp", vars, num_vars ) {

    // Build Module GUI
	 QWidget::setAttribute(Qt::WA_DeleteOnClose);
    createGUI();        
    initialize(); // Initialize parameters, initialize states, reset model, and update rate
    refreshDisplay();
    show();
} // End constructor

IScale_DynClamp::Module::~Module(void) {
    delete protocol;
    modelCell = NULL;
    delete livshitzRudy2009;
    delete faberRudy2000;
} // End destructor

void IScale_DynClamp::Module::execute(void) { // Real-Time Execution
    voltage = input(0) * 1e3 - LJP;

    switch( executeMode ) {
    case IDLE:
        break;

    case THRESHOLD:
        // Apply stimulus for given number of ms (StimLength) 
        if( time - cycleStartTime <= stimLength ) {
            backToBaseline = false;
            peakVoltageT = Vrest;
            output( 0 ) = stimulusLevel * 1e-9; // stimulsLevel is in nA, convert to A for amplifier
        }
        
        else {
            output( 0 ) = 0;

            if( voltage > peakVoltageT ) // Find peak voltage after stimulus
                peakVoltageT = voltage;

            // If Vm is back to resting membrane potential (within 2 mV; determined when threshold detection button is first pressed) 
            if( voltage-Vrest < 2 ) { // Vrest: voltage at the time threshold test starts
                if ( !backToBaseline ) {
                    responseDuration = time-cycleStartTime;
                    responseTime = time;
                    backToBaseline = true;
                }

                // Calculate time length of voltage response
                if( responseDuration > 50 && peakVoltageT > 10 ) { // If the response was more than 50ms long and peakVoltage is more than 10mV, consider it an action potential
                    stimMag = stimulusLevel*1.5; // Set the current stimulus value as the calculated threshold * 2
                    thresholdOn = false;
                    executeMode = IDLE;
                }
                // If no action potential occurred, and Vm is back to rest 
                else {

                    // If the cell has rested for  200ms since returning to baseline 
                    if( time-responseTime > 200 ) {
                        stimulusLevel += 0.1; // Increase the magnitude of the stimulus and try again 
                        cycleStartTime = time; // Record the time of stimulus application 
                    }   
                }
            }
        }
        time += period;
        break;

    case PACE:
        
        time += period;
        stepTime += 1;
        // If time is greater than BCL, advance the beat
        if ( stepTime - cycleStartTime >= BCLInt ) {
            beatNum++;            
            cycleStartTime = stepTime;
            Vrest = voltage;
            calculateAPD( 1 ); // First step of APD calculation called at each stimulus
        }
        
        // Stimulate cell for stimLength(ms)
        if ( (stepTime - cycleStartTime) < stimLengthInt )
            outputCurrent = stimMag * 1e-9; // stimMag in nA, convert to A for amplifier
        else
            outputCurrent = 0;

        // Inject Current
        output( 0 ) = outputCurrent;
        //Calulate APD
        calculateAPD( 2 ); // Second step of APD calculation
        break;

    case PROTOCOL:

        time += period;
        stepTime += 1;
        
        if( protocolMode == STEPINIT ) {
            if( recordData && !recording && currentStep == 0 ) { // Record data if dataRecord is toggled
                Event::Object event(Event::START_RECORDING_EVENT);
                Event::Manager::getInstance()->postEventRT(&event);
            }
            
            modelInit = true;                                
            // Model changes do not use up a thread loop by themselves
            // Using a while loop makes sure if multiple model changes are called
            // consecutively, they will all be called within one execute loop
            while( modelInit ) {
                if( currentStep >= protocolContainer->size() ) {// If end of protocol has been reached
                    protocolMode = END;
                    modelInit = false;
                }
                else {
                    stepPtr = protocolContainer->at( currentStep );
                    stepType = stepPtr->stepType;

                    if( stepType == ProtocolStep::CHANGEMODEL ) {
                        if( stepPtr->modelType == ProtocolStep::LIVRUDY2009 )
                            modelCell = livshitzRudy2009;
                        else
                            modelCell = faberRudy2000;
                        currentStep++;
                    }
                    else if( stepType == ProtocolStep::STARTMODEL ) {
                        voltageClamp = true;
                        currentStep++;
                    }
                    else if( stepType == ProtocolStep::STOPMODEL ) {
                        voltageClamp = false;
                        currentStep++;
                    }
                    else if( stepType == ProtocolStep::RESETMODEL ) {
                        modelCell->resetModel();
                        currentStep++;
                    }
                    else { 
                        stepTime = 0;
                        cycleStartTime = 0;

                        if( stepType == ProtocolStep::PACE || stepType == ProtocolStep::SCALE)
                            stepEndTime = (( stepPtr->BCL * stepPtr->numBeats ) / period ) - 1; // -1 since time starts at 0, not 1
                        else
                            stepEndTime = ( stepPtr->waitTime / period ) - 1; // -1 since time starts at 0, not 1
                        
                        pBCLInt = stepPtr->BCL / period; // BCL for protocol
                        protocolMode = EXEC;
                        beatNum++;
                        Vrest = voltage;
                        calculateAPD( 1 );
                        modelInit = false;
                    }
                    
                } // end else
            } // end while( modelInit )
        } // end STEPINIT
        
        if( protocolMode == EXEC ) { // Execute protocol
            if( stepType == ProtocolStep::PACE || stepType == ProtocolStep::SCALE) { // Pace cell at BCL
                if (stepTime - cycleStartTime >= pBCLInt){
                    beatNum++;
                    cycleStartTime = stepTime;
                    Vrest = voltage;
                    calculateAPD( 1 );
                }
                // Stimulate cell for stimLength(ms)
                if ( (stepTime - cycleStartTime) < stimLengthInt )
                    outputCurrent = stimMag * 1e-9;
                else
                    outputCurrent = 0;

                if( voltageClamp || stepType == ProtocolStep::SCALE )
                    totalModelCurrent = modelCell->voltageClamp(voltage);
                
                if( stepType == ProtocolStep::SCALE) { // If Scaling step, scale current
                    targetCurrent = modelCell->getParameter( stepPtr->currentToScale );
                    scaledCurrent = targetCurrent + ( targetCurrent * ( stepPtr->scalingPercentage / 100.0 ) );
                    outputCurrent += ( targetCurrent - scaledCurrent ) *  Cm * 1e-12; // Scale current to cell size; Cm in pF, convert to F
                }
                
                output(0) = outputCurrent;
                calculateAPD(2);

                
            } // end if(PACE || SCALE)
        
            else { // If stepType = WAIT
                output(0) = 0;
            }
            
            if( stepTime >= stepEndTime ) {
                currentStep++;
                protocolMode = STEPINIT;
            }            
        } // end EXEC

        if( protocolMode == END ) { // End of Protocol: Stop Data recorder and untoggle button
            if(recording == true) {
                Event::Object event(Event::STOP_RECORDING_EVENT);
                Event::Manager::getInstance()->postEventRT(&event);
            }
            protocolOn = false;
            executeMode = IDLE;
        } // end END
        
    } // end switch( executeMode )     
} // end execute()

void IScale_DynClamp::Module::initialize(void){ // Initialize all variables, protocol, and model cell
std::cout<<"initialize called"<<std::endl;
    protocol = new Protocol();
    livshitzRudy2009 = new ModelCell();
    livshitzRudy2009->changeModel( ModelCell::LIVRUDY2009 );
    faberRudy2000 = new ModelCell();
    faberRudy2000->changeModel( ModelCell::FABERRUDY2000 );
    modelCell = livshitzRudy2009; // Livshitz Rudy model is the default

    protocolContainer = &protocol->protocolContainer; // Pointer to protocol container
        
    // States
    time = 0;
    voltage = 0;
    beatNum = 0;
    APD = 0;
    targetCurrent = 0;
    scaledCurrent = 0;

    // Parameters
    APDRepol = 90;    
    minAPD = 50;
    stimWindow = 4;
    numTrials = 1;
    intervalTime = 1000;
    BCL = 1000;
    stimMag = 4;
    stimLength = 1;
    Cm = 100;
    LJP = 0;

    mainWindow->APDRepolEdit->setText( QString::number(APDRepol) );
    mainWindow->minAPDEdit->setText( QString::number(minAPD) );
    mainWindow->stimWindowEdit->setText( QString::number(stimWindow) );
    mainWindow->numTrialEdit->setText( QString::number(numTrials) );
    mainWindow->intervalTimeEdit->setText( QString::number(intervalTime) );
    mainWindow->BCLEdit->setText( QString::number(BCL) );
    mainWindow->stimMagEdit->setText( QString::number(stimMag) );
    mainWindow->stimLengthEdit->setText( QString::number(stimLength) );
    mainWindow->CmEdit->setText( QString::number(Cm) );
    mainWindow->LJPEdit->setText( QString::number(LJP) );

    // Flags
    recordData = mainWindow->recordDataCheckBox->isChecked();
    recording = false;
    voltageClamp = false;
    modelInit = true;
    loadedFile = "";
    protocolOn = false;

    // APD parameters
   upstrokeThreshold = -40;
std::cout<<"initialize returned"<<std::endl;
}

void IScale_DynClamp::Module::reset( void ) {
    period = RT::System::getInstance()->getPeriod()*1e-6; // Grabs RTXI thread period and converts to ms (from ns)
    BCLInt = BCL / period;
    stimLengthInt = stimLength / period;
    modelCell->setModelRate(100000, period);
     
    stepTime = -1;
    time = -period;
    cycleStartTime = 0;
    beatNum = 1;
    Vrest = voltage;
    calculateAPD( 1 );

    // Protocol variables
    currentStep = 0;
    targetCurrent = 0;
    scaledCurrent = 0;
}

void IScale_DynClamp::Module::addStep( void ) {
    int idx = mainWindow->protocolEditorListBox->currentRow();
    if( idx == -1 ) { // Protocol is empty or nothing is selected, add step to end
        if( protocol->addStep( this ) )   // Update protocolEditorListBox if a step was added
            rebuildListBox();
    }
    else // If a step is selected, add step after
        if( protocol->addStep( this, idx ) )   // Update protocolEditorListBox if a step was added
            rebuildListBox();            
}

void IScale_DynClamp::Module::deleteStep( void ) {
    int idx = mainWindow->protocolEditorListBox->currentRow();
    if( idx == -1 ) // Protocol is empty or nothing is selected, return
        return ;
    
    protocol->deleteStep( this, idx ); // Delete the currently selected step in the list box
    rebuildListBox();
}

void IScale_DynClamp::Module::saveProtocol( void ) {
    protocol->saveProtocol( this );
}

void IScale_DynClamp::Module::loadProtocol( void ) {
    loadedFile = protocol->loadProtocol( this );
    rebuildListBox();
}

void IScale_DynClamp::Module::clearProtocol( void ) {
    protocol->clearProtocol();
    rebuildListBox();
}

void IScale_DynClamp::Module::toggleThreshold( void ) {
std::cout<<"toggleThreshold called"<<std::endl;
    thresholdOn = mainWindow->thresholdButton->isChecked();
    
    ToggleThresholdEvent event( this, thresholdOn );
std::cout<<"before postEvent called for type: "<<std::endl;//event->getName()<<std::endl;
    RT::System::getInstance()->postEvent( &event );
std::cout<<"toggleThreshold returned"<<std::endl;
}

void IScale_DynClamp::Module::toggleProtocol( void ) {
    protocolOn = mainWindow->startProtocolButton->isChecked();
    
    if( protocolOn ){
        if( protocolContainer->size() <= 0 ) {
            QMessageBox::warning( this, "Error", "Protocol has yet to be defined." );
            mainWindow->startProtocolButton->setChecked( false );
            protocolOn = false;
        }
    }

    ToggleProtocolEvent event( this, protocolOn );
    RT::System::getInstance()->postEvent( &event );
}

void IScale_DynClamp::Module::togglePace( void ) {
    paceOn = mainWindow->staticPacingButton->isChecked();

    TogglePaceEvent event( this, paceOn );
    RT::System::getInstance()->postEvent( &event );
}

void IScale_DynClamp::Module::changeModel( int idx ) {
    if( idx ) // Index 1 -> FaberRudy
        modelCell = faberRudy2000; // Old model is deleted and new one is instanciated
    else // Index 0 -> LivShitz Rudy
        modelCell = livshitzRudy2009;
}

/*** Other Functions ***/

void IScale_DynClamp::Module::Module::calculateAPD(int step){ // Two APDs are calculated based on different criteria
    switch( step ) {
    case 1:
        APDMode = START;
        break;

    case 2:
        switch( APDMode ) { 
        case START:// Find time membrane voltage passes upstroke threshold, start of AP            
            if( voltage >= upstrokeThreshold ) {
                APStart = time;
                peakVoltage = Vrest;
                APDMode = PEAK;
            }
            break;
            
        case PEAK: // Find peak of AP, points within "window" are ignored to eliminate effect of stimulus artifact
            if( (time - APStart) > stimWindow ) { // If we are outside the chosen time window after the AP
                if( peakVoltage < voltage  ) { // Find peak voltage                    
                    peakVoltage = voltage;
                    peakTime = time;
                }
                else if ( (time - peakTime) > 5 ) { // Keep looking for the peak for 5ms to account for noise
                    double APAmp;                    
                    APAmp = peakVoltage - Vrest ; // Amplitude of action potential based on resting membrane and peak voltage
                    // Calculate downstroke threshold based on AP amplitude and desired AP repolarization %
                    downstrokeThreshold = peakVoltage - ( APAmp * (APDRepol / 100.0) );
                    APDMode = DOWN;
                }
            }
            break;
            
        case DOWN: // Find downstroke threshold and calculate APD
            if( voltage <= downstrokeThreshold ) {
                APD = time - APStart;
                APDMode = DONE;
            }
            break;

        default: // DONE: APD has been found, do nothing
            break;
        }
    }
}

// Rebuilds list box, run after modifying protocol
void IScale_DynClamp::Module::rebuildListBox( void ) {
    mainWindow->protocolEditorListBox->clear(); // Clear list box

    // Rebuild list box
    for( int i = 0; i < protocolContainer->size(); i++ ) {
        mainWindow->protocolEditorListBox->insertItem( i,  protocol->getStepDescription( i ) );
    }
}
/* Build Module GUI */
void IScale_DynClamp::Module::createGUI( void ) {
std::cout<<"createGUI called"<<std::endl;

    QMdiSubWindow *subWindow  = new QMdiSubWindow;
    subWindow->setWindowTitle( QString::number( getID() ) + " Current Scaling Dynamic Clamp" );
	 subWindow->setWindowIcon(QIcon("/usr/local/lib/rtxi/RTXI-widget-icon.png"));
	 subWindow->setMinimumSize(300,450);
	 MainWindow::getInstance()->createMdi(subWindow); 
	 subWindow->setWidget(this);

//    mainWindow = new IScale_DynClampUI(this);
    mainWindow = new IScale_DynClampUI(subWindow);
    // Construct Main Layout - vertical layout
//    QBoxLayout *layout = new QVBoxLayout(subWindow);
    QVBoxLayout *layout = new QVBoxLayout(this);
//	 setLayout(layout);
	 layout->addWidget(mainWindow);

    // Model Combo Box
    mainWindow->modelComboBox->addItem("LivRudy 2009");
    mainWindow->modelComboBox->addItem("FaberRudy 2000");

    // Set GUI refresh rate
    QTimer *timer = new QTimer(this);
    timer->start(500);

    // Set validators
    mainWindow->APDRepolEdit->setValidator( new QIntValidator(mainWindow->APDRepolEdit) );
    mainWindow->minAPDEdit->setValidator( new QIntValidator(mainWindow->minAPDEdit) );
    mainWindow->stimWindowEdit->setValidator( new QIntValidator(mainWindow->stimWindowEdit) );
    mainWindow->numTrialEdit->setValidator( new QIntValidator(mainWindow->numTrialEdit) );
    mainWindow->intervalTimeEdit->setValidator( new QIntValidator(mainWindow->intervalTimeEdit) );
    mainWindow->BCLEdit->setValidator( new QIntValidator(mainWindow->BCLEdit) );
    mainWindow->stimMagEdit->setValidator( new QDoubleValidator(mainWindow->stimMagEdit) );
    mainWindow->stimLengthEdit->setValidator( new QDoubleValidator(mainWindow->stimLengthEdit) );
    mainWindow->CmEdit->setValidator( new QDoubleValidator(mainWindow->CmEdit) );
    mainWindow->LJPEdit->setValidator( new QDoubleValidator(mainWindow->CmEdit) );
    
    // Connect MainWindow elements to slot functions
    QObject::connect( mainWindow->addStepButton, SIGNAL(clicked(void)), this, SLOT( addStep(void)) );
    QObject::connect( mainWindow->deleteStepButton, SIGNAL(clicked(void)), this, SLOT( deleteStep(void)) );
    QObject::connect( mainWindow->saveProtocolButton, SIGNAL(clicked(void)), this, SLOT( saveProtocol(void)) );
    QObject::connect( mainWindow->loadProtocolButton, SIGNAL(clicked(void)), this, SLOT( loadProtocol(void)) );
    QObject::connect( mainWindow->clearProtocolButton, SIGNAL(clicked(void)), this, SLOT( clearProtocol(void)) );
    QObject::connect( mainWindow->recordDataCheckBox, SIGNAL(clicked(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->startProtocolButton, SIGNAL(clicked(void)), this, SLOT( toggleProtocol(void)) );
    QObject::connect( mainWindow->thresholdButton, SIGNAL(clicked(void)), this, SLOT( toggleThreshold(void)) );
    QObject::connect( mainWindow->staticPacingButton, SIGNAL(clicked(void)), this, SLOT( togglePace(void)) );
    QObject::connect( mainWindow->resetButton, SIGNAL(clicked(void)), this, SLOT( reset(void)) );
    QObject::connect( mainWindow->modelComboBox, SIGNAL(activated(int)), this, SLOT( changeModel(int)) );    
    QObject::connect( mainWindow->APDRepolEdit, SIGNAL(returnPressed(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->minAPDEdit, SIGNAL(returnPressed(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->stimWindowEdit, SIGNAL(returnPressed(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->numTrialEdit, SIGNAL(returnPressed(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->intervalTimeEdit, SIGNAL(returnPressed(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->BCLEdit, SIGNAL(returnPressed(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->stimMagEdit, SIGNAL(returnPressed(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->stimLengthEdit, SIGNAL(returnPressed(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->CmEdit, SIGNAL(returnPressed(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->LJPEdit, SIGNAL(returnPressed(void)), this, SLOT( modify(void)) );
    QObject::connect(timer, SIGNAL(timeout(void)), this, SLOT(refreshDisplay(void)));

    // Connections to allow only one button being toggled at a time
    QObject::connect( mainWindow->thresholdButton, SIGNAL(toggled(bool)), mainWindow->staticPacingButton, SLOT( setDisabled(bool)) );
    QObject::connect( mainWindow->thresholdButton, SIGNAL(toggled(bool)), mainWindow->startProtocolButton, SLOT( setDisabled(bool)) );
    QObject::connect( mainWindow->startProtocolButton, SIGNAL(toggled(bool)), mainWindow->staticPacingButton, SLOT( setDisabled(bool)) );
    QObject::connect( mainWindow->startProtocolButton, SIGNAL(toggled(bool)), mainWindow->thresholdButton, SLOT( setDisabled(bool)) );
    QObject::connect( mainWindow->staticPacingButton, SIGNAL(toggled(bool)), mainWindow->thresholdButton, SLOT( setDisabled(bool)) );
    QObject::connect( mainWindow->staticPacingButton, SIGNAL(toggled(bool)), mainWindow->startProtocolButton, SLOT( setDisabled(bool)) );
                      
    // Connect states to workspace
    setData( Workspace::STATE, 0, &time );
    setData( Workspace::STATE, 1, &voltage );
    setData( Workspace::STATE, 2, &beatNum );
    setData( Workspace::STATE, 3, &APD );
    setData( Workspace::STATE, 4, &targetCurrent );
    setData( Workspace::STATE, 5, &scaledCurrent );

	 show();
std::cout<<"createGUI returned"<<std::endl;
} // End createGUI()

// Load from Settings
void IScale_DynClamp::Module::doLoad(const Settings::Object::State &s) {
    if (s.loadInteger("Maximized"))
        showMaximized();
    else if (s.loadInteger("Minimized"))
        showMinimized();
    
    if (s.loadInteger("W") != NULL) {
        resize(s.loadInteger("W"), s.loadInteger("H"));
        parentWidget()->move(s.loadInteger("X"), s.loadInteger("Y"));
    }

    loadedFile = QString::fromStdString(s.loadString("Protocol"));
    if( loadedFile != "" ) {        
        protocol->loadProtocol( this, loadedFile );
        rebuildListBox();
    }

    mainWindow->APDRepolEdit->setText( QString::number( s.loadInteger("APD Repol") ) );
    mainWindow->minAPDEdit->setText( QString::number( s.loadInteger("Min APD") ) );
    mainWindow->stimWindowEdit->setText( QString::number( s.loadInteger("Stim Window") ) );
    mainWindow->numTrialEdit->setText( QString::number( s.loadInteger("Num Trials") ) );
    mainWindow->intervalTimeEdit->setText( QString::number( s.loadInteger("Interval Time") ) );
    mainWindow->BCLEdit->setText( QString::number( s.loadInteger("BCL") ) );
    mainWindow->stimMagEdit->setText( QString::number( s.loadInteger("Stim Mag") ) );
    mainWindow->stimLengthEdit->setText( QString::number( s.loadInteger("Stim Length") ) );
    mainWindow->CmEdit->setText( QString::number( s.loadInteger("Cm") ) );
    mainWindow->LJPEdit->setText( QString::number( s.loadInteger("LJP") ) );    
    
    modify();
}

// Save Settings
void IScale_DynClamp::Module::doSave(Settings::Object::State &s) const {
    if (isMaximized())
        s.saveInteger( "Maximized", 1 );
    else if (isMinimized())
        s.saveInteger( "Minimized", 1 );

    QPoint pos = parentWidget()->pos();
    s.saveInteger( "X", pos.x() );
    s.saveInteger( "Y", pos.y() );
    s.saveInteger( "W", width() );
    s.saveInteger( "H", height() );
    s.saveString( "Protocol", loadedFile.toStdString() );
    s.saveInteger( "APD Repol", APDRepol );
    s.saveInteger( "Min APD", minAPD );
    s.saveInteger( "Stim Window", stimWindow );
    s.saveInteger( "Num Trials", numTrials);
    s.saveInteger( "Interval Time", intervalTime );
    s.saveInteger( "BCL", BCL );
    s.saveDouble( "Stim Mag", stimMag );
    s.saveDouble( "Stim Length", stimLength );
    s.saveDouble( "Cm", Cm );
    s.saveDouble( "LJP", LJP );
}
void IScale_DynClamp::Module::modify(void) {
    int APDr = mainWindow->APDRepolEdit->text().toInt();
    int mAPD = mainWindow->minAPDEdit->text().toInt();
    int sw = mainWindow->stimWindowEdit->text().toInt();
    int nt = mainWindow->numTrialEdit->text().toInt();
    int it = mainWindow->intervalTimeEdit->text().toInt();
    int b = mainWindow->BCLEdit->text().toInt();
    double sm = mainWindow->stimMagEdit->text().toDouble();
    double sl = mainWindow->stimLengthEdit->text().toDouble();
    double c = mainWindow->CmEdit->text().toDouble();
    double ljp = mainWindow->LJPEdit->text().toDouble();
    bool rd = mainWindow->recordDataCheckBox->isChecked();

    if( APDr == APDRepol && mAPD == minAPD && sw == stimWindow && nt == numTrials && it == intervalTime
        && b == BCL && sm == stimMag && sl == stimLength && c == Cm && ljp == LJP && rd == recordData ) // If nothing has changed
        return ;

    // Set parameters
    setValue( 0, APDr );
    setValue( 1, mAPD );
    setValue( 2, sw );
    setValue( 3, nt );
    setValue( 4, it );
    setValue( 5, b );
    setValue( 6, sm );
    setValue( 7, sl );
    setValue( 8, c );
    setValue( 9, ljp );

    ModifyEvent event( this, APDr, mAPD, sw, nt, it, b, sm, sl, c, ljp, rd );
    RT::System::getInstance()->postEvent( &event );
}

void IScale_DynClamp::Module::refreshDisplay(void) {
    mainWindow->timeEdit->setText( QString::number(time) );
    mainWindow->voltageEdit->setText( QString::number(voltage) );
    mainWindow->beatNumEdit->setText( QString::number(beatNum) );
    mainWindow->APDEdit->setText( QString::number(APD) );

    if( executeMode == IDLE ) {
        if( mainWindow->startProtocolButton->isChecked() && !protocolOn )
            mainWindow->startProtocolButton->setChecked( false );
        else if( mainWindow->thresholdButton->isChecked() && !thresholdOn ) {
            mainWindow->thresholdButton->setChecked( false );
            mainWindow->stimMagEdit->setText( QString::number( stimMag ) );
            modify();
        }
    }
    else if( executeMode == PROTOCOL ) {
        if( stepTracker != currentStep ) {
            stepTracker = currentStep;
            mainWindow->protocolEditorListBox->setCurrentRow( currentStep);
        }        
    }
}

// RT::Events - Called from GUI thread, handled by RT thread
IScale_DynClamp::Module::ToggleProtocolEvent::ToggleProtocolEvent( Module *m, bool o )
    : module( m ), on( o ) {
}

int IScale_DynClamp::Module::ToggleProtocolEvent::callback( void ) {
    if( on ) { // Start protocol, reinitialize parameters to start values
        
        module->executeMode = IDLE; // Keep on IDLE until update is finished
        module->voltageClamp = false;
        module->modelInit = true;
        module->reset();
        module->modelCell->resetModel();
        module->beatNum = 0; // beatNum is changed at beginning of protocol, so it must start at 0 instead of 1
        module->stepTracker = -1; // Used to highlight the current step in list box, -1 to force first step to be highlighted
        module->protocolMode = STEPINIT; 
        module->executeMode = PROTOCOL;
        module->setActive( true );
    }
    else { // Stop protocol, only called when protocol button is unclicked in the middle of a run
        if( module->recording ) { // Stop data recorder if recording
            ::Event::Object event(::Event::STOP_RECORDING_EVENT);
            ::Event::Manager::getInstance()->postEventRT(&event);
        }        
        module->executeMode = IDLE;
        module->setActive( false );
    }
    
    return 0;
}

IScale_DynClamp::Module::TogglePaceEvent::TogglePaceEvent( Module *m, bool o )
    : module( m ), on( o ) {
}

int IScale_DynClamp::Module::TogglePaceEvent::callback( void ) {
    if( on ) { // Start protocol, reinitialize parameters to start values
        module->reset();
        module->executeMode = PACE;
        module->setActive( true );
    }
    else { // Stop protocol, only called when pace button is unclicked in the middle of a run
        if( module->recording ) { // Stop data recorder if recording
            ::Event::Object event(::Event::STOP_RECORDING_EVENT);
            ::Event::Manager::getInstance()->postEventRT(&event);
        }        
        module->executeMode = IDLE;
        module->setActive( false );
    }
    
    return 0;
}

IScale_DynClamp::Module::ToggleThresholdEvent::ToggleThresholdEvent( Module *m, bool o )
    : module( m ), on( o ) {
}

int IScale_DynClamp::Module::ToggleThresholdEvent::callback( void ) {
    if( on ) { // Start protocol, reinitialize parameters to start values
        
        module->executeMode = THRESHOLD;
        module->reset();
        module->Vrest = module->input(0) * 1e3;
        module->peakVoltageT = module->Vrest;
        module->stimulusLevel = 2.0; // na
        module->responseDuration = 0;
        module->responseTime = 0;
        module->setActive( true );
    }
    else { // Stop protocol, only called when pace button is unclicked in the middle of a run
        module->executeMode = IDLE;
        module->setActive( false );
    }
    
    return 0;
}
 
IScale_DynClamp::Module::ModifyEvent::ModifyEvent( Module *m, int APDr, int mAPD, int sw,
                                                   int nt, int it, int b, double sm, double sl, double c, double ljp, bool rd )
    : module( m ), APDRepolValue( APDr ), minAPDValue( mAPD ), stimWindowValue( sw ),
      numTrialsValue( nt ), intervalTimeValue( it ), BCLValue( b ), stimMagValue( sm ),
      stimLengthValue( sl ), CmValue( c ), LJPValue( ljp ), recordDataValue( rd ) {
}

int IScale_DynClamp::Module::ModifyEvent::callback( void ) {
    module->APDRepol = APDRepolValue;
    module->minAPD = minAPDValue;
    module->numTrials = numTrialsValue;
    module->intervalTime = intervalTimeValue;
    module->BCL = BCLValue;
    module->BCLInt = module->BCL / module->period; // Update BCLInt when BCL is updated
    module->stimMag = stimMagValue;
    module->stimLength = stimLengthValue;
    module->Cm = CmValue;
    module->LJP = LJPValue;
    module->recordData = recordDataValue;
    
    return 0;
}

// Event handling
void IScale_DynClamp::Module::receiveEvent( const ::Event::Object *event ) {
std::cout<<"receiveEvent called for type: "<<event->getName()<<std::endl;
    if( event->getName() == Event::RT_POSTPERIOD_EVENT ) {
        period = RT::System::getInstance()->getPeriod()*1e-6; // Grabs RTXI thread period and converts to ms (from ns)
        BCLInt = BCL / period;
        stimLengthInt = stimLength / period;
        modelCell->setModelRate(100000, period);
    }
    if( event->getName() == Event::START_RECORDING_EVENT )
        recording = true;
    if( event->getName() == Event::STOP_RECORDING_EVENT )
        recording = false;
}

void IScale_DynClamp::Module::receiveEventRT( const ::Event::Object *event ) {
std::cout<<"receiveEventRT called for type: "<<event->getName()<<std::endl;
    if( event->getName() == Event::RT_POSTPERIOD_EVENT ) {
        period = RT::System::getInstance()->getPeriod()*1e-6; // Grabs RTXI thread period and converts to ms (from ns)
        BCLInt = BCL / period;
        stimLengthInt = stimLength / period;
        modelCell->setModelRate(100000, period);
    }
    if( event->getName() == Event::START_RECORDING_EVENT )
        recording = true;
    if( event->getName() == Event::STOP_RECORDING_EVENT )
        recording = false;
}

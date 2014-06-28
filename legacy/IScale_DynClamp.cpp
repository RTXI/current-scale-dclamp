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
#include <qlistbox.h>
#include <qtooltip.h>
#include <qvalidator.h>
#include <qtimer.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qstring.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qmessagebox.h>

#include "/usr/local/rtxi/plugins/data_recorder/data_recorder.h"

using namespace std;

/* SyncEvent: Required for modify(), pause(), and exit() overloading */
namespace {
    class SyncEvent: public RT::Event {
    public:
        int callback(void) {
            return 0;
        };
    }; // class SyncEvent
} // namespace

/* Create Module Instance */
extern "C" Plugin::Object *createRTXIPlugin(void) {
    return new IScale_DynClamp();
}

/* Inputs, Outputs, and Parameters for DefaultGUIModel */
static IScale_DynClamp::variable_t vars[] = {
    {
        "Input Voltage (V)", "Input Voltage (V)", IScale_DynClamp::INPUT, }, // Voltage of target cell, from amplifier, input(0)
    {
        "Output Current (A)", "Output Current (A)", IScale_DynClamp::OUTPUT, }, //  Current sent to target cell, to internal input, output(0)
    {
        "Time (ms)", "Time Elapsed (ms)", IScale_DynClamp::STATE, }, 
    {
        "Voltage (mv)", "Membrane voltage of target cell (mv)", IScale_DynClamp::STATE, }, // Voltage in mV, converted from amplifier input
    {
        "Beat Number", "Number of beats", IScale_DynClamp::STATE, },
    {
        "APD (ms)", "Action Potential Duration of cell (ms)", IScale_DynClamp::STATE, }, 
    {
        "APD Repolarization %", "APD Repolarization %", IScale_DynClamp::PARAMETER | IScale_DynClamp::INTEGER, },
    {
        "Minimum APD (ms)", "Minimum depolarization duration considered to be an action potential (ms)", IScale_DynClamp::PARAMETER | IScale_DynClamp::INTEGER, }, 
    {
        "Number of Trials", "Number of times the protocol will be repeated", IScale_DynClamp::PARAMETER | IScale_DynClamp::INTEGER, }, 
    {
        "Interval Time (ms)", "Amont of time between each trial", IScale_DynClamp::PARAMETER | IScale_DynClamp::INTEGER, }, 
    {
        "BCL (ms)", "Basic Cycle Length", IScale_DynClamp::PARAMETER | IScale_DynClamp::INTEGER, }, 
    {
        "Stim Mag (nA)", "Amplitude of stimulation pulse (nA)", IScale_DynClamp::PARAMETER | IScale_DynClamp::DOUBLE, }, 
    {
        "Stim Length (ms)", "Duration of stimulation pulse (nA", IScale_DynClamp::PARAMETER | IScale_DynClamp::DOUBLE, }, 
    {
        "Cm (pF)", "Membrane capacitance of target cell (pF)", IScale_DynClamp::PARAMETER | IScale_DynClamp::DOUBLE, },

    // Hidden States
    {
        "Target Curent (A/F)", "Value of model current targeted for scaling (A/F)", IScale_DynClamp::STATE, },
    {
        "Scaled Target Current (A/F)", "Value of model current after scaling (A/F)", IScale_DynClamp::STATE, }, 
};

/* Required variable */
static size_t num_vars = sizeof(vars) / sizeof(IScale_DynClamp::variable_t);

/* Constructor */
IScale_DynClamp::IScale_DynClamp(void) :
    DefaultGUIModel("IScale_DynClamp",::vars,::num_vars) {

    // Build Module GUI
    createGUI(vars, num_vars);

    // Set GUI refresh rate
    QTimer *timer = new QTimer(this);
    timer->start(100);
    QObject::connect(timer, SIGNAL(timeout(void)), this, SLOT(refresh(void)));
    show();
    
    initialize(); // Initialize parameters, initialize states, reset model, and update rate

    refresh();
} // End constructor

/* Destructor */
IScale_DynClamp::~IScale_DynClamp(void) {
    delete protocol;
    delete mainWindow;
    delete modelCell;
} // End destructor

/* Real-Time Execution */
void IScale_DynClamp::execute(void) {
    voltage = input(0) * 1e3;

    switch( executeMode ) {
    case IDLE:
        break;

    case THRESHOLD:
        // Apply stimulus for given number of ms (StimLength) 
        if( time - cycleStartTime <= stimLength ) {
            backToBaseline = false;
            peakVoltage = Vrest;
            output( 0 ) = stimulusLevel * 1e-9; // stimulsLevel is in nA, convert to A for amplifier
        }
        
        else {
            output( 0 ) = 0;

            if( voltage > peakVoltage ) // Find peak voltage after stimulus
                peakVoltage = voltage;

            // If Vm is back to resting membrane potential (within 2 mV; determined when threshold detection button is first pressed) 
            if( voltage-Vrest < 2 ) { // Vrest: voltage at the time threshold test starts
                if ( !backToBaseline ) {
                    responseDuration = time-cycleStartTime;
                    responseTime = time;
                    backToBaseline = true;
                }

                // Calculate time length of voltage response
                if( responseDuration > 50 && peakVoltage > 10 ) { // If the response was more than 50ms long and peakVoltage is more than 10mV, consider it an action potential
                    stimMag = stimulusLevel*1.5; // Set the current stimulus value as the calculated threshold * 2
                    threshold = false;
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
        if( recordData && !recording ){ // Record data if dataRecord is toggled
            DataRecorder::startRecording();
            recording = true;
        }
        
        time += period;
        stepTime += 1;
        // If time is greater than BCL, advance the beat
        if ( stepTime - cycleStartTime >= BCLInt ) {
            beatNum++;
            
            cycleStartTime = stepTime;
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
                DataRecorder::startRecording();
                recording = true;
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
                    
                    if( stepType == ProtocolStep::STARTMODEL ) {
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
                        calculateAPD(1);
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
                    calculateAPD(1);
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
            if(recordData == true)
                DataRecorder::stopRecording();
            protocolOn = false;
            executeMode = IDLE;
        } // end END
        
    } // end switch( executeMode )     
} // end execute()

/* Non-Real-Time Update */
void IScale_DynClamp::update(IScale_DynClamp::update_flags_t flag) {
    switch(flag){
        
    case MODIFY: // The parameters have been modified by the user
        // Get Parameters
        APDRepol = getParameter("APD Repolarization %").toInt();
        minAPD = getParameter("Minimum APD (ms)").toInt();
        numTrials = getParameter("Number of Trials").toInt();
        intervalTime = getParameter("Interval Time (ms)").toInt();
        BCL = getParameter("BCL (ms)").toInt();
        stimMag = getParameter("Stim Mag (nA)").toDouble();
        stimLength = getParameter("Stim Length (ms)").toDouble();
        Cm = getParameter("Cm (pF)").toDouble();
        update(PERIOD);
        break;

    case RESET:
        update(PERIOD);
        stepTime = -1;
        time = -period;
        cycleStartTime = 0;
        beatNum = 1;
        Vrest = voltage;
        APD_start = -1;
        upstroke_threshold = Vrest - (Vrest*0.50);
        downstroke_threshold = Vrest * ( APDRepol / 100.0) ;

        // Protocol variables
        currentStep = 0;
        targetCurrent = 0;
        scaledCurrent = 0;
        break;

    case RESETMODEL:
        modelCell->resetModel();
        break;
            
    case PERIOD: // The system period has changed
        period = RT::System::getInstance()->getPeriod()*1e-6; // Grabs RTXI thread period and converts to ms (from ns)
        BCLInt = BCL / period;
        stimLengthInt = stimLength / period;
        modelCell->setModelRate(100000, period);
        break;
                
    case PAUSE: // The Pause button has been activated
        break;
                    
    case UNPAUSE: // When the pause button has been deactivated
        update(PERIOD);
        break;
                
    case EXIT: // When the module has been told to exit
        break;
        
    } // End switch(flag)
} // End update()

/* Initializiation */
void IScale_DynClamp::initialize(void){
    protocol = new Protocol();
    modelCell = new ModelCell();
    modelCell->changeModel( ModelCell::LIVRUDY2009 );
    protocolContainer = &protocol->protocolContainer; // Pointer to protocol container
        
    // States
    time = 0;
    voltage = 0;
    beatNum = 0;
    APD = 0;
    targetCurrent = 0;
    scaledCurrent = 0;
    setState( "Time (ms)", time );
    setState( "Voltage (mv)", voltage );
    setState( "Beat Number", beatNum );
    setState( "APD (ms)", APD );
    setState( "Target Curent (A/F)", targetCurrent );
    setState( "Scaled Target Current (A/F)", scaledCurrent );

    // Parameters
    APDRepol = 90;
    minAPD = 50;
    numTrials = 1;
    intervalTime = 1000;
    BCL = 1000;
    stimMag = 4;
    stimLength = 1;
    Cm = 100;
    setParameter("APD Repolarization %", APDRepol);
    setParameter("Minimum APD (ms)", minAPD);
    setParameter("Number of Trials", numTrials);
    setParameter("Interval Time (ms)", intervalTime);
    setParameter("BCL (ms)", BCL);
    setParameter("Stim Mag (nA)", stimMag);
    setParameter("Stim Length (ms)", stimLength);
    setParameter("Cm (pF)", Cm);

    // Flags
    recordData = mainWindow->recordDataCheckBox->isChecked();
    recording = false;
    voltageClamp = false;
    modelInit = true;
    loadedFile = "";
    threshold = false;
    protocolOn = false;
    
    update(PERIOD); // Get period
}

/*** Slot Functions ***/

void IScale_DynClamp::reset( void ) {
    update(RESET);
}

void IScale_DynClamp::addStep( void ) {
    int idx = mainWindow->protocolEditorListBox->currentItem();
    if( idx == -1 ) { // Protocol is empty or nothing is selected, add step to end
        if( protocol->addStep( this ) )   // Update protocolEditorListBox if a step was added
            rebuildListBox();
    }
    else // If a step is selected, add step after
        if( protocol->addStep( this, idx ) )   // Update protocolEditorListBox if a step was added
            rebuildListBox();            
}

void IScale_DynClamp::deleteStep( void ) {
    int idx = mainWindow->protocolEditorListBox->currentItem();
    if( idx == -1 ) // Protocol is empty or nothing is selected, return
        return ;
    
    protocol->deleteStep( this, idx ); // Delete the currently selected step in the list box
    rebuildListBox();
}

void IScale_DynClamp::saveProtocol( void ) {
    protocol->saveProtocol( this );
}

void IScale_DynClamp::loadProtocol( void ) {
    loadedFile = protocol->loadProtocol( this );
    rebuildListBox();
}

void IScale_DynClamp::clearProtocol( void ) {
    protocol->clearProtocol();
    rebuildListBox();
}

void IScale_DynClamp::toggleRecordData( bool toggled ) {
    if( toggled )
        recordData = true;
    else
        recordData = false;
}

void IScale_DynClamp::toggleProtocol( bool toggled ) {
    protocolOn = toggled;
    
    if( toggled ){
        if( protocolContainer->size() > 0 ) {
            executeMode = IDLE; // Keep on IDLE until update is finished
            recording = false;
            voltageClamp = false;
            modelInit = true;
            update(RESET); // Reset timings
            update(RESETMODEL);
            beatNum = 0; // beatNum is changed at beginning of protocol, so it must start at 0 instead of 1
            protocolMode = STEPINIT; 
            executeMode = PROTOCOL;
        }
        else {
            QMessageBox::warning( this, "Error", "Protocol has yet to be defined." );
            mainWindow->startProtocolButton->setOn( false );
        }
    }
    else{
        if(recording) DataRecorder::stopRecording(); // True if protocol is prematurely ended by clicking button
        recording = false;
        voltageClamp = false;
        executeMode = IDLE;
    }
}

void IScale_DynClamp::toggleThreshold( bool toggled ) {
    threshold = toggled;
    
    if( toggled ){
        Vrest = input(0)*1e3;
        peakVoltage = Vrest;
        stimulusLevel = 1e-9;
        responseDuration = 0;
        responseTime = 0;
        update(RESET);
        executeMode = THRESHOLD;
    }
    else{
        executeMode = IDLE;
        setParameter("Stim Mag (nA)",stimMag); // Set StimMag parameter
    }
}

void IScale_DynClamp::togglePace( bool toggled ) {
    if( toggled ){
        executeMode = IDLE; // Keep on IDLE until update is finished
        recording = false;
        update(RESET); // Reset timings
        executeMode = PACE;
    }
    else{
        if(recording) DataRecorder::stopRecording(); // True if protocol is prematurely ended by clicking button
        recording = false;
        executeMode = IDLE;
    }
}

void IScale_DynClamp::changeModel( int idx ) {
    if( idx ) // Index 1 -> FaberRudy
        modelCell->changeModel( ModelCell::FABERRUDY2000 ); // Old model is deleted and new one is instanciated
    else // Index 0 -> LivShitz Rudy
        modelCell->changeModel( ModelCell::LIVRUDY2009 );
}

/*** Other Functions ***/

/* Calculated APD function */
void IScale_DynClamp::calculateAPD(int step) {

    switch(step) {

    case 1:
        if(APD_start == 1) { // Update only after AP has finished
            APD_start = -1;
            Vrest = voltage;
            upstroke_threshold = Vrest - (Vrest*0.50);
            downstroke_threshold = Vrest * ( APDRepol / 100.0 ) ;
        }
        
    case 2:
        // Update start time after voltage has passed depolarization threshold
        if(APD_start == -1 && voltage > upstroke_threshold) { 
            APD_start_time = time;
            APD_start = 0;
        }
        // Calculate APD once voltage has passed repolarization threshold and is greater than minimum APD
        if(APD_start == 0 && voltage < downstroke_threshold && (time - APD_start_time) > minAPD) { 
            APD_end_time = time;
            APD_start = 1;
            APD = APD_end_time - APD_start_time;
        }

        break;
        
    default:
        cout << "\nErrorr: *default case called* IScale_DynCLamp::calculateAPD()";
        break;
    }
}

// Rebuilds list box, run after modifying protocol
void IScale_DynClamp::rebuildListBox( void ) {
    mainWindow->protocolEditorListBox->clear(); // Clear list box

    // Rebuild list box
    for( int i = 0; i < protocolContainer->size(); i++ ) {
        mainWindow->protocolEditorListBox->insertItem( protocol->getStepDescription( i ) );
    }
}
/* Build Module GUI */
void IScale_DynClamp::createGUI(DefaultGUIModel::variable_t *var, int size) {
    mainWindow = new IScale_DynClampUI(this);
    // Construct Main Layout - vertical layout
    QBoxLayout *layout = new QVBoxLayout(this);

    // The following is a workaroud to incorporate custom GUI items in a default_gui format

    param_t param;
    size_t nstate = 0, nparam = 0, i=2;
    // Manually set parameter array
    // Time
    param.label = mainWindow->timeLabel;
    param.edit = mainWindow->timeEdit;
    param.type = STATE;
    param.index = nstate++;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // Voltage
    param.label = mainWindow->voltageLabel;
    param.edit = mainWindow->voltageEdit;
    param.type = STATE;
    param.index = nstate++;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // beatNum
    param.label = mainWindow->beatNumLabel;
    param.edit = mainWindow->beatNumEdit;
    param.type = STATE;
    param.index = nstate++;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // APD
    param.label = mainWindow->APDLabel;
    param.edit = mainWindow->APDEdit;
    param.type = STATE;
    param.index = nstate++;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // APDRepol
    param.label = mainWindow->APDRepolLabel;
    param.edit = mainWindow->APDRepolEdit;
    param.edit->setValidator(new QIntValidator(param.edit));
    param.type = PARAMETER | INTEGER;
    param.index = nparam++;
    param.str_value = new QString;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // minAPD
    param.label = mainWindow->minAPDLabel;
    param.edit = mainWindow->minAPDEdit;
    param.edit->setValidator(new QIntValidator(param.edit));
    param.type = PARAMETER | INTEGER;
    param.index = nparam++;
    param.str_value = new QString;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // numTrial
    param.label = mainWindow->numTrialLabel;
    param.edit = mainWindow->numTrialEdit;
    param.edit->setValidator(new QIntValidator(param.edit));
    param.type = PARAMETER | INTEGER;
    param.index = nparam++;
    param.str_value = new QString;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // intervalTime
    param.label = mainWindow->intervalTimeLabel;
    param.edit = mainWindow->intervalTimeEdit;
    param.edit->setValidator(new QIntValidator(param.edit));
    param.type = PARAMETER | INTEGER;
    param.index = nparam++;
    param.str_value = new QString;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // BCL
    param.label = mainWindow->BCLLabel;
    param.edit = mainWindow->BCLEdit;
    param.edit->setValidator(new QIntValidator(param.edit));
    param.type = PARAMETER | INTEGER;
    param.index = nparam++;
    param.str_value = new QString;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // stimMag
    param.label = mainWindow->stimMagLabel;
    param.edit = mainWindow->stimMagEdit;
    param.edit->setValidator(new QDoubleValidator(param.edit));
    param.type = PARAMETER | DOUBLE;
    param.index = nparam++;
    param.str_value = new QString;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // stimLength
    param.label = mainWindow->stimLengthLabel;
    param.edit = mainWindow->stimLengthEdit;
    param.edit->setValidator(new QDoubleValidator(param.edit));
    param.type = PARAMETER | DOUBLE;
    param.index = nparam++;
    param.str_value = new QString;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
 
    // Cm
    param.label = mainWindow->CmLabel;
    param.edit = mainWindow->CmEdit;
    param.edit->setValidator(new QDoubleValidator(param.edit));
    param.type = PARAMETER | DOUBLE;
    param.index = nparam++;
    param.str_value = new QString;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;
        
    // Hidden States
    QWidget *hiddenWidget = new QWidget( this );
    hiddenWidget->setEnabled(false);
    hiddenWidget->setHidden(true);
    
    // Target Current *Hidden*
    param.label = new QLabel( var[i].name, hiddenWidget );
    param.edit = new DefaultGUILineEdit( hiddenWidget );
    param.type = STATE;
    param.index = nstate++;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;

    // Scaled Target Current *Hidden*
    param.label = new QLabel( var[i].name, hiddenWidget );
    param.edit = new DefaultGUILineEdit( hiddenWidget );
    param.type = STATE;
    param.index = nstate++;
    parameter[var[i].name] = param;
    QToolTip::add(param.label, vars[i].description);
    QToolTip::add(param.edit, vars[i].description);
    i++;

    // Model Combo Box
    mainWindow->modelComboBox->insertItem("LivRudy 2009");
    mainWindow->modelComboBox->insertItem("FaberRudy 2000");
    
    // Connect MainWindow elements to slot functions
    pauseButton = mainWindow->pauseButton;
    QObject::connect( pauseButton, SIGNAL(toggled(bool)), this, SLOT(pause(bool)) );
    QObject::connect( mainWindow->modifyButton, SIGNAL(clicked(void)), this, SLOT( modify(void)) );
    QObject::connect( mainWindow->unloadButton, SIGNAL(clicked(void)), this, SLOT( exit(void)) );
    QObject::connect( mainWindow->addStepButton, SIGNAL(clicked(void)), this, SLOT( addStep(void)) );
    QObject::connect( mainWindow->deleteStepButton, SIGNAL(clicked(void)), this, SLOT( deleteStep(void)) );
    QObject::connect( mainWindow->saveProtocolButton, SIGNAL(clicked(void)), this, SLOT( saveProtocol(void)) );
    QObject::connect( mainWindow->loadProtocolButton, SIGNAL(clicked(void)), this, SLOT( loadProtocol(void)) );
    QObject::connect( mainWindow->clearProtocolButton, SIGNAL(clicked(void)), this, SLOT( clearProtocol(void)) );
    QObject::connect( mainWindow->recordDataCheckBox, SIGNAL(toggled(bool)), this, SLOT( toggleRecordData(bool)) );
    QObject::connect( mainWindow->startProtocolButton, SIGNAL(toggled(bool)), this, SLOT( toggleProtocol(bool)) );
    QObject::connect( mainWindow->thresholdButton, SIGNAL(toggled(bool)), this, SLOT( toggleThreshold(bool)) );
    QObject::connect( mainWindow->staticPacingButton, SIGNAL(toggled(bool)), this, SLOT( togglePace(bool)) );
    QObject::connect( mainWindow->resetButton, SIGNAL(clicked(void)), this, SLOT( reset(void)) );
    QObject::connect( mainWindow->modelComboBox, SIGNAL(activated(int)), this, SLOT( changeModel(int)) );    
    
    layout->addWidget(mainWindow);
	show();
} // End createGUI()

/***
 * Overloaded DefaultGUIModel Functions
 ***/   

/* Load from Settings */
void IScale_DynClamp::doLoad(const Settings::Object::State &s) {
    for (std::map<QString, param_t>::iterator i = parameter.begin(); i
             != parameter.end(); ++i)
        i->second.edit->setText(s.loadString(i->first));
    if (s.loadInteger("Maximized"))
        showMaximized();
    else if (s.loadInteger("Minimized"))
        showMinimized();
    // this only exists in RTXI versions >1.3
    if (s.loadInteger("W") != NULL) {
        resize(s.loadInteger("W"), s.loadInteger("H"));
        parentWidget()->move(s.loadInteger("X"), s.loadInteger("Y"));
    }

    loadedFile = s.loadString("Protocol");
    if( loadedFile != "" ) {        
        protocol->loadProtocol( this, loadedFile );
        rebuildListBox();
    }

    pauseButton->setOn(s.loadInteger("paused"));
    modify();
}

/*** Overloaded DefaultGUIModel Functions ***/

/* Save Settings */
void IScale_DynClamp::doSave(Settings::Object::State &s) const {
    s.saveInteger("paused", pauseButton->isOn());
    if (isMaximized())
        s.saveInteger("Maximized", 1);
    else if (isMinimized())
        s.saveInteger("Minimized", 1);

    QPoint pos = parentWidget()->pos();
    s.saveInteger("X", pos.x());
    s.saveInteger("Y", pos.y());
    s.saveInteger("W", width());
    s.saveInteger("H", height());

    s.saveString("Protocol", loadedFile);

    for (std::map<QString, param_t>::const_iterator i = parameter.begin(); i
             != parameter.end(); ++i)
        s.saveString(i->first, i->second.edit->text());
}

/*** Required Functions to Overload if Using Specific Set of Update Flags ***/

void IScale_DynClamp::pause(bool p) {
	if (pauseButton->isOn() != p)
		pauseButton->setDown(p);

	setActive(!p);
	if (p)
		update(PAUSE);
	else
		update(UNPAUSE);
}

void IScale_DynClamp::modify(void) {
	bool active = getActive();

	setActive(false);

	// Ensure that the realtime thread isn't in the middle of executing IScale_DynClamp::execute()
	SyncEvent event;
	RT::System::getInstance()->postEvent(&event);

	for (std::map<QString, param_t>::iterator i = parameter.begin(); i != parameter.end(); ++i)
		if (i->second.type & COMMENT)
			Workspace::Instance::setComment( i->second.index, i->second.edit->text().latin1() );

	update(MODIFY);
	setActive(active);

	for (std::map<QString, param_t>::iterator i = parameter.begin(); i != parameter.end(); ++i)
		i->second.edit->blacken();
}

void IScale_DynClamp::exit(void) {
	update(EXIT);
	Plugin::Manager::getInstance()->unload(this);
}

void IScale_DynClamp::refresh(void) {
	for (std::map<QString, param_t>::iterator i = parameter.begin(); i
			!= parameter.end(); ++i) {
		if (i->second.type & (STATE | EVENT)) {
			i->second.edit->setText(QString::number(getValue(i->second.type,
					i->second.index)));
			i->second.edit->setPaletteForegroundColor(Qt::darkGray);
		} else if ((i->second.type & PARAMETER) && !i->second.edit->edited()
				&& i->second.edit->text() != *i->second.str_value) {
			i->second.edit->setText(*i->second.str_value);
		} else if ((i->second.type & COMMENT) && !i->second.edit->edited()
				&& i->second.edit->text() != getValueString(COMMENT,
						i->second.index)) {
			i->second.edit->setText(getValueString(COMMENT, i->second.index));
		}
	}
	pauseButton->setOn(!getActive());
    if(mainWindow->thresholdButton->isOn())
        mainWindow->thresholdButton->setOn(threshold);
    if(mainWindow->startProtocolButton->isOn())
        mainWindow->startProtocolButton->setOn(protocolOn);
}

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

#include <IScale_DynClamp.h>
#include <math.h>
#include <main_window.h>
#include <data_recorder.h>

#include <QtGlobal>
#if QT_VERSION >= 0x050000
	#include <QtWidgets>
#else
	#include <QtGui>
#endif

using namespace std;

namespace {
	class IScale_DynClamp_SyncEvent : public RT::Event {
		public:
			int callback(void) {
				return 0;
			}
	};
}

// Create Module Instance
extern "C" Plugin::Object *createRTXIPlugin(void) {
    return new IScale_DynClamp::Module();
}

// INPUTs, OUTPUTs, PARAMETERs, and STATEs
static Workspace::variable_t vars[] = {
	{ "Input Voltage (V)", "Input voltage (V) from target cell", 
	  Workspace::INPUT, }, 
	{ "Output Current (A)", "Output current (A) to target cell or internal input", 
	  Workspace::OUTPUT, }, 
	{ "Time (ms)", "Time Elapsed (ms)", Workspace::STATE, }, 
	{ "Voltage (mV)", 
	  "Membrane voltage (mV) of target cell computed from amplifier input", 
	  Workspace::STATE, }, 
	{ "Beat Number", "Number of beats", Workspace::STATE, },
	{ "APD (ms)", "Action potential duration of cell (ms)", Workspace::STATE, },
	{ "Target Curent (A/F)", 
	  "Value of model current targeted for scaling (A/F)", Workspace::STATE, },
	{ "Scaled Target Current (A/F)", 
	  "Value of model current after scaling (A/F)", Workspace::STATE, },
	{ "APD Repolarization %", "APD Repolarization %", Workspace::PARAMETER, },
	{ "Minimum APD (ms)", 
	  "Minimum depolarization duration considered to be an action potential (ms)", 
	  Workspace::PARAMETER, },
	{ "Stim Window (ms)", 
	  "Window of time after stimulus that is ignored by APD calculation", 
	  Workspace::PARAMETER, }, 
	{ "Number of Trials", "Number of times the protocol will be repeated", 
	  Workspace::PARAMETER, }, 
	{ "Interval Time (ms)", "Amont of time between each trial", 
	  Workspace::PARAMETER, }, 
	{ "BCL (ms)", "Basic Cycle Length", Workspace::PARAMETER, }, 
	{ "Stim Mag (nA)", "Amplitude of stimulation pulse (nA)", 
	  Workspace::PARAMETER, }, 
	{ "Stim Length (ms)", "Duration of stimulation pulse (nA)", 
	  Workspace::PARAMETER, }, 
	{ "Cm (pF)", "Membrane capacitance of target cell (pF)", 
	  Workspace::PARAMETER, },
	{ "LJP (mv)", "Liquid Junction Potential (mV)", Workspace::PARAMETER, },
};

// Number of variables in vars
static size_t num_vars = sizeof(vars) / sizeof(Workspace::variable_t);

IScale_DynClamp::Module::Module(void) : 
	QWidget(MainWindow::getInstance()->centralWidget()), RT::Thread(0), 
           Workspace::Instance("Current-scaling Dynamic Clamp", vars, num_vars) {

// Build Module GUI
	//QWidget::setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(QString::number( getID() ) + " Current-scaling Dynamic Clamp");
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

	/*
	setActive(false);
	IScale_DynClamp_SyncEvent event;
	RT::System::getInstance()->postEvent(&event);
	Plugin::Manager::getInstance()->unload(this);
	mainWindow->close();
	*/
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

			// stimulsLevel is in nA, convert to A for amplifier
			output( 0 ) = stimulusLevel * 1e-9; 
		}

		else {
			output( 0 ) = 0;

			// Find peak voltage after stimulus
			if( voltage > peakVoltageT ) peakVoltageT = voltage;

			// If Vm is back to resting membrane potential (within 2 mV; 
			// determined when threshold detection button is first pressed) 
			// Vrest: voltage at the time threshold test starts
			if( voltage-Vrest < 2 ) { 
				if ( !backToBaseline ) {
					responseDuration = time-cycleStartTime;
					responseTime = time;
					backToBaseline = true;
				}

				// Calculate time length of voltage response
				// If the response was more than 50ms long and peakVoltage is 
				// more than 10mV, consider it an action potential
				if( responseDuration > 50 && peakVoltageT > 10 ) { 
					// Set the current stimulus value as the calculated threshold * 2
					stimMag = stimulusLevel*1.5; 
					thresholdOn = false;
					executeMode = IDLE;
				}
				// If no action potential occurred, and Vm is back to rest 
				else {

					// If the cell has rested for  200ms since returning to baseline 
					if( time-responseTime > 200 ) {
						// Increase the magnitude of the stimulus and try again 
						stimulusLevel += 0.1; 

						// Record the time of stimulus application 
						cycleStartTime = time; 
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
			// First step of APD calculation called at each stimulus
			calculateAPD( 1 ); 
		}

		// Stimulate cell for stimLength(ms)
		if ( (stepTime - cycleStartTime) < stimLengthInt ) {
			// stimMag in nA, convert to A for amplifier
			outputCurrent = stimMag * 1e-9; 
		}
		else outputCurrent = 0;

		// Inject Current
		output( 0 ) = outputCurrent;

		//Calulate APD
		calculateAPD( 2 ); // Second step of APD calculation
		break;

	case PROTOCOL:
		time += period;
		stepTime += 1;

		switch( protocolMode ) {
		case STEPINIT:
			// Record data if dataRecord is toggled
			if( recordData && !recording && currentStep == 0 ) {
				Event::Object event(Event::START_RECORDING_EVENT);
				Event::Manager::getInstance()->postEventRT(&event);
				recording = true;
			}

			modelInit = true;                                
			// Model changes do not use up a thread loop by themselves
			// Using a while loop makes sure if multiple model changes are called
			// consecutively, they will all be called within one execute loop
			while( modelInit ) {
				// If end of protocol has been reached
				if( currentStep >= protocolContainer->size() ) {
					protocolMode = END;
					modelInit = false;
				}
				else {
					stepPtr = protocolContainer->at( currentStep );
					stepType = stepPtr->stepType;

					switch( stepType ) {
					case ProtocolStep::CHANGEMODEL:
						if( stepPtr->modelType == ProtocolStep::LIVRUDY2009 ) {
							modelCell = livshitzRudy2009;
						}
						else modelCell = faberRudy2000;
						currentStep++;
						break;

					case ProtocolStep::STARTMODEL:
						voltageClamp = true;
						currentStep++;
						break;

					case ProtocolStep::STOPMODEL:
						voltageClamp = false;
						currentStep++;
						break;

					case ProtocolStep::RESETMODEL:
						modelCell->resetModel();
						currentStep++;
						break;

					case ProtocolStep::PACE:
						stepTime = 0;
						cycleStartTime = 0;
						// set to -1 since time starts at 0, not 1
						stepEndTime = (( stepPtr->BCL * stepPtr->numBeats ) / period ) - 1; 

						pBCLInt = stepPtr->BCL / period; // BCL for protocol
//						pDIInt = stepPtr->DI / period; // DI for protocol
						protocolMode = EXEC;
						beatNum++;
						Vrest = voltage;
						calculateAPD( 1 );
						modelInit = false;
						break;

					case ProtocolStep::SCALE:
						stepTime = 0;
						cycleStartTime = 0;
						// set to -1 since time starts at 0, not 1
						stepEndTime = (( stepPtr->BCL * stepPtr->numBeats ) / period ) - 1; 

						pBCLInt = stepPtr->BCL / period; // BCL for protocol
//						pDIInt = stepPtr->DI / period; // DI for protocol
						protocolMode = EXEC;
						beatNum++;
						Vrest = voltage;
						calculateAPD( 1 );
						modelInit = false;
						break;

					case ProtocolStep::DIPACE:
						stepTime = 0;
						cycleStartTime = 0;
						stepEndBeat = beatNum + stepPtr->numBeats; 

						// pad stepEndTime to hell to avoid setting off:
						//    if( stepTime => stepEndTime ) {...}
						stepEndTime = (( 1 * stepPtr->numBeats ) / period ) - 1; 

//						pBCLInt = stepPtr->BCL / period; // BCL for protocol
						pDIInt = stepPtr->DI / period; // DI for protocol
						protocolMode = EXEC;
						beatNum++;
						Vrest = voltage;
						calculateAPD( 1 );
						modelInit = false;
						break;

					case ProtocolStep::DISCALE:
						stepTime = 0;
						cycleStartTime = 0;
						stepEndBeat = beatNum + stepPtr->numBeats; 

						// pad stepEndTime to hell to avoid setting off:
						//    if( stepTime => stepEndTime ) {...}
						stepEndTime = (( 1 * stepPtr->numBeats ) / period ) - 1; 

//						pBCLInt = stepPtr->BCL / period; // BCL for protocol
						pDIInt = stepPtr->DI / period; // DI for protocol
						protocolMode = EXEC;
						beatNum++;
						Vrest = voltage;
						calculateAPD( 1 );
						modelInit = false;
						break;

					case ProtocolStep::WAIT:
						stepTime = 0;
						cycleStartTime = 0;
						stepEndTime = ( stepPtr->waitTime / period ) - 1; 

//						pBCLInt = stepPtr->BCL / period; // BCL for protocol
//						pDIInt = stepPtr->DI / period; // DI for protocol
						protocolMode = EXEC;
						beatNum++;
						Vrest = voltage;
//						calculateAPD( 1 );
						modelInit = false;
						break;

					default:
						break;

					} // end switch( stepType )
				} // end else
			} // end while( modelInit )
			break; // end STEPINIT

		case EXEC: // execute protocol
			// Pace cell at BCL
			switch( stepType ) {
			case ProtocolStep::PACE:
				if ( stepTime - cycleStartTime >= pBCLInt ) {
					beatNum++;
					cycleStartTime = stepTime;
					Vrest = voltage;
					calculateAPD( 1 );
				}
				// Stimulate cell for stimLength(ms)
				if ( (stepTime - cycleStartTime) < stimLengthInt ) {
					outputCurrent = stimMag * 1e-9;
				}
				else outputCurrent = 0;

				// voltage clamp the model; returns totalModelCurrent for 
				// debugging purposes only
				if( voltageClamp ) {
					totalModelCurrent = modelCell->voltageClamp(voltage);
				}

				output(0) = outputCurrent;
				calculateAPD(2);
				break;

			case ProtocolStep::SCALE:
				if ( stepTime - cycleStartTime >= pBCLInt ) {
					beatNum++;
					cycleStartTime = stepTime;
					Vrest = voltage;
					calculateAPD( 1 );
				}
				// Stimulate cell for stimLength(ms)
				if ( (stepTime - cycleStartTime) < stimLengthInt ) {
					outputCurrent = stimMag * 1e-9;
				}
				else outputCurrent = 0;

				// required for SCALE?
				totalModelCurrent = modelCell->voltageClamp(voltage);

				// If Scaling step, scale current
				targetCurrent = modelCell->getParameter( stepPtr->currentToScale );
				scaledCurrent = targetCurrent + ( targetCurrent * ( stepPtr->scalingPercentage / 100.0 ) );
				
				// Scale current to cell size; Cm in pF, convert to F
				outputCurrent += ( targetCurrent - scaledCurrent ) *  Cm * 1e-12; 

				output(0) = outputCurrent;
				calculateAPD(2);
				break;

			case ProtocolStep::DIPACE:
				if ( APDMode == DONE ) {
					if ( stepTime - APEndStepTime >= pDIInt ) {
						if ( beatNum < stepEndBeat ) {
							cycleStartTime = stepTime;
							beatNum++;
							Vrest = voltage;
							calculateAPD(1);
						}
						else {
							currentStep++;
							protocolMode = STEPINIT;
						}
					}
				}
				
				// Stimulate cell for stimLength(ms)
				if ( (stepTime - cycleStartTime) < stimLengthInt ) {
					outputCurrent = stimMag * 1e-9;
				}
				else outputCurrent = 0;

				// voltage clamp the model; returns totalModelCurrent for 
				// debugging purposes only
				if( voltageClamp ) {
					totalModelCurrent = modelCell->voltageClamp(voltage);
				}
				
				output(0) = outputCurrent;
				calculateAPD(2);
				stepEndTime++;
				break;

			case ProtocolStep::DISCALE:
				if ( APDMode == DONE ) {
					if ( time - APEnd  >= (pDIInt * period) ) {
						if ( beatNum < stepEndBeat ) {
							cycleStartTime = stepTime;
							beatNum++;
							Vrest = voltage;
							calculateAPD(1);
						}
						else {
							currentStep++;
							protocolMode = STEPINIT;
						}
					}
				}
				
				// Stimulate cell for stimLength(ms)
				if ( (stepTime - cycleStartTime) < stimLengthInt ) {
					outputCurrent = stimMag * 1e-9;
				}
				else outputCurrent = 0;

				// required for DISCALE?
				totalModelCurrent = modelCell->voltageClamp(voltage);
				
				// If Scaling step, scale current
				targetCurrent = modelCell->getParameter( stepPtr->currentToScale );
				scaledCurrent = targetCurrent + ( targetCurrent * ( stepPtr->scalingPercentage / 100.0 ) );
				
				// Scale current to cell size; Cm in pF, convert to F
				outputCurrent += ( targetCurrent - scaledCurrent ) *  Cm * 1e-12; 

				output(0) = outputCurrent;
				calculateAPD(2);
				stepEndTime++;
				break;

			case ProtocolStep::WAIT:
				output(0) = 0;
				break;

			default:
				break;
			} // end switch( stepType)

			if( stepTime >= stepEndTime ) {
				currentStep++;
				protocolMode = STEPINIT;
			}            
			break; // end EXEC

		case END:
			// End of Protocol: Stop Data recorder and untoggle button
			if(recording == true) {
				Event::Object event(Event::STOP_RECORDING_EVENT);
				Event::Manager::getInstance()->postEventRT(&event);
				recording = false;
			}
			protocolOn = false;
			executeMode = IDLE;
			break;// end END

		default:
			break;

		} // end switch( protocolMode )
	} // end switch( executeMode )     
} // end execute()

/*
		if( protocolMode == STEPINIT ) { 
			// Record data if dataRecord is toggled
			if( recordData && !recording && currentStep == 0 ) {
				Event::Object event(Event::START_RECORDING_EVENT);
				Event::Manager::getInstance()->postEventRT(&event);
				recording = true;
			}

			modelInit = true;                                
			// Model changes do not use up a thread loop by themselves
			// Using a while loop makes sure if multiple model changes are called
			// consecutively, they will all be called within one execute loop
			while( modelInit ) {
				// If end of protocol has been reached
				if( currentStep >= protocolContainer->size() ) {
					protocolMode = END;
					modelInit = false;
				}
				else {
					stepPtr = protocolContainer->at( currentStep );
					stepType = stepPtr->stepType;

					if( stepType == ProtocolStep::CHANGEMODEL ) {
						if( stepPtr->modelType == ProtocolStep::LIVRUDY2009 ) {
							modelCell = livshitzRudy2009;
						}
						else modelCell = faberRudy2000;
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

						if( stepType == ProtocolStep::PACE || stepType == ProtocolStep::SCALE ) {
							// set to -1 since time starts at 0, not 1
							stepEndTime = (( stepPtr->BCL * stepPtr->numBeats ) / period ) - 1; 
						}
						else if( stepType == ProtocolStep::DIPACE || stepType == ProtocolStep::DISCALE ) {
							stepEndBeat = beatNum + stepPtr->numBeats; 

							// pad stepEndTime to hell to avoid setting off:
							//    if( stepTime => stepEndTime ) {...}
							stepEndTime = (( 1 * stepPtr->numBeats ) / period ) - 1; 
						}
						else {
							// set to -1 since time starts at 0, not 1
							stepEndTime = ( stepPtr->waitTime / period ) - 1; 
						}

						pBCLInt = stepPtr->BCL / period; // BCL for protocol
						pDIInt = stepPtr->DI / period; // DI for protocol
						protocolMode = EXEC;
						beatNum++;
						Vrest = voltage;
						calculateAPD( 1 );
						modelInit = false;
					}
				} // end else
			} // end while( modelInit )
		} // end STEPINIT
*/

/*
		if( protocolMode == EXEC ) { // Execute protocol 
			// Pace cell at BCL
			if( stepType == ProtocolStep::PACE || stepType == ProtocolStep::SCALE) {
				if ( stepTime - cycleStartTime >= pBCLInt ) {
					beatNum++;
					cycleStartTime = stepTime;
					Vrest = voltage;
					calculateAPD( 1 );
				}
				// Stimulate cell for stimLength(ms)
				if ( (stepTime - cycleStartTime) < stimLengthInt ) {
					outputCurrent = stimMag * 1e-9;
				}
				else outputCurrent = 0;

				if( voltageClamp || stepType == ProtocolStep::SCALE ) {
					totalModelCurrent = modelCell->voltageClamp(voltage);
				}

			  	// If Scaling step, scale current
				if( stepType == ProtocolStep::SCALE) {
					targetCurrent = modelCell->getParameter( stepPtr->currentToScale );
					scaledCurrent = targetCurrent + 
					                ( targetCurrent * ( stepPtr->scalingPercentage / 100.0 ) );
					
					// Scale current to cell size; Cm in pF, convert to F
					outputCurrent += ( targetCurrent - scaledCurrent ) *  Cm * 1e-12; 
				}

				output(0) = outputCurrent;
				calculateAPD(2);

			} // end if(PACE || SCALE)
			
			// Stimulate based on set diastolic intervals
			else if( stepType == ProtocolStep::DIPACE || stepType == ProtocolStep::DISCALE) {
				
				if ( APDMode == DONE ) {
					if ( time - APEnd  >= (pDIInt * period) ) {
						if ( beatNum < stepEndBeat ) {
							cycleStartTime = stepTime;
							beatNum++;
							Vrest = voltage;
							calculateAPD(1);
						}
						else {
							currentStep++;
							protocolMode = STEPINIT;
						}
					}
				}
				
				// Stimulate cell for stimLength(ms)
				if ( (stepTime - cycleStartTime) < stimLengthInt ) {
					outputCurrent = stimMag * 1e-9;
				}
				else outputCurrent = 0;

				if( voltageClamp || stepType == ProtocolStep::DISCALE ) {
					totalModelCurrent = modelCell->voltageClamp(voltage);
				}
			  	
				// If Scaling step, scale current
				if( stepType == ProtocolStep::DISCALE) {
					targetCurrent = modelCell->getParameter( stepPtr->currentToScale );
					scaledCurrent = targetCurrent + 
					                ( targetCurrent * ( stepPtr->scalingPercentage / 100.0 ) );
					
					// Scale current to cell size; Cm in pF, convert to F
					outputCurrent += ( targetCurrent - scaledCurrent ) *  Cm * 1e-12; 
				}

				output(0) = outputCurrent;
				calculateAPD(2);
				stepEndTime++;
			} // end if(DIPACE || DISCALE)

			else { // If stepType = WAIT
				output(0) = 0;
			}

			if( stepTime >= stepEndTime ) {
				currentStep++;
				protocolMode = STEPINIT;
			}            
		} // end EXEC
*/

/*
		// End of Protocol: Stop Data recorder and untoggle button
		if( protocolMode == END ) { 
			if(recording == true) {
				Event::Object event(Event::STOP_RECORDING_EVENT);
				Event::Manager::getInstance()->postEventRT(&event);
				recording = false;
			}
			protocolOn = false;
			executeMode = IDLE;
		} // end END
*/

/*
	} // end switch( executeMode )     
} // end execute()
*/

// Initialize all variables, protocol, and model cell
void IScale_DynClamp::Module::initialize(void){ 
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
	executeMode = IDLE;

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
}

void IScale_DynClamp::Module::reset( void ) {
	// Grabs RTXI thread period and converts to ms (from ns)
	period = RT::System::getInstance()->getPeriod()*1e-6; 

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
	
	// Protocol is empty or nothing is selected, add step to end
	if( idx == -1 ) { 
		// Update protocolEditorListBox if a step was added
		if( protocol->addStep( this ) ) {
			rebuildListBox();
		}
	}

	// If a step is selected, add step after
	else {
		// Update protocolEditorListBox if a step was added
		if( protocol->addStep( this, idx ) ) {  
			rebuildListBox();
		}
	}
}

void IScale_DynClamp::Module::deleteStep( void ) {
	int idx = mainWindow->protocolEditorListBox->currentRow();
	
	// Protocol is empty or nothing is selected, return
	if( idx == -1 ) return ;

	// Delete the currently selected step in the list box
	protocol->deleteStep( this, idx ); 
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
	thresholdOn = mainWindow->thresholdButton->isChecked();

	setActive(false); //breakage maybe...
	IScale_DynClamp_SyncEvent event;
	RT::System::getInstance()->postEvent(&event);

	// Start protocol, reinitialize parameters to start values
	if( thresholdOn ) { 
		executeMode = THRESHOLD;
		reset();
		Vrest = input(0) * 1e3;
		peakVoltageT = Vrest;
		stimulusLevel = 2.0; // na
		responseDuration = 0;
		responseTime = 0;
		setActive( true );
	}
	// Stop protocol, only called when pace button is unclicked in the 
	// middle of a run
	else { 
		executeMode = IDLE;
		setActive( false );
	}

	//ToggleThresholdEvent event( this, thresholdOn );
	//RT::System::getInstance()->postEvent( &event );
}

void IScale_DynClamp::Module::toggleProtocol( void ) {
	bool protocolOn = mainWindow->startProtocolButton->isChecked();

	setActive(false);
	IScale_DynClamp_SyncEvent event;
	RT::System::getInstance()->postEvent(&event);

	if( protocolOn ){
		if( protocolContainer->size() <= 0 ) {
			QMessageBox * msgBox = new QMessageBox;
			msgBox->setWindowTitle("Error");
			msgBox->setText("I need a protocol first, buddy");
			msgBox->setStandardButtons(QMessageBox::Ok);
			msgBox->setDefaultButton(QMessageBox::NoButton);
			msgBox->setWindowModality(Qt::WindowModal);
			msgBox->open();
			protocolOn = false;
			executeMode = IDLE;
		} else {
			// Keep on IDLE until update is finished
			executeMode = IDLE;
			voltageClamp = false;
			modelInit = true;
			reset();
			modelCell->resetModel();
			
			// beatNum is changed at beginning of protocol, so it must start 
			// at 0 instead of 1
			beatNum = 0; 

			// Used to highlight the current step in list box, -1 to force first 
			// step to be highlighted
			stepTracker = -1; 

			protocolMode = STEPINIT; 
			executeMode = PROTOCOL;
			setActive( true );
		}
	} 
	// Stop protocol, only called when protocol button is unclicked in the 
	// middle of a run
	else {
		// Stop data recorder if recording
		if( recording ) {
			::Event::Object event(::Event::STOP_RECORDING_EVENT);
			::Event::Manager::getInstance()->postEventRT(&event);
			recording = false;
		} 
		executeMode = IDLE;
		setActive( false );
	}

	//ToggleProtocolEvent event( this, protocolOn );
	//RT::System::getInstance()->postEvent( &event );
}

void IScale_DynClamp::Module::togglePace( void ) {
	paceOn = mainWindow->staticPacingButton->isChecked();

	setActive(false);
	IScale_DynClamp_SyncEvent event;
	RT::System::getInstance()->postEvent(&event);

	// Start protocol, reinitialize parameters to start values
	if( paceOn ) { 
		reset();
		executeMode = PACE;
		setActive( true );
	}

	// Stop protocol, only called when pace button is unclicked in the 
	// middle of a run
	else { 
		// Stop data recorder if recording
		if( recording ) { 
			::Event::Object event(::Event::STOP_RECORDING_EVENT);
			::Event::Manager::getInstance()->postEventRT(&event);
			recording = false;
		}        
		executeMode = IDLE;
		setActive( false );
	}

	//TogglePaceEvent event( this, paceOn );
	//RT::System::getInstance()->postEvent( &event );
}

void IScale_DynClamp::Module::changeModel( int idx ) {
	// Old model is deleted and new one is instanciated
	if( idx ) // Index 1 -> FaberRudy
	modelCell = faberRudy2000; 
	else // Index 0 -> LivShitz Rudy
	modelCell = livshitzRudy2009;
}

/*** Other Functions ***/

// Two APDs are calculated based on different criteria
void IScale_DynClamp::Module::Module::calculateAPD(int step) { 
	switch( step ) {
	case 1:
		APDMode = START;
		break;

	case 2:
		switch( APDMode ) { 
		// Find time membrane voltage passes upstroke threshold, start of AP
		case START:
			if( voltage >= upstrokeThreshold ) {
				APStart = time;
				peakVoltage = Vrest;
				APDMode = PEAK;
			}
			break;

		// Find peak of AP, points within "window" are ignored to eliminate 
		// effect of stimulus artifact
		case PEAK: 
			// If we are outside the chosen time window after the AP
			if( (time - APStart) > stimWindow ) { 
				if( peakVoltage < voltage  ) { // Find peak voltage 
					peakVoltage = voltage;
					APPeak = time;
				}
				// Keep looking for the peak for 5ms to account for noise
				else if ( (time - APPeak) > 5 ) { 
					double APAmp;

					// Amplitude of action potential based on resting membrane 
					// and peak voltage
					APAmp = peakVoltage - Vrest ; 

					// Calculate downstroke threshold based on AP amplitude and 
					// desired AP repolarization %
					downstrokeThreshold = peakVoltage - ( APAmp * (APDRepol / 100.0) );

					APDMode = DOWN;
				}
			}
			break;

		case DOWN: // Find downstroke threshold and calculate APD
			if( voltage <= downstrokeThreshold ) {
				APEnd = time;
				APEndStepTime = stepTime;
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

void IScale_DynClamp::Module::printProtocol(void) {

}

/* Build Module GUI */
void IScale_DynClamp::Module::createGUI( void ) {

	QMdiSubWindow *subWindow  = new QMdiSubWindow;
	subWindow->setAttribute(Qt::WA_DeleteOnClose);
	subWindow->setWindowIcon(QIcon("/usr/local/lib/rtxi/RTXI-widget-icon.png"));
	subWindow->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | 
	                          Qt::WindowMinimizeButtonHint );
	MainWindow::getInstance()->createMdi(subWindow); 
	subWindow->setWidget(this);

	mainWindow = new IScale_DynClampUI(subWindow);
	// Construct Main Layout - vertical layout
	QVBoxLayout *layout = new QVBoxLayout(this);
	setLayout(layout);
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
	mainWindow->BCLEdit->setValidator( new QDoubleValidator(mainWindow->BCLEdit) );
	mainWindow->stimMagEdit->setValidator( new QDoubleValidator(mainWindow->stimMagEdit) );
	mainWindow->stimLengthEdit->setValidator( new QDoubleValidator(mainWindow->stimLengthEdit) );
	mainWindow->CmEdit->setValidator( new QDoubleValidator(mainWindow->CmEdit) );
	mainWindow->LJPEdit->setValidator( new QDoubleValidator(mainWindow->CmEdit) );

	// Connect MainWindow elements to slot functions
	QObject::connect( mainWindow->addStepButton, SIGNAL(clicked(void)), 
	                  this, SLOT( addStep(void)) );
	QObject::connect( mainWindow->deleteStepButton, SIGNAL(clicked(void)), 
	                  this, SLOT( deleteStep(void)) );
	QObject::connect( mainWindow->saveProtocolButton, SIGNAL(clicked(void)), 
	                  this, SLOT( saveProtocol(void)) );
	QObject::connect( mainWindow->loadProtocolButton, SIGNAL(clicked(void)), 
	                  this, SLOT( loadProtocol(void)) );
	QObject::connect( mainWindow->clearProtocolButton, SIGNAL(clicked(void)), 
	                  this, SLOT( clearProtocol(void)) );
	QObject::connect( mainWindow->recordDataCheckBox, SIGNAL(clicked(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect( mainWindow->startProtocolButton, SIGNAL(toggled(bool)), 
	                  this, SLOT( toggleProtocol(void)) );
	QObject::connect( mainWindow->thresholdButton, SIGNAL(clicked(void)), 
	                  this, SLOT( toggleThreshold(void)) );
	QObject::connect( mainWindow->staticPacingButton, SIGNAL(clicked(void)), 
	                  this, SLOT( togglePace(void)) );
	QObject::connect( mainWindow->resetButton, SIGNAL(clicked(void)), 
	                  this, SLOT( reset(void)) );
	QObject::connect( mainWindow->modelComboBox, SIGNAL(activated(int)), 
	                  this, SLOT( changeModel(int)) );    
	QObject::connect( mainWindow->APDRepolEdit, SIGNAL(returnPressed(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect( mainWindow->minAPDEdit, SIGNAL(returnPressed(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect( mainWindow->stimWindowEdit, SIGNAL(returnPressed(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect( mainWindow->numTrialEdit, SIGNAL(returnPressed(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect( mainWindow->intervalTimeEdit, SIGNAL(returnPressed(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect( mainWindow->BCLEdit, SIGNAL(returnPressed(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect( mainWindow->stimMagEdit, SIGNAL(returnPressed(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect( mainWindow->stimLengthEdit, SIGNAL(returnPressed(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect( mainWindow->CmEdit, SIGNAL(returnPressed(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect( mainWindow->LJPEdit, SIGNAL(returnPressed(void)), 
	                  this, SLOT( modify(void)) );
	QObject::connect(timer, SIGNAL(timeout(void)), 
	                  this, SLOT(refreshDisplay(void)));

	// Connections to allow only one button being toggled at a time
	QObject::connect( mainWindow->thresholdButton, SIGNAL(toggled(bool)), 
	                  mainWindow->staticPacingButton, SLOT( setDisabled(bool)) );
	QObject::connect( mainWindow->thresholdButton, SIGNAL(toggled(bool)),
	                  mainWindow->startProtocolButton, SLOT( setDisabled(bool)) );
	QObject::connect( mainWindow->startProtocolButton, SIGNAL(toggled(bool)), 
	                  mainWindow->staticPacingButton, SLOT( setDisabled(bool)) );
	QObject::connect( mainWindow->startProtocolButton, SIGNAL(toggled(bool)), 
	                  mainWindow->thresholdButton, SLOT( setDisabled(bool)) );
	QObject::connect( mainWindow->staticPacingButton, SIGNAL(toggled(bool)), 
	                  mainWindow->thresholdButton, SLOT( setDisabled(bool)) );
	QObject::connect( mainWindow->staticPacingButton, SIGNAL(toggled(bool)), 
	                  mainWindow->startProtocolButton, SLOT( setDisabled(bool)) );

	// Connect states to workspace
	setData( Workspace::STATE, 0, &time );
	setData( Workspace::STATE, 1, &voltage );
	setData( Workspace::STATE, 2, &beatNum );
	setData( Workspace::STATE, 3, &APD );
	setData( Workspace::STATE, 4, &targetCurrent );
	setData( Workspace::STATE, 5, &scaledCurrent );

	subWindow->show();
	subWindow->adjustSize();
} // End createGUI()

// Load from Settings
void IScale_DynClamp::Module::doLoad(const Settings::Object::State &s) {
	if (s.loadInteger("Maximized")) showMaximized();
	else if (s.loadInteger("Minimized")) showMinimized();

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
	mainWindow->BCLEdit->setText( QString::number( s.loadDouble("BCL") ) );
	mainWindow->stimMagEdit->setText( QString::number( s.loadInteger("Stim Mag") ) );
	mainWindow->stimLengthEdit->setText( QString::number( s.loadInteger("Stim Length") ) );
	mainWindow->CmEdit->setText( QString::number( s.loadInteger("Cm") ) );
	mainWindow->LJPEdit->setText( QString::number( s.loadInteger("LJP") ) );    

	modify();
}

// Save Settings
void IScale_DynClamp::Module::doSave(Settings::Object::State &s) const {
	if (isMaximized()) s.saveInteger( "Maximized", 1 );
	else if (isMinimized()) s.saveInteger( "Minimized", 1 );

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
	s.saveDouble( "BCL", BCL );
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
	int b = mainWindow->BCLEdit->text().toDouble();
	double sm = mainWindow->stimMagEdit->text().toDouble();
	double sl = mainWindow->stimLengthEdit->text().toDouble();
	double c = mainWindow->CmEdit->text().toDouble();
	double ljp = mainWindow->LJPEdit->text().toDouble();
	bool rd = mainWindow->recordDataCheckBox->isChecked();

	// If nothing has changed, return
	if( APDr == APDRepol && mAPD == minAPD && sw == stimWindow && 
	    nt == numTrials && it == intervalTime	&& b == BCL && sm == stimMag 
	    && sl == stimLength && c == Cm && ljp == LJP && rd == recordData ) 
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
		if( mainWindow->startProtocolButton->isChecked() && !protocolOn ) {
			mainWindow->startProtocolButton->setChecked( false );
		} else if( mainWindow->thresholdButton->isChecked() && !thresholdOn ) {
			mainWindow->thresholdButton->setChecked( false );
			mainWindow->stimMagEdit->setText( QString::number( stimMag ) );
			modify();
		}
	}
	else if( executeMode == PROTOCOL ) {
		if( stepTracker != currentStep ) {
			stepTracker = currentStep;
			mainWindow->protocolEditorListBox->setCurrentRow( currentStep );
		}        
	}
}

/*
// RT::Events - Called from GUI thread, handled by RT thread
IScale_DynClamp::Module::ToggleProtocolEvent::ToggleProtocolEvent( Module *m, bool o ) : 
	module( m ), on( o ) { }

int IScale_DynClamp::Module::ToggleProtocolEvent::callback( void ) {
	if( on ) { // Start protocol, reinitialize parameters to start values

		// Keep on IDLE until update is finished
		module->executeMode = IDLE; 

		module->voltageClamp = false;
		module->modelInit = true;
		module->reset();
		module->modelCell->resetModel();

		// beatNum is changed at beginning of protocol, so it must start 
		// at 0 instead of 1
		module->beatNum = 0; 

		// Used to highlight the current step in list box, -1 to force 
		// first step to be highlighted
		module->stepTracker = -1; 
		module->protocolMode = STEPINIT; 
		module->executeMode = PROTOCOL;
		//module->setActive( true );
	}
	// Stop protocol, only called when protocol button is unclicked in the 
	// middle of a run
	else { 
		if( module->recording ) { // Stop data recorder if recording
			::Event::Object event(::Event::STOP_RECORDING_EVENT);
			::Event::Manager::getInstance()->postEventRT(&event);
		}        
		module->executeMode = IDLE;
		//        module->setActive( false );
	}

	return 0;
}

IScale_DynClamp::Module::TogglePaceEvent::TogglePaceEvent( Module *m, bool o ) : 
	module( m ), on( o ) { }

int IScale_DynClamp::Module::TogglePaceEvent::callback( void ) {

	// Start protocol, reinitialize parameters to start values
	if( on ) { 
		module->reset();
		module->executeMode = PACE;
		module->setActive( true );
	}
	// Stop protocol, only called when pace button is unclicked in the 
	// middle of a run
	else { 
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
	: module( m ), on( o ) { }

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
*/

IScale_DynClamp::Module::ModifyEvent::ModifyEvent( 
	Module *m, int APDr, int mAPD, int sw, int nt, int it, int b, double sm, 
	double sl, double c, double ljp, bool rd ) : 
	module( m ), APDRepolValue( APDr ), minAPDValue( mAPD ), 
	stimWindowValue( sw ), numTrialsValue( nt ), intervalTimeValue( it ), 
	BCLValue( b ), stimMagValue( sm ), stimLengthValue( sl ), CmValue( c ), 
	LJPValue( ljp ), recordDataValue( rd ) { }

int IScale_DynClamp::Module::ModifyEvent::callback( void ) {
	module->APDRepol = APDRepolValue;
	module->minAPD = minAPDValue;
	module->numTrials = numTrialsValue;
	module->intervalTime = intervalTimeValue;
	module->BCL = BCLValue;
	
	// Update BCLInt when BCL is updated
	module->BCLInt = module->BCL / module->period; 
	
	module->stimMag = stimMagValue;
	module->stimLength = stimLengthValue;
	module->Cm = CmValue;
	module->LJP = LJPValue;
	module->recordData = recordDataValue;

	return 0;
}

// Event handling
void IScale_DynClamp::Module::receiveEvent( const ::Event::Object *event ) {
	if( event->getName() == Event::RT_POSTPERIOD_EVENT ) {
		period = RT::System::getInstance()->getPeriod()*1e-6; // Grabs RTXI thread period and converts to ms (from ns)
		BCLInt = BCL / period;
		stimLengthInt = stimLength / period;
		modelCell->setModelRate(100000, period);
	}

	if( event->getName() == Event::START_RECORDING_EVENT ) recording = true;
	if( event->getName() == Event::STOP_RECORDING_EVENT ) recording = false;
}

void IScale_DynClamp::Module::receiveEventRT( const ::Event::Object *event ) {
	if( event->getName() == Event::RT_POSTPERIOD_EVENT ) {
		period = RT::System::getInstance()->getPeriod()*1e-6; // Grabs RTXI thread period and converts to ms (from ns)
		BCLInt = BCL / period;
		stimLengthInt = stimLength / period;
		modelCell->setModelRate(100000, period);
	}

	if( event->getName() == Event::START_RECORDING_EVENT ) recording = true;
	if( event->getName() == Event::STOP_RECORDING_EVENT ) recording = false;
}

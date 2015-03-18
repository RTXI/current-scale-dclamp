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
 * IScale_DynClamp.h, v1.0
 *
 * Author: Francis A. Ortega (2011)
 *
 *** NOTES
 *
 * v1.0 - Initial Version
 *
 ***/

#include <default_gui_model.h>
#include <cstdlib>
#include <qwidget.h>
#include <string>
#include "include/MCL/ModelCell.h" // Model Cell Library
#include "include/IS_DC_Protocol.h" // Protocol Library
#include "include/IS_DC_MainWindowUI.h" // Main Window GUI

class IScale_DynClamp: public DefaultGUIModel {
    
    Q_OBJECT // macro needed if slots are implemented

    public:

    enum update_flags_t {
        MODIFY, /*!< The parameters have been modified by the user. */
        PERIOD, /*!< The system period has changed.                 */
        PAUSE, /*!< The Pause button has been activated            */
        UNPAUSE, /*!< When the pause button has been deactivated     */
        EXIT,
        // Additional Custom Flags
        RESET,
        RESETMODEL,
    };
    
    IScale_DynClamp( void );
    virtual ~IScale_DynClamp(void);
    virtual void update( update_flags_t flag );
    virtual void refresh( void );
    void execute( void  );
                         
public slots:
    void modify( void ); // Updates parameters
    void pause( bool ); // Pauses plugin, halts RT execution
    void exit( void ); // Unloads plugin
    void reset( void ); // Calls update(RESET)
    void addStep( void ); // Adds a protocol set
    void deleteStep( void ); // Deletes a protocol step
    void saveProtocol( void ); // Saves protocol into a xml file
    void loadProtocol( void ); // Loads xml protocol file
    void clearProtocol( void ); // Clears protocol
    void toggleRecordData( bool ); // Called when record button is checked/unchecked
    void toggleProtocol( bool ); // Called when protocol button is toggled
    void toggleThreshold( bool ); // Called when threshold button is toggled
    void togglePace( bool ); // Called when pace button is toggled
    void changeModel( int ); // Called when new model is selected

private:
    // GUI
    IScale_DynClampUI *mainWindow;

    ModelCell *modelCell; // Model used in dynamic clamp
    
    // Flags
    enum executeMode_t { IDLE, THRESHOLD, PACE, PROTOCOL } executeMode;
    enum protocolMode_t { STEPINIT, EXEC, END } protocolMode;
    bool recordData; // True if data will be recorded
    bool recording; // True if data recording is recording
    bool voltageClamp;
    bool modelInit;
    QString loadedFile;
    bool threshold;
    bool protocolOn;

    // States
    double time; // Time (ms)
    double voltage; // Membrane voltage
    double beatNum; // Beat number
    double APD; // Action potential duration

    // Parameters
    int APDRepol; // APD Repolarization percentage
    int minAPD; // Minimum duration of depolarization that counts as action potential
    int numTrials; // Number of trials to be run
    int intervalTime; // Time between trials
    int BCL; // Basic cycle length
    double stimMag; // Stimulation magnitude (nA)
    double stimLength; // Stimulation length (ms)
    double Cm; // Membrane capacitance (pF)

    // Protocol Variables
    Protocol *protocol;
    std::vector<ProtocolStepPtr> *protocolContainer; // Protocol container
    ProtocolStepPtr stepPtr; // Pointer to protocol step in protocol ctonainer
    ProtocolStep::stepType_t stepType; // Current step type for current step
    double outputCurrent; // Current output
    int currentStep; // Current step in protocol
    int stepTime; // Time tracker for step
    int stepEndTime; // Time end tracker for step
    int cycleStartTime; // Time tracker for BCL
    double totalModelCurrent; // Total current in the model during voltage clamp
    double targetCurrent; // Current that will be scaled
    double scaledCurrent; // Current after it has been scaled
    double period; // Period based on RTXI thread rate
    int BCLInt; // BCL / period (unitless)
    int pBCLInt; // BCL for protocol
    int stimLengthInt; // stimLength / period (unitless)

    // APD Variables
    double Vrest;
    int APD_start;
    double APD_start_time;
    double APD_end_time;
    double upstroke_threshold;
    double downstroke_threshold;

    // Threshold Variables
    bool actionPotential;
    bool thresholdStimulate;
    bool backToBaseline;
    double stimulusLevel;
    double startingStimulusLevel;
    double responseTime, initialStimulusTime;
    double diastolicThreshold;
    double responseDuration;
    double peakVoltage;
   
    // Module functions
    void createGUI( DefaultGUIModel::variable_t *var, int size ); // Overloaded DefaultGUIModel function for custom GUI
    void initialize( ); // Initialization
    void doLoad( const Settings::Object::State & ); // Load from settings file
    void doSave( Settings::Object::State & ) const; // Save to settings file
    void rebuildListBox( void ); // Builds protocol list box
    void calculateAPD( int ); // Calulates action potential duration
                                          
private slots:

};

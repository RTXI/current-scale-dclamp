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
 * IS_DC_Protocol.h
 * Contains classes for customizeable protocol
 *
 * Author: Francis A. Ortega (2011)
 *
 *** NOTES
 *
 * v1.0 - Initial Version
 *
 ***/

#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>
#include <qdom.h>
#include <QtWidgets>
#include "IS_DC_AddStepDialogUI.h"

class AddStepInputDialog: public AddStepDialog {
    Q_OBJECT
    
    private:
    QString stepType;
    QString BCL;
    QString numBeats;
    QString currentToScale;
    QString scalingPercentage;
    QString waitTime;
    QString model;
    
    signals:
    void checked( void );

    private slots:
    void addStepClicked( void );
    void stepComboBoxUpdate( int );
    
    public:
    AddStepInputDialog( QWidget * );
    ~AddStepInputDialog( void );
    std::vector<QString> gatherInput(void);    
};

class ProtocolStep {
public:
    enum stepType_t { PACE, SCALE, WAIT, STARTMODEL, STOPMODEL, RESETMODEL, CHANGEMODEL } stepType;    
    int BCL; // ms
    int numBeats;
    std::string currentToScale; // String name of current
    int scalingPercentage; // Whole number %
    int waitTime; // ms
    enum modelType_t { LIVRUDY2009, FABERRUDY2000 } modelType;
    
    ProtocolStep( stepType_t, int, int, std::string, int, int, modelType_t );
    ~ProtocolStep( void );
    int stepLength ( double );
};

typedef boost::shared_ptr<ProtocolStep> ProtocolStepPtr; // Step pointer
typedef std::vector<ProtocolStepPtr> ProtocolContainer; // Vector of steps: protocol

class Protocol {
public:
    Protocol( void );
    ~Protocol( void );
    bool addStep( QWidget * ); // Add a protocol step at the end
    bool addStep( QWidget *, int ); // Add a protocol step at a specific point
    void deleteStep( QWidget *, int ); // Delete a protocol step
    void saveProtocol( QWidget * ); // Save protocol in xml format
    void clearProtocol( void ); // Clears protocol
    QString loadProtocol( QWidget * ); // Build protocol container from xml file, file browser is opened
    void loadProtocol( QWidget *, QString ); // Build protocol container from xml file, file name is parameter
    QString getStepDescription( int ); // Retrieve a string description of step
    QDomElement stepToNode( QDomDocument &, const ProtocolStepPtr, int );

    ProtocolContainer protocolContainer;
};


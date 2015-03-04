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
 *
 * Model Cell Library
 * ModelCell.h, v1.0
 * 
 * ModelCell.h, v1.1
 *
 * Author: Francis Ortega (v1.0-1.1)(2011)
 *
 *** NOTES
 *
 * v1.0 - Initial version
 * v1.1 - added get parameter, set parameter
 *
 ***/

/*** Header Guard ***/
#ifndef MODELCELL_H
#define MODELCELL_H

#include <string.h>
#include <QtGui>
#include "models/include/default_model.h"

class ModelCell {

public:
    // Models list
    enum model_t{
        PANDIT = 0,
        WANGSOBIE = 1,
        FABERRUDY2000 = 2,
        LIVRUDY2009 = 3,
        TENTUSSCHER2006 = 4
    };

    ModelCell();
    ~ModelCell();

    /**** IMPORTANT: Must be called before model is used ****/
    // Set DT and number of loops done by model
    // Default is for a RTXI thread rate of 10khz and model rate of 100khz
    void setModelRate(double modelRate, double RealTimePeriod);
    void setModelRate(double modelRate);
    
    double currentClamp(double current); // Current clamp model, returns voltage
    double voltageClamp(double voltage); // Voltage clamp model, returns current
    void resetModel(); // Reset model to initial conditions
    int resetModel(double); // Reset model to a specific set of initial conditions, return value indicating which set was chosen
    void resetModel(double*); // Using the array pointer, modify certain parameters of the model (Used with the genetic algorithm)
    void changeModel(model_t); // Delete current model and switch to desired model
    double getCurrent(int); // Returns a model current *** Obsolete due to parameter functions ***
    double getConcentration(int); // Returns a model concentration *** Obsolete due to parameter functions ***
    double getParameter(int); // Returns desired parameter
    double getParameter(std::string); // Returns desired parameter, uses map for better code readability
    void setParameter(int, double); // Sets a parameter to a value
    QStringList getParameterList( void ); // Returns a list of parameters available for retrieval

public:
    double DT;
    
private:
    int steps;
    default_model *model;
};

#endif

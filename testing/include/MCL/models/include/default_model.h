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
 * Base class for all models
 * 
 * default_model.h, v1.1
 *
 * Author: Francis Ortega (v1.0-1.1)(2011)
 *
 *** NOTES
 *
 * v1.0 - Initial version
 * v1.1 - Added get and set parameter functions
 *
 ***/

/*** Header Guard ***/
#ifndef DEFAULT_MODEL_H
#define DEFAULT_MODEL_H

#include <string>
#include <qstringlist.h>
#include "../include/RealTimeMath.h" // RealTimeMath library

/*** Class default_model ***/
class default_model{
    
public:
    default_model();
    virtual ~default_model();

    void setDT(double);
    void setSteps(int);
    
    // Virtual functions, every model must be derived from this class and contain these functions
    virtual double vClamp(double); // Parameter: Voltage | Return: Current
    virtual double iClamp(double); // Parameter: Current | Return: Voltage
    virtual void reset(); // Reset to initial conditions
    virtual int reset(double); // Reset to specific set of initial conditions, returns int describing which set was chosen
    virtual void reset(double*); // Using the array pointer, modify certain parameters of the model (Used with the genetic algorithm)
    virtual double current(int); // Get current function *** Obsolete due to param function ***
    virtual double concentration(int); // Get concentration function *** Obsolete due to param function ***
    virtual double param(int); // Get parameter function
    virtual double param(std::string); // Get parameter function, uses map for better code readability
    virtual void setParam(int, double); // Set parameter function
    virtual QStringList paramList( void ); // Returns a list of parameters available for retrieval
    

protected:
    int i; // vClamp and iClamp loop counter
    int steps; // Number of loops model must go through to match
    
    double DT;
    double I_Inject; // Current injected during current clamp
    // RealTimeMath Object
    RealTimeMath *RTmath;
};

#endif // End header guard

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
 *  Foundation, Inc., 6adsfadfsadsfadsf75 Mass Ave, Cambridge, MA 02139, USA.
 */

/*** INTRO
 *
 * Model Cell Library
 * Base class for all models
 * 
 * default_model.cpp, v1.0
 *
 * Author: Francis Ortega (v1.0-1.1)(2011)
 *
 *** NOTES
 *
 * Notes in Header
 *
 ***/

#include <iostream>
#include "default_model.h"

using namespace std;

/*** default_model constructor ***/
default_model::default_model(){
    I_Inject = 0; // I_Inject must be initialized to 0 to prevent errors

    // DT and steps initalized for a RTXI thread rate of 10khz, and model rate of 100khz
    DT = 0.01;
    steps = 10;

    // Create RTMath object
	RTmath = new RealTimeMath();
}

/*** default_model destructor ***/
default_model::~default_model(){
    delete RTmath;
}

/*** Set functions ***/
void default_model::setDT(double x){
    DT = x;
}

void default_model::setSteps(int x){
    steps = x;
}

/*** Virtual functions ***/
double default_model::iClamp(double x){ // Derived class iClamp() should be called, never base class function
    cout << "****ERROR**** default_model iClamp called, function not defined in derived class" << endl;
    return 0;
}

double default_model::vClamp(double x){ // Derived class vClamp() should be called, never base class function
    cout << "****ERROR**** default_model vClamp called, function not defined in derived class" << endl;
    return 0;
}

void default_model::reset(){ // Derived class reset() should be called, never base class function
    cout << "****ERROR**** default_model reset called, function not defined in derived class" << endl;
}

int default_model::reset(double x){ // Derived class reset(double) should be called, never base class function
    cout << "****ERROR**** default_model reset(double) called, function not defined in derived class" << endl;
}

void default_model::reset(double *x){ // Derived class reset(*double) should be called, never base class function
    cout << "****ERROR**** default_model reset(*double) called, function not defined in derived class" << endl;
}

double default_model::current(int x){ // Derived class current() should be called, never base class function
    cout << "****ERROR**** default_model current() called, function not defined in derived class" << endl;
}

double default_model::concentration(int x){ // Derived class concentration() should be called, never base class function
    cout << "****ERROR**** default_model concentratoin() called, function not defined in derived class" << endl;
}

double default_model::param(int x){ // Derived class param() should be called, never base class function
    cout << "****ERROR**** default_model param(int) called, function not defined in derived class" << endl;
}

double default_model::param(string x){ // Derived class param() should be called, never base class function
    cout << "****ERROR**** default_model param(string) called, function not defined in derived class" << endl;
}

void default_model::setParam(int x, double y){ // Derived class setParam() should be called, never base class function
    cout << "****ERROR**** default_model setParam() called, function not defined in derived class" << endl;
}

QStringList default_model::paramList( void ){ // Derived class setParam() should be called, never base class function
    cout << "****ERROR**** default_model paramList() called, function not defined in derived class" << endl;
}

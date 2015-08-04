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
 * ModelCell.cpp, v1.1
 *
 * Author: Francis Ortega (v1.0-1.1)(2011)
 *
 *** NOTES
 *
 * Notes in Header
 *
 ***/

#include <iostream>
#include <math.h>
#include "ModelCell.h"
#include "models/include/default_model.h"

// Model includes
#include "models/LivRudy2009/LivRudy2009.h"
#include "models/FaberRudy2000/FaberRudy2000.h"
#include "models/WangSobie/WangSobie.h"
#include "models/Pandit/Pandit.h"
#include "models/TenTusscher2006/TenTusscher2006.h"

using namespace std;

/*** ModelCell Constructor ***/
ModelCell::ModelCell(){
    // Default model is LivshitzRudy2009
    model = new LivRudy2009();
}

/*** ModelCell Destructor ***/
ModelCell::~ModelCell(){
    delete model;
}

/*** resetModel Function ***/
// Resets model to initial conditions
void ModelCell::resetModel(){
    model->reset();
}
// Resets model to a specific set of initial conditions, returns int describing which set was chosen
int ModelCell::resetModel(double x){
    int y;
    y = model->reset(x);
    return y;
}

void ModelCell::resetModel(double *x){ // Using the array pointer, modify certain parameters of the model (Used with the genetic algorithm)
    model->reset(x);
}

/*** changeModel Function ***/
// Deletes existing model, and then initializes new model based on parameter
void ModelCell::changeModel(model_t newModel){

    delete model;

    switch (newModel){

    case LIVRUDY2009:
        model = new LivRudy2009();
        break;
        
    case FABERRUDY2000:
        model = new FaberRudy2000();
        break;

    case WANGSOBIE:
        model = new WangSobie();
        break;

    case PANDIT:
        model = new Pandit();
        break;

    case TENTUSSCHER2006:
        model = new TenTusscher2006();
        break;

    }
}

/*** setModelRate Function ***/
// Updates DT and steps based on desired model integration rate and RTXI period
void ModelCell::setModelRate(double modelRate, double RTperiod){
    DT = (1/modelRate)*1000; // Calculates DT (ms)
    model->setDT(DT);
	steps = static_cast<int>(ceil(RTperiod/DT)); // Determines number of iterations model solver will run based on RTXI thread rate
    model->setSteps(steps);
}

void ModelCell::setModelRate(double modelRate){
    DT = (1/modelRate)*1000; // Calculates DT (ms)
    model->setDT(DT);
    model->setSteps(1);
}

/*** currentClamp Function ***/
// Passes current to model, runs its iClamp() function, and returns voltage
double ModelCell::currentClamp(double current){
    return model->iClamp(current);
}

/*** voltageClamp Function ***/
// Passes voltage to model, runs its vClamp() function, and returns current
double ModelCell::voltageClamp(double voltage){
    return model->vClamp(voltage);
}

/*** returnCurrent Function ***/
// Return a model current, see list of currents in model folders
double ModelCell::getCurrent(int current){
    return model->current(current);
}

/*** returnConcentration Function ***/
// Return a model ion concentration, see list of currents in model folders
double ModelCell::getConcentration(int concentration){
    return model->concentration(concentration);
}


// Return a model parameter, see list of parameters in model folders or use define list
double ModelCell::getParameter( int paramNum ) {
    return model->param(paramNum);
}

/*** Return Parameter Function ***/
// Uses a map for better code readability
double ModelCell::getParameter( string paramNum ) {
   return model->param(paramNum);
}


/*** Set Parameter Function ***/
// Sets a model parameter, see list of parameters in model folders or use define list
void ModelCell::setParameter( int paramNum, double value ) {
    model->setParam(paramNum, value);
}

/*** Get Parameter List Function ***/
// Returns a list of parameters available for retrieval
QStringList ModelCell::getParameterList( void ) {
    return model->paramList();
}

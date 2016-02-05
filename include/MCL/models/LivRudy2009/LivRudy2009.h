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
 * 2009 Livshitz Rudy Model of a ventricular guinea pig myocte
 * Biophysical Journal, 2009
 * 
 * LivRudy2009.h, v2.1
 *
 * Author: Francis Ortega (v1.0-2.1)(2011)
 *
 *** NOTES
 *
 * Model equations taken from Matlab model created by Dr. Eric Sobie based
 * on Livshitz 2009 paper.
 *
 *
 * math.h function exp(x) replaced with fastEXP(x) which uses PowFast.hpp due
 * to spikes in computation time of math.h function. - Now makes calls to
 * RealTimeMath Library, which in turn uses PowFast functions
 *
 * v1.0 - initial version
 * v1.1 - added rate changer
 * v1.2 - Replaced calls to PowFast library with calls to RealTimeMath library
 * v2.0 - Made compatible with and added to Model Cell Library (MCL)
 * v2.1 - Added parameter functions for use with gScaling DynClamp
 *
 ***/
/*** Header Guard ***/
#ifndef LIVRUDY2009_H
#define LIVRUDY2009_H

#include <map>
#include "../include/default_model.h" // default_model base class

#include <QtGlobal>
#if QT_VERSION >= 0x050000
	#include <QtWidgets>
#else
	#include <QtGui>
#endif

/*** LivRudy2009 Class ***/
class LivRudy2009 : public default_model { // Base class is default_model
    
public:
	LivRudy2009(void); // Constructor
	virtual ~LivRudy2009(void); // Destructor

    // Virtual functions for default_model base class
    virtual double iClamp(double); // Current clamp
    virtual double vClamp(double); // Voltage clamp
	 virtual void reset(); // Reset model to initial conditions
    virtual double param(int); // Get parameter
    virtual void setParam(int, double); // Set parameter
    virtual double param(std::string);
    virtual QStringList paramList( void ); // Returns a list of parameters available for retrieval

private:
    void solve(); // Model current solver
    void makeMap(); // Initialize parameter map
    
    std::map<std::string, double*> parameterMap;
    
    // Loop variable
	int i;
   
	// Lookup Table variables
	double V_min;
	double Vx;
	int z;
	int ilow;
   double linext;
   double (*lkup)[20];
	
   //// Model variables
    
   // Model parameters
   double V;
    
   //double DT; // Already part of base class
	double dVdt;
	double Cai;
	double CaNSR;
	double CaJSR;
	double Nai;
	double Ki;
	double m;
	double h;
	double j;
	double d;
	double f;
	double b;
	double g;
	double xKr;
	double xs1;
	double xs2;
	double Jrel;
    
	// Gating variables in lookup table 
	double lambda_na;
	double ah;
	double bh;
	double aj;
	double bj;
	double am;
	double bm;
	double dinf_0;
	double dinf_1;
	double lambda_g;
	double xsinf;
	double tau_xs1;
	double hinf;
	double tauh;
	double tauj;
	double jinf;
	double minf;
	double taum;
	double dinf;
	double taud;
	double finf;
	double tauf;
	double binf;
	double taub;
	double ginf;
	double taug;
	double xKrinf;
	double tauxKr;
	double tauxs1;
	double tauxs2;
    
	// Current Variables
	double ENa, EK, EKs, ECa; // Reversal potetentials 
	double INa, INab; // Na current 
	double ICa_, ICaK_, ICaNa_, fCa, ICaL, ICaL_K, ICaL_Na; // L-type Ca current 
	double ICab; // Background calcium current 
	double IpCa; // Sarcolemmal calcium pump 
	double ICaT; // T-type calcium current
	double xK1, IK1, RKr, IKr, IKs, Kp, IKp; // K currents
	double sigma_NaK, fNaK, INaK, INCX; // Pumps and transporters
	double Iion; // Total current
	double Iinjected; // Injected current
    
    // Intracellular Ca flux
	double Jrelinf, tau_rel, Jserca, Jtr;
    
	// Buffering
	double BJSR, Bi;
    
	// Derivatives
	double dNai, dKi, dCai, dCaJSR, dCaNSR, dJreldt;

    //// Model Constants
    double F; // Faraday's constant, C/mol
    double R; // gas constant, mJ/K
    double T; // absolute temperature, K
    double RTF;
    double FRT;
    double pi; // Pi
    
    // Cell Geometry 
    double length_cell; // Length of the cell (cm)
    double radius; // Radius of the cell (cm)
    double Vcell; // 3.801e-5 uL Cell volume (uL)
    double Ageo; // 7.671e-5 cm^2 Geometric membrane area (cm^2)
    double Acap; // 1.534e-4 cm^2 Capacitive membrane area (cm^2)
    double Vmyo; // Myoplasm volume (uL)
    double Vmito; // Mitochondria volume (uL)
    double VNSR; // NSR volume (uL)
    double VJSR; // JSR volume (uL)
    double Vss;
    
    // Cell Capacitance 
    double Cm;
    
    // Fixed ionic concentrations 
    double Ko; // uM
    double Nao; // uM
    double Cao; // uM
    
    // Na current constants 
    double GNa_; // mS/cm^2
    double GNab;
    //double GNaL_= 6.5e-3;
    
    // Ca current constants	
    double PCa; // cm/s
    double PCa_Na; // cm/s
    double PCa_K; // cm/s
    double PCab; // cm/s
    double gamma_Cao; // dimensionless
    double gamma_Cai; // dimensionless
    double gamma_Nao; // dimensionless
    double gamma_Nai; // dimensionless
    double gamma_Ko; // dimensionless
    double gamma_Ki; // dimensionless
    
    //const double hLca = 1; // dimensionless, Hill coefficient
    double KmCa; // Half saturation constant, mM
    
    // T-type & background currents	
    double GCaT;
    double GCab;
    
    // K Currents 
    double GK1_;
    double GKr_;
    double GKs_;
    double pKNa; // relative permeability of IKs, Na to K
    double GKp_;
    double INaK_; // Max. current through Na-K pump (uA/uF)
    double KmNa_NaK; // Half-saturation concentration of NaK pump (mM)
    double KmK_NaK; // Half-saturation concentration of NaK pump (mM)
    double kNCX;
    double ksat;
    double eta;
	double alpha_rel;
    double Krel_inf;
    double hrel;
    double beta_tau;
    double Krel_tau;
    
    // Pumps and Transporters 
    double IpCa_; // Max. Ca current through sarcolemmal Ca pump (uA/uF)
    double KmpCa; // Half-saturation concentration of sarcolemmal Ca pump (mM)
    double Vserca; // mM/ms
    double Kmserca; // mM
    double CaNSR_max;
    double tau_transfer;
    
    // Buffers in cytosol 
    double TRPNtot;
    double KmTRPN;
    double CMDNtot;
    double KmCMDN;
    
    // Buffers in JSR 
    double CSQNtot;
    double KmCSQN;
};

#endif

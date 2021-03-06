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
 * 2000 Faber Rudy Model of a ventricular guinea pig myocte
 * Faber G et al - Kinetic Properties of the Cardiac L-type Ca Channel
 * and its Role in Myocyte Electrophysiology. Biophys. J. 2006, 92: 1522-1543
 * 
 * FaberRudy2000.h, v1.2
 *
 * Author: Francis Ortega and Corina Bot (v1.0)(2011)
 *
 *** NOTES
 *
 * Real-time optimized ventricular guinea pig myocyte model. Uses lookup
 * tables and the RealTimeMath library to eliminate spikes in computation
 * time seen with the generic math library. Code adapted from code used
 * by Rebecca Nicklas-Ahrens.
 *
 * v1.0 - Initial version
 * v1.1 - Fixed memory leak
 * v1.2 - Voltage now updates
 *
 ***/

/*** Header Guard ***/
#ifndef FABERRUDY2000_H
#define FABERRUDY2000_H

#include <map>
#include "../include/default_model.h" // default_model base class

#include <QtGlobal>
#if QT_VERSION >= 0x050000
	#include <QtWidgets>
#else
	#include <QtGui>
#endif

/*** FaberRudy2000 Class ***/
class FaberRudy2000 : public default_model { // Base class is default_model

public:
    FaberRudy2000(void);          // Constructor
    virtual ~FaberRudy2000(void); // Destructor

    // Virtual functions for default_model base class
    virtual double iClamp(double);         // Current clamp
    virtual double vClamp(double);         // Voltage clamp
    virtual double current(int);           // Current return function
    virtual double concentration(int);     // Concentration return function
    virtual double param(std::string);
    virtual QStringList paramList( void ); // Returns a list of parameters available for retrieval
    virtual void reset();

    //double DT; *Part of base class
    //int steps; *Part of base class

private:
    void solve();
    void makeMap(); // Initialize parameter map

    std::map<std::string, double*> parameterMap;

	// Cosine and Acosine lookup table
    double (*coslkup)[2];
  	double (*acoslkup)[2];
  	double acos_num_min;
  	double cos_num_min;
  	double acosHolder, cosHolder, cosHolder2;

    // Gating variable lookup table
    int index;
	double (*lkup)[22];
	double V_min;
	int ilow;
	double linext;
    double GUINEA_PIG[15];

    //// Parameters
    double V;
    double I_Inject;
    int flag;
    
    //Ion Valences and Universal Constants	
    double R;
    double T;
    double F;
    double z_Na;						
    double z_Ca;
    double z_K;
    
    //Cell Geometry
    double pi;						
    double L;       // Length 100um (cm)
    double r;       // Radius 11um (cm)
    double R_cg;    // Ratio of capacitive membrane area to gemometric membrane area
    double V_cell;  // Volume of cell 38E-6 uL
    double A_geo;   // Geometric membrane area; 0.767E-4 cm^2
    double A_cap;   // Capacitive membrane area
    double V_myo;   // Myoplasm volume set to 68% of volume of cell
    double V_mito;  // Mitochondria volume set to 26% of volume of cell
    double V_sr;    // Sarcoplasmic reticulum volume set to 6%
    double V_nsr;   // Network SR is 92% of SR
    double V_jsr;   // Junctional SR is 8% of SR
    double V_cleft; // Cleft volume

    //initial conditions taken from the LR code on the web
    double Na_out;
    double Ca_out;
    double K_out;
    double dCa_in;
    double dCa_jsr;
    double dCa_nsr;
    double dNa_in;
    double dK_in;
    double I_Total;
   
    double I_Na, E_Na, am, bm, ah, bh, aj, bj, mtau, htau, jtau, mss, hss, jss; // I_Na channel
    double d_inf, f_inf, tau_d, tau_f, ad, bd, af, bf;                          // L-type Ca channel
    double f_Ca, I_Ca_bar, I_Ca_L, I_Ca_K_bar, I_Ca_K, I_Ca_Na_bar, I_Ca_Na;    // L-type Ca channel
    double E_Ca_T, tau_b, tau_g, b_ss, g_ss, I_Ca_T;                            // T type Ca channel
    double I_K1, K1_s, aK1, bK1, G_K1, E_K1;                                    // I_K1 channel
    double Kp, I_Kp, E_Kp;                                                      // I_Kp channel
    double I_Na_Ca; 
    double I_Na_K, f_Na_K, sigma;
    double I_p_Ca;
    double G_Kr, E_Kr, xr_ss, r_Kr, tau_xr, I_Kr;
    double G_Ks, E_Ks, I_Ks;
    double xs2_ss; 
    double xs1_ss; 
    double tau_xs1;  
    double tau_xs2; 
    double I_Ca_b, E_Ca_N, I_Na_b, E_Na_N;
    double I_rel, on, off, magrel, Ca_in_total_old, dCa_ion_total, dCa_ion_total_new;
    double I_rel_OL, G_rel_OL; 
    double I_up, I_leak, I_tr;
    double Ca_total, b_myo, c_myo, d_myo, g_myo;
    double bjsr, cjsr;
    double I_Ca_ion_total, I_Na_ion_total, I_K_ion_total; 
   
    //Various CICR constants needed for the JSR/ NSR	
    double tau_on; //  constant of activation of Ca release from JSR
    double tau_off; // time constant of deactivation of Ca release from JSR
    double tcicr;
    double tjsrol;
    double TRPN;
    double CMDN;
    double Ca_CSQN;
    double GP_err;
    int GP_i4;
   
    double sum;
    double gna;
    double Km_Ca ;
    double P_Ca;
    double g_Ca_in;
    double g_Ca_out;
    double P_K;
    double g_K_in;
    double g_K_out;
    double P_Na;
    double g_Na_in;
    double g_Na_out;
    double G_Ca_T;
    double PR_NaK;
    double G_Kp;
    double c1;         // Scaling factor for inaca (uA/uF)
    double c2;         // Half-saturation concentration of NaCa exhanger (mM)
    double gammas;     // Position of energy barrier controlling voltage dependance of inaca
    double I_Na_K_bar;
    double Km_Na_i;
    double Km_Ko;
    double I_p_Ca_bar;
    double Km_p_Ca;
    double G_Ca_b_bar;
    double G_Na_b_bar; //0.00141;
    double tau_tr;
    double I_up_bar ;
    double Ca_nsr_bar;
    double K_leak;
    double Km_up;
    double G_rel_bar;  // Max. rate constant of Ca release from JSR due to overload (ms^-1)
    double G_rel_bar_OL;
    double CSQN_bar;   // Max. [Ca] buffered in CSQN (mM)
    double Km_CSQN;    // Equalibrium constant of buffering for CSQN (mM)
    double TRPN_bar;						
    double CMDN_bar;						
    double Km_TRPN;
    double Km_CMDN;
    //Parameters whose value we need to store between beats
    double d; 
    double f;
    double xs1; 
    double xs2;
    double xr; 
    double b; 
    double g;
    double m; 
    double hh; 
    double j; 
    double Na_in;	          //10;
    double K_in;            //145;
    double Ca_in, Ca_in_x;	 //0.12E-3;
    double Ca_jsr;
    double Ca_nsr;

	// Loop variable 
	int i;
};

#endif

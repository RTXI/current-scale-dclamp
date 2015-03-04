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
 * Neonatal Ventricular Mouse Model - A Modified Pandit Adult Rat Myocyte Model
 *
 * A Mathematical Model of Action Potential Heterogeneity in Adult Rat Left
 * Ventricular Myocytes
 * Sandeep V. Pandit, Robert B. Clark, Wayne R. Giles and Semahat S. Demir
 * Biophysical Journal, Volume 81, Issue 6, December 2001, Pages 3029-3051
 *
 * Pandit.h, v1.3
 *
 * Author: Francis Ortega and Corina Bot (v1.0 - 1.3)(2011)
 *
 *** NOTES
 *
 * MODIFIED FROM PUBLISHED MODEL. Original model described adult rat left
 * ventricular myocytes. This is a modified model that attempts to model
 * neonatal mouse ventricular myocytes through modifications in the
 * parameters. Code adapted from code used by Rebecca Nicklas-Ahrens. This
 * is the target canceling model that was used in original publication
 * of CTC.
 *
 * v1.0 - Initial version
 * v1.1 - Added initial conditions modifier for CTC based on APD, based on
 *        original CTC by Nicklas-Ahrens.
 * v1.2 - Made intial conditions modifier function into an overloaded reset
 *        function
 * v1.3 - Added another reset function that accepts an array pointer for use
 *        with something like a genetic algorithm
 *        Added Ca_inact_bar
 *
 ***/

/*** Header Guard ***/
#ifndef PANDIT_H
#define PANDIT_H

#include "../include/default_model.h" // default_model base class

/*** Pandit Class ***/
class Pandit : public default_model {
    
public:
    Pandit(void); // Constructor
    virtual ~Pandit(void); // Destructor

    // Virtual functions for default_model base class
    virtual double iClamp(double); // Current clamp
    virtual double vClamp(double); // Voltage clamp
    virtual double current(int); // Current return function
    virtual double concentration(int); // Concentration return function
    virtual void reset(); // Reset to initial conditions
    virtual int reset(double); // Reset to specific set of initial conditions, returns int describing which parameter set is being used
    virtual void reset(double*); // Using the array pointer, modify certain parameters of the model (Used with the genetic algorithm)
    
    //double DT; *Part of base class
    //int steps; *Part of base class

private:
    void calc_gates();
    void calc_currents();
    void solve();
    
    // Look up table 
    double V_min;
    int ilow;
    double linext;
    double (*mlkup)[23];

    // Model for initial condition set function
    int mouseModel;
    
    // External concentrations
    double Ko;
    double Nao;
    double Cao;
  
    //  Intracellular volumes in uL
    double Vc;
    double Vnuc;
    double Vmito;
    double Vss;
    double Vsr;
    double Vjsr;
    double Vnsr;
    double Vmyo;
  
    // Constants
    double R;
    double F;
    double T;
  
    // Cellular capacitance
    double CAP; // nF
  
    // Parameters for INa
    double GNa; // 0.8 * 1.33 for left to right change
  
    // Parameters for ICaL
    double GCaL;
  
    // Parameters for It
    double Gt;
  
    // Parameters for Iss
    double Gss;
  
    // Parameters for Ik1
    double Gk1;
  
    // Parameters for Ikslow
    double Gkslow;
  
    // Parameters for background currents
    double GbNa;
    double GbCa;
    double GbK;
  
    // Parameters for If
    double Gf;
  
    // Parameters for INaK
    double ImaxNaK;
    double KmNa;
    double KmK;
  
    // Parameters for ICaP
    double ImaxCaP;
  
    // Parameters for INaCa
    double kNaCa; // Scaling factor
    double dNaCa; // Denominator constant
    double gam; // Position of energy barrier
  
    // Parameters for SR function
    double v1; // Max RyR channel Ca flux
    double Kfb; // Forward half-sat constant for Ca/ATPase
    double Krb;// Backward half-sat constant for Ca/ATPase
    double Ksr; // Scaling factor for Ca/ATPase
    double Nfb; // Forward cooperativity constant for Ca/ATPase
    double Nrb; // Reverse cooperativity constant for Ca/ATPase
    double vmaxf; // Ca/ATPase forward rate parameter
    double vmaxr; // Ca/ATPase reverse rate parameter
    double tau_tr; // Time constant for transfer for NSR to JSR
    double tau_xfer; // Time constant for transfer from subspace to myoplasm
    double Ka_pos; // RyR Pc1-Po1 rate constant
    double Ka_neg; // RyR Po1-Pc1 rate constant
    double Kb_pos; // RyR Po1-Po2 rate constant
    double Kb_neg; // RyR Po2-Po1 rate constant
    double Kc_pos; // RyR Po1-Pc2 rate constant
    double Kc_neg; // RyR Pc2-Po1 rate constant
    double n_ry; // RyR Ca cooperativity parameter Pc1-Po1
    double m_ry; // RyR Ca cooperativity parameter Po1-Po2
    double LTRPNtot; // Total troponin low-affinity site concentration
    double HTRPNtot; // Total troponin high-affinity site concentration
    double Khtrpn_pos; // Ca on rate for troponin high-affinity sites
    double Khtrpn_neg; // Ca off rate for troponin high-affinity sites
    double Kltrpn_pos; // Ca on rate for troponin low-affinity sites
    double Kltrpn_neg; // Ca off rate for troponin low-affinity sites
    double CMDN_tot; // Total myoplasm calmodulin concentration
    double CSQN_tot; // Total myoplasm calsequestrin concentration
    double EGTA_tot; // Total myoplasm EGTA concentration
    double KmCMDN; // Ca half-saturation constant for calmodulin
    double KmCSQN; // Ca half-saturation constant for calsequestrin
    double KmEGTA; // Ca half-saturation constant for EGTA
  
    // Gating variables
    double m_bar, tau_m;
    double h_bar, tau_h;
    double j_bar, tau_j;
    double d_bar, tau_d;
    double f11_bar, tau_f11;
    double f12_bar, tau_f12;
    double Ca_inact_bar, tau_Ca_inact;
    double r_bar, tau_r;
    double s_bar, tau_s;
    double rss_bar, tau_rss;
    double rkslow_bar, tau_rkslow;
    double skslow_bar, tau_skslow;
    double y_inf, tau_y;
    double Ek, ENa, V, dV_dt, Itotal;
    double m, h_gate, j, d, f11, f12, Ca_inact, r, s, rkslow, skslow, rss, y; // Gating variables
    double INa, ICaL, IfNa, IfK, It, Ikslow, Iss, INaK, ICaP, INaCa, Ik1; // Major currents
    double Ca_nsr, Ca_ss, Ca_jsr, Pc1, Po1, Po2, Pc2, ltrpn, htrpn;
    double Jtr, Jxfer, Jtrpn, Jup, Jrel;
    double fb, rb, Bi, Bss, Bjsr;
    double IBNa, IBK, IBCa, IB; // Background currents
    double Nai, Ki, Cai; // Intracellular ion concentrations
    double RTONF;
    double sigma; // For INaK calculation
    double ECal;
    double fna, fk;

};

#endif

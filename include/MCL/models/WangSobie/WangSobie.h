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
 * 2008 Model of a Neonatal Mouse Ventricular Cell
 * Wang and Sobie - Mathematical model of the neonatal mouse ventricular
 * action potential. AJP: Heart and Circulatory Physiology (2008) vol. 294
 * (6) pp. H2565-H2575
 * 
 * WangSobie.h, v1.0
 *
 * Author: Francis Ortega and Corina Bot (v1.0)(2011)
 *
 *** NOTES
 *
 * Real-time optimized ventricular neonatal mouse myocyte model. Uses lookup
 * tables and the RealTimeMath library to eliminate spikes in computation
 * time seen with the generic math library. Code adapted from code used
 * by Rebecca Nicklas-Ahrens.
 *
 * v1.0 - Initial version
 *
 ***/

/*** Header Guard ***/
#ifndef WANGSOBIE_H
#define WANGSOBIE_H

#include "../include/default_model.h" // default_model base class

#define NUM_STATES2 32  // Number of states without sodium gates
#define SODIUM_NUM_STATES2 3 //Number of Hodgkin Huxley sodium gates

/*** WangSobie Class ***/
class WangSobie : public default_model {
    
public:
    WangSobie(void); // Constructor
    virtual ~WangSobie(void); // Destructor

    // Virtual functions for default_model base class
    virtual double iClamp(double); // Current clamp
    virtual double vClamp(double); // Voltage clamp
    virtual double current(int); // Current return function
    virtual double concentration(int); // Concentration return function
    virtual void reset(); // Reset to initial conditions

    //double DT; *Part of base class
    //int steps; *Part of base class

private:
    void calc_gates();
    void calc_currents();
    void calc_sodium(double);
    void solve();

    //solver variables for sodium
    double sodium_rate;
    double sodium_dt;
    int sodium_steps;

    // Lookup table for voltage-dependent gating variables
    double V_min;
    int ilow;
    double linext;
    double (*mlkup)[33];

    // Parameter structures
    double y2[NUM_STATES2];
    double dy2[NUM_STATES2]; 
   
    double sodium_y2[SODIUM_NUM_STATES2];
    double sodium_dy2[SODIUM_NUM_STATES2]; 
    
    struct sodium_params2{
        double am;
        double bm;
        double ah;
        double aj;
        double bh;
        double bj;
    };

    struct params2 {
        double F; 
        double R; 
        double T; 
        double RTF;
        double VJSR;
        double VNSR; 
        double Acap; 
        double Vmyo; 
        double Vss; 
        double Cm;
        double Ko; 
        double Nao; 
        double Cao; 
        double Clo; 
        double Cli;
        double GNa_; 
        double GNab_; 
        double GCab_; 
        double GK1_; 
        double GKr_; 
        double GKs_; 
        double GKtof_; 
        double GKur_; 
        double GKss_; 
        double kf_Kr; 
        double kb_Kr; 
        double P_CaCl;
        double n_h; 
        double Km_CaCl; 
        double GCaL_; 
        double ECaL; 
        double Kpcmax; 
        double Kpchalf; 
        double kPCFmax; 
        double kPCB; 
        double ICaLmax; 
        double GCaT_; 
        double ECaT;
        double kNaCa; 
        double KmNa; 
        double KmCa; 
        double ksat; 
        double eta; 
        double INaKmax; 
        double KmNai; 
        double KmKo; 
        double Ipmax; 
        double KmpCa;
        double nu1; 
        double nu2; 
        double nu3; 
        double Kmserca; 
        double tau_transfer; 
        double tau_xfer;
        double kaplus; 
        double kaminus; 
        double kbplus; 
        double kbminus; 
        double kcplus; 
        double kcminus; 
        double nRyR; 
        double mRyR;
        double LOWTRPNtot;
        double HIGHTRPNtot; 
        double LOWkp_Ca; 
        double HIGHkp_Ca; 
        double LOWkm_Ca;
        double HIGHkm_Ca; 
        double CMDNtot; 
        double KmCMDN; 
        double CSQNtot; 
        double KmCSQN;
        double sigma;
        double ENa; 
        double ECa;
        double EK;
        double INa; 
        double INab;
        double ICaL;
        double ICaT;
        double ICab;
        double IpCa;
        double INCX;
        double fNaK;
        double INaK;
        double IKr;
        double IKs;
        double IK1;
        double IKtof;
        double IKur;
        double IKss;
        double f_CaCl;
        double ICaCl;
        double Iion;
        double Jrel;
        double Jtransfer;
        double Jxfer;
        double Jleak;
        double Jserca;
        double Bi;
        double Bss;
        double BJSR;
        double dCaTRPN;
        double Jtrpn;
        double alpha_L;
        double beta_L;
        double gamma_L;
        double kPCF;
        double b_Tinf;
        double g_Tinf;
        double taub_T;
        double taug_T;
        double an;
        double bn;
        double a0_Kr;
        double b0_Kr;
        double a1_Kr;
        double b1_Kr;
        double ai_Kr;
        double bi_Kr;
        double aatof;
        double batof;
        double aitof;
        double bitof;
        double aitof2;
        double bitof2;
        double itofinf;
        double tauitof;
        double akinf; 
        double ikinf;
        double tauaur;
        double tauiur;
        double tauakss;
        double C1_L;
        double C0_Kr;
        double C1_ryr;
    };

    struct sodium_params2 sodium_myParams2;
    struct sodium_params2 *sodium_Params2;
    
    struct params2 myParams2;
    struct params2 *Params2;

};

#endif

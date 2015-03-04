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
 * TenTusscher2006.h, v1.0
 *
 * Author: Corina Bot and Francis Ortega (v1.0)(2011)
 *
 *** NOTES
 *
 * Human ventricular model by Kirsten ten Tusscher. Reduced version is presented here.
 *
 * http://www-binf.bio.uu.nl/khwjtuss/SourceCodes/
 *
 * Original Model:
 * ten Tusscher KH, Panfilov AV. Alternans and spiral breakup in a human ventricular tissue model. Am J Physiol Heart Circ Physiol. 2006; 291: H1088-H1100
 *
 * Reduced Version:
 * ten Tusscher KH, Panfilov AV. Cell model for efficient simulation of wave propagation in human ventricular tissue under normal and pathological conditions. Phys. Med.Biol., 51: 6141-6156
 *   no intracellular ion dynamics
 *   steady state approximations of fast gating variables
 *   adjusted formulation for ICaL
 *
 * v1.0 - initial version
 * 
 ***/
/*** Header Guard ***/
#ifndef TENTUSSCHER2006_H
#define TENTUSSCHER2006_H

#include "../include/default_model.h" // default_model base class


/*** TenTusscher2006 Class ***/
class TenTusscher2006 : public default_model { // Base class is default_model
    
public:
	TenTusscher2006(void); // Constructor
	virtual ~TenTusscher2006(void); // Destructor

    // Virtual functions for default_model base class
    virtual double iClamp(double); // Current clamp
    virtual double vClamp(double); // Voltage clamp
	virtual void reset(); // Reset model to initial conditions

private:
    void solve(); // Model current solver
    /* Solve functions */
    double mnew(double, double, double);
    double hnew(double, double, double);
    double jnew(double, double, double);
    double xr1new(double, double, double);
    double xr2new(double, double, double);
    double xsnew( double, double, double);
    double rnew( double, double, double);
    double snew( double, double, double);
    double dnew( double, double, double);
    double fnew( double, double, double);
    double f2new( double, double, double);
    double f_cassnew( double, double, double);
    
    /* Constants */
    //External concentrations
    double Ko;
    double Cao;
    double Nao;
    //Intracellular volumes
    double Vc;
    double Vsr;
    double Vss;
    //Calcium buffering dynamics
    double Bufc;
    double Kbufc;
    double Bufsr;
    double Kbufsr;
    double Bufss;
    double Kbufss;
    //Intracellular calcium flux dynamics
    double Vmaxup;
    double Kup;
    double Vrel;
    double k1_;
    double k2_;
    double k3;
    double k4;
    double EC;
    double maxsr;
    double minsr;
    double Vleak;
    double Vxfer;
    //Constants
    double R;
    double F;
    double T;
    //Cellular capacitance
    double CAP;
    //Parameters for IKr
    double Gkr;
    //Parameters for Iks
    double pKNa;
    double Gks;
    //Parameters for Ik1
    double GK1;
    //Parameters for Ito
    double Gto;
    //Parameters for INa
    double GNa;
    //Parameters for IbNa
    double GbNa;
    //Parameters for INaK
    double KmK;
    double KmNa;
    double knak;
    //Parameters for ICaL
    double GCaL;
    //Parameters for IbCa
    double GbCa;
    //Parameters for INaCa
    double knaca;
    double KmNai;
    double KmCa;
    double ksat;
    double n;
    //Parameters for IpCa
    double GpCa;
    double KpCa;
    //Parameters for IpK;
    double GpK;

    /* Variables */
    double RTONF, Ek, Ena, Eks, Eca;

    double alpha_K1, beta_K1, x_K1_inf;
    double V, dV_dt, Cai, CaSR, CaSS, m, h, j, xr1, xr2, xs, r, s, d, f, f2, f_cass, RR, OO, Nai, Ki;  //f_ca;  //Corina change
    double INa, ICaL, Ito, IKr, IKs, IK1, INaCa, INaK, IpCa, IpK, IbNa, IbCa, Istim, Itotal;
    double kCaSR, k1, k2, Ixfer, CaSSBuf, bcss, ccss, Ileak, Iup, Irel, CaBuf, CaCSQN, dCaSS, dCaSR, bjsr, cjsr, dCai, bc, cc;

    double inverseVcF2;
    double inverseVcF;
    double inversevssF2;

    /* Solve Function Variables */
    double alpha_m, beta_m, tau_m, m_inf;
    double alpha_h, beta_h, tau_h, h_inf;
    double alpha_j, beta_j, tau_j, j_inf;
    double alpha_xr1, beta_xr1, xr1_inf, tau_xr1;
    double alpha_xr2, beta_xr2, xr2_inf, tau_xr2;
    double alpha_xs, beta_xs, xs_inf, tau_xs;
    double r_inf, tau_r;
    double s_inf, tau_s;
    double alpha_d, beta_d, gamma_d, tau_d, d_inf;
    double alpha_f, beta_f, gamma_f, tau_f, f_inf;
    double alpha_f2, beta_f2, gamma_f2, tau_f2, f2_inf;
    double f_cass_inf, tau_f_cass;
};

#endif

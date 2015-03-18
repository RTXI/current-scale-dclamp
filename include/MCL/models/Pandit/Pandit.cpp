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
 * Pandit.cpp, v1.4
 *
 * Author: Francis Ortega and Corina Bot (v1.0 - 1.3)(2011)
 * This code has Gt, Gss and Gkslow modified as for Mouse model 60
 *
 *
 ***/

#include <iostream>
#include <math.h>
#include "Pandit.h"

using namespace std;
#define fastEXP RTmath->fastEXP //define shortcut for fastEXP function
#define fastPOW RTmath->fastPOW //define shortcut for fastPOW function

/*** Model Constructor ***/
Pandit::Pandit(void) {
    // External concentrations
    Ko=5.4;
    Nao=140.0;
    Cao=1.2;

    // Intracellular volumes in uL
    Vc=16.0e-6;
    Vnuc=0.32e-6;
    Vmito=5.76e-6;
    Vss=1.2e-9;
    Vsr=0.056e-6;
    Vjsr=0.056e-6;
    Vnsr=0.504e-6;
    Vmyo=9.36e-6;

    // Constants
    R=8314.0;
    F=96487.0;
    T=295.0;

    // Cellular capacitance
    CAP=100e-06*1000; // nF

    // Parameters for INa
    GNa=1.064; // 0.8 * 1.33 for left to right change

    // Parameter for ICaL
    GCaL=0.031;

    // Parameter for Ik1
    Gk1=0.024;

    // Parameter for Ito
    Gt=0.033*0.1;

    // Parameters for background currents
    GbNa=8.015e-05;
    GbCa=3.24e-05;
    GbK=13.8e-05;

    // Parameters for If
    Gf=0.00145;

    // Parameters for INaK
    ImaxNaK=0.08;
    KmNa=10.0;
    KmK=1.5;

    // Parameters for ICaP
    ImaxCaP=0.004;

    // Parameters for INaCa
    kNaCa=0.9984e-05; // Scaling factor
    dNaCa=0.0001; // Denominator constant
    gam = 0.5; // Position of energy barrier

    /* Parameters for SR function */
    v1=1800/1000; // Max RyR channel Ca flux
    Kfb= 168e-03; // Forward half-sat constant for Ca/ATPase
    Krb=3.29;// Backward half-sat constant for Ca/ATPase
    Ksr=1.0; // Scaling factor for Ca/ATPase
    Nfb=1.2; // Forward cooperativity constant for Ca/ATPase
    Nrb=1.0; // Reverse cooperativity constant for Ca/ATPase
    vmaxf=0.4e-01/1000; // Ca/ATPase forward rate parameter
    vmaxr=0.9/1000; // Ca/ATPase reverse rate parameter

    tau_tr=.5747e-03 * 1000; // Time constant for transfer for NSR to JSR
    tau_xfer=26.7e-03*1000; // Time constant for transfer from subspace to myoplasm

    Ka_pos=12.15e12/1000; // RyR Pc1-Po1 rate constant
    Ka_neg=576.0/1000; // RyR Po1-Pc1 rate constant
    Kb_pos=4.05e09/1000; // RyR Po1-Po2 rate constant
    Kb_neg=1.930e03/1000; // RyR Po2-Po1 rate constant
    Kc_pos=.1e03/1000; // RyR Po1-Pc2 rate constant
    Kc_neg=0.0008e03/1000; // RyR Pc2-Po1 rate constant
    n_ry=4.0; // RyR Ca cooperativity parameter Pc1-Po1
    m_ry=3.0; // RyR Ca cooperativity parameter Po1-Po2

    LTRPNtot=70e-03; // total troponin low-affinity site concentration
    HTRPNtot=140e-03; // total troponin high-affinity site concentration
    Khtrpn_pos=200e03/1000; // Ca on rate for troponin high-affinity sites
    Khtrpn_neg=66.0e-03/1000; // Ca off rate for troponin high-affinity sites
    Kltrpn_pos=40e03/1000; // Ca on rate for troponin low-affinity sites
    Kltrpn_neg=.04e03/1000; // Ca off rate for troponin low-affinity sites

    CMDN_tot=50e-03; // Total myoplasm calmodulin concentration
    CSQN_tot=15.0; // Total myoplasm calsequestrin concentration
    EGTA_tot=0.0; // Total myoplasm EGTA concentration

    KmCMDN=2.38e-03; // Ca half-saturation constant for calmodulin

    KmCSQN=0.8; // Ca half-saturation constant for calsequestrin
    KmEGTA=1.5e-04; // Ca half-saturation constant for EGTA

    // taus that are not voltage dependent
    tau_Ca_inact = 1000*0.009;
    tau_s =  1000*0.0572;
    tau_skslow= 1000* 1.174;

    sigma = (exp(Nao/67.3)-1.0)/7.0; 
    ECal = 65.0;
    RTONF = (R*T)/F;
    fna = 0.2;
    fk = 1-fna;

  
    mlkup= new double[7000][23];
    // Make lookup tables for voltage-dependant parameters
    double volt = 0;
    int z = 0;
    V_min = -300;
  
    for(z=0; z<7000; z++){
        volt = V_min+0.1*z;
        mlkup[z][0] = V_min+0.1*z; // v
    
        // Sodium current
        mlkup[z][1] = 1.0/(1.0+exp((volt+45.0)/-6.5));// m_bar
        mlkup[z][2] = 1000*(0.00136/(((0.32*(volt+47.13))/(1.0-exp(-0.1*(volt+47.13))))+ 0.08*exp(-1.0*volt/11.0)));; // tau_m
        mlkup[z][3] = 1.0/(1.0+exp((volt+76.1)/6.07)); // h_bar
	
	
        if (volt >= -40)
            { 
                mlkup[z][4] = 1000*0.0004537*(1.0+exp(-1.0*(volt+10.66)/11.1)); // tau_h
                mlkup[z][5] = 1000*0.01163*(1.0+exp(-0.1*(volt+32.0)))/exp(-2.535e-7*volt); // tau_j
            }
        else
            {
                mlkup[z][4] = 1000*0.00349/(0.135*exp(-1.0*(volt+80.0)/6.8) + 3.56*exp(0.079*volt) + 3.1e5*exp(0.35*volt));// tau_h
                mlkup[z][5] = 1000*0.00349/((volt+37.78)*(-127140.0*exp(0.2444*volt)-3.474e-5*exp(-0.04391*volt))/
                                            (1.0+exp(0.311*(volt+79.23))) +0.1212*exp(-0.01052*volt)/(1.0+exp(-0.1378*(volt+40.14))) ); // tau_j
            }
    
        mlkup[z][6] = 1.0/(1.0+exp((volt+76.1)/6.07)); // j_bar
	
        // L-type calcium current
        mlkup[z][7] = 1.0/(1.0+exp((volt+15.3)/-5.0)); // d_bar
        mlkup[z][8] = 1000*(0.00305*exp(-0.0045*(volt+7.0)*(volt+7.0))+0.00105*exp(-0.002*(volt-18.0)*(volt-18.0)) +0.00025); // tau_d
        mlkup[z][9] = 1.0/(1.0+exp((volt+26.7)/5.4)); // f11_bar
        mlkup[z][10] = 1000*(0.105*exp(-1.0*((volt+45.0)/12.0)*((volt+45.0)/12.0)) + 0.04/(1.0+exp((-1.0*volt+25.0)/25.0)) + 0.015/
                             (1.0+exp((volt+75.0)/25.0))+0.0017); // tau_f11
        mlkup[z][11] = 1.0/(1.0+exp((volt+26.7)/5.4)); // f12_bar
        mlkup[z][12] = 1000*(0.041*exp(-1.0*((volt+47.0)/12.0)*((volt+47.0)/12.0)) + 0.08/(1.0+exp((volt+55.0)/-5.0)) + 0.015/
                             (1.0+exp((volt+75.0)/25.0))+0.0017); // tau_f12
	
        // It current
        mlkup[z][13] = 1.0/(1.0 + exp((volt+12.5)/-7.7)); // r_bar
        mlkup[z][14] = 1000* ( 1.0/(45.16*exp(0.03577*(volt+50.0)) + 98.9*exp(-0.1*(volt+38.0)))); // tau_r
        mlkup[z][15] = 1.0/(1.0 + exp((volt+24.8)/3.5)); // s_bar
	
        // Iss current
        mlkup[z][16] = 1.0/(1.0+exp((volt+12.5)/-7.7)); // rss_bar
        mlkup[z][17] = 1000* (3.0/(45.16*exp(0.03577*(volt+50.0))+ 98.9*exp(-0.1*(volt+38.0)))); // tau_rss
	
        // IKslow current
        mlkup[z][18] = 1.0/(1.0+exp((volt+12.5)/-7.7)); // rkslow_bar
        mlkup[z][19] = 1000* (1.0/(45.16*exp(0.03577*(volt+50.0)) + 98.9*exp(-0.1*(volt+38.0)))); // tau_rkslow
        mlkup[z][20] = 1.0/(1.0+exp((volt+37.6)/5.9)); // skslow_bar
	
        // IfK and IfNa currents
        mlkup[z][21] = 1.0/(1.0 + exp((volt+138.6)/10.48)); // y_inf
        mlkup[z][22] = 1000*(1.0/(0.11885*exp((volt+80.0)/28.37)+ 0.5623*exp((volt+80.0)/-14.19))); // tau_y
	
    } // End of making lookup table

  
   /* // Initial conditions
    V = -8.050146e01;
    m = 4.164108e-03;
    h_gate = 6.735613e-01;
    j = 6.729362e-01;
    d = 2.171081e-06;
    f11 = 9.999529e-01;
    f12 = 9.999529e-01;
    Ca_inact = 9.913102e-01;
    r = 2.191519e-03;
    s = 9.842542e-01;
    rkslow = 6.421196e-1;
    skslow = 3.142767e-1;
    rss = 2.907171e-03;
    y = 3.578708e-03;
    Ca_nsr =  6.607948e-02;
    Ca_ss = 8.737212e-05;
    Ca_jsr = 6.607948e-02;
    Pc1 = 6.348229e-01;
    Po1 = 4.327548e-04;
    Po2 = 6.062540e-10;
    Pc2 = 3.647471e-01;
    ltrpn = 5.161900e-03;
    htrpn = 1.394301e-01;

    Nai = 1.073519e1;
    Ki = 1.392751e2;
    Cai = 7.901351e-05; */

 //initial conditions mouse model 60
      
   // Mouse model 60
    Gss = 0.005 * 0.575;
    Gkslow = 0.014 * 0.575;
    V = -8.084585e+01;
    m = 4.005816e-03;
    h_gate = 6.863717e-01;
    j = 6.863635e-01;
    d = 2.023296e-06;
    f11 = 9.999559e-01;
    f12 = 9.999559e-01;
    Ca_inact = 2.223295e-322;
    r = 1.395230e-04;
    s = 9.999999e-01;
    rkslow = 1.395230e-04;
    skslow = 9.722446e-01;
    rss = 1.395230e-04;
    y = 3.522662e-03;
    Ca_nsr = 6.607948e-02;
    Ca_ss = 8.737212e-05;
    Ca_jsr = 6.607948e-02;
    Pc1 = 6.348229e-01;
    Po1 = 4.327548e-04;
    Po2 = 6.062540e-10;
    Pc2 = 3.647471e-01;
    ltrpn = 5.161900e-03;
    htrpn = 1.394301e-01;
    Nai = 8.456099e+00;
    Ki = 1.438322e+02;
    Cai = 7.901351e-05;

    ENa = RTONF*log(Nao/Nai);
    Ek =  RTONF*log(Ko/Ki);

    cout << "\n**** Pandit Model Cell Loaded ****";
} // End constructor

/*** Model Destructor ***/
Pandit::~Pandit(void){
    delete[] mlkup;
    cout << "\n**** Pandit Model Cell Unloaded ****";
} // End destructor

/**** Solve Function ****/
void Pandit::solve()
{
    // Solver loop
    for(int i = 0; i < steps; i++) 
        {
            calc_currents();
            calc_gates();
        }
} // End solve function


/*** Current Calculation Function ***/
void Pandit::calc_currents(){
    ENa = RTONF*log(Nao/Nai);
	Ek =  RTONF*log(Ko/Ki);
	INa = (GNa*m*m*m*h_gate*j*(V-ENa));
    ICaL = (GCaL*d*((0.9+Ca_inact/10.0)*f11+(0.1-Ca_inact/10.0)*f12)* (V-ECal));
	It = (Gt*r*s*(V-Ek));
	Ikslow = (Gkslow*rkslow*skslow*(V-Ek));
    Iss = (Gss*rss*(V-Ek));
	Ik1 = ((48.0/(fastEXP((V+37.0)/25.0) + fastEXP((V+37.0)/-25.0))+ 10.0)* (0.001/(1.0+ fastEXP((V-Ek-76.77)/-17.0))) +Gk1*(V-Ek-1.73)/(1.0+ fastEXP(1.613*F*(V-Ek-1.73)/(R*T))*(1.0+ fastEXP((Ko-0.9988)/-0.124))));
	IfNa = (Gf*y*(fna*(V-ENa) ));
	IfK  = (Gf*y*(fk*(V-Ek) ));
    INaK = (ImaxNaK*(1.0/(1.0+0.1245*fastEXP(-0.1*V*F/(R*T))+ 0.0365*sigma*fastEXP(-1.0*V*F/(R*T))))*(Ko/(Ko+KmK)) *(1.0/(1.0+fastPOW(KmNa/Nai,1.5))));
    ICaP = (ImaxCaP*(Cai/(Cai+0.0004)));
	INaCa =(kNaCa*(Nai*Nai*Nai*Cao*fastEXP(0.03743*gam*V) - Nao*Nao*Nao*Cai*fastEXP(0.03743*(gam-1.0)*V))/(1.0+dNaCa*(Nao*Nao*Nao*Cai+Nai*Nai*Nai*Cao))) ;
	IBNa = (GbNa * (V - ENa));
	IBK = (GbK * (V - Ek));
	IBCa = (GbCa * (V - ECal));
	IB = IBNa + IBK + IBCa;

    // Since currents are in A/nF, conversion factor of (1/CAP) is used, resulting in Itotal having units of (A/F)
	Itotal = (1/CAP * (INa + It + Ikslow + Iss + Ik1 + IfNa + IfK + INaK + ICaP + INaCa + IB + ICaL)) + I_Inject;

	dV_dt = -Itotal;

} // End calc_currents function

/*** Gate Calculation Function ***/
void Pandit::calc_gates(){
    Nai += DT * -1 * 1e-3 *(INa+IBNa+3.0 * INaCa+3.0* INaK+IfNa)*(1.0/(Vmyo*F));  //1e-3 converts to mM/ms
    Ki  += DT * -1 * 1e-3 *(Iss+IBK+It+Ik1+IfK-2.0*INaK)*(1.0/(Vmyo*F)); //1e-3 converts to mM/ms

#ifdef USE_CALCIUM
    //Calcium handling
    Jtr = (Ca_nsr-Ca_jsr)/tau_tr; //mM/ms
    Jxfer = (Ca_ss-Cai)/tau_xfer; //mM/ms
    htrpn = DT * (Khtrpn_pos*Cai*(HTRPNtot-htrpn)-Khtrpn_neg*htrpn); //mM/ms
    ltrpn = DT * (Kltrpn_pos*Cai*(LTRPNtot-ltrpn)-Kltrpn_neg*ltrpn); //mM/ms
    Jtrpn = htrpn + ltrpn;
    Jrel = v1*(Po1+Po2)*(Ca_jsr-Ca_ss);
    fb = fastPOW(Cai/Kfb,Nfb);
    rb = fastPOW(Ca_nsr/Krb,Nrb);
    Jup = Ksr*(vmaxf*fb-vmaxr*rb)/(1.0+fb+rb); //mM/ms
    Bi = 1.0/(1.0 + CMDN_tot*KmCMDN/((KmCMDN+Cai)*(KmCMDN+Cai)) + EGTA_tot*KmEGTA/((KmEGTA+Cai)*(KmEGTA+Cai)));
    Bss = 1.0/(1.0+CMDN_tot*KmCMDN/((KmCMDN+Ca_ss)*(KmCMDN+Ca_ss)));
    Bjsr = 1.0/(1.0+CSQN_tot*KmCSQN/((KmCSQN+Ca_jsr)*(KmCSQN+Ca_jsr)));
         
         

    Cai += DT * Bi*(Jxfer-Jup-Jtrpn-1e-3*(IBCa-2.0*INaCa+ICaP)*1.0/(2.0*Vmyo*F)); //1e-3 converts second term to mM/ms *ms
    Ca_ss += DT * Bss*(Jrel*Vjsr/Vss - Jxfer*Vmyo/Vss - 1e-3*ICaL/(2.0*Vss*F)); //1e-3 converts last term to mM/ms *ms
    Ca_jsr += DT * Bjsr*(Jtr - Jrel); //mM/ms *ms
    Ca_nsr += DT * (Jup*Vmyo/Vnsr - Jtr*Vjsr/Vnsr);
        

    Pc1 += DT * (-1.0*Ka_pos*fastPOW(Ca_ss,n_ry)*Pc1 + Ka_neg*Po1); // 1/ms * ms
    Po1 += DT * (Ka_pos*fastPOW(Ca_ss,n_ry)*Pc1 - Ka_neg*Po1-Kb_pos*fastPOW(Ca_ss,m_ry)*Po1 +Kb_neg*Po2 - Kc_pos*Po1+Kc_neg*Pc2);// 1/ms *ms
    Po2 += DT * (Kb_pos*fastPOW(Ca_ss,m_ry)*Po1 - Kb_neg*Po2); //1/ms *ms
    Pc2 += DT * (Kc_pos*Po1 - Kc_neg*Pc2); //1/ms*ms
#endif

    ilow = fabs((V-V_min)/0.1);
    linext = -(-V+mlkup[ilow+1][0])/0.1;

    m_bar = (mlkup[ilow+1][1]-mlkup[ilow][1])*linext+mlkup[ilow+1][1];
    tau_m = (mlkup[ilow+1][2]-mlkup[ilow][2])*linext+mlkup[ilow+1][2];
    h_bar = (mlkup[ilow+1][3]-mlkup[ilow][3])*linext+mlkup[ilow+1][3];
    tau_h = (mlkup[ilow+1][4]-mlkup[ilow][4])*linext+mlkup[ilow+1][4];
    tau_j = (mlkup[ilow+1][5]-mlkup[ilow][5])*linext+mlkup[ilow+1][5];
    j_bar = (mlkup[ilow+1][6]-mlkup[ilow][6])*linext+mlkup[ilow+1][6];
    d_bar = (mlkup[ilow+1][7]-mlkup[ilow][7])*linext+mlkup[ilow+1][7];
    tau_d = (mlkup[ilow+1][8]-mlkup[ilow][8])*linext+mlkup[ilow+1][8];
    f11_bar = (mlkup[ilow+1][9]-mlkup[ilow][9])*linext+mlkup[ilow+1][9];
    tau_f11 = (mlkup[ilow+1][10]-mlkup[ilow][10])*linext+mlkup[ilow+1][10];
    f12_bar = (mlkup[ilow+1][11]-mlkup[ilow][11])*linext+mlkup[ilow+1][11];
    tau_f12 = (mlkup[ilow+1][12]-mlkup[ilow][12])*linext+mlkup[ilow+1][12];
    r_bar = (mlkup[ilow+1][13]-mlkup[ilow][13])*linext+mlkup[ilow+1][13];
    tau_r = (mlkup[ilow+1][14]-mlkup[ilow][14])*linext+mlkup[ilow+1][14];
    s_bar = (mlkup[ilow+1][15]-mlkup[ilow][15])*linext+mlkup[ilow+1][15];
    rss_bar = (mlkup[ilow+1][16]-mlkup[ilow][16])*linext+mlkup[ilow+1][16];
    tau_rss = (mlkup[ilow+1][17]-mlkup[ilow][17])*linext+mlkup[ilow+1][17];
    rkslow_bar = (mlkup[ilow+1][18]-mlkup[ilow][18])*linext+mlkup[ilow+1][18];
    tau_rkslow = (mlkup[ilow+1][19]-mlkup[ilow][19])*linext+mlkup[ilow+1][19];
    skslow_bar = (mlkup[ilow+1][20]-mlkup[ilow][20])*linext+mlkup[ilow+1][20];
    y_inf = (mlkup[ilow+1][21]-mlkup[ilow][21])*linext+mlkup[ilow+1][21];
    tau_y = (mlkup[ilow+1][22]-mlkup[ilow][22])*linext+mlkup[ilow+1][22];  
	
    m = m_bar-(m_bar -m)*fastEXP(-DT/tau_m);
    h_gate = h_bar-(h_bar -h_gate)*fastEXP(-DT/tau_h);
    j = j_bar-(j_bar -j)*fastEXP(-DT/tau_j);
    d = d_bar-(d_bar-d)*fastEXP(-DT/tau_d);
    f11 = f11_bar-(f11_bar -f11)*fastEXP(-DT/tau_f11);
    f12 = f12_bar-(f12_bar -f12)*fastEXP(-DT/tau_f12);
    Ca_inact_bar= 1.0/(1.0 + Ca_ss/0.01);  // Added v1.3
    Ca_inact = Ca_inact_bar-(Ca_inact_bar -Ca_inact)*fastEXP(-DT/tau_Ca_inact);
    r = r_bar-(r_bar -r)*fastEXP(-DT/tau_r);
    s = s_bar-(s_bar -s)*fastEXP(-DT/tau_s);
    rss = rss_bar-(rss_bar -rss)*fastEXP(-DT/tau_rss);
    rkslow = rkslow_bar-(rkslow_bar -rkslow)*fastEXP(-DT/tau_rkslow);
    skslow = skslow_bar-(skslow_bar -skslow)*fastEXP(-DT/tau_skslow);
    y =  y_inf-(y_inf -y)*fastEXP(-DT/tau_y);

} // End calc_gates

/*** Virtual functions used by default_model class ***/

// Voltage Clamp Function
double Pandit::vClamp(double voltage){
    // Clamp model voltage
    V = voltage;

    // Run model solver
    solve(); // voltage free to change during this time period

    // Return current
    return Itotal;
}

// Current Clamp Function
double Pandit::iClamp(double current){
    // Inject current into model
    I_Inject = current;

    // Run model solver
    solve();

    // Return voltage
    return V;
}

// Current Return Function
double Pandit::current(int current){

    switch(current){
        
    // Currents
    case 0: return Itotal; break;
    case 1: return INa; break;
    case 2: return It; break;
    case 3: return Ikslow; break;
    case 4: return Iss; break;
    case 5: return Ik1; break;
    case 6: return IfNa; break;
    case 7: return IfK; break;
    case 8: return INaK; break;
    case 9: return ICaP; break;
    case 10: return INaCa; break;
    case 11: return IB; break;
    case 12: return ICaL; break;
    case 13: return GNa; break;
    case 14: return GCaL; break;
    case 15: return Gss; break;
    case 16: return Gkslow; break;
    case 17: return Gk1; break;
    case 18: return Gt; break;
    case 19: return r; break;
        
    default: return -1; break;
    } // End switch(current)
}

// Concentration Return Function
double Pandit::concentration(int concentration){

    switch(concentration){
        
    case 0: return Nai; break;
    case 1: return Ki; break;
    case 2: return Cai; break;
        
    default: return -1; break;
    } // End switch(concentration)
}

// Model Reset Function
void Pandit::reset(){ // Reset to initial conditions
    
    //Initial conditions
/*
    V = -8.050146e01;
    m = 4.164108e-03;
    h_gate = 6.735613e-01;
    j = 6.729362e-01;
    d = 2.171081e-06;
    f11 = 9.999529e-01;
    f12 = 9.999529e-01;
    Ca_inact = 9.913102e-01;
    r = 2.191519e-03;
    s = 9.842542e-01;
    rkslow = 6.421196e-1;
    skslow = 3.142767e-1;
    rss = 2.907171e-03;
    y = 3.578708e-03;
    Ca_nsr =  6.607948e-02;
    Ca_ss = 8.737212e-05;
    Ca_jsr = 6.607948e-02;
    Pc1 = 6.348229e-01;
    Po1 = 4.327548e-04;
    Po2 = 6.062540e-10;
    Pc2 = 3.647471e-01;
    ltrpn = 5.161900e-03;
    htrpn = 1.394301e-01;

    Nai = 1.073519e1;
    Ki = 1.392751e2;
    Cai = 7.901351e-05; */

 //initial conditions mouse model 60
      
   // Mouse model 60
  
    Gss = 0.005 * 0.575;
    Gkslow = 0.014 * 0.575;
    V = -8.084585e+01;
    m = 4.005816e-03;
    h_gate = 6.863717e-01;
    j = 6.863635e-01;
    d = 2.023296e-06;
    f11 = 9.999559e-01;
    f12 = 9.999559e-01;
    Ca_inact = 2.223295e-322;
    r = 1.395230e-04;
    s = 9.999999e-01;
    rkslow = 1.395230e-04;
    skslow = 9.722446e-01;
    rss = 1.395230e-04;
    y = 3.522662e-03;
    Ca_nsr = 6.607948e-02;
    Ca_ss = 8.737212e-05;
    Ca_jsr = 6.607948e-02;
    Pc1 = 6.348229e-01;
    Po1 = 4.327548e-04;
    Po2 = 6.062540e-10;
    Pc2 = 3.647471e-01;
    ltrpn = 5.161900e-03;
    htrpn = 1.394301e-01;
    Nai = 8.456099e+00;
    Ki = 1.438322e+02;
    Cai = 7.901351e-05;


    ENa = RTONF*log(Nao/Nai);
    Ek =  RTONF*log(Ko/Ki);

    cout << "\n**** Pandit model reset to initial conditions ****\n";
}

// Model Specific Conditions Reset Function
int Pandit::reset(double APD){ // Sets initial conditions depending on APD, and also returns mouseModel(int)
    // Choose mouse model depending on APD
    if (APD <= 25.0) mouseModel = 20;
    else if (APD > 25.0 && APD <= 35.0) mouseModel = 30;
    else if (APD > 35.0 && APD <= 45.0) mouseModel = 40;
    else if (APD > 45.0 && APD <= 55.0) mouseModel = 50;
    else if (APD > 55.0 && APD <= 65.0) mouseModel = 60;
    else if (APD > 65.0 && APD <= 75.0) mouseModel = 70;
    else if (APD > 75.0 && APD <= 85.0) mouseModel = 80;
    else if (APD > 85.0 && APD <= 95.0) mouseModel = 90;
    else mouseModel = 100; // APD > 95.0

    // Change appropriate parameters depending on mouseModel;
    switch(mouseModel){
        
    case 20:
        Gss = 0.005 * 1.7;
        Gkslow = 0.014 * 1.7;
        V = -8.100417e+01;
        m = 3.860082e-03;
        h_gate = 6.948809e-01;
        j = 6.948810e-01;
        d = 1.927746e-06;
        f11 = 9.999578e-01;
        f12 = 9.999578e-01;
        Ca_inact = 2.223295e-322;
        r = 1.352101e-04;
        s = 9.999999e-01;
        rkslow = 1.352101e-04;
        skslow = 9.920144e-01;
        rss = 1.352101e-04;
        y = 3.934319e-03;
        Ca_nsr = 6.607948e-02;
        Ca_ss = 8.737212e-05;
        Ca_jsr = 6.607948e-02;
        Pc1 = 6.348229e-01;
        Po1 = 4.327548e-04;
        Po2 = 6.062540e-10;
        Pc2 = 3.647471e-01;
        ltrpn = 5.161900e-03;
        htrpn = 1.394301e-01;
        Nai = 8.712882e+00;
        Ki = 1.444906e+02;
        Cai = 7.901351e-05;
        break; // End case 20
        
    case 30:
        Gss = 0.005 * 1.2;
        Gkslow = 0.014 * 1.2;
        V = -8.095160e+01;
        m = 3.948381e-03;
        h_gate = 6.897047e-01;
        j = 6.897027e-01;
        d = 1.985516e-06;
        f11 = 9.999566e-01;
        f12 = 9.999566e-01;
        Ca_inact = 2.223295e-322;
        r = 1.378259e-04;
        s = 9.999999e-01;
        rkslow = 1.378259e-04;
        skslow = 9.875300e-01;
        rss = 1.378259e-04;
        y = 3.826723e-03;
        Ca_nsr = 6.607948e-02;
        Ca_ss = 8.737212e-05;
        Ca_jsr = 6.607948e-02;
        Pc1 = 6.348229e-01;
        Po1 = 4.327548e-04;
        Po2 = 6.062540e-10;
        Pc2 = 3.647471e-01;
        ltrpn = 5.161900e-03;
        htrpn = 1.394301e-01;
        Nai = 8.646110e+00;
        Ki = 1.442518e+02;
        Cai = 7.901351e-05;
        break; // End case 30

    case 40:
        Gss = 0.005 * 0.9;
        Gkslow = 0.014 * 0.9;
        V = -8.090780e+01;
        m = 3.921885e-03;
        h_gate = 6.912488e-01;
        j = 6.912452e-01;
        d = 1.968128e-06;
        f11 = 9.999570e-01;
        f12 = 9.999570e-01;
        Ca_inact = 2.223295e-322;
        r = 1.370421e-04;
        s = 9.999999e-01;
        rkslow = 1.370421e-04;
        skslow = 9.825950e-01;
        rss = 1.370421e-04;
        y = 3.757779e-03;
        Ca_nsr = 6.607948e-02;
        Ca_ss = 8.737212e-05;
        Ca_jsr = 6.607948e-02;
        Pc1 = 6.348229e-01;
        Po1 = 4.327548e-04;
        Po2 = 6.062540e-10;
        Pc2 = 3.647471e-01;
        ltrpn = 5.161900e-03;
        htrpn = 1.394301e-01;
        Nai = 8.580517e+00;
        Ki = 1.440643e+02;
        Cai = 7.901351e-05;
        break; // End case 40

    case 50:
        Gss = 0.005 * 0.7;
        Gkslow = 0.014 * 0.7;
        V = -8.087234e+01;
        m = 4.022089e-03;
        h_gate = 6.854320e-01;
        j = 6.854254e-01;
        d = 2.034026e-06;
        f11 = 9.999557e-01;
        f12 = 9.999557e-01;
        Ca_inact = 2.223295e-322;
        r = 1.400033e-04;
        s = 9.999999e-01;
        rkslow = 1.400033e-04;
        skslow = 9.772578e-01;
        rss = 1.400033e-04;
        y = 3.605487e-03;
        Ca_nsr = 6.607948e-02;
        Ca_ss = 8.737212e-05;
        Ca_jsr = 6.607948e-02;
        Pc1 = 6.348229e-01;
        Po1 = 4.327548e-04;
        Po2 = 6.062540e-10;
        Pc2 = 3.647471e-01;
        ltrpn = 5.161900e-03;
        htrpn = 1.394301e-01;
        Nai = 8.514994e+00;
        Ki = 1.439248e+02;
        Cai = 7.901351e-05;
        break; // End case 50
 
    case 60:
        Gss = 0.005 * 0.575;
        Gkslow = 0.014 * 0.575;
        V = -8.084585e+01;
        m = 4.005816e-03;
        h_gate = 6.863717e-01;
        j = 6.863635e-01;
        d = 2.023296e-06;
        f11 = 9.999559e-01;
        f12 = 9.999559e-01;
        Ca_inact = 2.223295e-322;
        r = 1.395230e-04;
        s = 9.999999e-01;
        rkslow = 1.395230e-04;
        skslow = 9.722446e-01;
        rss = 1.395230e-04;
        y = 3.522662e-03;
        Ca_nsr = 6.607948e-02;
        Ca_ss = 8.737212e-05;
        Ca_jsr = 6.607948e-02;
        Pc1 = 6.348229e-01;
        Po1 = 4.327548e-04;
        Po2 = 6.062540e-10;
        Pc2 = 3.647471e-01;
        ltrpn = 5.161900e-03;
        htrpn = 1.394301e-01;
        Nai = 8.456099e+00;
        Ki = 1.438322e+02;
        Cai = 7.901351e-05;
        break; // End case 60
        
    case 70:
        Gss = 0.005 * 0.475;
        Gkslow = 0.014 * 0.475;
        V = -8.082087e+01;
        m = 3.990475e-03;
        h_gate = 6.872576e-01;
        j = 6.872476e-01;
        d = 2.013181e-06;
        f11 = 9.999561e-01;
        f12 = 9.999561e-01;
        Ca_inact = 2.223295e-322;
        r = 1.390702e-04;
        s = 9.999999e-01;
        rkslow = 1.390702e-04;
        skslow = 9.664968e-01;
        rss = 1.390702e-04;
        y = 3.425507e-03;
        Ca_nsr = 6.607948e-02;
        Ca_ss = 8.737212e-05;
        Ca_jsr = 6.607948e-02;
        Pc1 = 6.348229e-01;
        Po1 = 4.327548e-04;
        Po2 = 6.062540e-10;
        Pc2 = 3.647471e-01;
        ltrpn = 5.161900e-03;
        htrpn = 1.394301e-01;
        Nai = 8.390674e+00;
        Ki = 1.437557e+02;
        Cai = 7.901351e-05;
        break; // End case 70

    case 80:
        Gss = 0.005 * 0.41;
        Gkslow = 0.014 * 0.41;
        V = -8.080155e+01;
        m = 3.978610e-03;
        h_gate = 6.879426e-01;
        j = 6.879309e-01;
        d = 2.005357e-06;
        f11 = 9.999562e-01;
        f12 = 9.999562e-01;
        Ca_inact = 2.223295e-322;
        r = 1.387201e-04;
        s = 9.999999e-01;
        rkslow = 1.387201e-04;
        skslow = 9.613508e-01;
        rss = 1.387201e-04;
        y = 3.338707e-03;
        Ca_nsr = 6.607948e-02;
        Ca_ss = 8.737212e-05;
        Ca_jsr = 6.607948e-02;
        Pc1 = 6.348229e-01;
        Po1 = 4.327548e-04;
        Po2 = 6.062540e-10;
        Pc2 = 3.647471e-01;
        ltrpn = 5.161900e-03;
        htrpn = 1.394301e-01;
        Nai = 8.332834e+00;
        Ki = 1.437045e+02;
        Cai = 7.901351e-05;
        break; // End case 80

    case 90:
        Gss = 0.005 * 0.355;
        Gkslow = 0.014 * 0.355;
        V = -8.078260e+01;
        m = 4.090587e-03;
        h_gate = 6.815024e-01;
        j = 6.814858e-01;
        d = 2.079354e-06;
        f11 = 9.999547e-01;
        f12 = 9.999547e-01;
        Ca_inact = 2.223295e-322;
        r = 1.420214e-04;
        s = 9.999998e-01;
        rkslow = 1.420214e-04;
        skslow = 9.555115e-01;
        rss = 1.420214e-04;
        y = 3.181580e-03;
        Ca_nsr = 6.607948e-02;
        Ca_ss = 8.737212e-05;
        Ca_jsr = 6.607948e-02;
        Pc1 = 6.348229e-01;
        Po1 = 4.327548e-04;
        Po2 = 6.062540e-10;
        Pc2 = 3.647471e-01;
        ltrpn = 5.161900e-03;
        htrpn = 1.394301e-01;
        Nai = 8.271795e+00;
        Ki = 1.436581e+02;
        Cai = 7.901351e-05;
        break; // End case 90

    case 100:
        Gss = 0.005 * 0.315;
        Gkslow = 0.014 * 0.315;
        V = -8.076557e+01;
        m = 4.079966e-03;
        h_gate = 6.821101e-01;
        j = 6.820912e-01;
        d = 2.072317e-06;
        f11 = 9.999549e-01;
        f12 = 9.999549e-01;
        Ca_inact = 2.223295e-322;
        r = 1.417087e-04;
        s = 9.999998e-01;
        rkslow = 1.417087e-04;
        skslow = 9.498209e-01;
        rss = 1.417087e-04;
        y = 3.098781e-03;
        Ca_nsr = 6.607948e-02;
        Ca_ss = 8.737212e-05;
        Ca_jsr = 6.607948e-02;
        Pc1 = 6.348229e-01;
        Po1 = 4.327548e-04;
        Po2 = 6.062540e-10;
        Pc2 = 3.647471e-01;
        ltrpn = 5.161900e-03;
        htrpn = 1.394301e-01;
        Nai = 8.215027e+00;
        Ki = 1.436195e+02;
        Cai = 7.901351e-05;
        break; // End case 100

    } // End switch(mouseModel)

    cout << "**** Pandit Model " << mouseModel << " chosen ****" << endl;
    return mouseModel; // Return mouse model
} // End changeInit()

// Conductance modifier for the genetic algorithm
// Uses mouse model 60 as a starting point
// Modifies [GNaScale, GCaLScale, GssScale, GkslowScale, Gk1Scale, GtScale]
void Pandit::reset(double *optimizations){ // Using the array pointer, modify certain parameters of the model (Used with the genetic algorithm)

    // Mouse model 60
    Gss = 0.005 * 0.575;
    Gkslow = 0.014 * 0.575;
    V = -8.084585e+01;
    m = 4.005816e-03;
    h_gate = 6.863717e-01;
    j = 6.863635e-01;
    d = 2.023296e-06;
    f11 = 9.999559e-01;
    f12 = 9.999559e-01;
    Ca_inact = 2.223295e-322;
    r = 1.395230e-04;
    s = 9.999999e-01;
    rkslow = 1.395230e-04;
    skslow = 9.722446e-01;
    rss = 1.395230e-04;
    y = 3.522662e-03;
    Ca_nsr = 6.607948e-02;
    Ca_ss = 8.737212e-05;
    Ca_jsr = 6.607948e-02;
    Pc1 = 6.348229e-01;
    Po1 = 4.327548e-04;
    Po2 = 6.062540e-10;
    Pc2 = 3.647471e-01;
    ltrpn = 5.161900e-03;
    htrpn = 1.394301e-01;
    Nai = 8.456099e+00;
    Ki = 1.438322e+02;
    Cai = 7.901351e-05;

    // Genetic algorithm modifications
    GNa = 1.064 * optimizations[0];
    GCaL = 0.031 * optimizations[1];
    Gss *= optimizations[2];
    Gkslow *= optimizations[3];
    Gk1 = 0.024 * optimizations[4];
    Gt *= optimizations[5];

    cout << "*** PANDIT *** GA optimizations complete\n";
    cout << "Optimizations " << optimizations[0] << " " << optimizations[1] << " " << optimizations[2] << " " << optimizations[3] << " " << optimizations[4] << " " << optimizations[5] << "\n";
    cout << "Optimized conductances " << GNa << " " << GCaL << " " <<Gss << " " << Gkslow << " " << Gk1 << " " << Gt << "\n";
}

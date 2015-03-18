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
 * TenTusscher2006.cpp, v1.0
 *
 * Author: Corina Bot and Francis Ortega (v1.0)(2011)
 *
 *** NOTES
 *
 * v1.0 - initial version
 *
 ***/

#include <math.h>
#include <iostream>
#include "TenTusscher2006.h"

using namespace std;

#define fastEXP RTmath->fastEXP //define shortcut for fastEXP function

#define LENGTH 10000000
#define NAME 20

#define EPI
//#define ENDO
//#define MCELL

TenTusscher2006::TenTusscher2006(void){
    /* Initialize Constants */
    //External concentrations
    Ko=5.4;
    Cao=2.0;
    Nao=140.0;    
    //Intracellular volumes
    Vc=0.016404;
    Vsr=0.001094;
    Vss=0.00005468;    
    //Calcium buffering dynamics
    Bufc=0.2;
    Kbufc=0.001;
    Bufsr=10.0;
    Kbufsr=0.3;
    Bufss=0.4;
    Kbufss=0.00025;    
    //Intracellular calcium flux dynamics
    Vmaxup=0.006375;
    Kup=0.00025;
    Vrel=0.102;
    k1_=0.15;
    k2_=0.045;
    k3=0.060;
    k4=0.005;
    EC=1.5;
    maxsr=2.5;
    minsr=1.;
    Vleak=0.00036;
    Vxfer=0.0038;   
    //Constants
    R=8314.472;
    F=96485.3415;
    T=310.0;    
    //Cellular capacitance
    CAP=0.185;    
    //Parameters for IKr
    Gkr=0.153;    
    //Parameters for Iks
    pKNa=0.03;
#ifdef EPI
    Gks=0.392;
#endif
#ifdef ENDO
    Gks=0.392;
#endif
#ifdef MCELL
    Gks=0.098;
#endif    
    //Parameters for Ik1
    GK1=5.405;    
    //Parameters for Ito
#ifdef EPI
    Gto = 0.294;
#endif
#ifdef ENDO
    Gto = 0.073;
#endif
#ifdef MCELL
    Gto = 0.294;
#endif    
    //Parameters for INa
    GNa=14.838;  
    //Parameters for IbNa
    GbNa=0.00029;
    //Parameters for INaK
    KmK=1.0;
    KmNa=40.0;
    knak=2.724;
    //Parameters for ICaL
    GCaL=0.00003980;
    //Parameters for IbCa
    GbCa=0.000592;
    //Parameters for INaCa
    knaca=1000;
    KmNai=87.5;
    KmCa=1.38;
    ksat=0.1;
    n=0.35;
    //Parameters for IpCa
    GpCa=0.1238;
    KpCa=0.0005;
    //Parameters for IpK;
    GpK=0.0146;

    RTONF = (R*T)/F;
    inverseVcF2=1/(2*Vc*F);
    inverseVcF=1/(Vc*F);
    inversevssF2=1/(2*Vss*F);

    //Internal concentrations
    Nai = 10.170516;
    Ki = 139.371006;

    //Initial values for BCL = 1000 ms
    V = -86.139864;
    Cai = 0.000105;
    CaSR = 3.533937;
    CaSS = 0.000210;
    m = 0.001414;
    h = 0.768983;
    j = 0.768685;
    xr1 = 0.000186;
    xr2 = 0.480633;
    xs = 0.003060;
    r = 0.000000;
    s = 0.999998;
    d = 0.000030;
    f = 0.977599;
    f2 = 0.999463;
    f_cass = 0.999973;
    RR = 0.989237;
    OO = 0.000000;

    cout << "\n**** TenTusscher2006 Model Cell Loaded ****";
}

TenTusscher2006::~TenTusscher2006(void){
    cout << "\n**** TenTusscher2006 Model Cell Unloaded ****";
}

void TenTusscher2006::solve() {

    for (i=0; i<steps; i++) {

        Eca = 0.5*RTONF*(log((Cao/Cai)));
        Ek = RTONF*(log((Ko/Ki)));
        Ena = RTONF*(log((Nao/Nai)));
        Eks = RTONF*(log((Ko+pKNa*Nao)/(Ki+pKNa*Nai)));

        alpha_K1 = 0.1/(1.+fastEXP(0.06*(V-Ek-200)));
        beta_K1 = (3.*fastEXP(0.0002*(V-Ek+100))+fastEXP(0.1*(V-Ek-10)))/(1.+fastEXP(-0.5*(V-Ek)));
        x_K1_inf = alpha_K1/(alpha_K1+beta_K1);

        INa = GNa*m*m*m*h*j*(V-Ena);
        ICaL = GCaL*d*f*f2*f_cass*4*(V-15)*(F*F/(R*T))*(0.25*fastEXP(2*(V-15)*F/(R*T))*CaSS-Cao)/(fastEXP(2*(V-15)*F/(R*T))-1.);
        Ito = Gto*r*s*(V-Ek);
        IKr = Gkr*sqrt(Ko/5.4)*xr1*xr2*(V-Ek);
        IKs = Gks*xs*xs*(V-Eks);
        IK1 = GK1*sqrt(Ko/5.4)*x_K1_inf*(V-Ek);
        INaCa = knaca*(1.0/(KmNai*KmNai*KmNai+Nao*Nao*Nao))*(1.0/(KmCa+Cao))*(1.0/(1+ksat*fastEXP((n-1)*V*F/(R*T))))*(fastEXP(n*V*F/(R*T))*Nai*Nai*Nai*Cao-fastEXP((n-1)*V*F/(R*T))*Nao*Nao*Nao*Cai*2.5);
        INaK = knak*(Ko/(Ko+KmK))*(Nai/(Nai+KmNa))*(1./(1.+0.1245*fastEXP(-0.1*V*F/(R*T))+0.0353*fastEXP(-V*F/(R*T))));
        IpCa = GpCa*Cai/(KpCa+Cai);
        IpK = GpK*(V-Ek)*(1./(1.+fastEXP((25-V)/5.98)));
        IbNa = GbNa*(V-Ena);
        IbCa = GbCa*(V-Eca);

        //Itotal = 1/CAP *(INa + ICaL + Ito + IKr + IKs + IK1 + INaCa + INaK + IpCa + IpK + IbNa + IbCa + Istim);
        Itotal = INa + ICaL + Ito + IKr + IKs + IK1 + INaCa + INaK + IpCa + IpK + IbNa + IbCa + Istim;

        dV_dt = -Itotal;  //Corina change

        Nai=Nai+DT*(-(INa+IbNa+3*INaK+3*INaCa)*inverseVcF*CAP);
        Ki=Ki+DT*(-(Istim+IK1+Ito+IKr+IKs-2*INaK+IpK)*inverseVcF*CAP);

        kCaSR=maxsr-((maxsr-minsr)/(1+(EC/CaSR)*(EC/CaSR)));
        k1=k1_/kCaSR;
        k2=k2_*kCaSR;
        RR=RR+DT*(k4*(1-RR)-k2*CaSS*RR);
        OO=k1*CaSS*CaSS*RR/(k3+k1*CaSS*CaSS);

        Irel=Vrel*OO*(CaSR-CaSS);
        Ileak=Vleak*(CaSR-Cai);
        Iup=Vmaxup/(1.+((Kup*Kup)/(Cai*Cai)));
        Ixfer=Vxfer*(CaSS-Cai);

        CaCSQN=Bufsr*CaSR/(CaSR+Kbufsr);
        dCaSR=DT*(Iup-Irel-Ileak);
        bjsr=Bufsr-CaCSQN-dCaSR-CaSR+Kbufsr;
        cjsr=Kbufsr*(CaCSQN+dCaSR+CaSR);
        CaSR=(sqrt(bjsr*bjsr+4*cjsr)-bjsr)/2;

        CaSSBuf=Bufss*CaSS/(CaSS+Kbufss);
        dCaSS=DT*(-Ixfer*(Vc/Vss)+Irel*(Vsr/Vss)+(-ICaL*inversevssF2*CAP));
        bcss=Bufss-CaSSBuf-dCaSS-CaSS+Kbufss;
        ccss=Kbufss*(CaSSBuf+dCaSS+CaSS);
        CaSS=(sqrt(bcss*bcss+4*ccss)-bcss)/2;

        CaBuf=Bufc*Cai/(Cai+Kbufc);
        dCai=DT*((-(IbCa+IpCa-2*INaCa)*inverseVcF2*CAP)-(Iup-Ileak)*(Vsr/Vc)+Ixfer);
        bc=Bufc-CaBuf-dCai-Cai+Kbufc;
        cc=Kbufc*(CaBuf+dCai+Cai);
        Cai=(sqrt(bc*bc+4*cc)-bc)/2;

        m = mnew(m,V, DT);
        h = hnew(h,V, DT);
        j = jnew(j,V, DT);
        xr1 = xr1new(xr1,V, DT);
        xr2 = xr2new(xr2,V, DT);
        xs = xsnew(xs,V, DT);
        r = rnew(r,V, DT);
        s = snew(s,V, DT);
        d = dnew(d,V, DT);
        f = fnew(f,V, DT);
        f2 = f2new(f2,V, DT);
        f_cass = f_cassnew(f_cass,CaSS, DT);

        V += DT * dV_dt;
    }  // End of for loop
}

double TenTusscher2006::vClamp(double voltage){
    // Clamp model voltage
    V = voltage;

    // Run model solver
    solve(); // voltage free to change during this time period

    // Return current
    return Itotal;
}

double TenTusscher2006::iClamp(double current){
    // Inject current into model
    I_Inject = current;

    // Run model solver
    solve();

    // Return voltage
    return V;
}

void TenTusscher2006::reset(){
    //Initial values for BCL = 1000 ms
    V = -86.139864;
    Cai = 0.000105;
    CaSR = 3.533937;
    CaSS = 0.000210;
    m = 0.001414;
    h = 0.768983;
    j = 0.768685;
    xr1 = 0.000186;
    xr2 = 0.480633;
    xs = 0.003060;
    r = 0.000000;
    s = 0.999998;
    d = 0.000030;
    f = 0.977599;
    f2 = 0.999463;
    f_cass = 0.999973;
    RR = 0.989237;
    OO = 0.000000;
    cout << "\n**** TenTusscher2006 model reset to initial conditions ****";
}

double TenTusscher2006::mnew( double m, double V, double DT ) {
    alpha_m = 1./(1.+fastEXP((-60.-V)/5.));
    beta_m = 0.1/(1.+fastEXP((V+35.)/5.))+0.10/(1.+fastEXP((V-50.)/200.));

    tau_m = alpha_m*beta_m;
    m_inf = 1./((1.+fastEXP((-56.86-V)/9.03))*(1.+fastEXP((-56.86-V)/9.03)));

    return m_inf-(m_inf-m)*fastEXP(-DT/tau_m);
}

double TenTusscher2006::hnew( double h, double V, double DT ) {    
    if ( V >= -40. )
        {
            alpha_h = 0.;
            beta_h = (0.77/(0.13*(1.+fastEXP(-(V+10.66)/11.1))));
        }
    else
        {
            alpha_h = (0.057*fastEXP(-(V+80.)/6.8));
            beta_h = (2.7*fastEXP(0.079*V)+(3.1e5)*fastEXP(0.3485*V));
        }

    tau_h = 1.0/(alpha_h+beta_h);
    h_inf = 1./((1.+fastEXP((V+71.55)/7.43))*(1.+fastEXP((V+71.55)/7.43)));

    return h_inf-(h_inf-h)*fastEXP(-DT/tau_h);
}

double TenTusscher2006::jnew( double j, double V, double DT ) {  
	if( V >= -40. ) {
        alpha_j = 0.;
        beta_j = (0.6*fastEXP((0.057)*V)/(1.+fastEXP(-0.1*(V+32.))));
    }
	else {
        alpha_j = (((-2.5428e4)*fastEXP(0.2444*V)-(6.948e-6)*fastEXP(-0.04391*V))*(V+37.78)/(1.+fastEXP(0.311*(V+79.23))));
        beta_j = (0.02424*fastEXP(-0.01052*V)/(1.+fastEXP(-0.1378*(V+40.14))));
    }

    tau_j = 1.0/(alpha_j+beta_j);
    j_inf = 1./((1.+fastEXP((V+71.55)/7.43))*(1.+fastEXP((V+71.55)/7.43)));

    return j_inf-(j_inf-j)*fastEXP(-DT/tau_j);
}

double TenTusscher2006::xr1new( double xr1, double V, double DT ) {    
    xr1_inf = 1./(1.+fastEXP((-26.-V)/7.));
    alpha_xr1 = 450./(1.+fastEXP((-45.-V)/10.));
    beta_xr1 = 6./(1.+fastEXP((V-(-30.))/11.5));
    tau_xr1 = alpha_xr1*beta_xr1;

    return xr1_inf-(xr1_inf-xr1)*fastEXP(-DT/tau_xr1);
}

double TenTusscher2006::xr2new( double xr2, double V, double DT ) {    
    xr2_inf = 1./(1.+fastEXP((V-(-88.))/24.));
    alpha_xr2 = 3./(1.+fastEXP((-60.-V)/20.));
    beta_xr2 = 1.12/(1.+fastEXP((V-60.)/20.));
    tau_xr2 = alpha_xr2*beta_xr2;

    return xr2_inf-(xr2_inf-xr2)*fastEXP(-DT/tau_xr2);
}

double TenTusscher2006::xsnew( double xs, double V, double DT ) {    
    xs_inf = 1./(1.+fastEXP((-5.-V)/14.));
    alpha_xs = 1400./(sqrt(1.+fastEXP((5.-V)/6)));
    beta_xs = 1./(1.+fastEXP((V-35.)/15.));
    tau_xs = alpha_xs*beta_xs+80;

    return xs_inf-(xs_inf-xs)*fastEXP(-DT/tau_xs);
}

double TenTusscher2006::rnew( double r, double V, double DT ) {    
    r_inf = 1./(1.+fastEXP((20.0-V)/6.));
    tau_r = 9.5*fastEXP(-(V+40.)*(V+40.)/1800.)+0.8;

    return r_inf-(r_inf-r)*fastEXP(-DT/tau_r);
}

double TenTusscher2006::snew( double s, double V, double DT ) {    
#ifdef EPI
    s_inf = 1./(1.+fastEXP((V+20.0)/5.));
    tau_s = 85.*fastEXP(-(V+45.)*(V+45.)/320.)+5./(1.+fastEXP((V-20.)/5.))+3.;
#endif
#ifdef ENDO
    s_inf = 1./(1.+fastEXP((V+28.)/5.));
    tau_s = 1000.*fastEXP(-(V+67.)*(V+67.)/1000.)+8.;
#endif
#ifdef MCELL
    s_inf = 1./(1.+fastEXP((V+20.0)/5.));
    tau_s = 85.*fastEXP(-(V+45.)*(V+45.)/320.)+5./(1.+fastEXP((V-20.)/5.))+3.;
#endif

    return s_inf-(s_inf-s)*fastEXP(-DT/tau_s);
}

double TenTusscher2006::dnew( double d, double V, double DT ) {   
    alpha_d = 1.4/(1.+fastEXP((-35-V)/13))+0.25;
    beta_d = 1.4/(1.+fastEXP((V+5)/5));
    gamma_d = 1./(1.+fastEXP((50-V)/20));

    tau_d = alpha_d*beta_d+gamma_d;
    d_inf = 1./(1.+fastEXP((-8-V)/7.5));

    return d_inf-(d_inf-d)*fastEXP(-DT/tau_d);
}

double TenTusscher2006::fnew( double f, double V, double DT ) {    
    alpha_f = 1102.5*fastEXP(-(V+27)*(V+27)/225);
    beta_f = 200./(1+fastEXP((13-V)/10.));
    gamma_f = (180./(1+fastEXP((V+30)/10)))+20;

    tau_f = alpha_f+beta_f+gamma_f;
    f_inf = 1./(1.+fastEXP((V+20)/7));

    return f_inf-(f_inf-f)*fastEXP(-DT/tau_f);
}

double TenTusscher2006::f2new( double f2, double V, double DT ) {
    alpha_f2 = 562*fastEXP(-(V+27)*(V+27)/240);
    beta_f2 = 31/(1.+fastEXP((25-V)/10));
    gamma_f2 = 80/(1.+fastEXP((V+30)/10));

    tau_f2 = alpha_f2+beta_f2+gamma_f2;
    f2_inf = 0.67/(1.+fastEXP((V+35)/7))+0.33;

    return f2_inf-(f2_inf-f2)*fastEXP(-DT/tau_f2);
}

double TenTusscher2006::f_cassnew( double f_cass, double CaSS, double DT ) {
    f_cass_inf = 0.6/(1+(CaSS/0.05)*(CaSS/0.05))+0.4;
    tau_f_cass = 80./(1+(CaSS/0.05)*(CaSS/0.05))+2.;

    return f_cass_inf-(f_cass_inf-f_cass)*fastEXP(-DT/tau_f_cass);
}

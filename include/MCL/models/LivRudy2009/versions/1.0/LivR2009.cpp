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
 * LivR2009.cpp, v1.0
 *
 * Author: Francis Ortega (v1.0)(2011)
 *
 *** NOTES
 *
 * Model equations taken from Matlab model created by Dr. Eric Sobie.
 * Plugin constructed using only DefaultGUIModel.
 *
 * math.h function exp(x) replaced with fastEXP(x) which uses PowFast.hpp due
 * to spikes in computation time of math.h function.
 *
 ***/

#include <math.h>
#include "LivR2009.h"
#include <rtfile.h>

/*** Model Constructor ***/
LivR2009::LivR2009(void){ // Model initialization
	
	// Initial conditions at 0 beats
	// Not being used, retained as a reference
	/*
	  V = -84.7;
	  Cai = 0.0822e-3;
	  CaNSR = 1.25;
	  CaJSR = 1.25;
	  Nai = 9.71;
	  Ki = 142.82;
	  m = 2.46e-4;
	  h = 0.99869;
	  j = 0.99887;
	  d = 1e-4;
	  f = 0.983;
	  b = 1e-4;
	  g = 0.983;
	  xKr = 0.229;
	  xs1 = 1e-4;
	  xs2 = 1e-4;
	  Jrel = 1e-4;
	*/

	// Initial conditions after 700 beats
	V = -88.9248;
	Cai = 1.1366e-04;
	CaNSR = 1.7519;
	CaJSR = 1.6213;
	Nai = 14.1538;
	Ki = 136.5910;
	m = 8.0083e-04;
	h = 0.9931;
	j = 0.9957;
	d = 9.8446e-26;
	f = 0.9998;
	b = 9.6988e-04;
	g = 0.9942;
	xKr = 1.2471e-04;
	xs1 = 0.0049;
	xs2 = 0.0243;
	Jrel = 2.4967e-18;

	// Gating Variable Lookup Table
	lkup= new double[20000][20];
	Vx = 0; // Voltage placeholder for lookup table
	V_min = -1000;

	// Lookup Table
	for(z=0; z<20000; z++){
		Vx = V_min+0.1*z;

		// Voltage
		lkup[z][0] = V_min+0.1*z;

		// H-gate
		lambda_na = 1 - 1/(1+exp(-(Vx+40)/0.024));
		ah = lambda_na * 0.135 * exp(-(80+Vx)/6.8);
		bh = (1-lambda_na) / (0.13*(1+exp((Vx+10.66)/(-11.1)))) + lambda_na * (3.56*exp(0.079*Vx) + 3.1 * 1e5 * exp(0.35*Vx));
		lkup[z][1] = ah/(ah + bh); // hinf
		lkup[z][2] = 1/(ah + bh); // tauh

		// J-gate
		aj =  lambda_na * (-1.2714e5*exp(0.2444*Vx)-3.474e-5*exp(-0.04391*Vx)) * (Vx+37.78) / (1+exp(0.311*(Vx+79.23)));
		bj = (1-lambda_na) * (0.3*exp(-2.535e-7*Vx) / (1+exp(-0.1*(Vx+32)))) + 
			lambda_na * (0.1212*exp(-0.01052*Vx) / (1+exp(-0.1378*(Vx+40.14))));
		lkup[z][3] = 1/(aj + bj); // tauj
		lkup[z][4] = aj/(aj + bj); // jinf

		// M-gate
		if( Vx > -47.14 && Vx < -47.12)// if V = -47.13, divide by 0 error
			am = 3.41333;
		else
			am = 0.32 * (Vx+47.13) / (1-exp(-0.1*(Vx+47.13)));
		bm = 0.08 * exp(-Vx/11.0);
		lkup[z][5] = am / (am + bm); // minf
		lkup[z][6] = 1/(am + bm); // taum

		// D-gate
		dinf_0 = 1/(1+exp(-(Vx+10)/6.24));
		dinf_1 = 1/(1+exp(-(Vx+60)/0.024));
		lkup[z][7] = dinf_0 * dinf_1; // dinf
		if( Vx > -10.01 && Vx < -9.99)// if V = -10, divide by 0 error
			lkup[z][8] = 2.30655; // taud
		else
			lkup[z][8] =  1/(1+exp(-(Vx+10)/6.24)) * (1-exp(-(Vx+10)/6.24))/(0.035*(Vx+10)); // taud

		// F-gate
		lkup[z][9] = 1/(1+exp((Vx+32)/8.0))+(0.6)/(1+exp((50-Vx)/20.0)); // finf
		lkup[z][10] = 1/(0.0197 * exp(-(0.0337*(Vx+10))*(0.0337*(Vx+10))) + 0.02); // tauf

		// B-gate
		lkup[z][11] = 1/(1+exp(-(Vx+14.0)/10.8)); // binf
		lkup[z][12] = (3.7 + 6.1/(1+exp((Vx+25.0)/4.5))); // taub

		// G-gate
		lambda_g = 1 - 1/(1+exp(-Vx/0.0024));
		lkup[z][13] = 1/(1+exp((Vx+60.0)/5.6)); // ginf
		lkup[z][14] = 1 * (lambda_g*(-0.875*Vx+12.0) + 12.0 * (1-lambda_g)); // taug

		// IKr
		if( Vx > -30.01 && Vx < -29.99 ) // if V = -30, divide by 0 error
			tau_xs1 = 411.501;
		else
			tau_xs1 = 10000/(0.719*(Vx+30) / (1-exp(-0.148*(Vx+30))) + 1.31 * (Vx+30) / (exp(0.0687*(Vx+30))-1));
		lkup[z][15] = 1/(1+exp(-(Vx+21.5)/7.5)); // xKrinf
		if( Vx > -14.21 && Vx < -14.19 ) // if V = -14.2, divide by 0 error
			lkup[z][16] = 87.1735; // tauxKr
		lkup[z][16] = ( 1/(0.00138*(Vx+14.2) / (1-exp(-0.123*(Vx+14.2))) + 0.00061 * (Vx+38.9) / (exp(0.145*(Vx+38.9))-1)) ); // tauxKr
		lkup[z][17] = tau_xs1; // tau_xs1
		lkup[z][18] = 4 * tau_xs1; // tau_xs2
		lkup[z][19] = 1/(1+exp(-(Vx-1.5)/16.7)); // xsinf
	}
	
	// Create PowFast object
	powFast = new PowFast(18); // PowFast object with maximum precision

	// Current Length
	currentLength = 2;
	
}

/*** Model Destructor ***/
LivR2009::~LivR2009(void){
}

/*** Model Current Calculation ***/
void LivR2009::calc_currents(double DT, double voltage, double stim){ // Parameters: (DT , voltage , stimulus current)
	
	V = voltage;
	
	// Reversel Potentials
	ENa = RTF * log(Nao/Nai);
	EK = RTF * log(Ko/Ki);
	EKs = RTF * log((Ko + pKNa*Nao)/(Ki + pKNa*Nai));
	ECa = 0.5 * RTF * log(Cao/Cai);

	// Na currents
	INa = GNa_ * m*m*m * h * j * (V - ENa);
	INab = GNab * (V - ENa);

	// L-type Ca current
	ICa_ = PCa * 4 * F * FRT * V * (gamma_Cai*Cai*fastEXP(2*V*FRT) - gamma_Cao*Cao)/(fastEXP(2*V*FRT) - 1);
	ICaK_ = PCa_K * F * FRT * V * (gamma_Ki*Ki*fastEXP(V*FRT) - gamma_Ko*Ko)/(fastEXP(V*FRT) - 1);
	ICaNa_ = PCa_Na * F * FRT * V * (gamma_Nai*Nai*fastEXP(V*FRT) - gamma_Nao*Nao) / (fastEXP(V*FRT) - 1) ;
	fCa = 1/(Cai/KmCa + 1);
	ICaL = ICa_ * d * f * fCa;
	ICaL_K = ICaK_* d * f * fCa;
	ICaL_Na = ICaNa_ * d * f * fCa;
		
	// Background calcium current
	ICab = GCab * (V - ECa);
				
	// Sarcolemmal calcium pump
	IpCa = IpCa_ * Cai / (Cai + KmpCa);

	// T-type Ca current
	ICaT = GCaT * b*b * g * (V-ECa);

	// K currents
	// Time independent K current
	xK1 = 0.004 * (1 + fastEXP(0.6987*(V-EK+11.724))) / (1+fastEXP(0.6168*(V-EK+4.872)));
	IK1 = GK1_ * sqrt(Ko/5.4) * (V-EK) / (1+xK1);

	// Fast component of the delayed rectifier K current
	RKr = 1/(fastEXP((V+9)/22.4) + 1);
	IKr = GKr_ * sqrt(Ko/5.4) * xKr * RKr * (V - EK);
	
	// Fast component of the delayed rectifier K current
	//IKs = GKs_ * (1 + 0.6/(pow(3.8e-5/Cai,1.4)+1)) * xs1 * xs2 * (V - EKs);
	IKs = GKs_ * (1 + 0.6/(fastEXP(1.4*log(3.8e-5/Cai))+1)) * xs1 * xs2 * (V - EKs); // pow() removed
	
	// Plateau K current
	Kp = 1/(1+fastEXP((7.488-V)/5.98));
	IKp = GKp_ * Kp * (V - EK);

	// Pumps and transporters
	// Na-K pump
	sigma_NaK = (fastEXP(Nao/67.3) - 1) / 7.0; 
	fNaK = 1/(1 + 0.1245*fastEXP(-0.1*V*FRT) + 0.0365 * sigma_NaK * fastEXP(-V*FRT));
	//INaK = INaK_ * fNaK * Ko / ( (Ko + KmK_NaK) * pow( 1 + ((KmNa_NaK/Nai)*(KmNa_NaK/Nai)),2) );
	INaK = INaK_ * fNaK * Ko / ( (Ko + KmK_NaK) * ( 1 + ((KmNa_NaK/Nai)*(KmNa_NaK/Nai))) ); // pow() removed
	
	// Na-Ca exchanger
	INCX = kNCX * fastEXP((eta-1)*V*FRT) * ((Nai*Nai*Nai)*Cao*fastEXP(V*FRT)-(Nao*Nao*Nao)*Cai) / 
		(1+ksat*fastEXP((eta-1)*V*FRT) * ((Nai*Nai*Nai)*Cao*fastEXP(V*FRT)+(Nao*Nao*Nao)*Cai) );

	// Intracellular Ca fluxes
	// SR Ca release, uptake, and leak 
	//Jrelinf = alpha_rel * beta_tau * ICaL / (pow((Krel_inf/CaJSR),hrel) + 1);
	Jrelinf = alpha_rel * beta_tau * ICaL / (fastEXP(hrel*log(Krel_inf/CaJSR)) + 1);
	tau_rel = beta_tau / (Krel_tau/CaJSR + 1);
	dJreldt = - (Jrelinf + Jrel) / tau_rel;

	Jserca = Vserca * (Cai/(Cai+Kmserca) - CaNSR/CaNSR_max );

	Jtr = (CaNSR-CaJSR) / tau_transfer;

	// Buffering factors for rapid buffering approximation
	BJSR = 1.0/(1 + CSQNtot * KmCSQN / ((KmCSQN + CaJSR)*(KmCSQN + CaJSR)));
	Bi = 1.0/(1 + ( CMDNtot * KmCMDN / ( (Cai+KmCMDN)*(Cai+KmCMDN) ) ) + (TRPNtot * KmTRPN / ( (Cai+KmTRPN)*(Cai+KmTRPN) ) ) );

	// Total Current
	Iion = INa + INab + ICaL + ICaL_Na + ICaL_K + ICab + ICaT + IpCa + IKr + IKs + IK1 + IKp + INCX + INaK - stim;

	// Derivatives for ionic concentration
	dNai = -(INa + INab + ICaL_Na + 3*INCX + 3*INaK)*Acap/(Vmyo*F);
	dKi = -(IKr + IKs + IK1 + IKp + ICaL_K - 2*INaK)*Acap/(Vmyo*F);
	dCai = Bi * ( -Jserca*VNSR/Vmyo + Jrel*VJSR/Vmyo - (ICaL + ICaT + ICab + IpCa - 2*INCX) * Acap / (2*Vmyo*F) ) ;
	dCaJSR = BJSR * (Jtr - Jrel);
	dCaNSR = Jserca - Jtr * VJSR / VNSR;
	
	// Derivative for voltage
	dVdt = -(Iion);
				
	// Update voltage and ionic concentrations
	V += DT*dVdt;
	Nai += DT*dNai;
	Ki += DT*dKi;
	Cai += DT*dCai;
	CaJSR += DT*dCaJSR;
	CaNSR += DT*dCaNSR;
	Jrel += DT*dJreldt;

	// Set gating variables using lookup table
	ilow = fabs((V-V_min)/0.1);
	linext = -(-V+lkup[ilow+1][0])/0.1;
	hinf = (lkup[ilow+1][1]-lkup[ilow][1])*linext+lkup[ilow+1][1];
	tauh = (lkup[ilow+1][2]-lkup[ilow][2])*linext+lkup[ilow+1][2];
	tauj = (lkup[ilow+1][3]-lkup[ilow][3])*linext+lkup[ilow+1][3];
	jinf = (lkup[ilow+1][4]-lkup[ilow][4])*linext+lkup[ilow+1][4];
	minf = (lkup[ilow+1][5]-lkup[ilow][5])*linext+lkup[ilow+1][5];
	taum = (lkup[ilow+1][6]-lkup[ilow][6])*linext+lkup[ilow+1][6];
	dinf = (lkup[ilow+1][7]-lkup[ilow][7])*linext+lkup[ilow+1][7];
	taud = (lkup[ilow+1][8]-lkup[ilow][8])*linext+lkup[ilow+1][8];
	finf = (lkup[ilow+1][9]-lkup[ilow][9])*linext+lkup[ilow+1][9];
	tauf = (lkup[ilow+1][10]-lkup[ilow][10])*linext+lkup[ilow+1][10];
	binf = (lkup[ilow+1][11]-lkup[ilow][11])*linext+lkup[ilow+1][11];
	taub = (lkup[ilow+1][12]-lkup[ilow][12])*linext+lkup[ilow+1][12];
	ginf = (lkup[ilow+1][13]-lkup[ilow][13])*linext+lkup[ilow+1][13];
	taug = (lkup[ilow+1][14]-lkup[ilow][14])*linext+lkup[ilow+1][14];
	xKrinf = (lkup[ilow+1][15]-lkup[ilow][15])*linext+lkup[ilow+1][15];
	tauxKr = (lkup[ilow+1][16]-lkup[ilow][16])*linext+lkup[ilow+1][16];
	tauxs1 = (lkup[ilow+1][17]-lkup[ilow][17])*linext+lkup[ilow+1][17];
	tauxs2 = (lkup[ilow+1][18]-lkup[ilow][18])*linext+lkup[ilow+1][18];
	xsinf = (lkup[ilow+1][19]-lkup[ilow][19])*linext+lkup[ilow+1][19];

	
	// Update gating variables - Euler Method
	h += DT*((hinf-h) / tauh);
	j += DT*((jinf-j) / tauj);
	m = (minf - (minf-m)*fastEXP(-DT/taum)); //Rush-Larsen approximation used for m gate, Euler method too unstable
	d += DT*((dinf - d)/taud);
	f += DT*((finf - f)/tauf);
	b += DT*((binf-b) / taub);
	g += DT*((ginf-g) / taug);
	xKr += DT*((xKrinf - xKr)/tauxKr);
	xs1 += DT*((xsinf - xs1) / tauxs1);
	xs2 += DT*((xsinf - xs2) / tauxs2);
}

/*** Current Scaling Function ***/
double LivR2009::scale_current(current_t current, double factor){ // Parameters: (Current to be scaled , scaling factor)

	// Switch structure to scale a specific current
	switch(current){

	case IKS:
		return IKs*factor;
		break;
		
	case INA:
		return INa*factor;
		break;
		
	case IKR:
		return IKr*factor;
		break;
	}
	return 0;
		
}

/*** Get Current Function ***/
double LivR2009::get_current(current_t current){ // Parameters: (Desired current)

	// Switch structure to choose which current magnitude to return
	switch(current){

	case IKS:
		return IKs;
		break;

	case INA:
		return INa;
		break;

	case IKR:
		return IKr;
		break;
	}
	return 0;
}

/*** Optimized e^x function using PowFast ***/
double LivR2009::fastEXP(double x){
	if(x > 88.5 || x < -87){ // prevent overflow since powFast uses floats

		powCount = 1;
		powAns = 1;
		powExp = x;
		
		while(powExp > 88.5 || powExp < -87){
			powCount++;
			powExp = x / powCount;
		}

		for(int n = 1; n <= powCount; n++){
			powAns = powAns * powFast->e(powExp);
		}

		return powAns;
		
	}
		
	else
		return powFast->e(x);
}

/*** Reset Function ***/
void LivR2009::reset(){ // Reset to initial conditions
		// Initial conditions at 0 beats
	// Not being used, retained as a reference
	/*
	  V = -84.7;
	  Cai = 0.0822e-3;
	  CaNSR = 1.25;
	  CaJSR = 1.25;
	  Nai = 9.71;
	  Ki = 142.82;
	  m = 2.46e-4;
	  h = 0.99869;
	  j = 0.99887;
	  d = 1e-4;
	  f = 0.983;
	  b = 1e-4;
	  g = 0.983;
	  xKr = 0.229;
	  xs1 = 1e-4;
	  xs2 = 1e-4;
	  Jrel = 1e-4;
	*/

	// Initial conditions after 700 beats
	V = -88.9248;
	Cai = 1.1366e-04;
	CaNSR = 1.7519;
	CaJSR = 1.6213;
	Nai = 14.1538;
	Ki = 136.5910;
	m = 8.0083e-04;
	h = 0.9931;
	j = 0.9957;
	d = 9.8446e-26;
	f = 0.9998;
	b = 9.6988e-04;
	g = 0.9942;
	xKr = 1.2471e-04;
	xs1 = 0.0049;
	xs2 = 0.0243;
	Jrel = 2.4967e-18;
}

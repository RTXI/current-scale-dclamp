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

#include <iostream>
#include <math.h>
#include "WangSobie.h"

using namespace std;
#define fastEXP RTmath->fastEXP //define shortcut for fastEXP function
#define fastPOW RTmath->fastPOW //define shortcut for fastPOW function
#define SODIUM_STEPS 4 // Sodium is integrated 3 times faster than rest of model for stability

/*** Model Constructor ***/
WangSobie::WangSobie(void) {

    // Initialization of constants
    myParams2.F = 96.5;                   
    myParams2.R = 8.314;                
    myParams2.T = 298;
    myParams2.RTF = 25.67;			
    myParams2.VJSR = 1.2e-9;            
    myParams2.VNSR = 2.098e-7;        
    myParams2.Acap = 1.5410e-5;         
    myParams2.Vmyo = 2.286e-6;           
    myParams2.Vss = 3.0734e-8;             
    myParams2.Cm = 1;                  
    myParams2.Ko = 5400; // Ko uM
    myParams2.Nao = 140000; // Nao uM
    myParams2.Cao = 1000; // Cao uM
    myParams2.Clo = 132000; // Clo uM
    myParams2.Cli = 30000; //Cli uM
    myParams2.GNa_ = 10; // 16 for Markov, 10 for HH GNa ms/uF
    myParams2.GNab_ = 0.0026; // GNab ms/uF
    myParams2.GCab_ = 0.00025; // GCab ms/uF
    myParams2.GK1_ = 0.235; // GK1 ms/uF
    myParams2.GKr_ = 1.17; // GKr ms/uF
    myParams2.GKs_ = 0.046; // GKs ms/uF
    myParams2.GKtof_ = 0.1017; // GKtof ms/uF
    myParams2.GKur_ = 0.0048; // GKur ms/uF
    myParams2.GKss_ = 0.015; // GKss ms/uF
    myParams2.kf_Kr = 0.023761; // kf_Kr ms-1
    myParams2.kb_Kr = 0.036778; // kb_Kr ms-1
    myParams2.P_CaCl = 2.74e-7; // P_CaCl cm/s
    myParams2.n_h = 3; // n_h 
    myParams2.Km_CaCl = 4; // Km_CaCl uM
    myParams2.GCaL_ = 0.19019; // GCal ms/uF
    myParams2.ECaL = 63; // ECaL mV
    myParams2.Kpcmax = 0.23324; // Kpcmax ms-1
    myParams2.Kpchalf = 20; // Kpchalf uM 
    myParams2.kPCFmax = 13; // kPCFmax new from Bondarenko to be able to vary voltage inactivation
    myParams2.kPCB = 0.0005; // kPCB ms-1 
    myParams2.ICaLmax = 7; // ICaLmax pA/pF 
    myParams2.GCaT_ = 0.055; // GCaT ms/uF 
    myParams2.ECaT = 50; // ECaT ms/uF  
    myParams2.kNaCa = 907.68; // kNaCa uA/uF 
    myParams2.KmNa = 87500; // KmNa uM 
    myParams2.KmCa = 1380; // KmCa uM 
    myParams2.ksat = 0.1; // ksat 
    myParams2.eta = 0.35; // eta 
    myParams2.INaKmax = 0.88; // INaKmax pA/pF 
    myParams2.KmNai = 21000; // KmNai uM 
    myParams2.KmKo = 1500; // KmKo uM 
    myParams2.Ipmax = 0.2; // Ipmax pA/pF 0.4 
    myParams2.KmpCa = 0.5; // KmpCa uM 
    myParams2.nu1 = 0.45; // nu1 ms-1 
    myParams2.nu2= .088e-5; // nu2 ms-1 
    myParams2.nu3= 0.09; // nu3 ms-1 
    myParams2.Kmserca =0.5; // Kmserca uM  
    myParams2.tau_transfer = 20; // tau_transfer ms  
    myParams2.tau_xfer = 8; // tau_xfer ms 
    myParams2.kaplus = 0.006075; // kaplus uM-4 ms-1 
    myParams2.kaminus =0.07125; // kaminus ms-1 
    myParams2.kbplus = 0.00405; // kbplus uM-3 ms-1 
    myParams2.kbminus = 0.965; // kbminus ms-1 
    myParams2.kcplus = 0.009; // kcplus ms-1 
    myParams2.kcminus= 0.0008; // kcminus ms-1 
    myParams2.nRyR = 4; // nRyR 
    myParams2.mRyR = 3; // mRyR 
    myParams2.LOWTRPNtot = 35; // LOWTRPNtot uM 
    myParams2.HIGHTRPNtot = 70; // HIGHTRPNtot uM 
    myParams2.LOWkp_Ca = 0.0327; // LOWkp_Ca 
    myParams2.HIGHkp_Ca = 0.00237; // HIGHkp_Ca uM-1 ms-1 
    myParams2.LOWkm_Ca = 0.0196; // LOWkm_Ca 
    myParams2.HIGHkm_Ca = 3.2e-5; // HIGHKm_Ca ms-1 
    myParams2.CMDNtot = 25; // CMDNtot uM 
    myParams2.KmCMDN = 0.238; // KmCMDN uM 
    myParams2.CSQNtot = 15000; // CSQNtot uM 
    myParams2.KmCSQN = 800; // KmCSQN uM 
    myParams2.sigma = (exp(140000/67300) - 1)/7;
 
    // Lookup Table for gates calculations
    mlkup= new double[7000][33];
    //make lookup tables for voltage-dependant parameters
    double V = 0;
    int z = 0;
    V_min = -300;
  
    for(z=0; z<7000; z++){
        V = V_min+0.1*z;
        mlkup[z][0] = V_min+0.1*z; //v
    
        //Sodium current
        mlkup[z][1] = 0.32*(V+47.13)/(1-exp(-0.1*(V+47.13)));//am
        mlkup[z][2] = 0.08*exp(-V/11); //bm
    
        if (V >= -40)
            { mlkup[z][3] = 0; //ah
                mlkup[z][4] = 0; //aj
                mlkup[z][5] = 1/(0.13*(1+exp((V+10.66)/(-11.1)))); //bh
                mlkup[z][6] = 0.3*exp(-2.535*pow(10,(-7))*V)/(1+exp(-0.1*(V+32)));}//bj
        else
            { mlkup[z][3] = 0.135*exp((80+V)/(-6.8)); //ah
                mlkup[z][4] = (-1.2714*10e5*exp(0.2444*V)-3.474*10e-5*exp(-0.04391*V))*(V+37.78)/(1+exp(0.311*(V+79.23)));//aj
                mlkup[z][5] = 3.56*exp(0.079*V)+3.1*10e5*exp(0.35*V); //bh
                mlkup[z][6] = 0.1212*exp(-0.01052*V)/(1+exp(-0.1378*(V+40.14))); //bj
            }
    
        //L-type calcium current
        mlkup[z][7] = 0.4*exp((V+12)/10)*(0.7*exp(-pow((V+40),2)/10) - 0.75*exp(-pow((V+20),2)/400) + 1)/(0.12*exp((V+12)/10) + 1); //alpha_L
        mlkup[z][8] = 0.05*exp(-(V+12)/13); //beta_L
        mlkup[z][9] = myParams2.kPCFmax*(1 - exp(-pow((V+14.5),2)/100)); //kPCF
    
        //T-type calcium current
        mlkup[z][10] =  1/(1+ exp(-(V+48)/6.1)); //b_Tinf
        mlkup[z][11] = 1/(1+ exp((V+66)/6.6)); //g_Tinf
        mlkup[z][12] = 0.1 + (5.4/(1+exp((V+100)/33))); //taub_T
        mlkup[z][13] = 8 + (32/(1+exp((V+65)/5))); //taug_T   
    
        //IKs current
        if(V > -26.59 && V < -26.41) //to account for indeterminate derivative
            mlkup[z][14] = (4.81333e-6)/(.128 * exp(-0.128*(V + 26.5))); //an
    
        else
            mlkup[z][14] = 4.81333e-6*(V + 26.5)/(1 - exp(-0.128*(V + 26.5))); //an
        mlkup[z][15] = 9.53333e-5*exp(-0.038*(V + 26.5));	//bn
    
        //IKr current
        mlkup[z][16] = 0.022348*exp(0.01176*V);//a0_Kr
        mlkup[z][17] = 0.047002*exp(-0.0631*V); //b0_Kr
        mlkup[z][18] = 0.013773*exp(0.038198*V); //a1_Kr
        mlkup[z][19] = 6.89e-5*exp(-0.04178*V); //b1_Kr
        mlkup[z][20] = 0.090821*exp(0.023391*(V+5)); //ai_Kr
        mlkup[z][21] = 0.006497*exp(-0.03268*(V+5)); //bi_Kr
    
        //Itof current
        mlkup[z][22] = 0.18064*exp(0.03577*(V+30)); //aatof
        mlkup[z][23] = 0.3956*exp(-0.06237*(V+30)); //batof
        mlkup[z][24] = 0.000152*exp(-(V-3.81)/15.75)/(0.067083*exp(-(V+132.05)/15.75) + 1); //aitof
        mlkup[z][25] = 0.00095*exp((V+132.05)/15.75)/(0.051335*exp((V+132.05)/15.75) + 1); //bitof
        mlkup[z][26] = 0.000152*exp(-(V+13.5)/7)/(0.067083*exp(-(V+33.5)/7) + 1); //aitof2
        mlkup[z][27] = 0.00095*exp((V+33.5)/7)/(0.051335*exp((V+33.5)/7) + 1); //bitof2
    
        //IKur current
        mlkup[z][28] = 1/(exp(-(V+22.5)/7.7) + 1); //akinf
        mlkup[z][29] = 1/(exp((V+45.2)/5.7) + 1); //ikinf
        mlkup[z][30] = 0.493*exp(-0.0629*V) + 2.058; //tauaur
        mlkup[z][31] = 1200 - 170/(exp((V+45.2)/5.7) + 1); //tauiur
    
        //IKss current
        mlkup[z][32] = 13.17 + 39.3*exp(-0.0862*V); //tauakss
    } //end of making lookup table
  
    sodium_y2[0]= 0.0032; //m
    sodium_y2[1]= 0.9605; //h
    sodium_y2[2]= 0.9743; //j
  
    y2[0]= -80.63; //V
    y2[1]= 8.5734e-4; //O1_ryr
    y2[2]= 2.3420e-8; //O2_ryr
    y2[3]= 0.0768; //C2_ryr
    y2[4]= 8.8918; //LOWCaTRPN
    y2[5]= 65.9936; //HIGHCaTRPN
    y2[6]= 1.9638e-13; //PRyR
    y2[7]= 0.2040; //Cai
    y2[8]= 0.1867; //Cass
    y2[9]= 704.5995; //CaJSR
    y2[10]= 702.1971; //CaNSR
    y2[11]= 2.1748e4; //Nai
    y2[12]= 1.3644e5; //Ki
    y2[13]= 1.2036e-14; //used to be y2[16]- O_L
    y2[14]= 1.7049e-4; //C2_L
    y2[15]= 1.0895e-8; //C3_L
    y2[16]= 4.2195e-12; //C4_L
    y2[17]= 9.4119e-10; //I1_L
    y2[18]= 3.1179e-11; //I2_L
    y2[19]= 6.8932e-9; //I3_L
    y2[20]= 0.0047; //b_T
    y2[21]= 0.9017; //g_T
    y2[22]= 0.0021; //n
    y2[23]= 0.0011; //C1_Kr
    y2[24]= 7.8269e-4; //C2_Kr
    y2[25]= 0.0011; //O_Kr	
    y2[26]= 2.3215e-4; //I_Kr
    y2[27]= 0.0032; //atof
    y2[28]= 0.7527; //itof
    y2[29]= 5.2609e-4; //aur
    y2[30]= 0.9902; //iur
    y2[31]= 0.8441; //akss

    Params2 = &myParams2; //define a pointer so that the #defines will be consistent  
    sodium_Params2 = &sodium_myParams2; //define a pointer so that the #defines will be consistent 

    cout << "\n**** WangSobie Model Cell Loaded ****";
} // End constructor

/*** Model Destructor ***/
WangSobie::~WangSobie(void){
    delete[] mlkup;
    cout << "\n**** WangSobie Model Cell Unloaded ****";
} // End destructor

/**** Solve Function ****/
void WangSobie::solve()
{
    // Solver loop
    for(int i = 0; i < steps; i++) 
        {
            calc_currents();
            calc_gates();

            for(int j = 0; j < (SODIUM_STEPS); j++){ // Sodium Loop, runs SODIUM_STEPS times faster than rest of model
                calc_sodium(DT / SODIUM_STEPS);
            }
        }
} // End solve function

// Define shortcuts for constants

#define am sodium_Params2->am
#define bm sodium_Params2->bm
#define ah sodium_Params2->ah
#define aj sodium_Params2->aj
#define bh sodium_Params2->bh
#define bj sodium_Params2->bj
#define F Params2->F  
#define R Params2->R  
#define T Params2->T  
#define RTF Params2->RTF 
#define VJSR Params2->VJSR 
#define VNSR Params2->VNSR  
#define Acap Params2->Acap  
#define Vmyo Params2->Vmyo  
#define Vss Params2->Vss  
#define Cm Params2->Cm 
#define Ko Params2->Ko  
#define Nao Params2->Nao  
#define Cao Params2->Cao  
#define Clo Params2->Clo  
#define Cli Params2->Cli 
#define GNa_ Params2->GNa_  
#define GNab_ Params2->GNab_  
#define GCab_ Params2->GCab_  
#define GK1_ Params2->GK1_  
#define GKr_ Params2->GKr_  
#define GKs_ Params2->GKs_  
#define GKtof_ Params2->GKtof_  
#define GKur_ Params2->GKur_  
#define GKss_ Params2->GKss_  
#define kf_Kr Params2->kf_Kr  
#define kb_Kr Params2->kb_Kr  
#define n_h Params2->n_h  
#define P_CaCl Params2->P_CaCl 
#define Km_CaCl Params2->Km_CaCl  
#define GCaL_ Params2->GCaL_  
#define ECaL Params2->ECaL  
#define Kpcmax Params2->Kpcmax  
#define Kpchalf Params2->Kpchalf  
#define kPCFmax Params2->kPCFmax  
#define kPCB Params2->kPCB  
#define ICaLmax Params2->ICaLmax  
#define GCaT_ Params2->GCaT_  
#define ECaT Params2->ECaT 
#define kNaCa Params2->kNaCa  
#define KmNa Params2->KmNa  
#define KmCa Params2->KmCa  
#define ksat Params2->ksat  
#define eta Params2->eta  
#define INaKmax Params2->INaKmax  
#define KmNai Params2->KmNai  
#define KmKo Params2->KmKo   
#define Ipmax Params2->Ipmax  
#define KmpCa Params2->KmpCa 
#define nu1 Params2->nu1  
#define nu2 Params2->nu2  
#define nu3 Params2->nu3  
#define Kmserca Params2->Kmserca  
#define tau_transfer Params2->tau_transfer  
#define tau_xfer Params2->tau_xfer 
#define kaplus Params2->kaplus  
#define kaminus Params2->kaminus  
#define kbplus Params2->kbplus  
#define kbminus Params2->kbminus  
#define kcplus Params2->kcplus  
#define kcminus Params2->kcminus  
#define nRyR Params2->nRyR  
#define mRyR Params2->mRyR 
#define LOWTRPNtot Params2->LOWTRPNtot 
#define HIGHTRPNtot Params2->HIGHTRPNtot  
#define LOWkp_Ca Params2->LOWkp_Ca  
#define HIGHkp_Ca Params2->HIGHkp_Ca  
#define LOWkm_Ca Params2->LOWkm_Ca 
#define HIGHkm_Ca Params2->HIGHkm_Ca  
#define CMDNtot Params2->CMDNtot  
#define KmCMDN Params2->KmCMDN  
#define CSQNtot Params2->CSQNtot  
#define KmCSQN Params2->KmCSQN
#define sigma Params2->sigma	
#define ENa Params2->ENa 
#define ECa Params2->ECa
#define EK Params2->EK
#define INa Params2->INa
#define INab Params2->INab
#define ICaL Params2->ICaL
#define ICaT Params2->ICaT
#define ICab Params2->ICab
#define IpCa Params2->IpCa
#define INCX Params2->INCX
#define fNaK Params2->fNaK
#define INaK Params2->INaK
#define IKr Params2->IKr
#define IKs Params2->IKs
#define IK1 Params2->IK1
#define IKtof Params2->IKtof
#define IKur Params2->IKur
#define IKss Params2->IKss
#define f_CaCl Params2->f_CaCl
#define ICaCl Params2->ICaCl
#define Iion Params2->Iion
#define Jrel Params2->Jrel
#define Jtransfer Params2->Jtransfer
#define Jxfer Params2->Jxfer
#define Jleak Params2->Jleak
#define Jserca Params2->Jserca
#define Bi Params2->Bi
#define Bss Params2->Bss
#define BJSR Params2->BJSR
#define dCaTRPN Params2->dCaTRPN
#define Jtrpn Params2->Jtrpn
#define alpha_L Params2->alpha_L
#define beta_L Params2->beta_L
#define gamma_L Params2->gamma_L
#define kPCF Params2->kPCF
#define b_Tinf Params2->b_Tinf
#define g_Tinf Params2->g_Tinf
#define taub_T Params2->taub_T
#define taug_T Params2->taug_T
#define an Params2->an
#define bn Params2->bn
#define a0_Kr Params2->a0_Kr
#define b0_Kr Params2->b0_Kr
#define a1_Kr Params2->a1_Kr
#define b1_Kr Params2->b1_Kr
#define ai_Kr Params2->ai_Kr
#define bi_Kr Params2->bi_Kr
#define aatof Params2->aatof
#define batof Params2->batof
#define aitof Params2->aitof
#define bitof Params2->bitof
#define aitof2 Params2->aitof2
#define bitof2 Params2->bitof2
#define itofinf Params2->itofinf
#define tauitof Params2->tauitof
#define akinf Params2->akinf
#define ikinf Params2->ikinf
#define tauaur Params2->tauaur
#define tauiur Params2->tauiur
#define tauakss Params2->tauakss
#define C1_L Params2->C1_L
#define C0_Kr Params2->C0_Kr
#define C1_ryr Params2->C1_ryr
// end define shortcuts

/*** Current Calculation Function ***/
void WangSobie::calc_currents(){
    ENa = RTF*log(Nao/y2[11]);
    ECa = RTF/2*log(Cao/y2[7]);
    EK = RTF*log(Ko/y2[12]);
  
    INa = 10*fastPOW(sodium_y2[0],3)*sodium_y2[1]*sodium_y2[2]*(y2[0]-ENa); //HH description
    INab = GNab_*(y2[0] - ENa);
    ICaL = GCaL_*y2[13]*(y2[0] - ECaL);
    ICaT = GCaT_*y2[20]*y2[21]*(y2[0] - ECaT);
    ICab = GCab_*(y2[0] - ECa);
    IpCa = Ipmax*fastPOW(y2[7],2)/(fastPOW(y2[7],2) + fastPOW(KmpCa,2));
    INCX = kNaCa*(1/(fastPOW(KmNa,3) + fastPOW(Nao,3)))*(1/(KmCa + Cao))*(1/(ksat*fastEXP((eta-1)*y2[0]/RTF) + 1)) *
        (fastEXP(eta*y2[0]/RTF)*fastPOW(y2[11],3)*Cao - fastEXP((eta-1)*y2[0]/RTF)*fastPOW(Nao,3)*y2[7]);
    fNaK = 1/(1 + 0.1245*fastEXP(-0.1*y2[0]/RTF) + 0.0365*sigma*fastEXP(-y2[0]/RTF));
    INaK = INaKmax*fNaK*Ko/(Ko + KmKo)*(1/(1 + fastPOW((KmNai/y2[11]),1.5)));
    IKr = GKr_*y2[25]*(y2[0] - EK);
    IKs = GKs_*fastPOW(y2[22],2)*(y2[0] - EK);
    IK1 = GK1_*Ko/(Ko + 210)*(y2[0] - EK)/(fastEXP(0.0896*(y2[0]-EK)) + 1);
    IKtof = GKtof_*fastPOW(y2[27],6.5)*y2[28]*(y2[0] - EK);
    IKur = GKur_*y2[29]*y2[30]*(y2[0] - EK);
    IKss = GKss_*y2[30]*(y2[0] - EK);
    f_CaCl = fastPOW((y2[8]/(Km_CaCl + y2[8])),n_h); 
    ICaCl = P_CaCl*f_CaCl*(y2[0]*fastPOW(F,2)/(R*T))*((Clo*fastEXP(y2[0]*F/(R*T))- Cli)/(fastEXP(y2[0]*F/(R*T))-1));
    Iion = INa + INab + ICaL + ICaT + ICab + IpCa + INCX + INaK + IKtof + IKur + IKr + IKs + IKss + IK1 + ICaCl + I_Inject;
} // End calc_currents function

/*** Gate Calculation Function ***/
void WangSobie::calc_gates()
{
    ilow = fabs((y2[0]-V_min)/0.1);
    linext = -(-y2[0]+mlkup[ilow+1][0])/0.1;
    //parameters for HH sodium current calculation
    am = (mlkup[ilow+1][1]-mlkup[ilow][1])*linext+mlkup[ilow+1][1];
    bm = (mlkup[ilow+1][2]-mlkup[ilow][2])*linext+mlkup[ilow+1][2];
    ah = (mlkup[ilow+1][3]-mlkup[ilow][3])*linext+mlkup[ilow+1][3];
    aj = (mlkup[ilow+1][4]-mlkup[ilow][4])*linext+mlkup[ilow+1][4];
    bh = (mlkup[ilow+1][5]-mlkup[ilow][5])*linext+mlkup[ilow+1][5];
    bj = (mlkup[ilow+1][6]-mlkup[ilow][6])*linext+mlkup[ilow+1][6];
  
    //parameters for all other currents
    alpha_L = (mlkup[ilow+1][7]-mlkup[ilow][7])*linext+mlkup[ilow+1][7];
    beta_L = (mlkup[ilow+1][8]-mlkup[ilow][8])*linext+mlkup[ilow+1][8];
    kPCF = (mlkup[ilow+1][9]-mlkup[ilow][9])*linext+mlkup[ilow+1][9];
    b_Tinf = (mlkup[ilow+1][10]-mlkup[ilow][10])*linext+mlkup[ilow+1][10];
    g_Tinf = (mlkup[ilow+1][11]-mlkup[ilow][11])*linext+mlkup[ilow+1][11];
    taub_T = (mlkup[ilow+1][12]-mlkup[ilow][12])*linext+mlkup[ilow+1][12];
    taug_T = (mlkup[ilow+1][13]-mlkup[ilow][13])*linext+mlkup[ilow+1][13];
    an = (mlkup[ilow+1][14]-mlkup[ilow][14])*linext+mlkup[ilow+1][14];
    bn = (mlkup[ilow+1][15]-mlkup[ilow][15])*linext+mlkup[ilow+1][15];
    a0_Kr = (mlkup[ilow+1][16]-mlkup[ilow][16])*linext+mlkup[ilow+1][16];
    b0_Kr = (mlkup[ilow+1][17]-mlkup[ilow][17])*linext+mlkup[ilow+1][17];
    a1_Kr = (mlkup[ilow+1][18]-mlkup[ilow][18])*linext+mlkup[ilow+1][18];
    b1_Kr = (mlkup[ilow+1][19]-mlkup[ilow][19])*linext+mlkup[ilow+1][19];
    ai_Kr = (mlkup[ilow+1][20]-mlkup[ilow][20])*linext+mlkup[ilow+1][20];
    bi_Kr = (mlkup[ilow+1][21]-mlkup[ilow][21])*linext+mlkup[ilow+1][21];
    aatof= (mlkup[ilow+1][22]-mlkup[ilow][22])*linext+mlkup[ilow+1][22];  
    batof= (mlkup[ilow+1][23]-mlkup[ilow][23])*linext+mlkup[ilow+1][23];
    aitof= (mlkup[ilow+1][24]-mlkup[ilow][24])*linext+mlkup[ilow+1][24];
    bitof= (mlkup[ilow+1][25]-mlkup[ilow][25])*linext+mlkup[ilow+1][25];
    aitof2= (mlkup[ilow+1][26]-mlkup[ilow][26])*linext+mlkup[ilow+1][26];
    bitof2= (mlkup[ilow+1][27]-mlkup[ilow][27])*linext+mlkup[ilow+1][27];
    akinf= (mlkup[ilow+1][28]-mlkup[ilow][28])*linext+mlkup[ilow+1][28];
    ikinf= (mlkup[ilow+1][29]-mlkup[ilow][29])*linext+mlkup[ilow+1][29];
    tauaur= (mlkup[ilow+1][30]-mlkup[ilow][30])*linext+mlkup[ilow+1][30];
    tauiur= (mlkup[ilow+1][31]-mlkup[ilow][31])*linext+mlkup[ilow+1][31];
    tauakss= (mlkup[ilow+1][32]-mlkup[ilow][32])*linext+mlkup[ilow+1][32];
  
    //parameters not in lookup tables
    tauitof = 1/(aitof2+bitof2);
    itofinf = aitof/(aitof+bitof);
    gamma_L = Kpcmax*y2[8]/(Kpchalf+y2[8]);
  
    //Ca release
    Jrel = nu1*(y2[1] + y2[2])*(y2[9] - y2[8])*y2[6];
    Jtransfer = (y2[10] - y2[9])/tau_transfer;
    Jxfer = (y2[8] - y2[7])/tau_xfer;
    Jleak = nu2*(y2[10] - y2[7]);
    Jserca = nu3*fastPOW(y2[7],2)/(fastPOW(y2[7],2) + fastPOW(Kmserca,2));
    Jtrpn = -LOWkm_Ca*y2[4] + LOWkp_Ca*y2[7]*(LOWTRPNtot - y2[4])+-HIGHkm_Ca*y2[5] + HIGHkp_Ca*y2[7]*(HIGHTRPNtot - y2[5]);//This may have to go into calcDerivatives
  
    //Buffers
    Bi = fastPOW((1 + CMDNtot*KmCMDN/fastPOW((KmCMDN + y2[7]),2)),-1);
    Bss = fastPOW((1 + CMDNtot*KmCMDN/fastPOW((KmCMDN + y2[8]),2)),-1);
    BJSR = fastPOW((1 + CSQNtot*KmCSQN/fastPOW((KmCSQN + y2[9]),2)),-1);
  
    //Last markov states
    C1_ryr = 1 - (y2[3] + y2[1] + y2[2]);
    C0_Kr = 1 - (y2[23] + y2[24] + y2[25] + y2[26]);
    C1_L = 1 - (y2[13] + y2[14] + y2[15] + y2[16] + y2[17] + y2[18] + y2[19]); \

    // Derivatives
    dy2[0] = -Iion;
    dy2[1] = kaplus*fastPOW(y2[8],nRyR)*C1_ryr - kaminus*y2[1] - kbplus*fastPOW(y2[8],mRyR)*y2[1] + kbminus*y2[2] - kcplus*y2[1] + kcminus*y2[3] ;
    dy2[2] = kbplus*fastPOW(y2[8],mRyR)*y2[1] - kbminus*y2[2] ;
    dy2[3] = kcplus*y2[1] - kcminus*y2[3] ;
    dy2[4] = -LOWkm_Ca*y2[4] + LOWkp_Ca*y2[7]*(LOWTRPNtot - y2[4]) ;
    dy2[5] = -HIGHkm_Ca*y2[5] + HIGHkp_Ca*y2[7]*(HIGHTRPNtot - y2[5]) ;
    dy2[6] = -0.04*y2[6] - 0.1*ICaL/ICaLmax*exp(-1*fastPOW((y2[0]-5),2)/648);
    dy2[7] = Bi*(Jleak + Jxfer - Jserca - Jtrpn) ;                       
    dy2[8] = Bss*( Jrel*VJSR/Vss - Jxfer*Vmyo/Vss - (ICaL + ICab - 2*INCX + IpCa + ICaT)*Acap*Cm/(2*Vss*F) ) ; 
    dy2[9] = BJSR*(Jtransfer - Jrel) ;
    dy2[10] = (Jserca - Jleak)*Vmyo/VNSR - Jtransfer*VJSR/VNSR ;
    dy2[11] = -(INa + INab + 3*INCX + 3*INaK)*Acap*Cm/(F*Vmyo) ;  
    dy2[12] = -(IKtof + IK1 + IKs + IKss + IKur + IKr - 2*INaK)*Acap*Cm/(F*Vmyo) ;
    dy2[13] = alpha_L*y2[16] - 4*beta_L*y2[13] + kPCB*y2[17] - gamma_L*y2[13] + 0.001*(alpha_L*y2[18] - kPCF*y2[13]) ;
    dy2[14] = 4*alpha_L*C1_L - beta_L*y2[14] + 2*beta_L*y2[15] - 3*alpha_L*y2[14] ;
    dy2[15] = 3*alpha_L*y2[14] - 2*beta_L*y2[15] + 3*beta_L*y2[16] - 2*alpha_L*y2[15] ;
    dy2[16] = 2*alpha_L*y2[15] - 3*beta_L*y2[16] + 4*beta_L*y2[13] - alpha_L*y2[16] + 0.01*(4*kPCB*beta_L*y2[17] - alpha_L*gamma_L*y2[16]) + 0.002*(4*beta_L*y2[18] - kPCF*y2[16]) + 4*beta_L*kPCB*y2[19] - gamma_L*kPCF*y2[16] ;
    dy2[17] = gamma_L*y2[13] - kPCB*y2[17] + 0.001*(alpha_L*y2[19] - kPCF*y2[17]) + 0.01*(alpha_L*gamma_L*y2[16] - 4*beta_L*kPCB*y2[17]) ;
    dy2[18] = 0.001*(- alpha_L*y2[18] + kPCF*y2[13]) + kPCB*y2[19] - gamma_L*y2[18] + 0.002*(-4*beta_L*y2[18] + kPCF*y2[16]) ;
    dy2[19] = 0.001*(-alpha_L*y2[19] + kPCF*y2[17]) + gamma_L*y2[18] - kPCB*y2[19] + gamma_L*kPCF*y2[16] - 4*beta_L*kPCB*y2[19] ;
    dy2[20] = (b_Tinf-y2[20])/taub_T ;
    dy2[21] = (g_Tinf-y2[21])/taug_T ;
    dy2[22] = an - (an+bn)*y2[22] ;
    dy2[23] = a0_Kr*C0_Kr - b0_Kr*y2[23] - kf_Kr*y2[23] + kb_Kr*y2[24] ;
    dy2[24] = kf_Kr*y2[23] - kb_Kr*y2[24] - a1_Kr*y2[24] + b1_Kr*y2[25] ;
    dy2[25] = a1_Kr*y2[24] - b1_Kr*y2[25] - ai_Kr*y2[25] + bi_Kr*y2[26] ;
    dy2[26] = ai_Kr*y2[25] - bi_Kr*y2[26] ;
    dy2[27] = aatof - (aatof+batof)*y2[27] ;
    dy2[28] = (itofinf-y2[28])/tauitof ;
    dy2[29] = (akinf-y2[29])/tauaur ;
    dy2[30] = (ikinf-y2[30])/tauiur ;
    dy2[31] = (akinf-y2[31])/tauakss ;

    // Euler
    y2[0]+= DT*dy2[0]; //V
    y2[1]+= DT*dy2[1]; //O1_ryr
    y2[2]+= DT*dy2[2]; //O2_ryr
    y2[3]+= DT*dy2[3]; //C2_ryr
    y2[4]+= DT*dy2[4]; //LOWCaTRPN
    y2[5]+= DT*dy2[5]; //HIGHCaTRPN
    y2[6]+= DT*dy2[6]; //PRyR
    y2[7]+= DT*dy2[7]; //Cai
    y2[8]+= DT*dy2[8]; //Cass
    y2[9]+= DT*dy2[9]; //CaJSR
    y2[10]+= DT*dy2[10]; //CaNSR
    y2[11]+= DT*dy2[11]; //Nai
    y2[12]+= DT*dy2[12]; //Ki
    y2[13]+= DT*dy2[13]; //used to be y2[16]- O_L
    y2[14]+= DT*dy2[14]; //C2_L
    y2[15]+= DT*dy2[15]; //C3_L
    y2[16]+= DT*dy2[16]; //C4_L
    y2[17]+= DT*dy2[17]; //I1_L
    y2[18]+= DT*dy2[18]; //I2_L
    y2[19]+= DT*dy2[19]; //I3_L
    y2[20]+= DT*dy2[20]; //b_T
    y2[21]+= DT*dy2[21]; //g_T
    y2[22]+= DT*dy2[22]; //n
    y2[23]+= DT*dy2[23]; //C1_Kr
    y2[24]+= DT*dy2[24]; //C2_Kr
    y2[25]+= DT*dy2[25]; //O_Kr	
    y2[26]+= DT*dy2[26]; //I_Kr
    y2[27]+= DT*dy2[27]; //atof
    y2[28]+= DT*dy2[28]; //itof
    y2[29]+= DT*dy2[29]; //aur
    y2[30]+= DT*dy2[30]; //iur
    y2[31]+= DT*dy2[31]; //akss
} // End calc_gates

/*** Sodium Gate Calculation Function ***/
void WangSobie::calc_sodium(double sodium_dt){
    // Sodium Derivates - Rush-Larsen
    sodium_dy2[0] = am - (am+bm)*sodium_y2[0] ;
    sodium_dy2[1] = ah - (ah+bh)*sodium_y2[1] ;
    sodium_dy2[2] = aj - (aj+bj)*sodium_y2[2] ;
    
    sodium_y2[0]+= sodium_dt*sodium_dy2[0];
    sodium_y2[1]+= sodium_dt*sodium_dy2[1];
    sodium_y2[2]+= sodium_dt*sodium_dy2[2];
} // End calc_sodium

/*** Virtual functions used by default_model class ***/

// Voltage Clamp Function
double WangSobie::vClamp(double voltage){
    // Clamp model voltage
    y2[0] = voltage;

    // Run model solver
    solve(); // voltage free to change during this time period

    // Return current
    return Iion;
}

// Current Clamp Function
double WangSobie::iClamp(double current){
    // Inject current into model
    I_Inject = current;

    // Run model solver
    solve();

    // Return voltage
    return y2[0];
}

// Current Return Function
double WangSobie::current(int current){

    switch(current){
        
    // Currents
    case 0: return Iion; break;
    case 1: return INa; break;
    case 2: return INab; break;
    case 3: return ICaL; break;
    case 4: return ICaT; break;
    case 5: return ICab; break;
    case 6: return IpCa; break;
    case 7: return INCX; break;
    case 8: return INaK; break;
    case 9: return IKtof; break;
    case 10: return IKur; break;
    case 11: return IKr; break;
    case 12: return IKs; break;
    case 13: return IKss; break;
    case 14: return IK1; break;
    case 15: return ICaCl; break;
        
    default: return -1; break;
    } // End switch(current)
}

// Concentration Return Function
double WangSobie::concentration(int concentration){

    switch(concentration){

    // Nothing added yet
        
    default: return -1; break;
    } // End switch(concentration)
}

// Model Reset Function
void WangSobie::reset(){ // Reset to initial conditions
    
    //Initial conditions
	y2[0]= -80.63; //V
    y2[1]= 8.5734e-4; //O1_ryr
    y2[2]= 2.3420e-8; //O2_ryr
    y2[3]= 0.0768; //C2_ryr
    y2[4]= 8.8918; //LOWCaTRPN
    y2[5]= 65.9936; //HIGHCaTRPN
    y2[6]= 1.9638e-13; //PRyR
    y2[7]= 0.2040; //Cai
    y2[8]= 0.1867; //Cass
    y2[9]= 704.5995; //CaJSR
    y2[10]= 702.1971; //CaNSR
    y2[11]= 2.1748e4; //Nai
    y2[12]= 1.3644e5; //Ki
    y2[13]= 1.2036e-14; //used to be y2[16]- O_L
    y2[14]= 1.7049e-4; //C2_L
    y2[15]= 1.0895e-8; //C3_L
    y2[16]= 4.2195e-12; //C4_L
    y2[17]= 9.4119e-10; //I1_L
    y2[18]= 3.1179e-11; //I2_L
    y2[19]= 6.8932e-9; //I3_L
    y2[20]= 0.0047; //b_T
    y2[21]= 0.9017; //g_T
    y2[22]= 0.0021; //n
    y2[23]= 0.0011; //C1_Kr
    y2[24]= 7.8269e-4; //C2_Kr
    y2[25]= 0.0011; //O_Kr	
    y2[26]= 2.3215e-4; //I_Kr
    y2[27]= 0.0032; //atof
    y2[28]= 0.7527; //itof
    y2[29]= 5.2609e-4; //aur
    y2[30]= 0.9902; //iur
    y2[31]= 0.8441; //akss

    cout << "\n**** WangSobie model reset to initial conditions ****\n";
}

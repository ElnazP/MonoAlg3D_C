#include "model_common.h"
#include <assert.h>
#include <stdlib.h>


void RHS_cpu(Real *sv, Real *rDY_, Real stim_current, Real stim_start, Real stim_dur, Real time, void *extra_data);


struct cell_model_data *new_model_data() {

    struct cell_model_data* result = (struct cell_model_data*)malloc(sizeof(struct cell_model_data));

}

void init_cell_model_data(struct cell_model_data* cell_model) {

    assert(cell_model);

    cell_model->initial_v = -82.4202;
    cell_model->number_of_ode_equations = 41;

}

void set_model_initial_conditions(Real *sv) {

        sv[0] = -82.4202f;	 // V millivolt
        sv[1] = 0.115001f;	 // Cai msvromolar
        sv[2] = 0.115001f;	 // Cass msvromolar
        sv[3] = 1299.5f;	 // CaJSR msvromolar
        sv[4] = 1299.5f;	 // CaNSR msvromolar
        sv[5] = 0.0f;	 // P_RyR dimensionless
        sv[6] = 11.2684f;	 // LTRPN_Ca msvromolar
        sv[7] = 125.29f;	 // HTRPN_Ca msvromolar
        sv[8] = 0.149102e-4f;	 // P_O1 dimensionless
        sv[9] = 0.951726e-10f;	 // P_O2 dimensionless
        sv[10] = 0.16774e-3f;	 // P_C2 dimensionless
        sv[11] = 0.930308e-18f;	 // O dimensionless
        sv[12] = 0.124216e-3f;	 // C2 dimensionless
        sv[13] = 0.578679e-8f;	 // C3 dimensionless
        sv[14] = 0.119816e-12f;	 // C4 dimensionless
        sv[15] = 0.497923e-18f;	 // I1 dimensionless
        sv[16] = 0.345847e-13f;	 // I2 dimensionless
        sv[17] = 0.185106e-13f;	 // I3 dimensionless
        sv[18] = 14237.1f;	 // Nai msvromolar
        sv[19] = 0.020752f;	 // C_Na2 dimensionless
        sv[20] = 0.279132e-3f;	 // C_Na1 dimensionless
        sv[21] = 0.713483e-6f;	 // O_Na dimensionless
        sv[22] = 0.153176e-3f;	 // IF_Na dimensionless
        sv[23] = 0.673345e-6f;	 // I1_Na dimensionless
        sv[24] = 0.155787e-8f;	 // I2_Na dimensionless
        sv[25] = 0.0113879f;	 // sv_Na2 dimensionless
        sv[26] = 0.34278f;	 // sv_Na3 dimensionless
        sv[27] = 143720.0f;	 // Ki msvromolar
        sv[28] = 0.265563e-2f;	 // ato_f dimensionless
        sv[29] = 0.999977f;	 // ito_f dimensionless
        sv[30] = 0.417069e-3f;	 // ato_s dimensionless
        sv[31] = 0.998543f;	 // ito_s dimensionless
        sv[32] = 0.262753e-3f;	 // nKs dimensionless
        sv[33] = 0.417069e-3f;	 // aur dimensionless
        sv[34] = 0.998543f;	 // iur dimensionless
        sv[35] = 0.417069e-3f;	 // aKss dimensionless
        sv[36] = 1.0f;	 // iKss dimensionless
        sv[37] = 0.641229e-3f;	 // C_K2 dimensionless
        sv[38] = 0.992513e-3f;	 // C_K1 dimensionless
        sv[39] = 0.175298e-3f;	 // O_K dimensionless
        sv[40] = 0.319129e-4f;	 // I_K dimensionless
}


void solve_model_ode_cpu(Real dt, Real *sv, Real stim_current, Real stim_start, Real stim_dur,
                         Real time, int neq, void *extra_data)  {

    assert(sv);

    Real rY[neq], rDY[neq];

    for(int i = 0; i < neq; i++)
        rY[i] = sv[i];

    RHS_cpu(rY, rDY, stim_current, stim_start, stim_dur, time, extra_data);

    for(int i = 0; i < neq; i++)
        sv[i] = dt*rDY[i] + rY[i];
}


void RHS_cpu(Real *sv, Real *rDY_, Real stim_current, Real stim_start, Real stim_dur, Real time, void *extra_data) {

    // State variables
    const Real V_old_ = sv[0];	 // initial value = -82.4202 millivolt
    const Real Cai_old_ = sv[1];	 // initial value = 0.115001 micromolar
    const Real Cass_old_ = sv[2];	 // initial value = 0.115001 micromolar
    const Real CaJSR_old_ = sv[3];	 // initial value = 1299.5 micromolar
    const Real CaNSR_old_ = sv[4];	 // initial value = 1299.5 micromolar
    const Real P_RyR_old_ = sv[5];	 // initial value = 0 dimensionless
    const Real LTRPN_Ca_old_ = sv[6];	 // initial value = 11.2684 micromolar
    const Real HTRPN_Ca_old_ = sv[7];	 // initial value = 125.29 micromolar
    const Real P_O1_old_ = sv[8];	 // initial value = 0.149102e-4 dimensionless
    const Real P_O2_old_ = sv[9];	 // initial value = 0.951726e-10 dimensionless
    const Real P_C2_old_ = sv[10];	 // initial value = 0.16774e-3 dimensionless
    const Real O_old_ = sv[11];	 // initial value = 0.930308e-18 dimensionless
    const Real C2_old_ = sv[12];	 // initial value = 0.124216e-3 dimensionless
    const Real C3_old_ = sv[13];	 // initial value = 0.578679e-8 dimensionless
    const Real C4_old_ = sv[14];	 // initial value = 0.119816e-12 dimensionless
    const Real I1_old_ = sv[15];	 // initial value = 0.497923e-18 dimensionless
    const Real I2_old_ = sv[16];	 // initial value = 0.345847e-13 dimensionless
    const Real I3_old_ = sv[17];	 // initial value = 0.185106e-13 dimensionless
    const Real Nai_old_ = sv[18];	 // initial value = 14237.1 micromolar
    const Real C_Na2_old_ = sv[19];	 // initial value = 0.020752 dimensionless
    const Real C_Na1_old_ = sv[20];	 // initial value = 0.279132e-3 dimensionless
    const Real O_Na_old_ = sv[21];	 // initial value = 0.713483e-6 dimensionless
    const Real IF_Na_old_ = sv[22];	 // initial value = 0.153176e-3 dimensionless
    const Real I1_Na_old_ = sv[23];	 // initial value = 0.673345e-6 dimensionless
    const Real I2_Na_old_ = sv[24];	 // initial value = 0.155787e-8 dimensionless
    const Real IC_Na2_old_ = sv[25];	 // initial value = 0.0113879 dimensionless
    const Real IC_Na3_old_ = sv[26];	 // initial value = 0.34278 dimensionless
    const Real Ki_old_ = sv[27];	 // initial value = 143720 micromolar
    const Real ato_f_old_ = sv[28];	 // initial value = 0.265563e-2 dimensionless
    const Real ito_f_old_ = sv[29];	 // initial value = 0.999977 dimensionless
    const Real ato_s_old_ = sv[30];	 // initial value = 0.417069e-3 dimensionless
    const Real ito_s_old_ = sv[31];	 // initial value = 0.998543 dimensionless
    const Real nKs_old_ = sv[32];	 // initial value = 0.262753e-3 dimensionless
    const Real aur_old_ = sv[33];	 // initial value = 0.417069e-3 dimensionless
    const Real iur_old_ = sv[34];	 // initial value = 0.998543 dimensionless
    const Real aKss_old_ = sv[35];	 // initial value = 0.417069e-3 dimensionless
    const Real iKss_old_ = sv[36];	 // initial value = 1 dimensionless
    const Real C_K2_old_ = sv[37];	 // initial value = 0.641229e-3 dimensionless
    const Real C_K1_old_ = sv[38];	 // initial value = 0.992513e-3 dimensionless
    const Real O_K_old_ = sv[39];	 // initial value = 0.175298e-3 dimensionless
    const Real I_K_old_ = sv[40];	 // initial value = 0.319129e-4 dimensionless


    // Parameters
    const Real Acap = 1.534e-4f;	 // cm2
    const Real Cm = 1.0f;	 // microF_per_cm2
    const Real Vmyo = 25.84e-6f;	 // microlitre
    const Real F = 96.5f;	 // coulomb_per_millimole
    const Real VJSR = 0.12e-6f;	 // microlitre
    const Real Vss = 1.485e-9f;	 // microlitre
    const Real VNSR = 2.098e-6f;	 // microlitre
    const Real CMDN_tot = 50.0f;	 // micromolar
    const Real Km_CMDN = 0.238f;	 // micromolar
    const Real CSQN_tot = 15000.0f;	 // micromolar
    const Real Km_CSQN = 800.0f;	 // micromolar
    const Real v1 = 4.5f;	 // per_millisecond
    const Real tau_tr = 20.0f;	 // millisecond
    const Real tau_xfer = 8.0f;	 // millisecond
    const Real v2 = 1.74e-5f;	 // per_millisecond
    const Real v3 = 0.45f;	 // micromolar_per_millisecond
    const Real Km_up = 0.5f;	 // micromolar
    const Real k_plus_htrpn = 0.00237f;	 // per_micromolar_millisecond
    const Real HTRPN_tot = 140.0f;	 // micromolar
    const Real k_plus_ltrpn = 0.0327f;	 // per_micromolar_millisecond
    const Real LTRPN_tot = 70.0f;	 // micromolar
    const Real k_minus_htrpn = 3.2e-5f;	 // per_millisecond
    const Real k_minus_ltrpn = 0.0196f;	 // per_millisecond
    const Real i_CaL_max = 7.0f;	 // picoA_per_picoF
    const Real k_plus_a = 0.006075f;	 // micromolar4_per_millisecond
    const Real n = 4.0f;	 // dimensionless
    const Real k_minus_b = 0.965f;	 // per_millisecond
    const Real k_minus_c = 0.0008f;	 // per_millisecond
    const Real k_minus_a = 0.07125f;	 // per_millisecond
    const Real k_plus_b = 0.00405f;	 // micromolar3_per_millisecond
    const Real m = 3.0f;	 // dimensionless
    const Real k_plus_c = 0.009f;	 // per_millisecond
    const Real g_CaL = 0.1729f;	 // milliS_per_microF
    const Real E_CaL = 63.0f;	 // millivolt
    const Real Kpcb = 0.0005f;	 // per_millisecond
    const Real Kpc_max = 0.23324f;	 // per_millisecond
    const Real Kpc_half = 20.0f;	 // micromolar
    const Real i_pCa_max = 1.0f;	 // picoA_per_picoF
    const Real Km_pCa = 0.5f;	 // micromolar
    const Real k_NaCa = 292.8f;	 // picoA_per_picoF
    const Real K_mNa = 87500.0f;	 // micromolar
    const Real Nao = 140000.0f;	 // micromolar
    const Real K_mCa = 1380.0f;	 // micromolar
    const Real Cao = 1800.0f;	 // micromolar
    const Real k_sat = 0.1f;	 // dimensionless
    const Real eta = 0.35f;	 // dimensionless
    const Real R = 8.314f;	 // joule_per_mole_kelvin
    const Real T = 298.0f;	 // kelvin
    const Real g_Cab = 0.000367f;	 // milliS_per_microF
    const Real g_Na = 13.0f;	 // milliS_per_microF
    const Real Ko = 5400.0f;	 // micromolar
    const Real g_Nab = 0.0026f;	 // milliS_per_microF
    const Real g_Kto_f = 0.4067f;	 // milliS_per_microF
    const Real g_Kto_s = 0.0f;	 // milliS_per_microF
    const Real g_Ks = 0.00575f;	 // milliS_per_microF
    const Real g_Kur = 0.16f;	 // milliS_per_microF
    const Real g_Kss = 0.05f;	 // milliS_per_microF
    const Real g_Kr = 0.078f;	 // milliS_per_microF
    const Real kf = 0.023761f;	 // per_millisecond
    const Real kb = 0.036778f;	 // per_millisecond
    const Real i_NaK_max = 0.88f;	 // picoA_per_picoF
    const Real Km_Nai = 21000.0f;	 // micromolar
    const Real Km_Ko = 1500.0f;	 // micromolar
    const Real g_ClCa = 10.0f;	 // milliS_per_microF
    const Real Km_Cl = 10.0f;	 // micromolar
    const Real E_Cl = -40.0f;	 // millivolt

    // Algebraic Equations
    Real calc_i_stim = ((time>=stim_start)&&(time<=stim_start+stim_dur)) ? stim_current: 0.0f;	//0
    
    Real calc_Bi = powf((1.0f+((CMDN_tot*Km_CMDN)/powf((Km_CMDN+Cai_old_),2.0f))),(-1.0f));	//6
    Real calc_Bss = powf((1.0f+((CMDN_tot*Km_CMDN)/powf((Km_CMDN+Cass_old_),2.0f))),(-1.0f));	//7
    Real calc_BJSR = powf((1.0f+((CSQN_tot*Km_CSQN)/powf((Km_CSQN+CaJSR_old_),2.0f))),(-1.0f));	//8
    Real calc_J_rel = (v1*(P_O1_old_+P_O2_old_)*(CaJSR_old_-Cass_old_)*P_RyR_old_);	//9
    Real calc_J_tr = ((CaNSR_old_-CaJSR_old_)/tau_tr);	//10
    Real calc_J_xfer = ((Cass_old_-Cai_old_)/tau_xfer);	//11
    Real calc_J_leak = (v2*(CaNSR_old_-Cai_old_));	//12
    Real calc_J_up = ((v3*powf(Cai_old_,2.0f))/(powf(Km_up,2.0f)+powf(Cai_old_,2.0f)));	//13
    Real calc_J_trpn = (((k_plus_htrpn*Cai_old_*(HTRPN_tot-HTRPN_Ca_old_))+(k_plus_ltrpn*Cai_old_*(LTRPN_tot-LTRPN_Ca_old_)))-((k_minus_htrpn*HTRPN_Ca_old_)+(k_minus_ltrpn*LTRPN_Ca_old_)));	//14
    Real calc_P_C1 = (1.0f-(P_C2_old_+P_O1_old_+P_O2_old_));	//19
    Real calc_i_CaL = (g_CaL*O_old_*(V_old_-E_CaL));	//22
    Real calc_C1 = (1.0f-(O_old_+C2_old_+C3_old_+C4_old_+I1_old_+I2_old_+I3_old_));	//24
    Real calc_alpha = ((0.4f*expf(((V_old_+12.0f)/10.0f))*((1.0f+(0.7f*expf(((-powf((V_old_+40.0f),2.0f))/10.0f))))-(0.75f*expf(((-powf((V_old_+20.0f),2.0f))/400.0f)))))/(1.0f+(0.12f*expf(((V_old_+12.0f)/10.0f)))));	//31
    Real calc_beta = (0.05f*expf(((-(V_old_+12.0f))/13.0f)));	//32
    Real calc_gamma = ((Kpc_max*Cass_old_)/(Kpc_half+Cass_old_));	//33
    Real calc_Kpcf = (13.0f*(1.0f-expf(((-powf((V_old_+14.5f),2.0f))/100.0f))));	//34
    Real calc_i_pCa = ((i_pCa_max*powf(Cai_old_,2.0f))/(powf(Km_pCa,2.0f)+powf(Cai_old_,2.0f)));	//35
    Real calc_i_NaCa = (((((((k_NaCa*1.0f)/(powf(K_mNa,3.0)+powf(Nao,3.0)))*1.0f)/(K_mCa+Cao))*1.0f)/(1.0f+(k_sat*expf((((eta-1.0f)*V_old_*F)/(R*T))))))*((expf(((eta*V_old_*F)/(R*T)))*powf(Nai_old_,3.0)*Cao)-(expf((((eta-1.0f)*V_old_*F)/(R*T)))*powf(Nao,3.0)*Cai_old_)));	//36
    Real calc_E_CaN = (((R*T)/(2.0f*F))*logf((Cao/Cai_old_)));	//38
    Real calc_E_Na = (((R*T)/F)*logf((((0.9f*Nao)+(0.1f*Ko))/((0.9f*Nai_old_)+(0.1f*Ki_old_)))));	//41
    Real calc_C_Na3 = (1.0f-(O_Na_old_+C_Na1_old_+C_Na2_old_+IF_Na_old_+I1_Na_old_+I2_Na_old_+IC_Na2_old_+IC_Na3_old_));	//42
    Real calc_alpha_Na11 = (3.802f/((0.1027f*expf(((-(V_old_+2.5f))/17.0f)))+(0.2f*expf(((-(V_old_+2.5f))/150.0f)))));	//51
    Real calc_alpha_Na12 = (3.802f/((0.1027f*expf(((-(V_old_+2.5f))/15.0f)))+(0.23f*expf(((-(V_old_+2.5f))/150.0f)))));	//52
    Real calc_alpha_Na13 = (3.802f/((0.1027f*expf(((-(V_old_+2.5f))/12.0f)))+(0.25f*expf(((-(V_old_+2.5f))/150.0f)))));	//53
    Real calc_beta_Na11 = (0.1917f*expf(((-(V_old_+2.5f))/20.3f)));	//54
    Real calc_beta_Na12 = (0.2f*expf(((-(V_old_-2.5f))/20.3f)));	//55
    Real calc_beta_Na13 = (0.22f*expf(((-(V_old_-7.5f))/20.3f)));	//56
    Real calc_alpha_Na3 = (7e-7f*expf(((-(V_old_+7.0f))/7.7f)));	//57
    Real calc_beta_Na3 = (0.00854f+(0.00002f*V_old_));	//58
    Real calc_alpha_Na2 = (1.0f/((0.188495f*expf(((-(V_old_+7.0f))/16.6f)))+0.393956f));	//59
    Real calc_E_K = (((R*T)/F)*logf((Ko/Ki_old_)));	//68
    Real calc_alpha_a = (0.18064f*expf((0.03577f*(V_old_+ 30.0f))));	//71
    Real calc_beta_a = (0.3956f*expf(((-0.06237f)*(V_old_+ 30.0f))));	//72
    Real calc_alpha_i = ((0.000152f*expf(((-(V_old_+13.5f))/7.0f)))/((0.067083f*expf(((-(V_old_+33.5f))/7.0f)))+1.0f));	//73
    Real calc_beta_i = ((0.00095f*expf(((V_old_+33.5f)/7.0f)))/((0.051335f*expf(((V_old_+33.5f)/7.0f)))+1.0f));	//74
    Real calc_ass = (1.0f/(1.0f+expf(((-(V_old_+22.5f))/7.7f))));	//78
    Real calc_iss = (1.0f/(1.0f+expf(((V_old_+45.2f)/5.7f))));	//79
    Real calc_tau_ta_s = ((0.493f*expf(((-0.0629f)*V_old_)))+2.058f);	//80
    Real calc_tau_ti_s = (270.0f+(1050.0f/(1.0f+expf(((V_old_+45.2f)/5.7f)))));	//81
    Real calc_alpha_n = (V_old_ != -26.5f)?((0.00000481333f*(V_old_+26.5f))/(1.0f-expf(((-0.128f)*(V_old_+26.5f))))): 0.000037604f;   //85
    Real calc_beta_n = (0.0000953333f*expf(((-0.038f)*(V_old_+26.5f))));	//86
    Real calc_tau_aur = ((0.493f*expf(((-0.0629f)*V_old_)))+2.058f);	//90
    Real calc_tau_iur = (1200.0f-(170.0f/(1.0f+expf(((V_old_+45.2f)/5.7f)))));	//91
    Real calc_tau_Kss = ((39.3f*expf(((-0.0862f)*V_old_)))+13.17f);	//95
    Real calc_i_Kr = (g_Kr*O_K_old_*(V_old_-(((R*T)/F)*logf((((0.98f*Ko)+(0.02f*Nao))/((0.98f*Ki_old_)+(0.02f*Nai_old_)))))));	//96
    Real calc_C_K0 = (1.0f-(C_K1_old_+C_K2_old_+O_K_old_+I_K_old_));	//97
    Real calc_alpha_a0 = (0.022348f*expf((0.01176f*V_old_)));	//102
    Real calc_beta_a0 = (0.047002f*expf(((-0.0631f)*V_old_)));	//103
    Real calc_alpha_a1 = (0.013733f*expf((0.038198f*V_old_)));	//104
    Real calc_beta_a1 = (0.0000689f*expf(((-0.04178f)*V_old_)));	//105
    Real calc_alpha_i_duplicated_rapid_delayed_rectifier_potassium_current = (0.090821f*expf((0.023391f*(V_old_+5.0f))));	//106
    Real calc_beta_i_duplicated_rapid_delayed_rectifier_potassium_current = (0.006497f*expf(((-0.03268f)*(V_old_+5.0f))));	//107
    Real calc_sigma = ((1.0f/7.0f)*(expf((Nao/67300.0f))-1.0f));	//110
    Real calc_O_ClCa = (0.2f/(1.0f+expf(((-(V_old_-46.7f))/7.8f))));	//112
    Real calc_beta_Na2 = ((calc_alpha_Na13*calc_alpha_Na2*calc_alpha_Na3)/(calc_beta_Na13*calc_beta_Na3));	//60
    Real calc_alpha_Na4 = (calc_alpha_Na2/1000.0f);	//61
    Real calc_beta_Na4 = calc_alpha_Na3;	//62
    Real calc_alpha_Na5 = (calc_alpha_Na2/95000.0f);	//63
    Real calc_beta_Na5 = (calc_alpha_Na3/50.0f);	//64
    Real calc_i_Nab = (g_Nab*(V_old_-calc_E_Na));	//65
    Real calc_i_Kto_s = (g_Kto_s*ato_s_old_*ito_s_old_*(V_old_-calc_E_K));	//75
    Real calc_i_K1 = ((((0.2938f*Ko)/(Ko+210.0f))*(V_old_-calc_E_K))/(1.0f+expf((0.0896f*(V_old_-calc_E_K)))));	//82
    Real calc_i_Ks = (g_Ks*powf(nKs_old_,2.0f)*(V_old_-calc_E_K));	//83
    Real calc_i_Kur = (g_Kur*aur_old_*iur_old_*(V_old_-calc_E_K));	//87
    Real calc_i_Kss = (g_Kss*aKss_old_*iKss_old_*(V_old_-calc_E_K));	//92
    Real calc_i_Cab = (g_Cab*(V_old_-calc_E_CaN));	//37
    Real calc_i_Na = (g_Na*O_Na_old_*(V_old_-calc_E_Na));	//40
    Real calc_i_Kto_f = (g_Kto_f*powf(ato_f_old_,3.0)*ito_f_old_*(V_old_-calc_E_K));	//67
    Real calc_f_NaK = (1.0f/(1.0f+(0.1245f*expf((((-0.1f)*V_old_*F)/(R*T))))+(0.0365f*calc_sigma*expf((((-V_old_)*F)/(R*T))))));	//109
    Real calc_i_ClCa = (((g_ClCa*calc_O_ClCa*Cai_old_)/(Cai_old_+Km_Cl))*(V_old_-E_Cl));	//111
    Real calc_i_NaK = ((((i_NaK_max*calc_f_NaK*1.0f)/(1.0f+powf((Km_Nai/Nai_old_),1.5)))*Ko)/(Ko+Km_Ko));	//108

    // Differential Equations
    Real d_dt_V = (-(calc_i_CaL+calc_i_pCa+calc_i_NaCa+calc_i_Cab+calc_i_Na+calc_i_Nab+calc_i_NaK+calc_i_Kto_f+calc_i_Kto_s+calc_i_K1+calc_i_Ks+calc_i_Kur+calc_i_Kss+calc_i_Kr+calc_i_ClCa+calc_i_stim));	// 1
    Real d_dt_Cai = (calc_Bi*((calc_J_leak+calc_J_xfer)-(calc_J_up+calc_J_trpn+((((calc_i_Cab+calc_i_pCa)-(2.0f*calc_i_NaCa))*Acap*Cm)/(2.0f*Vmyo*F)))));	// 2
    Real d_dt_Cass = (calc_Bss*(((calc_J_rel*VJSR)/Vss)-(((calc_J_xfer*Vmyo)/Vss)+((calc_i_CaL*Acap*Cm)/(2.0f*Vss*F)))));	// 3
    Real d_dt_CaJSR = (calc_BJSR*(calc_J_tr-calc_J_rel));	// 4
    Real d_dt_CaNSR = ((((calc_J_up-calc_J_leak)*Vmyo)/VNSR)-((calc_J_tr*VJSR)/VNSR));	// 5
    Real d_dt_P_RyR = (((-0.04f)*P_RyR_old_)-(((0.1f*calc_i_CaL)/i_CaL_max)*expf(((-powf((V_old_-5.0f),2.0f))/648.0f))));	// 15
    Real d_dt_LTRPN_Ca = ((k_plus_ltrpn*Cai_old_*(LTRPN_tot-LTRPN_Ca_old_))-(k_minus_ltrpn*LTRPN_Ca_old_));	// 16
    Real d_dt_HTRPN_Ca = ((k_plus_htrpn*Cai_old_*(HTRPN_tot-HTRPN_Ca_old_))-(k_minus_htrpn*HTRPN_Ca_old_));	// 17
    Real d_dt_P_O1 = (((k_plus_a*powf(Cass_old_,n)*calc_P_C1)+(k_minus_b*P_O2_old_)+(k_minus_c*P_C2_old_))-((k_minus_a*P_O1_old_)+(k_plus_b*powf(Cass_old_,m)*P_O1_old_)+(k_plus_c*P_O1_old_)));	// 18
    Real d_dt_P_O2 = ((k_plus_b*powf(Cass_old_,m)*P_O1_old_)-(k_minus_b*P_O2_old_));	// 20
    Real d_dt_P_C2 = ((k_plus_c*P_O1_old_)-(k_minus_c*P_C2_old_));	// 21
    Real d_dt_O = (((calc_alpha*C4_old_)+(Kpcb*I1_old_)+(0.001f*((calc_alpha*I2_old_)-(calc_Kpcf*O_old_))))-((4.0f*calc_beta*O_old_)+(calc_gamma*O_old_)));	// 23
    Real d_dt_C2 = (((4.0f*calc_alpha*calc_C1)+(2.0f*calc_beta*C3_old_))-((calc_beta*C2_old_)+(3.0f*calc_alpha*C2_old_)));	// 25
    Real d_dt_C3 = (((3.0f*calc_alpha*C2_old_)+(3.0f*calc_beta*C4_old_))-((2.0f*calc_beta*C3_old_)+(2.0f*calc_alpha*C3_old_)));	// 26
    Real d_dt_C4 = (((2.0f*calc_alpha*C3_old_)+(4.0f*calc_beta*O_old_)+(0.01f*((4.0f*Kpcb*calc_beta*I1_old_)-(calc_alpha*calc_gamma*C4_old_)))+(0.002f*((4.0f*calc_beta*I2_old_)-(calc_Kpcf*C4_old_)))+(4.0f*calc_beta*Kpcb*I3_old_))-((3.0f*calc_beta*C4_old_)+(calc_alpha*C4_old_)+(1.0f*calc_gamma*calc_Kpcf*C4_old_)));	// 27
    Real d_dt_I1 = (((calc_gamma*O_old_)+(0.001f*((calc_alpha*I3_old_)-(calc_Kpcf*I1_old_)))+(0.01f*((calc_alpha*calc_gamma*C4_old_)-(4.0f*calc_beta*Kpcb*I1_old_))))-(Kpcb*I1_old_));	// 28
    Real d_dt_I2 = (((0.001f*((calc_Kpcf*O_old_)-(calc_alpha*I2_old_)))+(Kpcb*I3_old_)+(0.002f*((calc_Kpcf*C4_old_)-(4.0f*calc_beta*I2_old_))))-(calc_gamma*I2_old_));	// 29
    Real d_dt_I3 = (((0.001f*((calc_Kpcf*I1_old_)-(calc_alpha*I3_old_)))+(calc_gamma*I2_old_)+(1.0f*calc_gamma*calc_Kpcf*C4_old_))-((4.0f*calc_beta*Kpcb*I3_old_)+(Kpcb*I3_old_)));	// 30
    Real d_dt_Nai = (((-(calc_i_Na+calc_i_Nab+(3.0f*calc_i_NaK)+(3.0f*calc_i_NaCa)))*Acap*Cm)/(Vmyo*F));	// 39
    Real d_dt_C_Na2 = (((calc_alpha_Na11*calc_C_Na3)+(calc_beta_Na12*C_Na1_old_)+(calc_alpha_Na3*IC_Na2_old_))-((calc_beta_Na11*C_Na2_old_)+(calc_alpha_Na12*C_Na2_old_)+(calc_beta_Na3*C_Na2_old_)));	// 43
    Real d_dt_C_Na1 = (((calc_alpha_Na12*C_Na2_old_)+(calc_beta_Na13*O_Na_old_)+(calc_alpha_Na3*IF_Na_old_))-((calc_beta_Na12*C_Na1_old_)+(calc_alpha_Na13*C_Na1_old_)+(calc_beta_Na3*C_Na1_old_)));	// 44
    Real d_dt_O_Na = (((calc_alpha_Na13*C_Na1_old_)+(calc_beta_Na2*IF_Na_old_))-((calc_beta_Na13*O_Na_old_)+(calc_alpha_Na2*O_Na_old_)));	// 45
    Real d_dt_IF_Na = (((calc_alpha_Na2*O_Na_old_)+(calc_beta_Na3*C_Na1_old_)+(calc_beta_Na4*I1_Na_old_)+(calc_alpha_Na12*IC_Na2_old_))-((calc_beta_Na2*IF_Na_old_)+(calc_alpha_Na3*IF_Na_old_)+(calc_alpha_Na4*IF_Na_old_)+(calc_beta_Na12*IF_Na_old_)));	// 46
    Real d_dt_I1_Na = (((calc_alpha_Na4*IF_Na_old_)+(calc_beta_Na5*I2_Na_old_))-((calc_beta_Na4*I1_Na_old_)+(calc_alpha_Na5*I1_Na_old_)));	// 47
    Real d_dt_I2_Na = ((calc_alpha_Na5*I1_Na_old_)-(calc_beta_Na5*I2_Na_old_));	// 48
    Real d_dt_IC_Na2 = (((calc_alpha_Na11*IC_Na3_old_)+(calc_beta_Na12*IF_Na_old_)+(calc_beta_Na3*C_Na2_old_))-((calc_beta_Na11*IC_Na2_old_)+(calc_alpha_Na12*IC_Na2_old_)+(calc_alpha_Na3*IC_Na2_old_)));	// 49
    Real d_dt_IC_Na3 = (((calc_beta_Na11*IC_Na2_old_)+(calc_beta_Na3*calc_C_Na3))-((calc_alpha_Na11*IC_Na3_old_)+(calc_alpha_Na3*IC_Na3_old_)));	// 50
    Real d_dt_Ki = (((-((calc_i_Kto_f+calc_i_Kto_s+calc_i_K1+calc_i_Ks+calc_i_Kss+calc_i_Kur+calc_i_Kr)-(2.0f*calc_i_NaK)))*Acap*Cm)/(Vmyo*F));	// 66
    Real d_dt_ato_f = ((calc_alpha_a*(1.0f-ato_f_old_))-(calc_beta_a*ato_f_old_));	// 69
    Real d_dt_ito_f = ((calc_alpha_i*(1.0f-ito_f_old_))-(calc_beta_i*ito_f_old_));	// 70
    Real d_dt_ato_s = ((calc_ass-ato_s_old_)/calc_tau_ta_s);	// 76
    Real d_dt_ito_s = ((calc_iss-ito_s_old_)/calc_tau_ti_s);	// 77
    Real d_dt_nKs = ((calc_alpha_n*(1.0f-nKs_old_))-(calc_beta_n*nKs_old_));	// 84
    Real d_dt_aur = ((calc_ass-aur_old_)/calc_tau_aur);	// 88
    Real d_dt_iur = ((calc_iss-iur_old_)/calc_tau_iur);	// 89
    Real d_dt_aKss = ((calc_ass-aKss_old_)/calc_tau_Kss);	// 93
    Real d_dt_iKss = 0.0f;	// 94
    Real d_dt_C_K2 = (((kf*C_K1_old_)+(calc_beta_a1*O_K_old_))-((kb*C_K2_old_)+(calc_alpha_a1*C_K2_old_)));	// 98
    Real d_dt_C_K1 = (((calc_alpha_a0*calc_C_K0)+(kb*C_K2_old_))-((calc_beta_a0*C_K1_old_)+(kf*C_K1_old_)));	// 99
    Real d_dt_O_K = (((calc_alpha_a1*C_K2_old_)+(calc_beta_i_duplicated_rapid_delayed_rectifier_potassium_current*I_K_old_))-((calc_beta_a1*O_K_old_)+(calc_alpha_i_duplicated_rapid_delayed_rectifier_potassium_current*O_K_old_)));	// 100
    Real d_dt_I_K = ((calc_alpha_i_duplicated_rapid_delayed_rectifier_potassium_current*O_K_old_)-(calc_beta_i_duplicated_rapid_delayed_rectifier_potassium_current*I_K_old_));	// 101

    rDY_[0] = d_dt_V;
    rDY_[1] = d_dt_Cai;
    rDY_[2] = d_dt_Cass;
    rDY_[3] = d_dt_CaJSR;
    rDY_[4] = d_dt_CaNSR;
    rDY_[5] = d_dt_P_RyR;
    rDY_[6] = d_dt_LTRPN_Ca;
    rDY_[7] = d_dt_HTRPN_Ca;
    rDY_[8] = d_dt_P_O1;
    rDY_[9] = d_dt_P_O2;
    rDY_[10] = d_dt_P_C2;
    rDY_[11] = d_dt_O;
    rDY_[12] = d_dt_C2;
    rDY_[13] = d_dt_C3;
    rDY_[14] = d_dt_C4;
    rDY_[15] = d_dt_I1;
    rDY_[16] = d_dt_I2;
    rDY_[17] = d_dt_I3;
    rDY_[18] = d_dt_Nai;
    rDY_[19] = d_dt_C_Na2;
    rDY_[20] = d_dt_C_Na1;
    rDY_[21] = d_dt_O_Na;
    rDY_[22] = d_dt_IF_Na;
    rDY_[23] = d_dt_I1_Na;
    rDY_[24] = d_dt_I2_Na;
    rDY_[25] = d_dt_IC_Na2;
    rDY_[26] = d_dt_IC_Na3;
    rDY_[27] = d_dt_Ki;
    rDY_[28] = d_dt_ato_f;
    rDY_[29] = d_dt_ito_f;
    rDY_[30] = d_dt_ato_s;
    rDY_[31] = d_dt_ito_s;
    rDY_[32] = d_dt_nKs;
    rDY_[33] = d_dt_aur;
    rDY_[34] = d_dt_iur;
    rDY_[35] = d_dt_aKss;
    rDY_[36] = d_dt_iKss;
    rDY_[37] = d_dt_C_K2;
    rDY_[38] = d_dt_C_K1;
    rDY_[39] = d_dt_O_K;
    rDY_[40] = d_dt_I_K;


}
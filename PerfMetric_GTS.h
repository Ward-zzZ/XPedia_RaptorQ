#ifndef __PERF_METRIC_GTS_H
#define __PERF_METRIC_GTS_H

/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*
*   file: PerfMetric_GTS.h
*   purpose: claims for GTS(global time stamps), GTS is used to count the running time of functions or code segments
*   authors: Duan Weiminng 
*   date: since 2015...
*
*   Change History
*   1st version designed by Duan Weiming in 2015 (at home)
*   
*************************************************************************************************************************************************************************  */

#include "PerfMetric_GTSdef.h"


#define GLOBAL_TIMESTAMP_SWITCH_ON    1

#ifdef __cplusplus 
extern "C" {   
#endif  


typedef struct __stTimeStamp{
    int nUsed;  
    char strName[128];
    long lCounter; /* the triggered times */
    long lCurrTime; 
    double dSumTime;
} stTimeStamp;


extern stTimeStamp gvstGlobalTimeStampList[];
extern int gnGlobalTimesStampList_CHECKED;
extern int gnGlobalTimesStampList_REG_OK;
void Check_GlobalTimeStampList();
void GlobalTimeStamp_Register();
void GlobalTimeStamp_Show(int isON);
void GlobalTimeStamp_ResetCounter(int isON) ;



enum GlobalTIMESTAMP_ENUM{
    __GTS_NEW(UniformVEC_________)
    __GTS_NEW(GaussianAbsVEC____)
    __GTS_NEW(GaussianVEC________)
    __GTS_NEW(GaussianVEC8_______)

    
    __GTS_NEW(BlkMatrixTranpose_______)
    __GTS_NEW(Tst1____________________)
    __GTS_NEW(Tst2____________________)
    __GTS_NEW(Tst3____________________)
    __GTS_NEW(Tst4____________________)
    __GTS_NEW(Tst4s____________________)
    __GTS_NEW(Tst4d____________________)
    
    __GTS_NEW(Tst1x____________________)
    __GTS_NEW(Tst2x____________________)
    __GTS_NEW(Tst3x____________________)
    __GTS_NEW(Tst4x____________________)    
    __GTS_NEW(AVX_FFT_Base2_________)
    
    __GTS_NEW(FFT_Base8_AVX______)
    __GTS_NEW(FFT_Base4_AVX______)
    __GTS_NEW(FFT_Base4_AVX_REL______)
    __GTS_NEW(FFT8_BaseN_AVX_REL______)
    
    
    __GTS_NEW(fast_sine_cosine_lowprecison____)
    __GTS_NEW(tst_Standard_Sine_Cosine____)
    __GTS_NEW(AVX_Fast_Sine_Cosine___)
    __GTS_NEW(std_pwr10__________________)
    __GTS_NEW(fast_pwr10_________________)
    
    __GTS_NEW(AVX_fast_pwr10____________)
    
    
    __GTS_NEW(std_exp)
    __GTS_NEW(AVX_fast_exp)
    __GTS_NEW(VEC_expRAW)
    
    
    __GTS_NEW(std_log2__________________)
    __GTS_NEW(fastlog2__________________)   
    __GTS_NEW(fast_log2_________________)
    __GTS_NEW(AVX_fast_log2____________)
    
    __GTS_NEW(AVX_fast_log10____________)
    __GTS_NEW(std_log10__________________)
    
    __GTS_NEW(AVX_fast_log____________)
    __GTS_NEW(std_log__________________)    
    
    __GTS_NEW(SSE_64QAM_DEMOD)
    __GTS_NEW(tst_SSE_64QAM_DEMOD)
    __GTS_NEW(AVX_64QAM_DEMOD)
    
    
    __GTS_NEW(CxMatrixMulCxVec________)
    __GTS_NEW(AVX_CxMatrixMulCxVec____)
    
    
    __GTS_NEW(BinFile_LoadBytes_________)
    __GTS_NEW(BinFile_SaveMem_________)
    
    __GTS_NEW(Convert_Byte2Float________)
    __GTS_NEW(FDFIR_Filtering___________)
    __GTS_NEW(BlockCxOversampling_______)
    
    __GTS_NEW(OptimalPrecoding__________)
    __GTS_NEW(GenTruc_FDFading__________)
    
    __GTS_NEW(GenCIRShaping_____________)
    __GTS_NEW(BlockCxSubCONST)
    __GTS_NEW(AVX_BlockCxSubCONST)
    
    __GTS_NEW(TxtModu_str2CxSig)
    __GTS_NEW(Fast_PeakFind)
    __GTS_NEW(Test_PeakFind)
    __GTS_NEW(FindSlotPeak_T)
    
    __GTS_NEW(BlockCxMulCxVEC)
    __GTS_NEW(AVX_BlockCxMulCxVEC)

    __GTS_NEW(FFTV_std)
    __GTS_NEW(FFT_Base4_AVX_REL)
    __GTS_NEW(FFTW3_AVX_REL)    
    __GTS_NEW(FFTV_BaseN_AVX_REL______)
    __GTS_NEW(FFTV_BaseN_AVX_REL)

    __GTS_NEW(FFTW3_Run)

    __GTS_NEW(FFT_std_________________) 
    __GTS_NEW(FFTV_BaseN_AVX_REL___RearrangeData)
    __GTS_NEW(FFTV_BaseN_AVX_REL___1stFFT)
    __GTS_NEW(FFTV_BaseN_AVX_REL___nextFFT)
    __GTS_NEW(FFTV_BaseN_AVX_REL___postFFT) 
    
    __GTS_NEW(CxVEC_phaseRotateSTD)
    __GTS_NEW(CxVEC_phaseRotate)
    
    __GTS_NEW(CxVEC_XCorr_STD)
    __GTS_NEW(AVX_CxVEC_XCorr_REL)
    __GTS_NEW(AVX_CxVEC_XCorr_REL_MTSK)
    
    __GTS_NEW(AVX_BlockMulconst)
    __GTS_NEW(BlockMulconst)
    
    
    __GTS_NEW(BlockCxVECmulCONST)
    __GTS_NEW(AVX_BlockCxVECmulCONST)
    
    __GTS_NEW(AVX_Fast_Sine_H)
    __GTS_NEW(STD_sine)
    __GTS_NEW(AVX_Fast_Cosine_H)
    __GTS_NEW(STD_cosine)
    __GTS_NEW(AVX_Fast_Sine_Cosine_H)
    __GTS_NEW(STD_sine_cosine)
    
    
    
    __GTS_NEW(Gen_ZadoffChu_SEQ)
    __GTS_NEW(AVX_Gen_ZadoffChu_SEQ)
    
    __GTS_NEW(VEC_maxSTD)
    __GTS_NEW(VEC_maxAVX)
    
    __GTS_NEW(VEC_minSTD)
    __GTS_NEW(VEC_minAVX)
    
    __GTS_NEW(VEC_sqrtSTD)
    __GTS_NEW(VEC_sqrt)
    
    __GTS_NEW(FDFIR_run)
    __GTS_NEW(LTEsync_cp)
    __GTS_NEW(LTEsync_pss)
    __GTS_NEW(LTEsync_sssORG)
    __GTS_NEW(LTEcrs_est_ORG)
    
    
    __GTS_NEW(std_logBase)
    __GTS_NEW(AVX_fast_logBase)  
    __GTS_NEW(AVX_logBase_raw)  
    
    __GTS_NEW(VEC_invSTD)
    __GTS_NEW(VEC_invAVX)    
    
    __GTS_NEW(VEC_debpskSTD)
    __GTS_NEW(VEC_debpsk)

    __GTS_NEW(VEC_absAVXtry)
    __GTS_NEW(VEC_abs)

    
    __GTS_NEW(NRldpc_encoder)
    __GTS_NEW(NRldpc_decoder)
    __GTS_NEW(NRldpc_rowCHKllr)
    __GTS_NEW(NRldpc_rowCHKllrFAST)

    __GTS_NEW(NRldpc_tanh)
    __GTS_NEW(NRldpc_logTanhLKT)
    __GTS_NEW(VECs_logTanhFaST)
    __GTS_NEW(VECs_logTanhFaST_X)   
    __GTS_NEW(VECs_logTanhFaST_Y)       
    __GTS_NEW(VECs_logTanhFaST_Y0)           
    __GTS_NEW(VECs_logTanhFaST_Y1)       
    __GTS_NEW(VECs_logTanhFaST_Y2)               
    __GTS_NEW(VECs_logTanhFaST_Z)       
    __GTS_NEW(VECs_logTanhFaST_Z0)           
    __GTS_NEW(VECs_logTanhFaST_Z1)       
    __GTS_NEW(VECs_logTanhFaST_Z2)  

    __GTS_NEW(VECs_logTanhFaST_S)       
    __GTS_NEW(VECs_logTanhFaST_S0)           
    __GTS_NEW(VECs_logTanhFaST_S1)       
    __GTS_NEW(VECs_logTanhFaST_S2)        

    __GTS_NEW(VEC_atanhExpFaST_Z)        
    __GTS_NEW(VEC_atanhExpFaST_Z0)    
    __GTS_NEW(VEC_atanhExpFaST_Z1)                

    __GTS_NEW(VEC_atanhExpFaST_S)        
    __GTS_NEW(VEC_atanhExpFaST_S0)    
    __GTS_NEW(VEC_atanhExpFaST_S1)                


    __GTS_NEW(NRldpc_atanh)
    __GTS_NEW(NRldpc_atanhExpLKT)
    __GTS_NEW(NRldpc_product)
    __GTS_NEW(NRldpc_LKTcalc)

    __GTS_NEW(VEC_lktIDsign)
    __GTS_NEW(NRldpc_LKTlogtanh)
    __GTS_NEW(NRldpc_LKTatanhExp)
    

    __GTS_NEW(VEC_upClipping_STD)                                               //  auto-coding!!!
    __GTS_NEW(AVX_UpClipping_REL)                                               //  auto-coding!!!
    __GTS_NEW(VECs_max)                                                         //  auto-coding!!!
    __GTS_NEW(VECs_maxSTD)                                                      //  auto-coding!!!
    __GTS_NEW(NullFUNC_forINS)
    

    
    
    MAX_GLOBAL_TIMESTAMP_NUM,
};
/* 
__GTS_REG(FFT_Base4_AVX_REL)
__GTS_TICK(AVX_fast_exp)
__GTS_TUCK(AVX_fast_exp)
__GTS_FUNC(CxVEC_XCorr_STD, __call_func__)

*/


#ifdef __cplusplus 
} 
#endif  




#endif /* __PERF_METRIC_GTS_H */
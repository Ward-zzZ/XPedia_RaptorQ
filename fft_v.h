
#ifndef __FFT_V_H
#define __FFT_V_H
/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */

#define MAX_FFTN_BASE_NUM  16
#define MAX_FFTN_SIZE 65536
#define MAX_FFTSize_NUM 64  /* total 256 types of FFT size */



#include "PerfMetric_COMM.h"
//#include "PerfMetric_AVXs.h"
//#include "PerfMetric_MEM.h"
//#include "PerfMetric_CHK.h"
//#include "PerfMetric_GTS.h"
#ifndef  NEON_FLAG
#include "/usr/local/include/fftw3.h"
#include "xmmintrin.h"
#include "immintrin.h"
#endif



#ifdef __cplusplus 
extern "C" {
    #endif  
    

	
	void  _SetIntArray_(int *vnArray, int nStartVal, int nStep, int nNUM);
	int _BlockSumInt_(int *vnData, int nSize );
	int _FindInSortedINTs_(int *vnSortedData, int nTarget, int nSize);
	void _SortIntsWithIndex_(int *vnIndiceList, int *vnSortedData, int nSize, int isResetIndice);

	

	int  FFT_Plan();
	int  GetFFTStep(int *pOutFFTSize, int nFFTSize );
	int  GetFFT4Step(int *pOutFFTSize, int nFFTSize );
	int  GetFFT8Step(int *pOutFFTSize, int nFFTSize );
	int  FFT_TwiddleFactor(float *vfFFTTwiddleIQs, int nMaxBuffSIZE, int nFFTSize);
	int  FFTPlan_Base8_TwiddleFactor(float *vfIQMatrix8x8, float *vfFFTTwiddleIQs, int nMaxBuffSIZE, int nMaxFFTSize);
	int  FFTPlan_Base4_TwiddleFactor(float *vfFFTTwiddleIQs, int nMaxBuffSIZE, int nMaxFFTSize);	
	int  FFT_DataSortIndice(int *vnFFTSortIndice,  int nFFTSize);
	void FFT_RearrangeData(float *vfOut, float *vfSRC, int nFFTSize,int isFFT);	//void FFT_RearrangeData(float *vfOut, float *vfSRC, int nFFTSize,int isFFT=1);	
	void FFT_RearrangeDataVEC(float *vfOUT_IQVEC, float *vfSRC_IQVEC, int nFFTSize, int VECSize);	
	int  FFT8_DataSortIndice(int *vnFFTSortIndice,  int nFFTSize);
	int  FFTN_DataSortIndice(int *vnFFTSortIndice,  int nFFTSize);	
	int  FFT_std(float *vfOUT_IQ, float *vfSRC_IQ,int nFFTSize, int isNORM, int isFFT);//int  FFT_std(float *vfOUT_IQ, float *vfSRC_IQ,int nFFTSize, int isNORM=1, int isFFT=1);
	

	
	typedef struct __stFFTParam{
		int nFFTSize;	
		int nFFTStep;
		int   vnFFTBaseLIST[MAX_FFTN_BASE_NUM];
		int   vnButterflyGrpLIST[MAX_FFTN_BASE_NUM];
		int   vnButtflyNumPerGRP_LIST[MAX_FFTN_BASE_NUM*4];	
		float vfBaseTwiddleDeltaIQList[MAX_FFTN_BASE_NUM*4*2];    /*delta twiddle IQ for :  vec 8 ==> vec 4 ==> vec 2 ==> vec 1  */
		float vfBaseTwiddleInitVECList[MAX_FFTN_BASE_NUM*4*8*2];  /* initial twiddle IQ vector for :  vec 8 ==> vec 4 ==> vec 2 ===> vec 1 */
		float vfBaseTwiddleDeltaIQIFFT[MAX_FFTN_BASE_NUM*4*2];    /*delta twiddle IQ IFFT :  vec 8 ==> vec 4 ==> vec 2 ==> vec 1  */
		float vfBaseTwiddleInitVECIFFT[MAX_FFTN_BASE_NUM*4*8*2];  /* initial twiddle IQ vector IFFT :  vec 8 ==> vec 4 ==> vec 2 ===> vec 1	 */
		int*   vnFFTSortIndice;  /*int   vnFFTSortIndice[MAX_FFTN_SIZE]; */
	} stFFTParam;
	
	extern stFFTParam* gpstGlobalFFTParam_LIST;
	
	
	
	/*
	stFFTParam*  FFTN_Param_Init_REL( int nFFTSize);
	int FFT8_BaseN_AVX_REL(float *vfOUT_IQVEC, float *vfSRC_IQVEC,int nFFTSize);
	int FFTV_BaseN_AVX_REL(float *vfOUT_IQVEC, float *vfSRC_IQVEC,int nFFTSize, int nCxNumPerVEC, int isFFT=1, int isNORM=1, int CxVECGap=0);  */
	
	void FFTV_BaseN_AVX_REL(float *vfOUT_IQVEC, float *vfSRC_IQVEC,int nFFTSize, int nCxNumPerVEC, int isFFT, int isNORM);//void FFTV_BaseN_AVX_REL(float *vfOUT_IQVEC, float *vfSRC_IQVEC,int nFFTSize, int nCxNumPerVEC, int isFFT=1, int isNORM=1);
	
	#define FFTN_AVX_REL(__vfFFTinout__, __FFTSize__, __isFFT__)   	            FFTV_BaseN_AVX_REL(__vfFFTinout__, __vfFFTinout__, __FFTSize__, 1,__isFFT__,1)
	
	#define FFTN_AVX_RELX(__vfFFTout__,__vfFFTsrc__, __FFTSize__, __isFFT__)  	FFTV_BaseN_AVX_REL(__vfFFTout__,__vfFFTsrc__, __FFTSize__, 1,__isFFT__,1)
	
	#ifndef  NEON_FLAG
    extern fftwf_plan fftwf_plan_dft_1d(int n, fftwf_complex *in, fftwf_complex *out, int sign, unsigned flags);             
	extern void fftwf_execute_dft(const fftwf_plan p, fftwf_complex *in, fftwf_complex *out);     
	extern void fftwf_destroy_plan(const fftwf_plan plan);
	
	
	typedef struct {
		int m_FFTSize;
		int m_isFFT;
		fftwf_plan m_fftplan;
		float *vfCxFFT_In;
		float *vfCxFFT_out;	
	}  stFFTW3param;
	void FFTW3_Init(stFFTW3param *pstFFTW3,  int FFTSize, int isFFT);
	void FFTW3_Run(float *vfCxFFT_out, float *vfCxFFT_In, int FFTSize, int isFFT,stFFTW3param *pstFFTW3 );
	void FFTW3_Free(stFFTW3param *pstFFTW3 );	

	extern stFFTW3param* gpstGlobalFFTW3param_LIST;
	#endif
	
	//void FFTW3_AVX_REL(float *vfCxVFFT_out, float *vfCxVFFT_In, int FFTSize, int nCxNumPerVEC, int isFFT, int isFFTvec=1);
	//void FFTW3_AVX_REL(float *vfCxVFFT_out, float *vfCxVFFT_In, int FFTSize, int nCxNumPerVEC, int isFFT, int isFFTvec=1, int isNORM=1);
	void FFTW3_AVX_REL(float *vfCxVFFT_out, float *vfCxVFFT_In, int FFTSize, int nCxNumPerVEC, int isFFT, int isFFTvec, int isNORM);


	//void FFTV_AVX_InterFACE(float *vfOUT_IQVEC, float *vfSRC_IQVEC,int nFFTSize, int nCxNumPerVEC, int isFFT, int isNORM ,int gCMD_FFTW_ON, int isFFTvec=1);
	void FFTV_AVX_InterFACE(float *vfOUT_IQVEC, float *vfSRC_IQVEC,int nFFTSize, int nCxNumPerVEC, int isFFT, int isNORM ,int gCMD_FFTW_ON);
	
	#define FFT_AVX_InterFACE(__vfCxOUT__, __vfCxSRC__, __FFTlen__, __isFFT__ ) FFTV_AVX_InterFACE(__vfCxOUT__, __vfCxSRC__, __FFTlen__,1, __isFFT__, 1, 1) 
	#define FFT_AVX_REL(__vfCxSIG__, __FFTlen__, __isFFT__ )                  	FFTV_AVX_InterFACE(__vfCxSIG__, __vfCxSIG__, __FFTlen__,1, __isFFT__, 1, 1)
	
	#define CxVEC_fft(__CxVECout__,__CxVEC__, __FFTlen__)                       FFTV_AVX_InterFACE(__CxVECout__, __CxVEC__, __FFTlen__,1, 1, 1, 1 )
	#define CxVEC_ifft(__CxVECout__,__CxVEC__, __FFTlen__)                      FFTV_AVX_InterFACE(__CxVECout__, __CxVEC__, __FFTlen__,1, 0, 1, 1 )

	#define CxVECs_fft( __CxVECs_o__,__CxVECs__, __FFTlen__, __FFTnum__)        FFTV_AVX_InterFACE(__CxVECs_o__, __CxVECs__, __FFTlen__,__FFTnum__, 1, 1, 1)
	#define CxVECs_ifft(__CxVECs_o__,__CxVECs__, __FFTlen__, __FFTnum__)        FFTV_AVX_InterFACE(__CxVECs_o__, __CxVECs__, __FFTlen__,__FFTnum__, 0, 1, 1)


	
	#define CxVEC_fftS(__CxVEC__, __FFTlen__)                                   FFTV_AVX_InterFACE(__CxVEC__, __CxVEC__, __FFTlen__,1, 1, 1, 1 )
	#define CxVEC_ifftS(__CxVEC__, __FFTlen__)                                  FFTV_AVX_InterFACE(__CxVEC__, __CxVEC__, __FFTlen__,1, 0, 1, 1 )

	
	#define CxVEC_fftS_woNORM(__CxVEC__, __FFTlen__)                            FFTV_AVX_InterFACE(__CxVEC__, __CxVEC__, __FFTlen__,1, 1, 0, 1 )
	#define CxVEC_ifftS_woNORM(__CxVEC__, __FFTlen__)                           FFTV_AVX_InterFACE(__CxVEC__, __CxVEC__, __FFTlen__,1, 0, 0, 1 )

	
	
	
    #ifdef __cplusplus 
}
#endif  




//                             X(n)= X_2nd_0(m)*W(N,0n) +  X_2nd_1(m)*W(N,1n) 
//                                      W(N,0n)                       W(N,1n)                   
//0<= m < N/2    n = 0N/2 + m    ....    1                            W(N,m),       
//0<= m < N/2    n = 1N/2 + m   ....     1                           -W(N,m),        

//0<= m < N/2    n = 0N/2 + m  ....    | 1.0000000 + j*0.0000000         1.0000000 + j*0.0000000  |     |X_2nd_0(m)*1      |
//0<= m < N/2    n = 1N/2 + m  ....    | 1.0000000 + j*0.0000000         -1.0000000 + j*0.000000  |     |X_2nd_1(m)*W(N,1m)|
#define MICROXXX_AVX_BASE2_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__, __nDataInterlvrGAP__, \
	__ymmS0,__ymmS1,__ymmS2,__ymmS3,____pfCurrTMP_IQPtr____,__ymm0,__ymm1,__ymm2,__ymm3) \
/* ********************************************  1st output octect vector                   ***********************************************  //  \
//1.0000000 + j*0.0000000         1.0000000 + j*0.0000000   \
// *********************************************************************************************************************************** */  \
__ymm0 = _mm256_add_ps(__ymmS0, __ymmS2);  \
__ymm1 = _mm256_add_ps(__ymmS1, __ymmS3);  /*1st output octect vector ----image part */ \
_mm256_storeu_ps(__pfDataIQVEC_OUT__, __ymm0);       _mm256_storeu_ps(__pfDataIQVEC_OUT__ + 8, __ymm1);  \
/*  ********************************************  2nd output octect vector                   ***********************************************  //  \
//1.0000000 + j*0.0000000         -1.0000000 + j*0.000000   \
// *********************************************************************************************************************************** */  \
____pfCurrTMP_IQPtr____ = __pfDataIQVEC_OUT__ + __nDataInterlvrGAP__; \
__ymm2 = _mm256_sub_ps(__ymmS0, __ymmS2);  \
__ymm3 = _mm256_sub_ps(__ymmS1, __ymmS3);  /*1st output octect vector ----image part */ \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm2);   _mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);  


//                             X(n)= X_third_0(m)*W(N,0n) +X_third_1(m)*W(N,1n)   + X_third_2(m)*W(N,2n)   
//                                   W(N,0n)                   W(N,1n)                       W(N,2n)                     
//0<= m < N/3    n = m         ....    1                       W(N,m),                       W(N,2m),      
//0<= m < N/3    n = 1N/3 + m  ....    1        exp(-j*PI*2/3)*W(N,m),        exp(-j*PI*4/3)*W(N,2m),      
//0<= m < N/3    n = 2N/3 + m  ....    1        exp(-j*PI*4/3)*W(N,m),        exp(-j*PI*8/3)*W(N,2m),      

//0<= m < N/3    n = m         ....    | 1.0000000 + j*0.0000000         1.0000000 + j*0.0000000          1.0000000 + j*0.0000000  |     |X_third_0(m)*W(N,0m)|
//0<= m < N/3    n = 1N/3 + m  ....    | 1.0000000 + j*0.0000000         -0.500000 - j*0.8660254          -0.500000 + j*0.8660254  |     |X_third_1(m)*W(N,1m)|
//0<= m < N/3    n = 2N/3 + m  ....    | 1.0000000 + j*0.0000000         -0.500000 + j*0.8660254          -0.500000 - j*0.8660254  |     |X_third_2(m)*W(N,2m)|
#define MICROXXX_AVX_BASE3_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__, __nDataInterlvrGAP__, \
	__ymmS0,__ymmS1,__ymmS2,__ymmS3,__ymmS4,__ymmS5, ____pfCurrTMP_IQPtr____,__ymmC_I,__ymmC_Q,__ymm0,__ymm1,__ymm2,__ymm3) \
/* ********************************************  1st output octect vector                   ***********************************************  //  \
//1.0000000 + j*0.0000000         1.0000000 + j*0.0000000         1.0000000 + j*0.0000000   \
// *********************************************************************************************************************************** */  \
__ymmC_I = _mm256_set1_ps(0.5); \
__ymmC_Q = _mm256_set1_ps(0.8660254); \
____pfCurrTMP_IQPtr____ = __pfDataIQVEC_OUT__; \
__ymm2 = _mm256_add_ps(__ymmS0, __ymmS2);  \
__ymm2 = _mm256_add_ps(__ymm2, __ymmS4);   /*1st output octect vector ----real part */  \
__ymm3 = _mm256_add_ps(__ymmS1, __ymmS3);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS5);  /*1st output octect vector ----image part */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm2);   _mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  2nd output octect vector                   ***********************************************  //  \
//1.0000000 + j*0.0000000         -0.500000  -  j*0.8660254          -0.500000 + j*0.8660254    \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( -__ymmC_I  -  j*__ymmC_Q) = (__ymmS3*__ymmC_Q - __ymmS2*__ymmC_I  ) - j*(__ymmS2*__ymmC_Q + __ymmS3*__ymmC_I ) */  \
__ymm0 = _mm256_mul_ps(__ymmC_Q,__ymmS3); \
__ymm2 = _mm256_add_ps(__ymmS0, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_I,__ymmS2); \
__ymm2 = _mm256_sub_ps(__ymm2, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_Q,__ymmS2); \
__ymm3 = _mm256_sub_ps(__ymmS1, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_I,__ymmS3); \
__ymm3 = _mm256_sub_ps(__ymm3, __ymm0);  \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_I  + j*__ymmC_Q ) = -(__ymmS4*__ymmC_I + __ymmS5*__ymmC_Q  ) + j*(__ymmS4*__ymmC_Q - __ymmS5*__ymmC_I ) */  \
__ymm0 = _mm256_mul_ps(__ymmC_I,__ymmS4); \
__ymm2 = _mm256_sub_ps(__ymm2, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_Q,__ymmS5); \
__ymm2 = _mm256_sub_ps(__ymm2, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_Q,__ymmS4); \
__ymm3 = _mm256_add_ps(__ymm3, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_I,__ymmS5); \
__ymm3 = _mm256_sub_ps(__ymm3, __ymm0);  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm2);   _mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  3rd output octect vector                   ***********************************************  //  \
//1.0000000 + j*0.0000000         -0.500000 + j*0.8660254          -0.500000  -  j*0.8660254   \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( -__ymmC_I  +  j*__ymmC_Q ) = - (__ymmS3*__ymmC_Q + __ymmS2*__ymmC_I  ) + j*(__ymmS2*__ymmC_Q - __ymmS3*__ymmC_I ) */  \
__ymm0 = _mm256_mul_ps(__ymmC_Q,__ymmS3); \
__ymm2 = _mm256_sub_ps(__ymmS0, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_I,__ymmS2); \
__ymm2 = _mm256_sub_ps(__ymm2, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_Q,__ymmS2); \
__ymm3 = _mm256_add_ps(__ymmS1, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_I,__ymmS3); \
__ymm3 = _mm256_sub_ps(__ymm3, __ymm0);  \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_I  -  j*__ymmC_Q ) = (__ymmS5*__ymmC_Q - __ymmS4*__ymmC_I  ) -  j*(__ymmS4*__ymmC_Q +  __ymmS5*__ymmC_I ) */  \
__ymm0 = _mm256_mul_ps(__ymmC_Q,__ymmS5); \
__ymm2 = _mm256_add_ps(__ymm2, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_I,__ymmS4); \
__ymm2 = _mm256_sub_ps(__ymm2, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_Q,__ymmS4); \
__ymm3 = _mm256_sub_ps(__ymm3, __ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmC_I,__ymmS5); \
__ymm3 = _mm256_sub_ps(__ymm3, __ymm0);  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm2);   _mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  



//1.0000000000+j* 0.0000000000     1.0000000000+j* 0.0000000000       1.0000000000+j* 0.0000000000      1.0000000000+j* 0.0000000000      1.0000000000+j* 0.0000000000     
//1.0000000000+j* 0.0000000000     0.3090169944 - j* 0.9510565163     -0.8090169944 -j*0.5877852523     -0.8090169944+j*0.5877852523      0.3090169944 + j* 0.9510565163
//1.0000000000+j* 0.0000000000     -0.8090169944 -j*0.5877852523      0.3090169944 + j* 0.9510565163    0.3090169944 - j* 0.9510565163    -0.8090169944+j*0.5877852523
//1.0000000000+j* 0.0000000000     -0.8090169944+j*0.5877852523       0.3090169944 - j* 0.9510565163     0.3090169944+ j* 0.9510565163    -0.8090169944 -j*0.5877852523 
//1.0000000000+j* 0.0000000000     0.3090169944 + j* 0.9510565163     -0.8090169944+j*0.5877852523      -0.8090169944 -j*0.5877852523     0.3090169944 - j* 0.9510565163
#define MICROXXX_AVX_BASE5_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__,  __nDataInterlvrGAP__, \
	__ymmS0,__ymmS1,__ymmS2,__ymmS3,__ymmS4,__ymmS5,__ymmS6,__ymmS7, __ymmS8,__ymmS9, ____pfCurrTMP_IQPtr____,__ymm0,__ymm1,__ymmC_0,__ymmC_1,__ymmC_2,__ymmC_3) \
/* ********************************************  1st output octect vector                   ***********************************************  //  \
//1.0000000000+j* 0.0000000000     1.0000000000+j* 0.0000000000      1.0000000000+j* 0.0000000000     1.0000000000+j* 0.0000000000     1.0000000000+j* 0.0000000000     \
// *********************************************************************************************************************************** */  \
__ymmC_0 = _mm256_set1_ps(0.3090169944); \
__ymmC_1 = _mm256_set1_ps(0.9510565163); \
__ymmC_2 = _mm256_set1_ps(0.8090169944); \
__ymmC_3 = _mm256_set1_ps(0.5877852523); \
____pfCurrTMP_IQPtr____ = __pfDataIQVEC_OUT__; \
__ymm0 = _mm256_add_ps(__ymmS0, __ymmS2);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS4);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS6);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS8);  /*1st output octect vector ----real part */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  \
__ymm0 = _mm256_add_ps(__ymmS1, __ymmS3);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS5);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS7);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS9);  /*1st output octect vector ----image part */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0);  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  2nd output octect vector                   ***********************************************  //  \
//1.0000000000+j* 0.0000000000     0.3090169944 - j* 0.9510565163      -0.8090169944 -j*0.5877852523     -0.8090169944+j*0.5877852523     0.3090169944 + j* 0.9510565163    \
// __ymmC_0 = (0.3090169944); __ymmC_1 = (0.9510565163); __ymmC_2 = (0.8090169944); __ymmC_3 = (0.5877852523); \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS2*__ymmC_0 + __ymmS3*__ymmC_1 ) + j* (__ymmS3*__ymmC_0 - __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS2 );  \
__ymm0 =  _mm256_add_ps(__ymmS0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS3 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_2 - j*__ymmC_3 ) = (__ymmS5*__ymmC_3 - __ymmS4*__ymmC_2 ) - j* (__ymmS4*__ymmC_3 + __ymmS5*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS5 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS4 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( -__ymmC_2 + j*__ymmC_3 ) = -(__ymmS6*__ymmC_2 + __ymmS7*__ymmC_3 ) + j* (__ymmS6*__ymmC_3 - __ymmS7*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS6 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS7 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( __ymmC_0 + j*__ymmC_1 ) = (__ymmS8*__ymmC_0 - __ymmS9*__ymmC_1 ) + j* (__ymmS8*__ymmC_1 + __ymmS9*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS8 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS9 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  /* output the  real part of the octect vector */ \
/* (__ymmS2 + j*__ymmS3 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS2*__ymmC_0 + __ymmS3*__ymmC_1 ) + j* (__ymmS3*__ymmC_0 - __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS3 );  \
__ymm0 =  _mm256_add_ps(__ymmS1, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS2 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_2 - j*__ymmC_3 ) = (__ymmS5*__ymmC_3 - __ymmS4*__ymmC_2 ) - j* (__ymmS4*__ymmC_3 + __ymmS5*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS4 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS5 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( -__ymmC_2 + j*__ymmC_3 ) = -(__ymmS6*__ymmC_2 + __ymmS7*__ymmC_3 ) + j* (__ymmS6*__ymmC_3 - __ymmS7*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS6 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS7 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( __ymmC_0 + j*__ymmC_1 ) = (__ymmS8*__ymmC_0 - __ymmS9*__ymmC_1 ) + j* (__ymmS8*__ymmC_1 + __ymmS9*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS8 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS9 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0); /* output the  imag part of the octect vector */  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  3nd output octect vector                   ***********************************************  //  \
//1.0000000000+j* 0.0000000000     -0.8090169944 -j*0.5877852523       0.3090169944 + j* 0.9510565163   0.3090169944 - j* 0.9510565163    -0.8090169944+j*0.5877852523    \
// __ymmC_0 = (0.3090169944); __ymmC_1 = (0.9510565163); __ymmC_2 = (0.8090169944); __ymmC_3 = (0.5877852523); \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( -__ymmC_2 - j*__ymmC_3 ) = (__ymmS3*__ymmC_3 - __ymmS2*__ymmC_2 ) - j* (__ymmS2*__ymmC_3 + __ymmS3*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS3 );  \
__ymm0 =  _mm256_add_ps(__ymmS0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS2 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( __ymmC_0 + j*__ymmC_1 ) = (__ymmS4*__ymmC_0 - __ymmS5*__ymmC_1 ) + j* (__ymmS4*__ymmC_1 + __ymmS5*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS4 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS5 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS7*__ymmC_1 + __ymmS6*__ymmC_0 ) + j* (__ymmS7*__ymmC_0 - __ymmS6*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS7 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS6 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_2 + j*__ymmC_3 ) = -(__ymmS8*__ymmC_2 + __ymmS9*__ymmC_3 ) + j* (__ymmS8*__ymmC_3 - __ymmS9*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS8 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS9 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  /* output the  real part of the octect vector */ \
/* (__ymmS2 + j*__ymmS3 ) * ( -__ymmC_2 - j*__ymmC_3 ) = (__ymmS3*__ymmC_3 - __ymmS2*__ymmC_2 ) - j* (__ymmS2*__ymmC_3 + __ymmS3*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS2 );  \
__ymm0 =  _mm256_sub_ps(__ymmS1, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS3 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( __ymmC_0 + j*__ymmC_1 ) = (__ymmS4*__ymmC_0 - __ymmS5*__ymmC_1 ) + j* (__ymmS4*__ymmC_1 + __ymmS5*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS4 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS5 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS7*__ymmC_1 + __ymmS6*__ymmC_0 ) + j* (__ymmS7*__ymmC_0 - __ymmS6*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS7 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS6 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_2 + j*__ymmC_3 ) = -(__ymmS8*__ymmC_2 + __ymmS9*__ymmC_3 ) + j* (__ymmS8*__ymmC_3 - __ymmS9*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS8 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS9 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0); /* output the  imag part of the octect vector */  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  4th output octect vector                   ***********************************************  //  \
//1.0000000000+j* 0.0000000000     -0.8090169944+j*0.5877852523       0.3090169944 - j* 0.9510565163     0.3090169944+ j* 0.9510565163   -0.8090169944 -j*0.5877852523    \
// __ymmC_0 = (0.3090169944); __ymmC_1 = (0.9510565163); __ymmC_2 = (0.8090169944); __ymmC_3 = (0.5877852523); \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( -__ymmC_2 + j*__ymmC_3 ) = -(__ymmS3*__ymmC_3 + __ymmS2*__ymmC_2 ) + j* (__ymmS2*__ymmC_3 - __ymmS3*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS3 );  \
__ymm0 =  _mm256_sub_ps(__ymmS0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS2 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS4*__ymmC_0 + __ymmS5*__ymmC_1 ) + j* (__ymmS5*__ymmC_0 - __ymmS4*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS4 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS5 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( __ymmC_0 + j*__ymmC_1 ) = ( __ymmS6*__ymmC_0 - __ymmS7*__ymmC_1 ) + j* (__ymmS7*__ymmC_0 + __ymmS6*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS7 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS6 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_2 - j*__ymmC_3 ) = (__ymmS9*__ymmC_3 - __ymmS8*__ymmC_2  ) - j* (__ymmS8*__ymmC_3 +  __ymmS9*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS8 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS9 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  /* output the  real part of the octect vector */ \
/* (__ymmS2 + j*__ymmS3 ) * ( -__ymmC_2 + j*__ymmC_3 ) = -(__ymmS3*__ymmC_3 + __ymmS2*__ymmC_2 ) + j* (__ymmS2*__ymmC_3 - __ymmS3*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS2 );  \
__ymm0 =  _mm256_add_ps(__ymmS1, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS3 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS4*__ymmC_0 + __ymmS5*__ymmC_1 ) + j* (__ymmS5*__ymmC_0 - __ymmS4*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS5 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS4 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( __ymmC_0 + j*__ymmC_1 ) = ( __ymmS6*__ymmC_0 - __ymmS7*__ymmC_1 ) + j* (__ymmS7*__ymmC_0 + __ymmS6*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS7 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS6 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_2 - j*__ymmC_3 ) = (__ymmS9*__ymmC_3 - __ymmS8*__ymmC_2  ) - j* (__ymmS8*__ymmC_3 +  __ymmS9*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS8 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS9 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0); /* output the  imag part of the octect vector */  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  5th output octect vector                   ***********************************************  //  \
//1.0000000000+j* 0.0000000000     0.3090169944 + j* 0.9510565163    -0.8090169944+j*0.5877852523      -0.8090169944 -j*0.5877852523     0.3090169944 - j* 0.9510565163   \
// __ymmC_0 = (0.3090169944); __ymmC_1 = (0.9510565163); __ymmC_2 = (0.8090169944); __ymmC_3 = (0.5877852523); \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( __ymmC_0 + j*__ymmC_1 ) = (__ymmS2*__ymmC_0 - __ymmS3*__ymmC_1 ) + j* (__ymmS3*__ymmC_0 + __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS2 );  \
__ymm0 =  _mm256_add_ps(__ymmS0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS3 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_2 + j*__ymmC_3 ) = -(__ymmS5*__ymmC_3 + __ymmS4*__ymmC_2 ) + j* (__ymmS4*__ymmC_3 - __ymmS5*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS5 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS4 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( -__ymmC_2 - j*__ymmC_3 ) = ( __ymmS7*__ymmC_3 -  __ymmS6*__ymmC_2 ) - j* (__ymmS6*__ymmC_3 + __ymmS7*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS6 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS7 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS8*__ymmC_0 + __ymmS9*__ymmC_1 ) + j* ( __ymmS9*__ymmC_0 - __ymmS8*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS8 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS9 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  /* output the  real part of the octect vector */ \
/* (__ymmS2 + j*__ymmS3 ) * ( __ymmC_0 + j*__ymmC_1 ) = (__ymmS2*__ymmC_0 - __ymmS3*__ymmC_1 ) + j* (__ymmS3*__ymmC_0 + __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS3 );  \
__ymm0 =  _mm256_add_ps(__ymmS1, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS2 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_2 + j*__ymmC_3 ) = -(__ymmS5*__ymmC_3 + __ymmS4*__ymmC_2 ) + j* (__ymmS4*__ymmC_3 - __ymmS5*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS4 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS5 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( -__ymmC_2 - j*__ymmC_3 ) = ( __ymmS7*__ymmC_3 -  __ymmS6*__ymmC_2 ) - j* (__ymmS6*__ymmC_3 + __ymmS7*__ymmC_2 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_3, __ymmS6 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_2, __ymmS7 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS8*__ymmC_0 + __ymmS9*__ymmC_1 ) + j* ( __ymmS9*__ymmC_0 - __ymmS8*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS9 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS8 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0); /* output the  imag part of the octect vector */  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  





//1.00000000 + j*0.0000000    1.00000000 + j*0.0000000       1.00000000 + j*0.0000000        1.00000000 + j*0.0000000      1.00000000 + j*0.0000000         1.00000000 + j*0.0000000
//1.00000000 + j*0.0000000    0.500000000 - j*0.866025404    -0.500000000 - j*0.866025404    -1.00000000 +j*0.0000000     -0.500000000 + j*0.866025404      0.500000000 + j*0.866025404
//1.00000000 + j*0.0000000   -0.500000000 - j*0.866025404    -0.500000000 + j*0.866025404     1.00000000 + j*0.0000000    -0.500000000-  j*0.866025404     -0.500000000 + j*0.866025404
//1.00000000 + j*0.0000000   -1.00000000   + j*0.0000000     1.00000000 + j*0.0000000        -1.00000000 +  j*0.0000000    1.00000000    + j*0.0000000      -1.00000000 + j*0.0000000
//1.00000000 + j*0.0000000   -0.500000000 + j*0.866025404    -0.500000000 - j*0.866025404     1.00000000 + j*0.0000000    -0.500000000 +  j*0.866025404     -0.500000000 - j*0.866025404
//1.00000000 + j*0.0000000    0.500000000 + j*0.866025404    -0.500000000 + j*0.866025404    -1.00000000 + j*0.0000000    -0.500000000  -  j*0.866025404     0.500000000 - j*0.866025404
#define MICROXXX_AVX_BASE6_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__,  __nDataInterlvrGAP__, \
	__ymmS0,__ymmS1,__ymmS2,__ymmS3,__ymmS4,__ymmS5,__ymmS6,__ymmS7, __ymmS8,__ymmS9, __ymmS10,__ymmS11, ____pfCurrTMP_IQPtr____,__ymm0,__ymm1,__ymmC_0,__ymmC_1) \
__ymmC_0 = _mm256_set1_ps(0.500000000);  \
__ymmC_1 = _mm256_set1_ps(0.866025404);  \
/* ********************************************  1st output octect vector                   ***********************************************  //  \
//1.00000000 + j*0.0000000    1.00000000 + j*0.0000000         1.00000000 + j*0.0000000          1.00000000 + j*0.0000000      1.00000000 + j*0.0000000            1.00000000 + j*0.0000000     \
// *********************************************************************************************************************************** */  \
____pfCurrTMP_IQPtr____ = __pfDataIQVEC_OUT__; \
__ymm0 = _mm256_add_ps(__ymmS0, __ymmS2);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS4);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS6);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS8);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS10);  /*1st output octect vector ----real part */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  \
__ymm0 = _mm256_add_ps(__ymmS1, __ymmS3);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS5);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS7);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS9);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS11);  /*1st output octect vector ----image part */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0);  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  2nd output octect vector                   ***********************************************  //  \
//1.00000000 + j*0.0000000    0.500000000 - j*0.866025404    -0.500000000 - j*0.866025404     -1.00000000 + j*0.0000000     -0.500000000 + j*0.866025404      0.500000000 + j*0.866025404   \
//__ymmC_0 = (0.500000000);  __ymmC_1 = (0.866025404);  \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS2*__ymmC_0 + __ymmS3*__ymmC_1 ) + j* (__ymmS3*__ymmC_0 - __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS2 );  \
__ymm0 =  _mm256_add_ps(__ymmS0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS3 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (__ymmS5*__ymmC_1 - __ymmS4*__ymmC_0 ) - j* (__ymmS4*__ymmC_1 + __ymmS5*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS5 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS4 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( -1.00000000 + j*0.0000000 ) =  -__ymmS6  - j*__ymmS7 */  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymmS6 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_0 + j*__ymmC_1 ) = -(__ymmS8*__ymmC_0 + __ymmS9*__ymmC_1 ) + j* (__ymmS8*__ymmC_1 - __ymmS9*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS8 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS9 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS10 + j*__ymmS11 ) * ( __ymmC_0 + j*__ymmC_1 ) = (__ymmS10*__ymmC_0 - __ymmS11*__ymmC_1 ) + j* (__ymmS10*__ymmC_1 + __ymmS11*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS10 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS11 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  /* output the  real part of the octect vector */ \
/* (__ymmS2 + j*__ymmS3 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS2*__ymmC_0 + __ymmS3*__ymmC_1 ) + j* (__ymmS3*__ymmC_0 - __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps(__ymmC_0, __ymmS3 );  \
__ymm0 =  _mm256_add_ps(__ymmS1, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS2 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (__ymmS5*__ymmC_1 - __ymmS4*__ymmC_0 ) - j* (__ymmS4*__ymmC_1 + __ymmS5*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS4 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS5 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( -1.00000000 + j*0.0000000 ) =  -__ymmS6  - j*__ymmS7 */  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymmS7 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_0 + j*__ymmC_1 ) = -(__ymmS8*__ymmC_0 + __ymmS9*__ymmC_1 ) + j* (__ymmS8*__ymmC_1 - __ymmS9*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS8 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS9 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS10 + j*__ymmS11 ) * ( __ymmC_0 + j*__ymmC_1 ) = (__ymmS10*__ymmC_0 - __ymmS11*__ymmC_1 ) + j* (__ymmS10*__ymmC_1 + __ymmS11*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS10 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS11 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0); /* output the  imag part of the octect vector */  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  3rd output octect vector                   ***********************************************  //  \
//1.00000000 + j*0.0000000   -0.500000000 - j*0.866025404    -0.500000000 + j*0.866025404    1.00000000 + j*0.0000000    -0.500000000  -  j*0.866025404     -0.500000000 + j*0.866025404 \
//__ymmC_0 = (0.500000000);  __ymmC_1 = (0.866025404);  \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (-__ymmS2*__ymmC_0 + __ymmS3*__ymmC_1 ) - j* (__ymmS3*__ymmC_0 + __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS2 );  \
__ymm0 =  _mm256_sub_ps(__ymmS0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS3 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_0 +j*__ymmC_1 ) = (-__ymmS5*__ymmC_1 - __ymmS4*__ymmC_0 ) + j* (__ymmS4*__ymmC_1 - __ymmS5*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS5 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS4 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( 1.00000000 + j*0.0000000 ) =  __ymmS6  + j*__ymmS7 */  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymmS6 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (-__ymmS8*__ymmC_0 + __ymmS9*__ymmC_1 ) + j* (-__ymmS8*__ymmC_1 - __ymmS9*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS8 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS9 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS10 + j*__ymmS11 ) * ( -__ymmC_0 + j*__ymmC_1 ) = (-__ymmS10*__ymmC_0 - __ymmS11*__ymmC_1 ) + j* (__ymmS10*__ymmC_1 - __ymmS11*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS10 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS11 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  /* output the  real part of the octect vector */ \
/* (__ymmS2 + j*__ymmS3 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (-__ymmS2*__ymmC_0 + __ymmS3*__ymmC_1 ) - j* (__ymmS3*__ymmC_0 + __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS3 );  \
__ymm0 =  _mm256_sub_ps(__ymmS1, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS2 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_0 +j*__ymmC_1 ) = (-__ymmS5*__ymmC_1 - __ymmS4*__ymmC_0 ) + j* (__ymmS4*__ymmC_1 - __ymmS5*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS4 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS5 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( 1.00000000 + j*0.0000000 ) =  __ymmS6  + j*__ymmS7 */  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymmS7 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (-__ymmS8*__ymmC_0 + __ymmS9*__ymmC_1 ) + j* (-__ymmS8*__ymmC_1 - __ymmS9*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS8 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS9 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS10 + j*__ymmS11 ) * ( -__ymmC_0 + j*__ymmC_1 ) = (-__ymmS10*__ymmC_0 - __ymmS11*__ymmC_1 ) + j* (__ymmS10*__ymmC_1 - __ymmS11*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS10 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS11 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0); /* output the  imag part of the octect vector */  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/* ********************************************  4th output octect vector                   ***********************************************  //  \
//1.00000000 + j*0.0000000   -1.00000000   + j*0.0000000         1.00000000 + j*0.0000000       -1.00000000 +  j*0.0000000    1.00000000    + j*0.0000000        -1.00000000 + j*0.0000000  \
// *********************************************************************************************************************************** */  \
__ymm0 = _mm256_sub_ps(__ymmS0, __ymmS2);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS4);  \
__ymm0 = _mm256_sub_ps(__ymm0, __ymmS6);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS8);  \
__ymm0 = _mm256_sub_ps(__ymm0, __ymmS10);  /*1st output octect vector ----real part */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  \
__ymm0 = _mm256_sub_ps(__ymmS1, __ymmS3);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS5);  \
__ymm0 = _mm256_sub_ps(__ymm0, __ymmS7);  \
__ymm0 = _mm256_add_ps(__ymm0, __ymmS9);  \
__ymm0 = _mm256_sub_ps(__ymm0, __ymmS11);  /*1st output octect vector ----image part */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0);  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  5th output octect vector                   ***********************************************  //  \
//1.00000000 + j*0.0000000   -0.500000000 + j*0.866025404   -0.500000000 - j*0.866025404     1.00000000 + j*0.0000000    -0.500000000 +  j*0.866025404      -0.500000000 - j*0.866025404  \
//__ymmC_0 = (0.500000000);  __ymmC_1 = (0.866025404);  \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * (-__ymmC_0 + j*__ymmC_1 ) = (-__ymmS2*__ymmC_0 - __ymmS3*__ymmC_1 ) + j* (-__ymmS3*__ymmC_0 + __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS2 );  \
__ymm0 =  _mm256_sub_ps(__ymmS0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS3 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (__ymmS5*__ymmC_1 - __ymmS4*__ymmC_0 ) - j* (__ymmS4*__ymmC_1 + __ymmS5*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS5 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS4 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( 1.00000000 + j*0.0000000 ) =  __ymmS6  + j*__ymmS7 */  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymmS6 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_0 + j*__ymmC_1 ) = -(__ymmS8*__ymmC_0 + __ymmS9*__ymmC_1 ) + j* (__ymmS8*__ymmC_1 - __ymmS9*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS8 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS9 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS10 + j*__ymmS11 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (-__ymmS10*__ymmC_0 + __ymmS11*__ymmC_1 ) + j* (-__ymmS10*__ymmC_1 - __ymmS11*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS10 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS11 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  /* output the  real part of the octect vector */ \
/* (__ymmS2 + j*__ymmS3 ) * (-__ymmC_0 + j*__ymmC_1 ) = (-__ymmS2*__ymmC_0 - __ymmS3*__ymmC_1 ) + j* (-__ymmS3*__ymmC_0 + __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS3 );  \
__ymm0 =  _mm256_sub_ps(__ymmS1, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS2 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (__ymmS5*__ymmC_1 - __ymmS4*__ymmC_0 ) - j* (__ymmS4*__ymmC_1 + __ymmS5*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS4 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS5 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( 1.00000000 + j*0.0000000 ) =  __ymmS6  + j*__ymmS7 */  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymmS7 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_0 + j*__ymmC_1 ) = -(__ymmS8*__ymmC_0 + __ymmS9*__ymmC_1 ) + j* (__ymmS8*__ymmC_1 - __ymmS9*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS8 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS9 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS10 + j*__ymmS11 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (-__ymmS10*__ymmC_0 + __ymmS11*__ymmC_1 ) + j* (-__ymmS10*__ymmC_1 - __ymmS11*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS10 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS11 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0); /* output the  imag part of the octect vector */  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  6th output octect vector                   ***********************************************  //  \
//1.00000000 + j*0.0000000    0.500000000 + j*0.866025404   -0.500000000 + j*0.866025404   -1.00000000 + j*0.0000000    -0.500000000  -  j*0.866025404       0.500000000 - j*0.866025404  \
//__ymmC_0 = (0.500000000);  __ymmC_1 = (0.866025404);  \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( __ymmC_0 + j*__ymmC_1 ) = (__ymmS2*__ymmC_0 - __ymmS3*__ymmC_1 ) + j* (__ymmS3*__ymmC_0 + __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS2 );  \
__ymm0 =  _mm256_add_ps(__ymmS0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS3 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_0 +j*__ymmC_1 ) = (-__ymmS5*__ymmC_1 - __ymmS4*__ymmC_0 ) + j* (__ymmS4*__ymmC_1 - __ymmS5*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS5 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS4 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( -1.00000000 + j*0.0000000 ) =  -__ymmS6  - j*__ymmS7 */  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymmS6 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (-__ymmS8*__ymmC_0 + __ymmS9*__ymmC_1 ) + j* (-__ymmS8*__ymmC_1 - __ymmS9*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS8 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS9 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS10 + j*__ymmS11 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS10*__ymmC_0 + __ymmS11*__ymmC_1 ) + j* (-__ymmS10*__ymmC_1 + __ymmS11*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS10 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS11 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm0);  /* output the  real part of the octect vector */ \
/* (__ymmS2 + j*__ymmS3 ) * ( __ymmC_0 + j*__ymmC_1 ) = (__ymmS2*__ymmC_0 - __ymmS3*__ymmC_1 ) + j* (__ymmS3*__ymmC_0 + __ymmS2*__ymmC_1 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS3 );  \
__ymm0 =  _mm256_add_ps(__ymmS1, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS2 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
/* (__ymmS4 + j*__ymmS5 ) * ( -__ymmC_0 +j*__ymmC_1 ) = (-__ymmS5*__ymmC_1 - __ymmS4*__ymmC_0 ) + j* (__ymmS4*__ymmC_1 - __ymmS5*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS4 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS5 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS6 + j*__ymmS7 ) * ( -1.00000000 + j*0.0000000 ) =  -__ymmS6  - j*__ymmS7 */  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymmS7 ); \
/* (__ymmS8 + j*__ymmS9 ) * ( -__ymmC_0 - j*__ymmC_1 ) = (-__ymmS8*__ymmC_0 + __ymmS9*__ymmC_1 ) + j* (-__ymmS8*__ymmC_1 - __ymmS9*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS8 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS9 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
/* (__ymmS10 + j*__ymmS11 ) * ( __ymmC_0 - j*__ymmC_1 ) = (__ymmS10*__ymmC_0 + __ymmS11*__ymmC_1 ) + j* (-__ymmS10*__ymmC_1 + __ymmS11*__ymmC_0 )  */  \
__ymm1 =  _mm256_mul_ps( __ymmC_1, __ymmS10 );  \
__ymm0 =  _mm256_sub_ps(__ymm0, __ymm1 ); \
__ymm1 =  _mm256_mul_ps( __ymmC_0, __ymmS11 );  \
__ymm0 =  _mm256_add_ps(__ymm0, __ymm1 ); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm0); /* output the  imag part of the octect vector */  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  



//0<= m < N/4 
//n= m         ....|X(0N/4+m) | = |  1.000+j*0.000,   1.000+j*0.000,   1.000+j*0.000,   1.000+j*0.000,   |     |X_quad_0(m)*W(N,0m) |
//n= 1N/4 + m  ....|X(1N/4+m) | = |  1.000+j*0.000,   0.000 -j*1.000,  -1.000+j*0.000,  0.000+j*1.000,   |     |X_quad_1(m)*W(N,1m) |
//n= 2N/4 + m  ....|X(2N/4+m) | = |  1.000+j*0.000,   -1.000+j*0.000,  1.000+j*0.000,   -1.000+j*0.000,  |     |X_quad_2(m)*W(N,2m) | 
//n= 3N/4 + m  ....|X(3N/4+m) | = |  1.000+j*0.000,   0.000+j*1.000,  -1.000+j*0.000,   0.000-j*1.000,   |     |X_quad_3(m)*W(N,3m) | 

#define MICROXXX_AVX_BASE4_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__, __nDataInterlvrGAP__,__ymmS0,__ymmS1,__ymmS2,__ymmS3,__ymmS4,__ymmS5,__ymmS6,__ymmS7, ____pfCurrTMP_IQPtr____,__ymm0,__ymm1,__ymm2,__ymm3) \
/* ********************************************  1st output octect vector                   ***********************************************  //  \
//1.000+j*0.000,   1.000+j*0.000,  1.000+j*0.000,  1.000+j*0.000,  \
// *********************************************************************************************************************************** */  \
____pfCurrTMP_IQPtr____ = __pfDataIQVEC_OUT__; \
__ymm2 = _mm256_add_ps(__ymmS0, __ymmS2);  \
__ymm2 = _mm256_add_ps(__ymm2, __ymmS4);  \
__ymm2 = _mm256_add_ps(__ymm2, __ymmS6);  /*1st output octect vector ----real part */  \
__ymm3 = _mm256_add_ps(__ymmS1, __ymmS3);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS5);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS7);  /*1st output octect vector ----image part */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm2);   _mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  2nd output octect vector                   ***********************************************  //  \
//1.000+j*0.000,   0.000 -j*1.000,  -1.000+j*0.000,  0.000+j*1.000,    \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( 0.0000 - j*1.0000) = __ymmS3 - j*__ymmS2 */  \
__ymm2 = _mm256_add_ps(__ymmS0, __ymmS3);  \
__ymm3 = _mm256_sub_ps(__ymmS1, __ymmS2);   \
/* (__ymmS4 + j*__ymmS5 ) * ( -1.000+j*0.000 ) = -__ymmS4 - j*__ymmS5 */  \
__ymm2 = _mm256_sub_ps(__ymm2, __ymmS4);  \
__ymm3 = _mm256_sub_ps(__ymm3, __ymmS5);   \
/* (__ymmS6 + j*__ymmS7 ) * ( 0.000+j*1.000 ) = -__ymmS7 + j*__ymmS6 */  \
__ymm2 = _mm256_sub_ps(__ymm2, __ymmS7);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS6);   \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm2);   _mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  3rd output octect vector                   ***********************************************  //  \
//1.000+j*0.000,   -1.000+j*0.000,  1.000+j*0.000, -1.000+j*0.000   \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( -1.0000 + j*0.0000) = -__ymmS2 - j*__ymmS3 */  \
__ymm2 = _mm256_sub_ps(__ymmS0, __ymmS2);  \
__ymm3 = _mm256_sub_ps(__ymmS1, __ymmS3);   \
/* (__ymmS4 + j*__ymmS5 ) * ( 1.000+j*0.000 ) = __ymmS4 + j*__ymmS5 */  \
__ymm2 = _mm256_add_ps(__ymm2, __ymmS4);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS5);   \
/* (__ymmS6 + j*__ymmS7 ) * ( -1.000+j*0.000 ) = -__ymmS6 - j*__ymmS7 */  \
__ymm2 = _mm256_sub_ps(__ymm2, __ymmS6);  \
__ymm3 = _mm256_sub_ps(__ymm3, __ymmS7);   \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm2);   _mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  \
/*  ********************************************  4th output octect vector                   ***********************************************  //  \
//1.000+j*0.000,   0.000+j*1.000,  -1.000+j*0.000,  0.000-j*1.000,   \
// *********************************************************************************************************************************** */  \
/* (__ymmS2 + j*__ymmS3 ) * ( 0.0000 + j*1.0000) = -__ymmS3 + j*__ymmS2 */  \
__ymm2 = _mm256_sub_ps(__ymmS0, __ymmS3);  \
__ymm3 = _mm256_add_ps(__ymmS1, __ymmS2);   \
/* (__ymmS4 + j*__ymmS5 ) * ( -1.000+j*0.000 ) = -__ymmS4 - j*__ymmS5 */  \
__ymm2 = _mm256_sub_ps(__ymm2, __ymmS4);  \
__ymm3 = _mm256_sub_ps(__ymm3, __ymmS5);   \
/* (__ymmS6 + j*__ymmS7 ) * ( 0.000-j*1.000 ) = __ymmS7 - j*__ymmS6 */  \
__ymm2 = _mm256_add_ps(__ymm2, __ymmS7);  \
__ymm3 = _mm256_sub_ps(__ymm3, __ymmS6);   \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm2);   _mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);  \
____pfCurrTMP_IQPtr____ += __nDataInterlvrGAP__;  


/*

		1.0000,  0.0000, 1.0000,  0.0000,    1.0000,  0.0000,   1.0000,  0.0000,   1.0000,  0.0000,   1.0000,  0.0000,   1.0000,  0.0000,    1.0000,  0.0000, 
		1.0000,  0.0000, 0.7071,  -0.7071,   0.0000,  -1.0000,  -0.7071, -0.7071,  -1.0000,  0.0000,  -0.7071,  0.7071,  0.0000,   1.0000,   0.7071,  0.7071,  
		1.0000,  0.0000, 0.0000,  -1.0000,  -1.0000,  0.0000,    0.0000,  1.0000,   1.0000,  0.0000,   0.0000, -1.0000, -1.0000,   0.0000,   0.0000,  1.0000,   
		1.0000,  0.0000, -0.7071, -0.7071,   0.0000,  1.0000,    0.7071, -0.7071,  -1.0000,  0.0000,  0.7071,   0.7071,  0.0000,  -1.0000,  -0.7071,  0.7071,  
		1.0000,  0.0000, -1.0000,  0.0000,   1.0000,  0.0000,   -1.0000,  0.0000,   1.0000,  0.0000,  -1.0000,  0.0000,  1.0000,   0.0000,  -1.0000,  0.0000,  
		1.0000,  0.0000, -0.7071,  0.7071,   0.0000, -1.0000,    0.7071,  0.7071,  -1.0000,  0.0000,  0.7071,  -0.7071,  0.0000,   1.0000,  -0.7071, -0.7071,  
		1.0000,  0.0000, 0.0000,   1.0000,  -1.0000,  0.0000,    0.0000, -1.0000,   1.0000,  0.0000,  0.0000,   1.0000, -1.0000,   0.0000,   0.0000, -1.0000,
		1.0000,  0.0000, 0.7071,   0.7071,   0.0000,  1.0000,   -0.7071,  0.7071,  -1.0000,  0.0000,  -0.7071, -0.7071,  0.0000,  -1.0000,   0.7071, -0.7071,
*/
#define MICROXXX_AVX_BASE8_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__, __pfCurr1stSrcOctVEC__, __nDataInterlvrGAP__,__ymmS2,__ymmS3,__ymmS4,__ymmS5,__ymmS6,__ymmS7,__ymmS8,__ymmS9,__ymmS10,__ymmS11,__ymmS12,__ymmS13,__ymmS14,__ymmS15, ____pfCurrTMP_IQPtr____,__ymm0,__ymm1,__ymm2,__ymm3) \
/* ********************************************  1st output octect vector                   ***********************************************  //  \
//1.0000,  0.0000,  1.0000,  0.0000,   1.0000,  0.0000,  1.0000,  0.0000,  1.0000,  0.0000,  1.0000,  0.0000, 1.0000,  0.0000,  1.0000,  0.0000,  \
// *********************************************************************************************************************************** */  \
____pfCurrTMP_IQPtr____ = __pfDataIQVEC_OUT__; \
__ymm1 = _mm256_loadu_ps(__pfCurr1stSrcOctVEC__);  	  /* load real part of the 1st octect vector */  \
__ymm3 = _mm256_add_ps(__ymm1, __ymmS2);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS4);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS6);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS8);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS10); \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS12); \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS14);  /*1st output octect vector ----real part */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm3); ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  \
/*  ********************************************  3rd output octect vector                   ***********************************************  //  \
//1.0000,  0.0000, 0.0000,  -1.0000,  -1.0000,  0.0000,    0.0000,  1.0000,   1.0000,  0.0000,   0.0000, -1.0000, -1.0000,   0.0000,   0.0000,  1.0000,   \
// *********************************************************************************************************************************** */  \
__ymm3 = _mm256_add_ps(__ymm1,__ymmS3);   /* (__ymmS2 + j*__ymmS3 ) * ( 0.0000 - j*1.0000) = __ymmS3 - j*__ymmS2  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS4);   /* (__ymmS4 + j* __ymmS5 ) * ( -1.000 + j*0.000)  = -__ymmS4 - j*__ymmS5 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS7);  /* (__ymmS6 + j*__ymmS7 ) * ( 0.000 + j*1.000) = -__ymmS7 + j*__ymmS6  */ \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS8);  /* (__ymmS8 + j*__ymmS9 ) * ( 1.000 + j*0.000) = __ymmS8 + j*__ymmS9  */ \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS11);  /* (__ymmS10 + j*__ymmS11 ) * ( 0.0000 - j*1.0000) = __ymmS11 - j*__ymmS10  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS12);  /* (__ymmS12 + j*__ymmS13) * ( -1.000 + j*0.000) = -__ymmS12 -  j*__ymmS13  */   \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS15);  /* (__ymmS14 + j*__ymmS15 ) * ( 0.000 + j*1.000) = -__ymmS15 + j*__ymmS14  */ \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm3); ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /* 3rd output octect vector ----real part */  \
/* ********************************************  5th output octect vector                   ***********************************************  //  \
//1.0000,  0.0000, -1.0000,  0.0000,   1.0000,  0.0000,   -1.0000,  0.0000,   1.0000,  0.0000,  -1.0000,  0.0000,  1.0000,   0.0000,  -1.0000,  0.0000,  \
// *********************************************************************************************************************************** */  \
__ymm3 = _mm256_sub_ps(__ymm1,__ymmS2);  /* (__ymmS2 + j*__ymmS3 ) * ( -1.0000 + j*0.0000) = -__ymmS2 - j*__ymmS3 */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS4);  /* (__ymmS4 + j* __ymmS5 ) * ( 1.000 + j*0.000)  = __ymmS4 + j*__ymmS5 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS6);  /* (__ymmS6 + j*__ymmS7 ) * ( -1.000 + j*0.000) = - __ymmS6 - j*__ymmS7 */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS8); /* (__ymmS8 + j*__ymmS9 ) * ( 1.000 + j*0.000) = __ymmS8 + j*__ymmS9 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS10); /* (__ymmS10 + j*__ymmS11 ) * ( -1.0000 + j*0.0000) = - __ymmS10  - j*__ymmS11 */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS12); /* (__ymmS12 + j*__ymmS13) * ( 1.000 + j*0.000) = __ymmS12 +  j*__ymmS13 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS14); /* (__ymmS14 + j*__ymmS15 ) * ( -1.000 + j*0.000) = -__ymmS14 -  j*__ymmS15 */ \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm3);  ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /* 5th output octect vector ----real part */  \
/* ********************************************  7th output octect vector                   ***********************************************  //   \
//1.0000,  0.0000, 0.0000,   1.0000,  -1.0000,  0.0000,    0.0000, -1.0000,   1.0000,  0.0000,  0.0000,   1.0000, -1.0000,   0.0000,   0.0000, -1.0000,  \
// *********************************************************************************************************************************** */  \
__ymm3 = _mm256_sub_ps(__ymm1,__ymmS3);  /*  (__ymmS2 + j*__ymmS3 ) * ( 0.0000 + j*1.0000) = -__ymmS3 + j*__ymmS2 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS4);  /* (__ymmS4 + j* __ymmS5 ) * ( -1.000 + j*0.000)  = - __ymmS4 - j*__ymmS5 */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS7); /* (__ymmS6 + j*__ymmS7 ) * ( 0.000 - j*1.000) = __ymmS7 - j*__ymmS6 */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS8); /* (__ymmS8 + j*__ymmS9 ) * ( 1.000 + j*0.000) = __ymmS8 + j*__ymmS9 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS11); /* (__ymmS10 + j*__ymmS11 ) * ( 0.0000 + j*1.0000) = - __ymmS11  + j*__ymmS10 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS12); /*  (__ymmS12 + j*__ymmS13) * ( -1.000 + j*0.000) = - __ymmS12 -   j*__ymmS13 */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS15); /*  (__ymmS14 + j*__ymmS15 ) * ( 0.000 - j*1.000) = + __ymmS15 - j*__ymmS14  */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm3); ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /* 7th output octect vector ----real part */  \
____pfCurrTMP_IQPtr____ = __pfDataIQVEC_OUT__ ; \
__ymm1 = _mm256_loadu_ps(__pfCurr1stSrcOctVEC__ +8);  /* load imaginary part of the 1st octect vector  */  \
__ymm3 = _mm256_add_ps(__ymm1, __ymmS3);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS5);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS7);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS9);  \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS11); \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS13); \
__ymm3 = _mm256_add_ps(__ymm3, __ymmS15); \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);   ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__; /* 1st output octect vector ----imag part */  \
__ymm3 = _mm256_sub_ps(__ymm1,__ymmS2);  /*  (__ymmS2 + j*__ymmS3 ) * ( 0.0000 - j*1.0000) = __ymmS3 - j*__ymmS2 */   \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS5);  /*  (__ymmS4 + j* __ymmS5 ) * ( -1.000 + j*0.000)  = -__ymmS4 - j*__ymmS5 */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS6); /* (__ymmS6 + j*__ymmS7 ) * ( 0.000 + j*1.000) = -__ymmS7 + j*__ymmS6  */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS9); /* (__ymmS8 + j*__ymmS9 ) * ( 1.000 + j*0.000) = __ymmS8 + j*__ymmS9  */ \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS10); /* (__ymmS10 + j*__ymmS11 ) * ( 0.0000 - j*1.0000) = __ymmS11 - j*__ymmS10 */ \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS13); /* (__ymmS12 + j*__ymmS13) * ( -1.000 + j*0.000) = -__ymmS12 -  j*__ymmS13 */ \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS14); /* (__ymmS14 + j*__ymmS15 ) * ( 0.000 + j*1.000) = -__ymmS15 + j*__ymmS14  */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);   ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__; /* 3rd output octect vector ----imag part */ \
__ymm3 = _mm256_sub_ps(__ymm1,__ymmS3);  /* (__ymmS2 + j*__ymmS3 ) * ( -1.0000 + j*0.0000) = -__ymmS2 - j*__ymmS3 */ \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS5);  /* (__ymmS4 + j* __ymmS5 ) * ( 1.000 + j*0.000)  = __ymmS4 + j*__ymmS5 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS7); /* (__ymmS6 + j*__ymmS7 ) * ( -1.000 + j*0.000) = - __ymmS6 - j*__ymmS7 */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS9); /* (__ymmS8 + j*__ymmS9 ) * ( 1.000 + j*0.000) = __ymmS8 + j*__ymmS9  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS11); /* (__ymmS10 + j*__ymmS11 ) * ( -1.0000 + j*0.0000) = - __ymmS10  - j*__ymmS11	 */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS13);  /* (__ymmS12 + j*__ymmS13) * ( 1.000 + j*0.000) = __ymmS12 +  j*__ymmS13 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS15); /* (__ymmS14 + j*__ymmS15 ) * ( -1.000 + j*0.000) = -__ymmS14 -  j*__ymmS15  */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);   ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /* 5th output octect vector ----imag part  */  \
__ymm3 = _mm256_add_ps(__ymm1,__ymmS2);  /* (__ymmS2 + j*__ymmS3 ) * ( 0.0000 + j*1.0000) = -__ymmS3 + j*__ymmS2 */ \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS5);  /* (__ymmS4 + j* __ymmS5 ) * ( -1.000 + j*0.000)  = -__ymmS4 - j*__ymmS5 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS6); /* (__ymmS6 + j*__ymmS7 ) * ( 0.000 - j*1.000) = __ymmS7 - j*__ymmS6  */ \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS9); /* (__ymmS8 + j*__ymmS9 ) * ( 1.000 + j*0.000) = __ymmS8 + j*__ymmS9  */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS10); /* (__ymmS10 + j*__ymmS11 ) * ( 0.0000 + j*1.0000) = - __ymmS11  + j*__ymmS10 */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS13); /* (__ymmS12 + j*__ymmS13) * ( -1.000 + j*0.000) = - __ymmS12 -   j*__ymmS13 */ \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS14); /* (__ymmS14 + j*__ymmS15 ) * ( 0.000 - j*1.000) = + __ymmS15 - j*__ymmS14  */ \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);   ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__; /* 7th output octect vector ----imag part */  \
__ymm2 = _mm256_set1_ps(0.7071);  \
____pfCurrTMP_IQPtr____ = __pfDataIQVEC_OUT__ + __nDataInterlvrGAP__;  \
__ymm1 = _mm256_loadu_ps(__pfCurr1stSrcOctVEC__);  	  /* load real part of the 1st octect vector */  \
/*  ********************************************  2nd output octect vector                   ***********************************************  //  \
//1.0000,  0.0000, 0.7071,  -0.7071,   0.0000,  -1.0000,  -0.7071, -0.7071,  -1.0000,  0.0000,  -0.7071,  0.7071,  0.0000,   1.0000,   0.7071,  0.7071,   \
// *********************************************************************************************************************************** */  \
__ymm0 = _mm256_mul_ps(__ymmS2,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm1,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS3,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  /* + (0.7071*__ymmS2 + 0.7071*__ymmS3 )  */ \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS5);   /* + __ymmS5  */  \
__ymm0 = _mm256_mul_ps(__ymmS7,__ymm2); \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS6,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /* + (0.7071*__ymmS7 - 0.7071*__ymmS6)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS8); /* -__ymmS8  */  \
__ymm0 = _mm256_mul_ps(__ymmS10,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS11,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /* - (0.7071*__ymmS10 + 0.7071*__ymmS11) */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS13);  /* - __ymmS13  */  \
__ymm0 = _mm256_mul_ps(__ymmS14,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);   \
__ymm0 = _mm256_mul_ps(__ymmS15,__ymm2); \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /* + ( 0.7071*__ymmS14 - 0.7071*__ymmS15)  */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm3);     ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /* 2nd output octect vector ----real part */  \
/*  ********************************************  4th output octect vector                   ***********************************************  //  \
//1.0000,  0.0000, -0.7071, -0.7071,   0.0000,  1.0000,    0.7071, -0.7071,  -1.0000,  0.0000,  0.7071,   0.7071,  0.0000,  -1.0000,  -0.7071,  0.7071,  \
// *********************************************************************************************************************************** */  \
__ymm0 = _mm256_mul_ps(__ymmS3,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm1,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS2,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);     /* + (0.7071*__ymmS3 - 0.7071*__ymmS2)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS5);   /* - __ymmS5  */  \
__ymm0 = _mm256_mul_ps(__ymmS7,__ymm2); \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS6,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0); /* + (0.7071*__ymmS7 + 0.7071*__ymmS6) */ \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS8); /* -__ymmS8  */  \
__ymm0 = _mm256_mul_ps(__ymmS10,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS11,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /* + (0.7071*__ymmS10 - 0.7071*__ymmS11) */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS13); /* + __ymmS13  */   \
__ymm0 = _mm256_mul_ps(__ymmS14,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS15,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /*  - ( 0.7071*__ymmS14 + 0.7071*__ymmS15) */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm3);   ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /* 4th output octect vector ----real part */  \
/* ********************************************  6th output octect vector                   ***********************************************  //  \
//1.0000,  0.0000, -0.7071,  0.7071,   0.0000, -1.0000,    0.7071,  0.7071,  -1.0000,  0.0000,  0.7071,  -0.7071,  0.0000,   1.0000,  -0.7071, -0.7071,  \
// *********************************************************************************************************************************** */  \
__ymm0 = _mm256_mul_ps(__ymmS2,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm1,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS3,__ymm2); \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /*  - ( 0.7071*__ymmS2 + 0.7071*__ymmS3)  */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS5);  /* + __ymmS5  */  \
__ymm0 = _mm256_mul_ps(__ymmS6,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS7,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);   /* +  (0.7071*__ymmS6 - 0.7071*__ymmS7)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS8); /* -__ymmS8  */  \
__ymm0 = _mm256_mul_ps(__ymmS10,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS11,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  /* + (0.7071*__ymmS10 + 0.7071*__ymmS11)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS13); /*  - __ymmS13  */  \
__ymm0 = _mm256_mul_ps(__ymmS15,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);   \
__ymm0 = _mm256_mul_ps(__ymmS14,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  /* + ( 0.7071*__ymmS15 - 0.7071*__ymmS14)  */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm3);  ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /* 6th output octect vector ----real part */  \
/* ********************************************  8th output octect vector                   ***********************************************  //  \
//1.0000,  0.0000, 0.7071,   0.7071,   0.0000,  1.0000,   -0.7071,  0.7071,  -1.0000,  0.0000,  -0.7071, -0.7071,  0.0000,  -1.0000,   0.7071, -0.7071,  \
// ***********************************************************************************************************************************  */  \
__ymm0 = _mm256_mul_ps(__ymmS2,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm1,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS3,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  /* + (0.7071*__ymmS2 - 0.7071*__ymmS3)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS5);   /* - __ymmS5  */  \
__ymm0 = _mm256_mul_ps(__ymmS7,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);   \
__ymm0 = _mm256_mul_ps(__ymmS6,__ymm2);	 \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /*  - (0.7071*__ymmS7 + 0.7071*__ymmS6)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS8); /* -__ymmS8  */  \
__ymm0 = _mm256_mul_ps(__ymmS11,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS10,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /* + (0.7071*__ymmS11 - 0.7071*__ymmS10)  */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS13); /* + __ymmS13  */  \
__ymm0 = _mm256_mul_ps(__ymmS14,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS15,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0); /* + ( 0.7071*__ymmS14 + 0.7071*__ymmS15)  */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____, __ymm3);  ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /*  8th output octect vector ----real part  */  \
____pfCurrTMP_IQPtr____ = __pfDataIQVEC_OUT__  +__nDataInterlvrGAP__;  \
__ymm1 = _mm256_loadu_ps(__pfCurr1stSrcOctVEC__ +8);  /* load imaginary part of the 1st octect vector  */  \
__ymm0 = _mm256_mul_ps(__ymmS3,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm1,__ymm0); \
__ymm0 = _mm256_mul_ps(__ymmS2,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  /* + j*( 0.7071*__ymmS3 - 0.7071*__ymmS2)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS4);   /* - j*__ymmS4  */  \
__ymm0 = _mm256_mul_ps(__ymmS7,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);   \
__ymm0 = _mm256_mul_ps(__ymmS6,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /* - j*( 0.7071*__ymmS6 + 0.7071*__ymmS7) */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS9); /*  -j*__ymmS9  */  \
__ymm0 = _mm256_mul_ps(__ymmS10,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0); \
__ymm0 = _mm256_mul_ps(__ymmS11,__ymm2); \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /* + j*( 0.7071*__ymmS10 - 0.7071*__ymmS11)  */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS12); /* + j*__ymmS12  */  \
__ymm0 = _mm256_mul_ps(__ymmS14,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS15,__ymm2); \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0); /* + j*(0.7071*__ymmS14 + 0.7071*__ymmS15)  */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);   ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /*  2nd output octect vector ----imag part  */  \
__ymm0 = _mm256_mul_ps(__ymmS2,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm1,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS3,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  /* - j*( 0.7071*__ymmS2 + 0.7071*__ymmS3)  */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS4); /* + j*__ymmS4  */  \
__ymm0 = _mm256_mul_ps(__ymmS7,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);   \
__ymm0 = _mm256_mul_ps(__ymmS6,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  /*  + j*( 0.7071*__ymmS7 - 0.7071*__ymmS6) */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS9); /* -j*__ymmS9  */  \
__ymm0 = _mm256_mul_ps(__ymmS10,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS11,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0); 	 /* + j*( 0.7071*__ymmS10 + 0.7071*__ymmS11) */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS12); /*  - j*__ymmS12  */  \
__ymm0 = _mm256_mul_ps(__ymmS14,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS15,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);   /* + j*(0.7071*__ymmS14 - 0.7071*__ymmS15)  */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);   ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__; /*  4th output octect vector ----imag part  */  \
__ymm0 = _mm256_mul_ps(__ymmS3,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm1,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS2,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  /* + j*(0.7071*__ymmS2 - 0.7071*__ymmS3)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS4);  /* - j*__ymmS4  */  \
__ymm0 = _mm256_mul_ps(__ymmS6,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS7,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0); 	 /* +  (0.7071*__ymmS6 + 0.7071*__ymmS7)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS9); /*  -j*__ymmS9  */  \
__ymm0 = _mm256_mul_ps(__ymmS11,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS10,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  	 /* + j*( 0.7071*__ymmS11 - 0.7071*__ymmS10)  */  \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS12); /*  + j*__ymmS12  */  \
__ymm0 = _mm256_mul_ps(__ymmS15,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS14,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);    /* - j*(0.7071*__ymmS14 + 0.7071*__ymmS15)  */   \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);   ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /*  6th output octect vector ----imag part  */  \
__ymm0 = _mm256_mul_ps(__ymmS3,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm1,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS2,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  /* + j*( 0.7071*__ymmS2 + 0.7071*__ymmS3)  */ \
__ymm3 = _mm256_add_ps(__ymm3,__ymmS4); /* + j*__ymmS4  */  \
__ymm0 = _mm256_mul_ps(__ymmS6,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS7,__ymm2); \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /*  + j*( 0.7071*__ymmS6 - 0.7071*__ymmS7)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS9); /* -j*__ymmS9  */  \
__ymm0 = _mm256_mul_ps(__ymmS10,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS11,__ymm2); \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0); /* - j*( 0.7071*__ymmS10 + 0.7071*__ymmS11)  */  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymmS12); /*  - j*__ymmS12  */  \
__ymm0 = _mm256_mul_ps(__ymmS14,__ymm2);  \
__ymm3 = _mm256_sub_ps(__ymm3,__ymm0);  \
__ymm0 = _mm256_mul_ps(__ymmS15,__ymm2);  \
__ymm3 = _mm256_add_ps(__ymm3,__ymm0);  /* + j*(0.7071*__ymmS15 - 0.7071*__ymmS14)  */  \
_mm256_storeu_ps(____pfCurrTMP_IQPtr____ + 8, __ymm3);   ____pfCurrTMP_IQPtr____ += 2*__nDataInterlvrGAP__;  /* 8th output octect vector ----imag part */




#define MICROXXX_AVX_LoadA_MUL_B_REL( ____ymmA_I____, ____ymmA_Q____,__pfSrcIVEC__, __pfSrcQVEC__, ____ymmB_I____, ____ymmB_Q____, ____ymmTmp0____, ____ymmTmp1____)  \
____ymmA_I____  = _mm256_loadu_ps(__pfSrcIVEC__);                       /* load src I vector */   \
____ymmA_Q____ = _mm256_loadu_ps(__pfSrcQVEC__);                        /* load src Q vector */   \
____ymmTmp0____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_I____); \
____ymmTmp1____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_sub_ps(____ymmA_I____, ____ymmTmp1____); \
____ymmA_Q____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_I____); \
____ymmA_Q____ = _mm256_add_ps(____ymmA_Q____, ____ymmTmp0____); 


#define MICROXXX_AVX_A_MUL_B_OnSITE( ____ymmA_I____, ____ymmA_Q____, ____ymmB_I____, ____ymmB_Q____, ____ymmTmp0____, ____ymmTmp1____)  \
____ymmTmp0____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_I____); \
____ymmTmp1____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_sub_ps(____ymmA_I____, ____ymmTmp1____); \
____ymmA_Q____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_I____); \
____ymmA_Q____ = _mm256_add_ps(____ymmA_Q____, ____ymmTmp0____); 


#define MICROXXX_AVX_A_MUL_CxConst_OnSITE( ____ymmA_I____, ____ymmA_Q____,____Const_I____,____Const_Q____,____ymmB_I____, ____ymmB_Q____, ____ymmTmp0____, ____ymmTmp1____)  \
____ymmB_I____ = _mm256_set1_ps(____Const_I____);    \
____ymmB_Q____ = _mm256_set1_ps(____Const_Q____);    \
____ymmTmp0____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_I____); \
____ymmTmp1____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_sub_ps(____ymmA_I____, ____ymmTmp1____); \
____ymmA_Q____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_I____); \
____ymmA_Q____ = _mm256_add_ps(____ymmA_Q____, ____ymmTmp0____); 


#define MICROXXX_HADD_DualQuad(__ymmOut__, __ymmA__, __ymmB__,__ymmTMP__ ) \
__ymmOut__ = _mm256_permute2f128_ps(__ymmA__,__ymmB__, 0x20); /* 00 10 00 00 */ \
__ymmTMP__ = _mm256_permute2f128_ps(__ymmA__,__ymmB__, 0x31); /* 00 11 00 01 */ \
__ymmOut__ = _mm256_add_ps(__ymmOut__,__ymmTMP__);


#define MICROXXX_EXCHANGE( ____AA____, ____BB____, ____TMP____) \
____TMP____ = ____AA____;  ____AA____ =  ____BB____;  ____BB____ = ____TMP____;


#define MICROXXX_AVX_SPLIT_01452367_IQ(__ymmOutI__,__ymmOutQ__,__ymmIQ1__,__ymmIQ2__) \
__ymmOutI__=_mm256_shuffle_ps(__ymmIQ1__,__ymmIQ2__,0x88);  /* 10 00 10 00 ==> i0 i1 i4 i5   i2 i3 i6 i7 */ \
__ymmOutQ__=_mm256_shuffle_ps(__ymmIQ1__,__ymmIQ2__,0xdd);  /* 11 01 11 01 ==> q0 q1 q4 q5   q2 q3 q6 q7 */ 



#define MICROXXX_AVX_A_MUL_B(____ymmOutI____,  ____ymmOutQ____, ____ymmA_I____, ____ymmA_Q____, ____ymmB_I____, ____ymmB_Q____, ____ymmTmp____)  \
____ymmOutI____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_I____); \
____ymmTmp____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_Q____); \
____ymmOutI____ = _mm256_sub_ps(____ymmOutI____, ____ymmTmp____); \
____ymmOutQ____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_Q____); \
____ymmTmp____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_I____); \
____ymmOutQ____ = _mm256_add_ps(____ymmOutQ____, ____ymmTmp____); 

#define MICROXXX_AVX_A_MUL_B_OnSITE( ____ymmA_I____, ____ymmA_Q____, ____ymmB_I____, ____ymmB_Q____, ____ymmTmp0____, ____ymmTmp1____)  \
____ymmTmp0____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_I____); \
____ymmTmp1____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_sub_ps(____ymmA_I____, ____ymmTmp1____); \
____ymmA_Q____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_I____); \
____ymmA_Q____ = _mm256_add_ps(____ymmA_Q____, ____ymmTmp0____); 





#endif // __FFT_V_H

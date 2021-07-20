
#ifndef __PERF_METRIC_COMMavx_H
#define __PERF_METRIC_COMMavx_H
/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */


#define MICRO_AVX_ABS(__ymmABS__, __ymmSRC__,__ymmT__) __ymmT__ = _mm256_set1_ps(-0.f); __ymmABS__ = _mm256_andnot_ps(__ymmT__, __ymmSRC__);

#define AVX_IF_ELSE_ADD(_ymmOUT, _ymmMASK, _ymmIF, _ymmELSE, _ymmTMP ) \
_ymmTMP = _mm256_and_ps(_ymmMASK, _ymmIF);   _ymmOUT = _mm256_andnot_ps(_ymmMASK,_ymmELSE);  _ymmOUT = _mm256_add_ps(_ymmOUT,_ymmTMP);

#define AVX_IF_ELSE_ADDS(_ymmIF, _ymmELSE, _ymmMASK,  _ymmTMP ) \
_ymmTMP = _mm256_and_ps(_ymmMASK, _ymmIF);   _ymmIF = _mm256_andnot_ps(_ymmMASK,_ymmELSE);  _ymmIF = _mm256_add_ps(_ymmIF,_ymmTMP);





#define MICRO_AVX_IF_ELSE_OP(__ymmOUT,__ymmA, __ymmB_CMP, __CMP_OP__ , __ymmIF, __ymmELSE, __ymmT0 ) \
__ymmT0 = _mm256_cmp_ps(__ymmA, __ymmB_CMP, __CMP_OP__); \
__ymmOUT = _mm256_and_ps(__ymmT0, __ymmIF); \
__ymmT0 = _mm256_andnot_ps(__ymmT0, __ymmELSE); \
__ymmOUT = _mm256_add_ps(__ymmOUT, __ymmT0);


#define MICRO_EXCHANGE( ____AA____, ____BB____, ____TMP____) \
____TMP____ = ____AA____;  ____AA____ =  ____BB____;  ____BB____ = ____TMP____;

#define MICRO_CxA_ADD_CxB(____OutI____, ____OutQ____, ____A_I____, ____A_Q____,____B_I____, ____B_Q____) \
____OutI____ =  (____A_I____) + (____B_I____) ; \
____OutQ____ =  (____A_Q____) + (____B_Q____);

#define MICRO_CxA_SUB_CxB(____OutI____, ____OutQ____, ____A_I____, ____A_Q____,____B_I____, ____B_Q____) \
____OutI____ =  (____A_I____) - (____B_I____) ; \
____OutQ____ =  (____A_Q____) - (____B_Q____);

#define MICRO_CxA_MUL_CxB(____OutI____, ____OutQ____, ____A_I____, ____A_Q____,____B_I____, ____B_Q____) \
____OutI____ =  (____A_I____)*(____B_I____) - (____A_Q____)*(____B_Q____); \
____OutQ____ =  (____A_I____)*(____B_Q____) + (____A_Q____)*(____B_I____);

#define MICRO_CxA_MUL_ConjCxB(____OutI____, ____OutQ____, ____A_I____, ____A_Q____,____B_I____, ____B_Q____) \
____OutI____ =  (____A_I____)*(____B_I____) + (____A_Q____)*(____B_Q____); \
____OutQ____ =  (____B_I____)*(____A_Q____) - (____B_Q____)*(____A_I____);


#define AVX_MinusZERO( __ymmMinusZERO__ )  __ymmMinusZERO__ = _mm256_set1_ps(-0.0f);
#define _AVX_GET_SIGN_( __ymmData__, __ymmMinusZERO__ )  _mm256_and_ps(__ymmMinusZERO__, __ymmData__)
#define AVX_ABS_OP( __ymmData__, __ymmMinusZERO__ )  __ymmData__ = _mm256_andnot_ps(__ymmMinusZERO__, __ymmData__);
#define AVX_NEG_OP( __ymmData__, __ymmMinusZERO__ )  __ymmData__ = _mm256_xor_ps(__ymmData__, __ymmMinusZERO__);


#define  MICRO_AVX_modConst(__ymmData,__fInvConst,__fConst, __ymmT1,__ymmT2) \
__ymmT1 = _mm256_set1_ps(__fInvConst);  __ymmT1 = _mm256_mul_ps(__ymmData,__ymmT1); /* X*fInv_2PI ==>__ymmT1 */  \
__ymmT1 = _mm256_round_ps(__ymmT1,(_MM_FROUND_TO_NEG_INF |_MM_FROUND_NO_EXC) );     /* round(X*fInv_2PI) ==> __ymmT1 , round down, and suppress exceptions */ \
__ymmT2 = _mm256_set1_ps(__fConst);     __ymmT1 = _mm256_mul_ps(__ymmT1,__ymmT2);   /* round(X*fInv_2PI)*2PI ==> __ymmT1 */   \
__ymmData = _mm256_sub_ps(__ymmData, __ymmT1);                                      /*  X - round(X*fInv_2PI)*2PI ==> __ymmData */



#define MICRO_AVX_2PI_to_halfPI(__ymmData, __ymmTMP1,__ymmTMP2) \
__ymmTMP1 = _mm256_set1_ps(_PI_);   __ymmData = _mm256_sub_ps(__ymmData, __ymmTMP1);                     /* x =  X - PI ==>__ymmData, from (0~2PI) to ( -PI ~ PI ) */ \
__ymmTMP1 = _mm256_set1_ps(-1*__HalfPI__);    __ymmTMP2 = _mm256_cmp_ps(__ymmData,__ymmTMP1,_CMP_LT_OS); /* mask( if( x < -0.5PI)) ==> __ymmTMP2  */ \
__ymmTMP1 = _mm256_set1_ps(-1*_PI_);          __ymmTMP1 = _mm256_sub_ps(__ymmTMP1,__ymmData);            /* x = -PI - x ==>__ymmTMP1  */  \
__ymmTMP1 = _mm256_and_ps(__ymmTMP2,__ymmTMP1);                                                          /* if ( x < -0.5PI ){ x = -PI - x; } ==> __ymmTMP1 */ \
__ymmData = _mm256_andnot_ps(__ymmTMP2,__ymmData);                                                       /* else { x = x } ==> __ymmData  */ \
__ymmData = _mm256_add_ps( __ymmData,__ymmTMP1);                                                         /* if ( x < -0.5PI ){ x = -PI - x; } else { x = x; } */ \
__ymmTMP1 = _mm256_set1_ps(__HalfPI__);       __ymmTMP2 = _mm256_cmp_ps(__ymmData,__ymmTMP1,_CMP_GT_OS); /* mask( if( x > 0.5PI)) ==> __ymmTMP2  */ \
__ymmTMP1 = _mm256_set1_ps(_PI_);             __ymmTMP1 = _mm256_sub_ps(__ymmTMP1,__ymmData);            /* x = PI - x ==>__ymmTMP1  */  \
__ymmTMP1 = _mm256_and_ps(__ymmTMP2,__ymmTMP1);                                                          /* if ( x > 0.5PI ){ x = PI - x; } ==> __ymmTMP1  */ \
__ymmData = _mm256_andnot_ps(__ymmTMP2,__ymmData);                                                       /* else { x = x } ==> __ymmData   */ \
__ymmData = _mm256_add_ps( __ymmData,__ymmTMP1);                                                         /* if ( x > 0.5PI  ){ x = PI -  x; } else { x = x; }  */



/*  sin(X) =  -1*sin(x) = -1*(x - fInv_6*x^3 + fInv_120*x^5 - fInv_5040*x^7) = -1.0*x + fInv_6*x^3 - fInv_120*x^5 + fInv_5040*x^7;  */
#define MICRO_AVX_Sine_halfPI_range(__ymmSine,__ymmData, __ymmTMP1,__ymmTMP2, __ymmTMP3) \
__ymmTMP1 = _mm256_mul_ps(__ymmData,__ymmData);  /* x*x ==>__ymmTMP1  */  \
__ymmTMP3 = _mm256_set1_ps(0.166666666666667);   /* fInv_6   */  \
__ymmTMP2 = _mm256_mul_ps(__ymmData,__ymmTMP1);  /* x^3 ==>__ymmTMP2  */  \
__ymmTMP3 = _mm256_mul_ps(__ymmTMP3,__ymmTMP2);  /* fInv_6*x^3 ==>__ymmTMP3  */ \
__ymmSine = _mm256_sub_ps(__ymmTMP3,__ymmData);   /* -x + fInv_6*x^3 ==> __ymmSine */ \
__ymmTMP2 = _mm256_mul_ps(__ymmTMP1,__ymmTMP2);  /* x^5 ==> __ymmTMP2   */  \
__ymmTMP3 = _mm256_set1_ps(0.00833333333333333); /* fInv_120*/  \
__ymmTMP3 = _mm256_mul_ps(__ymmTMP3,__ymmTMP2);  /* fInv_120*x^5==>__ymmTMP3  */ \
__ymmSine = _mm256_sub_ps(__ymmSine,__ymmTMP3);    /* -x + fInv_6*x^3  - fInv_120*x^5 ==> __ymmSine */  \
__ymmTMP2 = _mm256_mul_ps(__ymmTMP2,__ymmTMP1);  /* x^7 ==>__ymmTMP1  */ \
__ymmTMP3 = _mm256_set1_ps(1.98412698412698e-04);/* fInv_5040 = 1.0/5040 */   \
__ymmTMP3 = _mm256_mul_ps(__ymmTMP3,__ymmTMP2);  /* fInv_5040*x^7 ==> __ymmTMP3  */ \
__ymmSine = _mm256_add_ps(__ymmSine,__ymmTMP3);    /* -x + fInv_6*x^3 -  fInv_120*x^5 + fInv_5040*x^7  ==> __ymmSine */


#define MICRO_AVX_SPLIT_IQ_ONSITE(__ymmOutI__,__ymmOutQ__,__ymmIQ1__,__ymmIQ2__,__ymmTMP1__,__ymmTMP2__) \
__ymmTMP1__ = _mm256_permute2f128_ps(__ymmIQ1__,__ymmIQ2__,0x20); /* i0 q0 i1 q1 i4 q4 i5 q5    */  \
__ymmTMP2__ = _mm256_permute2f128_ps(__ymmIQ1__,__ymmIQ2__,0x31); /* i2 q2 i3 q3 i6 q6 i7 q7  */  \
__ymmOutI__ = _mm256_shuffle_ps(__ymmTMP1__,__ymmTMP2__,0x88 );   /* 10 00 10 00==>0x88 ::: i0 i1 i2 i3 i4 i5 i6 i7 */  \
__ymmOutQ__ = _mm256_shuffle_ps(__ymmTMP1__,__ymmTMP2__,0xdd );   /* 11 01 11 01==>0xdd ::: q0 q1 q2 q3 q4 q5 q6 q7 */  


#define MICRO_AVX_MERGE_IQ_ONSITE(__ymmOutIQ1__,__ymmOutIQ2__,__ymmI__,__ymmQ__,__ymmTMP1__,__ymmTMP2__) \
__ymmTMP1__ = _mm256_shuffle_ps(__ymmI__,__ymmQ__,0x44);          /* 01 00 01 00==>0x44 ::: i0 i1 q0 q1 i4 i5 q4 q5    */  \
__ymmTMP2__ = _mm256_shuffle_ps(__ymmI__,__ymmQ__,0xee);          /* 11 10 11 10==>0xee ::: i2 i3 q2 q3 i6 i7 q6 q7    */  \
__ymmTMP1__ = _mm256_shuffle_ps(__ymmTMP1__,__ymmTMP1__,0xd8 );   /* 11 01 10 00==>0xd8 ::: i0 q0 i1 q1 i4 q4 i5 q5    */  \
__ymmTMP2__ = _mm256_shuffle_ps(__ymmTMP2__,__ymmTMP2__,0xd8 );   /* 11 01 10 00==>0xd8 ::: i2 q2 i3 q3 i6 q6 i7 q7    */  \
__ymmOutIQ1__ = _mm256_permute2f128_ps(__ymmTMP1__,__ymmTMP2__,0x20); /* i0 q0 i1 q1 i2 q2 i3 q3    */  \
__ymmOutIQ2__ = _mm256_permute2f128_ps(__ymmTMP1__,__ymmTMP2__,0x31); /* i4 q4 i5 q5 i6 q6 i7 q7    */  

#define MICRO_AVX_SPLIT_01452367_IQ(__ymmOutI__,__ymmOutQ__,__ymmIQ1__,__ymmIQ2__) \
__ymmOutI__=_mm256_shuffle_ps(__ymmIQ1__,__ymmIQ2__,0x88);  /* 10 00 10 00 ==> i0 i1 i4 i5   i2 i3 i6 i7 */ \
__ymmOutQ__=_mm256_shuffle_ps(__ymmIQ1__,__ymmIQ2__,0xdd);  /* 11 01 11 01 ==> q0 q1 q4 q5   q2 q3 q6 q7 */ 

#define MICRO_AVX_MERGE_01452367_IQ(__ymmOutIQ1__,__ymmOutIQ2__,__ymmI__,__ymmQ__,__ymm0__) \
__ymm0__ = _mm256_shuffle_ps(__ymmI__,__ymmQ__,0x44 );      /* 01  00  01 00 ==> i0 i1 q0 q1 i2 i3 q2 q3 */ \
__ymmOutIQ1__ = _mm256_shuffle_ps(__ymm0__,__ymm0__, 0xd8); /* 11  01  10 00 ==> i0 q0 i1 q1 i2 q2 i3 q3 */ \
__ymm0__ = _mm256_shuffle_ps(__ymmI__,__ymmQ__,0xee );      /* 11  10  11 10 ==> i4 i5 q4 q5 i6 i7 q6 q7 */ \
__ymmOutIQ2__ = _mm256_shuffle_ps(__ymm0__,__ymm0__, 0xd8); /* 11  01  10 00 ==> i4 q4 i5 q5 i6 q6 i7 q7  __ymmOutIQ1__==>__ymmOutIQ2__ ,bug fixed in 2017-12-25@home */ 



#define MICRO_AVX_A_ADD_B_OnSITE(____ymmOutI____, ____ymmOutQ____, ____ymmA_I____, ____ymmA_Q____,____ymmB_I____, ____ymmB_Q____) \
____ymmOutI____ = _mm256_add_ps(____ymmA_I____,____ymmB_I____); \
____ymmOutQ____= _mm256_add_ps(____ymmA_Q____,____ymmB_Q____); 


#define MICRO_AVX_A_SUB_B_OnSITE(____ymmOutI____, ____ymmOutQ____, ____ymmA_I____, ____ymmA_Q____,____ymmB_I____, ____ymmB_Q____) \
____ymmOutI____ = _mm256_sub_ps(____ymmA_I____,____ymmB_I____); \
____ymmOutQ____= _mm256_sub_ps(____ymmA_Q____,____ymmB_Q____); 


#define MICRO_AVX_IQ_POWER(__ymmPwr__,__ymmI__,__ymmQ__,__ymmTMP__) \
__ymmPwr__ = _mm256_mul_ps(__ymmI__,__ymmI__); \
__ymmTMP__ = _mm256_mul_ps(__ymmQ__,__ymmQ__); \
__ymmPwr__ = _mm256_add_ps(__ymmPwr__,__ymmTMP__);

#define MICRO_AVX_IQ_POWER_S(__ymmIinout__,__ymmQtmp__) \
__ymmIinout__ = _mm256_mul_ps(__ymmIinout__,__ymmIinout__); \
__ymmQtmp__ = _mm256_mul_ps(__ymmQtmp__,__ymmQtmp__); \
__ymmIinout__ = _mm256_add_ps(__ymmIinout__,__ymmQtmp__);
                       

#define MICRO_AVX_A_MUL_B(____ymmOutI____,  ____ymmOutQ____, ____ymmA_I____, ____ymmA_Q____, ____ymmB_I____, ____ymmB_Q____, ____ymmTmp____)  \
____ymmOutI____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_I____); \
____ymmTmp____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_Q____); \
____ymmOutI____ = _mm256_sub_ps(____ymmOutI____, ____ymmTmp____); \
____ymmOutQ____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_Q____); \
____ymmTmp____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_I____); \
____ymmOutQ____ = _mm256_add_ps(____ymmOutQ____, ____ymmTmp____); 

#define MICRO_AVX_A_MUL_B_OnSITE( ____ymmA_I____, ____ymmA_Q____, ____ymmB_I____, ____ymmB_Q____, ____ymmTmp0____, ____ymmTmp1____)  \
____ymmTmp0____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_I____); \
____ymmTmp1____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_sub_ps(____ymmA_I____, ____ymmTmp1____); \
____ymmA_Q____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_I____); \
____ymmA_Q____ = _mm256_add_ps(____ymmA_Q____, ____ymmTmp0____); 

#define MICRO_AVX_A_MUL_CxConst_OnSITE( ____ymmA_I____, ____ymmA_Q____,____Const_I____,____Const_Q____,____ymmB_I____, ____ymmB_Q____, ____ymmTmp0____, ____ymmTmp1____)  \
____ymmB_I____ = _mm256_set1_ps(____Const_I____);    \
____ymmB_Q____ = _mm256_set1_ps(____Const_Q____);    \
____ymmTmp0____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_I____); \
____ymmTmp1____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_sub_ps(____ymmA_I____, ____ymmTmp1____); \
____ymmA_Q____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_I____); \
____ymmA_Q____ = _mm256_add_ps(____ymmA_Q____, ____ymmTmp0____); 


#define MICRO_AVX_A_MUL_Const(__pfOutIVEC__, __pfOutQVEC__, __pfSrcIVEC__, __pfSrcQVEC__, __fConstI__,__fConstQ__,__ymm0__,__ymm1__,__ymm2__,__ymm3__,__ymm4__,__ymm5__) \
__ymm0__ = _mm256_loadu_ps(__pfSrcIVEC__);                 /* load src I vector */   \
__ymm1__ = _mm256_loadu_ps(__pfSrcQVEC__);            /* load src Q vector */   \
__ymm2__ = _mm256_set1_ps(__fConstI__);   \
__ymm3__ = _mm256_set1_ps(__fConstQ__);	\
__ymm4__ = _mm256_mul_ps(__ymm0__, __ymm2__);  \
__ymm5__ = _mm256_mul_ps(__ymm1__, __ymm3__);  /* use __ymm5__ as buffer */ \
__ymm4__ = _mm256_sub_ps(__ymm4__, __ymm5__);  \
__ymm5__ = _mm256_mul_ps(__ymm0__, __ymm3__);  \
__ymm2__ = _mm256_mul_ps(__ymm1__, __ymm2__);  /* destroy __ymm2__,which is defined as __fConstI__ */   \
__ymm5__ = _mm256_add_ps(__ymm5__, __ymm2__);  \
_mm256_storeu_ps(__pfOutIVEC__,__ymm4__);   \
_mm256_storeu_ps(__pfOutQVEC__,__ymm5__);   

/* 
Change History
1st version designed by Duan Weiming in 2016-05-22
*/
#define MICRO_AVX_SumMUL_1CXVEC(__xmmOUT,__ymmA_I,__ymmA_Q,__ymmB_I,__ymmB_Q, __ymm0,__ymm1,__ymm2,__xmm0) \
__ymm0 = _mm256_mul_ps(__ymmA_I,__ymmB_I); \
__ymm1 = _mm256_mul_ps(__ymmA_Q,__ymmB_Q); \
__ymm2 = _mm256_sub_ps(__ymm0,__ymm1);  \
__ymm0 = _mm256_mul_ps(__ymmA_I,__ymmB_Q); \
__ymm1 = _mm256_mul_ps(__ymmA_Q,__ymmB_I); \
__ymm1 = _mm256_add_ps(__ymm0,__ymm1);  \
__ymm0 = _mm256_permute2f128_ps (__ymm2, __ymm1, 0x20);  /*    0010  0000   i0~i3 q0~q3  */ \
__ymm1 = _mm256_permute2f128_ps (__ymm2, __ymm1, 0x31);  /*    0011  0001   i4~i7 q4~q7  */ \
__ymm0 = _mm256_add_ps(__ymm0,__ymm1);   /* i0~i3 q0~q3 */ \
__xmmOUT = _mm256_extractf128_ps(__ymm0,0x00); /* get low 128bits   1 cycle / 1 TP */ \
__xmm0 = _mm256_extractf128_ps(__ymm0,0x01); /* get high 128bits */ \
__xmmOUT = _mm_hadd_ps(__xmmOUT,__xmm0); /* x0~x1 y0~y1 */ \
__xmmOUT = _mm_hadd_ps(__xmmOUT,__xmmOUT); /* x0 y0 x0 y0 */


#define MICRO_AVX_SumMUL_4CXVEC(__ymm0,__ymmA_I,__ymmA_Q,__ymmB_I,__ymmB_Q,__ymmC_I,__ymmC_Q,__ymmD_I,__ymmD_Q,__ymmE_I,__ymmE_Q, __ymm1,__ymm2,__ymm3,__ymm4) \
__ymm0 = _mm256_mul_ps(__ymmA_I,__ymmB_I); \
__ymm1 = _mm256_mul_ps(__ymmA_Q,__ymmB_Q); \
__ymm2 = _mm256_sub_ps(__ymm0,__ymm1);  \
__ymm0 = _mm256_mul_ps(__ymmA_I,__ymmB_Q); \
__ymm1 = _mm256_mul_ps(__ymmA_Q,__ymmB_I); \
__ymm1 = _mm256_add_ps(__ymm0,__ymm1);  \
__ymm0 = _mm256_permute2f128_ps (__ymm2, __ymm1, 0x20);  /*    0010  0000   i0~i3 q0~q3  */ \
__ymm1 = _mm256_permute2f128_ps (__ymm2, __ymm1, 0x31);  /*    0011  0001   i4~i7 q4~q7  */ \
__ymm3 = _mm256_add_ps(__ymm0,__ymm1);   /* i0_4 q0_4 */ \
__ymm0 = _mm256_mul_ps(__ymmA_I,__ymmC_I); \
__ymm1 = _mm256_mul_ps(__ymmA_Q,__ymmC_Q); \
__ymm2 = _mm256_sub_ps(__ymm0,__ymm1);  \
__ymm0 = _mm256_mul_ps(__ymmA_I,__ymmC_Q); \
__ymm1 = _mm256_mul_ps(__ymmA_Q,__ymmC_I); \
__ymm1 = _mm256_add_ps(__ymm0,__ymm1);  \
__ymm0 = _mm256_permute2f128_ps (__ymm2, __ymm1, 0x20);  /*    0010  0000   i0~i3 q0~q3 */ \
__ymm1 = _mm256_permute2f128_ps (__ymm2, __ymm1, 0x31);  /*    0011  0001   i4~i7 q4~q7 */ \
__ymm0 = _mm256_add_ps(__ymm0,__ymm1); /* i1_4 q1_4 */ \
__ymm1 = _mm256_permute2f128_ps (__ymm3, __ymm0, 0x20);  /*    0010  0000   i0_4 i1_4  */ \
__ymm4 = _mm256_permute2f128_ps (__ymm3, __ymm0, 0x31);  /*    0011  0001   q0_4 q1_4  */ \
__ymm4 = _mm256_hadd_ps(__ymm1,__ymm4);   /*  i0_2 q0_2 i1_2 q1_2 */ \
__ymm0 = _mm256_mul_ps(__ymmA_I,__ymmD_I); \
__ymm1 = _mm256_mul_ps(__ymmA_Q,__ymmD_Q); \
__ymm2 = _mm256_sub_ps(__ymm0,__ymm1);  \
__ymm0 = _mm256_mul_ps(__ymmA_I,__ymmD_Q); \
__ymm1 = _mm256_mul_ps(__ymmA_Q,__ymmD_I); \
__ymm1 = _mm256_add_ps(__ymm0,__ymm1);  \
__ymm0 = _mm256_permute2f128_ps (__ymm2, __ymm1, 0x20);  /*    0010  0000   i0~i3 q0~q3  */ \
__ymm1 = _mm256_permute2f128_ps (__ymm2, __ymm1, 0x31);  /*    0011  0001   i4~i7 q4~q7  */ \
__ymm3 = _mm256_add_ps(__ymm0,__ymm1);   /* i2_4 q2_4 */ \
__ymm0 = _mm256_mul_ps(__ymmA_I,__ymmE_I); \
__ymm1 = _mm256_mul_ps(__ymmA_Q,__ymmE_Q); \
__ymm2 = _mm256_sub_ps(__ymm0,__ymm1);  \
__ymm0 = _mm256_mul_ps(__ymmA_I,__ymmE_Q); \
__ymm1 = _mm256_mul_ps(__ymmA_Q,__ymmE_I); \
__ymm1 = _mm256_add_ps(__ymm0,__ymm1);  \
__ymm0 = _mm256_permute2f128_ps (__ymm2, __ymm1, 0x20);  /*    0010  0000   i0~i3 q0~q3 */ \
__ymm1 = _mm256_permute2f128_ps (__ymm2, __ymm1, 0x31);  /*    0011  0001   i4~i7 q4~q7 */ \
__ymm0 = _mm256_add_ps(__ymm0,__ymm1); /* i3_4 q3_4 */ \
__ymm1 = _mm256_permute2f128_ps (__ymm3, __ymm0, 0x20);  /*    0010  0000   i2_4 i3_4  */ \
__ymm3 = _mm256_permute2f128_ps (__ymm3, __ymm0, 0x31);  /*    0011  0001   q2_4 q3_4  */ \
__ymm1 = _mm256_hadd_ps(__ymm1,__ymm3);   /*  i2_2 q2_2 i3_2 q3_2 */ \
__ymm0 = _mm256_permute2f128_ps (__ymm4, __ymm1, 0x20);  /*    0010  0000   i0_2 q0_2 i2_2 q2_2  */ \
__ymm4 = _mm256_permute2f128_ps (__ymm4, __ymm1, 0x31);  /*    0011  0001   i1_2 q1_2 i3_2 q3_2  */ \
__ymm0 = _mm256_hadd_ps(__ymm0,__ymm4); /* i0 q0 i1 q1 i2 q2 i3 q3 */


#define MICRO_AVX_SUM_A_MUL_Const(__ymmOutI, __ymmOutQ, __pfSrcIVEC__, __pfSrcQVEC__, __fConstI__,__fConstQ__,__ymm0__,__ymm1__,__ymm2__,__ymm3__,__ymm4__,__ymm5__) \
__ymm0__ = _mm256_loadu_ps(__pfSrcIVEC__);                 /* load src I vector */   \
__ymm1__ = _mm256_loadu_ps(__pfSrcQVEC__);            /* load src Q vector */   \
__ymm2__ = _mm256_set1_ps(__fConstI__);   \
__ymm3__ = _mm256_set1_ps(__fConstQ__);	\
__ymm4__ = _mm256_mul_ps(__ymm0__, __ymm2__);  \
__ymm5__ = _mm256_mul_ps(__ymm1__, __ymm3__);  /* use __ymm5__ as buffer */ \
__ymm4__ = _mm256_sub_ps(__ymm4__, __ymm5__);  \
__ymm5__ = _mm256_mul_ps(__ymm0__, __ymm3__);  \
__ymm2__ = _mm256_mul_ps(__ymm1__, __ymm2__);  /* destroy __ymm2__,which is defined as __fConstI__ */   \
__ymm5__ = _mm256_add_ps(__ymm5__, __ymm2__);  \
__ymmOutI = _mm256_add_ps(__ymmOutI,__ymm4__);   \
__ymmOutQ = _mm256_add_ps(__ymmOutQ,__ymm5__);   


#define MICRO_AVX_LoadA_MUL_B_REL( ____ymmA_I____, ____ymmA_Q____,__pfSrcIVEC__, __pfSrcQVEC__, ____ymmB_I____, ____ymmB_Q____, ____ymmTmp0____, ____ymmTmp1____)  \
____ymmA_I____  = _mm256_loadu_ps(__pfSrcIVEC__);                       /* load src I vector */   \
____ymmA_Q____ = _mm256_loadu_ps(__pfSrcQVEC__);                        /* load src Q vector */   \
____ymmTmp0____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_mul_ps(____ymmA_I____, ____ymmB_I____); \
____ymmTmp1____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_Q____); \
____ymmA_I____ = _mm256_sub_ps(____ymmA_I____, ____ymmTmp1____); \
____ymmA_Q____ = _mm256_mul_ps(____ymmA_Q____, ____ymmB_I____); \
____ymmA_Q____ = _mm256_add_ps(____ymmA_Q____, ____ymmTmp0____); 

#define MICRO_AVX_LoadA_MUL_B_REL_X(__ymmOutI__,__ymmOutQ__, __pfSrcIVEC__, __pfSrcQVEC__, __BI__,__BQ__,__ymm0__,__ymm1__,__ymm2__,__ymm3__) \
__ymm0__ = _mm256_loadu_ps(__pfSrcIVEC__);                         /* load src I vector */   \
__ymm1__ = _mm256_loadu_ps(__pfSrcQVEC__);                        /* load src Q vector */   \
__ymmOutQ__ = _mm256_set1_ps(__BI__);                                   /* BI ==>  __ymmOutQ__ */  \
__ymmOutI__ = _mm256_mul_ps(__ymm0__, __ymmOutQ__);        /* srcI * BI ==> __ymmOutI__ */ \
__ymm2__       = _mm256_set1_ps(__BQ__);                                /* BQ ==>  __ymm2__ */  \
__ymm3__ = _mm256_mul_ps(__ymm1__, __ymm2__);                  /*  srcQ * BQ ==> __ymm3__  */ \
__ymmOutI__ = _mm256_sub_ps(__ymmOutI__, __ymm3__);      \
__ymm0__ = _mm256_mul_ps(__ymm0__, __ymm2__);                      /* srcI * BQ ==> __ymm0__ */ \
__ymmOutQ__ = _mm256_mul_ps(__ymm1__, __ymmOutQ__);          /*  srcQ * BI  ==> __ymmOutQ__  */   \
__ymmOutQ__ = _mm256_add_ps(__ymm0__, __ymmOutQ__); 

#define MICRO_SSE_16BITS_MUL(____xmmiOUT____, ____xmmiA____, ____xmmiB____, ____xmmiTMP____, ____FractionalBits____ )  \
____xmmiOUT____ = _mm_mulhi_epi16(____xmmiA____,____xmmiB____); /* high 16 bits */  \
____xmmiOUT____ = _mm_slli_epi16 (____xmmiOUT____ , ____FractionalBits____);  \
____xmmiTMP____ = _mm_mullo_epi16(____xmmiA____,____xmmiB____); /* low 16 bits  */  \
____xmmiTMP____ = _mm_srli_epi16 (____xmmiTMP____ , 16-____FractionalBits____); \
____xmmiOUT____ = _mm_adds_epi16(____xmmiOUT____,____xmmiTMP____);


#define MICRO_GET_16BITS_MASK(____xmmiOutMASK____,____xmmiFillZERO____,____xmmiFillONE____, ____xmmiROOT____, ____low_mask____,____high_mask____)   \
____xmmiOutMASK____ = _mm_shufflelo_epi16(____xmmiROOT____,  ____low_mask____);   \
____xmmiOutMASK____ = _mm_shufflehi_epi16(____xmmiOutMASK____,  ____high_mask____);  \
____xmmiFillZERO____ = _mm_shufflelo_epi16(____xmmiROOT____,  ____low_mask____+0xaa);  /* 0xaa = 10101010 */  \
____xmmiFillZERO____ = _mm_shufflehi_epi16(____xmmiFillZERO____,  ____high_mask____+0xaa);  \
____xmmiFillONE____ = _mm_shufflelo_epi16(____xmmiROOT____,  0xff - ____low_mask____);  /* 0xff = 11111111 */  \
____xmmiFillONE____ = _mm_shufflehi_epi16(____xmmiFillONE____, 0xff -  ____high_mask____); 



#define MICRO_LLR_16BITS_MASK(____xmmiOUT____,____xmmiIN____,____xmmiROOT____,____xmmiTMP0____,____xmmiTMP1____,____xmmiTMP2____,  ____low_mask____,____high_mask____)   \
____xmmiTMP0____ = _mm_shufflelo_epi16(____xmmiROOT____,  ____low_mask____);   \
____xmmiTMP0____ = _mm_shufflehi_epi16(____xmmiTMP0____,  ____high_mask____);             /* set bit1 constellation mask 0xffff */ \
____xmmiTMP1____ = _mm_shufflelo_epi16(____xmmiROOT____,  ____low_mask____+0xaa);     /* 0xaa = 10101010 */  \
____xmmiTMP1____ = _mm_shufflehi_epi16(____xmmiTMP1____,  ____high_mask____+0xaa);    /* set bit1 padding values 0x7fff */  \
____xmmiTMP2____ = _mm_shufflelo_epi16(____xmmiROOT____,  0xff - ____low_mask____);      /* 0xff = 11111111 */  \
____xmmiTMP2____ = _mm_shufflehi_epi16(____xmmiTMP2____, 0xff -  ____high_mask____);     /* set bit0 padding values 0x7fff */   \
____xmmiOUT____ = _mm_and_si128(____xmmiTMP0____,____xmmiIN____);                               /* get the values for mask 0xffff, value of mask 0x0 is set to 0 */  \
____xmmiOUT____ = _mm_adds_epi16(____xmmiOUT____,____xmmiTMP1____);                          /* add the  padding values of 0x7fff for mask 0x0 */ \
____xmmiOUT____ = _mm_minpos_epu16(____xmmiOUT____);                                                   /* get the minimum distance of current bit of 1 */ \
____xmmiTMP0____ = _mm_andnot_si128(____xmmiTMP0____,____xmmiIN____);                       /* get the values for mask 0x00,   value of mask 0xffff is set to 0 */ \
____xmmiTMP0____ = _mm_adds_epi16(____xmmiTMP0____,____xmmiTMP2____);                     /*  add the  padding values of 0x7fff for mask 0xffff */ \
____xmmiTMP0____ = _mm_minpos_epu16(____xmmiTMP0____);                                               /* get the minimum distance of current bit of 0 */ \
____xmmiOUT____ = _mm_subs_epi16(____xmmiTMP0____,____xmmiOUT____);  \
____xmmiOUT____ = _mm_shufflelo_epi16(____xmmiOUT____, 0x00);


#define MICRO_HADD_DualQuad(__ymmOut__, __ymmA__, __ymmB__,__ymmTMP__ ) \
__ymmOut__ = _mm256_permute2f128_ps(__ymmA__,__ymmB__, 0x20); /* 00 10 00 00 */ \
__ymmTMP__ = _mm256_permute2f128_ps(__ymmA__,__ymmB__, 0x31); /* 00 11 00 01 */ \
__ymmOut__ = _mm256_add_ps(__ymmOut__,__ymmTMP__);



/*
//                             X(n)= X_2nd_0(m)*W(N,0n) +  X_2nd_1(m)*W(N,1n) 
//                                      W(N,0n)                       W(N,1n)                   
//0<= m < N/2    n = 0N/2 + m    ....    1                            W(N,m),       
//0<= m < N/2    n = 1N/2 + m   ....     1                           -W(N,m),        

//0<= m < N/2    n = 0N/2 + m  ....    | 1.0000000 + j*0.0000000         1.0000000 + j*0.0000000  |     |X_2nd_0(m)*1      |
//0<= m < N/2    n = 1N/2 + m  ....    | 1.0000000 + j*0.0000000         -1.0000000 + j*0.000000  |     |X_2nd_1(m)*W(N,1m)|   */
#define MICRO_AVX_BASE2_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__, __nDataInterlvrGAP__, \
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

/*
//                             X(n)= X_third_0(m)*W(N,0n) +X_third_1(m)*W(N,1n)   + X_third_2(m)*W(N,2n)   
//                                   W(N,0n)                   W(N,1n)                       W(N,2n)                     
//0<= m < N/3    n = m         ....    1                       W(N,m),                       W(N,2m),      
//0<= m < N/3    n = 1N/3 + m  ....    1        exp(-j*PI*2/3)*W(N,m),        exp(-j*PI*4/3)*W(N,2m),      
//0<= m < N/3    n = 2N/3 + m  ....    1        exp(-j*PI*4/3)*W(N,m),        exp(-j*PI*8/3)*W(N,2m),      

//0<= m < N/3    n = m         ....    | 1.0000000 + j*0.0000000         1.0000000 + j*0.0000000          1.0000000 + j*0.0000000  |     |X_third_0(m)*W(N,0m)|
//0<= m < N/3    n = 1N/3 + m  ....    | 1.0000000 + j*0.0000000         -0.500000 - j*0.8660254          -0.500000 + j*0.8660254  |     |X_third_1(m)*W(N,1m)|
//0<= m < N/3    n = 2N/3 + m  ....    | 1.0000000 + j*0.0000000         -0.500000 + j*0.8660254          -0.500000 - j*0.8660254  |     |X_third_2(m)*W(N,2m)|  */
#define MICRO_AVX_BASE3_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__, __nDataInterlvrGAP__, \
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


/*
//1.0000000000+j* 0.0000000000     1.0000000000+j* 0.0000000000       1.0000000000+j* 0.0000000000      1.0000000000+j* 0.0000000000      1.0000000000+j* 0.0000000000     
//1.0000000000+j* 0.0000000000     0.3090169944 - j* 0.9510565163     -0.8090169944 -j*0.5877852523     -0.8090169944+j*0.5877852523      0.3090169944 + j* 0.9510565163
//1.0000000000+j* 0.0000000000     -0.8090169944 -j*0.5877852523      0.3090169944 + j* 0.9510565163    0.3090169944 - j* 0.9510565163    -0.8090169944+j*0.5877852523
//1.0000000000+j* 0.0000000000     -0.8090169944+j*0.5877852523       0.3090169944 - j* 0.9510565163     0.3090169944+ j* 0.9510565163    -0.8090169944 -j*0.5877852523 
//1.0000000000+j* 0.0000000000     0.3090169944 + j* 0.9510565163     -0.8090169944+j*0.5877852523      -0.8090169944 -j*0.5877852523     0.3090169944 - j* 0.9510565163    */
#define MICRO_AVX_BASE5_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__,  __nDataInterlvrGAP__, \
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




/*
//1.00000000 + j*0.0000000    1.00000000 + j*0.0000000       1.00000000 + j*0.0000000        1.00000000 + j*0.0000000      1.00000000 + j*0.0000000         1.00000000 + j*0.0000000
//1.00000000 + j*0.0000000    0.500000000 - j*0.866025404    -0.500000000 - j*0.866025404    -1.00000000 +j*0.0000000     -0.500000000 + j*0.866025404      0.500000000 + j*0.866025404
//1.00000000 + j*0.0000000   -0.500000000 - j*0.866025404    -0.500000000 + j*0.866025404     1.00000000 + j*0.0000000    -0.500000000-  j*0.866025404     -0.500000000 + j*0.866025404
//1.00000000 + j*0.0000000   -1.00000000   + j*0.0000000     1.00000000 + j*0.0000000        -1.00000000 +  j*0.0000000    1.00000000    + j*0.0000000      -1.00000000 + j*0.0000000
//1.00000000 + j*0.0000000   -0.500000000 + j*0.866025404    -0.500000000 - j*0.866025404     1.00000000 + j*0.0000000    -0.500000000 +  j*0.866025404     -0.500000000 - j*0.866025404
//1.00000000 + j*0.0000000    0.500000000 + j*0.866025404    -0.500000000 + j*0.866025404    -1.00000000 + j*0.0000000    -0.500000000  -  j*0.866025404     0.500000000 - j*0.866025404  */
#define MICRO_AVX_BASE6_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__,  __nDataInterlvrGAP__, \
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





/*
//0<= m < N/4 
//n= m         ....|X(0N/4+m) | = |  1.000+j*0.000,   1.000+j*0.000,   1.000+j*0.000,   1.000+j*0.000,   |     |X_quad_0(m)*W(N,0m) |
//n= 1N/4 + m  ....|X(1N/4+m) | = |  1.000+j*0.000,   0.000 -j*1.000,  -1.000+j*0.000,  0.000+j*1.000,   |     |X_quad_1(m)*W(N,1m) |
//n= 2N/4 + m  ....|X(2N/4+m) | = |  1.000+j*0.000,   -1.000+j*0.000,  1.000+j*0.000,   -1.000+j*0.000,  |     |X_quad_2(m)*W(N,2m) | 
//n= 3N/4 + m  ....|X(3N/4+m) | = |  1.000+j*0.000,   0.000+j*1.000,  -1.000+j*0.000,   0.000-j*1.000,   |     |X_quad_3(m)*W(N,3m) |   */

#define MICRO_AVX_BASE4_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__, __nDataInterlvrGAP__,__ymmS0,__ymmS1,__ymmS2,__ymmS3,__ymmS4,__ymmS5,__ymmS6,__ymmS7, ____pfCurrTMP_IQPtr____,__ymm0,__ymm1,__ymm2,__ymm3) \
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
#define MICRO_AVX_BASE8_BUTTERFLY_OPERATION(__pfDataIQVEC_OUT__, __pfCurr1stSrcOctVEC__, __nDataInterlvrGAP__,__ymmS2,__ymmS3,__ymmS4,__ymmS5,__ymmS6,__ymmS7,__ymmS8,__ymmS9,__ymmS10,__ymmS11,__ymmS12,__ymmS13,__ymmS14,__ymmS15, ____pfCurrTMP_IQPtr____,__ymm0,__ymm1,__ymm2,__ymm3) \
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



#define MICRO_AVX_SUM_A_MUL_Const_REPEAT7(__ymmOutI, __ymmOutQ, __pfSrcOctIQVEC_LIST__, __fConstIQ_LIST__,__ymm0__,__ymm1__,__ymm2__,__ymm3__,__ymm4__,__ymm5__) \
__ymm0__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src I vector */   \
__ymm1__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src Q vector */   \
__ymm2__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);   __fConstIQ_LIST__+= 1; \
__ymm3__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);	 __fConstIQ_LIST__+= 1; \
__ymm4__ = _mm256_mul_ps(__ymm0__, __ymm2__);  \
__ymm5__ = _mm256_mul_ps(__ymm1__, __ymm3__);  /* use __ymm5__ as buffer */ \
__ymm4__ = _mm256_sub_ps(__ymm4__, __ymm5__);  \
__ymm5__ = _mm256_mul_ps(__ymm0__, __ymm3__);  \
__ymm2__ = _mm256_mul_ps(__ymm1__, __ymm2__);  /* destroy __ymm2__,which is defined as __fConstI__ */   \
__ymm5__ = _mm256_add_ps(__ymm5__, __ymm2__);  \
__ymmOutI = _mm256_add_ps(__ymmOutI,__ymm4__);   \
__ymmOutQ = _mm256_add_ps(__ymmOutQ,__ymm5__);   \
__ymm0__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src I vector */   \
__ymm1__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src Q vector */   \
__ymm2__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);   __fConstIQ_LIST__+= 1; \
__ymm3__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);	 __fConstIQ_LIST__+= 1; \
__ymm4__ = _mm256_mul_ps(__ymm0__, __ymm2__);  \
__ymm5__ = _mm256_mul_ps(__ymm1__, __ymm3__);  /* use __ymm5__ as buffer */ \
__ymm4__ = _mm256_sub_ps(__ymm4__, __ymm5__);  \
__ymm5__ = _mm256_mul_ps(__ymm0__, __ymm3__);  \
__ymm2__ = _mm256_mul_ps(__ymm1__, __ymm2__);  /* destroy __ymm2__,which is defined as __fConstI__ */   \
__ymm5__ = _mm256_add_ps(__ymm5__, __ymm2__);  \
__ymmOutI = _mm256_add_ps(__ymmOutI,__ymm4__);   \
__ymmOutQ = _mm256_add_ps(__ymmOutQ,__ymm5__);   \
__ymm0__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src I vector */   \
__ymm1__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src Q vector */   \
__ymm2__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);   __fConstIQ_LIST__+= 1; \
__ymm3__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);	 __fConstIQ_LIST__+= 1; \
__ymm4__ = _mm256_mul_ps(__ymm0__, __ymm2__);  \
__ymm5__ = _mm256_mul_ps(__ymm1__, __ymm3__);  /* use __ymm5__ as buffer */ \
__ymm4__ = _mm256_sub_ps(__ymm4__, __ymm5__);  \
__ymm5__ = _mm256_mul_ps(__ymm0__, __ymm3__);  \
__ymm2__ = _mm256_mul_ps(__ymm1__, __ymm2__);  /* destroy __ymm2__,which is defined as __fConstI__ */   \
__ymm5__ = _mm256_add_ps(__ymm5__, __ymm2__);  \
__ymmOutI = _mm256_add_ps(__ymmOutI,__ymm4__);   \
__ymmOutQ = _mm256_add_ps(__ymmOutQ,__ymm5__);   \
__ymm0__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src I vector */   \
__ymm1__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src Q vector */   \
__ymm2__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);   __fConstIQ_LIST__+= 1; \
__ymm3__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);	 __fConstIQ_LIST__+= 1; \
__ymm4__ = _mm256_mul_ps(__ymm0__, __ymm2__);  \
__ymm5__ = _mm256_mul_ps(__ymm1__, __ymm3__);  /* use __ymm5__ as buffer */ \
__ymm4__ = _mm256_sub_ps(__ymm4__, __ymm5__);  \
__ymm5__ = _mm256_mul_ps(__ymm0__, __ymm3__);  \
__ymm2__ = _mm256_mul_ps(__ymm1__, __ymm2__);  /* destroy __ymm2__,which is defined as __fConstI__ */   \
__ymm5__ = _mm256_add_ps(__ymm5__, __ymm2__);  \
__ymmOutI = _mm256_add_ps(__ymmOutI,__ymm4__);   \
__ymmOutQ = _mm256_add_ps(__ymmOutQ,__ymm5__);   \
__ymm0__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src I vector */   \
__ymm1__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src Q vector */   \
__ymm2__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);   __fConstIQ_LIST__+= 1; \
__ymm3__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);	 __fConstIQ_LIST__+= 1; \
__ymm4__ = _mm256_mul_ps(__ymm0__, __ymm2__);  \
__ymm5__ = _mm256_mul_ps(__ymm1__, __ymm3__);  /* use __ymm5__ as buffer */ \
__ymm4__ = _mm256_sub_ps(__ymm4__, __ymm5__);  \
__ymm5__ = _mm256_mul_ps(__ymm0__, __ymm3__);  \
__ymm2__ = _mm256_mul_ps(__ymm1__, __ymm2__);  /* destroy __ymm2__,which is defined as __fConstI__ */   \
__ymm5__ = _mm256_add_ps(__ymm5__, __ymm2__);  \
__ymmOutI = _mm256_add_ps(__ymmOutI,__ymm4__);   \
__ymmOutQ = _mm256_add_ps(__ymmOutQ,__ymm5__);   \
__ymm0__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src I vector */   \
__ymm1__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src Q vector */   \
__ymm2__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);   __fConstIQ_LIST__+= 1; \
__ymm3__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);	 __fConstIQ_LIST__+= 1; \
__ymm4__ = _mm256_mul_ps(__ymm0__, __ymm2__);  \
__ymm5__ = _mm256_mul_ps(__ymm1__, __ymm3__);  /* use __ymm5__ as buffer */ \
__ymm4__ = _mm256_sub_ps(__ymm4__, __ymm5__);  \
__ymm5__ = _mm256_mul_ps(__ymm0__, __ymm3__);  \
__ymm2__ = _mm256_mul_ps(__ymm1__, __ymm2__);  /* destroy __ymm2__,which is defined as __fConstI__ */   \
__ymm5__ = _mm256_add_ps(__ymm5__, __ymm2__);  \
__ymmOutI = _mm256_add_ps(__ymmOutI,__ymm4__);   \
__ymmOutQ = _mm256_add_ps(__ymmOutQ,__ymm5__);   \
__ymm0__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src I vector */   \
__ymm1__ = _mm256_loadu_ps(__pfSrcOctIQVEC_LIST__);  __pfSrcOctIQVEC_LIST__+=8;           /* load src Q vector */   \
__ymm2__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);   __fConstIQ_LIST__+= 1; \
__ymm3__ = _mm256_set1_ps(__fConstIQ_LIST__[0]);	 __fConstIQ_LIST__+= 1; \
__ymm4__ = _mm256_mul_ps(__ymm0__, __ymm2__);  \
__ymm5__ = _mm256_mul_ps(__ymm1__, __ymm3__);  /* use __ymm5__ as buffer */ \
__ymm4__ = _mm256_sub_ps(__ymm4__, __ymm5__);  \
__ymm5__ = _mm256_mul_ps(__ymm0__, __ymm3__);  \
__ymm2__ = _mm256_mul_ps(__ymm1__, __ymm2__);  /* destroy __ymm2__,which is defined as __fConstI__ */   \
__ymm5__ = _mm256_add_ps(__ymm5__, __ymm2__);  \
__ymmOutI = _mm256_add_ps(__ymmOutI,__ymm4__);   \
__ymmOutQ = _mm256_add_ps(__ymmOutQ,__ymm5__);   



                  
#define  _SSE2_IEEE754_EXP_FRAC(_xmmiEXP,_xmmFRC,__pm128i_FRC,  __pm128i_SRC, _xmmi0,_xmmi1,_xmmi2,_xmmi3) \
_xmmi0   = _mm_loadu_si128(__pm128i_SRC);       /* !!!! ymmi0  <== source data                                        */  \
_xmmi1   = _mm_set1_epi32(0x7F800000);          /*                                                                    */  \
_xmmi2   = _mm_and_si128(_xmmi0,_xmmi1);        /*                                                                    */  \
_xmmi2   = _mm_srli_epi32(_xmmi2,23);           /*  !!!! ymmi2  <==get the 8 exponential bits                         */  \
_xmmi3   = _mm_set1_epi32(0x00400000);          /*                                                                    */  \
_xmmi1   = _mm_and_si128(_xmmi0,_xmmi3);        /* get the 23rd bit, the fractional is greater than 1.5 if it is 1    */  \
_xmmi1   = _mm_cmpeq_epi32(_xmmi1,_xmmi3);      /* !!!! _xmmi1  <== if( fractional part is greater than 1.5 )         */  \
_xmmi3   = _mm_set1_epi32(126);   _xmmi2 = _mm_sub_epi32(_xmmi2,_xmmi3);        /*  _xmmi2 = EXP -126              */  \
_xmmi3   = _mm_set1_epi32(1);     _xmmi3 = _mm_sub_epi32(_xmmi2,_xmmi3);        /*  _xmmi2 = EXP -127              */  \
_xmmi2   = _mm_and_si128(_xmmi1,_xmmi2);        /*                                                                    */  \
_xmmi3   = _mm_andnot_si128(_xmmi1,_xmmi3);     /*                                                                    */  \
_xmmiEXP = _mm_add_epi32(_xmmi2,_xmmi3);      /*                                                                    */  \
_xmmi2   = _mm_set1_epi32(0x807FFFFF);       _xmmi0 = _mm_and_si128(_xmmi0,_xmmi2);     /* !!!! _xmmi0 <== fractional bits   & sign bit!!             */  \
_xmmi2   = _mm_set1_epi32(0x3f000000);       _xmmi2 = _mm_or_si128(_xmmi0,_xmmi2);      /* !!!! _xmmi2 <== create the number which is 0.5*fractional  */  \
_xmmi3   = _mm_set1_epi32(0x3f800000);       _xmmi3 = _mm_or_si128(_xmmi0,_xmmi3);      /* !!!! _xmmi3 <== create the number which is 1.0*fractional  */  \
_xmmi2   = _mm_and_si128(_xmmi1,_xmmi2);     _xmmi3 = _mm_andnot_si128(_xmmi1,_xmmi3);  /*                                                            */  \
_xmmi3   = _mm_add_epi32(_xmmi2,_xmmi3);        /*                                                                    */  \
_xmmFRC  = _mm_castsi128_ps(_xmmi3);            /*  KnowHow in 2019-12-26 , not faster???                             */

//_mm_storeu_si128(__pm128i_FRC,_xmmi3);        /*   save new fractional number                                       */  \
//_xmmFRC = _mm_loadu_ps((float*)__pm128i_FRC); /*                                                                    */  


 

#define  _AVX2_IEEE754_EXP_FRAC(_ymmiEXP,_ymmFRC,__pm256i_FRC,  __pm256i_SRC, _ymmi0,_ymmi1,_ymmi2,_ymmi3) \
_ymmi0 = _mm256_loadu_si256(__pm256i_SRC);       /* !!!! ymmi0  <== source data                                        */  \
_ymmi1 = _mm256_set1_epi32(0x7F800000);          /*                                                                    */  \
_ymmi2 = _mm256_and_si256(_ymmi0,_ymmi1);        /*                                                                    */  \
_ymmi2 = _mm256_srli_epi32(_ymmi2,23);           /*  !!!! ymmi2  <==get the 8 exponential bits                         */  \
_ymmi3 = _mm256_set1_epi32(0x00400000);          /*                                                                    */  \
_ymmi1 = _mm256_and_si256(_ymmi0,_ymmi3);        /* get the 23rd bit, the fractional is greater than 1.5 if it is 1    */  \
_ymmi1 = _mm256_cmpeq_epi32(_ymmi1,_ymmi3);      /* !!!! _ymmi1  <== if( fractional part is greater than 1.5 )         */  \
_ymmi3 = _mm256_set1_epi32(126);   _ymmi2 = _mm256_sub_epi32(_ymmi2,_ymmi3);        /*  _ymmi2 = EXP -126              */  \
_ymmi3 = _mm256_set1_epi32(1);     _ymmi3 = _mm256_sub_epi32(_ymmi2,_ymmi3);        /*  _ymmi2 = EXP -127              */  \
_ymmi2 = _mm256_and_si256(_ymmi1,_ymmi2);        /*                                                                    */  \
_ymmi3 = _mm256_andnot_si256(_ymmi1,_ymmi3);     /*                                                                    */  \
_ymmiEXP = _mm256_add_epi32(_ymmi2,_ymmi3);      /*                                                                    */  \
_ymmi2 = _mm256_set1_epi32(0x807FFFFF);       _ymmi0 = _mm256_and_si256(_ymmi0,_ymmi2);     /* !!!! _ymmi0 <== fractional bits   & sign bit!!             */  \
_ymmi2 = _mm256_set1_epi32(0x3f000000);       _ymmi2 = _mm256_or_si256(_ymmi0,_ymmi2);      /* !!!! _ymmi2 <== create the number which is 0.5*fractional  */  \
_ymmi3 = _mm256_set1_epi32(0x3f800000);       _ymmi3 = _mm256_or_si256(_ymmi0,_ymmi3);      /* !!!! _ymmi3 <== create the number which is 1.0*fractional  */  \
_ymmi2 = _mm256_and_si256(_ymmi1,_ymmi2);     _ymmi3 = _mm256_andnot_si256(_ymmi1,_ymmi3);  /*                                                            */  \
_ymmi3 = _mm256_add_epi32(_ymmi2,_ymmi3);        /*                                                                    */  \
_mm256_storeu_si256(__pm256i_FRC,_ymmi3);        /*   save new fractional number                                       */  \
_ymmFRC = _mm256_loadu_ps((float*)__pm256i_FRC); /*                                                                    */  

//_ymmFRC= _mm256_castsi256_ps(_ymmi3);            /*  KnowHow in 2019-12-26 , not faster???                             */


#define  _AVX2_IEEE754_EXP_FRAC_LT1(_ymmiEXP,_ymmFRC,__pm256i_FRC,  __pm256i_SRC, _ymmi0,_ymmi1,_ymmi2,_ymmi3) \
_ymmi0 = _mm256_loadu_si256(__pm256i_SRC);       /* !!!! ymmi0  <== source data                                        */  \
_ymmi1 = _mm256_set1_epi32(0x7F800000);          /*                                                                    */  \
_ymmi2 = _mm256_and_si256(_ymmi0,_ymmi1);        /*                                                                    */  \
_ymmi2 = _mm256_srli_epi32(_ymmi2,23);           /*  !!!! ymmi2  <==get the 8 exponential bits                         */  \
_ymmi3 = _mm256_set1_epi32(127);              _ymmiEXP = _mm256_sub_epi32(_ymmi2,_ymmi3);        /*  _ymmi2 = EXP -127              */  \
_ymmi3 = _mm256_set1_epi32(0x3f800000);       _ymmi3   = _mm256_or_si256(_ymmi0,_ymmi3);      /* !!!! _ymmi3 <== create the number which is 1.0*fractional  */  \
_mm256_storeu_si256(__pm256i_FRC,_ymmi3);        /*   save new fractional number                                       */  \
_ymmFRC = _mm256_loadu_ps((float*)__pm256i_FRC); /*                                                                    */  


#define  _SSE2_IEEE754_EXP_FRAC_LT1(_xmmiEXP,_xmmFRC,__pm128i_FRC,  __pm128i_SRC, _xmmi0,_xmmi1,_xmmi2,_xmmi3) \
_xmmi0 = _mm_loadu_si128(__pm128i_SRC);       /* !!!! xmmi0  <== source data                                        */  \
_xmmi1 = _mm_set1_epi32(0x7F800000);          /*                                                                    */  \
_xmmi2 = _mm_and_si128(_xmmi0,_xmmi1);        /*                                                                    */  \
_xmmi2 = _mm_srli_epi32(_xmmi2,23);           /*  !!!! xmmi2  <==get the 8 exponential bits                         */  \
_xmmi3 = _mm_set1_epi32(127);              _xmmiEXP = _mm_sub_epi32(_xmmi2,_xmmi3);        /*  _xmmi2 = EXP -127              */  \
_xmmi3 = _mm_set1_epi32(0x3f800000);       _xmmi3   = _mm_or_si128(_xmmi0,_xmmi3);      /* !!!! _xmmi3 <== create the number which is 1.0*fractional  */  \
_mm_storeu_si128(__pm128i_FRC,_xmmi3);        /*   save new fractional number                                       */  \
_xmmFRC = _mm_loadu_ps((float*)__pm128i_FRC); /*                                                                    */ 




// the following design is not faster , commented by Duan Weiming in 2019-12-26
#define  _AVX2_IEEE754_EXP_FRAC_try(_ymmiEXP,_ymmFRC,__pm256i_FRC,  __pm256i_SRC, _ymmi0,_ymmi1,_ymmi2,_ymmi3,ymmiC_7F800000,ymmiC_00400000,ymmiC_126,ymmiC_807FFFFF,ymmiC_3F000000,ymmiC_3F800000) \
_ymmi0 = _mm256_loadu_si256(__pm256i_SRC);       /* !!!! ymmi0  <== source data                                        */  \
_ymmi2 = _mm256_and_si256(_ymmi0,ymmiC_7F800000);        /*                                                                    */  \
_ymmi2 = _mm256_srli_epi32(_ymmi2,23);           /*  !!!! ymmi2  <==get the 8 exponential bits                         */  \
_ymmi1 = _mm256_and_si256(_ymmi0,ymmiC_00400000);        /* get the 23rd bit, the fractional is greater than 1.5 if it is 1    */  \
_ymmi1 = _mm256_cmpeq_epi32(_ymmi1,ymmiC_00400000);      /* !!!! _ymmi1  <== if( fractional part is greater than 1.5 )         */  \
_ymmi2 = _mm256_sub_epi32(_ymmi2,ymmiC_126);        /*  _ymmi2 = EXP -126              */  \
_ymmi3 = _mm256_set1_epi32(1);     _ymmi3 = _mm256_sub_epi32(_ymmi2,_ymmi3);        /*  _ymmi2 = EXP -127              */  \
_ymmi2 = _mm256_and_si256(_ymmi1,_ymmi2);        /*                                                                    */  \
_ymmi3 = _mm256_andnot_si256(_ymmi1,_ymmi3);     /*                                                                    */  \
_ymmiEXP = _mm256_add_epi32(_ymmi2,_ymmi3);      /*                                                                    */  \
_ymmi0 = _mm256_and_si256(_ymmi0,ymmiC_807FFFFF);     /* !!!! _ymmi0 <== fractional bits   & sign bit!!                */  \
_ymmi2 = _mm256_or_si256(_ymmi0,ymmiC_3F000000);      /* !!!! _ymmi2 <== create the number which is 0.5*fractional     */  \
_ymmi3 = _mm256_or_si256(_ymmi0,ymmiC_3F800000);      /* !!!! _ymmi3 <== create the number which is 1.0*fractional     */  \
_ymmi2 = _mm256_and_si256(_ymmi1,_ymmi2);     _ymmi3 = _mm256_andnot_si256(_ymmi1,_ymmi3);  /*                         */  \
_ymmi3 = _mm256_add_epi32(_ymmi2,_ymmi3);        /*                                                                    */  \
_mm256_storeu_si256(__pm256i_FRC,_ymmi3);        /*   save new fractional number                                       */  \
_ymmFRC = _mm256_loadu_ps((float*)__pm256i_FRC); /*                                                                    */  




                                         

// the following has bad precision due to mean value is 1.5 (instead of 1.0) , commented by Duan Weiming in 2019-12-26
#define  _AVX2_IEEE754_EXP_FRAC_raw(_ymmiEXP,_ymmFRC,__pm256i_FRC,  __pm256i_SRC, _ymmi0,_ymmi1,_ymmi2,_ymmi3) \
_ymmi0 = _mm256_loadu_si256(__pm256i_SRC);       /* !!!! ymmi0  <== source data                                        */  \
_ymmi1 = _mm256_set1_epi32(0x7F800000);          /*                                                                    */  \
_ymmi2 = _mm256_and_si256(_ymmi0,_ymmi1);        /*                                                                    */  \
_ymmi2 = _mm256_srli_epi32(_ymmi2,23);           /*  !!!! ymmi2  <==get the 8 exponential bits                         */  \
_ymmi1 = _mm256_set1_epi32(127);   _ymmiEXP = _mm256_sub_epi32(_ymmi2,_ymmi1);        /*  _ymmi2 = EXP -127              */  \
_ymmi2 = _mm256_set1_epi32(0x807FFFFF);       _ymmi0 = _mm256_and_si256(_ymmi0,_ymmi2);     /* !!!! _ymmi0 <== fractional bits   & sign bit!!             */  \
_ymmi2 = _mm256_set1_epi32(0x3f800000);       _ymmi2 = _mm256_or_si256(_ymmi0,_ymmi2);      /* !!!! _ymmi3 <== create the number which is 1.0*fractional  */  \
_ymmFRC  = _mm256_castsi256_ps(_ymmi2);            /*  KnowHow in 2019-12-26 , not faster???                             */

//_mm256_storeu_si256(__pm256i_FRC,_ymmi2);        /*   save new fractional number                                       */  
//_ymmFRC = _mm256_loadu_ps((float*)__pm256i_FRC); /*                                                                    */  
 



#define __AVX_OCTnum_LSTlen(__OCTnum__,__LSTlen__,__VEClen__) \
int __OCTnum__ = ((__VEClen__) >> 3); int __LSTlen__ = 8; if( 0 < (__VEClen__ - __OCTnum__*8) ) { __LSTlen__=(__VEClen__ - __OCTnum__*8); __OCTnum__+=1;} 


#define __AVX_SUM_uptXn_SCALE(__ymmSUM__, __ymmXn__,__ymmX__,__fscale__,__ymmT__) \
__ymmT__    = _mm256_set1_ps(__fscale__);                          \
__ymmXn__   = _mm256_mul_ps(__ymmXn__,__ymmX__);                   \
__ymmT__    = _mm256_mul_ps(__ymmT__,__ymmXn__);                   \
__ymmSUM__  = _mm256_add_ps(__ymmSUM__,__ymmT__);   


#define __AVX_SUM_uptXn_ADD(__ymmSUM__, __ymmXn__,__ymmX__,__ymmScale__,__ymmT__) \
__ymmXn__   = _mm256_mul_ps(__ymmXn__,__ymmX__);                   \
__ymmT__    = _mm256_mul_ps(__ymmScale__,__ymmXn__);               \
__ymmSUM__  = _mm256_add_ps(__ymmSUM__,__ymmT__);

#define __AVX_SUM_uptXn_SUB(__ymmSUM__, __ymmXn__,__ymmX__,__ymmScale__,__ymmT__) \
__ymmXn__   = _mm256_mul_ps(__ymmXn__,__ymmX__);                   \
__ymmT__    = _mm256_mul_ps(__ymmScale__,__ymmXn__);               \
__ymmSUM__  = _mm256_sub_ps(__ymmSUM__,__ymmT__);   


#define _AVX_OCTNUM(__OCTnum__, __RSTnum__,__VEClen__) int __OCTnum__ = ((__VEClen__)>>3);   int __RSTnum__ = (__VEClen__) - (__OCTnum__)*8;  if( 0 == __RSTnum__) {  __OCTnum__ -= 1; __RSTnum__ = 8; } 
#define _AVX_OCTFLTS_INI(__vfOCTmem__,__OCTnum__, __RSTnum__,__VEClen__) int __OCTnum__ = ((__VEClen__)>>3);   int __RSTnum__ = (__VEClen__) - (__OCTnum__)*8;  if( 0 == __RSTnum__) {  __OCTnum__ -= 1; __RSTnum__ = 8; }  float __vfOCTmem__[8]; 

#define _AVX_OCTINTS_INI(__pm256i_MEM__,__viOCTmem__,__OCTnum__, __RSTnum__,__VEClen__) \
int __OCTnum__ = ((__VEClen__)>>3);   int __RSTnum__ = (__VEClen__) - (__OCTnum__)*8;  if( 0 == __RSTnum__) {  __OCTnum__ -= 1; __RSTnum__ = 8; }  \
int __viOCTmem__[8];  __m256i *__pm256i_MEM__ = (__m256i *)__viOCTmem__;






#endif /* __PERF_METRIC_COMMavx_H */
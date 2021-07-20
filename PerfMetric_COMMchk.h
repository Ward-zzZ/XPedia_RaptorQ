#ifndef __PERF_METRIC_COMMchk_H
#define __PERF_METRIC_COMMchk_H
/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */

extern int  gnGlobal_ERROR_Counter;


#define EXIT_ERROR_FULL() if( 10 <=  gnGlobal_ERROR_Counter ) { printf("    @@@@@@@@@@ EXIT!!!  <%s,%s,%d>   gnGlobal_ERROR_Counter = %d  \n", __FILE__,__FUNCTION__,__LINE__, (gnGlobal_ERROR_Counter)); exit(-1); }



// ****************************************************************************************************************************************************************************************************************************************************
#define  ECHO_STR( __str_value__)  printf(" "#__str_value__": %s  \n", (char *)(__str_value__));
#define  ECHO_INT( __ival__)  printf(" "#__ival__"=%d  \n", (int)(__ival__));
#define _ECHO_INT( __ival__)  printf(" "#__ival__"=%d  ", (int)(__ival__));
#define  ECHO_FLT( __fval__)  printf(" "#__fval__"=%.3e  \n", (float)(__fval__));
#define _ECHO_FLT( __fval__)  printf(" "#__fval__"=%.3e ", (float)(__fval__));

#define  ECHO_fVEC( __vfVEC__, __VEClen__ )  { int __jjj = 0;  printf(" "#__vfVEC__"= [ ");  for(__jjj = 0; __jjj < __VEClen__; __jjj++ ) { printf("%.3e,", (__vfVEC__)[__jjj]); } printf("]; \n"); }	
#define  ECHO_iVEC( __viVEC__, __VEClen__ )  { int __jjj = 0;  printf(" "#__viVEC__"= [ ");  for(__jjj = 0; __jjj < __VEClen__; __jjj++ ) { printf("%d,", (__viVEC__)[__jjj]); } printf("]; \n");  }

// ****************************************************************************************************************************************************************************************************************************************************

// ((__to0__) > (__var0__) ==> ((__to0__) >= (__var0__), modified by Duan Weimign in 2020-02-18
#define _isRNG(__var__,__from__, __to__)   ( ((__from__) <= (__var__) ) && ((__to__) >= (__var__) ) )
#define _IF_RNG(__var__,__from__, __to__) if( ((__from__) <= (__var__) ) && ((__to__) >= (__var__) ) )
#define _IF_RNG2(__var0__,__from0__, __to0__,__var1__,__from1__, __to1__) if( ((__from0__) <= (__var0__) ) && ((__to0__) >= (__var0__) ) && ((__from1__) <= (__var1__) ) && ((__to1__) >= (__var1__) )  )

#define IF_OUTrng( __Val__, __MinVal__, __MaxVal__)  if( ( (__MinVal__) > (__Val__) ) || ( (__MaxVal__) < (__Val__) ) ) 
#define _IS_OUTrng( __Val__, __MinVal__, __MaxVal__)  ( ( (__MinVal__) > (__Val__) ) || ( (__MaxVal__) < (__Val__) ) ) 


// ****************************************************************************************************************************************************************************************************************************************************
#define WARNING_COND_1INT(__cond__, __ival__) \
if( (__cond__) ){ printf("WARNING!!!<%s,%s,%d>"#__cond__ " ,  ( "#__ival__ ") = %d  \n", __FILE__,__FUNCTION__,__LINE__, (__ival__)); }


#define WARNING_COND_2INT(__cond__, __i0, __i1) \
if( (__cond__) ){ printf("WARNING!!!<%s,%s,%d>"#__cond__ " ,  ( "#__i0 ") = %d ,  ( "#__i1 ") = %d \n", __FILE__,__FUNCTION__,__LINE__, (__i0), (__i1)); }


#define ALARM_VAL2(__val0__, __val1__)   printf("ALARM!!!<%s,%s,%d>"#__val0__ "=%f ... "#__val1__ "=%f  !!!  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__val0__ ), (float)(__val1__ )); //gnGlobal_ERROR_Counter++;
#define ALARM_N2(__val0__, __val1__)     printf("ALARM!!!<%s,%s,%d>"#__val0__ "=%d ... "#__val1__ "=%d  !!!  \n", __FILE__,__FUNCTION__,__LINE__, (int)(__val0__ ), (int)(__val1__ ));     //gnGlobal_ERROR_Counter++;
#define ALARM_N3(__v0, __v1,__v2)        printf("ALARM!!!<%s,%s,%d>"#__v0"=%d.. "#__v1"=%d.."#__v2"=%d..  !!!  \n", __FILE__,__FUNCTION__,__LINE__, __v0,__v1,__v2);                       //gnGlobal_ERROR_Counter++;
#define ALARM_N4(__v0, __v1,__v2,__v3)   printf("ALARM!!!<%s,%s,%d>"#__v0"=%d.. "#__v1"=%d.."#__v2"=%d.."#__v3"=%d..  !!!  \n", __FILE__,__FUNCTION__,__LINE__, __v0,__v1,__v2,__v3);      //gnGlobal_ERROR_Counter++;

#define CLAIM_N2(__val0__, __val1__)     printf("INFO!!!<%s,%s,%d>"#__val0__ "=%d ... "#__val1__ "=%d  !!!  \n", __FILE__,__FUNCTION__,__LINE__, (int)(__val0__ ), (int)(__val1__ )); 
#define CLAIM_N4(__v0, __v1,__v2,__v3)   printf("INFO!!!<%s,%s,%d>"#__v0"=%d.. "#__v1"=%d.."#__v2"=%d.."#__v3"=%d..  !!!  \n", __FILE__,__FUNCTION__,__LINE__, __v0,__v1,__v2,__v3);

#define CLAIM_L2(__val0__, __val1__)     printf("INFO!!!<%s,%s,%d>"#__val0__ "=%ld... "#__val1__ "=%ld !!!  \n", __FILE__,__FUNCTION__,__LINE__, (long)(__val0__ ), (long)(__val1__ )); 
#define CLAIM_L4(__v0, __v1,__v2,__v3)   printf("INFO!!!<%s,%s,%d>"#__v0"=%ld.."#__v1"=%ld.."#__v2"=%ld.."#__v3"=%ld.. !!!  \n", __FILE__,__FUNCTION__,__LINE__, (long)__v0,(long)__v1,(long)__v2,(long)__v3);

#define CLAIM_SN1(__strSAY__,__val__)     printf("INFO!!!<%s,%s,%d> %s ... "#__val__ "=%d !!!  \n", __FILE__,__FUNCTION__,__LINE__, (char*)__strSAY__,__val__); 
#define CLAIM_S1(__strSAY__)     printf("INFO!!!<%s,%s,%d> %s ...  !!!  \n", __FILE__,__FUNCTION__,__LINE__, (char*)__strSAY__); 
#define CLAIM_S2(__strS1__,__strS2__)     printf("INFO!!!<%s,%s,%d>  %s %s  !!!  \n", __FILE__,__FUNCTION__,__LINE__, (char*)__strS1__, (char*)__strS2__); 

#define ERR_1INT(_ival_)           printf("ERROR!!!<%s,%s,%d> ( "#_ival_ ") = %d  \n", __FILE__,__FUNCTION__,__LINE__, (_ival_)); gnGlobal_ERROR_Counter++;
#define ERR_2INT(_ival0_, _ival1_) printf("ERROR!!!<%s,%s,%d> ( "#_ival0_ ") = %d ,  ( "#_ival1_ ") = %d \n", __FILE__,__FUNCTION__,__LINE__, (_ival0_), (_ival1_)); gnGlobal_ERROR_Counter++; 
#define ERR_1FLT(__flt_value__)    printf("ERROR!!!<%s,%s,%d> ( "#__flt_value__ ") = %f  \n", __FILE__,__FUNCTION__,__LINE__, (__flt_value__)); gnGlobal_ERROR_Counter++; 


#define ERR_CHK(__cond__) if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ "  !!!  \n", __FILE__,__FUNCTION__,__LINE__); gnGlobal_ERROR_Counter++; }
#define ERR_CHKstr(__cond__,__strwhy__) if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ " ... %s !!!  \n", __FILE__,__FUNCTION__,__LINE__,__strwhy__); gnGlobal_ERROR_Counter++; }


#define ERR_CHKrng(__Val__, __MinVal__, __MaxVal__)  if( ( (__MinVal__) > (__Val__) ) || ( (__MaxVal__) < (__Val__) ) ){ printf("ERROR!!!<%s,%s,%d> "#__Val__"=%d (%d~%d) !!!  \n", __FILE__,__FUNCTION__,__LINE__,__Val__, __MinVal__, __MaxVal__); gnGlobal_ERROR_Counter++; } 

#define ERR_CHKrngFLT(__Val__, __MinVal__, __MaxVal__)  if( ( (__MinVal__) > (__Val__) ) || ( (__MaxVal__) < (__Val__) ) ){ printf("ERROR!!!<%s,%s,%d> "#__Val__"=%f (%f~%f) !!!  \n", __FILE__,__FUNCTION__,__LINE__,__Val__, __MinVal__, __MaxVal__); gnGlobal_ERROR_Counter++; } 

#define ERR_COND_1INT(__cond__, __ival__)         if( (__cond__) ) { printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__ival__ ") = %d  \n", __FILE__,__FUNCTION__,__LINE__, (__ival__)); gnGlobal_ERROR_Counter++;}
#define ERR_COND_STR(__cond__, __str_value__)     if( (__cond__) ) { printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  %s  \n", __FILE__,__FUNCTION__,__LINE__, (__str_value__)); gnGlobal_ERROR_Counter++; }
#define ERR_COND_2INT(__cond__, __i0, __i1)       if( (__cond__) ) { printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__i0 ") = %d ,  ( "#__i1 ") = %d \n", __FILE__,__FUNCTION__,__LINE__, (__i0), (__i1)); gnGlobal_ERROR_Counter++; }
#define ERR_COND_3INT(__cond__, __i0, __i1, __i2) if( (__cond__) ) { printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__i0 ") = %d ,  ( "#__i1 ") = %d,  ( "#__i2 ") = %d \n", __FILE__,__FUNCTION__,__LINE__,(__i0),(__i1),(__i2)); gnGlobal_ERROR_Counter++; }

#define ERR_COND_1FLT(__cond__, __fval__)         if( (__cond__) ) { printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__fval__ ") = %f  \n", __FILE__,__FUNCTION__,__LINE__, (__fval__)); gnGlobal_ERROR_Counter++; }
#define ERR_COND_2FLT(__cond__, __f0, __f1)       if( (__cond__) ) { printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__f0 ") = %f ,  ( "#__f1 ") = %f \n", __FILE__,__FUNCTION__,__LINE__, (__f0), (__f1)); gnGlobal_ERROR_Counter++; }
#define ERR_STR(__string1__)                                       { printf("ERROR!!!<%s,%s,%d>  <%s>  \n", __FILE__,__FUNCTION__,__LINE__, (char *)(__string1__)); gnGlobal_ERROR_Counter++; }


	
// ****************************************************************************************************************************************************************************************************************************************************
#define ERR_RNG( __Val__, __MinVal__, __MaxVal__) if( ( (__MinVal__) > (__Val__) ) || ( (__MaxVal__) < (__Val__) ) ){ printf("ERROR!!! <%s,%s,%d>,( "#__Val__ " = %f ) exceeds (%f,%f)  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__Val__),(float)(__MinVal__),(float)(__MaxVal__)); gnGlobal_ERROR_Counter++;  }
#define ERR_NEQ(  __Val0__, __Val1__) if(  (__Val0__) != (__Val1__)  ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__Val0__ " = %f ) != ( "#__Val1__ " = %f )  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__Val0__),(float)(__Val1__)); gnGlobal_ERROR_Counter++;  }

#define ERR_LT(  __Val0__, __Val1__)  if(  (__Val0__) < (__Val1__)  ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__Val0__ " = %f ) != ( "#__Val1__ " = %f )  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__Val0__),(float)(__Val1__)); gnGlobal_ERROR_Counter++;  }

#define SOS_WARNING(__cond__) if( (__cond__) ){ printf("WARNING!!!<%s,%s,%d>!!! %s !!!  \n", __FILE__,__FUNCTION__,__LINE__,(char*)(__cond__));  }

#define WARNING_N1(__strClaim__,__val0__) printf("WARNING!!!<%s,%s,%d>!!! %s , %d !!!  \n", __FILE__,__FUNCTION__,__LINE__,(char*)__strClaim__,(int)(__val0__));  

// ****************************************************************************************************************************************************************************************************************************************************

#define retERR_validVEC(__vfVEC__, __VEClen, __fMin__, __fMax__ )  \
{  int __currID__ = VEC_chkvalid(__vfVEC__, __VEClen, __fMin__, __fMax__ );  \
	if( 0 <= __currID__ ) {  \
		printf("ERROR!!!<%s,%s,%d> ,  ( "#__vfVEC__"[%d] = %f ) is invalid(%f~%f)  \n", __FILE__,__FUNCTION__,__LINE__,__currID__, (__vfVEC__)[__currID__],__fMin__, __fMax__); gnGlobal_ERROR_Counter++; return; \
	}    \
}

#define retERR_validIVEC(__viVEC__, __VEClen, __iMin__, __iMax__ )  \
{  int __currID__ = IVEC_chkvalid(__viVEC__, __VEClen, __iMin__, __iMax__ );  \
	if( 0 <= __currID__ ) {  \
		printf("ERROR!!!<%s,%s,%d> ,  ( "#__viVEC__"[%d] = %d ) is invalid(%d~%d)  \n", __FILE__,__FUNCTION__,__LINE__,__currID__, (__viVEC__)[__currID__],__iMin__, __iMax__); gnGlobal_ERROR_Counter++; return; \
	}    \
}

#define ret0ERR_validIVEC(__viVEC__, __VEClen, __iMin__, __iMax__ )  \
{  int __currID__ = IVEC_chkvalid(__viVEC__, __VEClen, __iMin__, __iMax__ );  \
	if( 0 <= __currID__ ) {  \
		printf("ERROR!!!<%s,%s,%d> ,  ( "#__viVEC__"[%d] = %d ) is invalid(%d~%d)  \n", __FILE__,__FUNCTION__,__LINE__,__currID__, (__viVEC__)[__currID__],__iMin__, __iMax__); gnGlobal_ERROR_Counter++; return 0; \
	}    \
}




#define retERR_LEZ_LIST(__num__, ...) \
{   int __vnOptions__[]={__VA_ARGS__};  int  __argNUM__ = (sizeof(__vnOptions__) >> 2);  int __jjj__; int __find__=0; \
  /* int __errNUM__ =  Chk_LEZero_INTS(__argNUM__,__VA_ARGS__); */ \
  /* if( 0 < __errNUM__ ) { printf("ERROR!!!<%s,%s,%d> ,   [%d]  invalid arguments (<0) !!! \n", __FILE__,__FUNCTION__,__LINE__,__errNUM__); gnGlobal_ERROR_Counter++; return ; } */ \
  for( __jjj__ = 0; __jjj__ < __argNUM__; __jjj__++ ) {   if( 0 >= __vnOptions__[__jjj__] ) { __find__ += 1; } } \
  if( 0 < __find__ ) { printf("ERROR!!!<%s,%s,%d> ,   [%d]  invalid arguments (<=0) !!! \n", __FILE__,__FUNCTION__,__LINE__,__find__); gnGlobal_ERROR_Counter++; return ; }  \
}


#define ret0ERR_LEZ_LIST(__num__, ...) \
{   int __vnOptions__[]={__VA_ARGS__};  int  __argNUM__ = (sizeof(__vnOptions__) >> 2);  int __jjj__; int __find__=0; \
  for( __jjj__ = 0; __jjj__ < __argNUM__; __jjj__++ ) {   if( 0 >= __vnOptions__[__jjj__] ) { __find__ += 1; } } \
  if( 0 < __find__ ) { printf("ERROR!!!<%s,%s,%d> ,   [%d]  invalid arguments (<=0) !!! \n", __FILE__,__FUNCTION__,__LINE__,__find__); gnGlobal_ERROR_Counter++; return 0; }  \
}


#define retERR_OUT_LIST(__var__, ...) \
{ int __vnOptions__[]={__VA_ARGS__}; int __maxNUM__ = (sizeof(__vnOptions__)>>2); int __jjj__; int __find__=0; \
	for( __jjj__ = 0; __jjj__ < __maxNUM__; __jjj__++ ) {  	if( (__var__) == __vnOptions__[__jjj__] ) { __find__ = 1; break; } } \
	if( 0 == __find__ ) { printf("ERROR!!! <%s,%s,%d>, "#__var__"[%d] is invalid !!! \n", __FILE__,__FUNCTION__,__LINE__,__var__); gnGlobal_ERROR_Counter++; return ; } \
}

#define ret0ERR_OUT_LIST(__var__, ...) \
{ int __vnOptions__[]={__VA_ARGS__}; int __maxNUM__ = (sizeof(__vnOptions__)>>2); int __jjj__; int __find__=0; \
	for( __jjj__ = 0; __jjj__ < __maxNUM__; __jjj__++ ) {  	if( (__var__) == __vnOptions__[__jjj__] ) { __find__ = 1; break; } } \
	if( 0 == __find__ ) { printf("ERROR!!! <%s,%s,%d>, "#__var__"[%d] is invalid !!! \n", __FILE__,__FUNCTION__,__LINE__,__var__); gnGlobal_ERROR_Counter++; return 0; } \
}


#define retERR_LTZ_LIST(__num__, ...) \
{   int __vnOptions__[]={__VA_ARGS__};  int  __argNUM__ = (sizeof(__vnOptions__) >> 2);  int __jjj__; int __find__=0; \
  for( __jjj__ = 0; __jjj__ < __argNUM__; __jjj__++ ) {   if( 0 > __vnOptions__[__jjj__] ) { __find__ += 1; } } \
  if( 0 < __find__ ) { printf("ERROR!!!<%s,%s,%d> ,   [%d]  invalid arguments (<0) !!! \n", __FILE__,__FUNCTION__,__LINE__,__find__); gnGlobal_ERROR_Counter++; return ; }  \
}

#define ret0ERR_LTZ_LIST(__num__, ...) \
{   int __vnOptions__[]={__VA_ARGS__};  int  __argNUM__ = (sizeof(__vnOptions__) >> 2);  int __jjj__; int __find__=0; \
  for( __jjj__ = 0; __jjj__ < __argNUM__; __jjj__++ ) {   if( 0 > __vnOptions__[__jjj__] ) { __find__ += 1; } } \
  if( 0 < __find__ ) { printf("ERROR!!!<%s,%s,%d> ,   [%d]  invalid arguments (<0) !!! \n", __FILE__,__FUNCTION__,__LINE__,__find__); gnGlobal_ERROR_Counter++; return 0; }  \
}





#define retERR_LIST(__var__, ...) \
{ int __vnOptions__[]={__VA_ARGS__}; int __maxNUM__ = (sizeof(__vnOptions__)>>2); int __jjj__; int __find__=0; \
	for( __jjj__ = 0; __jjj__ < __maxNUM__; __jjj__++ ) {  	if( (__var__) == __vnOptions__[__jjj__] ) { __find__ = 1; break; } } \
	if( 0 == __find__ ) { printf("ERROR!!!<%s,%s,%d> ,   "#__var__"[%d] is invalid !!! \n", __FILE__,__FUNCTION__,__LINE__,__var__); gnGlobal_ERROR_Counter++; return ; } \
}

#define ret0ERR_LIST(__var__, ...) \
{ int __vnOptions__[]={__VA_ARGS__}; int __maxNUM__ = (sizeof(__vnOptions__)>>2); int __jjj__; int __find__=0; \
	for( __jjj__ = 0; __jjj__ < __maxNUM__; __jjj__++ ) {  	if( (__var__) == __vnOptions__[__jjj__] ) { __find__ = 1; break; } } \
	if( 0 == __find__ ) { printf("ERROR!!!<%s,%s,%d> ,   "#__var__"[%d] is invalid !!! \n", __FILE__,__FUNCTION__,__LINE__,__var__); gnGlobal_ERROR_Counter++; return 0; } \
}
// ****************************************************************************************************************************************************************************************************************************************************


#define retERR_RNG( __Val__, __MinVal__, __MaxVal__) \
if( ( (__MinVal__) > (__Val__) ) || ( (__MaxVal__) < (__Val__) ) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__Val__ " = %f ) exceeds (%f,%f)  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__Val__),(float)(__MinVal__),(float)(__MaxVal__)); gnGlobal_ERROR_Counter++; return; }

#define ret0ERR_RNG( __Val__, __MinVal__, __MaxVal__) \
if( ( (__MinVal__) > (__Val__) ) || ( (__MaxVal__) < (__Val__) ) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__Val__ " = %f ) exceeds (%f,%f)  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__Val__),(float)(__MinVal__),(float)(__MaxVal__)); gnGlobal_ERROR_Counter++; return 0; }

#define retERR_ENUM(__eID,  __eNUMname) \
if( ( 0 > (__eID) ) || ( ENUM_LEN(__eNUMname) <= (__eID) ) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__eID " = %d ) exceeds (0,%d)  \n", __FILE__,__FUNCTION__,__LINE__, (int)(__eID),(int)(ENUM_LEN(__eNUMname)-1) ); gnGlobal_ERROR_Counter++; return; }

#define ret0ERR_ENUM(__eID,  __eNUMname) \
if( ( 0 > (__eID) ) || ( ENUM_LEN(__eNUMname) <= (__eID) ) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__eID " = %d ) exceeds (0,%d)  \n", __FILE__,__FUNCTION__,__LINE__, (int)(__eID),(int)(ENUM_LEN(__eNUMname)-1) ); gnGlobal_ERROR_Counter++; return 0; }


#define retERR_VEC_RNG( __Vec__,__num__, __MinVal__, __MaxVal__) \
{  int __jjj__; for( __jjj__ = 0; __jjj__ < (__num__); __jjj__++ ) {  \
	if( ( (__MinVal__) > (__Vec__)[__jjj__] ) || ( (__MaxVal__) < (__Vec__)[__jjj__] ) ) {  \
	printf("ERROR!!!<%s,%s,%d> , ( "#__Vec__"[%d] = %f) exceeds (%f,%f)  \n", __FILE__,__FUNCTION__,__LINE__,__jjj__,(float)(__Vec__)[__jjj__],(float)(__MinVal__),(float)(__MaxVal__)); gnGlobal_ERROR_Counter++; return; } \
	} \
}

#define ret0ERR_VEC_RNG( __Vec__,__num__, __MinVal__, __MaxVal__) \
{  int __jjj__; for( __jjj__ = 0; __jjj__ < (__num__); __jjj__++ ) {  \
	if( ( (__MinVal__) > (__Vec__)[__jjj__] ) || ( (__MaxVal__) < (__Vec__)[__jjj__] ) ) {  \
	printf("ERROR!!!<%s,%s,%d> , ( "#__Vec__"[%d] = %f) exceeds (%f,%f)  \n", __FILE__,__FUNCTION__,__LINE__,__jjj__,(float)(__Vec__)[__jjj__],(float)(__MinVal__),(float)(__MaxVal__)); gnGlobal_ERROR_Counter++; return 0; } \
	} \
}

#define RET_ERROR_SET( __Len__,__vals__, __MinVal__, __MaxVal__) \
{   int ErrIDX = VEC_chkrng((float*)__vals__, __Len__, __MinVal__, __MaxVal__); \
	if (0 < ErrIDX) { \
		printf("ERROR!!!<%s,%s,%d> ,  ( "#__vals__"[%d] = %f ) exceeds (%f,%f)  \n", __FILE__,__FUNCTION__,__LINE__,ErrIDX-1, (float)(__vals__[ErrIDX-1]),(float)(__MinVal__),(float)(__MaxVal__)); gnGlobal_ERROR_Counter++; return; \
	} \
}

#define RET0_ERROR_SET( __Len__,__vals__, __MinVal__, __MaxVal__) \
{   int ErrIDX = VEC_chkrng((float*)__vals__, __Len__, __MinVal__, __MaxVal__); \
	if (0 < ErrIDX) { \
		printf("ERROR!!!<%s,%s,%d> ,  ( "#__vals__"[%d] = %f ) exceeds (%f,%f)  \n", __FILE__,__FUNCTION__,__LINE__,ErrIDX-1, (float)(__vals__[ErrIDX-1]),(float)(__MinVal__),(float)(__MaxVal__)); gnGlobal_ERROR_Counter++; return 0; \
	} \
}


#define retERR_NOT_SAME(  __Val0__, __Val1__) \
if(  (__Val0__) != (__Val1__)  ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__Val0__ " = %f ) != ( "#__Val1__ " = %f )  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__Val0__),(float)(__Val1__)); gnGlobal_ERROR_Counter++; return; }

#define retERR_NEQ(  __Val0__, __Val1__) \
if(  (__Val0__) != (__Val1__)  ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__Val0__ " = %f ) != ( "#__Val1__ " = %f )  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__Val0__),(float)(__Val1__)); gnGlobal_ERROR_Counter++; return; }


#define ret0ERR_NEQ(  __Val0__, __Val1__) \
if(  (__Val0__) != (__Val1__)  ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__Val0__ " = %f ) != ( "#__Val1__ " = %f )  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__Val0__),(float)(__Val1__)); gnGlobal_ERROR_Counter++; return 0; }




#define retERR_LT( _v0__,_v1__) if( (_v0__) < (_v1__) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_v0__ " = %f ) < ( "#_v1__ " = %f )  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_v0__), (float)(_v1__)); gnGlobal_ERROR_Counter++; return; }
#define ret0ERR_LT(_v0__,_v1__) if( (_v0__) < (_v1__) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_v0__ " = %f ) < ( "#_v1__ " = %f )  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_v0__), (float)(_v1__)); gnGlobal_ERROR_Counter++; return 0; }

#define retERR_LE( _v0__,_v1__) if( (_v0__) <= (_v1__) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_v0__ " = %f ) <= ( "#_v1__ " = %f )  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_v0__), (float)(_v1__)); gnGlobal_ERROR_Counter++; return; }
#define ret0ERR_LE(_v0__,_v1__) if( (_v0__) <= (_v1__) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_v0__ " = %f ) <= ( "#_v1__ " = %f )  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_v0__), (float)(_v1__)); gnGlobal_ERROR_Counter++; return 0; }




#define retERR_EQZ( __val__) \
if( 0 == (__val__) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__val__ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__val__)); gnGlobal_ERROR_Counter++; return; }


#define retERR_LEZ( __val__) \
if( 0 >= (__val__) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__val__ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__val__)); gnGlobal_ERROR_Counter++; return; }

#define retERR_LEZ2( _Val0_,_Val1_) \
if( 0 >= (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return; }


#define ret0ERR_LEZ2( _Val0_,_Val1_) \
if( 0 >= (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return 0; }


#define retERR_LEZ3( _Val0_,_Val1_,_Val2_) \
if( 0 >= (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return; }

#define ret0ERR_LEZ3( _Val0_,_Val1_,_Val2_) \
if( 0 >= (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return 0; }


#define retERR_LEZ4( _Val0_,_Val1_,_Val2_,_Val3_) \
if( 0 >= (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val3_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val3_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val3_)); gnGlobal_ERROR_Counter++; return; } 

#define ret0ERR_LEZ4( _Val0_,_Val1_,_Val2_,_Val3_) \
if( 0 >= (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val3_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val3_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val3_)); gnGlobal_ERROR_Counter++; return 0; } 



#define retERR_LEZ5( _Val0_,_Val1_,_Val2_,_Val3_,_Val4_) \
if( 0 >= (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val3_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val3_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val3_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val4_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val4_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val4_)); gnGlobal_ERROR_Counter++; return; }


#define ret0ERR_LEZ5( _Val0_,_Val1_,_Val2_,_Val3_,_Val4_) \
if( 0 >= (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val3_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val3_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val3_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val4_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val4_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val4_)); gnGlobal_ERROR_Counter++; return 0; }



#define retERR_LEZ6( _Val0_,_Val1_,_Val2_,_Val3_,_Val4_,_Val5_) \
if( 0 >= (_Val0_) ){ printf("ERROR!!! <%s,%s,%d>,( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val1_) ){ printf("ERROR!!! <%s,%s,%d>,( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val2_) ){ printf("ERROR!!! <%s,%s,%d>,( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val3_) ){ printf("ERROR!!! <%s,%s,%d>,( "#_Val3_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val3_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val4_) ){ printf("ERROR!!! <%s,%s,%d>,( "#_Val4_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val4_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 >= (_Val5_) ){ printf("ERROR!!! <%s,%s,%d>,( "#_Val5_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val5_)); gnGlobal_ERROR_Counter++; return; }


#define ret0ERR_LEZ6( _Val0_,_Val1_,_Val2_,_Val3_,_Val4_,_Val5_) \
if( 0 >= (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val3_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val3_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val3_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val4_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val4_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val4_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 >= (_Val5_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val5_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val5_)); gnGlobal_ERROR_Counter++; return 0; }







#define retERR_LTZ( __val__) \
if( 0 > (__val__) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__val__ " = %f )  < 0 \n", __FILE__,__FUNCTION__,__LINE__, (float)(__val__)); gnGlobal_ERROR_Counter++; return; }

#define retERR_LTZ2( _Val0_,_Val1_) \
if( 0 > (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 > (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return; }

#define retERR_LTZ3( _Val0_,_Val1_,_Val2_) \
if( 0 > (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 > (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 > (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return; }

#define retERR_LTZ4( _Val0_,_Val1_,_Val2_,_Val3_) \
if( 0 > (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 > (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 > (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 > (_Val3_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val3_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val3_)); gnGlobal_ERROR_Counter++; return; } 

#define retERR_LTZ5( _Val0_,_Val1_,_Val2_,_Val3_,_Val4_) \
if( 0 > (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 > (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 > (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 > (_Val3_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val3_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val3_)); gnGlobal_ERROR_Counter++; return; } \
if( 0 > (_Val4_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val4_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val4_)); gnGlobal_ERROR_Counter++; return; }




#define ret0ERR_LTZ( __val__) \
if( 0 > (__val__) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__val__ " = %f )  < 0 \n", __FILE__,__FUNCTION__,__LINE__, (float)(__val__)); gnGlobal_ERROR_Counter++; return 0; }

#define ret0ERR_LTZ2( _Val0_,_Val1_) \
if( 0 > (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 > (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return 0; }

#define ret0ERR_LTZ3( _Val0_,_Val1_,_Val2_) \
if( 0 > (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 > (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 > (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return 0; }

#define ret0ERR_LTZ4( _Val0_,_Val1_,_Val2_,_Val3_) \
if( 0 > (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 > (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 > (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 > (_Val3_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val3_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val3_)); gnGlobal_ERROR_Counter++; return 0; } 

#define ret0ERR_LTZ5( _Val0_,_Val1_,_Val2_,_Val3_,_Val4_) \
if( 0 > (_Val0_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val0_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val0_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 > (_Val1_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val1_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val1_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 > (_Val2_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val2_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val2_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 > (_Val3_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val3_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val3_)); gnGlobal_ERROR_Counter++; return 0; } \
if( 0 > (_Val4_) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#_Val4_ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(_Val4_)); gnGlobal_ERROR_Counter++; return 0; }






#define ret0ERR_LEZ( __val__) \
if( 0 >= (__val__) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__val__ " = %f ) <= 0  \n", __FILE__,__FUNCTION__,__LINE__, (float)(__val__)); gnGlobal_ERROR_Counter++; return 0; }

#define ret0ERR_LT_ZERO( __val__) \
if( 0 > (__val__) ){ printf("ERROR!!!<%s,%s,%d> ,  ( "#__val__ " = %f )  < 0 \n", __FILE__,__FUNCTION__,__LINE__, (float)(__val__)); gnGlobal_ERROR_Counter++; return 0; }

#define RETV_ERR_CHK(__cond__) \
if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d>  !!!!"#__cond__ "!!!  \n", __FILE__,__FUNCTION__,__LINE__); }





#define retCHK(__cond__) if( (__cond__) ){ return ;  }
#define ret0CHK(__cond__) if( (__cond__) ){ return 0;  }




#define retERR_CHK(__cond__) if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ "  \n", __FILE__,__FUNCTION__,__LINE__); gnGlobal_ERROR_Counter++; return; }
#define ret0ERR_CHK(__cond__) if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ "  \n", __FILE__,__FUNCTION__,__LINE__); gnGlobal_ERROR_Counter++; return 0; }

#define retERR_CHKfree(__cond__) if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ "  \n", __FILE__,__FUNCTION__,__LINE__); gnGlobal_ERROR_Counter++; _NEW_FREE(); return; }
#define ret0ERR_CHKfree(__cond__) if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ "  \n", __FILE__,__FUNCTION__,__LINE__); gnGlobal_ERROR_Counter++;_NEW_FREE(); return 0; }



#define retERR_CHK2(____condition0____, ____condition1____) \
if( (____condition0____) ){ printf("ERROR!!!<%s,%s,%d> "#____condition0____ "  \n", __FILE__,__FUNCTION__,__LINE__); gnGlobal_ERROR_Counter++; return; }	\
if( (____condition1____) ){ printf("ERROR!!!<%s,%s,%d> "#____condition1____ "  \n", __FILE__,__FUNCTION__,__LINE__); gnGlobal_ERROR_Counter++; return; }

#define ret0ERR_CHK2(____condition0____, ____condition1____) \
if( (____condition0____) ){ printf("ERROR!!!<%s,%s,%d> "#____condition0____ "  \n", __FILE__,__FUNCTION__,__LINE__); gnGlobal_ERROR_Counter++; return 0; }	\
if( (____condition1____) ){ printf("ERROR!!!<%s,%s,%d> "#____condition1____ "  \n", __FILE__,__FUNCTION__,__LINE__); gnGlobal_ERROR_Counter++; return 0; }



#define retERR_STR(__string1__) { printf("ERROR!!!<%s,%s,%d>  <%s>  \n", __FILE__,__FUNCTION__,__LINE__, (char *)(__string1__)); gnGlobal_ERROR_Counter++; return; }
#define ret0ERR_STR(__string1__) { printf("ERROR!!!<%s,%s,%d>  <%s>  \n", __FILE__,__FUNCTION__,__LINE__, (char *)(__string1__)); gnGlobal_ERROR_Counter++; return 0; }

	

#define retERR_CHK_1STR(__cond__, __string1__)   if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ " , <%s>  \n", __FILE__,__FUNCTION__,__LINE__, (char *)(__string1__)); gnGlobal_ERROR_Counter++; return; }
#define retERR_CHK_1FLT(__cond__, __fval__) if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__fval__ ") = %f  \n", __FILE__,__FUNCTION__,__LINE__, (__fval__)); gnGlobal_ERROR_Counter++; return; }


#define retERR_CHK_1INT(__cond__, __ival__) if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__ival__ ") = %d  \n", __FILE__,__FUNCTION__,__LINE__, (__ival__)); gnGlobal_ERROR_Counter++; return; }

#define retERR_CHK_2INT(__cond__, __i0, __i1) if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__i0 ") = %d ,  ( "#__i1 ") = %d \n", __FILE__,__FUNCTION__,__LINE__, (__i0), (__i1)); gnGlobal_ERROR_Counter++; return; }

#define retERR_CHK_3INT(__cond__, __i0, __i1, __ival2__) \
if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__i0 ") = %d ,  ( "#__i1 ") = %d,  ( "#__ival2__ ") = %d \n", __FILE__,__FUNCTION__,__LINE__, (__i0), (__i1), (__ival2__)); gnGlobal_ERROR_Counter++; return; }


#define ret0ERR_CHK_1STR(__cond__, __string1__) \
if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ " , <%s>  \n", __FILE__,__FUNCTION__,__LINE__, (__string1__)); gnGlobal_ERROR_Counter++; return 0;}

#define ret0ERR_CHK_1INT(__cond__, __ival__) \
if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__ival__ ") = %d  \n", __FILE__,__FUNCTION__,__LINE__, (__ival__)); gnGlobal_ERROR_Counter++; return 0; }

#define ret0ERR_CHK_2INT(__cond__, __i0, __i1) \
if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ " ,  ( "#__i0 ") = %d ,  ( "#__i1 ") = %d \n", __FILE__,__FUNCTION__,__LINE__, (__i0), (__i1)); gnGlobal_ERROR_Counter++; return 0; }



#define RETV_ERROR_CHK1(__cond__, ____val____) \
if( (__cond__) ){ printf("ERROR!!!<%s,%s,%d> "#__cond__ "  \n",__FILE__,__FUNCTION__,__LINE__ ); gnGlobal_ERROR_Counter++; return (____val____);}



#endif /* __PERF_METRIC_COMMchk_H */


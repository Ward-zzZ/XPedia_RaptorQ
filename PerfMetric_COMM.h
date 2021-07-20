#ifndef __PERF_METRIC_COMM_H
#define __PERF_METRIC_COMM_H
/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>



#define UINT8   unsigned char
#define UINT32  unsigned int
#define UINT64  unsigned long
#define _UINT32 unsigned int
#define _UINT64 unsigned long

#ifdef __cplusplus 
extern "C" {
    #endif  

    UINT64 _rdtsc();
    int GERROR_chk(int iERRnum);

    // ******************************************************************************************************************************************************************************************************************
    int  BinFile_SaveMem(long* pFileBytes,char* vbDataBUFF, long lWriteBytes, char* strFileName, int isNewFile,int isSYNC);

    long loadBytes(long* pFileBytes,char* vbDataBUFF,long lOffsetBytes, long lReadBytes, char* strFileName);
    long loadINTS(char *strFileName, int  *vnData, int lIntNum, long OffsetFLT);
    long loadFLTs(char *strFileName, float *vfData, long lFltNum, long lOffset);

    #define saveFLTs(__pMEM__, _FltN_, _strFile_)    { long _lFileBytes_; BinFile_SaveMem(&_lFileBytes_,(char*)((float *)(__pMEM__)),sizeof(float)*(long)(_FltN_), _strFile_, 1,0); }  
    #define saveINTs(__pMEM__, _IntN_, _strFile_)    { long _lFileBytes_; BinFile_SaveMem(&_lFileBytes_,(char*)((int   *)(__pMEM__)),sizeof(int  )*(long)(_IntN_), _strFile_, 1,0); }  

    #define  _LOAD_INTS(__strfile,  __viData, __ilen,  __loffset)   loadINTS((char *)(__strfile), __viData, __ilen, __loffset);  __loffset += (__ilen);
    #define  _LOAD_FLTS(__strfile,  __vfData, __ilen,  __loffset)   loadFLTs((char *)(__strfile), __vfData, __ilen, __loffset);  __loffset += (__ilen);


    int  ReadBinaryFile_Flts(char *strFileName, float *vfData, int FltNUM, long lOffset);   
    int  ReadBinaryFile_INTS(char *strFileName, int *vnData, int FltNUM, long OffsetFLT);
    int  ReadBinaryFile_ByteNUM(char *strFileName);


    int  chkfile_exist(char *strFileName);
    long chkfile_bytes(char* strFileName);
    #define BinFile_GetSize(__strFile__)  chkfile_bytes(__strFile__)
    
    
    #define BinFile_WriteFlts(__pMEM__, _FltN_, _strFile_)    { long _lFileBytes_; BinFile_SaveMem(&_lFileBytes_,(char*)((float *)(__pMEM__)),sizeof(float)*(long)(_FltN_), _strFile_, 1,0); }  
    #define BinFile_AppendFlts(__pMEM__, _FltN_, _strFile_)   { long _lFileBytes_; BinFile_SaveMem(&_lFileBytes_,(char*)((float *)(__pMEM__)),sizeof(float)*(long)(_FltN_), _strFile_, 0,0); }  
    #define BinFile_AppendBytes(__pMEM__, _ByteN_, _strFile_) { long _lFileBytes_; BinFile_SaveMem(&_lFileBytes_,(char*)((__pMEM__)),sizeof(char)*(long)(_ByteN_), _strFile_, 0,0); }

    //#define dumpFLTS(_strFile_,__pMEM__, _FltN_, __isNEW)    { long _lFileBytes_; BinFile_SaveMem(&_lFileBytes_,(char*)((float *)(__pMEM__)),sizeof(float)*(long)(_FltN_), _strFile_, __isNEW,0); } 
    void dumpFLTS(char *strFile,float *pMEM, int FltN, int isNEW);

    void dumpMat(char *strFile,float *pMEM, int iRow, int iCol);
    void dumpIMat(char *strFile,int *pMEM, int iRow, int iCol);    
    void dumpCxM(char *strFile,float *pMEM, int iRow, int iCol);


    // ******************************************************************************************************************************************************************************************************************
    void  IVEC_sync2bin(int *piMEM, int VEClen, char *strFileName);
    void  BinFile_Slicing(char* strFileDST,char* strFileSRC, long lOffsetBYTES, long lSliceBYTES);
    void  SplitBinaryFile_InterF(char *strOutFileName, char *strInFileName, int nSliceDIV, int nSliceIDX, int nSliceNUM);
    int   Chk_LEZero_INTS(int num,...);
    int   Chk_LTZero_INTS(int num,...);

    // ******************************************************************************************************************************************************************************************************************

    //int Parse_Float(float *pfOUT,char *strSRC, char *strKey, char *strDelimitor);
    int Parse_Float(float   *pfOUT,char *strSRC_list[], char *strKey, char *strDelimitor, int iNUM);
    int Parse_Double(double *pdOUT,char *strSRC_list[], char *strKey, char *strDelimitor, int iNUM);
    int Parse_Number(int    *piOUT,char *strSRC_list[], char *strKey, char *strDelimitor, int iNUM);


    int Parse_Int(int *pnOUT,char *strSRC, char *strKey, char *strDelimitor);
    int Parse_Str(char *strOUT,char *strSRC, char *strKey, char *strDelimitor);

    // ******************************************************************************************************************************************************************************************************************

    int  VEC_chkvalid(float *vfVEC, int VEClen, float fMin, float fMax);
    int  IVEC_chkvalid(int *viVEC, int VEClen, int iMin, int iMax);
    int  IVEC_chkError(int *viVEC, int VEClen, int OPTn, int *viOPTs);



    void CompareFloats_Org(float* vfData_A, float* vfData_B, float fDiffRatio, int nSize);
    int  CompareBits_Org(int *vnSrc, int *vnDst, int nSize);
    int  CompareInts_Org(int *vnSrc, int *vnDst, int nSize);

    int  CompareBits(int *vnSrc, int *vnDst, int nSize);

    // ******************************************************************************************************************************************************************************************************************
    void  miQ_2DcurveS(float *vfXlist, float *vfYlist, int VEClen,int iColor, int islgY,int iCfgID, int iPlotID,char *strKEY);
    int   miQ_2DcurveSread(float *vfVx_list, float *vfVy_list, int VEClen, int *viVlen_list,int iMaxCurve, int iPlotOBJ, char *strTXTfile, int *pISlogY, int *piColor_list,  int isColor);


    void   PIXEL_insString(int* viPixels, int iW, int iH, char* strINFO);


    // ******************************************************************************************************************************************************************************************************************
    typedef struct  _stPDF
    {
        int    m_CNTR;
        int    m_PDFlen;
        float *m_vfCNTR;
        float  m_fFrom;
        float  m_fTO;
        float  m_fStep;
        float  m_fInvStep;
        char   m_strName[32];
    } stPDF;

    #define _PDF_cntr(__psPDF__)  (__psPDF__)->m_CNTR

    void   PDF_new(stPDF *psPDF, float fFrom, float fTO, int PDFlen, char *strName);
    void   PDF_free(stPDF *psPDF);
    void   PDF_reset(stPDF *psPDF);
    void   PDF_run(stPDF *psPDF, float *vfVECsrc, int VEClen);
    float  PDF_getProb(stPDF *psPDF, float fProb);
    int    PDF_dump(float* vfPDF, int iMaxLEN, stPDF *psPDF, int isReset);
    
    void   PDF_gen(float* vfCxPDF, float* vfVEC_s, int Vlen, float fRngMin, float fRngMax, int PDFlen, int isPDFxy, int isCDF=0);

    #define CxCDF_gen(__CxCDF, __vfData, __Vlen, __fmin, __fmax, __CDFlen)  PDF_gen(__CxCDF, __vfData, __Vlen, __fmin, __fmax, __CDFlen, 1,1)


    int    GPDF_dump(float* vfPDF, int iMaxLEN, char* strGPDFname);


    // ******************************************************************************************************************************************************************************************************************




    #ifdef __cplusplus 
}
#endif  

#include "PerfMetric_COMMavx.h"
#include "PerfMetric_COMMmem.h"
#include "PerfMetric_COMMchk.h"
#include "PerfMetric_COMMgdb.h"
#include "PerfMetric_COMMstr.h"

#include "PerfMetric_GPARAM.h"
#include "PerfMetric_GTS.h"
#include "PerfMetric_GMEM.h"
//#include "PerfMetric_GSTRUC.h"  // move to RadioSignalBase.h




#define _LOOPUP_LT(__counter__, __from__, __to__)  for((__counter__) = (__from__);  (__counter__) < (__to__); (__counter__) ++ ) 
#define _LOOPDOWN_GE(__counter__, __from__, __to__) for((__counter__) = (__from__);  (__counter__) >= (__to__); (__counter__) -- ) 


#define __STR(__str1__)  ((char *)#__str1__)
#define STR_disp(__strDISP__) printf("  %s \n",(char *)__strDISP__)
#define STR_dispX(__nID__,__strDISP__) printf("[%d]  %s \n",(int)(__nID__),(char *)__strDISP__)
#define _strEQ()  "="
#define _strFUSE(__strA__,__strB__)  (__strA__  __strB__)
#define CAT2STRS(__str1__,__str2__) __str1__##__str2__


#define _ABSOP(____data____) ((____data____) < 0 ? (-1)*(____data____) : (____data____))

#define SQROP(____data____)  ((____data____)*(____data____))

#define ABSOP(____data____) ((____data____) < 0 ? (-1)*(____data____) : (____data____))
#define LLROP(____data____) ((____data____)*(____data____)*__inv_2xNoisePwr__)

#define SIGNOP(____data____) ((____data____) < 0 ? (-1.0) : (1.0))

#define _ROUNDOP(__fval__)  ( (0 <= (__fval__)) ? (int)((__fval__)+0.5) :  (int)((__fval__)-0.5)  )
#define _DIVOP(__numerator__,__denominator__)  ( ( 0 != (__denominator__) ) ?  ((float)(__numerator__)/(float)(__denominator__)) : 1.0 )
#define _DIVOPHD(__numerator__,__denominator__)  ( ( 0 != (__denominator__) ) ?  ((double)(__numerator__)/(double)(__denominator__)) : 1.0 )

#define _INVOP(__denominator__)  ( ( 0 != (__denominator__) ) ?  (1.0/(float)(__denominator__)) : 1.0 )

#define _INVOP_X(__denominator__)  ( ( 0 != (__denominator__) ) ?  (1.0/(float)(__denominator__)) : 1.0e6 )

#define _LOG10_OP(__fval__)  ( (0 < (__fval__)) ? 10*log10(__fval__) :  -100.0  )



#define MINOP(____AA____,____BB____) ((____AA____) <= (____BB____) ? (____AA____) : (____BB____))
#define MAXOP(____AA____,____BB____) ((____AA____) >= (____BB____) ? (____AA____) : (____BB____))
#define RNGOP(__val__,__min__,__max__)  __val__ = MAXOP(__val__,__min__); __val__ = MINOP(__val__,__max__);


#define MICRO_SWAP_A_B(____AA____, ____BB____, ____tmp____)  (____tmp____) = (____BB____); (____BB____)  = (____AA____); (____AA____)  = (____tmp____);

#define MICRO_SWAP_A_B_CONJ(____AA____, ____BB____, ____tmp____)  (____tmp____) = (____BB____); (____BB____)  = -1.0*(____AA____); (____AA____)  = -1.0*(____tmp____);

#define SWAP_OP(____AA____, ____BB____, ____tmp____)         (____tmp____) = (____BB____); (____BB____)  = (____AA____); (____AA____)  = (____tmp____);



#define CHAR_CP(____vnFROM____, ____vnTO____,__num__)  memcpy(____vnTO____,____vnFROM____,sizeof(char)*(__num__));
#define INT_CP(____vnFROM____, ____vnTO____,__num__)   memcpy(____vnTO____,____vnFROM____,sizeof(int)*(__num__));
#define FLT_CP(__vfFrom__, __vfTO__,__num__)   memcpy(__vfTO__,__vfFrom__,sizeof(float)*(__num__));
#define FLT_ZERO(____vfData____, __num__)              memset(____vfData____,'\0',sizeof(float)*(__num__));

#define FLT_CPZ(__vfFrom__, __vfTO__,__num__,__TOlen__) memcpy(__vfTO__,__vfFrom__,sizeof(float)*(__num__)); if( (__TOlen__) > (__num__) ) { memset((__vfTO__)+(__num__),'\0',sizeof(float)*((__TOlen__)-(__num__))); }


#define INT_ZERO(____vnData____, __num__)  memset(____vnData____,'\0',sizeof(int)*(__num__))
#define CHAR_ZERO(____vcData____, __num__) memset((char *)____vcData____,'\0',sizeof(char)*(__num__))

#define IVEC_zero(____vnData____, __num__)  memset(____vnData____,'\0',sizeof(int)*(__num__))

#define _GetRe_CxAmulCxB(__fA_I, __fA_Q, __fB_I,__fB_Q ) ((__fA_I)*(__fB_I) - (__fA_Q)*(__fB_Q))
#define _GetIm_CxAmulCxB(__fA_I, __fA_Q, __fB_I,__fB_Q ) ((__fA_I)*(__fB_Q) + (__fA_Q)*(__fB_I))

#define _GetRe_CxAmulCxBconj(__fA_I, __fA_Q, __fB_I,__fB_Q ) ((__fA_I)*(__fB_I) + (__fA_Q)*(__fB_Q))
#define _GetIm_CxAmulCxBconj(__fA_I, __fA_Q, __fB_I,__fB_Q ) (-(__fA_I)*(__fB_Q) + (__fA_Q)*(__fB_I))



#define _CxScale(__pCxO__, __pCxA__, __C__)  {  (__pCxO__)[0] = (__pCxA__)[0]*(__C__);    (__pCxO__)[1] = (__pCxA__)[1]*(__C__); }




#define _CxAmulCxB(__pCxO__, __pCxA__, __pCxB__) \
{ float __fA_I = (__pCxA__)[0]; float __fA_Q = (__pCxA__)[1];  float __fB_I = (__pCxB__)[0]; float __fB_Q = (__pCxB__)[1]; \
    (__pCxO__)[0] = ((__fA_I)*(__fB_I) - (__fA_Q)*(__fB_Q));   (__pCxO__)[1] =  ((__fA_I)*(__fB_Q) + (__fA_Q)*(__fB_I)); \
}

#define _CxAmulconjCxB(__pCxO__, __pCxA__, __pCxB__) \
{ float __fA_I = (__pCxA__)[0]; float __fA_Q = (__pCxA__)[1];  float __fB_I = (__pCxB__)[0]; float __fB_Q = (__pCxB__)[1]; \
    (__pCxO__)[0] = ((__fA_I)*(__fB_I) + (__fA_Q)*(__fB_Q));   (__pCxO__)[1] =  ( (__fA_Q)*(__fB_I) - (__fA_I)*(__fB_Q) ); \
}

#define _CxAaddCxB(__pCxO__, __pCxA__, __pCxB__) (__pCxO__)[0] = (__pCxA__)[0]+(__pCxB__)[0];(__pCxO__)[1] = (__pCxA__)[1]+(__pCxB__)[1];
#define _CxAsubCxB(__pCxO__, __pCxA__, __pCxB__) (__pCxO__)[0] = (__pCxA__)[0]-(__pCxB__)[0];(__pCxO__)[1] = (__pCxA__)[1]-(__pCxB__)[1];

#define _GetIQPower(__fI__,__fQ__)   ( (__fI__)*(__fI__) + (__fQ__)*(__fQ__) )
#define _GetCxPower(__CxVal__)   ((__CxVal__)[0]*(__CxVal__)[0] + (__CxVal__)[1]*(__CxVal__)[1])
#define GetCxPowerHD(__fCxPwr,__CxVal__)   { double __dI = (double)(__CxVal__)[0];   double __dQ = (double)(__CxVal__)[1];  __fCxPwr = (float)(__dI*__dI+__dQ*__dQ); }



#define _CxAMP(__CxVal__)  sqrt( ((__CxVal__)[0]*(__CxVal__)[0] + (__CxVal__)[1]*(__CxVal__)[1]) )
#define _CxInv(__CxInv, __CxVal__, __fscale)   { float __fPWRinv = _GetCxPower(__CxVal__);  __fPWRinv = __fscale*_DIVOP(1.0,__fPWRinv);  __CxInv[0] = __CxVal__[0]*__fPWRinv;  __CxInv[1] = -1.0*__CxVal__[1]*__fPWRinv; }

#define _CxInvHD(__CxInv, __CxVal__, __fscale)   { \
double __dI = (double)(__CxVal__)[0];   double __dQ = (double)(__CxVal__)[1];  \
double __fPWRinv = __dI*__dI+__dQ*__dQ;  __fPWRinv = __fscale*_DIVOPHD(1.0,__fPWRinv);  __CxInv[0] = (float)(__dI*__fPWRinv);  __CxInv[1] = (float)(-1.0*__dQ*__fPWRinv); \
}



#define _CxSquare(__pCxO__, __pCxA__) \
{ float __fA_I = (__pCxA__)[0]; float __fA_Q = (__pCxA__)[1];  \
    (__pCxO__)[0] = ((__fA_I)*(__fA_I) - (__fA_Q)*(__fA_Q));   (__pCxO__)[1] =  ((__fA_I)*(__fA_Q) + (__fA_Q)*(__fA_I)); \
}




#define ENUM_DEF(__enum_name__,...)  enum __enum_name__ { __VA_ARGS__, __enum_name__##_LEN };  const char __enum_name__##_names[]=#__VA_ARGS__;
#define ENUM_LEN(__enum_name__)  __enum_name__##_LEN 
#define ENUM_name(__strITEMname,__enum_name__, __ID)    char __strITEMname[50];  strs_get(__strITEMname, 50,__ID , (char*)__enum_name__##_names, (char*)",",30);




#define _CHK_OPT1(__iVAR__,__opt0__)                                      (  (__opt0__) == (__iVAR__))
#define _CHK_OPT2(__iVAR__,__opt0__,__opt1__)                             ( ((__opt0__) == (__iVAR__)) || ((__opt1__) == (__iVAR__)) )
#define _CHK_OPT3(__iVAR__,__opt0__,__opt1__,__opt2__)                    ( ((__opt0__) == (__iVAR__)) || ((__opt1__) == (__iVAR__)) || ((__opt2__) == (__iVAR__)) )
#define _CHK_OPT4(__iVAR__,__opt0__,__opt1__,__opt2__,__opt3__)           ( ((__opt0__) == (__iVAR__)) || ((__opt1__) == (__iVAR__)) || ((__opt2__) == (__iVAR__)) || ((__opt3__) == (__iVAR__)) )
#define _CHK_OPT5(__iVAR__,__opt0__,__opt1__,__opt2__,__opt3__,__opt4__)  ( ((__opt0__) == (__iVAR__)) || ((__opt1__) == (__iVAR__)) || ((__opt2__) == (__iVAR__)) || ((__opt3__) == (__iVAR__)) || ((__opt4__) == (__iVAR__)) )


#define INTS_2FLTS(__vfVEC__, __iVEC__, __VEClen__)  { int _jjj_; for(_jjj_=0; _jjj_ < (__VEClen__); _jjj_++) { (__vfVEC__)[_jjj_] = (float)(__iVEC__)[_jjj_];   } }


#define _pSTRUC_SET(__psSTRUC__, __STRUCname__, __pMEM__)  MEMCHK(__pMEM__, (sizeof(__STRUCname__)>>2));    __STRUCname__ *__psSTRUC__ = (__STRUCname__ *)(__pMEM__)


#define PRINT_INTVEC(__vnDATA__,__row_size__,__total_size__)  \
printf(""#__vnDATA__" = [ "); \
{   int __jj__,__nRowPtr__; __nRowPtr__ = 0; \
    if( __total_size__ > __row_size__ ){ printf("\n"); } \
    for( __jj__ = 0; __jj__ < __total_size__; __jj__++) { \
        printf("%d,",__vnDATA__[__jj__]); __nRowPtr__++; \
        if( __nRowPtr__ == __row_size__){ printf("\n"); __nRowPtr__ = 0;} \
    }   printf(" ]; \n"); \
}   
#define PRINT_FLTVEC(__vfDATA__,__row_size__,__total_size__)  \
printf(""#__vfDATA__" = [ "); \
{   int __jj__,__nRowPtr__;     __nRowPtr__ = 0; \
    if( __total_size__ > __row_size__ ){ printf("\n"); } \
    for( __jj__ = 0; __jj__ < __total_size__; __jj__++) {   \
        printf("%+.3e,",__vfDATA__[__jj__]); __nRowPtr__++; \
        if( __nRowPtr__ == __row_size__){ printf("\n"); __nRowPtr__ = 0;} \
    }   printf(" ]; \n"); \
}

#define PRINT_1INT(__var_name__)  printf("  "#__var_name__" = %d  \n",(int) (__var_name__));

#define PRINT_1FLT(__var_name__)  printf("  "#__var_name__" = %e  \n",(float) (__var_name__));

#define COMPARE_2FLTVEC(____vfSRC____, ____vfDest____, ____Size____,____MaxRelErrRatio____)  \
{   int  ____nMaxRelPOS____;float ____fMaxRelErr____ =  MaxRelError(&____nMaxRelPOS____, ____vfSRC____, ____vfDest____, ____Size____); \
    if( ____MaxRelErrRatio____ < ____fMaxRelErr____ ) {  printf("    RelError[@%d] = %e   btw "#____vfSRC____" (%e)  and "#____vfDest____" (%e) , total %d items for comparison \n", ____nMaxRelPOS____, ____fMaxRelErr____, ____vfSRC____[____nMaxRelPOS____], ____vfDest____[____nMaxRelPOS____],____Size____);   } \
}






#define _PI_         3.1415926535898
#define _2PI_        6.28318530717959
#define __HalfPI__   1.57079632679490
#define ____EXP____  2.71828182845905



#endif /* __PERF_METRIC_COMM_H */
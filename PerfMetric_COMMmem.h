#ifndef __PERF_METRIC_COMMmem_H
#define __PERF_METRIC_COMMmem_H
/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */

#include<sys/ipc.h>
#include<sys/shm.h>

#define MAX_LOCALPTR_NUM 1000
extern int gnGlobal_CloseLoopMEMUsage_Balance;
extern int gnGlobal_OpenLoopMEMUsage_Balance; 
extern int giGlobal_MEMCHK_ERR;
#define MEMCHK_MASK  20050523


#define GLOBAL_MAX_MEMPTR_NUM 4096
#define GLOBAL_MAX_GPDF_NUM   100

typedef struct _stGMEM
{
    int    m_len;
    int    m_key;    
    float* m_pfMEM;        
} stGMEM;

extern stGMEM gvsGMEMs_LIST[]; extern int    gnGlobal_MEMPtr_Counter;    extern float* gpfGlobal_MEMPtr_LIST[]; 
extern stPDF  gvsGPDFs_LIST[]; extern int    gnGlobal_GPDF_Counter;



void GlobalMEMPtr_Free();

// ********************************************************************************************************************************************************************************************************  
#define GPDF_REG(__GPDFname__)  int  iGPDFkey_##__GPDFname__ = -1;
#define GPDF_RUN(__GPDFname__, __vfData, __Vlen, __fFrom, __fTO,__PDFlen ) \
if( ( 0 > iGPDFkey_##__GPDFname__  ) || (gnGlobal_GPDF_Counter <= iGPDFkey_##__GPDFname__) ) { \
	if( GLOBAL_MAX_GPDF_NUM > gnGlobal_GPDF_Counter ) {  \
		PDF_new(&gvsGPDFs_LIST[gnGlobal_GPDF_Counter], __fFrom, __fTO,__PDFlen,(char *)#__GPDFname__);  iGPDFkey_##__GPDFname__ = gnGlobal_GPDF_Counter;  gnGlobal_GPDF_Counter++; \
		PDF_run(&gvsGPDFs_LIST[iGPDFkey_##__GPDFname__], __vfData, __Vlen); \
	}  \
    else { printf("ERROR!!!<%s,%s,%d>  failed to create %d-th  GPDF ... "#__GPDFname__"!!!  \n ",__FILE__,__FUNCTION__,__LINE__,gnGlobal_GPDF_Counter+1); }  \
} \
else {	PDF_run(&gvsGPDFs_LIST[iGPDFkey_##__GPDFname__], __vfData, __Vlen); }



// ********************************************************************************************************************************************************************************************************  
#define GMEM_REG(__GMEMname__)  stGMEM* psGMEM_##__GMEMname__ = 0;   int  iGMEMkey_##__GMEMname__ = 0;
#define GMEM_GET(__pfGMEM__, __GMEMname__ , __len__)    __pfGMEM__ = 0;  if( GMEM_exist(__GMEMname__) ) {  if(  GMEM_chk(__GMEMname__)  &&  ( (__len__) == GMEM_len(__GMEMname__) ) ) {  __pfGMEM__ = GMEM_ptr(__GMEMname__); } }
#define GMEM_GETchk(__pfGMEM__, __GMEMname__ ,__CHKID_) \
__pfGMEM__ = 0;  \
if( GMEM_exist(__GMEMname__) ) {  \
	if(  GMEM_chk(__GMEMname__)  &&  ( 0 < GMEM_len(__GMEMname__) ) ) {  __pfGMEM__ = GMEM_ptr(__GMEMname__); } else {  __CHKID_ = 0;  } \
} else { __CHKID_ = 0; } 


//#define GMEM_exist(__GMEMname__)  (0 < iGMEMkey_##__GMEMname__)  // a bug !!! killed by Duan Weiming in 2021-05-09
#define GMEM_exist(__GMEMname__)  (0 < iGMEMkey_##__GMEMname__)  && ( gnGlobal_MEMPtr_Counter >= iGMEMkey_##__GMEMname__ )
#define GMEM_chk(__GMEMname__)  ( iGMEMkey_##__GMEMname__ ==  psGMEM_##__GMEMname__->m_key)
#define GMEM_len(__GMEMname__)  ( psGMEM_##__GMEMname__->m_len)
#define GMEM_ptr(__GMEMname__)  ( psGMEM_##__GMEMname__->m_pfMEM)


#define GMEM_NEW(__pfGMEM__, __GMEMname__,__VarNUM__) \
psGMEM_##__GMEMname__ = 0;  iGMEMkey_##__GMEMname__ = 0;  __pfGMEM__ = 0; \
if( (GLOBAL_MAX_MEMPTR_NUM > gnGlobal_MEMPtr_Counter ) && (0 < __VarNUM__) ){  \
	float* __vfBUFF__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __vfBUFF__){ \
		gpfGlobal_MEMPtr_LIST[gnGlobal_MEMPtr_Counter] = (float *)	__vfBUFF__;  \
		int* _vnMEMMask_ =  (int *) __vfBUFF__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		gvsGMEMs_LIST[gnGlobal_MEMPtr_Counter].m_pfMEM = (float *)(_vnMEMMask_ + 2); 	gvsGMEMs_LIST[gnGlobal_MEMPtr_Counter].m_len = __VarNUM__;  gvsGMEMs_LIST[gnGlobal_MEMPtr_Counter].m_key = gnGlobal_MEMPtr_Counter+1; \
		psGMEM_##__GMEMname__  = &gvsGMEMs_LIST[gnGlobal_MEMPtr_Counter]; iGMEMkey_##__GMEMname__ = gvsGMEMs_LIST[gnGlobal_MEMPtr_Counter].m_key;  __pfGMEM__ = gvsGMEMs_LIST[gnGlobal_MEMPtr_Counter].m_pfMEM; \
		gnGlobal_MEMPtr_Counter++;   \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed allocate memory for "#__GMEMname__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  global memory for "#__GMEMname__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,gnGlobal_MEMPtr_Counter,(__VarNUM__));  }


//#define GMEM_NEW_INT(__VarName__,__VarNUM__) \
//__VarName__ = 0;   \
//if( (GLOBAL_MAX_MEMPTR_NUM > gnGlobal_MEMPtr_Counter ) && (0 < __VarNUM__) ){  \
//	float* __vfBUFF__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
//	if( __vfBUFF__){ \
//		gpfGlobal_MEMPtr_LIST[gnGlobal_MEMPtr_Counter] = (float *)	__vfBUFF__;  \
//		int* _vnMEMMask_ =  (int *) __vfBUFF__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
//		gvsGMEMs_LIST[gnGlobal_MEMPtr_Counter].m_pfMEM = (float *)(_vnMEMMask_ + 2); 	gvsGMEMs_LIST[gnGlobal_MEMPtr_Counter].m_len = __VarNUM__;  gvsGMEMs_LIST[gnGlobal_MEMPtr_Counter].m_key = gnGlobal_MEMPtr_Counter+1; \
//		__VarName__  = (int *)(_vnMEMMask_ + 2);  gnGlobal_MEMPtr_Counter++;   \
//	}   \
//	else{ printf("ERROR!!!<%s,%s,%d>  failed allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
//} \
//else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  global memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,gnGlobal_MEMPtr_Counter,(__VarNUM__));  }


//#define NEW_GMEM_FLT(__VarName__,__VarNUM__) \
//__VarName__ = 0; \
//if( (GLOBAL_MAX_MEMPTR_NUM > gnGlobal_MEMPtr_Counter ) && (0 < __VarNUM__) ){  \
//	float* __vfBUFF__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
//	if( __vfBUFF__){ \
//		gpfGlobal_MEMPtr_LIST[gnGlobal_MEMPtr_Counter] = (float *)	__vfBUFF__;  \
//		int* _vnMEMMask_ =  (int *) __vfBUFF__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
//		__VarName__ = (float *)(_vnMEMMask_ + 2); 	gnGlobal_MEMPtr_Counter++;  \
//	}   \
//	else{ printf("ERROR!!!<%s,%s,%d>  global memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
//} \
//else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  global memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,gnGlobal_MEMPtr_Counter,(__VarNUM__));  }


//#define NEW_GMEM_INT(__VarName__,__VarNUM__) \
//__VarName__ = 0; \
//if( (GLOBAL_MAX_MEMPTR_NUM > gnGlobal_MEMPtr_Counter ) && (0 < __VarNUM__) ){  \
//	float* __vfBUFF__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
//	if( __vfBUFF__){ \
//		gpfGlobal_MEMPtr_LIST[gnGlobal_MEMPtr_Counter] = (float *)	__vfBUFF__;  \
//		int* _vnMEMMask_ =  (int *) __vfBUFF__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
//		__VarName__ = (int *)(_vnMEMMask_ + 2); 	gnGlobal_MEMPtr_Counter++;  \
//	}   \
//	else{ printf("ERROR!!!<%s,%s,%d>  global memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
//} \
//else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  global memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,gnGlobal_MEMPtr_Counter,(__VarNUM__));  }


// ********************************************************************************************************************************************************************************************************  


// ********************************************************************************************************************************************************************************************************  
#define CLAIM_FLT(__vfVEC__, _Vlen_)  int __localMEM_##__vfVEC__[2+(_Vlen_)]; __localMEM_##__vfVEC__[0] = MEMCHK_MASK; __localMEM_##__vfVEC__[1] = _Vlen_; float *__vfVEC__ = (float *)(__localMEM_##__vfVEC__ + 2);
#define CLAIM_INT(__vnVEC__, _Vlen_)  int __localMEM_##__vnVEC__[2+(_Vlen_)]; __localMEM_##__vnVEC__[0] = MEMCHK_MASK; __localMEM_##__vnVEC__[1] = _Vlen_; int *__vnVEC__ = (int *)(__localMEM_##__vnVEC__ + 2);


#define CLAIM_IVEC(_Vlen_,__iVEC__, ...)  int   __iVEC__[_Vlen_] =  {__VA_ARGS__};
#define CLAIM_VEC(_Vlen_,__vfVEC__, ...)  float __vfVEC__[_Vlen_] =  {__VA_ARGS__};


#define CLAIM_INT0(__vnVEC__, _Vlen_)  \
int __localMEM_##__vnVEC__[2+(_Vlen_)]; 	__localMEM_##__vnVEC__[0] = MEMCHK_MASK;  __localMEM_##__vnVEC__[1] = _Vlen_; \
int *__vnVEC__ = (int *)(__localMEM_##__vnVEC__ + 2);  memset(__vnVEC__,'\0',sizeof(int)*(_Vlen_));

#define CLAIM_STR(__strmem__, __STRlen__)  \
int  __localMEM_##__strmem__[2+((__STRlen__)>>2)+2]; 	__localMEM_##__strmem__[0] = MEMCHK_MASK;  __localMEM_##__strmem__[1] = __STRlen__; \
char *__strmem__ = (char *)(__localMEM_##__strmem__ + 2);  memset(__strmem__,'\0',sizeof(char)*(__STRlen__));


#define CLAIM_pSTRU0(__pmem__, __STRUCtype__)  \
int  __localMEM_##__pmem__[2+((sizeof(__STRUCtype__)>>2)+2)];    __localMEM_##__pmem__[0] = MEMCHK_MASK;  __localMEM_##__pmem__[1] = ((sizeof(__STRUCtype__)>>2)+2); \
int *__pmem__ = (int *)(__localMEM_##__pmem__ + 2);  memset(__pmem__,'\0',sizeof(int)*((sizeof(__STRUCtype__)>>2)+2));

// ********************************************************************************************************************************************************************************************************  


#define _NEW_INIT() \
float*  ____vfLocalMEMLST[MAX_LOCALPTR_NUM]; ____vfLocalMEMLST[0] = 0; \
int      ____nLOCALMEM_NUM = 0;


#define _NEW_FREE() \
{ int ____jj____; \
	for( ____jj____ = 0; ____jj____ < ____nLOCALMEM_NUM; ____jj____++){ \
		if( ____vfLocalMEMLST[____jj____] ){ free(____vfLocalMEMLST[____jj____]); ____vfLocalMEMLST[____jj____] = 0;  gnGlobal_CloseLoopMEMUsage_Balance--; } \
	} \
	____nLOCALMEM_NUM = 0; \
}

#define _RET_FREE() \
_NEW_FREE()  return;

#define _RET0_FREE() \
_NEW_FREE()  return 0;



//#define _NEW_ERRfail(__VarName__,__VarNUM__) printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); 
//#define _NEW_ERRfull(__VarName__,__VarNUM__) printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(int)(__VarNUM__));  
//#define _NEW_MASKi(__VarName__, __VarNUM__)   __VarName__ = (int   *)malloc(sizeof(float)*(2+(__VarNUM__))); if( __VarName__){ int* _vnMEMMask_ =  (int *) __VarName__;  _vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; __VarName__ = (int *   )(_vnMEMMask_ + 2); ____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; } else { _NEW_ERRfail(__VarName__,__VarNUM__) }
//#define _NEW_MASKi0(__VarName__, __VarNUM__)  __VarName__ = (int   *)malloc(sizeof(float)*(2+(__VarNUM__))); if( __VarName__){ int* _vnMEMMask_ =  (int *) __VarName__;  _vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; __VarName__ = (int *   )(_vnMEMMask_ + 2); ____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++;   memset(__VarName__,'\0',sizeof(int)*(__VarNUM__)); } else { _NEW_ERRfail(__VarName__,__VarNUM__) }
//#define _NEW_MASKf(__VarName__, __VarNUM__)   __VarName__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); if( __VarName__){ int* _vnMEMMask_ =  (int *) __VarName__;  _vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; __VarName__ = (float * )(_vnMEMMask_ + 2); ____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; } else { _NEW_ERRfail(__VarName__,__VarNUM__) }
//#define _NEW_MASKf0(__VarName__, __VarNUM__)  __VarName__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); if( __VarName__){ int* _vnMEMMask_ =  (int *) __VarName__;  _vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; __VarName__ = (float * )(_vnMEMMask_ + 2); ____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++;   memset(__VarName__,'\0',sizeof(int)*(__VarNUM__)); } else { _NEW_ERRfail(__VarName__,__VarNUM__) }
//#define _NEW_INT(__VarName__,__VarNUM__)    int*    __VarName__ = 0;  if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){ _NEW_MASKi( __VarName__, __VarNUM__)  } else { _NEW_ERRfull(__VarName__,__VarNUM__) }
//#define _NEW_INT0(__VarName__,__VarNUM__)   int*    __VarName__ = 0;  if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){ _NEW_MASKi0(__VarName__, __VarNUM__)  } else { _NEW_ERRfull(__VarName__,__VarNUM__) }
//#define _NEW_FLT(__VarName__,__VarNUM__)    float*  __VarName__ = 0;  if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){ _NEW_MASKf( __VarName__, __VarNUM__)  } else { _NEW_ERRfull(__VarName__,__VarNUM__) }
//#define _NEW_FLT0(__VarName__,__VarNUM__)   float*  __VarName__ = 0;  if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){ _NEW_MASKf0(__VarName__, __VarNUM__)  } else { _NEW_ERRfull(__VarName__,__VarNUM__) }

// the following does not work !!!
//#define _NEW_INT0(__VarName__,__VarNUM__) \
//int*  __VarName__ = 0;  \
//if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
//	_NEW_MASKi0(__VarName__, __VarNUM__) \
//} \
//else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(int)(__VarNUM__));  }




#define _NEW_INT(__VarName__,__VarNUM__) \
int*  __VarName__ = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (int *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;	\
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (int *)(_vnMEMMask_ + 2); \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} \
else{ 	  printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }


#define _NEW_INT0(__VarName__,__VarNUM__) \
int*  __VarName__ = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (int *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)__VarName__;int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (int *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__VarName__,'\0',sizeof(int)*(__VarNUM__)); \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(int)(__VarNUM__));  }





#define _NEW_BMP(__VarName__,__iW,__iH) \
int*  __VarName__ = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && ( 0 < (__iW)*(__iH) ) ){  \
	__VarName__ = (int *)malloc(sizeof(float)*(2+((__iW)*(__iH)+2))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;	\
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = ((__iW)*(__iH)+2); \
		__VarName__ = (int *)(_vnMEMMask_ + 2);   __VarName__[0]=__iW; __VarName__[1]=__iH; \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of  %d+2 \n ",__FILE__,__FUNCTION__,__LINE__,((__iW)*(__iH))); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of  %d+2 \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,((__iW)*(__iH)));  }



#define _NEW_STRU(__struName__,__STRUtype__,__struNUM__) \
__STRUtype__*  __struName__ = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __struNUM__) ){  \
	int __strucFLTnum__ = (sizeof(__STRUtype__) >> 2); if( sizeof(__STRUtype__) > __strucFLTnum__*4 ) { __strucFLTnum__ += 1; } \
	int __fltNUM__ = __strucFLTnum__*(__struNUM__);  \
	float* __VarName__ = (float *)malloc(sizeof(float)*(2+(__fltNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;	\
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __fltNUM__; \
		__struName__ = (__STRUtype__*)((float *)(_vnMEMMask_ + 2)); \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__struName__" with size of "#__struNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__struNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__struName__" with size of "#__struNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__struNUM__));  }




#define _NEW2_INT0(__VarName__,__Vec1,__VarNUM__) \
int*  __VarName__ = 0; int*  __Vec1 = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (int *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)__VarName__;int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (int *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__VarName__,'\0',sizeof(int)*(__VarNUM__)); \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  } \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__Vec1 = (int *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __Vec1){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)__Vec1;int* _vnMEMMask_ =  (int *) __Vec1; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__Vec1 = (int *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__Vec1,'\0',sizeof(int)*(__VarNUM__)); \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__Vec1" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__Vec1" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }


#define _NEW3_INT0(__VarName__,__Vec1,__Vec2,__VarNUM__) \
int*  __VarName__ = 0; int*  __Vec1 = 0; int*  __Vec2 = 0; \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (int *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (int *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__VarName__,'\0',sizeof(int)*(__VarNUM__)); \
	} else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
}  else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  } \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__Vec1 = (int *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __Vec1){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__Vec1;int* _vnMEMMask_ =  (int *) __Vec1; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__Vec1 = (int *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__Vec1,'\0',sizeof(int)*(__VarNUM__)); \
	} else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__Vec1" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__Vec1" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  } \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__Vec2 = (int *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __Vec2){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__Vec2;int* _vnMEMMask_ =  (int *) __Vec2; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__Vec2 = (int *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__Vec2,'\0',sizeof(int)*(__VarNUM__)); \
	}  else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__Vec2" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__Vec2" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }


#define _NEW2_FLT0(__VarName__,__Vec1,__VarNUM__) \
float*  __VarName__ = 0; float*  __Vec1 = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (float *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__VarName__,'\0',sizeof(int)*(__VarNUM__)); \
	}   else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
}       else{ printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  } \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__Vec1 = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __Vec1){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__Vec1;int* _vnMEMMask_ =  (int *) __Vec1; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__Vec1 = (float *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__Vec1,'\0',sizeof(int)*(__VarNUM__)); \
	}   else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__Vec1" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
}       else{ printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__Vec1" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  } 



#define _NEW3_FLT0(__VarName__,__Vec1,__Vec2,__VarNUM__) \
float*  __VarName__ = 0; float*  __Vec1 = 0; float*  __Vec2 = 0; \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  __VarName__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (float *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__VarName__,'\0',sizeof(int)*(__VarNUM__)); \
	}   else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
}       else{ printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  } \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  __Vec1 = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __Vec1){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__Vec1;int* _vnMEMMask_ =  (int *) __Vec1; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__Vec1 = (float *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__Vec1,'\0',sizeof(int)*(__VarNUM__)); \
	}   else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__Vec1" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
}       else{ printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__Vec1" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  } \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  __Vec2 = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __Vec2){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__Vec2;int* _vnMEMMask_ =  (int *) __Vec2; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__Vec2 = (float *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__Vec2,'\0',sizeof(int)*(__VarNUM__)); \
	}   else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__Vec2" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
}       else{ printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__Vec2" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }


#define _NEW4_FLT0(__VarName__,__Vec1,__Vec2,__Vec3,__VarNUM__) \
float*  __VarName__ = 0; float*  __Vec1 = 0; float*  __Vec2 = 0;  float*  __Vec3 = 0; \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  __VarName__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (float *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__VarName__,'\0',sizeof(int)*(__VarNUM__)); \
	}   else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
}       else{ printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  } \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  __Vec1 = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __Vec1){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__Vec1;int* _vnMEMMask_ =  (int *) __Vec1; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__Vec1 = (float *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__Vec1,'\0',sizeof(int)*(__VarNUM__)); \
	}   else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__Vec1" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
}       else{ printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__Vec1" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  } \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  __Vec2 = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __Vec2){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__Vec2;int* _vnMEMMask_ =  (int *) __Vec2; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__Vec2 = (float *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__Vec2,'\0',sizeof(int)*(__VarNUM__)); \
	}   else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__Vec2" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
}       else{ printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__Vec2" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  } \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  __Vec3 = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __Vec3){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__Vec3;int* _vnMEMMask_ =  (int *) __Vec3; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__Vec3 = (float *)(_vnMEMMask_ + 2); 	____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; 	memset(__Vec3,'\0',sizeof(int)*(__VarNUM__)); \
	}   else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__Vec3" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
}       else{ printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__Vec3" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }



#define _NEW_FLT(__VarName__,__VarNUM__) \
float*  __VarName__ = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;  \
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (float *)(_vnMEMMask_ + 2); \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }



#define _NEW_DUMP0(__VarName__,__VarNUM__) \
float*  __VarName__ = 0; int  __localDUMPcnt_##__VarName__ = 0; int  __localDUMPlen_##__VarName__ = __VarNUM__; \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;  \
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (float *)(_vnMEMMask_ + 2); \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
		memset(__VarName__,'\0',sizeof(float)*(__VarNUM__)); \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }


#define _DUMP_ADD(__VarName__, __vfData, __Vlen)  \
if( ( __localDUMPcnt_##__VarName__ + (__Vlen)) <= __localDUMPlen_##__VarName__ ) { \
    memcpy(__VarName__ + __localDUMPcnt_##__VarName__,__vfData,sizeof(float)*(__Vlen));  __localDUMPcnt_##__VarName__ += (__Vlen); \
}  else { 	printf("ERROR!!!<%s,%s,%d>  dump overflow !!!  "#__VarName__" with size of %d \n ",__FILE__,__FUNCTION__,__LINE__,__localDUMPlen_##__VarName__);  }

#define _DUMP_VEC(__VarName__, __vfData, __Vlen)  \
if( ( __localDUMPcnt_##__VarName__ + (__Vlen)) <= __localDUMPlen_##__VarName__ ) { \
    memcpy(__VarName__ + __localDUMPcnt_##__VarName__,__vfData,sizeof(float)*(__Vlen));  __localDUMPcnt_##__VarName__ += (__Vlen); \
}  else { 	printf("ERROR!!!<%s,%s,%d>  dump overflow !!!  "#__VarName__" with size of %d \n ",__FILE__,__FUNCTION__,__LINE__,__localDUMPlen_##__VarName__);  }


#define _DUMP_FLT(__VarName__, __fval)  \
if( ( __localDUMPcnt_##__VarName__ + 1) <= __localDUMPlen_##__VarName__ ) { \
    __VarName__[__localDUMPcnt_##__VarName__] = __fval;  __localDUMPcnt_##__VarName__ += 1; \
}  else { 	printf("ERROR!!!<%s,%s,%d>  dump overflow !!!  "#__VarName__" with size of %d \n ",__FILE__,__FUNCTION__,__LINE__,__localDUMPlen_##__VarName__);  }




#define _DUMP_ADD0(__VarName__,  __Vlen)  \
if( ( __localDUMPcnt_##__VarName__ + (__Vlen)) <= __localDUMPlen_##__VarName__ ) { \
    memset(__VarName__ + __localDUMPcnt_##__VarName__,'\0',sizeof(float)*(__Vlen));  __localDUMPcnt_##__VarName__ += (__Vlen); \
}  else { 	printf("ERROR!!!<%s,%s,%d>  dump overflow !!!  "#__VarName__" with size of %d \n ",__FILE__,__FUNCTION__,__LINE__,__localDUMPlen_##__VarName__);  }



#define _DUMP_load(__strfile, __vfDUMP, __ilen, __loffset) \
loadFLTs(__strfile, __vfDUMP, __ilen, __loffset);  __localDUMPcnt_##__vfDUMP = 0;

#define _DUMP_popVEC(__VarName__, __vfData, __Vlen)  \
if( ( __localDUMPcnt_##__VarName__ + (__Vlen)) <= __localDUMPlen_##__VarName__ ) { \
    __vfData = __VarName__ + __localDUMPcnt_##__VarName__;  __localDUMPcnt_##__VarName__ += (__Vlen); \
}  else { 	printf("ERROR!!!<%s,%s,%d>  dump overflow !!!  "#__VarName__" with size of %d \n ",__FILE__,__FUNCTION__,__LINE__,__localDUMPlen_##__VarName__);  }

#define _DUMP_popINT(__VarName__, __iData)  \
if( ( __localDUMPcnt_##__VarName__ + 1) <= __localDUMPlen_##__VarName__ ) {    \
	int *__piMEM__ = (int *)(__VarName__ + __localDUMPcnt_##__VarName__);  __iData = __piMEM__[0];  __localDUMPcnt_##__VarName__ += 1; \
}  else { 	printf("ERROR!!!<%s,%s,%d>  dump overflow !!!  "#__VarName__" with size of %d \n ",__FILE__,__FUNCTION__,__LINE__,__localDUMPlen_##__VarName__);  }


#define _MEM_2INT(_pV,_V,_V1)                                   _V=(_pV)[0];_V1=(_pV)[1];
#define _MEM_3INT(_pV,_V,_V1,_V2)                               _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];
#define _MEM_4INT(_pV,_V,_V1,_V2,_V3)                           _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];
#define _MEM_5INT(_pV,_V,_V1,_V2,_V3,_V4)                       _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];
#define _MEM_6INT(_pV,_V,_V1,_V2,_V3,_V4,_V5)                   _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];
#define _MEM_7INT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6)               _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];
#define _MEM_8INT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7)           _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];_V7=(_pV)[7];
#define _MEM_9INT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8)       _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];_V7=(_pV)[7];_V8=(_pV)[8];
#define _MEM_10INT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8,_V9)  _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];_V7=(_pV)[7];_V8=(_pV)[8];_V9=(_pV)[9];


#define MEM_1INT(_pV,_V)                              int _V=(_pV)[0];
#define MEM_2INT(_pV,_V,_V1)                          int _V,_V1;                         _V=(_pV)[0];_V1=(_pV)[1];
#define MEM_3INT(_pV,_V,_V1,_V2)                      int _V,_V1,_V2;                     _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];
#define MEM_4INT(_pV,_V,_V1,_V2,_V3)                  int _V,_V1,_V2,_V3;                 _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];
#define MEM_5INT(_pV,_V,_V1,_V2,_V3,_V4)              int _V,_V1,_V2,_V3,_V4;             _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];
#define MEM_6INT(_pV,_V,_V1,_V2,_V3,_V4,_V5)          int _V,_V1,_V2,_V3,_V4,_V5;         _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];
#define MEM_7INT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6)      int _V,_V1,_V2,_V3,_V4,_V5,_V6;     _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];
#define MEM_8INT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7)  int _V,_V1,_V2,_V3,_V4,_V5,_V6,_V7; _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];_V7=(_pV)[7];
#define MEM_9INT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8)       int _V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8;     _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];_V7=(_pV)[7];_V8=(_pV)[8];
#define MEM_10INT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8,_V9)  int _V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8,_V9; _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];_V7=(_pV)[7];_V8=(_pV)[8];_V9=(_pV)[9];





#define MEM_1FLT(_pV,_V)                              float _V=(_pV)[0];
#define MEM_2FLT(_pV,_V,_V1)                          float _V,_V1;                         _V=(_pV)[0];_V1=(_pV)[1];
#define MEM_3FLT(_pV,_V,_V1,_V2)                      float _V,_V1,_V2;                     _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];
#define MEM_4FLT(_pV,_V,_V1,_V2,_V3)                  float _V,_V1,_V2,_V3;                 _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];
#define MEM_5FLT(_pV,_V,_V1,_V2,_V3,_V4)              float _V,_V1,_V2,_V3,_V4;             _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];
#define MEM_6FLT(_pV,_V,_V1,_V2,_V3,_V4,_V5)          float _V,_V1,_V2,_V3,_V4,_V5;         _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];
#define MEM_7FLT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6)      float _V,_V1,_V2,_V3,_V4,_V5,_V6;     _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];
#define MEM_8FLT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7)  float _V,_V1,_V2,_V3,_V4,_V5,_V6,_V7; _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];_V7=(_pV)[7];
#define MEM_9FLT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8)       float _V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8;     _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];_V7=(_pV)[7];_V8=(_pV)[8];
#define MEM_10FLT(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8,_V9)  float _V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8,_V9; _V=(_pV)[0];_V1=(_pV)[1];_V2=(_pV)[2];_V3=(_pV)[3];_V4=(_pV)[4];_V5=(_pV)[5];_V6=(_pV)[6];_V7=(_pV)[7];_V8=(_pV)[8];_V9=(_pV)[9];


#define MEM_1SET(_pV,_V)                                       (_pV)[0]=_V;
#define MEM_2SET(_pV,_V,_V1)                                   (_pV)[0]=_V;(_pV)[1]=_V1;
#define MEM_3SET(_pV,_V,_V1,_V2)                               (_pV)[0]=_V;(_pV)[1]=_V1;(_pV)[2]=_V2;
#define MEM_4SET(_pV,_V,_V1,_V2,_V3)                           (_pV)[0]=_V;(_pV)[1]=_V1;(_pV)[2]=_V2;(_pV)[3]=_V3;
#define MEM_5SET(_pV,_V,_V1,_V2,_V3,_V4)                       (_pV)[0]=_V;(_pV)[1]=_V1;(_pV)[2]=_V2;(_pV)[3]=_V3;(_pV)[4]=_V4;
#define MEM_6SET(_pV,_V,_V1,_V2,_V3,_V4,_V5)                   (_pV)[0]=_V;(_pV)[1]=_V1;(_pV)[2]=_V2;(_pV)[3]=_V3;(_pV)[4]=_V4;(_pV)[5]=_V5;
#define MEM_7SET(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6)               (_pV)[0]=_V;(_pV)[1]=_V1;(_pV)[2]=_V2;(_pV)[3]=_V3;(_pV)[4]=_V4;(_pV)[5]=_V5;(_pV)[6]=_V6;
#define MEM_8SET(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7)           (_pV)[0]=_V;(_pV)[1]=_V1;(_pV)[2]=_V2;(_pV)[3]=_V3;(_pV)[4]=_V4;(_pV)[5]=_V5;(_pV)[6]=_V6;(_pV)[7]=_V7;
#define MEM_9SET(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8)       (_pV)[0]=_V;(_pV)[1]=_V1;(_pV)[2]=_V2;(_pV)[3]=_V3;(_pV)[4]=_V4;(_pV)[5]=_V5;(_pV)[6]=_V6;(_pV)[7]=_V7;(_pV)[8]=_V8;
#define MEM_10SET(_pV,_V,_V1,_V2,_V3,_V4,_V5,_V6,_V7,_V8,_V9)  (_pV)[0]=_V;(_pV)[1]=_V1;(_pV)[2]=_V2;(_pV)[3]=_V3;(_pV)[4]=_V4;(_pV)[5]=_V5;(_pV)[6]=_V6;(_pV)[7]=_V7;(_pV)[8]=_V8;(_pV)[9]=_V9;






#define _DUMP_SAV( __VarName__, __strSave) dumpFLTS(__strSave, __VarName__, __localDUMPcnt_##__VarName__, 0);

#define _NEW_DBL0(__VarName__,__VarNUM__) \
double*  __VarName__ = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (double *)malloc(sizeof(double)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;  \
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (double *)(_vnMEMMask_ + 2); \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
		memset(__VarName__,'\0',sizeof(double)*(__VarNUM__)); \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }



#define _NEW_FLT0(__VarName__,__VarNUM__) \
float*  __VarName__ = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;  \
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (float *)(_vnMEMMask_ + 2); \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
		memset(__VarName__,'\0',sizeof(float)*(__VarNUM__)); \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }


#define _NEW_MEM0(__VarName__,__VarNUM__) \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (float *)malloc(sizeof(float)*(2+(__VarNUM__))); \
	if( __VarName__){ \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;  \
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (float *)(_vnMEMMask_ + 2); \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
		memset(__VarName__,'\0',sizeof(float)*(__VarNUM__)); \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }






#define _NEW_SHORT(__VarName__,__VarNUM__) \
short*  __VarName__ = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (short *)malloc(sizeof(float)*(2+(((__VarNUM__) >> 1) + 4))); \
	if( __VarName__){  \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;	\
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (short *)(_vnMEMMask_ + 2); \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(__VarNUM__));  }


#define _NEW_BYTE(__VarName__,__VarNUM__) \
unsigned char*  __VarName__ = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (unsigned char *)malloc(sizeof(float)*(2+(((__VarNUM__) >> 2) + 4))); \
	if( __VarName__){  \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;  \
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (unsigned char *)(_vnMEMMask_ + 2); \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++;  \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(int)(__VarNUM__));  }



#define _NEW_CHAR(__VarName__,__VarNUM__) \
char*  __VarName__ = 0;  \
if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < __VarNUM__) ){  \
	__VarName__ = (char *)malloc(sizeof(float)*(2+(((__VarNUM__) >> 2) + 4))); \
	if( __VarName__){  \
		____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;  \
		int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = __VarNUM__; \
		__VarName__ = (char *)(_vnMEMMask_ + 2); \
		____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++;  \
	}   \
	else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); } \
} \
else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__VarName__" with size of "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,(int)(__VarNUM__));  }


#define _NEW_CHAR0(__VarName__,__VarNUM__)    _NEW_CHAR(__VarName__,__VarNUM__)   memset(__VarName__,'\0',sizeof(char)*(__VarNUM__));


// ********************************************************************************************************************************************************************************************************  
#define _NEW_VFLT0(__pvfVEC_list__,_Vlen_, __VECnum__) \
float*  __pvfVEC_list__[__VECnum__];  \
{ \
	int __jjj__;  float*  __VarName__ = 0;  \
	for( __jjj__ = 0; __jjj__ < (__VECnum__);  __jjj__++ ) {  \
		if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < _Vlen_) ){  \
			__VarName__ = (float *)malloc(sizeof(float)*(2+(_Vlen_))); \
			if( __VarName__){ \
				____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;  \
				int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = _Vlen_; \
				__pvfVEC_list__[__jjj__] = (float *)(_vnMEMMask_ + 2); \
				____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
				memset(__VarName__,'\0',sizeof(float)*(_Vlen_)); \
			}   \
			else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__pvfVEC_list__"[%d] with size of "#_Vlen_" = %d \n ",__FILE__,__FUNCTION__,__LINE__,__jjj__,(_Vlen_)); } \
		} \
		else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__pvfVEC_list__"[%d] with size of "#_Vlen_" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,__jjj__,(_Vlen_));  } \
	} \
}

#define _NEW_VINT0(__pvnVEC_list__,_Vlen_, __VECnum__) \
int*  __pvnVEC_list__[__VECnum__];  \
{ \
	int __jjj__;  float*  __VarName__ = 0;  \
	for( __jjj__ = 0; __jjj__ < (__VECnum__);  __jjj__++ ) {  \
		if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < _Vlen_) ){  \
			__VarName__ = (float *)malloc(sizeof(float)*(2+(_Vlen_))); \
			if( __VarName__){ \
				____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;  \
				int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = _Vlen_; \
				__pvnVEC_list__[__jjj__] = (int *)(_vnMEMMask_ + 2); \
				____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
				memset(__VarName__,'\0',sizeof(float)*(_Vlen_)); \
			}   \
			else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__pvnVEC_list__"[%d] with size of "#_Vlen_" = %d \n ",__FILE__,__FUNCTION__,__LINE__,__jjj__,(_Vlen_)); } \
		} \
		else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__pvnVEC_list__"[%d] with size of "#_Vlen_" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,__jjj__,(_Vlen_));  } \
	} \
}


// the following allocate double memory for shorts !!!
#define _NEW_VSHORT0(__pvsVEC_list__,_Vlen_, __VECnum__) \
short*  __pvsVEC_list__[__VECnum__];  \
{ \
	int __jjj__;  float*  __VarName__ = 0;  \
	for( __jjj__ = 0; __jjj__ < (__VECnum__);  __jjj__++ ) {  \
		if( (MAX_LOCALPTR_NUM > ____nLOCALMEM_NUM ) && (0 < _Vlen_) ){  \
			__VarName__ = (float *)malloc(sizeof(float)*(2+(_Vlen_))); \
			if( __VarName__){ \
				____vfLocalMEMLST[____nLOCALMEM_NUM] = (float *)	__VarName__;  \
				int* _vnMEMMask_ =  (int *) __VarName__; 	_vnMEMMask_[0] = MEMCHK_MASK;  _vnMEMMask_[1] = _Vlen_; \
				__pvsVEC_list__[__jjj__] = (short *)(_vnMEMMask_ + 2); \
				____nLOCALMEM_NUM++;  gnGlobal_CloseLoopMEMUsage_Balance++; \
				memset(__VarName__,'\0',sizeof(float)*(_Vlen_)); \
			}   \
			else{ printf("ERROR!!!<%s,%s,%d>  failed to allocate memory for "#__pvsVEC_list__"[%d] with size of "#_Vlen_" = %d \n ",__FILE__,__FUNCTION__,__LINE__,__jjj__,(_Vlen_)); } \
		} \
		else{ 	printf("ERROR!!!<%s,%s,%d>  failed at %d-th  allocation for "#__pvsVEC_list__"[%d] with size of "#_Vlen_" = %d \n ",__FILE__,__FUNCTION__,__LINE__,____nLOCALMEM_NUM,__jjj__,(_Vlen_));  } \
	} \
}



/*
#define MEMCHK(__VarName__, __VarNUM__) \
{ \
	int* _vnMEMMask_ =  (int *)__VarName__-2;  \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ \
		if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__VarName__" required memory = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__));   } \
	} \
} */

#define nzMEMCHK(__VarName__, __VarNUM__) \
if( 0 != (__VarName__) ){ \
	int* _vnMEMMask_ =  (int *)__VarName__-2;  giGlobal_MEMCHK_ERR = 0; \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ \
		if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__VarName__" required memory = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); giGlobal_MEMCHK_ERR = 1;  } \
	} \
}

#define _MEMERR() ( 1 == giGlobal_MEMCHK_ERR )

#define MEMCHK(__VarName__, __VarNUM__) \
{ \
	int* _vnMEMMask_ =  (int *)__VarName__-2;  giGlobal_MEMCHK_ERR = 0; \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ \
		if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__VarName__" required memory = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__));  giGlobal_MEMCHK_ERR = 1; } \
	} \
}

#define MEMCHK2(__Var1__,__Var2__, __VarNUM__) \
{ \
	int* _vnMEMMask_ =  (int *)__Var1__-2; giGlobal_MEMCHK_ERR = 0;  \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__Var1__" required  = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); giGlobal_MEMCHK_ERR = 1;} } \
	_vnMEMMask_ =  (int *)__Var2__-2;  \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__Var2__" required  = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); giGlobal_MEMCHK_ERR = 1;} } \
}

#define MEMCHK3(__Var1__,__Var2__,__Var3__, __VarNUM__) \
{  int* _vnMEMMask_;  \
	_vnMEMMask_ =  (int *)__Var1__-2;  giGlobal_MEMCHK_ERR = 0;  \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__Var1__" required  = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); giGlobal_MEMCHK_ERR = 1;} } \
	_vnMEMMask_ =  (int *)__Var2__-2;  \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__Var2__" required  = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); giGlobal_MEMCHK_ERR = 1;} } \
	_vnMEMMask_ =  (int *)__Var3__-2;  \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__Var3__" required  = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); giGlobal_MEMCHK_ERR = 1;} } \
}

#define MEMCHK4(__Var1__,__Var2__,__Var3__,__Var4__, __VarNUM__) \
{  int* _vnMEMMask_;  \
	_vnMEMMask_ =  (int *)__Var1__-2;  giGlobal_MEMCHK_ERR = 0;  \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__Var1__" required  = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); giGlobal_MEMCHK_ERR = 1;} } \
	_vnMEMMask_ =  (int *)__Var2__-2;  \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__Var2__" required  = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); giGlobal_MEMCHK_ERR = 1;} } \
	_vnMEMMask_ =  (int *)__Var3__-2;  \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__Var3__" required  = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); giGlobal_MEMCHK_ERR = 1;} } \
	_vnMEMMask_ =  (int *)__Var4__-2;  \
	if( MEMCHK_MASK == _vnMEMMask_[0] ){ if( (__VarNUM__) > _vnMEMMask_[1] ) { printf("ERROR!!!<%s,%s,%d>  "#__Var4__" required  = %d \n ",__FILE__,__FUNCTION__,__LINE__,(int)(__VarNUM__)); giGlobal_MEMCHK_ERR = 1;} } \
}


#define NEW_PTR_DBL(__pVarName__, __VarNUM__) \
if( 0 < (__VarNUM__) ) { __pVarName__ = (double*)malloc(sizeof(double)*(__VarNUM__)); } \
if( ( 0 >= (__VarNUM__) ) || ( 0 == __pVarName__ ) ) { printf("ERROR!!!<%s,%s,%d>  failed to allocate memory "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
else { gnGlobal_OpenLoopMEMUsage_Balance++; }


#define NEW_PTR_DBL0(__pVarName__, __VarNUM__) \
if( 0 < (__VarNUM__) ) { __pVarName__ = (double*)malloc(sizeof(double)*(__VarNUM__)); } \
if( ( 0 >= (__VarNUM__) ) || ( 0 == __pVarName__ ) ) { printf("ERROR!!!<%s,%s,%d>  failed to allocate memory "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
else { gnGlobal_OpenLoopMEMUsage_Balance++; memset(__pVarName__,'\0',sizeof(double)*(__VarNUM__));}




#define NEW_PTR_FLT(__pVarName__, __VarNUM__) \
if( 0 < (__VarNUM__) ) { __pVarName__ = (float*)malloc(sizeof(float)*(__VarNUM__)); } \
if( ( 0 >= (__VarNUM__) ) || ( 0 == __pVarName__ ) ) { printf("ERROR!!!<%s,%s,%d>  failed to allocate memory "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
else { gnGlobal_OpenLoopMEMUsage_Balance++; }


#define NEW_PTR_FLT0(__pVarName__, __VarNUM__) \
if( 0 < (__VarNUM__) ) { __pVarName__ = (float*)malloc(sizeof(float)*(__VarNUM__)); } \
if( ( 0 >= (__VarNUM__) ) || ( 0 == __pVarName__ ) ) { printf("ERROR!!!<%s,%s,%d>  failed to allocate memory "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
else { gnGlobal_OpenLoopMEMUsage_Balance++; memset(__pVarName__,'\0',sizeof(float)*(__VarNUM__));}


#define NEW_PTR_INT(__pVarName__, __VarNUM__) \
if( 0 < (__VarNUM__) ) { __pVarName__ = (int*)malloc(sizeof(int)*(__VarNUM__)); } \
if( ( 0 >= (__VarNUM__) ) || ( 0 == __pVarName__ ) ) { printf("ERROR!!!<%s,%s,%d>  failed to allocate memory "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
else { gnGlobal_OpenLoopMEMUsage_Balance++; }


#define NEW_PTR_SHORT0(__pVarName__, __VarNUM__) \
if( 0 < (__VarNUM__) ) { __pVarName__ = (short*)malloc(sizeof(short)*(__VarNUM__)); } \
if( ( 0 >= (__VarNUM__) ) || ( 0 == __pVarName__ ) ) { printf("ERROR!!!<%s,%s,%d>  failed to allocate memory "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
else { gnGlobal_OpenLoopMEMUsage_Balance++; memset(__pVarName__,'\0',sizeof(short)*(__VarNUM__));}

#define NEW_PTR_INT0(__pVarName__, __VarNUM__) \
if( 0 < (__VarNUM__) ) { __pVarName__ = (int*)malloc(sizeof(int)*(__VarNUM__)); } \
if( ( 0 >= (__VarNUM__) ) || ( 0 == __pVarName__ ) ) { printf("ERROR!!!<%s,%s,%d>  failed to allocate memory "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
else { gnGlobal_OpenLoopMEMUsage_Balance++; memset(__pVarName__,'\0',sizeof(int)*(__VarNUM__));}



#define NEW_PTR_BYTE(__pVarName__, __VarNUM__) \
if( 0 < (__VarNUM__) ) { __pVarName__ = (char*)malloc(sizeof(char)*(__VarNUM__)); } \
if( ( 0 >= (__VarNUM__) ) || ( 0 == __pVarName__ ) ) { printf("ERROR!!!<%s,%s,%d>  failed to allocate memory "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
else { gnGlobal_OpenLoopMEMUsage_Balance++; }

#define NEW_PTR_BYTE0(__pVarName__, __VarNUM__) \
if( 0 < (__VarNUM__) ) { __pVarName__ = (char*)malloc(sizeof(char)*(__VarNUM__)); } \
if( ( 0 >= (__VarNUM__) ) || ( 0 == __pVarName__ ) ) { printf("ERROR!!!<%s,%s,%d>  failed to allocate memory "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
else { gnGlobal_OpenLoopMEMUsage_Balance++; memset(__pVarName__,'\0',sizeof(char)*(__VarNUM__));}


#define NEW_PTR_UINT8(__pVarName__, __VarNUM__) \
if( 0 < (__VarNUM__) ) { __pVarName__ = (unsigned char *)malloc(sizeof(char)*(__VarNUM__)); } \
if( ( 0 >= (__VarNUM__) ) || ( 0 == __pVarName__ ) ) { printf("ERROR!!!<%s,%s,%d>  failed to allocate memory "#__VarNUM__" = %d \n ",__FILE__,__FUNCTION__,__LINE__,(__VarNUM__)); } \
else { gnGlobal_OpenLoopMEMUsage_Balance++; }



#define NEW_PTR_FREE(__pVarName__) \
if(__pVarName__) { free(__pVarName__); __pVarName__=0; gnGlobal_OpenLoopMEMUsage_Balance--; }



// ********************************************************************************************************************************************************************************************************  

// ********************************************************************************************************************************************************************************************************  
#define  _SHMget(__SHMid__,__SHMkey__,__SHMlen__)   \
__SHMid__ = shmget(__SHMkey__, 4*((__SHMlen__)+3), 0644|IPC_CREAT); \
if( -1 == (__SHMid__)) { printf("ERROR!!!<%s,%s,%d>  failed to get id of shared memory with KEY=%d\n ",__FILE__,__FUNCTION__,__LINE__,(__SHMkey__)); }

#define  _SHMattch(__SHMptr__,__SHMid__)   \
__SHMptr__ = shmat(__SHMid__,NULL,0);  \
if( (void *)-1 == (__SHMptr__) ) { printf("ERROR!!!<%s,%s,%d>  failed to get pointer of shared memory\n ",__FILE__,__FUNCTION__,__LINE__);}

#define  _SHMdetach(__SHMptr__)            \
if( -1 == shmdt(__SHMptr__) ) { printf("ERROR!!!<%s,%s,%d>  failed to detach pointer of shared memory\n ",__FILE__,__FUNCTION__,__LINE__);}


#define  _SHMdestroy(__SHMid__)               \
if( -1 == shmctl(__SHMid__, IPC_RMID, 0) ) {  printf("ERROR!!!<%s,%s,%d>  failed to destroy shared memory ID=%d\n ",__FILE__,__FUNCTION__,__LINE__,__SHMid__); } 


/*
   int  m_cnt;
   int  m_complete;
   int  m_len;
*/

#define  _SHMnew(__SHMid__,__SHMptr__,__SHMkey__,__SHMlen__, __isCREATE__) \
int __SHMid__ = shmget(__SHMkey__, 4*((__SHMlen__)+3), 0644|IPC_CREAT);  void *__SHMptr__; \
if( -1 == (__SHMid__)) { printf("ERROR!!!<%s,%s,%d>  failed to get id of shared memory with KEY=%d\n ",__FILE__,__FUNCTION__,__LINE__,(__SHMkey__)); } \
else {  __SHMptr__ = shmat(__SHMid__,NULL,0);  \
    if( (void *)-1 == (__SHMptr__) ) { printf("ERROR!!!<%s,%s,%d>  failed to get pointer of shared memory\n ",__FILE__,__FUNCTION__,__LINE__);}   \
    else {  \
    	if( __isCREATE__ ) { ((int*)__SHMptr__)[0] = 0; ((int*)__SHMptr__)[1] = -1;  ((int*)__SHMptr__)[2] = __SHMlen__; } \
    } \
} 

#define _SHMmem(__SHMptr__) (((float*)(__SHMptr__))+3)
#define _SHMlen(__SHMptr__) (((int*)(__SHMptr__))[2])
#define _SHMchk(__SHMptr__) (((int*)(__SHMptr__))[1])
#define _SHMcnt(__SHMptr__) (((int*)(__SHMptr__))[0])


#define  _SHMfree(__SHMid__,__SHMptr__) \
if( -1 == shmdt(__SHMptr__) ) { printf("ERROR!!!<%s,%s,%d>  failed to detach pointer of shared memory\n ",__FILE__,__FUNCTION__,__LINE__);}  \
if( -1 == shmctl(__SHMid__, IPC_RMID, 0) ) {  printf("ERROR!!!<%s,%s,%d>  failed to destroy shared memory ID=%d\n ",__FILE__,__FUNCTION__,__LINE__,__SHMid__); } 




// ****************************************************************************************************  
// ****************************************************************************************************  

#ifdef __cplusplus 
extern "C" {
    #endif  


    // **************************************************************************************************************

    typedef struct _stRingBUF
    {
        int     m_PTR;
        int     m_CNT;
        int     m_LEN;
        float*  m_DataPTR;
    } stRingBUF;

    void stRingBUF_init(int *pRingBUF, float *pfMEM, int ilen,float fVal);
    void stRingBUF_push(int *pRingBUF,float *pfMEM, int ilen);
    int  stRingBUF_pop(int *pRingBUF,float *vfVEC, int VEClen, int iDelay, int isBlkItem=0);




    // **************************************************************************************************************

    
    
    #ifdef __cplusplus 
}
#endif  
    





#endif /* __PERF_METRIC_COMMmem_H */
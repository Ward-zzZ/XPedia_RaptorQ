#ifndef __PERF_METRIC_COMMstr_H
#define __PERF_METRIC_COMMstr_H
/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */
#include <stdarg.h> 

#ifdef __cplusplus 
extern "C" {   
#endif	


extern char* gstrLOCALPtr_GenNAME;

#define _SGnew(__nVAR__)   char __LOCALSTRGEN_##__nVAR__[20];  
#define _SGset(__nVAR__)  sprintf(__LOCALSTRGEN_##__nVAR__,"%d",__nVAR__);
#define _SGnum(__nVAR__)  __LOCALSTRGEN_##__nVAR__ 

int     STR_cats(char *strSRC,int maxLEN,int num,...);
//char*   STR_catmore(char *strOUT, int num, ...);
char*   STR_catmore(int isRST,char *strOUT, int num, ...);

#define STR_catM(__strOUT__,...) STR_catmore(0,__strOUT__,20,__VA_ARGS__,NULL)
#define STR_catX(__strOUT__,...) STR_catmore(1,__strOUT__,20,__VA_ARGS__,NULL)
#define STRg(__strOUT__,...)     STR_catmore(1,__strOUT__,20,__VA_ARGS__,NULL)
#define STR_new(__strOUT__,...)   char __strOUT__[100]; __strOUT__[0]=0;  STR_catmore(1,__strOUT__,20,__VA_ARGS__,NULL)

#define _STRn(__nVAR__)  char __LOCALSTRGEN_##__nVAR__[20];  sprintf(__LOCALSTRGEN_##__nVAR__,"%d",__nVAR__);
#define _STRx(__nVAR__)  char __LOCALSTRGEN_##__nVAR__[30];  sprintf(__LOCALSTRGEN_##__nVAR__,""#__nVAR__"%d",__nVAR__);
#define _STRx_(__nVAR__) char __LOCALSTRGEN_##__nVAR__[30];  sprintf(__LOCALSTRGEN_##__nVAR__,""#__nVAR__"%d_",__nVAR__);

#define _STR(__nVAR__)   __LOCALSTRGEN_##__nVAR__ 



//void strcatFLT(char *strMEM, float fval, char *strFMT=0);
//void strcatINT(char *strMEM, int ival,char *strNAME=0, char *strSEP=0, char *strFMT=0);
//void strcatFLTS(char *strTXT, float *vfVEC, int VEClen);
//int  strgetFLTS(float *vfVEC, int VEClen, char *strTXT, char *strKEY=0);
//int  strgetINTS(int   *viVEC, int VEClen, char *strTXT, char *strKEY=0);

void strcatFLT(char *strMEM, float fval, char *strFMT);
void strcatINT(char *strMEM, int ival,char *strNAME, char *strSEP, char *strFMT);
void strcatFLTS(char *strTXT, float *vfVEC, int VEClen);
int  strgetFLTS(float *vfVEC, int VEClen, char *strTXT, char *strKEY);
int  strgetINTS(int   *viVEC, int VEClen, char *strTXT, char *strKEY);

int  strRMVspace(char* strOUT, char* strSRC);
int  strs_get(char* strITEM, int iOlen, int iIDX, char* strTXT, char* strDElimiter, int MaxN);


int  strgetINT(char *strTXT, char *strBEG, char *strEND);
#define _strgetINT(__strTXT,  __strBEG, __strEND)  strgetINT((char*)__strTXT,  (char*)__strBEG, (char*)__strEND) 
#define _strkeyINT(__KeyName, __strTXT)            int __KeyName = strgetINT((char*)__strTXT,  (char*)#__KeyName, (char*)"") 

#define _strkey2INT(__KeyName0,__KeyName1, __strTXT)  \
int __KeyName0 = strgetINT((char*)__strTXT,  (char*)#__KeyName0, (char*)"");  \
int __KeyName1 = strgetINT((char*)__strTXT,  (char*)#__KeyName1, (char*)""); 

#define _strkey3INT(__KeyName0,__KeyName1,__KeyName2, __strTXT)  \
int __KeyName0 = strgetINT((char*)__strTXT,  (char*)#__KeyName0, (char*)"");  \
int __KeyName1 = strgetINT((char*)__strTXT,  (char*)#__KeyName1, (char*)"");  \
int __KeyName2 = strgetINT((char*)__strTXT,  (char*)#__KeyName2, (char*)""); 


#define _strkey4INT(__KeyName0,__KeyName1,__KeyName2, __KeyName3,__strTXT)   \
int __KeyName0 = strgetINT((char*)__strTXT,  (char*)#__KeyName0, (char*)"");  \
int __KeyName1 = strgetINT((char*)__strTXT,  (char*)#__KeyName1, (char*)"");  \
int __KeyName2 = strgetINT((char*)__strTXT,  (char*)#__KeyName2, (char*)"");  \
int __KeyName3 = strgetINT((char*)__strTXT,  (char*)#__KeyName3, (char*)"");  




#define _strcatCFG(__strMEM__,__iCfg__)   strcatINT(__strMEM__,__iCfg__,(char *)_strFUSE(#__iCfg__,"="),(char *)"; ",0)
#define _strgetCFG(__strMEM__,__iCfg__)   int __iCfg__; strgetINTS(&__iCfg__,1,__strMEM__,(char *)_strFUSE(#__iCfg__,"="))


char* StampPTR(char *pstrMEM, int ByteNUM, int isZERO);
int StampPTR_CHKBytes(char *pstrDATA);

#define _GSTR_NEW(__strNAME,__Size) \
char __strLOCALNAME_##__strNAME[(__Size)+8]; char* __strNAME = StampPTR(__strLOCALNAME_##__strNAME,(__Size)+8,1); gstrLOCALPtr_GenNAME = __strNAME; 


#define _GSTR_NEWSTR(__strNAME,__strNEW) \
char __strLOCALNAME_##__strNAME[(300)+8]; char* __strNAME = StampPTR(__strLOCALNAME_##__strNAME,(300)+8,1); gstrLOCALPtr_GenNAME = __strNAME; \
if( StampPTR_CHKBytes(__strNAME) >  (strlen(__strNEW) + strlen(__strNAME)) ) { strcat(__strNAME,__strNEW);   }  \
else { printf("    ERROR!!!  <%s,%s,%d> failed to add ...%s to @@"#__strNAME"...%s , overflowed !!!  \n", __FILE__,__FUNCTION__,__LINE__, __strNEW,__strNAME); }


#define _GSTR_STR(__strNEW) \
{ char* __strLOCALNAME = gstrLOCALPtr_GenNAME; \
	if( StampPTR_CHKBytes(__strLOCALNAME) >  (strlen(__strNEW) + strlen(__strLOCALNAME)) ) { strcat(__strLOCALNAME,__strNEW);   }  \
	else { printf("    ERROR!!!  <%s,%s,%d> failed to add ...%s to ...%s, overflowed !!!  \n", __FILE__,__FUNCTION__,__LINE__,(char *)(__strNEW),__strLOCALNAME); } \
}



#define _GSTR_INT(__nVAL) \
{ char* __strLOCALNAME = gstrLOCALPtr_GenNAME;  char __strNEW[30]; sprintf(__strNEW,"%d",__nVAL); \
	if( StampPTR_CHKBytes(__strLOCALNAME) >  (strlen(__strNEW) + strlen(__strLOCALNAME)) ) { strcat(__strLOCALNAME,__strNEW);   }  \
	else { printf("    ERROR!!!  <%s,%s,%d> failed to add ...%s to ...%s, overflowed !!! \n", __FILE__,__FUNCTION__,__LINE__, __strNEW,__strLOCALNAME); }  \
}

#define _GSTR_FLT(__fVAL) \
{ char* __strLOCALNAME = gstrLOCALPtr_GenNAME;  char __strNEW[30]; sprintf(__strNEW,"%.2e",(float)(__fVAL)); \
	if( StampPTR_CHKBytes(__strLOCALNAME) >  (strlen(__strNEW) + strlen(__strLOCALNAME)) ) { strcat(__strLOCALNAME,__strNEW);   }  \
	else { printf("    ERROR!!!  <%s,%s,%d> failed to add ...%s to ...%s, overflowed !!! \n", __FILE__,__FUNCTION__,__LINE__, __strNEW,__strLOCALNAME); }  \
}






    #ifdef __cplusplus 
}
#endif  

// ****************************************************************************************************  
// ****************************************************************************************************  



#endif /* __PERF_METRIC_COMMstr_H */
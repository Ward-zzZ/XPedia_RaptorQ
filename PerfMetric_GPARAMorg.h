#ifndef __PERF_METRIC_GPARAMorg_H
#define __PERF_METRIC_GPARAMorg_H


extern char   gstrGPARAM_UsedParamNameLIST[];
extern char   gstrGPARAM_UsedParamNameSHOW[];



// #define FOO(fmt, ...) printf(fmt, ##__VA_ARGS__)
// use extern volatile to claim a global param, it is not necessary , commented by Duan Weiming in 2019-12-12
/*
#define DEF_GPARAM_INT(__gparam_name__)   extern int  volatile    GPARAM_##__gparam_name__;   extern float volatile GPARAM_##__gparam_name__##_Counter;
#define DEF_GPARAM_FLT(__gparam_name__)   extern volatile float   GPARAM_##__gparam_name__;   extern volatile float GPARAM_##__gparam_name__##_Counter;
#define DEF_GPARAM_STR(__gparam_name__)   extern volatile char    GPARAM_##__gparam_name__[]; extern volatile float GPARAM_##__gparam_name__##_Counter;



#define REG_GPARAM_INT(__gparam_name__, __val__)  int volatile GPARAM_##__gparam_name__ = ( int volatile )__val__;   float volatile  GPARAM_##__gparam_name__##_Counter = (float volatile)0.0;
#define REG_GPARAM_FLT(__gparam_name__, __val__)  volatile float GPARAM_##__gparam_name__ = (volatile float)__val__;  volatile float GPARAM_##__gparam_name__##_Counter = (volatile float)0.0;
#define REG_GPARAM_STR(__gparam_name__)           volatile char  GPARAM_##__gparam_name__[100]={0};                   volatile float GPARAM_##__gparam_name__##_Counter = (volatile float)0.0;

#define DEF_GPARAM_ENUM(__gparam_name__,...)  \
extern  int volatile GPARAM_##__gparam_name__; extern float volatile GPARAM_##__gparam_name__##_Counter; \
enum GPARAM_##__gparam_name__##_ENUM { __VA_ARGS__, GPARAM_##__gparam_name__##_NUM }; \
const char gstrGPARAM_##__gparam_name__##_NAME[] = {""#__VA_ARGS__""};
*/
#define DEF_GPARAM_INT(__gparam_name__)   extern int     GPARAM_##__gparam_name__;   extern float GPARAM_##__gparam_name__##_Counter;
#define DEF_GPARAM_FLT(__gparam_name__)   extern float   GPARAM_##__gparam_name__;   extern float GPARAM_##__gparam_name__##_Counter;
#define DEF_GPARAM_STR(__gparam_name__)   extern char    GPARAM_##__gparam_name__[]; extern float GPARAM_##__gparam_name__##_Counter;



#define REG_GPARAM_INT(__gparam_name__, __val__)  int   GPARAM_##__gparam_name__ = __val__;   float   GPARAM_##__gparam_name__##_Counter = 0.0;
#define REG_GPARAM_FLT(__gparam_name__, __val__)  float GPARAM_##__gparam_name__ = __val__;   float   GPARAM_##__gparam_name__##_Counter = 0.0;
#define REG_GPARAM_STR(__gparam_name__)           char  GPARAM_##__gparam_name__[100]={0};    float   GPARAM_##__gparam_name__##_Counter = 0.0;

#define DEF_GPARAM_ENUM(__gparam_name__,...)  \
extern  int  GPARAM_##__gparam_name__; extern float  GPARAM_##__gparam_name__##_Counter; \
enum GPARAM_##__gparam_name__##_ENUM { __VA_ARGS__, GPARAM_##__gparam_name__##_NUM }; \
const char gstrGPARAM_##__gparam_name__##_NAME[] = {""#__VA_ARGS__""};







#ifdef __cplusplus 
extern "C" {
    #endif  
    
/*
extern "C" {  */
	int cfgGPARAM_org(char *strGlobalCONF);
	int cfg_GPARAM(char *strGlobalCONF);
	void  getEnumName_byID(char *strEnumNAME,  int nSize, char *srcSRC , int nID);
	int   getEnumID_byNAME(char *srcSRC,  char *strEnumNAME);
	
	
	
    #ifdef __cplusplus 
}
#endif  
	
/*	
}  */

/*
#define GET_GPARAM_INT(__gparam_name__)  int   __gparam_name__ = GPARAM_##__gparam_name__;
#define GET_GPARAM_FLT(__gparam_name__)  float __gparam_name__ = GPARAM_##__gparam_name__;
#define GET_GPARAM_STR(__gparam_name__)  char __gparam_name__[100]; __gparam_name__[0]=0; strcat(__gparam_name__, GPARAM_##__gparam_name__); */



#define GET_GPARAM_INT(__gparam_name__) \
int  __gparam_name__ = (int)GPARAM_##__gparam_name__; \
if( 1.0 > GPARAM_##__gparam_name__##_Counter ) { \
    char ____strNAME_BUFF____[500]; \
    sprintf(____strNAME_BUFF____, "%s=%d___", #__gparam_name__, __gparam_name__); \
    strcat(gstrGPARAM_UsedParamNameLIST, ____strNAME_BUFF____); \
    sprintf(____strNAME_BUFF____, " %%  @@@@ "#__gparam_name__" = %d !!!!,   <%s> <%s> <%d>  \n", __gparam_name__ ,__FILE__,__FUNCTION__,__LINE__); \
    strcat(gstrGPARAM_UsedParamNameSHOW, ____strNAME_BUFF____); printf("%s",____strNAME_BUFF____); \
} \
GPARAM_##__gparam_name__##_Counter += 1.0;

#define GET_GPARAM_FLT(__gparam_name__) \
float  __gparam_name__ = (float)GPARAM_##__gparam_name__; \
if( 1.0 > GPARAM_##__gparam_name__##_Counter ) { \
    char ____strNAME_BUFF____[500]; \
    sprintf(____strNAME_BUFF____, "%s=%f___", #__gparam_name__, __gparam_name__); \
    strcat(gstrGPARAM_UsedParamNameLIST, ____strNAME_BUFF____); \
    sprintf(____strNAME_BUFF____, " %%  @@@@ "#__gparam_name__" = %f !!!!,   <%s> <%s> <%d>  \n", __gparam_name__ ,__FILE__,__FUNCTION__,__LINE__); \
    strcat(gstrGPARAM_UsedParamNameSHOW, ____strNAME_BUFF____); printf("%s",____strNAME_BUFF____); \
} \
GPARAM_##__gparam_name__##_Counter += 1.0;

#define GET_GPARAM_STR(__gparam_name__) \
char __gparam_name__[100]; __gparam_name__[0]=0; strcat(__gparam_name__, GPARAM_##__gparam_name__); \
if( 1.0 > GPARAM_##__gparam_name__##_Counter ) { \
    char ____strNAME_BUFF____[500]; \
    sprintf(____strNAME_BUFF____, "%s=%s___", #__gparam_name__, __gparam_name__); \
    strcat(gstrGPARAM_UsedParamNameLIST, ____strNAME_BUFF____); \
    sprintf(____strNAME_BUFF____, " %%  @@@@ "#__gparam_name__" = %s !!!!,   <%s> <%s> <%d>  \n", __gparam_name__ ,__FILE__,__FUNCTION__,__LINE__); \
    strcat(gstrGPARAM_UsedParamNameSHOW, ____strNAME_BUFF____); printf("%s",____strNAME_BUFF____); \
} \
GPARAM_##__gparam_name__##_Counter += 1.0;


#define GET_GPARAM_ENUM(__gparam_name__) \
int  __gparam_name__ = (int)GPARAM_##__gparam_name__; \
if( 1.0 > GPARAM_##__gparam_name__##_Counter ) { \
    char ____strNAME_BUFF____[500];   char ___strEnumNAME___[50+1];  \
    getEnumName_byID(___strEnumNAME___,  50, (char*)gstrGPARAM_##__gparam_name__##_NAME , __gparam_name__);  \
    sprintf(____strNAME_BUFF____, "%s=%s", #__gparam_name__, ___strEnumNAME___); \
    strcat(gstrGPARAM_UsedParamNameLIST, ____strNAME_BUFF____); \
    sprintf(____strNAME_BUFF____, " %%  @@@@ "#__gparam_name__" = %s !!!!,   <%s> <%s> <%d>  \n", ___strEnumNAME___ ,__FILE__,__FUNCTION__,__LINE__); \
    strcat(gstrGPARAM_UsedParamNameSHOW, ____strNAME_BUFF____); printf("%s",____strNAME_BUFF____); \
} \
GPARAM_##__gparam_name__##_Counter += 1.0;


#define READ_GPARAM_INTX(__gparam_name__,__strIN__) \
{   \
    int __getval__[1];int __isDone__; \
    __isDone__ = Parse_Int(__getval__,(char *)__strIN__,(char *)#__gparam_name__,(char *)"="); \
    if( __isDone__ ) { GPARAM_##__gparam_name__ = __getval__[0]; } \
}

#define READ_GPARAM_INT(__gparam_name__) \
{   char *__strIN__ = strGlobalCONF; \
    int __getval__[1];int __isDone__ = Parse_Int(__getval__,__strIN__,(char *)#__gparam_name__,(char *)"=?"); \
    if( 1 == __isDone__ ) { return GPARAM_##__gparam_name__; }  \
    __isDone__ = Parse_Int(__getval__,__strIN__,(char *)#__gparam_name__,(char *)"="); \
    if( __isDone__ ) { GPARAM_##__gparam_name__ = __getval__[0]; } \
} 

#define READ_GPARAM_FLT(__gparam_name__)   \
{   char *__strIN__ = strGlobalCONF; \
    float __getval__[1];int __isDone__ = Parse_Float(__getval__,&__strIN__,(char *)#__gparam_name__,(char *)"=",1); \
    if( __isDone__ ) { GPARAM_##__gparam_name__ = __getval__[0]; } \
} 

#define READ_GPARAM_STR(__gparam_name__)   \
{   char *__strIN__ = strGlobalCONF; \
    char __getval__[100];int __isDone__ = Parse_Str(__getval__,__strIN__,(char *)#__gparam_name__,(char *)"="); \
    if( __isDone__ ) { GPARAM_##__gparam_name__[0]=0; strcat((char *)GPARAM_##__gparam_name__, __getval__); } \
} 

#define READ_GPARAM_ENUM(__gparam_name__)   \
{   char *__strIN__ = strGlobalCONF; \
    char __getval__[100];int __isDone__  = Parse_Str(__getval__,__strIN__,(char *)#__gparam_name__,(char *)"=?"); \
    if( 1 == __isDone__ ) { return GPARAM_##__gparam_name__; }  \
    __isDone__  = Parse_Str(__getval__,__strIN__,(char *)#__gparam_name__,(char *)"=");  \
    if( __isDone__ ) {   int __FindID__  = getEnumID_byNAME((char*)gstrGPARAM_##__gparam_name__##_NAME,  __getval__);  \
        if( 0 <= __FindID__ ) {  GPARAM_##__gparam_name__ = __FindID__;  }  \
    } \
} 


#endif /* __PERF_METRIC_GPARAMorg_H */
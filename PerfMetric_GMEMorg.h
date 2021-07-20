#ifndef __PERF_METRIC_GMEMorg_H
#define __PERF_METRIC_GMEMorg_H
/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */




#define DEF_gfMEM(__gMEM_name__) extern int  gMEM_##__gMEM_name__##_CHK; extern float gMEM_##__gMEM_name__##_fVEC[];  extern int  gMEM_##__gMEM_name__##_LEN;
#define REG_gfMEM(__gMEM_name__, __len__) int  gMEM_##__gMEM_name__##_CHK = 0;  float gMEM_##__gMEM_name__##_fVEC[__len__]; int gMEM_##__gMEM_name__##_LEN=(__len__);
#define GET_gfMEM(__gMEM_name__) float *__gMEM_name__ = gMEM_##__gMEM_name__##_fVEC;
#define _gMEMchk(__gMEM_name__)  gMEM_##__gMEM_name__##_CHK
#define _gMEMchecked(__gMEM_name__)  gMEM_##__gMEM_name__##_CHK=1;

#define gMEMclone(__gMEM_name__, __VECclone__, __len__)  \
if( (gMEM_##__gMEM_name__##_LEN == (__len__) ) && (gMEM_##__gMEM_name__##_CHK) ){  memcpy(__VECclone__,gMEM_##__gMEM_name__##_fVEC,sizeof(float)*(__len__)); } \
else { ERR_CHK(  (gMEM_##__gMEM_name__##_LEN != (__len__) ) || (0 == gMEM_##__gMEM_name__##_CHK) ) }

#define gMEMpush(__gMEM_name__,__VECclone__, __len__)  \
if (gMEM_##__gMEM_name__##_LEN == (__len__)) {  memcpy(gMEM_##__gMEM_name__##_fVEC,__VECclone__,sizeof(float)*(__len__)); gMEM_##__gMEM_name__##_CHK=1; }  \
else { ERR_CHK( gMEM_##__gMEM_name__##_LEN != (__len__) ) }




#ifdef __cplusplus 
extern "C" {
    #endif  
    // **************************************************************************************************************
    typedef struct _stDUMP
    {
        int    m_VEClen;
        int    m_VECnum;
        int    m_MaxLEN;
        int    m_SampSUM;         // added by Duan Weiming in 2021-03-28
        char   m_strLabel[50];
        float* m_pfDATA;        
    } stDUMP;

    #define  GDUMP_MAX_NUM 100

    extern int    giDUMPGlobal_CHECK;
    extern stDUMP gvstDUMPGlobal_list[];
    extern void   SCM3Denv_free(int iCFG);

    void    gMEM_free(int icheck);    
    void    gMEM_dumpREC(stDUMP *pstDUMP, int iIDsave, int isFinal=0);
    int     gMEM_dump(char *strlabel, float *vfVEC, int VEClen, int MaxSample, int iIDsave=0); // 0: not save to file
    int     gMEM_load(char *strlabel, float *vfVEC, int VEClen, int MaxSample);
    stDUMP* gMEM_find(char *strlabel, int VEClen);    

    // **************************************************************************************************************

    //typedef struct _stRingBUF
    //{
    //    int     m_PTR;
    //    int     m_CNT;
    //    int     m_LEN;
    //    float*  m_DataPTR;
    //} stRingBUF;
    //void stRingBUF_init(int *pRingBUF, float *pfMEM, int ilen,float fVal);
    //void stRingBUF_push(int *pRingBUF,float *pfMEM, int ilen);
    //int  stRingBUF_pop( int *pRingBUF,float *pfMEM, int VEClen, int iDly) ;




    // **************************************************************************************************************

    
    
    #ifdef __cplusplus 
}
#endif  
    




// ****************************************************************************************************  
// ****************************************************************************************************  



#endif /* __PERF_METRIC_GMEMorg_H */
/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...
*************************************************************************************************************************************************************************  */



#ifndef __XPEDIA_AMC_H
#define __XPEDIA_AMC_H


#ifndef DEF_GLOBAL_MCS_PARAM
#define DEF_GLOBAL_MCS_PARAM
#define MAX_MCS_N 29
#define MAX_ITBS_N 27
#define MAX_HARQ_TRANS_N 4
#define MAX_NetTBS_MIN  256
#define MAX_NetTBS_MAX  75376
#define MCS_MIN 0
#define MCS_MAX 28    // limit for only one code block in 10RB case,
#define MAX_TRANSTIMES 4 //max transmission times for each TB
#endif



#define MAPQamB_QamType(_QamB_) (2*(1==_QamB_)+4*(2==_QamB_)+16*(4==_QamB_)+64*(6==_QamB_)+256*(8==_QamB_))

#define  MAX_MEAS_DLY 20
extern "C" {

    typedef struct  _stAMC  {
        int    m_RvID;
        int    m_RVlen;
        int    m_netTBS;         // net TBsize
        int    m_QamType;
        int    m_MCSnow;
        int    m_QamN;           // m_QamN = LayrN*m_RBuse*144 , commented by Duan Weiming in 2021-03-17
        int    m_maxTBS;
        int    m_MCSmin;
        int    m_AMC_ON;
        int    m_RBuse;          // used RB number , added by Duan Weiming in 2021-03-17
        int    m_RXnum;          // receive channel number, added by Duan Weiming in 2021-03-17
        int    m_Transtimes;        //current trans times
        stRingBUF m_RingBUFmeas;
        stRingBUF m_RingBUF_PMs; // ring buffer for precoding matrix, added by Duan Weiming in 2021-03-18
        float  m_AvgSNRdB;       // snr averaged over rx channels
        int    m_LyrN;           // layer number, added by Duan Weiming in 2021-03-20
        float  m_MeasBUFF[MAX_MEAS_DLY+10];


    } stAMC;



    void AMC_init(int *pAMCmem, int NetTBS, int SUMsc, int iModuType,  float fEsN0_init, int iRXnum, int iAMC_ON);
    int  AMC_control(int *pAMCmem, int *viINFObits, int MAXlen,  int iNACK, float fEsN0_meas, int iDly=0, int iLyrN=1);


    int  Update_RV(int RvIDnow, int iNACK );
    int  AMC_updateRV(int *pAMCmem, int iNACK);

    void AMC_updateMCS(int *pAMCmem, float fEsN0_meas, int iDly, int iLyrN);
    int  AMC_chk(int *pAMCmem);
    void AMC_rst(int* pAMCmem);
    int  AMC_mcslkt(int *viNetTBS_list, int *viQamType_list, float *vfCodeR_list, int MaxLEN, int RBnum);

    extern float gvfMCS_snr_lktbl[];
    extern int   giMCS_snr_lktbl_CHK;
    //int  AMC_getMCSsnrs(float *vfSNR_list, int iNUM, int RBnum, int isDualRX=1);
    int  AMC_getMCSsnrs(float* vfSNR_list, int iNUM, int RBnum, float fSNRdB_inc=0.0);
    int  AMC_readMCSsnr(float *vfSNR_list , int MaxN, float fBLERobj ,char *strMiQfile);





    // ****************************************************************************************************************************************************************
    extern  void BlockAddConst(float *vfBlkOUT, float *vfBlk_A, float fConst, int nBlkSIZE);
    #define VEC_addC( __VEC_A__,  __VEClen__,__fConst__)   BlockAddConst(__VEC_A__, __VEC_A__, __fConst__, __VEClen__)
    #define VEC_subC(__VECout__, __VEClen__, __fConst__)   BlockAddConst(__VECout__, __VECout__, -1.0*(__fConst__), __VEClen__)

    extern  void VEC_abs(float *vfVEC_o, float *vfVECsrc, int VEClen, float *pfABSavg);
    extern  float VEC_minSTD(float *vfVECsrc, int VEClen, int *pMinPOS);
    extern  int GetQamBITS(int ModuTYPE);
    extern  int VEC_findsorted(float *vfVECsorted, int VEClen, float fTarget, int isAscend);
    extern  int IVEC_findsorted(int *vfVECsorted, int VEClen, int fTarget);
    extern  int IVEC_match(int *viVEC, int VEClen, int iMatchID, int *viMatchPOS);
    extern  void RandomBits(int *vnOUT,  int nSIZE);

    // ****************************************************************************************************************************************************************




}

#endif /* __XPEDIA_AMC_H */

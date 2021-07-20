/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */



#ifndef __XPEDIA_SCMlsp_H
#define __XPEDIA_SCMlsp_H


extern "C" {
    
    // ****************************************************************************************************************************************************************************  
    
    void   SCM3Dnet_DLSirCDF(float* vfCxCDF, int CDFlen,  float* vfMatGains,  int UserN, int iSCENAcase);  //0: eSCENA_Umi, 1:  eSCENA_Uma, 2: eSCENA_Rma, 3: eSCENA_InH

    void   SCM3Dnet_FDran_UplinkBound(float* vfCxPDF_sinr, int PDFlen, float* vfMatGaindB,int UserN, int MaxJointP, int SIMsampN, float fNetwrok_Load, int iSCENAcase, int *viO2I_IDs);
    
    void   SCM3Dnet_mimoFD(float* vfCxRxOFDMs_pool, float* vfCxTxOFDMs_pool, char* strCIRfile, int RxM, int TxN, int RBnum, int RBfrom, float fNoisePwr, float* vfCxScHs_pool, int iSenderN, int iRecvrM, int TTIcnt);



    // ****************************************************************************************************************************************************************************
    extern void   SCM3Denv_genlinkGain(float* vfMatGains, float* vfCxPOSx19_list, float *vfHeights, int *viO2I_IDs, int *viLOS_x19,  int UsrN, float fCarrierGHz, int iSCENAcase);    
    // This function is based single path (LOS direction), a simplified model for calibration phase1 defined in TR36.873 ,  remarked by Duan Weiming in in 2021-05-10    
    //*  vfMatGains      : propagation gain (Coupling loss) from each user to 57 sector  (size : UsrN*57)   , 
    //*  vfCxPOSx19_list : relative XY coordinate from user to each center site          (size : UsrN*19*2)
    //*  vfHeights       : height (meter) of each user                                   (size : UsrN) 
    //*  viO2I_IDs       : O2I id (1: o2i, 0: outdoor) for each user                     (size : UsrN)
    //*  viLOS_x19       : LOS id (1: los, 0: nlos   ) for each user w.r.t each site     (size : UsrN*19)
    //*  UsrN            : number of users
    //*  fCarrierGHz     : carrier frequency in GHz
    //*  iSCENAcase      : 0: eSCENA_Umi, 1:  eSCENA_Uma, 2: eSCENA_Rma, 3: eSCENA_InH   
    // ***************************************************************************************************************************************************************************

    extern float  MIMO_channelFD(float *vfCxSCs_flt, float *vfCxOFDMs_TXs,  char* strCIRfile,  int OFDMnum,  int RBnum,   int RxM, int TxN,  int TTIcnt, int RBfrom, float fNoisePwr, float *vfCxSCH_ice);

    extern  void   CxVEC_sum(float* vfCxVEC_sum, float* vfCxVEC_src, int Vlen);

    extern float AVX_BlockMax_ORG(int *pMaxPOS, float *vfVECsrc, int VEClen, int isMinOP,int isABS);
    #define VEC_max(__pnPEAK_, __vfVEC__, __VEClen__ )  AVX_BlockMax_ORG(__pnPEAK_, __vfVEC__, __VEClen__ ,0,0)


    extern float BlockSum(float *vfData, int nSize );    
    #define VEC_sum(__vfVEC__, __VEClen__)   BlockSum(__vfVEC__, __VEClen__) 
    
    extern void  AVX_fast_pwr10(float *vfOUT,  float *vfData, int nNUM);    
    #define VEC_pow10(__powlist__, __VECsrc__, __VEClen__)  AVX_fast_pwr10(__powlist__, __VECsrc__, __VEClen__)


    extern void BlockAddConst(float *vfBlkOUT, float *vfBlk_A, float fConst, int nBlkSIZE);
    #define VEC_addC( __VEC_A__,  __VEClen__,__fConst__)   BlockAddConst(__VEC_A__, __VEC_A__, __fConst__, __VEClen__) 


    extern void VEC_mulC(float *vfData, int nSample, float fConst);
    extern void  VEC_rand(float *vfnoise, int VEClen, float fFrom, float fTo);


    extern void  IVEC_indexRand(int *viINDICE_list, int VEClen, int VECnum);    
    #define IVEC_shuffle(__viVEC__, __Vlen)  IVEC_indexRand(__viVEC__, __Vlen,1) 

    extern void Mat_colSUM(float *vfSumVEC, float *vfMat_S, int iCOL_S, int iSumCOL, int iROW_S);
    #define VECs_sum(__VECsum__, __VECs_src__,__VEClen__, __VECnum__)  Mat_colSUM(__VECsum__, __VECs_src__,__VEClen__,__VEClen__, __VECnum__)


    extern void BlockSub(float *vfBlkOUT, float *vfBlk_A, float *vfBlk_B, int nBlkSIZE);
    #define VEC_sub(__VECout__, __VEC_A__, __VEC_B__, __VEClen__)          BlockSub(__VECout__, __VEC_A__, __VEC_B__, __VEClen__)

    extern void VEC_inv(float *vfVECinv, float *vfVECsrc, int VEClen, float fScale);

    extern void BlockMul(float *vfBlkOUT, float *vfBlk_A, float *vfBlk_B, int nBlkSIZE);
    #define VEC_mul(__VECout__,__VECsrs__, __VECby__, __VEClen__ ) BlockMul(__VECout__,__VECsrs__,__VECby__,__VEClen__)


    extern void  SetIntArray(int *vnArray, int nStartVal, int nStep, int nNUM);
    #define IVEC_step(__vnVEC__, __start__, __step__, __num__)  SetIntArray(__vnVEC__, __start__, __step__, __num__)

    extern void Mat_pick(float* vfMat_pick, float* vfMat_src, int SRCrow, int SRCcol, int PICKrow, int* viRowIDS, int PICKcol, int* viColIDS);

    extern float BlockMean(float *vfData, int nNum);
    #define VEC_mean(__vfVEC__, __VEClen__)   BlockMean(__vfVEC__, __VEClen__)

    #define _VEC_mulC(__vfVEC_O,__vfVEC_S, __Vlen, __fconst)  { int __jjj__; for(__jjj__=0; __jjj__ < (__Vlen);__jjj__++ ) { (__vfVEC_O)[__jjj__] = (__fconst)*(__vfVEC_S)[__jjj__];}}

    extern  void   Mat_diagGET(float* vfDiags, float* vfMat_src, int iDIM);

    extern  float SumCxPower( float *vfCxData, int nCxNum , int isAVG=0, float *vfOutPwr=0);    
    #define CxVEC_avgpwr(__CxVEC__, __VEClen__)          SumCxPower( __CxVEC__, __VEClen__,1, 0)

    extern  void  GaussianVEC_frannor(float *vfSignal,int nLEN, float fSigma, int isADDED, int isABS);  

    // ****************************************************************************************************************************************************************************

    


}



#endif /* __XPEDIA_SCMlsp_H */

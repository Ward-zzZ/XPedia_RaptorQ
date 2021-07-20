/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...
*************************************************************************************************************************************************************************  */



#ifndef __XPEDIA_AMC_SMP_H
#define __XPEDIA_AMC_SMP_H

#include "XPedia_AMC.h"

extern "C" {




    void   SMP_init(int* viMPCs_list, int MPClen, int NetTBS, int QamNUM, int iModuType, float fEsN0_dB,int BSnum, int RXnum,  int PMslen, int iAMC_ON=1);
    int SMP_control(int *viMPCs_list, int MPClen, float *vfCxPM_SBD, int *viINFOs_list, int MaxTBS, int *viCRC_list, float *vfSNR_list, float *vfCxPMsmeas, int PMslen, int SubBN, int TxN, int isPMok, int *viTransblock, int LyrN, int BSnum, int iSNRdlyTTI, int iPMIdlyTTI, int *viCRCblock);

    void   CxHs_merge(float* vfCxHs_full, float* vfCxHs_part, int RxM, int MaxN, int LyrN, int LyrBias, int MATnum);
    void   CxMat_pickCOLS(float* vfCxM_pick, float* vfCxM_src, int iRow, int iCol, int PickN, int iFrom);
    void   Mat_pickCOLS(float* vfMat_pick, float* vfMat_src, int iRow, int iCol, int PickN, int iFrom);




    // ******************************************************************************************************************************************************************************************
    extern  void CxMats_pullORG(float *vfCxMats_small, int iRow, int iCol, float *vfCxMats_BIG,int BigROW, int BigCOL,  int iRbias,int iCbias, int isTranpose, int isPULL, int MATnum);
    extern  void Mat_colcopy(float *vfMat_O, float *vfMat_S, int SRCcol, int SRCfrom,  int DSTcol, int DSTfrom,int MATrow, int COLcpy, int CloneN);
    extern  void MIMO_precoderRST(float* vfCxPM_SBD, int SubBN, int TxN, int LyrN, int isRandomPM);
    extern  void VEC_mulC(float *vfData, int nSample, float fConst);

    // ******************************************************************************************************************************************************************************************

}

#endif /* __XPEDIA_AMC_SMP_H */

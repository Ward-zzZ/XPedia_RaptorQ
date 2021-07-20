/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */



#ifndef __XPEDIA_MIMO_H
#define __XPEDIA_MIMO_H


#include "XPedia_mimoMLD.h"
#include "XPedia_mimoPrecoder.h"


extern "C" {

    
    void  MIMO_equalizer(float *vfllrs, float *vfCxRscs_list, float *vfCxH_scs, int RxM, int TxN, int SCnum , int ModuType, float fNoisePwr, int isLMMSE=1, int DOFDMnum=1);
    void  MIMO_layerSPLIT(float *vfData_O,  float *vfData_S,  int LyrSIZE, int SCnum, int LyrNUM);

    // *******************************************************************************************************************************************************************************
    extern  void BlockCxM_addDiagC(float *vfCxMats_out, float *vfCxMats_src,float *vfCxConst_list , int Dim, int MATnum);
    #define CxMats_addDiagC(__CxMats_out__, __CxMats_src__, __CxConst_list__, __dim__, __num__)     BlockCxM_addDiagC(__CxMats_out__, __CxMats_src__, __CxConst_list__, __dim__, __num__)

    extern  void LMMSE_Wgh_ORG(float *vfCxSC_wgh, float *vfCxSC_Hmat, float *vfCxSubB_Rvv, int RXport, int TXport, int SCnum, int SubBnum);
    extern  void  CxVEC_qamDemod(float *vfllrLIST,float *vfCxQamLIST,  int QamNum, int ModuType, float fNoisePwr);




    // *******************************************************************************************************************************************************************************



}



#endif /* __XPEDIA_MIMO_H */


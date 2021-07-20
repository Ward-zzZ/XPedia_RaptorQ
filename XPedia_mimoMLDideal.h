/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */



#ifndef __XPEDIA_MIMO_MLD_IDEAL_H
#define __XPEDIA_MIMO_MLD_IDEAL_H


extern "C" {
    
	void  MLD_cfgTX2(float *vfCxV_opts, int *viBitIDs_list, int TxN, int OPTs,  int ModuType);
    void  MIMO2x2_MLDideal(float *vfllrs, float *vfCxR2_sc, float *vfCxH2x2_sc,  int SCnum , int ModuType, float fNoisePwr );


    // ****************************************************************************************************************************
    extern   void  CxVECs_HxS(float *vfCxR_list,  float *vfCxH, float *vfCxS_list, int RxM, int TxN, int SCnum, int isHfixed );
    extern   void  Qam_Modu_REL(float *vfCxQamLIST, int *vnBits, int QamNum, int ModuType);
    extern   void  CxVECs_distSQR(float *vfDistSQR_list,  float *vfCxVEC_s, float *vfCxVECs_ref, int Vlen, int RefN );
    extern   void  VEC_pickMINS(float *vfMin_list, float *vfVEC_s, int Vlen, int *viPIDs_list, int PIDlen, int PIDnum);

    


    // ****************************************************************************************************************************


}



#endif /* __XPEDIA_MIMO_MLD_IDEAL_H */


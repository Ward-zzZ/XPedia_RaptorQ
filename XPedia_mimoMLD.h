/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */



#ifndef __XPEDIA_MIMO_MLD_H
#define __XPEDIA_MIMO_MLD_H


extern "C" {
    #define isPRINT_ON  0  //#define isPRINT_ON  1
    #define _isPrintF   if(isPRINT_ON) printf

    
    void   MIMO_mldDec(float* vfllrs, float* vfCxR_list, float* vfCxH_list, int LyrN, int SCnum, int ModuType, float fNoisePwr);
    void   MIMO_mldDec_ITF(float *vfLLRS, float* vfCxR_list, float* vfCxH_list, int LyrN, int ModuType, int SCnum, float fNoisePwr, int OFDMnum);


}



#endif /* __XPEDIA_MIMO_MLD_H */


/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */



#ifndef __XPEDIA_WAVEFORM_H
#define __XPEDIA_WAVEFORM_H


extern "C" {
    

    

    void   NXsubframe_genFD(float* vfCxFDofdm_list, int LyN, int DOFDMnum, float* vfCxQams_list, int DMRSnum, float* vfCxDMRSs_list, int RBnum, int RBfrom, int isGuardBand);
    void   NXQam_modu(float* vfCxQamLIST, int* viBits, int QamN, int ModuType);
    void   DMRSgen_ZCseq(float* vfCxSEQs_sc, int SCnum, int LyrN, int LyrBias, int MaxLyrN, int ZCroot, int DMRSnum, float *vfCxSEQs_all);

    // ****************************************************************************************************************************************************************************
    extern int   getPrime(int SCnum );
    extern void  CxSEQ_ZCseq(float *vfCxSEQs, int SCnum, int ZCroot, int ZCoffset);
    extern void VEC_clone(float *vfVEC_O,float *vfVEC_src, int  Vlen, int CloneN);

    extern void BlkMatrixTranpose(float *vfOutBlkMatrix,  float *vfSrcBlkMatrix, int nSrcMTXRow,  int nSrcMTXCol, int nBlkSize ,int isConj=0);    
    #define CxMat_tranposeS(__SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__)               BlkMatrixTranpose(__SrcMtx__, __SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__,2,0) 

    

    
    

    // ****************************************************************************************************************************************************************************

    


}



#endif /* __XPEDIA_WAVEFORM_H */

/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */



#ifndef __XPEDIA_MIMO_PRECODER_H
#define __XPEDIA_MIMO_PRECODER_H


extern "C" {

    void  MIMO_precoderRST(float* vfCxPM_SBD, int SubBN, int TxN, int LyrN, int isRandomPM=0);
    void  MIMO_precoder(float *vfCxSCV_TX,float *vfCxPM_SBD, float *vfCxSCs_lyr,   int TxN, int LyrN , int SubBN, int RBnum, int OFDMnum, int isPMok);
    float MIMO_precodingH(float *vfCxSCH_O, float *vfCxSCH_s, float *vfCxPM_SBD , int RxM,  int TxN, int LyrN , int SubBN, int RBnum, int OFDMnum);
    void  CxVEC_quantizePHS(float *vfCxVEC_O,  float *vfCxVEC_S, int Vlen, int BITnum);
    void  MIMO_precoderTypeII(float *vfCxPM_SBD , float *vfCxSCH_s,  int RxM,  int TxN, int LyrN , int SubBN, int RBnum, int TXAntC, int TXxplN, int  isRECsamples);
    




    // ************************************************************************************************************************************************************************************
    extern  void BlockCxCfg(float *vfCxData, float *vfCxConst, int CxNum);
    #define CxVEC_setIQ(__vfCxData__, __num__,__fI__,__fQ__) { float __vfCxConst__[2];__vfCxConst__[0]=__fI__; __vfCxConst__[1]=__fQ__;  BlockCxCfg(__vfCxData__, __vfCxConst__,__num__); }

    extern  void AVX_CxMats_mul_REL(float *vfCxM_out, float *vfCxM_A, float *vfCxM_B, int Row, int Joint , int Col, int MATnum, int isFixedMatA, int isBtranpose);
    #define CxMats_mul(__CxMout__, __CxMsrcA__,__CxMsrcB__,__row__,__Joint__,__col__, __num__)       AVX_CxMats_mul_REL(__CxMout__, __CxMsrcA__,__CxMsrcB__,__row__,__Joint__,__col__, __num__,0, 0)    
    #define CxMats_mulFixA(__CxMout__, __CxMsrcA__,__CxMsrcB__,__row__,__Joint__,__col__, __num__)   AVX_CxMats_mul_REL(__CxMout__, __CxMsrcA__,__CxMsrcB__,__row__,__Joint__,__col__, __num__,1, 0)    
    #define CxMats_mulFixB(__CxMout__, __CxMsrcA__,__CxMsrcB__,__row__,__Joint__,__col__, __num__)   AVX_CxMats_mul_REL(__CxMout__, __CxMsrcA__,__CxMsrcB__,__row__,__Joint__,__col__, __num__,2, 0)    
    #define CxMat_mul(__CxMout__, __CxMsrcA__,__CxMsrcB__,__row__,__Joint__,__col__)                 AVX_CxMats_mul_REL(__CxMout__, __CxMsrcA__,__CxMsrcB__,__row__,__Joint__,__col__,    1,   0, 0)
    #define CxMat_mulBT(__CxMout__, __CxMsrcA__,__CxMsrcB__,__row__,__Joint__,__col__)               AVX_CxMats_mul_REL(__CxMout__, __CxMsrcA__,__CxMsrcB__,__row__,__Joint__,__col__,    1,   0, 1)

    extern  float SumCxPower( float *vfCxData, int nCxNum , int isAVG, float *vfOutPwr);
    #define CxVEC_sumpwr(__CxVEC__, __VEClen__)          SumCxPower( __CxVEC__, __VEClen__,0, 0)
    #define CxVEC_avgpwr(__CxVEC__, __VEClen__)          SumCxPower( __CxVEC__, __VEClen__,1, 0)

    extern  void VEC_linear(float *vfData, float From, float Step, int nSample, int isHighPrecison);    
    #define VEC_step(__vfVEC__, __start__, __step__, __num__)  VEC_linear(__vfVEC__, __start__, __step__, __num__,1) 
    
    extern  void AVX_Fast_Sine_Cosine_H(float *vfSineVEC, float *vfCosineVEC, float *vfData, int nNUM); 
    #define VEC_sincos(__vfVECsin__,__vfVECcos__, __vfVECsrc__, __VEClen__ )    AVX_Fast_Sine_Cosine_H(__vfVECsin__,__vfVECcos__, __vfVECsrc__, __VEClen__ )

    extern  void  CxVEC_quant(float *vfCxVEC_quant, float *vfCxVEC_S, int Vlen, float *vfCxREF_list, int REFnum);
    extern  void  CxVEC_norm(float *vfCxVECnorm, float *vfCxVECsrc, int VEClen, float *pfVECamp);

    extern void BlockCxMulCONST(float *vfBlkOUT_IQ, float *vfBlkA_IQ, float fConst_I, float fConst_Q, int nCxNUM);    
    #define CxVEC_mulC(__CxVEC_o__,__CxVECsrc__, __VEClen__,__fConst_I__, __fConst_Q__)   BlockCxMulCONST(__CxVEC_o__,__CxVECsrc__, __fConst_I__, __fConst_Q__, __VEClen__);

    extern  void  VECs_avg(float *vfVECavg, float *vfVECs_list, int VEClen, int VECnum);
    #define CxVECs_avg(__CxVECavg,  __CxVEC_list, __Vlen, __Vnum)   VECs_avg(__CxVECavg,  __CxVEC_list, (__Vlen)*2, __Vnum)


    #define _CxVEC_conj(__CxVEC__, __VEClen__ )     { int __jjj__; float *__pfS = __CxVEC__;  for(__jjj__ = 0; __jjj__ < (__VEClen__); __jjj__++) { __pfS[1] *= -1.0; __pfS +=2; }   }

    extern  void BlkMatrixTranpose(float *vfOutBlkMatrix,  float *vfSrcBlkMatrix, int nSrcMTXRow,  int nSrcMTXCol, int nBlkSize ,int isConj);    
    #define Mat_tranpose(__SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__)                  BlkMatrixTranpose(__SrcMtx__, __SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__,1,0) 
    #define MatrixTranpose(__vfDstMtx__, __SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__)  BlkMatrixTranpose(__vfDstMtx__, __SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__,1,0) 
    #define CxMat_tranpose(__vfDstMtx__, __SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__)  BlkMatrixTranpose(__vfDstMtx__, __SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__,2,0) 
    #define CxMat_tranposeS(__SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__)               BlkMatrixTranpose(__SrcMtx__, __SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__,2,0) 
    #define CxMat_conjtrans(__vfDstMtx__, __SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__) BlkMatrixTranpose(__vfDstMtx__, __SrcMtx__, __SrcMtxROW__, __SrcMtxCOL__,2,1) 

    extern  void  CxMat_fillDiag(float* vfCxM_major, int iRow, int iCol, float* vfCxM_subM, int SubM_R, int SubM_C); 

    extern  void  VEC_clone(float *vfVEC_O,float *vfVEC_src, int  Vlen, int CloneN);
    #define CxVEC_clone(__vfCxV_O, __vfCxV_S, __Vlen, __CloneN)  VEC_clone(__vfCxV_O, __vfCxV_S, (__Vlen)*2, __CloneN) 
    
    extern  void  VEC_rand(float *vfnoise, int VEClen, float fFrom, float fTo);
    // ************************************************************************************************************************************************************************************


}



#endif /* __XPEDIA_MIMO_PRECODER_H */


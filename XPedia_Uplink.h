

#ifndef __XPEDIA_PUCCH_H
#define __XPEDIA_PUCCH_H


#include "PerfMetric_COMM.h"
//#include "RadioSignalBase.h"
#include "XPedia_CODEC.h"
#include "XPedia_waveform.h"
#include "XPedia_AMC.h"
#include "XPedia_mimoPrecoder.h"

extern "C" {

    #define  NR_FRAMESLOTS_N  10
    #define  NR_MAXCellNUM    335*3
    #define  PI              3.14159265

    #define _GET_QamBITS(__MT)  ((((__MT)>>1)&0x1)*1+(((__MT)>>2)&0x1)*2+(((__MT)>>3)&0x1)*3+(((__MT)>>4)&0x1)*4+(((__MT)>>6)&0x1)*6+(((__MT)>>8)&0x1)*8+(((__MT)>>10)&0x1)*10)
    
    extern  int gviPhi_len6[];
    extern  int gviPhi_len12[];
    extern  int gviPhi_len18[];
    extern  int gviPhi_len24[];

    // **************************************************  numerology definition  *******************************************************************************    
    extern int   gviTTI14_CPlist_14[];   
    extern int   gviTTI14_DMRSpos2[];
    
    extern void  LTEofdm_disassemble(float *vfCxSCsig_data, float *vfCxSCsig_dmrs, float *vfCxSCsrc_list, int SCnum,  int VEClen, int isDL);


    void   NRslot_config(int SLOTlen, int isNR);



    // **********************************************************************************************************************************************************    
    void  NR_GoldenSEQ(int *viVECseq, int VEClen, int Cinit);
    
    void  CxSEQ_papr(float *vfPAPR_list, float *vfCxSEQs_list, int SEQlen, int SEQnum );
    void  CxSEQs_xcorr(float *vfMATxcorr, float *vfCxSEQs_list, int SEQlen, int SEQnum );    
    void  NRseq_cgsQpsk(float *vfCxSEQ, int *viQpskIDS, int ilen);

    extern  void CxVEC_phaseRotateSTD(float *vfCxVECout, float *vfCxVECsrc, int nLEN, float fRADperSamp );
    extern  int  getPrime(int SCnum );
    extern  void AVX_Gen_ZadoffChu_SEQ(float *vfZC_IQLIST, int ZClen, int ZCprime, int ZCroot, int ZCoffset );
    extern  void GenLTE_GoldSeq_REL(float *vfCxGoldseq, int Cinit, int ilen );



    // **********************************************************************************************************************************************************    
    // *******************************************************       PUCCH    *****************************************************************************    
    int   PUCCH_ncs(int OFDMid, int SLOTid, int Cinit);
    float PUCCH_Alpha(int OFDMid, int SLOTid, int iM_cs, int CellID);
    //void  PUCCHformat0_genSEQ(float *vfCxSEQ_list, int SCnum, int OFDMnum, int iBIT0, int iBIT1);
    //void  PUCCHformat1_genSEQ(float *vfCxSEQ_list, int SCnum, int OFDMnum, int OCCid, int iBIT0, int iBIT11);
    void  PUCCHformat0_genSEQ(float *vfCxSEQ_list, int SCnum, int OFDMnum, int iBIT0, int iBIT11, int iSLOTcnt, int GRPid, int CellID);    
    void  PUCCHformat1_genSEQ(float *vfCxSEQ_list, int SCnum, int OFDMnum,int iBIT0, int iBIT11,int iSLOTcnt, int GRPid, int OCCid, int CellID);
    void  PUCCH_BaseSEQ_ITF(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid);
    void  PUCCH_baseSEQ_len6(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid);
    void  PUCCH_baseSEQ_len12(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid);
    void  PUCCH_baseSEQ_len18(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid);
    void  PUCCH_baseSEQ_len24(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid);
    void  PUCCH_baseSEQ_len30(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid);
    int   PUCCHformat1_occ(float *vfCxOCC_list, int Maxlen,  int OFDMnum);

    void  PUCCHformat0_est(int *viBITS_2, float *vfCxSCsrc_list,float *vfCxSEQs_org,int SCnum, int RXnum, int OFDMnum, int iBitN);
    void  PUCCHformat1_est(int *viBITS_2, float *vfCxSCsrc_list,float *vfCxSEQs_org,int SCnum, int RXnum, int OFDMnum, int iBitN);

    

    // **********************************************************************************************************************************************************
    // *******************************************************       PUSCH    *****************************************************************************    

    void  PUSCHDmrs_OFDM(float *vfCxVECseq, int RBnum, int SLOTid, int OFDMid, int iCellID);
    void  PUSCHDmrs_DFTsOFDM(float *vfCxVECseq, int RBnum, int SLOTid, int OFDMid, int iCellID, int iHoppingMODE);

    //void  NRofdm_equalizer(float *vfCxQams,  int SCnum, int VEClen, float *vfCxSCsrc_list,float *vfCxSEQs_org,  float fNoisePwr, float *vfCxSCfadings);
    //void  NRofdm_equalizer(float *vfCxQams,  int SCnum, int RXport, int TXport, float *vfCxSCsrc_list,float *vfCxSEQs_org,  float fNoisePwr, float *vfCxHice_list);
    void  NRofdm_equalizer(float *vfCxQams,  int SCnum, int RXport, int TXport, float *vfCxSCsrc_list,float *vfCxSEQs_org,  float fNoisePwr, float *vfCxHice_list, int ModuType=0, int isLMMSE=1);

    float NRcest_dmrs(float *vfCxDMRSfading_list, float  *vfCxDMRSsig_list, float *vfCxSEQs_list, int RXnum,  int SCnum, int DMRSnum);
    void  NRcest_2DInterp(float *vfCxDATAfadings_list,  float *vfCxDMRSfading_list, int RXnum, int SCnum, int DMRSnum, int DOFDMnum);
    float NRmeas_QamSNR(float  *vfCxQams_equalizer,   float *vfCxQams_org,  int QAMnum);

    
    extern int GetQamBITS(int ModuTYPE);
    extern void CxMats_pullORG(float *vfCxMats_small, int iRow, int iCol, float *vfCxMats_BIG,int BigROW, int BigCOL,  int iRbias,int iCbias, int isTranpose, int isPULL, int MATnum);
    extern void   CxHs_merge(float* vfCxHs_full, float* vfCxHs_part, int RxM, int MaxN, int LyrN, int LyrBias, int MATnum);

    // **********************************************************************************************************************************************************
    void NRslot_genOFDM(float *vfCxOFDMsig, int FFTlen, int CPlen, float *vfCxSC_list, int RBnum,int RBoffset, int isZeroDC);    
    void NRslot_gen(float* vfCxSLOTsig, int SLOTlen, float *vfCxSC_list, int RBnum, int RBoffset, int OFDMfrom, int OFDMnum, int isZeroDC);

    // **********************************************************************************************************************************************************
    void MIMO2x2_MLDideal(float *vfllrs, float *vfCxR2_sc, float *vfCxH2x2_sc,  int SCnum , int ModuType, float fNoisePwr );

    extern  void MIMO_equalizer(float *vfllrs, float *vfCxRscs_list, float *vfCxH_scs, int RxM, int TxN, int SCnum , int ModuType, float fNoisePwr, int isLMMSE, int DOFDMnum);            
    extern  void QRMLD_mimoDEC(float *vfLLRS, float* vfCxR_list, float* vfCxH_list, int Dim, int ModuType, int SCnum, float fNoisePwr, int OFDMnum);
    extern  void MIMO_mldDec_ITF(float *vfLLRS, float* vfCxR_list, float* vfCxH_list, int LyrN, int ModuType, int SCnum, float fNoisePwr, int OFDMnum);

    extern  void  GenFDSeq_OFDMwaveform(float *vfCxWaveform, float *vfFDSeqIQ, int SEQlen, int SysSCnum, int FFTsize);
    extern  float Calc_PAPRdB_REL(float *vfBlockCx, int nCxNum);

    //extern  void AVX_CxVEC_XCorr_REL(float *vfXCorrVEClist,int VEClen,int refNUM, float *vfCxVECreflist, int VECnum, float *vfCxVEClist,int isConj, int isNORM=0, int isXCPwr=1);
    //extern  void FFTV_AVX_InterFACE(float *vfOUT_IQVEC, float *vfSRC_IQVEC,int nFFTSize, int nCxNumPerVEC, int isFFT, int isNORM ,int gCMD_FFTW_ON, int isFFTvec=1);    
    extern  void AVX_CxVEC_XCorr_REL(float *vfXCorrVEClist,int VEClen,int refNUM, float *vfCxVECreflist, int VECnum, float *vfCxVEClist,int isConj, int isNORM, int isXCPwr);
    extern  void FFTV_AVX_InterFACE(float *vfOUT_IQVEC, float *vfSRC_IQVEC,int nFFTSize, int nCxNumPerVEC, int isFFT, int isNORM ,int gCMD_FFTW_ON);    

    #define CxVEC_fft(__CxVECout__,__CxVEC__, __FFTlen__)   FFTV_AVX_InterFACE(__CxVECout__, __CxVEC__, __FFTlen__,1, 1, 1, 1 )
    #define CxVEC_ifft(__CxVECout__,__CxVEC__, __FFTlen__)  FFTV_AVX_InterFACE(__CxVECout__, __CxVEC__, __FFTlen__,1, 0, 1, 1 )

    extern  void BlockCxM_addDiagC(float *vfCxMats_out, float *vfCxMats_src,float *vfCxConst_list , int Dim, int MATnum);
    #define CxMats_addDiagC(__CxMats_out__, __CxMats_src__, __CxConst_list__, __dim__, __num__)   BlockCxM_addDiagC(__CxMats_out__, __CxMats_src__, __CxConst_list__, __dim__, __num__)

    extern  void  DMRS_SubBrvv(float *vfCxRvv_list, float *vfCxDMRSsrc_list, float *vfCxSEQs_org,  float *vfCxCEvec_list, int VEClen,  int SCnum, int SubBnum, int DMRSnum);
    extern  void  LMMSE_Wgh_ORG(float *vfCxSC_wgh, float *vfCxSC_Hmat, float *vfCxSubB_Rvv, int RXport, int TXport, int SCnum, int SubBnum);
    extern  void  CxVECs_dotprodSTD(float *vfCxDotProd, float *vfCxVECs_A, float *vfCxVECs_B, int VEClen, int VECnum);


    extern  int   BlockSumInt(int *vnData, int nSize );
    #define IVEC_sum(__vnVEC__, __VEClen__)  BlockSumInt(__vnVEC__, __VEClen__) 

    extern float BlockSum(float *vfData, int nSize );    
    #define VEC_sum(__vfVEC__, __VEClen__)   BlockSum(__vfVEC__, __VEClen__) 

    extern  void BlockAdd(float *vfBlkOUT, float *vfBlk_A, float *vfBlk_B, int nBlkSIZE);
    #define VEC_add(__VECout__, __VEC_A__, __VEC_B__, __VEClen__) BlockAdd(__VECout__, __VEC_A__, __VEC_B__, __VEClen__)



    extern  void   CxMat_pickCOLS(float* vfCxM_pick, float* vfCxM_src, int iRow, int iCol, int PickN, int iFrom);
    extern  void   Mat_pickCOLS(float* vfMat_pick, float* vfMat_src, int iRow, int iCol, int PickN, int iFrom);
    extern  void  CxVEC_qamDemod(float *vfllrLIST,float *vfCxQamLIST,  int QamNum, int ModuType, float fNoisePwr);

    

    // **********************************************************************************************************************************************************    

    extern  void BlockFltCfg(float *vfData, float fConst, int nNUM);    
    #define VEC_set(__vfData__,__num__, __fConst__)           BlockFltCfg(__vfData__, __fConst__,__num__)
    extern  void BlockIntCfg(int *vnData, int nConst, int IntNum);
    #define IVEC_set(__vnData__,__num__, __iConst__)          BlockIntCfg(__vnData__, __iConst__,__num__)


    extern  void GDB_CxSave(char *strVarName, float *vfCxData, int nCxVECSize, int nVECNum );
    extern  void GDB_IntSave(char *strVarName, int *vnData, int nColPerROW, int nROW );
    extern  void GDB_FltSave(char *strVarName, float *vfData, int nColVECSize, int nVECNum);
    extern  void GDBrst_CHK(int isForceRst);

    extern  void BlockCxMulCONST(float *vfCxVEC_o, float *vfCxVECsrc, float fConst_I, float fConst_Q, int VEClen);

    //void GDB_svCxM(char *strVarName, float *vfCxMdata, int iRow, int iCol) { GDB_CxSave(strVarName,vfCxMdata,  iCol, iRow); }
    //void GDB_svMat(char *strVarName, float *vfMat, int iRow, int iCol)     { GDB_FltSave(strVarName,vfMat, iCol,iRow);      }
    //void GDB_svIMat(char *strVarName, int *viMat,  int iRow, int iCol)     { GDB_IntSave(strVarName,viMat, iCol,iRow);      }
    //void GDB_rst(int iForce)                                               { GDBrst_CHK(iForce);       } 

    




    
}

#endif /* __XPEDIA_PUCCH_H */

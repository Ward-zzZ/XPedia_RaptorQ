

#ifndef __XPEDIA_TRANSCEIVER_H
#define __XPEDIA_TRANSCEIVER_H


extern "C" {


    // **********************************************************************************************************************************************************
    // *******************************************************       Transceivers   *****************************************************************************


    void   NR_transmitterORG(float* vfCxOFDMs_TxN, int* viINFObits, int NetTBS, int RvID, int RBnum,int RBfrom, int TxN, int LyrN, int ModuType, int SEQmaxN, int SEQfrom, float* vfCxSEQs_pool, int iSEQready, int SubBN, float* vfCxPM_SBD, int isPMok);
    void   NR_receiverORG(int* viCRC, float* vfCxSCv_RX, float *vfCxScH_ICE, int* viNetTBS, int* viRvID, int RBnum, int RBfrom, int RxM, int* viLyrN, int* viModuType,int SEQmaxN, int* viSEQfrom, float* vfCxSEQs_pool, float* vfHARQllr_pool, int HARQlen, int CWnum, float fNoisePwr, float *pfMrgHARQllrs=0);

    void   NR_transmitterS(float* vfCxTxOFDMs_pool, int TxN, int* viMPC_pool, int MPClen, int* viSrcBITS_pool, int MaxTBS, int RBnum, int RBfrom, int SEQmaxN,float* vfCxSEQs_pool, int SubBN, int PMlen, float* vfCxSubBPMs_pool,int isPMok,int iSenderN);

    int NR_receiverS(int *viCRC_pool, int CRClen, int *viMPC_pool, int MPClen, float *vfCxOFDMs_pool, float *vfCxHe_pool, int iHElen, int RBnum, int RBfrom, int RxM, int SEQmaxN, float *vfCxSEQs_pool, int HARQlen, float *vfHARQllr_pool, int iSendrN, int iRecvrM, float fNoisePwr, int *viCRCblock);

    float  NR_ice(float* vfCxHes_pool,int iHElen, int* viMPC_pool, int MPClen, int RBnum , int SubBN, int PMslen, int isPMok, float* vfCxPMs_pool, int RxM, int TxN, float* vfCxSCHorg_pool,float fNoisePwr, int iSendrN, int iRecvrM, float *vfSNRdB_pool);
    void   NRprecoder_TypeII(float* vfCxPMs_pool, int* viMPC_pool, int MPClen, int SubBN, int PMslen, int RBnum, float* vfCxSCHorg_pool, int RxM, int TxN, int TXantC, int TXxplN, int iSendrN);
    void   NR_llrDEC(int* viCRC,  int* viNetTBS,int* viLyrN, int* viModuType, float* vfHARQllr_pool, int HARQlen,  int RBnum,  int CWnum);


    // **********************************************************************************************************************************************************




    // **********************************************************************************************************************************************************



}

#endif /* __XPEDIA_TRANSCEIVER_H */

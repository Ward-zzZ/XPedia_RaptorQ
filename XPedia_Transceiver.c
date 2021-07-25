
#include "XPedia_Uplink.h"
#include "XPedia_Transceiver.h"








void   NR_transmitterORG(float* vfCxOFDMs_TxN, int* viINFObits, int NetTBS, int RvID, int RBnum,int RBfrom, int TxN, int LyrN, int ModuType, int SEQmaxN, int SEQfrom, float* vfCxSEQs_pool, int iSEQready, int SubBN, float* vfCxPM_SBD, int isPMok)
/* generate one TTI PUSCH transmission signal
*  vfCxOFDMs_TxN : list of OFDMs, each subcarrier carries TxN complex values w.r.t TxN antennas
*  viINFObits    : information bits
*  NetTBS        : net TBSize
*  RvID          : Redundancy Version ID (used by encoder)
*  RBnum         : number of used RBs
*  RBfrom        : RB offset
*  TxN           : number of TX antennas
*  LyrN          : number of layers
*  ModuType      : modulation Type
*  SEQmaxN       : max number of sequences ( a group of sequences used )
*  SEQfrom       : offset of used sequences ( LyrN is the number of sequence used)
*  vfCxSEQs_pool : list of all sequences  (used by channel estimation)
*  iSEQready     : 1(sequences are ready) or  0(not ready)
*  SubBN         : number of subbands
*  vfCxPM_SBD    : list of precoding matrix for each subband
Change History
*  1st version designed by Duan Weiming in 2021-05-15
*/
{
    int ZCroot = 1;   int DMRSnum = 2;       int DOFDMn = 12;                    int OFDMnum = DOFDMn + DMRSnum;      int jjj,cnt, SUBBscn;
    retERR_LEZ4(NetTBS,RBnum,LyrN,SEQmaxN)   retERR_LTZ2(RBfrom, SEQfrom)        retERR_RNG(RBnum + RBfrom, 5, 100)   retERR_RNG(LyrN + SEQfrom, 1, SEQmaxN)
    int SCnum   = RBnum*12;                  retERR_LIST(ModuType,2,4,16,64,256)
    int QamBITS = GetQamBITS(ModuType);      retERR_LIST(QamBITS,2,4,6,8,10)     retERR_RNG(RvID, 0, 3)
    int QamNUM  = DOFDMn*SCnum*LyrN;
    int RVlen   = QamNUM*QamBITS;
    if(vfCxPM_SBD) { SUBBscn = SCnum/SubBN;  retERR_NEQ(SUBBscn*SubBN, SCnum)   }

    MEMCHK(vfCxOFDMs_TxN, 14*SCnum*TxN*2)     MEMCHK(viINFObits, NetTBS)     nzMEMCHK(vfCxSEQs_pool, DMRSnum*SEQmaxN*SCnum*2)     nzMEMCHK(vfCxPM_SBD, SubBN*TxN*LyrN*2)


    _NEW_INIT()   _NEW_FLT0(vfCxDMRS_list, DMRSnum*SCnum*LyrN*2)   _NEW_INT0(viRvBITS, RVlen)   _NEW_FLT0(vfCxQamS, QamNUM*2)    _NEW_FLT0(vfCxSCs_lyr, OFDMnum*SCnum*LyrN*2)



    //DMRSgen_ZCseq(float* vfCxSEQs_sc, int SCnum, int LyrN, int LyrBias, int MaxLyrN, int ZCroot, int DMRSnum, float *vfCxSEQs_all);
    if( iSEQready ) { CxMats_pullORG(vfCxDMRS_list, LyrN, SCnum,  vfCxSEQs_pool, SEQmaxN, SCnum ,   SEQfrom, 0,  1, 1, DMRSnum);  } // isTranpose=1  isPULL=1
    else            { DMRSgen_ZCseq(vfCxDMRS_list,  SCnum,  LyrN,  SEQfrom, SEQmaxN,  ZCroot,  DMRSnum, vfCxSEQs_pool);           }
    TurboEncoder_ITF(viRvBITS,  RVlen,viINFObits,  NetTBS,  ModuType,   RvID );
    NXQam_modu(vfCxQamS, viRvBITS,  QamNUM,  ModuType);
    NXsubframe_genFD(vfCxSCs_lyr, LyrN, DOFDMn, vfCxQamS, DMRSnum, vfCxDMRS_list,   RBnum,  RBfrom, 0);
    MIMO_precoder(vfCxOFDMs_TxN, vfCxPM_SBD,  vfCxSCs_lyr,  TxN,  LyrN ,  SubBN,  RBnum,  OFDMnum, isPMok);

    _NEW_FREE()

}





void   NR_receiverORG(int* viCRC, float* vfCxSCv_RX, float *vfCxScH_ICE, int* viNetTBS, int* viRvID, int RBnum, int RBfrom, int RxM, int* viLyrN, int* viModuType,
                      int SEQmaxN, int* viSEQfrom, float* vfCxSEQs_pool, float* vfHARQllr_pool, int HARQlen, int CWnum, float fNoisePwr, float *pfMrgHARQllrs)
/*  PUSCH receiver
*  viCRC          : CRC for each codeword
*  vfCxSCv_RX     : list of received OFDMs at RxM antennas, each subcarrier has a receive complex vector
*  vfCxScH_ICE    : list of H matrix for each subcarrier
*  viNetTBS       : net TBSize for each codeword
*  viRvID         : Redundancy Version ID (used by encoder) for each codeword
*  RBnum          : number of used RBs
*  RBfrom         : RB offset
*  RxM            : number of RX antennas
*  viLyrN         : number of layers for each codeword
*  viModuType     : modulation Type for each codeword
*  SEQmaxN        : max number of sequences
*  viSEQfrom      : offset of used sequences ( LyrN is the number of sequence used) for each codeword
*  vfCxSEQs_pool  : list of all sequences  (used by channel estimation)
*  vfHARQllr_pool : list of HARQ llr buffers (used for each decoder)
*  CWnum          : number of codeword
Change History
*  1st version designed by Duan Weiming in 2021-05-16
*/
{

    int isLMMSE = 1;        int ZCroot  = 1;
    int DMRSnum = 2;        int DOFDMn = 12;     int OFDMnum = DOFDMn + DMRSnum;      int jjj,cnt,QamBsum;   float *vfHARQ_llr, *pfMRGllrs;

    retERR_LEZ5(RBnum,RxM,SEQmaxN,CWnum,HARQlen)   retERR_LTZ(RBfrom)           retERR_RNG(RxM,1,4)    retERR_RNG(CWnum,1,4) retERR_RNG(RBfrom + RBnum, 5, 100)
    int SCnum   = RBnum*12;                        int SUMsc  = DOFDMn*SCnum;
    int LyrSUM  = IVEC_sum(viLyrN, CWnum);         int QamSUM = SUMsc*LyrSUM;
    int BITsum  = IVEC_sum(viNetTBS, CWnum) + 24*CWnum + 1000;

    MEMCHK(vfCxSCv_RX,  14*SCnum*RxM*2)          MEMCHK2(viModuType,viSEQfrom, CWnum)       MEMCHK4(viCRC,viNetTBS,viRvID,viLyrN, CWnum)       nzMEMCHK(pfMrgHARQllrs, CWnum*HARQlen)
    MEMCHK(vfCxScH_ICE, 14*SCnum*RxM*LyrSUM*2)   MEMCHK(vfHARQllr_pool,  CWnum*HARQlen )    nzMEMCHK(vfCxSEQs_pool, DMRSnum*SEQmaxN*SCnum*2)

    _NEW_INIT()              _NEW_FLT0(vfRVllrs, QamSUM*16)  _NEW2_INT0(vQamB, vQamN, CWnum)
    _NEW_INT0(viCRCmem,10)   _NEW_INT0(viDECbitS, BITsum)    _NEW2_FLT0(vfCxQams_RX, vfCxQams, QamSUM*2)

    _LOOPUP_LT(jjj, 0,CWnum) { vQamB[jjj] = GetQamBITS(viModuType[jjj]); }   QamBsum  = 0;
    _LOOPUP_LT(jjj, 0,CWnum) { vQamN[jjj] = viLyrN[jjj]*SUMsc;               QamBsum += viLyrN[jjj]*vQamB[jjj];       }

    NRofdm_equalizer(vfCxQams_RX, SCnum, RxM, LyrSUM, vfCxSCv_RX, vfCxSEQs_pool, fNoisePwr ,vfCxScH_ICE, 0, isLMMSE); // ModuType = 0 ==> output equalized Qam symbols instead of llr
    int  LyrBias = 0;     int  BITBias = 0;  int *pDECBiTS = viDECbitS;
    _LOOPUP_LT(cnt, 0, CWnum) { // for each codeword
        if( isLMMSE ) {
            CxMat_pickCOLS(vfCxQams, vfCxQams_RX, SUMsc, LyrSUM,  viLyrN[cnt], LyrBias);           LyrBias += viLyrN[cnt];   CxVEC_qamDemod(vfRVllrs, vfCxQams,QamSUM,viModuType[cnt],0.5*fNoisePwr);
        } else {
            Mat_pickCOLS(vfRVllrs, vfCxQams_RX, SUMsc, QamBsum, viLyrN[cnt]*vQamB[cnt], BITBias);  BITBias += viLyrN[cnt]*vQamB[cnt];
        }
        vfHARQ_llr  = vfHARQllr_pool + cnt*HARQlen;

        //int isRstHarqLLR = 0;  if( 0 == viRvID[cnt] ) { isRstHarqLLR = 1;  }
        //int isUptHarqLLR = 0;  int viCRCmmm[4];
        pfMRGllrs = 0;  if(pfMrgHARQllrs)      { pfMRGllrs = pfMrgHARQllrs + cnt*HARQlen; }

        LTEturbo_decoderORG(viCRCmem, vfRVllrs, viNetTBS[cnt], vQamN[cnt], viModuType[cnt], vfHARQ_llr, viRvID[cnt], 16, pDECBiTS,  1,  1, pfMRGllrs); // isRstHarqLLR=1,  isUptHarqLLR=1
        //TurboDecoder_ITF(viCRCmem, vfRVllrs, vQamN[cnt], viNetTBS[cnt], vfHARQ_llr, viModuType[cnt], viRvID[cnt],pDECBiTS ,16);

        pDECBiTS += viNetTBS[cnt] + 24;

        //if(viCRCmem[0] != viCRCmmm[0] ) {
        //    int iTST = 3;
        //}

        viCRC[cnt] = viCRCmem[0];

    }




    //     # (ModuType = 0) ==> equalization wo. demod
    //    # ********************************************************************************************************************************************************
    //    for cntBS in range(BSmaxN) :
    //        (LyrN0, LyrBias,RvID,RVlen,NetTBS,ModuType,iMCS) = getMPCs(viMPCs_BSs[cntBS*MPClen:(cntBS+1)*MPClen]);  QamNUM=LyrN0*SUMsc;  QamB=GetQamBITS(ModuType);
    //        if (0 == LyrN0) : continue;
    //        # ****************************************************************************************************************************************************
    //        # ******************************** Demodulation and decoder for layers of current base staion  *******************************************************
    //        # ****************************************************************************************************************************************************
    //        if  isLMMSE :  CxMat_pickCOLS(vfCxQams, vfCxQams_RX, SUMsc, LyrN,  LyrN0, LyrBias);      CxVEC_qamDemod(vfRVllrs, vfCxQams,  QamNUM,  ModuType,  0.5*fNoisePwr);
    //        else        :  Mat_pickCOLS(vfRVllrs, vfCxQams_RX, SUMsc, LyrN*QamB, LyrN0*QamB, LyrBias*QamB);   #pick llrs for current link
    //        vfHARQ_llr  = vfHARQllr_BSs[cntBS*HARQlen:(cntBS+1)*HARQlen];
    //        TurboDecoder_ITF(viCRC, vfRVllrs, QamNUM, NetTBS, vfHARQ_llr, ModuType, RvID,viDECbits,16);

    _NEW_FREE()

}



void   NR_transmitterS(float* vfCxTxOFDMs_pool, int TxN, int* viMPC_pool, int MPClen, int* viSrcBITS_pool, int MaxTBS, int RBnum, int RBfrom, int SEQmaxN,float* vfCxSEQs_pool, int SubBN, int PMslen, float* vfCxPMs_pool,int isPMok,int iSenderN)
/* generate PUSCH transmission signal for each transimitter
*  vfCxTxOFDMs_pool : Pool of OFDMs for each Transmitter, each subcarrier carries TxN complex values w.r.t TxN antennas
*  TxN              : number of tx antennas for each Transmitter
*  viMPC_pool       : Pool of MPCs (Multi-Point Coordination scheduling parameter) for each Transimitter
*  MPClen           : length of MPC
*  viSrcBITS_pool   : Pool of information bits for each Transmitter
*  MaxTBS           : maximum TBsize
*  RBnum            : number of used RBs
*  RBfrom           : RB offset
*  SEQmaxN          : max number of sequences ( a group of sequences used )
*  vfCxSEQs_pool    : pool of sequences  (used by channel estimation)
*  SubBN            : number of subbands
*  PMslen           : max length of Precoding Matrice for each Transmitter
*  vfCxPMs_pool     : pool of precoding matrice(for each subband) for each Transimitter
*  iSenderN         : number of Transimitters
Change History
*  1st version designed by Duan Weiming in 2021-05-17
*/
{

    retERR_LEZ4(TxN,MPClen,MaxTBS,RBnum)  retERR_LEZ4(SEQmaxN,SubBN,PMslen,iSenderN)   int jjj,cnt;  int *pMPC, *piSrcBITS;  float *pfCxOFDMs, *pfCxPMs;

    int DMRSnum = 2;        int DOFDMn = 12;     int OFDMnum = DOFDMn + DMRSnum;      int SCnum   = RBnum*12;    int iSEQready=0;

    MEMCHK(vfCxTxOFDMs_pool, iSenderN*OFDMnum*SCnum*TxN*2)
    MEMCHK(viMPC_pool,       iSenderN*MPClen)
    MEMCHK(viSrcBITS_pool,   iSenderN*MaxTBS)
    MEMCHK(vfCxSEQs_pool,    SEQmaxN*SCnum*2)
    MEMCHK(vfCxPMs_pool,     iSenderN*PMslen)


    //_NEW_INIT() _NEW_FLT0()

    _LOOPUP_LT(jjj, 0, iSenderN) {
        pMPC      = viMPC_pool       + jjj*MPClen;
        pfCxOFDMs = vfCxTxOFDMs_pool + jjj*OFDMnum*SCnum*TxN*2;
        piSrcBITS = viSrcBITS_pool   + jjj*MaxTBS;
        pfCxPMs   = vfCxPMs_pool + jjj*PMslen;

        MEM_6INT(pMPC, LyrN, SEQfrom, iRvID, RVlen, NetTBS, iModuType )
        if( 0 == LyrN) {  FLT_ZERO(pfCxOFDMs, OFDMnum*SCnum*TxN*2);  continue; }
        ERR_RNG(SEQfrom,0,SEQmaxN-1)   ERR_RNG(LyrN,1,TxN)  ERR_RNG(iRvID,0,3)   ERR_RNG(iModuType,2,256)

        NR_transmitterORG(pfCxOFDMs , piSrcBITS,  NetTBS, iRvID, RBnum, RBfrom, TxN, LyrN, iModuType,  SEQmaxN, SEQfrom, vfCxSEQs_pool,  iSEQready,  SubBN,  pfCxPMs,  isPMok);
    }

    //_NEW_FREE()

}


void   MPCs_fetch(int* viLyrN, int* viSEQfrom, int* viRvID, int* viRVlen, int* viNetTBS, int* viModuType, int MPClen, int* viMPC_pool, int CWnum, int SEQmaxN, int MaxLyrN)
/* get parameters for each MPC
*  viLyrN     : layer number for each codeword
*  viSEQfrom  : SEQ start ID for each codeword
*  viRvID     : RV id for each codeword
*  viRVlen    : RV length for each codeword
*  viNetTBS   : Net TBsize for each codeword
*  viModuType : Modulation type for each codeword
*  MPClen     : length of MPC
*  viMPC_pool : pool of MPC parameters
*  CWnum      : number of codeword
Change History
*  1st version designed by Duan Weiming in 2021-05-22
*/
{

    retERR_LEZ2(MPClen,CWnum)     int jjj,cnt;             int *pMPC;
    MEMCHK4(viLyrN,viSEQfrom, viRvID, viRVlen, CWnum)      MEMCHK2(viNetTBS, viModuType, CWnum)    MEMCHK(viMPC_pool, CWnum*MPClen)



    _LOOPUP_LT(jjj, 0, CWnum) {
        pMPC = viMPC_pool + jjj*MPClen;
        _MEM_6INT(pMPC, viLyrN[jjj], viSEQfrom[jjj], viRvID[jjj], viRVlen[jjj], viNetTBS[jjj], viModuType[jjj] )
        ERR_RNG(viSEQfrom[jjj],0,SEQmaxN-1)   ERR_RNG(viLyrN[jjj],1,MaxLyrN)  ERR_RNG(viRvID[jjj],0,3)   ERR_RNG(viModuType[jjj],2,256)       // ERR_NEQ(viRVlen[0],viRVlen[jjj]) // removed!!! maybe different w.r.t different Qam type

    }



}



int    MPC_sumlayer(int* viLyrN_list, int* viMPC_pool, int MPClen, int iSendrN)
/* return sum layers of transmitters
*  viLyrN_list : list of layers for each transmitter
*  viMPC_pool  : list of MPCs (Multi-Point Coordination scheduling parameter)
*  iSendrN     : number of Transimitter
Change History
*  1st version designed by Duan Weiming in 2021-05-19
*/
{

    ret0ERR_LEZ2(iSendrN,MPClen)    int jjj,cnt;  int *pMPC;

    nzMEMCHK(viLyrN_list, iSendrN)     MEMCHK(viMPC_pool, iSendrN*MPClen)
    _NEW_INIT()   _NEW_INT0(viLyrN, iSendrN)


    _LOOPUP_LT(jjj, 0, iSendrN) {
        pMPC = viMPC_pool + jjj*MPClen;
        MEM_6INT(pMPC, iLyrN, iSEQfrom, iRvID, RVlen, iNetTBS, iModuType )
        ERR_RNG(iLyrN,1,4)  ERR_RNG(iRvID,0,3)   ERR_RNG(iModuType,2,256)
        viLyrN[jjj] = iLyrN;
    }

    int SumLyrN = IVEC_sum(viLyrN, iSendrN);
    if( viLyrN_list) { INT_CP(viLyrN, viLyrN_list, iSendrN);   }
    return SumLyrN;

}

int NR_receiverS(int *viCRC, int CRClen, int *viMPC_pool, int MPClen, float *vfCxOFDMs_pool, float *vfCxHe_pool, int iHElen, int RBnum, int RBfrom, int RxM, int SEQmaxN, float *vfCxSEQs_pool, int HARQlen, float *vfHARQllr_pool, int iSendrN, int iRecvrM, float fNoisePwr, int *viCRCblock, int *viCRCfull_pool)
/*  receivers
*  viCRC          : CRC for each codeword
*  viMPC_pool     : pool of MPCs (Multi-Point Coordination scheduling parameter)
*  MPClen         : length of MPC
*  vfCxOFDMs_pool : list of received OFDMs at RxM antennas, each subcarrier has a receive complex vector
*  vfCxHe_pool    : list of channel matrix for each subcarrier
*  RBnum          : number of used RBs
*  RBfrom         : RB offset
*  RxM            : number of RX antennas
*  LyrN           : number of TX layers
*  SEQmaxN        : max number of sequences
*  vfCxSEQs_pool  : pool of all sequences  (used by channel estimation)
*  vfHARQllr_pool : pool of HARQ llr buffers (used for each decoder)
*  iRecvrM        : number of receivers
*  fNoisePwr      : average noise power for each receive channel
Change History
*  1st version designed by Duan Weiming in 2021-05-16
*/
{
    ret0ERR_LEZ3(CRClen,  MPClen, HARQlen)  ret0ERR_LEZ4(RBnum,RxM,SEQmaxN,iRecvrM)      ret0ERR_LT(CRClen, iSendrN)  int jjj,cnt;   int *viCRCnow, *viMPCs;  float *vfCxOFDMs, *vfCxHeS, *vfHARQllrS;
    int DMRSnum = 2;        int DOFDMn = 12;     int OFDMnum = DOFDMn + DMRSnum;         int SCnum = RBnum*12;   int SCsum = OFDMnum*SCnum;

    GET_GPARAM_INT(gMPC_SoftCombine_ON)

    int LyrN;
    int CWnum;
    MEMCHK(viMPC_pool, iSendrN*MPClen )           MEMCHK(vfHARQllr_pool,  iSendrN*HARQlen)            //MEMCHK(vfCxHe_pool,  14*SCnum*RxM*LyrN*2)
    MEMCHK(vfCxOFDMs_pool, iRecvrM*SCsum*RxM*2)   nzMEMCHK(vfCxSEQs_pool, DMRSnum*SEQmaxN*SCnum*2)    MEMCHK(vfCxHe_pool,  iRecvrM*iHElen)

    int SumLyrN = MPC_sumlayer( 0, viMPC_pool, MPClen, iSendrN);                ERR_LT(iHElen , SCsum*RxM*SumLyrN*2)
    int *piOKBitN;
    int *pMPC;

    _NEW_INIT()
    _NEW2_INT0(viOKBitN_pool, viCRC_pool, iRecvrM*iSendrN)   _NEW_INT0(viOKBitN_pick, iSendrN)                  _NEW2_FLT0(vfMPCllrs_sum, vfMRGllrs_mem , iSendrN*HARQlen)
    _NEW3_INT0(viRVlen, viNetTBS,   viModuType, iSendrN)     _NEW3_INT0(viLyrN,viSEQfrom,  viRvID, iSendrN)     _NEW_INT0(viMPCcrcS, iSendrN)
    _NEW_INT0(viTranstimes, iSendrN)

    IVEC_set(viCRC, CRClen,1);
    IVEC_set(viCRC_pool, iRecvrM * iSendrN, 1);

    //viTranstimes=0,update CRCblock
    _LOOPUP_LT(jjj, 0, iSendrN)
        {
            pMPC = viMPC_pool + jjj * MPClen;
            viTranstimes[jjj] = (pMPC)[13];
            viCRCblock[jjj + 2] = (pMPC)[13];
            if (viTranstimes[jjj] == 0) { viCRCblock[jjj] = 1; }
        }

    _LOOPUP_LT(cnt, 0 , iRecvrM) {
        //viMPCs      = viMPC_pool;
        piOKBitN    = viOKBitN_pool  + cnt*iSendrN;
        viCRCnow    = viCRC_pool     + cnt*CRClen;
        vfCxOFDMs   = vfCxOFDMs_pool + cnt*SCsum*RxM*2;
        vfCxHeS     = vfCxHe_pool    + cnt*iHElen;
        vfHARQllrS  = vfHARQllr_pool + cnt*iSendrN*HARQlen;    //vfHARQllrS  = vfHARQllr_pool + cnt*HARQlen;




        MPCs_fetch( viLyrN, viSEQfrom, viRvID, viRVlen,  viNetTBS, viModuType, MPClen, viMPC_pool,  iSendrN, SEQmaxN, SumLyrN);
        NR_receiverORG( viCRCnow, vfCxOFDMs, vfCxHeS,  viNetTBS, viRvID,  RBnum, RBfrom, RxM,  viLyrN, viModuType, SEQmaxN,  viSEQfrom, vfCxSEQs_pool, vfHARQllrS, HARQlen, iSendrN, fNoisePwr, vfMRGllrs_mem);

        VEC_add(vfMPCllrs_sum,vfMPCllrs_sum, vfMRGllrs_mem,  iSendrN*HARQlen);

        INT_ZERO(piOKBitN, iSendrN);
        _LOOPUP_LT(jjj, 0, iSendrN)
        {
          //previous transmission is decoded correctly
          if (0 == viCRCblock[jjj]) { continue; }
          if( 0 == viCRCnow[jjj] ) {  piOKBitN[jjj] =  viNetTBS[jjj];   }
          *(viCRCfull_pool + (jjj * iRecvrM + cnt)) = viCRCnow[jjj];
        }


        _LOOPUP_LT(jjj,0, iSendrN) {
            viOKBitN_pick[jjj] = MAXOP(viOKBitN_pick[jjj], piOKBitN[jjj]);
            viCRC[jjj]         = MINOP(viCRC[jjj], viCRCnow[jjj]);
            viCRCblock[jjj]         = MINOP(viCRCblock[jjj], viCRCnow[jjj]);
        }
    }


    if( gMPC_SoftCombine_ON ) {
        INT_CP(viCRC, viMPCcrcS, iSendrN );
        _LOOPUP_LT(jjj,0, iSendrN) {
            if( 0 == viCRC[jjj] ) { continue;  }
            NR_llrDEC( &viMPCcrcS[jjj], &viNetTBS[jjj], &viLyrN[jjj],  &viModuType[jjj], vfMPCllrs_sum + jjj*HARQlen,  HARQlen,   RBnum,  1);   // iSendrN=1
            if( 0 == viMPCcrcS[jjj] ) {
                viCRC[jjj] = 0;  viOKBitN_pick[jjj] = viNetTBS[jjj];
                viCRCblock[jjj] = 0;
                //软合并共享当前packet
                *(viCRCfull_pool + jjj * iRecvrM + 0) = 0;
                *(viCRCfull_pool + jjj * iRecvrM + 1) = 0;
            }

        }
    }

    //if( ( viMPCcrcS[0] != viCRC[0] ) || (viMPCcrcS[1] != viCRC[1]) ) {
    //    int iTST = 3;
    //}



    int SumOKBITS = IVEC_sum(viOKBitN_pick, iSendrN);


    _NEW_FREE()



    return SumOKBITS;



}



void   NR_llrDEC(int* viCRC,  int* viNetTBS,int* viLyrN, int* viModuType, float* vfHARQllr_pool, int HARQlen,  int RBnum,  int CWnum)
/*  turbo decoder using  combined llrs
*  viCRC          : CRC for each codeword
*  viNetTBS       : net TBSize for each codeword
*  RBnum          : number of used RBs
*  viModuType     : modulation Type for each codeword
*  vfHARQllr_pool : list of HARQ llr buffers (used for each decoder)
*  HARQlen        :
*  CWnum          : number of codeword
Change History
*  1st version designed by Duan Weiming in 2021-05-22
*/
{


    int DMRSnum = 2;        int DOFDMn = 12;     int OFDMnum = DOFDMn + DMRSnum;      int jjj,cnt,QamBsum;   float *vfHARQ_llr;

    retERR_LEZ3(RBnum,CWnum,HARQlen)               retERR_RNG(CWnum,1,4)
    int SCnum   = RBnum*12;                        int SUMsc  = DOFDMn*SCnum;
    int LyrSUM  = IVEC_sum(viLyrN, CWnum);         int QamSUM = SUMsc*LyrSUM;
    int BITsum  = IVEC_sum(viNetTBS, CWnum) + 24*CWnum + 1000;

    MEMCHK4(viCRC,viNetTBS,viLyrN,viModuType, CWnum)
    MEMCHK(vfHARQllr_pool,  CWnum*HARQlen )

    _NEW_INIT()              _NEW_FLT0(vfRVllrs, QamSUM*16)    _NEW_INT0(vQamN, CWnum)   //_NEW2_INT0(vQamB, vQamN, CWnum)
    _NEW_INT0(viCRCmem,20)   _NEW_INT0(viDECbitS, BITsum)

    //_LOOPUP_LT(jjj, 0,CWnum) { vQamB[jjj] = GetQamBITS(viModuType[jjj]); }   QamBsum  = 0;
    //_LOOPUP_LT(jjj, 0,CWnum) { vQamN[jjj] = viLyrN[jjj]*SUMsc;               QamBsum += viLyrN[jjj]*vQamB[jjj];       }
    _LOOPUP_LT(jjj, 0,CWnum) { vQamN[jjj] = viLyrN[jjj]*SUMsc;  }


    int  iRvID = 0;     int *pDECBiTS = viDECbitS;      // int  BITBias = 0;
    _LOOPUP_LT(cnt, 0, CWnum) { // for each codeword
        vfHARQ_llr  = vfHARQllr_pool + cnt*HARQlen;
        //TurboDecoder_ITF(viCRCmem, vfRVllrs, vQamN[cnt], viNetTBS[cnt], vfHARQ_llr, viModuType[cnt], iRvID, pDECBiTS ,16);
        LTEturbo_decoderORG(viCRCmem, vfRVllrs, viNetTBS[cnt], vQamN[cnt], viModuType[cnt], vfHARQ_llr, iRvID, 16, pDECBiTS,  0,  1, 0); // isRstHarqLLR=1,  isUptHarqLLR=1  pfMRGllrs=0

        pDECBiTS += viNetTBS[cnt] + 24;
        viCRC[cnt] = viCRCmem[0];

    }

    _NEW_FREE()

}







float   NR_ice(float* vfCxHes_pool,int iHElen, int* viMPC_pool, int MPClen, int RBnum , int SubBN, int PMslen, int isPMok, float* vfCxPMs_pool, int RxM, int TxN, float* vfCxSCHorg_pool,float fNoisePwr, int iSendrN, int iRecvrM, float *vfSNRs_meas)
/* ideal channel estimation
*  vfCxHes_pool    : ideal channel matrix for each sub-carrier
*  viMPC_pool      : Pool of MPCs (Multi-Point Coordination scheduling parameter) for each Transimitter
*  SubBN           : number of subbands
*  PMslen           : max length of Precoding Matrice for each Transmitter
*  isPMok          : Precoding Matrix is ready (1) or not (0)
*  vfCxPMs_pool    : precoding matrice(for each subband) for each Transimitter
*  RxM             : number of rx antennas
*  TxN             : number of tx antennas for each Transmitter
*  vfCxSCHorg_pool : original channel matrix for each sub-carrier of each Transmitter
*  iSendrN         : number of Transimitter
Change History
*  1st version designed by Duan Weiming in 2021-05-19
*/
{

    ret0ERR_LEZ6(MPClen,SubBN,PMslen,RxM,TxN,iSendrN)      ret0ERR_LEZ(fNoisePwr)
    int jjj,cnt,rrr,sss, LyrN,CntTX,LyrBias;                 float fSumEs = 0;   float *vfCxHorg, *vfCxPM_SBD, *vfCxHeS, *vfCxSCHorg,*vfSNRdBs;   float fMeanRxSNR;
    float fNoise_10log10 = 10*log10(fNoisePwr);
    int DMRSnum = 2;        int DOFDMn = 12;         int OFDMnum = DOFDMn + DMRSnum;         int SCnum = RBnum*12;    int SCsum = OFDMnum*SCnum;


    _NEW_INIT()   _NEW_INT0(viLyrN_list, iSendrN)    _NEW_FLT0(vfAvgEs, iSendrN)    _NEW_FLT0(vfSNRdB_pool, iRecvrM*iSendrN)
    int SumLyrN = MPC_sumlayer( viLyrN_list, viMPC_pool, MPClen, iSendrN);          ERR_LT(iHElen , SCsum*RxM*SumLyrN*2)



    MEMCHK(vfSNRs_meas, iSendrN)            VEC_set(vfSNRs_meas, iSendrN, -20.0);     //MEMCHK(vfSNRdB_pool, iRecvrM*iSendrN)
    MEMCHK(viMPC_pool, iSendrN*MPClen)                  //MEMCHK(vfCxHes_pool, SCsum*RxM*SumLyrN*2)
    MEMCHK(vfCxPMs_pool, iSendrN*PMslen)    MEMCHK(vfCxSCHorg_pool, iSendrN*SCsum*RxM*TxN*2)    MEMCHK(vfCxHes_pool, iRecvrM*iHElen)

    _NEW_FLT0(vfCxSCHs_R0, SCsum*RxM*SumLyrN*2)
    fMeanRxSNR = 0;
    _LOOPUP_LT(rrr, 0, iRecvrM) {
        vfCxHeS   = vfCxHes_pool + rrr*iHElen;
        vfSNRdBs  = vfSNRdB_pool + rrr*iSendrN;

        LyrBias = 0;    fSumEs = 0;   CntTX = 0;
        _LOOPUP_LT(sss, 0, iSendrN) {
            vfCxSCHorg       = vfCxSCHorg_pool + (rrr*iSendrN + sss)*SCsum*RxM*TxN*2;
            vfCxPM_SBD       = vfCxPMs_pool    + sss*PMslen;
            LyrN             = viLyrN_list[sss];   if( 0 == LyrN ) { continue; }
            vfAvgEs[sss]     = MIMO_precodingH(vfCxSCHs_R0, vfCxSCHorg, vfCxPM_SBD ,  RxM,   TxN,  LyrN ,  SubBN,  RBnum,  OFDMnum);   // ICE and ideal EsN0
            vfSNRdBs[sss]    = 10*log10(vfAvgEs[sss]) - fNoise_10log10;
            vfSNRs_meas[sss] = MAXOP(vfSNRs_meas[sss], vfSNRdBs[sss]);
            fSumEs += vfAvgEs[sss];  CntTX++;
            CxHs_merge(vfCxHeS, vfCxSCHs_R0,  RxM, SumLyrN,  LyrN,  LyrBias, SCsum);   LyrBias += LyrN;
        }
        if(0 == rrr) { fMeanRxSNR = fSumEs/((float)CntTX*fNoisePwr); }
    }
    //float fAvgSNRdB = 10*log10(fSumEs/((float)CntTX*fNoisePwr));
    //VEC_set(vfSNRdB_pool, CntTX,fAvgSNRdB);

    //float fMeanRxSNR = fSumEs/((float)CntTX*fNoisePwr);


    _NEW_FREE()
    return  fMeanRxSNR;

}



void   NRprecoder_TypeII(float* vfCxPMs_pool, int* viMPC_pool, int MPClen, int SubBN, int PMslen, int RBnum, float* vfCxSCHorg_pool, int RxM, int TxN, int TXantC, int TXxplN, int iSendrN)
/* calc precoding matrix type II by using given full H matrix
*  vfCxPMs_pool     : precoding matrice(for each subband) for each Transimitter
*  viMPC_pool       : list of MPCs (Multi-Point Coordination scheduling parameter)
*  MPClen           : length of  MPC
*  PMslen           : length of subband precoding matrice for each transmitter
*  RBnum            : number of RBs
*  vfCxSCHorg_pool  : original channel matrix for each sub-carrier of each Transmitter
*  RxM              : number of rx antennas
*  TxN              : number of tx antennas for each Transmitter
*  TXantC           : columns of tx antenna array
*  TXxplN           : 1: v-pol, 2 : X-pol
*  iSendrN          : number of Transimitters
Change History
*  1st version designed by Duan Weiming in 2021-05-19
*/
{

    retERR_LEZ5(MPClen,SubBN,PMslen,RBnum,iSendrN)   retERR_LEZ4(RxM,TxN,TXantC,TXxplN)   int jjj,cnt, LyrN;  float *vfCxSCHorg, *vfCxPM_SBD;
    int DMRSnum = 2;      int DOFDMn = 12;           int OFDMnum = DOFDMn + DMRSnum;      int SCnum = RBnum*12;   int SCsum = OFDMnum*SCnum;

    MEMCHK(vfCxPMs_pool, iSendrN*PMslen)    MEMCHK(vfCxSCHorg_pool, iSendrN*SCsum*RxM*TxN*2)
    MEMCHK(viMPC_pool, iSendrN*MPClen)

    _NEW_INIT()   _NEW_INT0(viLyrN_list, iSendrN)    _NEW_FLT0(vfAvgEs, iSendrN)
    int SumLyrN = MPC_sumlayer( viLyrN_list, viMPC_pool, MPClen, iSendrN);

    int LyrBias = 0;
    _LOOPUP_LT(cnt, 0, iSendrN) {
        vfCxSCHorg = vfCxSCHorg_pool + cnt*SCsum*RxM*TxN*2;
        vfCxPM_SBD = vfCxPMs_pool    + cnt*PMslen;

        LyrN       = viLyrN_list[cnt];   if( 0 == LyrN ) { continue; }

        MIMO_precoderTypeII(vfCxPM_SBD , vfCxSCHorg,   RxM,   TxN, LyrN ,  SubBN,  RBnum, TXantC, TXxplN, 0);  // 0 : no recording !!!
    }




    //_NEW_FREE()

}

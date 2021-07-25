from ctypes import *
import ctypes
from PY3InterFACE_COMM import newBYTES, newINTS


exec(open('PY3InterFACE_COMM.py').read());
_mybase = ctypes.CDLL('libXpedia.so')   # load specially-designed library
libRQ=CDLL('libRQ.so')
exec(open('PY3ctypes_comm.py').read());

#void   TurboEncoder_ITF(int* viRV_bits, int RVlen, int* viSRCbits, int NetTBS, int ModuType, int RvID);
TurboEncoder_ITF = _mybase.TurboEncoder_ITF;  TurboEncoder_ITF.argtypes = (cINTS,cINT,cINTS,cINT, cINT, cINT);


#  void TurboDecoder_ITF(int *vnCRC,float *vfDemodLLR,int QamNUM, int NetTBS, float *vfCODECparams, int ModuType,int RvID, int *viINFOcrc=0,int MaxIter=12);
TurboDecoder_ITF = _mybase.TurboDecoder_ITF;  TurboDecoder_ITF.argtypes = (cINTS,cFLTS,cINT,cINT,cFLTS, cINT, cINT,cINTS,cINT);


#  void   NXQam_modu(float* vfCxQamLIST, int* viBits, int QamN, int ModuType)
NXQam_modu = _mybase.NXQam_modu;  NXQam_modu.argtypes = ( cFLTS  ,cINTS ,cINT  ,cINT  );

#  void   NXsubframe_genFD(float* vfCxFDofdm_list, int LyN, int DOFDMnum, float* vfCxQams_list, int DMRSnum, float* vfCxDMRSs_list, int RBnum, int RBfrom, int isGuardBand)
NXsubframe_genFD = _mybase.NXsubframe_genFD;  NXsubframe_genFD.argtypes = ( cFLTS  ,cINT  ,cINT  ,cFLTS  ,cINT  ,cFLTS  ,cINT  ,cINT  ,cINT  );


#  void NRofdm_equalizer(float *vfCxQams,  int SCnum, int RXport, int TXport, float *vfCxSCsrc_list,float *vfCxSEQs_org,  float fNoisePwr, float *vfCxHice_list, int ModuType, int isLMMSE)
NRofdm_equalizer = _mybase.NRofdm_equalizer;  NRofdm_equalizer.argtypes = (cFLTS,cINT,cINT,cINT,cFLTS, cFLTS, cFLT, cFLTS, cINT, cINT);

#  void   NRslot_config(int SLOTlen, int isNR);
NRslot_config = _mybase.NRslot_config;  NRslot_config.argtypes = ( cINT  ,cINT  );


#  void   SMP_init(int* viMPCs_list, int MPClen, int NetTBS, int QamNUM, int iModuType, float fEsN0_dB,int BSnum, int RXnum,  int PMslen, int iAMC_ON);
SMP_init = _mybase.SMP_init;  SMP_init.argtypes = ( cINTS ,cINT  ,cINT  ,cINT  ,cINT  ,cFLT  ,cINT  ,cINT  ,cINT  ,cINT  );


#  void   SMP_control(int* viMPCs_list, int MPClen, float *vfCxPM_SBD, int* viINFOs_list, int MaxTBS, int* viCRC_list, float* vfSNR_list, float* vfCxPMS_meas, int PMslen, int SubBN, int TxN, int isPMok ,int LyrN, int BSnum, int iSNRdlyTTI, int iPMIdlyTTI);
SMP_control = _mybase.SMP_control;  SMP_control.argtypes = ( cINTS ,cINT  ,cFLTS ,cINTS ,cINT  ,cINTS ,cFLTS  ,cFLTS  ,cINT  ,cINT  ,cINT  ,cINT  ,cINTS,cINT  ,cINT  ,cINT  ,cINT  ,cINTS,cINTS);


#  void   NR_transmitterS(float* vfCxTxOFDMs_pool, int TxN, int* viMPC_pool, int MPClen, int* viSrcBITS_pool, int MaxTBS, int RBnum, int RBfrom, int SEQmaxN,float* vfCxSEQs_pool, int SubBN, int PMlen, float* vfCxSubBPMs_pool,int isPMok,int iSenderN);
NR_transmitterS = _mybase.NR_transmitterS;  NR_transmitterS.argtypes = ( cFLTS  ,cINT  ,cINTS ,cINT  ,cINTS ,cINT  ,cINT  ,cINT  ,cINT  ,cFLTS  ,cINT  ,cINT  ,cFLTS  ,cINT  ,cINT  );



#  float  NR_ice(float* vfCxHes_pool,int iHElen, int* viMPC_pool, int MPClen, int RBnum , int SubBN, int PMslen, int isPMok, float* vfCxPMs_pool, int RxM, int TxN, float* vfCxSCHorg_pool,float fNoisePwr, int iSendrN, int iRecvrM, float *vfSNRdB_pool);
NR_ice = _mybase.NR_ice;  NR_ice.argtypes = ( cFLTS  ,cINT  ,cINTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cFLTS  ,cINT  ,cINT  ,cFLTS  ,cFLT  ,cINT  ,cINT  ,cFLTS ); NR_ice.restype = cFLT ;



#  void   SCM3Dnet_mimoFD(float* vfCxRxOFDMs_pool, float* vfCxTxOFDMs_pool, char* strCIRfile, int RxM, int TxN, int RBnum, int RBfrom, float fNoisePwr, float* vfCxScHs_pool, int iSenderN, int iRecvrM, int TTIcnt);
SCM3Dnet_mimoFD = _mybase.SCM3Dnet_mimoFD;  SCM3Dnet_mimoFD.argtypes = ( cFLTS  ,cFLTS  ,cSTR  ,cINT  ,cINT  ,cINT  ,cINT  ,cFLT  ,cFLTS  ,cINT  ,cINT  ,cINT  );


#  int   NR_receiverS(int* viCRC_pool, int CRClen, int* viMPC_pool, int MPClen, float* vfCxOFDMs_pool, float* vfCxHe_pool, int iHElen, int RBnum, int RBfrom, int RxM, int SEQmaxN,float* vfCxSEQs_pool, int HARQlen, float* vfHARQllr_pool, int iSendrN, int iRecvrM, float fNoisePwr);
NR_receiverS = _mybase.NR_receiverS;  NR_receiverS.argtypes = ( cINTS ,cINT  ,cINTS ,cINT  ,cFLTS  ,cFLTS  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cFLTS  ,cINT  ,cFLTS  ,cINT  ,cINT  ,cFLT  ,cINTS,cINTS); NR_receiverS.restype = cINT ;



#  void   NRprecoder_TypeII(float* vfCxPMs_pool, int* viMPC_pool, int MPClen, int SubBN, int PMslen, int RBnum, float* vfCxSCHorg_pool, int RxM, int TxN, int TXantC, int TXxplN, int iSendrN)
NRprecoder_TypeII = _mybase.NRprecoder_TypeII;  NRprecoder_TypeII.argtypes = ( cFLTS  ,cINTS ,cINT  ,cINT  ,cINT  ,cINT  ,cFLTS  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  );



#  void   CxVEC_sum(float* vfCxVEC_sum, float* vfCxVEC_src, int Vlen);
CxVEC_sum = _mybase.CxVEC_sum;  CxVEC_sum.argtypes = ( cFLTS  ,cFLTS  ,cINT  );

#      void  GaussianADD(float *vfData, int nSIZE, float fAddedNoiseSigma);
GaussianADD = _mybase.GaussianADD;  GaussianADD.argtypes = ( cFLTS ,cINT  ,cFLT  );


#  void   DMRSgen_ZCseq(float* vfCxSEQs_sc, int SCnum, int LyrN, int LyrBias, int MaxLyrN, int ZCroot, int DMRSnum, float *vfCxSEQs_all)
DMRSgen_ZCseq = _mybase.DMRSgen_ZCseq;  DMRSgen_ZCseq.argtypes = ( cFLTS  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cFLTS );



#  void CxHs_merge(float* vfCxHs_full, float* vfCxHs_part, int RxM, int MaxN, int LyrN, int LyrBias, int MATnum);
CxHs_merge = _mybase.CxHs_merge;  CxHs_merge.argtypes = ( cFLTS  ,cFLTS  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  );

#  void   CxMat_pickCOLS(float* vfCxM_pick, float* vfCxM_src, int iRow, int iCol, int PickN, int iFrom);
CxMat_pickCOLS = _mybase.CxMat_pickCOLS;  CxMat_pickCOLS.argtypes = ( cFLTS  ,cFLTS  ,cINT  ,cINT  ,cINT  ,cINT  );

#  void   Mat_pickCOLS(float* vfMat_pick, float* vfMat_src, int iRow, int iCol, int PickN, int iFrom);
Mat_pickCOLS = _mybase.Mat_pickCOLS;  Mat_pickCOLS.argtypes = ( cFLTS  ,cFLTS  ,cINT  ,cINT  ,cINT  ,cINT  );

# int cfg_GPARAM(char *strGlobalCONF)
cfg_GPARAM = _mybase.cfg_GPARAM;  cfg_GPARAM.argtypes = (cSTR,);   cfg_GPARAM.restype = cINT;

def cfgGPARAM(strGConfig) : cfg_GPARAM(_str(strGConfig));


def getMPCs(viMPCs):  i=0; LyrNUM=viMPCs[i];i+=1;  LyrBIS=viMPCs[i];i+=1;    RvID=viMPCs[i];i+=1;   RVlen=viMPCs[i];i+=1;  NetTBS=viMPCs[i];i+=1;  ModuType=viMPCs[i];i+=1;  iMCS=viMPCs[i];i+=1; return (LyrNUM, LyrBIS,RvID,RVlen,NetTBS,ModuType,iMCS);

def SCM3Dmimo_genHfile(RBnum,TTIsum,SEGnum,TxN,RxM,XplN) :
    TTIseg = int(TTIsum/SEGnum);  TTIgap = 10; isTXomni = 1;  strSavName = newSTR(300);     strSavTAG = 'MMIMO_nlos'; eSCMcaseID = 4;
    if( 1 == XplN)    :  TxAntN = TxN;          RxAntM = RxM;
    elif (2 == XplN)  :  TxAntN = TxN;          RxAntM = int(RxM/2);
    elif (4 == XplN)  :  TxAntN = int(TxN/2);   RxAntM = int(RxM/2);
    else              :  print('#ERROR!!! invalid XplN=' +str(XplN) + '\n');  return strSavName;
    if isTXomni       :  strSavTAG = strSavTAG + 'OmniAnt';
    xx = [];  getTICKs(xx,'creating mimo channels...' );
    SCM3Dmimo_genH(_str(strSavTAG),eSCMcaseID, SEGnum,  RBnum , TTIseg,  TxAntN,  RxAntM, XplN, TTIgap, isTXomni,strSavName)
    getTUCKs(xx);   print('saving H file : ' + str(strSavName.value));
    return strSavName;



################################################################### uplink  Coordinated Multi-Point ##################################################################################################################
# exec(open('PY3ITF_mmimo.py').read()); iSNRdly=2;iPMIdly=2; LyrN=2; iSendrN=2; iRecvrM=1; PUSCH_corelink(10.0,100*50,10,iSNRdly,iPMIdly,LyrN,iSendrN,iRecvrM,1,1,1,1);    # 10RB  isLMMSE=1 TXantC=1,TXantR=1,RXant=1
# exec(open('PY3ITF_mmimo.py').read()); iSNRdly=2;iPMIdly=2; LyrN=2; iSendrN=2; iRecvrM=2; PUSCH_corelink(10.0,100*50,10,iSNRdly,iPMIdly,LyrN,iSendrN,iRecvrM,1,1,1,1);    # 10RB  isLMMSE=1 TXantC=1,TXantR=1,RXant=1


################################################################## downlink Coordinated Multi-Point ##################################################################################################################
# exec(open('PY3ITF_mmimo.py').read()); iSNRdly=2;iPMIdly=2; LyrN=2; iSendrN=2; iRecvrM=1; PUSCH_corelink(10.0,100*50,10,iSNRdly,iPMIdly,LyrN,iSendrN,iRecvrM,1,4,1,1);    # 10RB  isLMMSE=1 TXantC=4,TXantR=1,RXant=1
# exec(open('PY3ITF_mmimo.py').read()); iSNRdly=2;iPMIdly=2; LyrN=2; iSendrN=2; iRecvrM=1; PUSCH_corelink(10.0,100*50,10,iSNRdly,iPMIdly,LyrN,iSendrN,iRecvrM,0,4,1,1);    # 10RB  isLMMSE=0 TXantC=4,TXantR=1,RXant=1
######################################################################################################################################################################################################################
def PUSCH_corelink(fEsN0cfg, TTIcfg, RBnum,  iSNRdlyTTI,iPMIdlyTTI, LyrN, iSendrN, iRecvrM, isLMMSE,TXantC,TXantR,RXant) :
    cfgGPARAM("gMIMO_RandomPrecoding_ON=1   gMPC_SoftCombine_ON=1 ");                      ts_start = getTICK();
    TXxplN   = 2;                RXxplN    = 2;              AMC_on   = 1;   # AMC OFF, fixed ModuType(4,16,64..) & NetTBScfg !!!
    ModuTcfg = 16;               NetTBScfg = 2880-24;        TxN      = TXantC*TXantR*TXxplN;   RxM    = RXant*RXxplN;
    TTIlen   = 30720;            FFTlen    = 2048;           TTInum   = TTIcfg;                 ZCroot = 1;               SEQmaxN = LyrN;
    OFDMnum  = 14;               DMRSnum   = 2;              DOFDMn   = OFDMnum-DMRSnum;        SubBN  = int(RBnum/5);
    SCnum    = RBnum*12;         SUMsc     = DOFDMn*SCnum;   QamMAX   = SUMsc*LyrN*8;           RBfrom = 0;               ModuTmax = 256;            RVmax  = QamMAX*8;
    MaxTBS   = 75376+24;         HARQlen   = 3*(MaxTBS+(24+4)*100)*4;
    PMslen   = SubBN*TxN*LyrN*2; iHElen    = OFDMnum*SCnum*RxM*LyrN*2;

    viCRC       = newINTS(4);                          viCRCs_pool = newINTS(iRecvrM*iSendrN);             viSNRs_meas = newFLTS(iSendrN);                 pTTInum     = newINTS(2);
    MPClen      = 1000;                                viMPCs_pool  = newINTS(iSendrN*MPClen);             vfSEQs_all  = newFLTS(iSendrN*LyrN*SCnum*2);

    #viRVbits    = newINTS(RVmax);                      vfRVllrs    = newFLTS(RVmax);                       vfCxQamS    = newFLTS(QamMAX*2);
    #vfTTItxsig  = newFLTS(TTIlen*2);                   vfSEQs_org  = newFLTS(2*SCnum*LyrN*2);              vfCxQams_RX = newFLTS(QamMAX*2);
    #vfTTIRXsig  = newFLTS(TTIlen*2);                   vfCxQams    = newFLTS(QamMAX*2);
    #vfCxSCv_rx  = newFLTS(OFDMnum*SCnum*RxM*2);        vfPathCoeff = newFLTS(TTInum*OFDMnum*RxM*16*2);     viDECbits   = newINTS(MaxTBS);
    #vfCxSCv_RX  = newFLTS(OFDMnum*SCnum*RxM*2);        vfCxICEs_r0 = newFLTS(OFDMnum*SCnum*RxM*LyrN*2);
    #vfCxSCV_TX  = newFLTS(OFDMnum*SCnum*TxN*2);        vfCxICEs_RX = newFLTS(OFDMnum*SCnum*RxM*LyrN*2);
    #vfCxSCs_lyr = newFLTS(OFDMnum*SCnum*LyrN*2);       vfCxHs_ice  = newFLTS(OFDMnum*SCnum*RxM*TxN*2);
    #viTTI_TBSs  = newINTS(TTInum*iSendrN);              vfTTIsnrDB  = newFLTS(TTInum);                 vfTTI_MCSs  = newFLTS(TTInum*iSendrN);
    viINFOs_pool   = newINTS(iSendrN*MaxTBS);            vfTxOFDMs_pool = newFLTS(iSendrN*OFDMnum*SCnum*TxN*2);
    vfCxPMs_pool   = newFLTS(iSendrN*PMslen);            vfRxOFDMs_pool = newFLTS(iRecvrM*OFDMnum*SCnum*RxM*2);
    vfCxPMS_meas   = newFLTS(iSendrN*PMslen);            vfCxSCHorg_pool= newFLTS(iRecvrM*iSendrN*OFDMnum*SCnum*RxM*TxN*2);
    vfHARQllr_pool = newFLTS(iRecvrM*iSendrN*HARQlen);   vfCxICEs_pool  = newFLTS(iRecvrM*OFDMnum*SCnum*RxM*LyrN*2);
    viTransblock = newINTS(8)
    viCRCblock = newINTS(iSendrN*2);

###################################################RaptorQ related############################################
    # num_packet=2
    # packet_size=2
    # # Maxblocksize = int((math.pow(2, 16)-1)*56403*4);#bytes,max overhead: 4
    # Maxblocksize = 1000;#1GB
    # Senderbuff = newBYTES(Maxblocksize*iSendrN);#bytes,save sender encoded block data
    # Receiverbuff = newBYTES(Maxblocksize*iSendrN*iRecvrM);
    # totalRecvr = newINTS(iSendrN*iRecvrM);#total received symbols numbers
    viNetTBs = newINTS(iSendrN);
    viCRCfull_pool= newINTS(iSendrN*iRecvrM);#本次TTI每个接收机对每个发送信息的接收情况
    # class OTI_pythonOrg(Structure):
    #   _fields_ = [("F",c_size_t),("T",c_size_t),("AL",c_size_t),
    #               ("Z",c_size_t),("N",c_size_t),("Kt",c_size_t),
    #               ("overhead",c_float),("srcsymNum",c_uint32),
    #               ("transNum",c_uint32),("Endflag",c_bool),]
    # OTI_python=(OTI_pythonOrg*iSendrN)()
    # #RQ init
    # for i in range(iSendrN):
    #     OTI_python[i].Endflag=True;
    #     OTI_python[i].overhead=3;#开销设置为3
    # RQ_encodeControl = libRQ.RQ_encodeControl;  RQ_encodeControl.argtypes = ( cUINT8, cINTS,cINTS, ctypes.POINTER(OTI_pythonOrg), ctypes.c_ulong  ,ctypes.c_size_t  ,ctypes.c_size_t  ,cINT  ,cINT  );
##############################################################################################################

    vfTTI_SNRs  = newFLTS(TTInum*iSendrN);                  vfTTIsnrSUM = newFLTS(TTInum);           vfTTIMbps = newFLTS(TTInum);
    #CxSEQ_ZCseq(vfSEQs_org[SCnum*0:SCnum*2],  SCnum, 1,0); # ZCroot = 1; ZCoffset = 0
    #CxSEQ_ZCseq(vfSEQs_org[SCnum*2:SCnum*4],  SCnum, 1,0);
    sumTTI = 0; sumDEC = 0;  errDEC = 0;  fSumTP = 0;  fAvgTP_se = 0;   fEsN0meas = fAvgEsN0  = fEsN0cfg;    #fNoisePwr   = math.pow(10,-0.1*fEsN0cfg);
    #RvID   = 0; iNACK  = 0;  cntBA  = 0;  bler   = 0;  SampeN    = 0;   minNTB = maxNTB = NetTBScfg; minQmT = maxQmT = ModuTcfg;
    RandSeed_INIT(13457);     NRslot_config(OFDMnum,1);    #SLOTlen=OFDMnum, isNR = 1, NR numerology!!!
    rmvFiles('tmpREC*.*');    rmvFiles('GDBtmp*.dat');
    #strCIRfile = _str('MMIMOlineOmniAnt_20SEGx600TTI_RXxpl2xTXxpl2xRXantM1xTXantN32_MaxPATH30.bin');  TXantC = 8; TXxplN = 2;
    #strCIRfile = _str('MMIMO_nlosOmniAnt_20SEGx1000TTI_RXxpl2xTXxpl2xRXantM2xTXantN32_MaxPATH30.bin');  TXantC = 8; TXxplN = 2;
    TTIsum = TTIcfg+2*iSendrN*iRecvrM*1000;   SEGnum = int(TTIsum/1000)+1;  TTIsum = 1000*SEGnum;   print(TTIsum,SEGnum)
    strCIRfile = SCM3Dmimo_genHfile(RBnum,TTIsum, SEGnum,TxN,RxM,TXxplN*RXxplN);                #TXantC = 8;


    fAvgSCpwr  = MIMOcirs_brief(pTTInum,  RxM ,  TxN , strCIRfile,_str('TTIrxPwr'));
    fNoisePwr = math.pow(10, -0.1*fEsN0cfg)*fAvgSCpwr
    fNoiseSigma = math.sqrt(0.5*fNoisePwr)
    print(fNoisePwr, fNoiseSigma)


    SMP_init(viMPCs_pool, MPClen, NetTBScfg, SUMsc, ModuTcfg, fEsN0meas, iSendrN, RxM,  PMslen, AMC_on);    viSNRs_meas.fill(fEsN0meas)

    # print(viMPCs_pool[11])
    for cntTTI in range(TTInum) :
        if GERROR_chk(10) : break;
        isPMok = 1;
        #小于PMI发送延时
        if (cntTTI <= iPMIdlyTTI) : isPMok = 0;
        # *******************************************************************************************************************************************************************************
        # ******************************** Multi. Point Control *************************************************************************************************************************
        CWnum = SMP_control(viMPCs_pool, MPClen, vfCxPMs_pool, viINFOs_pool,  MaxTBS,  viCRCs_pool,  viSNRs_meas,  vfCxPMS_meas,
                            PMslen, SubBN, TxN, isPMok, viTransblock, LyrN,  iSendrN,  iSNRdlyTTI,  iPMIdlyTTI, viCRCblock, viNetTBs)
        # print(viNetTBs)
        # libRQ.RQ_encodeControl(Senderbuff, viINFOs_pool, viNetTBs, byref(OTI_python[0]),
        #                          Maxblocksize, num_packet, packet_size, MaxTBS, iSendrN)

                                 #*******************************************************************************************************************************************************************************
        #vfCxSCv_RX.fill(0.0);    #reset receive channels
        #vfSEQs_all.fill(0.0);    #reset DMRSs
        #smpBS = 0;  smpEs = 0;
        #for cntBS in range(iSendrN) :
        #    (LyrN0, LyrBias,RvID,RVlen,NetTBS,ModuType,iMCS) = getMPCs(viMPCs_pool[cntBS*MPClen:(cntBS+1)*MPClen]); QamNUM=LyrN0*SUMsc;  vfTTI_SNRs[cntTTI*iSendrN+cntBS]=0.001;
        #    if (0 == LyrN0) : continue;
        #    vfCxPM_SBD = vfCxPMs_pool[cntBS*PMslen:(cntBS+1)*PMslen];
        #    vfCxPMmeas = vfCxPMS_meas[cntBS*PMslen:(cntBS+1)*PMslen];
        #    viINFObits = viINFOs_pool[cntBS*MaxTBS:(cntBS+1)*MaxTBS];
        #
        #    vfTTI_MCSs[cntTTI*iSendrN+cntBS] = float(iMCS);
        #    viTTI_TBSs[cntTTI*iSendrN+cntBS] = NetTBS;
        #    minNTB = min(minNTB,NetTBS);   maxNTB  = max(maxNTB,NetTBS);    minQmT = min(minQmT,ModuType);   maxQmT = max(maxQmT,ModuType);
        #    # ****************************************************************************************************************************************************
        #    # ******************************** transmission & randio channel filtering for current base station **************************************************
        #    # ****************************************************************************************************************************************************
        #    #  DMRSgen_ZCseq(vfSEQs_org,  SCnum,  LyrN0,  LyrBias, LyrN,  ZCroot,  DMRSnum, vfSEQs_all);         # ZCroot
        #    #  TurboEncoder_ITF(viRVbits,  RVlen,viINFObits,  NetTBS,  ModuType,   RvID );                        #LTEturbo_encoder(viRVbits, RVlen, viINFObits, NetTBS ,ModuType, RvID);
        #    #  NXQam_modu(vfCxQamS, viRVbits,  QamNUM,  ModuType);                                                #Qam_Modu_REL(vfCxQamS, viRVbits,  QamNUM,  ModuType);
        #    #  NXsubframe_genFD(vfCxSCs_lyr, LyrN0, DOFDMn, vfCxQamS, DMRSnum, vfSEQs_org,   RBnum,  RBfrom, 0);  #NXsubframe_mappingFD(vfCxSCs_lyr, LyrN0, DOFDMn, vfCxQamS, DMRSnum, vfSEQs_org,   RBnum,  RBfrom, 0);
        #    #  MIMO_precoder(vfCxSCV_TX, vfCxPM_SBD,  vfCxSCs_lyr,  TxN,  LyrN0 ,  SubBN,  RBnum,  OFDMnum, isPMok);     #isPMok=1
        #
        #    #NR_transmitterORG(vfCxSCV_TX, viINFObits,  NetTBS, RvID,  RBnum, RBfrom, TxN, LyrN0, ModuType, SEQmaxN, LyrBias, vfSEQs_all, 0,  SubBN, vfCxPM_SBD, isPMok);
        #    viMPCs = viMPCs_pool[cntBS*MPClen:(cntBS+1)*MPClen];
        #    NR_transmitterS(vfCxSCV_TX,  TxN, viMPCs,  MPClen, viINFObits,  MaxTBS,  RBnum, RBfrom,  SEQmaxN,vfSEQs_all,  SubBN,  PMslen, vfCxPM_SBD, isPMok,1); # iSenderN=1
        #    MIMO_channelFD(vfCxSCv_rx, vfCxSCV_TX, strCIRfile, OFDMnum,   RBnum,   RxM, TxN, cntTTI+cntBS*1000,  RBfrom,  0, vfCxHs_ice);   #  fNoisePwr=0, add noise after combination!!!
        #    CxVEC_sum(vfCxSCv_RX, vfCxSCv_rx, OFDMnum*SCnum*RxM);  #vfCxSCv_RX = vfCxSCv_RX + vfCxSCv_rx;
        #    # ****************************************************************************************************************************************************
        #    # ******************************** ideal channel estimation and ideal precoding measurement for current base station *********************************
        #    # ****************************************************************************************************************************************************
        #    fAvgEs = MIMO_precodingH(vfCxICEs_r0, vfCxHs_ice, vfCxPM_SBD ,  RxM,   TxN,  LyrN0 ,  SubBN,  RBnum,  OFDMnum);   # ICE and ideal EsN0
        #    CxHs_merge(vfCxICEs_RX, vfCxICEs_r0,  RxM, LyrN,  LyrN0,  LyrBias, OFDMnum*SCnum);
        #    vfTTI_SNRs[cntTTI*iSendrN+cntBS] = fAvgEs/fNoisePwr;     smpBS += 1;  smpEs += fAvgEs;
        #    MIMO_precoderTypeII(vfCxPMmeas , vfCxHs_ice,   RxM,   TxN, LyrN0 ,  SubBN,  RBnum, TXantC, TXxplN, (0 == cntBS)); # only record PMvec when cntBS is 0
        #    # ****************************************************************************************************************************************************
        #GaussianADD(vfCxSCv_RX, OFDMnum*SCnum*RxM*2, fNoiseSigma);
        #vfTTIsnrSUM[cntTTI] =  smpEs/(smpBS*fNoisePwr);     viSNRs_meas.fill(10*np.log10(vfTTIsnrSUM[cntTTI]));
        NR_transmitterS(vfTxOFDMs_pool,  TxN, viMPCs_pool,  MPClen, viINFOs_pool,  MaxTBS,  RBnum, RBfrom,  SEQmaxN,vfSEQs_all,  SubBN,  PMslen, vfCxPMs_pool, isPMok,iSendrN); # iSenderN=1
        SCM3Dnet_mimoFD(vfRxOFDMs_pool, vfTxOFDMs_pool, strCIRfile,  RxM,  TxN,  RBnum,  RBfrom,  fNoisePwr, vfCxSCHorg_pool,  iSendrN,  iRecvrM,  cntTTI);
        vfTTIsnrSUM[cntTTI] = NR_ice(vfCxICEs_pool, iHElen, viMPCs_pool,  MPClen,  RBnum ,  SubBN,  PMslen,  isPMok, vfCxPMs_pool,  RxM,  TxN,  vfCxSCHorg_pool, fNoisePwr,  iSendrN, iRecvrM, viSNRs_meas); #ideal channe estimation
        NRprecoder_TypeII(vfCxPMS_meas,  viMPCs_pool,  MPClen,  SubBN,  PMslen, RBnum, vfCxSCHorg_pool, RxM, TxN, TXantC, TXxplN, iSendrN);

        #iOK_BITS = NR_receiver(viCRC, viMPCs_pool, MPClen, vfCxSCv_RX,  vfCxICEs_RX,  RBnum,  RBfrom,  RxM,  LyrN, LyrN, vfSEQs_all,  HARQlen, vfHARQllr_pool ,  CWnum,  fNoisePwr);
        #iOK_BITS = NR_receiver(viCRCs_pool, viMPCs_pool, MPClen, vfRxOFDMs_pool,  vfCxICEs_pool,  RBnum,  RBfrom,  RxM,  LyrN, LyrN, vfSEQs_all,  HARQlen, vfHARQllr_pool ,  CWnum,  fNoisePwr);
        #NR_receiverS(int* viCRC_pool, int CRClen, int* viMPC_pool, int MPClen, float* vfCxOFDMs_pool, float* vfCxHe_pool, int iHElen, int RBnum, int RBfrom, int RxM, int SEQmaxN,float* vfCxSEQs_pool, int HARQlen, float* vfHARQllr_pool, int iSendrN, int iRecvrM, float fNoisePwr);
        iOK_BITS=NR_receiverS(viCRCs_pool, iSendrN, viMPCs_pool, MPClen, vfRxOFDMs_pool,  vfCxICEs_pool, iHElen ,  RBnum,  RBfrom,  RxM,  SEQmaxN, vfSEQs_all,  HARQlen, vfHARQllr_pool,  iSendrN, iRecvrM,  fNoisePwr, viCRCblock,viCRCfull_pool);


        # libRQ.RQ_decodePush(byref(viINFOs_pool), byref(Receiverbuff), byref(viCRCfull_pool), byref(OTI_python),
        #                       byref(totalRecvr), c_int(iRecvrM), c_int(iSendrN), c_int(MaxTBS), c_int(Maxblocksize))

        # iOK_BITS = libRQ.RQ_decodeControl(byref(Receiverbuff), byref(OTI_python),byref(totalRecvr), c_int(iRecvrM), c_int(iSendrN), c_int(Maxblocksize));

        fTPMbps =  float(iOK_BITS)*1.0e-3;      vfTTIMbps[cntTTI] =  fTPMbps;  fSumTP  += fTPMbps;    vfTTI_SNRs[cntTTI*iSendrN:(cntTTI+1)*iSendrN] = viSNRs_meas;
        # print('cntTTI:{:d},,,transtime:{:d},,,iOK_BITS:{:d},,,,transTime1:{:d},,,,transTime2:{:d},,,,INACK1:{:d},,,,INACK1:{:d},,,,viCRCblock1:{:d},,,,viCRCblock2:{:d}'.format(
        #     cntTTI, cntTTI%4, iOK_BITS, viCRCblock[2], viCRCblock[3], viCRCs_pool[0], viCRCs_pool[1], viCRCblock[0], viCRCblock[1]))
        for cntBS in range(CWnum)  :
            iNACK = viCRCs_pool[cntBS];   errDEC += iNACK;  sumDEC += 1;    # viCRCs_pool[cntBS] = iNACK;
            #if ( 0 == iNACK ) :     fSumTP += float(NetTBS)*1.0e-3;
        # ********************************************************************************************************************************************************
        # ******************************** MIMO equalizer ********************************************************************************************************
        #NRofdm_equalizer(vfCxQams_RX, SCnum, RxM, LyrN, vfCxSCv_RX, vfSEQs_all, fNoisePwr ,vfCxICEs_RX, ModuType, isLMMSE); # (ModuType = 0) ==> equalization wo. demod
        # ********************************************************************************************************************************************************
        #for cntBS in range(iSendrN) :
        #    (LyrN0, LyrBias,RvID,RVlen,NetTBS,ModuType,iMCS) = getMPCs(viMPCs_pool[cntBS*MPClen:(cntBS+1)*MPClen]);  QamNUM=LyrN0*SUMsc;  QamB=GetQamBITS(ModuType);
        #    if (0 == LyrN0) : continue;
        #    # ****************************************************************************************************************************************************
        #    # ******************************** Demodulation and decoder for layers of current base staion  *******************************************************
        #    # ****************************************************************************************************************************************************
        #    if  isLMMSE :  CxMat_pickCOLS(vfCxQams, vfCxQams_RX, SUMsc, LyrN,  LyrN0, LyrBias);      CxVEC_qamDemod(vfRVllrs, vfCxQams,  QamNUM,  ModuType,  0.5*fNoisePwr);
        #    else        :  Mat_pickCOLS(vfRVllrs, vfCxQams_RX, SUMsc, LyrN*QamB, LyrN0*QamB, LyrBias*QamB);   #pick llrs for current link
        #    vfHARQ_llr  = vfHARQllr_pool[cntBS*HARQlen:(cntBS+1)*HARQlen];
        #    TurboDecoder_ITF(viCRC, vfRVllrs, QamNUM, NetTBS, vfHARQ_llr, ModuType, RvID,viDECbits,16); # TurboDecoder_ITF(viCRC, vfRVllrs, QamNUM, NetTBS, vfHARQ_llr, ModuType, RvID,viDECbits,16); # MaxIter=16
        #    # ****************************************************************************************************************************************************
        #    iNACK = viCRC[0];  viCRCs_pool[cntBS] = iNACK;  errDEC += iNACK;  sumDEC += 1;
        #    if ( 0 == iNACK ) : fSumTP += float(NetTBS)*1.0e-3;
        sumTTI += 1;
        if(( 0 == cntTTI%200 ) and (0 < cntTTI) )  or (cntTTI == (TTInum-1)):    #if(( 0 == cntTTI%500 ) and (0 < cntTTI) ):
            fAvgEsN0 = 10*np.log10(np.mean(vfTTIsnrSUM[0:sumTTI]));   #print(vfTTI_SNRs[cntTTI*iSendrN:(cntTTI+1)*iSendrN],vfTTIsnrSUM[cntTTI] )
            strSay = '....sumDEC={:d}  errDEC={:d}   fAvgEsN0={:.2f}dB  AvgTPmbps={:.2f}  avgSpecEff={:.2f}  '.format(sumDEC,errDEC,fAvgEsN0, fSumTP/float(sumTTI),fSumTP/float(sumTTI*RBnum*12*12*0.001))
            strSay += '..TTIcnt={:d} TTIsnr={:.2f}dB '.format(cntTTI, 10*np.log10(vfTTIsnrSUM[cntTTI])) + str(vfTTI_SNRs[cntTTI*iSendrN:(cntTTI+1)*iSendrN]); print(strSay);
    ts_secs  = getTUCK(ts_start);
    fAvgEsN0 = 10*np.log10(np.mean(vfTTIsnrSUM[0:sumTTI]));
    GDB_svMat(_str('EsN0_list'), vfTTI_SNRs, sumTTI, iSendrN);
    # GDB_svMat(_str('MCS_list'),  vfTTI_MCSs, sumTTI, iSendrN);   #GDB_svIMat(_str('TBS_list'),  viTTI_TBSs, sumTTI, iSendrN);viCRCs_pool
    GDB_svMat(_str('TPmbps_list'),  vfTTIMbps, 1, sumTTI)

    if 0 < sumTTI : bler = float(errDEC)/float(sumDEC);  avgTP = fSumTP/float(sumTTI); fAvgTP_se = avgTP/float(RBnum*12*12*0.001); # avg. SE w.r.t data SCs occupied!!!
    print('....BLER={:.5f}@EsN0cfg={:.2f}dB  @EsN0meas={:.2f}dB...avgSE={:f}..TPmbps={:f}...{:d}@{:d}TTIs...{:.2f}seconds'.format(bler,fEsN0cfg,fAvgEsN0,fAvgTP_se,avgTP,errDEC,sumTTI,ts_secs))
    gMEM_free(1); #miQ_close(1);
    ##
    print('iNACK == 0... 0:{:d}...1:{:d}... 2:{:d}...3:{:d}...iNACK == 1... 0:{:d}...1:{:d}... 2:{:d}...3:{:d}'.format(
        viTransblock[0], viTransblock[1], viTransblock[2], viTransblock[3], viTransblock[4], viTransblock[5], viTransblock[6], viTransblock[7]))
    # exec(open('Plot_Harq.py').read())
    return (bler,fAvgEsN0,errDEC,sumTTI,fAvgTP_se);






# exec(open('PY3ITF_mmimo.py').read());  crcBITS=6120+24; PUSCH_corelinkX(5.0,crcBITS-24,10,64,100*50,30.0,3,1);    # 10RB+64QAM
def PUSCH_corelinkX(fEsN0cfg, NetTBScfg, RBnum,  ModuType, TTIcfg, fDoppler, FadingT,runbar_on) :
    ts_start = getTICK();  iBatchN = 500;            TTInum = iBatchN*int(TTIcfg/iBatchN);           TTIlen = 30720;            FFTlen = 2048;
    TxN    = 64;             RxM   = 2;              LyrN   = 1;     OFDMnum  = 14;   DMRSnum = 2;   DOFDMn = OFDMnum-DMRSnum;
    SCnum  = RBnum*12;      QamNUM = SCnum*LyrN*12;  RBfrom = 0;     ModuTmax = 256;  RBfrom  = 0;   MaxTBS = 75376+24;         RVmax  = QamNUM*8;
    iFadingON = FadingT;    SubBN  = int(RBnum/5);
    if( 0 == fDoppler ): iFadingON = 0;

    viCRC       = newINTS(4);                          viINFObits  = newINTS(MaxTBS);
    viRVbits    = newINTS(RVmax);                      vfRVllrs    = newFLTS(RVmax);                       viDECbits   = newINTS(MaxTBS);
    vfTTItxsig  = newFLTS(TTIlen*2);                   vfSEQs_org  = newFLTS(2*SCnum*2);                   vfCxQamS    = newFLTS(QamNUM*2);
    vfTTIRXsig  = newFLTS(TTIlen*2);                   vfSEQs_rx   = newFLTS(2*SCnum*2);                   vfCxQams_rx = newFLTS(QamNUM*2);
    vfHARQ_llr  = newFLTS(3*(MaxTBS+(24+4)*100));      viAMCs      = newINTS(100)                           #viAMCs      = newiSTRUC(_str('stAMC'));  vfCParams   = newSTRUC(_str('stTurboCParam'));
    vfPathCoeff = newFLTS(TTInum*OFDMnum*RxM*16*2);    vfTTIesn0   = newFLTS(TTInum);                      vfTTImcs    = newFLTS(TTInum);
    vfCxSCv_rx  = newFLTS(OFDMnum*SCnum*RxM*2);        vfCxICEs_RX = newFLTS(OFDMnum*SCnum*RxM*LyrN*2);    vfCxPM_SBD  = newFLTS(SubBN*TxN*LyrN*2);
    vfCxSCV_TX  = newFLTS(OFDMnum*SCnum*TxN*2);        vfCxHs_ice  = newFLTS(OFDMnum*SCnum*RxM*TxN*2);     viTTIs_tbs  = newINTS(TTInum);
    vfCxSCs_lyr = newFLTS(OFDMnum*SCnum*LyrN*2);       pTTInum     = newINTS(2);                           vfTTIsnrDB  = newFLTS(TTInum);
    CxSEQ_ZCseq(vfSEQs_org[SCnum*0:SCnum*2],  SCnum, 1,0); # ZCroot = 1; ZCoffset = 0
    CxSEQ_ZCseq(vfSEQs_org[SCnum*2:SCnum*4],  SCnum, 1,0);

    sumTTI = 0; cntERR = 0;  fSumTP = 0;  fEsN0meas = fEsN0cfg;           SampeN = 0;    fAvgEsN0 = fEsN0cfg;    #fNoisePwr   = math.pow(10,-0.1*fEsN0cfg);
    AMC_on = 1; RvID   = 0;   iNACK = 0;     minNTB = maxNTB = NetTBScfg; minQmT = maxQmT = ModuType;            cntBA = 0;
    RandSeed_INIT(13457);
    NRslot_config(OFDMnum,1);    #SLOTlen=OFDMnum, isNR = 1, NR numerology!!!
    strCIRfile = 'MMIMOlineOmniAnt_20SEGx600TTI_RXxpl2xTXxpl2xRXantM1xTXantN32_MaxPATH30.bin';  TXantC = 8; TXxplN = 2;
    #strCIRfile = 'MMIMO_losOmniAnt_20SEGx600TTI_RXxpl2xTXxpl2xRXantM1xTXantN32_MaxPATH30.bin';  TXantC = 8; TXxplN = 2;
    #fAvgSCpwr = MIMOcirs_brief(pTTInum,  RxM ,  TxN , _str(strCIRfile));
    fAvgSCpwr = 5.4; print(fAvgSCpwr)
    fNoisePwr = math.pow(10,-0.1*fEsN0cfg)*fAvgSCpwr;
    AMC_init(viAMCs, NetTBScfg, QamNUM, ModuType, fEsN0meas, RxM, AMC_on);

    for cntTTI in range(TTInum) :
        if GERROR_chk(10) : break;
        AMC_control(viAMCs,viINFObits,MaxTBS, iNACK ,fEsN0meas,0,1);      viTTIs_tbs[cntTTI] = viAMCs[2];
        RvID   = viAMCs[0];            RVlen = viAMCs[1];             NetTBS = viAMCs[2];              ModuType = viAMCs[3];            vfTTImcs[cntTTI] = float(viAMCs[4]);
        minNTB = min(minNTB,NetTBS);  maxNTB = max(maxNTB,NetTBS);    minQmT = min(minQmT,ModuType);   maxQmT = max(maxQmT,ModuType);


        TurboEncoder_ITF(viRVbits,  RVlen,viINFObits,  NetTBS,  ModuType,   RvID ); # TurboEncoder_ITF(viRVbits,  RVlen,viINFObits,  NetTBS, vfCParams,  ModuType,  1,  RvID ); # CWnum = 1

        Qam_Modu_REL(vfCxQamS, viRVbits,  QamNUM,  ModuType);

        NXsubframe_mappingFD(vfCxSCs_lyr, LyrN, DOFDMn, vfCxQamS, DMRSnum, vfSEQs_org,   RBnum,  RBfrom, 0);
        MIMO_precoder(vfCxSCV_TX, vfCxPM_SBD,  vfCxSCs_lyr,  TxN,  LyrN ,  SubBN,  RBnum,  OFDMnum, cntTTI);

        MIMO_channelFD(vfCxSCv_rx, vfCxSCV_TX, _str(strCIRfile), OFDMnum,   RBnum,   RxM, TxN, cntTTI,  RBfrom,  fNoisePwr, vfCxHs_ice);

        fAvgEs = MIMO_precodingH(vfCxICEs_RX, vfCxHs_ice, vfCxPM_SBD ,  RxM,   TxN,  LyrN ,  SubBN,  RBnum,  OFDMnum); # ICE and ideal EsN0
        vfTTIesn0[cntTTI]  = fAvgEs/fNoisePwr;
        vfTTIsnrDB[cntTTI] = 10*np.log10(vfTTIesn0[cntTTI]);
        MIMO_precoderTypeII(vfCxPM_SBD , vfCxHs_ice,   RxM,   TxN, LyrN ,  SubBN,  RBnum, TXantC, TXxplN);
        fEsN0meas = vfTTIsnrDB[cntTTI]; #vfTTIesn0[cntTTI];

        NRofdm_equalizer(vfRVllrs,   SCnum, RxM, 1,  vfCxSCv_rx, vfSEQs_org, fNoisePwr ,vfCxICEs_RX, ModuType, 1);
        #CxVEC_qamDemod(vfRVllrs,vfCxQams_rx,   QamNUM,  ModuType,0.5*fNoisePwr);

        TurboDecoder_ITF(viCRC, vfRVllrs, QamNUM, NetTBS, vfHARQ_llr, ModuType, RvID,viDECbits,16); # MaxIter=16


        iNACK = viCRC[0]; cntERR += iNACK;  sumTTI += 1;
        if ( 0 == iNACK ) : fSumTP += float(NetTBS)*1.0e-3;
        if(( 0 == cntTTI%500 ) and (0 < cntTTI) ):  print('....sumTTI={:d}  errTTI={:d}  AvgTPmbps={:f}  avgSpecEff={:f}'.format(sumTTI,cntERR,fSumTP/float(sumTTI),fSumTP/float(sumTTI*RBnum*12*12*0.001)));
    if  iFadingON :  fAvgEsN0 = 10*np.log10(np.mean(vfTTIesn0[0:sumTTI]));
    GDB_svMat(_str('EsN0_list'), vfTTIsnrDB, 1, TTInum);
    GDB_svIMat(_str('TBS_list'), viTTIs_tbs, 1, TTInum);
    if 0 < sumTTI : bler = float(cntERR)/float(sumTTI); fSpecEFF = (1.0-bler)*float(NetTBS)/float(QamNUM); avgTP = fSumTP/float(sumTTI); fAvgTP_se = avgTP/float(RBnum*12*12*0.001); # avg. SE w.r.t data SCs occupied!!!
    ts_secs  = getTUCK(ts_start);
    if runbar_on : print('....BLER={:.5f}@EsN0={:.2f}dB:{:.2f}dB...NetTBS={:d}~{:d}@QamNUM={:d}..ModuType={:d}~{:d}...avgSE={:f}..TPmbps={:f}...{:d}@{:d}TTIs...{:.2f}seconds'.format(bler,fEsN0cfg,fAvgEsN0,minNTB,maxNTB,QamNUM,minQmT,maxQmT,fAvgTP_se,avgTP,cntERR,sumTTI,ts_secs))
    gMEM_free(1); #miQ_close(1);
    return (bler,fAvgEsN0,cntERR,sumTTI,fAvgTP_se);


#  int gSTRUC_len(char *strSTRUCtype)
gSTRUC_len = _mybase.gSTRUC_len;  gSTRUC_len.argtypes = ( cSTR , ); gSTRUC_len.restype = cINT ; 

#      int GERROR_chk(int iERRnum);
GERROR_chk = _mybase.GERROR_chk;  GERROR_chk.argtypes = ( cINT , ); GERROR_chk.restype = cINT ; 



#  void NDarray_read(float *vfNDarray,int ilen)
NDarray_read = _mybase.NDarray_read;  NDarray_read.argtypes = ( cFLTS, cINT ); 



# int GetQamBITS(int ModuTYPE)
GetQamBITS = _mybase.GetQamBITS;
GetQamBITS.argtypes = (cINT,);     

#  void Qam_Modu_REL(float *vfCxQamLIST, int *vnBits, int QamNum, int ModuType);
Qam_Modu_REL = _mybase.Qam_Modu_REL;
Qam_Modu_REL.argtypes = (cFLTS,cINTS, cINT,cINT); 

#  void Qam_DeModu_REL(float *vfllrLIST,float *vfCxQamLIST,  int QamNum, int ModuType);
Qam_DeModu_REL = _mybase.Qam_DeModu_REL;
Qam_DeModu_REL.argtypes = (cFLTS,cFLTS, cINT,cINT); 

#  void CxVEC_qamDemod(float *vfllrLIST,float *vfCxQamLIST,  int QamNum, int ModuType, float fNoisePwr=1.0);
CxVEC_qamDemod = _mybase.CxVEC_qamDemod;
CxVEC_qamDemod.argtypes = (cFLTS,cFLTS, cINT,cINT,cFLT); 


#  int CompareBits(int *vnSrc, int *vnDst, int nSize);
CompareBits = _mybase.CompareBits;
CompareBits.argtypes = (cINTS,cINTS,cINT);  CompareBits.restype = cINT;


#      void  RandSeed_INIT(int seed);
RandSeed_INIT = _mybase.RandSeed_INIT;  RandSeed_INIT.argtypes = ( cINT , ); 

#      void  GaussianVEC_REL(float *vfSignal,float fScaling,int nLEN, int isADDED, int isABS); 
GaussianVEC_REL = _mybase.GaussianVEC_REL;  GaussianVEC_REL.argtypes = ( cFLTS ,cFLT  ,cINT  ,cINT  ,cINT  ); 

#      void  GaussianVEC(float *vfOUT, int nSIZE, float fSCALING);
GaussianVEC = _mybase.GaussianVEC;  GaussianVEC.argtypes = ( cFLTS ,cINT  ,cFLT  ); 

#      void  GaussianADD(float *vfData, int nSIZE, float fAddedNoiseSigma);
GaussianADD = _mybase.GaussianADD;  GaussianADD.argtypes = ( cFLTS ,cINT  ,cFLT  ); 

#      void  GaussianVEC_frannor(float *vfSignal,int nLEN, float fSigma, int isADDED, int isABS);  
GaussianVEC_frannor = _mybase.GaussianVEC_frannor;  GaussianVEC_frannor.argtypes = ( cFLTS ,cINT  ,cFLT  ,cINT  ,cINT  ); 

#      void  GaussianAbsVEC(float *vfOUT, int nSIZE, float fSCALING);
GaussianAbsVEC = _mybase.GaussianAbsVEC;  GaussianAbsVEC.argtypes = ( cFLTS ,cINT  ,cFLT  ); 

#      void  UniformVEC(float *vfOUT, int nSIZE, float fSCALING, float fFrom=0.0);
UniformVEC = _mybase.UniformVEC;  UniformVEC.argtypes = ( cFLTS ,cINT  ,cFLT  ,cFLT  ); 

#      void  UniformINTS(int *vnOUT, int nSIZE , int nFrom, int nTO);  
UniformINTS = _mybase.UniformINTS;  UniformINTS.argtypes = ( cINTS ,cINT  ,cINT  ,cINT  ); 

#      void  VEC_rand(float *vfnoise, int VEClen, float fFrom, float fTo);
VEC_rand = _mybase.VEC_rand;  VEC_rand.argtypes = ( cFLTS ,cINT  ,cFLT  ,cFLT  ); 

#      void  VEC_randn(float *vfnoise, int VEClen, float fMean, float fSigma, int isABS);
VEC_randn = _mybase.VEC_randn;  VEC_randn.argtypes = ( cFLTS ,cINT  ,cFLT  ,cFLT  ,cINT  ); 

#      void  VEC_noise(float *vfGaussian, int VEClen,  float fSigma);
VEC_noise = _mybase.VEC_noise;  VEC_noise.argtypes = ( cFLTS ,cINT  ,cFLT  ); 

#      void  zigset(unsigned int _rng_jsrseed);
zigset = _mybase.zigset;  zigset.argtypes = ( cINT , ); 

#      void  RandomBits(int *vnOUT,  int nSIZE);
RandomBits = _mybase.RandomBits;  RandomBits.argtypes = ( cINTS ,cINT  ); 

#      void  LTEsubframe_assemble(float *vfCxTTIsig, int TTIlen, float *vfCxSCs_list, float *vfCxSEQs_list, int SEQnum, int RBnum, int RBfrom, int FFTlen, int isDL=0);
LTEsubframe_assemble = _mybase.LTEsubframe_assemble;  LTEsubframe_assemble.argtypes = ( cFLTS ,cINT  ,cFLTS ,cFLTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ); 

#      void  LTEsubframe_deAssemble(float *vfCxSCs_list, float *vfCxSEQs_list, float *vfCxTTIsig, int TTIlen,  int SEQnum, int RBnum, int RBfrom, int FFTlen, int isDL=0);
LTEsubframe_deAssemble = _mybase.LTEsubframe_deAssemble;  LTEsubframe_deAssemble.argtypes = ( cFLTS ,cFLTS ,cFLTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ); 

#      void  CxSEQ_ZCseq(float *vfCxSEQs, int SCnum, int ZCroot, int ZCoffset);
CxSEQ_ZCseq = _mybase.CxSEQ_ZCseq;  CxSEQ_ZCseq.argtypes = ( cFLTS ,cINT  ,cINT  ,cINT  ); 

#      void stJakesMODEL_3GPPcfg(float *pstJakesMODELmem, int ModelTYPE,float fDopplerHz, float fSampleRate);
stJakesMODEL_3GPPcfg = _mybase.stJakesMODEL_3GPPcfg;  stJakesMODEL_3GPPcfg.argtypes = ( cFLTS ,cINT  ,cFLT  ,cFLT  ); 

#      void stJakesMODEL_FDfading(float *vfCxFDVec_list, int SAMPfrom , int SAMPnum, int SCoffset, int SCnum, int FFTlen,float fMaxBW_MHz, float *pstJakesMODELmem);
stJakesMODEL_FDfading = _mybase.stJakesMODEL_FDfading;  stJakesMODEL_FDfading.argtypes = ( cFLTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cFLT  ,cFLTS ); 


#  void LTEofdm_equalizer(float *vfCxQams,  int SCnum, int VEClen, float *vfCxSCsrc_list,float *vfCxSEQs_org,  float fNoisePwr, float *vfCxSCfadings)
LTEofdm_equalizer = _mybase.LTEofdm_equalizer;  LTEofdm_equalizer.argtypes = ( cFLTS ,cINT  ,cINT  ,cFLTS ,cFLTS ,cFLT  ,cFLTS ); 


#      void    gMEM_free(int icheck);    
gMEM_free = _mybase.gMEM_free;  gMEM_free.argtypes = ( cINT , ); 

#      void    gMEM_dump(char *strlabel, float *vfVEC, int VEClen, int MaxSample);
gMEM_dump = _mybase.gMEM_dump;  gMEM_dump.argtypes = ( cSTR  ,cFLTS ,cINT  ,cINT  ); 

#      int     gMEM_load(char *strlabel, float *vfVEC, int VEClen, int MaxSample);
gMEM_load = _mybase.gMEM_load;  gMEM_load.argtypes = ( cSTR  ,cFLTS ,cINT  ,cINT  ); gMEM_load.restype = cINT ; 

#      void MultiPATHfading_meas(float *vfCxPathVEC_Samples, int PathN, int SampleN , int SamplesSEC);
MultiPATHfading_meas = _mybase.MultiPATHfading_meas;  MultiPATHfading_meas.argtypes = ( cFLTS ,cINT  ,cINT  ,cINT  ); 


#  void CxVEC_amp(float *vfVECamp, float *vfCxVEC, int VEClen);
CxVEC_amp = _mybase.CxVEC_amp;  CxVEC_amp.argtypes = ( cFLTS ,cFLTS ,cINT  ); 

#  void  CxVEC_pwr(float *VECpwr, float *CxVEC, int VEClen);
CxVEC_pwr = _mybase.CxVEC_pwr;  CxVEC_pwr.argtypes = ( cFLTS ,cFLTS ,cINT  ); 

#  float LTEradioCH_simoFD(float *vfCxSCs_flt, float *vfCxTTIsig, int TTIlen, int TTIcnt, int RBfrom, int RBnum, float fNoisePwr, int linkN, int JakesTYPE, float fDopplerHz, float *vfCxSCfadings)
LTEradioCH_simoFD = _mybase.LTEradioCH_simoFD;  LTEradioCH_simoFD.argtypes = ( cFLTS ,cFLTS ,cINT  ,cINT  ,cINT  ,cINT  ,cFLT  ,cINT  ,cINT  ,cFLT  ,cFLTS ); LTEradioCH_simoFD.restype = cFLT ; 


#      int  AMC_control(int *pAMCmem, int *viINFObits, int MAXlen,  int iNACK, float fEsN0_meas, int iDly=0, int iLyrN=1);
AMC_control = _mybase.AMC_control;  AMC_control.argtypes = ( cINTS ,cINTS ,cINT  ,cINT  ,cFLT  ,cINT  ,cINT  ); AMC_control.restype = cINT ; 

#  void AMC_init(int *pAMCmem, int NetTBS, int SUMsc, int iModuType,  float fEsN0_init, int iRXnum int iAMC_ON)
AMC_init = _mybase.AMC_init;  AMC_init.argtypes = ( cINTS ,cINT  ,cINT  ,cINT  ,cFLT  ,cINT  ,cINT  ); 

#  int  AMC_mcslkt(int *viNetTBS_list, int *viQamType_list, float *vfCodeR_list, int MaxLEN, int RBnum);
AMC_mcslkt = _mybase.AMC_mcslkt;  AMC_mcslkt.argtypes = ( cINTS ,cINTS ,cFLTS ,cINT  ,cINT  ); AMC_mcslkt.restype = cINT ; 

#  void VEC_shannonSE(float *vfSErng,float *vfSpecEFF_list, float *vfEsN0_list, int VEClen, float fEsN0_min, float fEsN0_max, float fEsN0_bias=0);
VEC_shannonSE = _mybase.VEC_shannonSE;  VEC_shannonSE.argtypes = ( cFLTS ,cFLTS ,cFLTS ,cINT  ,cFLT  ,cFLT  ,cFLT  ); 

#  float  CxVEC_qamSNRdB(float *vfCxQam_rx, float *vfCxQam_tx, int VEClen)
CxVEC_qamSNRdB = _mybase.CxVEC_qamSNRdB;  CxVEC_qamSNRdB.argtypes = ( cFLTS ,cFLTS ,cINT  ); CxVEC_qamSNRdB.restype = cFLT ; 

#      void GDB_svCxM(char *strVarName, float *vfCxMdata, int iRow, int iCol);  
GDB_svCxM = _mybase.GDB_svCxM;  GDB_svCxM.argtypes = ( cSTR  ,cFLTS ,cINT  ,cINT  ); 

#      void GDB_svMat(char *strVarName, float *vfMat, int iRow, int iCol);      
GDB_svMat = _mybase.GDB_svMat;  GDB_svMat.argtypes = ( cSTR  ,cFLTS ,cINT  ,cINT  ); 

#      void GDB_svIMat(char *strVarName, int *viMat,  int iRow, int iCol);      
GDB_svIMat = _mybase.GDB_svIMat;  GDB_svIMat.argtypes = ( cSTR  ,cINTS ,cINT  ,cINT  ); 

#      void GDB_rst(int iForce);     
GDB_rst = _mybase.GDB_rst;  GDB_rst.argtypes = ( cINT , ); 

#  void  VECs_merge(float *vfVECs_mrg, int VEClen, int MaxNUM, float *vfVECs_add,   int iFrom, int iNUM );
VECs_merge = _mybase.VECs_merge;  VECs_merge.argtypes = ( cFLTS ,cINT  ,cINT  ,cFLTS ,cINT  ,cINT  ); 



#  float CxVECs_sumpwr(float *vfSumPwrs, float *vfCxVEC_list,  int VEClen, int VECnum);    
CxVECs_sumpwr = _mybase.CxVECs_sumpwr;  CxVECs_sumpwr.argtypes = ( cFLTS ,cFLTS ,cINT  ,cINT  ); CxVECs_sumpwr.restype = cFLT ; 

#  void  VEC_debpsk(int *viBITS, float *vfVECsrc, int VEClen, int isBIT1neg);
VEC_debpsk = _mybase.VEC_debpsk;  VEC_debpsk.argtypes = ( cINTS ,cFLTS ,cINT  ,cINT  ); 


#  float BITs_ber(int *viBITs_A, int *viBITS_B, int BITnum, int isDB=0);
BITs_ber = _mybase.BITs_ber;  BITs_ber.argtypes = ( cINTS ,cINTS ,cINT  ,cINT  ); BITs_ber.restype = cFLT ; 

#  void  MeasCIR2x2_fading(float *vfCxRX2_sc, float *vfCxH2x2_sc, float *vfCxQams_2T, float *vfCxCIR2x2_list, int TTIcnt,   int CIRlen,  int FFTlen,  int SCoffset, int SCnum, float *pfSVDx2=0);
MeasCIR2x2_fading = _mybase.MeasCIR2x2_fading;  MeasCIR2x2_fading.argtypes = ( cFLTS ,cFLTS ,cFLTS ,cFLTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cFLTS ); 



#  void  MIMO_equalizer(float *vfllrs, float *vfCxR2_sc, float *vfCxH2x2_sc,  int SCnum , int ModuType, float fNoisePwr, int isLMMSE=1, int isLyrSPLIT=0, int LyrN=2);
MIMO_equalizer = _mybase.MIMO_equalizer;  MIMO_equalizer.argtypes = ( cFLTS ,cFLTS ,cFLTS ,cINT  ,cINT  ,cFLT  ,cINT  ,cINT  ,cINT  ); 

#      void CODEC_turboENC(int *pCODECparam, int *viRvBITS,     int QamNUM, int ModuType, int NetTBS, int RvID, int *viINFOcrc);
CODEC_turboENC = _mybase.CODEC_turboENC;  CODEC_turboENC.argtypes = ( cINTS ,cINTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINTS ); 

#      int  CODEC_turboDEC(int *pCODECparam, float *vfDemodLLR, int QamNUM, int ModuType, int NetTBS, int RvID, int *viINFOdec=0);
CODEC_turboDEC = _mybase.CODEC_turboDEC;  CODEC_turboDEC.argtypes = ( cINTS ,cFLTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINTS ); CODEC_turboDEC.restype = cINT ; 


#  void  CxVEC_gaussianADD(float *vfCxVEC_O,  float *vfCxVEC_S, int VEClen, float fNoisePwr);
CxVEC_gaussianADD = _mybase.CxVEC_gaussianADD;  CxVEC_gaussianADD.argtypes = ( cFLTS ,cFLTS ,cINT  ,cFLT  ); 

#  void  MeasCIR2x2_refine(float *vfCxCIR2x2_O, float *vfCxCIR2x2_list, int isCIRnorm,   int CIRlen,  int FFTlen,  int SCoffset, int SCnum )
MeasCIR2x2_refine = _mybase.MeasCIR2x2_refine;  MeasCIR2x2_refine.argtypes = ( cFLTS ,cFLTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ); 



#  void NXsubframe_mappingFD(float *vfCxFDofdm_list, int Vlen, int DOFDMnum, float *vfCxSCs_list, int SEQnum, float *vfCxSEQs_list,  int RBnum, int RBfrom, int isGuardBand);
NXsubframe_mappingFD = _mybase.NXsubframe_mappingFD;  NXsubframe_mappingFD.argtypes = ( cFLTS ,cINT  ,cINT  ,cFLTS ,cINT  ,cFLTS ,cINT  ,cINT  ,cINT  ); 


#      float  MIMO_precodingH(float *vfCxSCH_O, float *vfCxSCH_s, float *vfCxPM_SBD , int RxM,  int TxN, int LyrN , int SubBN, int RBnum, int OFDMnum);
MIMO_precodingH = _mybase.MIMO_precodingH;  MIMO_precodingH.argtypes = ( cFLTS ,cFLTS ,cFLTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  );  MIMO_precodingH.restype = cFLT ; 

#      void  MIMO_precoderTypeII(float *vfCxPM_SBD , float *vfCxSCH_s,  int RxM,  int TxN, int LyrN , int SubBN, int RBnum, int TXAntC, int TXxplN, int isRECsamples);
MIMO_precoderTypeII = _mybase.MIMO_precoderTypeII;  MIMO_precoderTypeII.argtypes = ( cFLTS ,cFLTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ); 


#      void  MIMO_precoder(float *vfCxSCV_TX,float *vfCxPM_SBD, float *vfCxSCs_lyr,   int TxN, int LyrN , int SubBN, int RBnum, int OFDMnum, int isPMok);
MIMO_precoder = _mybase.MIMO_precoder;  MIMO_precoder.argtypes = ( cFLTS ,cFLTS ,cFLTS ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ); 

#  float MIMOcirs_brief(int *pTTIs, int RxM , int TxN , char *strCIRfile, char *strGDBrxpwrsave);
MIMOcirs_brief = _mybase.MIMOcirs_brief;  MIMOcirs_brief.argtypes = ( cINTS ,cINT  ,cINT  ,cSTR  ,cSTR  ); MIMOcirs_brief.restype = cFLT ; 

#  float MIMO_channelFD(float *vfCxSCs_flt, float *vfCxOFDMs_TXs,  char* strCIRfile,  int OFDMnum,  int RBnum,   int RxM, int TxN,  int TTIcnt, int RBfrom, float fNoisePwr, float *vfCxSCH_ice);
MIMO_channelFD = _mybase.MIMO_channelFD;  MIMO_channelFD.argtypes = ( cFLTS ,cFLTS ,cSTR ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cFLT  ,cFLTS ); MIMO_channelFD.restype = cFLT ; 

#  int SCM3DmimoH_QuaDriGa(char *strSaveTAG, char *strSEGcfgFILE, int SEGnum, int RBnum ,int TTInum, int TxN, int RxM, int iXplN, int TTIgap, int isTXomni);
SCM3DmimoH_QuaDriGa = _mybase.SCM3DmimoH_QuaDriGa;  SCM3DmimoH_QuaDriGa.argtypes = ( cSTR  ,cSTR  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ); SCM3DmimoH_QuaDriGa.restype = cINT ; 

#  int   SCM3Dmimo_genH(char* strSaveTAG, int eSCMcaseID, int DropN, int RBnum, int TTInum, int TxN, int RxM, int iXplN, int TTIgap, int isTXomni=0, char* strSaveName);
SCM3Dmimo_genH = _mybase.SCM3Dmimo_genH;  SCM3Dmimo_genH.argtypes = ( cSTR  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ,cSTR  ); SCM3Dmimo_genH.restype = cINT ; 



#      void   LTEturbo_encoder(int* viRVbits, int RVlen, int* viINFOcrc, int NetTBS, int ModuType, int RvID);
LTEturbo_encoder = _mybase.LTEturbo_encoder;  LTEturbo_encoder.argtypes = ( cINTS ,cINT  ,cINTS ,cINT  ,cINT  ,cINT  ); 

#      void   LTEturbo_decoder(int* viCRC, float* vfDemodLLR, int NetTBS, int QamNUM, int ModuType, float* vfHARQ_llr, int RvID, int MaxIter, int* viINFOcrc=0);
LTEturbo_decoder = _mybase.LTEturbo_decoder;  LTEturbo_decoder.argtypes = ( cINTS ,cFLTS  ,cINT  ,cINT  ,cINT  ,cFLTS  ,cINT  ,cINT  ,cINTS ); 




#  int  LDPCDec_aiCRC(float* vfDecLLRs_list, int Vlen, int Vnum);
LDPCDec_aiCRC = _mybase.LDPCDec_aiCRC;  LDPCDec_aiCRC.argtypes = ( cFLTS  ,cINT  ,cINT  ); LDPCDec_aiCRC.restype = cINT ; 


#  void LDPCDec_pickleBLER( float fBLER, int TTInum);
LDPCDec_pickleBLER = _mybase.LDPCDec_pickleBLER;  LDPCDec_pickleBLER.argtypes = ( cFLT  ,cINT  ); 

#  void CxHs_merge(float* vfCxHs_full, float* vfCxHs_part, int RxM, int MaxN, int LyrN, int LyrBias, int MATnum);
CxHs_merge = _mybase.CxHs_merge;  CxHs_merge.argtypes = ( cFLTS  ,cFLTS  ,cINT  ,cINT  ,cINT  ,cINT  ,cINT  ); 


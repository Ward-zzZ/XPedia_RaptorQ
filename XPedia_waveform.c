
#include "PerfMetric_COMM.h"
#include "XPedia_waveform.h"




void   DMRSgen_ZCseq(float* vfCxSEQs_sc, int SCnum, int LyrN, int LyrBias, int MaxLyrN, int ZCroot, int DMRSnum, float *vfCxSEQs_all)
/* generate orthogonal ZC sequences
*  vfCxSEQs_sc : ZC complex sequences,  LyrN compelx items on each SC
*  SCnum       : number of sub-carriers
*  LyrN        : number of layers
*  DMRSnum     : number of DMRS
Change History 
*  1st version designed by Duan Weiming in 2021-04-11
*/
{
    int ZCoffset = LyrBias;

    retERR_LEZ3(SCnum,LyrN,DMRSnum)    retERR_RNG(LyrN,1,8)    retERR_RNG(ZCoffset+LyrN,1,8)  retERR_RNG(DMRSnum,1,2)   retERR_RNG(LyrBias+LyrN,1, MaxLyrN)

    int iPrime = getPrime(SCnum);      retERR_RNG(ZCroot,1,iPrime-1)
    
    retERR_RNG(ZCoffset,0, iPrime-1)   retERR_RNG(ZCoffset+LyrN,0, iPrime-1)       

    MEMCHK(vfCxSEQs_sc, DMRSnum*SCnum*LyrN*2)   MEMCHK(vfCxSEQs_all, DMRSnum*MaxLyrN*SCnum*2) 

    float *vfCxSEQ;  int cnt;
    _LOOPUP_LT(cnt,0, LyrN) {
        vfCxSEQ = vfCxSEQs_sc + cnt*SCnum*2;
        CxSEQ_ZCseq(vfCxSEQ,  SCnum,  ZCroot,  ZCoffset+cnt);        
    }
    FLT_CP(vfCxSEQs_sc, vfCxSEQs_all + LyrBias*SCnum*2, LyrN*SCnum*2);
    CxMat_tranposeS(vfCxSEQs_sc, LyrN, SCnum);
    if(1 < DMRSnum) {
        VEC_clone(vfCxSEQs_sc  + SCnum*LyrN*2,    vfCxSEQs_sc, SCnum*LyrN*2,    DMRSnum-1);
        VEC_clone(vfCxSEQs_all + MaxLyrN*SCnum*2, vfCxSEQs_all,MaxLyrN*SCnum*2, DMRSnum-1);
    }
    int iTST = 3;
    

}



void NXsubframe_ofdmptrs(float **pvfSCs, int OFDMnum, int SCnum, float *vfCxQams_list,  int DMRSnum, int *viDMRSpos, float *vfCxDMRSs_list)
/*
Change History
*  de-coupled from LTEofdm_ofdmptrs(), byDuan Weiming in 2020-12-01
*  
*/
{
    retERR_NEQ(OFDMnum,14)     retERR_NEQ(DMRSnum,2)   retERR_CHK(OFDMnum < DMRSnum+2)    int jjj;//retERR_NEQ(FFTlen,2048)  
    MEMCHK(vfCxQams_list, (OFDMnum - DMRSnum)*SCnum*2)  retERR_validIVEC(viDMRSpos,DMRSnum, 0, OFDMnum-1) 
    MEMCHK(vfCxDMRSs_list, DMRSnum*SCnum*2)               

    _NEW_INIT()   _NEW_INT0(viIDS, OFDMnum)

    _LOOPUP_LT(jjj,0, DMRSnum) {  viIDS[viDMRSpos[jjj]] = 1; }

    float *pfSCsrc  = vfCxQams_list;  
    float *pfSEQsrc = vfCxDMRSs_list;  


    _LOOPUP_LT(jjj,0,OFDMnum) {   // arrange data for each OFDM
        
        //if(vfCxDMRSs_list && _CHK_OPT2(jjj,3,10) ) {  pvfSCs[jjj]  = pfSEQsrc;  pfSEQsrc += SCnum*2; }
        if( viIDS[jjj] ) {  pvfSCs[jjj]  = pfSEQsrc;  pfSEQsrc += SCnum*2; }
        else             {  pvfSCs[jjj]  = pfSCsrc;   pfSCsrc  += SCnum*2; }
        
    }

    _NEW_FREE()
    
}


void   NXsubframe_genFD(float* vfCxFDofdm_list, int LyN, int DOFDMnum, float* vfCxQams_list, int DMRSnum, float* vfCxDMRSs_list, int RBnum, int RBfrom, int isGuardBand)
/* generate ofdm sysmbols in Freq. Domain
*  vfCxFDofdm_list : OFDM symbols list , each OFDM symbol is composed of sub-carriers, and each data sub-carrrier carries 1~LyrN Qams (one Qam each layer)
*  LyN             : layer number (number of Qams carried by each sub-carrier)
*  DOFDMnum        : number of data ofdm symbols in one subframe
*  vfCxQams_list   : Qams list
*  DMRSnum         : number of DMRS symbols in one subframe
*  vfCxDMRSs_list  : DMRS sequences carried on each DMRS symbol
*  RBnum           : number of RBs used
*  RBfrom          : RB offset
*  isGuardBand     : padding zeros on unused sub-carriers , including null sub-carriers in guard-band or sub-carriers of unused RBs
Change History 
*  1st version designed by Duan Weiming in 2021-03-27
*/
{
	int FFTlen  = 2048;    int isDL  = 1;    int SYSRBnum = 100;    int SCnum = RBnum*12;    int OFDMnum  = DOFDMnum + DMRSnum;

    retERR_LEZ3(LyN,DOFDMnum,RBnum)    
    float *pvfSCs[32];                          retERR_CHK(32 < OFDMnum)
    CLAIM_IVEC(2, viDMRSpos,3,10)               retERR_NEQ(DMRSnum,2)
    
    retERR_RNG(RBnum,5, SYSRBnum)               retERR_RNG(RBfrom,0,SYSRBnum-5)             retERR_LT(SYSRBnum,RBfrom+RBnum)
    MEMCHK(vfCxDMRSs_list,DMRSnum*SCnum*LyN*2)  MEMCHK(vfCxQams_list,DOFDMnum*SCnum*LyN*2)  MEMCHK(vfCxFDofdm_list, OFDMnum*SCnum*LyN*2)
    
    int isZeroDC = 0;  if(isDL) { isZeroDC = 1; }    int jjj,cnt;   float *pfSRC, *pfDST;
    
    
    NXsubframe_ofdmptrs(pvfSCs, OFDMnum,  SCnum*LyN,  vfCxQams_list,   DMRSnum, viDMRSpos, vfCxDMRSs_list);

    int SCgap = 1; int SCshift = 0; int isRESET = 1;  int isMAP = 1; 
    _LOOPUP_LT(cnt,0,OFDMnum) {   // waveform for each OFDM
    	pfSRC = pvfSCs[cnt];
    	pfDST = vfCxFDofdm_list + cnt*SCnum*LyN*2;
    	FLT_CP(pfSRC, pfDST, SCnum*LyN*2);
        //_LOOPUP_LT(jjj, 0, SCnum) { CxVEC_clone(pfDST, pfSRC, 1 , LyN); pfSRC += 2;  pfDST += LyN*2;   }
        //OFDMmapSC_ORG(pvfOFDM[jjj],  pvfSCs[jjj], SCnum, FFTlen, SYSRBnum, RBfrom, isZeroDC, SCgap, SCshift,  isRESET, isMAP);  
    }
    int iTST = 3;

}



#define _BITmap_(__bit__) (1 - 2*(__bit__))
#define _QamBITS_(__MT) 	((((__MT)>>1)&0x1)*1+(((__MT)>>2)&0x1)*2+(((__MT)>>3)&0x1)*3+(((__MT)>>4)&0x1)*4+(((__MT)>>6)&0x1)*6+(((__MT)>>8)&0x1)*8+(((__MT)>>10)&0x1)*10)

void   NXQam_modu(float* vfCxQamLIST, int* viBits, int QamN, int ModuType)
/* generate complex Qam symbols according to definition of qam constellation in 3GPP
*  vfCxQamLIST : complex Qam symbols
*  viBits      : list of bits
*  QamN        : number of Qams
*  ModuType    : mudulation type, 2(Bpsk), 4(Qpsk), 16(16Qam), 64(64Qam),256(256Qam)
Change History 
*  1st version designed by Duan Weiming in 2021-03-28
*  1st version designed by Duan Weiming in 2018-02-25
*  fix a bug after reviewing 38.211, by Duan Weiming in 2020-01-02
*  change function name , by  Duan Weiming in 2021-03-28
*/
{
    const float __invsqrt_10  = 0.316227766;
    const float __invsqrt_42  = 0.154303350;
    const float __invsqrt_170 =   0.076696498884737;
    retERR_LIST(ModuType,-2,2,4,16,64,256)  retERR_LEZ(QamN)
    int ModuTYPE = ABSOP(ModuType);  int QamBITS =  _QamBITS_(ModuTYPE);
    MEMCHK(viBits, QamN*QamBITS)    MEMCHK(vfCxQamLIST, QamN*2)
    int jjj,kkk; 
    
    int *pnQamBITS = viBits;  float *pfQAM_IQ = vfCxQamLIST;
    if ( -2 == ModuType ) {
        _LOOPUP_LT(jjj,0, (QamN>>1)) { // i0 0 0 q1
            *pfQAM_IQ++ = (float)(_BITmap_(pnQamBITS[0])); *pfQAM_IQ++ = 0;
            *pfQAM_IQ++ = 0; *pfQAM_IQ++ =(float)(_BITmap_(pnQamBITS[1]));
            pnQamBITS += 2;
        }
    }
    else if ( 2 == ModuType ) {
        _LOOPUP_LT(jjj,0, QamN) { // 
            *pfQAM_IQ++ = (float)(1-2*pnQamBITS[0]); *pfQAM_IQ++ = 0;
            pnQamBITS++;
        }
    }
    else if ( 4 == ModuType ) {
        _LOOPUP_LT(jjj,0, QamN) {
            *pfQAM_IQ++ = 0.7071*(float)(_BITmap_(pnQamBITS[0]) );
            *pfQAM_IQ++ = 0.7071*(float)(_BITmap_(pnQamBITS[1]) );
            pnQamBITS += 2;
        }
    }
    else if ( 16 == ModuType ) {
        _LOOPUP_LT(jjj,0, QamN) {
            *pfQAM_IQ++ = __invsqrt_10*(float)(_BITmap_(pnQamBITS[0])*(2 - _BITmap_(pnQamBITS[2]) ) );  // 2 + _BITmap_() == 2 - _BITmap_(), modified by Duan Weiming in 2020-01-02
            *pfQAM_IQ++ = __invsqrt_10*(float)(_BITmap_(pnQamBITS[1])*(2 - _BITmap_(pnQamBITS[3]) ) );  // 2 + _BITmap_() == 2 - _BITmap_(), modified by Duan Weiming in 2020-01-02
            pnQamBITS += 4;
        }
    }
    else if ( 64 == ModuType ) {
        _LOOPUP_LT(jjj,0, QamN) {
            *pfQAM_IQ++ = __invsqrt_42*_BITmap_(pnQamBITS[0])*(4 - _BITmap_(pnQamBITS[2])*(2 - _BITmap_(pnQamBITS[4]) ) ); // +==>- modified by Duan Weiming in 2020-01-02
            *pfQAM_IQ++ = __invsqrt_42*_BITmap_(pnQamBITS[1])*(4 - _BITmap_(pnQamBITS[3])*(2 - _BITmap_(pnQamBITS[5]) ) ); // +==>- modified by Duan Weiming in 2020-01-02
            pnQamBITS += 6;
        }
    }
    else if ( 256 == ModuType ) {
        _LOOPUP_LT(jjj,0, QamN) {
            *pfQAM_IQ++ = __invsqrt_170*_BITmap_(pnQamBITS[0])*(8 - _BITmap_(pnQamBITS[2])*(4 - _BITmap_(pnQamBITS[4])*(2 - _BITmap_(pnQamBITS[6]) ) ) ) ;
            *pfQAM_IQ++ = __invsqrt_170*_BITmap_(pnQamBITS[1])*(8 - _BITmap_(pnQamBITS[3])*(4 - _BITmap_(pnQamBITS[5])*(2 - _BITmap_(pnQamBITS[7]) ) ) ) ;
            pnQamBITS += 8;
        }
    }
    
    int nTST = 3;
}






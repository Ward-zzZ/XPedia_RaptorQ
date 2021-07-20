
#include "XPedia_Uplink.h"

#include "XPedia_PUCCH_A1org.c"
#include "XPedia_PUCCH_A2org.c"
#include "XPedia_PUCCH_A3org.c"
#include "XPedia_PUSCH_A1org.c"
#include "XPedia_PUSCH_A2org.c"
#include "XPedia_PUSCH_A3org.c"
#include "XPedia_PUSCH_A4org.c"

//#include "XPedia_PUCCH_Phase1.c"
#include "XPedia_PUSCH_Phase1.c"




void NRslot_config(int SLOTlen, int isNR)
/*
Change History
*  1st version designed by Duan Weiming in 2020-05-20
*/
{
    retERR_NEQ(SLOTlen, 14)    
    CLAIM_IVEC(14,viCPlist_LTE, 160,144,144,144,144,144,144,160,144,144,144,144,144,144);  // numerology of LTE
    CLAIM_IVEC(14,viCPlist_NR,  176,144,144,144,144,144,144,144,144,144,144,144,144,144);  // numerology of NR
    int *piCPList;
    if( 0 == isNR) { piCPList = viCPlist_LTE;  gviTTI14_DMRSpos2[0] = 3;     gviTTI14_DMRSpos2[1] = 10;   }  // LTE numerology
    else           { piCPList = viCPlist_NR;   gviTTI14_DMRSpos2[0] = 3;     gviTTI14_DMRSpos2[1] = 10;   }  // NR numerology , to be checked !!!
    
    INT_CP(piCPList, gviTTI14_CPlist_14, 14);
}


void NRseq_cgsQpsk(float *vfCxSEQ, int *viQpskIDS, int ilen)
/*
Change History
*  1st version designed by Duan Weiming in 2020-05-14
*/
{
    retERR_LIST(ilen,6,12,18,24)  MEMCHK(vfCxSEQ, ilen)  //retERR_RNG(GrpID,0,29)
    int jjj,iQpskID; float *pfDST;
    pfDST = vfCxSEQ;
    _LOOPUP_LT(jjj, 0, ilen) {  
        iQpskID = viQpskIDS[jjj];
        if( -3 ==  iQpskID )     { *pfDST++ = -0.7071;  *pfDST++ = -0.7071; }
        else if( -1 == iQpskID)  { *pfDST++ = +0.7071;  *pfDST++ = -0.7071; }
        else if( +1 == iQpskID)  { *pfDST++ = +0.7071;  *pfDST++ = +0.7071; }
        else if( +3 == iQpskID)  { *pfDST++ = -0.7071;  *pfDST++ = +0.7071; }
        else                     {  ALARM_N2(iQpskID, jjj); *pfDST++ = 0; *pfDST++ = 0;  }  
    }
}


void PUCCH_BaseSEQ_ITF(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid)
/*
Change History
*  1st version designed by Duan Weiming in 2020-05-20
*/
{
    retERR_LIST(SCnum,6,12,18,24,30)
    if( 6  == SCnum) { PUCCH_baseSEQ_len6( vfCxVECseq, SCnum,  fAlpha,  GRPid); return; }
    if( 12 == SCnum) { PUCCH_baseSEQ_len12(vfCxVECseq, SCnum,  fAlpha,  GRPid); return; }
    if( 18 == SCnum) { PUCCH_baseSEQ_len18(vfCxVECseq, SCnum,  fAlpha,  GRPid); return; }
    if( 24 == SCnum) { PUCCH_baseSEQ_len24(vfCxVECseq, SCnum,  fAlpha,  GRPid); return; }
    if( 30 == SCnum) { PUCCH_baseSEQ_len30(vfCxVECseq, SCnum,  fAlpha,  GRPid); return; }

}


void NRslot_genOFDM(float *vfCxOFDMsig, int FFTlen, int CPlen, float *vfCxSC_list, int RBnum,int RBoffset, int isZeroDC)
/*  generate an OFDM complex signal with CP 
Change History
*  1st version designed by Duan Weiming in 2020-04-17
*/
{
    retERR_NEQ(FFTlen,2048)                   retERR_LIST(CPlen,144,176,160)         
    retERR_CHK(0 > RBoffset)                  retERR_CHK( 100 < RBnum + RBoffset)  
    MEMCHK(vfCxOFDMsig, (FFTlen+CPlen)*2)     MEMCHK(vfCxSC_list,RBnum*12*2)       

    int SYSoffset = (FFTlen - 1200)>>1;       float *pfSRC, *pfDST;
    int iZC = 0; if( isZeroDC) { iZC = 1;}


    _NEW_INIT()
    _NEW_FLT0(vfCxFFTmem, FFTlen*2)

    float *pfOFDM = vfCxOFDMsig + CPlen*2;     pfOFDM[0] = pfOFDM[1] = 0; // zero DC
    int iSCoffset = SYSoffset + RBoffset*12;     
    FLT_CP(vfCxSC_list, vfCxFFTmem + iSCoffset*2, RBnum*12*2);

    pfSRC = vfCxFFTmem;                   pfDST = pfOFDM + FFTlen;  FLT_CP(pfSRC,pfDST, FFTlen);
    pfSRC = vfCxFFTmem + FFTlen;          pfDST = pfOFDM + iZC*2;   FLT_CP(pfSRC,pfDST, FFTlen-iZC*2);
    CxVEC_ifft(pfOFDM,pfOFDM, FFTlen);   
    pfSRC = pfOFDM + (FFTlen - CPlen)*2;  pfDST = vfCxOFDMsig;      FLT_CP(pfSRC,pfDST, CPlen*2);         // add Cyclic Prefix

    _NEW_FREE()

}


void NRslot_gen(float *vfCxSLOTsig, int SLOTlen, float *vfCxSC_list, int RBnum, int RBoffset, int OFDMfrom, int OFDMnum, int isZeroDC)
/*
Change History
*  1st verson designed by Duan Weiming in 2020-04-19
*/
{
    int FFTlen = 2048;                 int SCnum = RBnum*12;                int jjj,iCPlen;             
    retERR_NEQ(SLOTlen, FFTlen*15)     retERR_LTZ2(RBoffset,OFDMfrom)       retERR_LEZ2(RBnum, OFDMnum) 
    retERR_CHK(100 < RBoffset+RBnum)   retERR_CHK(14 < OFDMfrom+OFDMnum)    
    MEMCHK(vfCxSLOTsig,SLOTlen*2)      MEMCHK(vfCxSC_list, OFDMnum*SCnum*2)


    //CLAIM_IVEC(14,viCPlist, 160,144,144,144,144,144,144,160,144,144,144,144,144,144);  // numerology of LTE
    int *viCPlist = gviTTI14_CPlist_14;


    _NEW_INIT()
    _NEW_FLT0(vfOFDMsig, (FFTlen+512)*2)

    float *pfSRC = vfCxSC_list;   
    float *pfDST = vfCxSLOTsig;
    _LOOPUP_LT(jjj,0, 14) {
        iCPlen = viCPlist[jjj];
        NRslot_genOFDM(vfOFDMsig, FFTlen, iCPlen, pfSRC, RBnum, RBoffset, isZeroDC);
        FLT_CP(vfOFDMsig, pfDST, (FFTlen+iCPlen)*2);
        pfSRC += SCnum*2;
        pfDST += (FFTlen + iCPlen)*2;
    }
    _NEW_FREE()

}

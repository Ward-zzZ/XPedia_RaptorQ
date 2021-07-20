
#include "PerfMetric_COMM.h"
#include "XPedia_mimoMLDideal.h"

#define _GET_QamBITS(__MT)  ((((__MT)>>1)&0x1)*1+(((__MT)>>2)&0x1)*2+(((__MT)>>3)&0x1)*3+(((__MT)>>4)&0x1)*4+(((__MT)>>6)&0x1)*6+(((__MT)>>8)&0x1)*8+(((__MT)>>10)&0x1)*10)

void MLD_cfgTX2(float *vfCxV_opts, int *viBitIDs_list, int TxN, int OPTs,  int ModuType)
/*
Change History
*  1st version designed by Duan Weiming in 2020-09-16
*/
{
    retERR_LIST(ModuType,4,16,64)         retERR_LEZ3(TxN,OPTs,ModuType)    retERR_NEQ(TxN, 2)   retERR_NEQ(OPTs, ModuType*ModuType)   
    int QamB = _GET_QamBITS(ModuType);    int BITn = TxN*QamB;              int MapB = (1 << QamB) - 1;
    MEMCHK(vfCxV_opts, OPTs*TxN*2)        MEMCHK(viBitIDs_list, BITn*OPTs)  
    //float vfCxQPSKs[4*2] = { +0.7071,+0.7071, +0.7071,-0.7071,  -0.7071,+0.7071,   -0.7071,-0.7071, };       // 00 01 10 11

    int cnt,iD0,iD1,iB,bbb;  float *pfDST; int *piGRP, *piBIT;
    int  QamN = ModuType;

    _NEW_INIT()   _NEW2_INT0(viBIT0cnt,  viBIT1cnt, BITn)  _NEW_INT0(viBITS_list,QamN*QamB)   _NEW_FLT0(vfCxQamS, QamN*2)   

    piBIT = viBITS_list;     _LOOPUP_LT(cnt, 0, QamN) {   _LOOPUP_LT(bbb, 0, QamB) {    *piBIT++ = (cnt >> (QamB-1-bbb)) & 0b01;   }   }

    Qam_Modu_REL(vfCxQamS, viBITS_list, QamN,  ModuType);  

    _LOOPUP_LT(cnt, 0, OPTs) {
        iD0   = (cnt >> QamB) & MapB;    // 0b11 ==> MapB
        iD1   = cnt & MapB;
        pfDST = vfCxV_opts + cnt*TxN*2;                 // cnt*2*2 ==> cnt*TxN*2
        FLT_CP(vfCxQamS + iD0*2 ,  pfDST + 0*2, 2);
        FLT_CP(vfCxQamS + iD1*2 ,  pfDST + 1*2, 2);
        _LOOPUP_LT(bbb, 0, BITn) {
            piGRP = viBitIDs_list + bbb*OPTs;    // 16 ==> OPTs
            iB = (cnt >> (BITn-1-bbb)) & 0x01;
            if (iB)  { piGRP[viBIT1cnt[bbb]+(OPTs>>1)] = cnt;   viBIT1cnt[bbb] += 1; }
            else     { piGRP[viBIT0cnt[bbb]]   = cnt;           viBIT0cnt[bbb] += 1; }
        }

    }

    _NEW_FREE()

}


void MIMO2x2_MLDideal(float *vfllrs, float *vfCxR2_sc, float *vfCxH2x2_sc,  int SCnum , int ModuType, float fNoisePwr )
/*
Change History
*  1st version designed by Duan Weiming in 2020-09-16
*/
{
    //MeasCIR2x2_fading(float *vfCxSCs_2R, float *vfCxM2x2_ices, float *vfCxQams_2T, float *vfCxCIR2x2_list, int TTIcnt,   int CIRlen,  int FFTlen,  int SCoffset, int SCnum )
    int RxM = 2;                           int TxN = 2;                               
    int cnt,jjj,iD0,iD1,iB,bbb;            float *pfDST,*pfCxR, *pfCxH, *pfLlr;  //int *piGRP;
    retERR_LEZ(SCnum)                      retERR_LTZ(fNoisePwr)                 retERR_LIST(ModuType,4,16,64)     
    int QAMnum = SCnum*TxN;                int QAMbit = _GET_QamBITS(ModuType);
    int OPTs = ModuType*ModuType;          int BITSsc = TxN*QAMbit;               int BITopt = (OPTs>>1);

    MEMCHK(vfCxH2x2_sc, SCnum*RxM*TxN*2)    MEMCHK(vfCxR2_sc, SCnum*RxM*2)        MEMCHK(vfllrs, QAMnum*QAMbit)
    float __inv_2xNoisePwr__ = _DIVOP(1.0, -2.0*fNoisePwr);

    _NEW_INIT()      
    _NEW2_FLT0(vfCxS2_opts, vfCxR2_opts, OPTs*TxN*2)   //  H2x2 * SV2 ==> RV2   OPTs*4*2 ==> OPTs*TxN*2
    _NEW_INT0(viBITids_grp, BITSsc*OPTs)               //  4 groups : 8 IDs of bit0 & 8 IDs of bit1 for each group
    _NEW_FLT0(vfDistS_opts,  OPTs)                   
    _NEW_FLT0(vfMinDST_lst, BITSsc*2)

    MLD_cfgTX2(vfCxS2_opts, viBITids_grp,  TxN,  OPTs,   ModuType);
    
    _LOOPUP_LT(cnt, 0,  SCnum) {
        pfCxR = vfCxR2_sc   + cnt*2*2;
        pfCxH = vfCxH2x2_sc + cnt*2*2*2;
        pfLlr = vfllrs      + cnt*BITSsc;
        CxVECs_HxS(vfCxR2_opts,  pfCxH, vfCxS2_opts, RxM,TxN, OPTs, 1 );  //isHfixed = 1
        CxVECs_distSQR(vfDistS_opts,  pfCxR, vfCxR2_opts, RxM , OPTs );   //  sum(|R2 - R2_opts|^2) ==> 
        VEC_pickMINS(vfMinDST_lst, vfDistS_opts, OPTs, viBITids_grp, BITopt, BITSsc*2);
        _LOOPUP_LT(jjj, 0, BITSsc) {  pfLlr[jjj] = (vfMinDST_lst[jjj*2+1] - vfMinDST_lst[jjj*2])*__inv_2xNoisePwr__; }        
    } 

    int iTST = 0;

    _NEW_FREE()

}

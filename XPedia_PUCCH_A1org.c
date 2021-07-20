
#include "XPedia_Uplink.h"


int gviPhi_len6[30*6] = {
-3  ,-1  ,3   ,3   ,-1  ,-3 ,
-3  ,3   ,-1  ,-1  ,3   ,-3 ,
-3  ,-3  ,-3  ,3   ,1   ,-3 ,
1   ,1   ,1   ,3   ,-1  ,-3 ,
1   ,1   ,1   ,-3  ,-1  ,3  ,
-3  ,1   ,-1  ,-3  ,-3  ,-3 ,
-3  ,1   ,3   ,-3  ,-3  ,-3 ,
-3  ,-1  ,1   ,-3  ,1   ,-1 ,
-3  ,-1  ,-3  ,1   ,-3  ,-3 ,
-3  ,-3  ,1   ,-3  ,3   ,-3 ,
-3  ,1   ,3   ,1   ,-3  ,-3 ,
-3  ,-1  ,-3  ,1   ,1   ,-3 ,
1   ,1   ,3   ,-1  ,-3  ,3  ,
1   ,1   ,3   ,3   ,-1  ,3  ,
1   ,1   ,1   ,-3  ,3   ,-1 ,
1   ,1   ,1   ,-1  ,3   ,-3 ,
-3  ,-1  ,-1  ,-1  ,3   ,-1 ,
-3  ,-3  ,-1  ,1   ,-1  ,-3 ,
-3  ,-3  ,-3  ,1   ,-3  ,-1 ,
-3  ,1   ,1   ,-3  ,-1  ,-3 ,
-3  ,3   ,-3  ,1   ,1   ,-3 ,
-3  ,1   ,-3  ,-3  ,-3  ,-1 ,
1   ,1   ,-3  ,3   ,1   ,3  ,
1   ,1   ,-3  ,-3  ,1   ,-3 ,
1   ,1   ,3   ,-1  ,3   ,3  ,
1   ,1   ,-3  ,1   ,3   ,3  ,
1   ,1   ,-1  ,-1  ,3   ,-1 ,
1   ,1   ,-1  ,3   ,-1  ,-1 ,
1   ,1   ,-1  ,3   ,-3  ,-1 ,
1   ,1   ,-3  ,1   ,-1  ,-1 };

int gviPhi_len12[30*12] = {
-3  ,1   ,-3  ,-3  ,-3  ,3   ,-3  ,-1  ,1   ,1   ,1   ,-3 ,
-3  ,3   ,1   ,-3  ,1   ,3   ,-1  ,-1  ,1   ,3   ,3   ,3  ,
-3  ,3   ,3   ,1   ,-3  ,3   ,-1  ,1   ,3   ,-3  ,3   ,-3 ,
-3  ,-3  ,-1  ,3   ,3   ,3   ,-3  ,3   ,-3  ,1   ,-1  ,-3 ,
-3  ,-1  ,-1  ,1   ,3   ,1   ,1   ,-1  ,1   ,-1  ,-3  ,1  ,
-3  ,-3  ,3   ,1   ,-3  ,-3  ,-3  ,-1  ,3   ,-1  ,1   ,3  ,
1   ,-1  ,3   ,-1  ,-1  ,-1  ,-3  ,-1  ,1   ,1   ,1   ,-3 ,
-1  ,-3  ,3   ,-1  ,-3  ,-3  ,-3  ,-1  ,1   ,-1  ,1   ,-3 ,
-3  ,-1  ,3   ,1   ,-3  ,-1  ,-3  ,3   ,1   ,3   ,3   ,1  ,
-3  ,-1  ,-1  ,-3  ,-3  ,-1  ,-3  ,3   ,1   ,3   ,-1  ,-3 ,
-3  ,3   ,-3  ,3   ,3   ,-3  ,-1  ,-1  ,3   ,3   ,1   ,-3 ,
-3  ,-1  ,-3  ,-1  ,-1  ,-3  ,3   ,3   ,-1  ,-1  ,1   ,-3 ,
-3  ,-1  ,3   ,-3  ,-3  ,-1  ,-3  ,1   ,-1  ,-3  ,3   ,3  ,
-3  ,1   ,-1  ,-1  ,3   ,3   ,-3  ,-1  ,-1  ,-3  ,-1  ,-3 ,
1   ,3   ,-3  ,1   ,3   ,3   ,3   ,1   ,-1  ,1   ,-1  ,3  ,
-3  ,1   ,3   ,-1  ,-1  ,-3  ,-3  ,-1  ,-1  ,3   ,1   ,-3 ,
-1  ,-1  ,-1  ,-1  ,1   ,-3  ,-1  ,3   ,3   ,-1  ,-3  ,1  ,
-1  ,1   ,1   ,-1  ,1   ,3   ,3   ,-1  ,-1  ,-3  ,1   ,-3 ,
-3  ,1   ,3   ,3   ,-1  ,-1  ,-3  ,3   ,3   ,-3  ,3   ,-3 ,
-3  ,-3  ,3   ,-3  ,-1  ,3   ,3   ,3   ,-1  ,-3  ,1   ,-3 ,
3   ,1   ,3   ,1   ,3   ,-3  ,-1  ,1   ,3   ,1   ,-1  ,-3 ,
-3  ,3   ,1   ,3   ,-3  ,1   ,1   ,1   ,1   ,3   ,-3  ,3  ,
-3  ,3   ,3   ,3   ,-1  ,-3  ,-3  ,-1  ,-3  ,1   ,3   ,-3 ,
3   ,-1  ,-3  ,3   ,-3  ,-1  ,3   ,3   ,3   ,-3  ,-1  ,-3 ,
-3  ,-1  ,1   ,-3  ,1   ,3   ,3   ,3   ,-1  ,-3  ,3   ,3  ,
-3  ,3   ,1   ,-1  ,3   ,3   ,-3  ,1   ,-1  ,1   ,-1  ,1  ,
-1  ,1   ,3   ,-3  ,1   ,-1  ,1   ,-1  ,-1  ,-3  ,1   ,-1 ,
-3  ,-3  ,3   ,3   ,3   ,-3  ,-1  ,1   ,-3  ,3   ,1   ,-3 ,
1   ,-1  ,3   ,1   ,1   ,-1  ,-1  ,-1  ,1   ,3   ,-3  ,1  ,
-3  ,3   ,-3  ,3   ,-3  ,-3  ,3   ,-1  ,-1  ,1   ,3   ,-3  };


void PUCCH_baseSEQ_len6(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid)
/*  generate low-PAPR complex sequence for PUCCH , 
*  reference #1:  subclause 5.2.2.2 (Base sequence of length less than 36) of TR38.211
*  reference #2:  table 5.2.2.2-3 of TR38.211
Change History
*  reference version designed by  Duan Weiming in 2020-05-15
*/
{

    retERR_NEQ(SCnum,6)                 // low-PAPR sequence length 6
    retERR_RNG(GRPid,0,29)              // base sequence Group ID
    retERR_CHK(0 > fAlpha)              // cyclic shift value
    MEMCHK(vfCxVECseq, SCnum*2)
    // add your codes here....
    int ilen = 6;   int *piQpskIDS = gviPhi_len6  + GRPid*ilen;
    NRseq_cgsQpsk(vfCxVECseq,piQpskIDS , ilen);
    CxVEC_phaseRotateSTD(vfCxVECseq, vfCxVECseq, ilen,  fAlpha );

}



void PUCCH_baseSEQ_len12(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid)
/*  generate low-PAPR complex sequence for PUCCH , 
*  reference #1:  subclause 5.2.2.2 (Base sequence of length less than 36) of TR38.211
*  reference #2:  table 5.2.2.2-4 of TR38.211
Change History
*  reference version designed by  Duan Weiming in 2020-05-15
*/
{
    retERR_NEQ(SCnum,12)                 // low-PAPR sequence length 6
    retERR_RNG(GRPid,0,29)              // base sequence Group ID
    retERR_CHK(0 > fAlpha)              // cyclic shift value
    MEMCHK(vfCxVECseq, SCnum*2)

    // add your codes here....
    int ilen = 12;   int *piQpskIDS = gviPhi_len12  + GRPid*ilen;
    NRseq_cgsQpsk(vfCxVECseq,piQpskIDS , ilen);
    CxVEC_phaseRotateSTD(vfCxVECseq, vfCxVECseq, ilen,  fAlpha );

}


int PUCCHformat0_mcs(int iBIT0, int iBIT11)
/*  
Change History
*  1st version designed by Duan Weiming in 2020-05-21
*/
{
    ret0ERR_RNG(iBIT0,0,1)             if( 0 <= iBIT11 ) { ret0ERR_RNG(iBIT11,0,1) }
    int vimcs_1bitmap[2] = {0,6};     // {bit0 , bit1 }                 defined in table 9.2.3-3 of TS38.213
    int vimcs_2bitmap[4] = {0,3,9,6}; // {bit00, bit01, bit10,  bit11}  defined in table 9.2.3-4 of TS38.213
    int iM_cs, iIDX; 
    if( 0 <= iBIT11 ) { iIDX = iBIT0 + iBIT11*2 ;  iM_cs = vimcs_2bitmap[iIDX];  }
    else              { iIDX = iBIT0 ;             iM_cs = vimcs_1bitmap[iIDX];  }
    return iM_cs;
}


void PUCCHformat0_genSEQ(float *vfCxSEQ_list, int SCnum, int OFDMnum, int iBIT0, int iBIT11, int iSLOTcnt, int GRPid, int CellID)
/*   generate complex sequences  for PUCCH format 0
Change History
*  reference version designed by  Duan Weiming in 2020-05-21
*/
{
    retERR_RNG(OFDMnum,1,2)   retERR_LIST(SCnum,6,12,18,24,30)        retERR_RNG(CellID,0,NR_MAXCellNUM-1)
    retERR_LTZ(iSLOTcnt)      retERR_RNG(GRPid,0,30-1)                MEMCHK(vfCxSEQ_list, OFDMnum*SCnum*2)      
    retERR_RNG(iBIT0,0,1)     if( 0 <= iBIT11 ) { retERR_RNG(iBIT11,0,1) }


    float fAlpha;  int iM_cs, SLOTid, jjj, OFDMid;  float *pfDST;
    SLOTid = iSLOTcnt%10;
    iM_cs  = PUCCHformat0_mcs(iBIT0, iBIT11);

    _LOOPUP_LT(jjj, 0,  OFDMnum) {
        OFDMid = 14 - OFDMnum + jjj;
        pfDST  = vfCxSEQ_list + jjj*SCnum*2;
        fAlpha = PUCCH_Alpha( OFDMid,  SLOTid,  iM_cs,  CellID);
        PUCCH_BaseSEQ_ITF(pfDST,  SCnum, fAlpha,  GRPid);
    }
}



#include "XPedia_Uplink.h"
int gviPhi_len18[30*18] = {
-1  ,3   ,-1  ,-3  ,3   ,1   ,-3  ,-1  ,3   ,-3  ,-1  ,-1  ,1   ,1   ,1   ,-1  ,-1  ,-1 ,
3   ,-3  ,3   ,-1  ,1   ,3   ,-3  ,-1  ,-3  ,-3  ,-1  ,-3  ,3   ,1   ,-1  ,3   ,-3  ,3  ,
-3  ,3   ,1   ,-1  ,-1  ,3   ,-3  ,-1  ,1   ,1   ,1   ,1   ,1   ,-1  ,3   ,-1  ,-3  ,-1 ,
-3  ,-3  ,3   ,3   ,3   ,1   ,-3  ,1   ,3   ,3   ,1   ,-3  ,-3  ,3   ,-1  ,-3  ,-1  ,1  , 
1   ,1   ,-1  ,-1  ,-3  ,-1  ,1   ,-3  ,-3  ,-3  ,1   ,-3  ,-1  ,-1  ,1   ,-1  ,3   ,1  ,
3   ,-3  ,1   ,1   ,3   ,-1  ,1   ,-1  ,-1  ,-3  ,1   ,1   ,-1  ,3   ,3   ,-3  ,3   ,-1 ,
-3  ,3   ,-1  ,1   ,3   ,1   ,-3  ,-1  ,1   ,1   ,-3  ,1   ,3   ,3   ,-1  ,-3  ,-3  ,-3 ,
1   ,1   ,-3  ,3   ,3   ,1   ,3   ,-3  ,3   ,-1  ,1   ,1   ,-1  ,1   ,-3  ,-3  ,-1  ,3  ,
-3  ,1   ,-3  ,-3  ,1   ,-3  ,-3  ,3   ,1   ,-3  ,-1  ,-3  ,-3  ,-3  ,-1  ,1   ,1   ,3  ,
3   ,-1  ,3   ,1   ,-3  ,-3  ,-1  ,1   ,-3  ,-3  ,3   ,3   ,3   ,1   ,3   ,-3  ,3   ,-3 ,
-3  ,-3  ,-3  ,1   ,-3  ,3   ,1   ,1   ,3   ,-3  ,-3  ,1   ,3   ,-1  ,3   ,-3  ,-3  ,3  ,
-3  ,-3  ,3   ,3   ,3   ,-1  ,-1  ,-3  ,-1  ,-1  ,-1  ,3   ,1   ,-3  ,-3  ,-1  ,3   ,-1 ,
-3  ,-1  ,-3  ,-3  ,1   ,1   ,-1  ,-3  ,-1  ,-3  ,-1  ,-1  ,3   ,3   ,-1  ,3   ,1   ,3  ,
1   ,1   ,-3  ,-3  ,-3  ,-3  ,1   ,3   ,-3  ,3   ,3   ,1   ,-3  ,-1  ,3   ,-1  ,-3  ,1  ,
-3  ,3   ,-1  ,-3  ,-1  ,-3  ,1   ,1   ,-3  ,-3  ,-1  ,-1  ,3   ,-3  ,1   ,3   ,1   ,1  ,
3   ,1   ,-3  ,1   ,-3  ,3   ,3   ,-1  ,-3  ,-3  ,-1  ,-3  ,-3  ,3   ,-3  ,-1  ,1   ,3  ,
-3  ,-1  ,-3  ,-1  ,-3  ,1   ,3   ,-3  ,-1  ,3   ,3   ,3   ,1   ,-1  ,-3  ,3   ,-1  ,-3 ,
-3  ,-1  ,3   ,3   ,-1  ,3   ,-1  ,-3  ,-1  ,1   ,-1  ,-3  ,-1  ,-1  ,-1  ,3   ,3   ,1  ,
-3  ,1   ,-3  ,-1  ,-1  ,3   ,1   ,-3  ,-3  ,-3  ,-1  ,-3  ,-3  ,1   ,1   ,1   ,-1  ,-1 ,
3   ,3   ,3   ,-3  ,-1  ,-3  ,-1  ,3   ,-1  ,1   ,-1  ,-3  ,1   ,-3  ,-3  ,-1  ,3   ,3  ,
-3  ,1   ,1   ,-3  ,1   ,1   ,3   ,-3  ,-1  ,-3  ,-1  ,3   ,-3  ,3   ,-1  ,-1  ,-1  ,-3 ,
1   ,-3  ,-1  ,-3  ,3   ,3   ,-1  ,-3  ,1   ,-3  ,-3  ,-1  ,-3  ,-1  ,1   ,3   ,3   ,3  ,
-3  ,-3  ,1   ,-1  ,-1  ,1   ,1   ,-3  ,-1  ,3   ,3   ,3   ,3   ,-1  ,3   ,1   ,3   ,1  ,
3   ,-1  ,-3  ,1   ,-3  ,-3  ,-3  ,3   ,3   ,-1  ,1   ,-3  ,-1  ,3   ,1   ,1   ,3   ,3  ,
3   ,-1  ,-1  ,1   ,-3  ,-1  ,-3  ,-1  ,-3  ,-3  ,-1  ,-3  ,1   ,1   ,1   ,-3  ,-3  ,3  ,
-3  ,-3  ,1   ,-3  ,3   ,3   ,3   ,-1  ,3   ,1   ,1   ,-3  ,-3  ,-3  ,3   ,-3  ,-1  ,-1 ,
-3  ,-1  ,-1  ,-3  ,1   ,-3  ,3   ,-1  ,-1  ,-3  ,3   ,3   ,-3  ,-1  ,3   ,-1  ,-1  ,-1 ,
-3  ,-3  ,3   ,3   ,-3  ,1   ,3   ,-1  ,-3  ,1   ,-1  ,-3  ,3   ,-3  ,-1  ,-1  ,-1  ,3  ,
-1  ,-3  ,1   ,-3  ,-3  ,-3  ,1   ,1   ,3   ,3   ,-3  ,3   ,3   ,-3  ,-1  ,3   ,-3  ,1  ,
-3  ,3   ,1   ,-1  ,-1  ,-1  ,-1  ,1   ,-1  ,3   ,3   ,-3  ,-1  ,1   ,3   ,-1  ,3   ,-1  };

int gviPhi_len24[30*24] = {
-1  ,-3  ,3   ,-1  ,3   ,1   ,3   ,-1  ,1   ,-3  ,-1  ,-3  ,-1  ,1   ,3   ,-3  ,-1  ,-3  ,3   ,3   ,3   ,-3  ,-3  ,-3 ,
-1  ,-3  ,3   ,1   ,1   ,-3  ,1   ,-3  ,-3  ,1   ,-3  ,-1  ,-1  ,3   ,-3  ,3   ,3   ,3   ,-3  ,1   ,3   ,3   ,-3  ,-3 ,
-1  ,-3  ,-3  ,1   ,-1  ,-1  ,-3  ,1   ,3   ,-1  ,-3  ,-1  ,-1  ,-3  ,1   ,1   ,3   ,1   ,-3  ,-1  ,-1  ,3   ,-3  ,-3 ,
1   ,-3  ,3   ,-1  ,-3  ,-1  ,3   ,3   ,1   ,-1  ,1   ,1   ,3   ,-3  ,-1  ,-3  ,-3  ,-3  ,-1  ,3   ,-3  ,-1  ,-3  ,-3 ,
-1  ,3   ,-3  ,-3  ,-1  ,3   ,-1  ,-1  ,1   ,3   ,1   ,3   ,-1  ,-1  ,-3  ,1   ,3   ,1   ,-1  ,-3  ,1   ,-1  ,-3  ,-3 ,
-3  ,-1  ,1   ,-3  ,-3  ,1   ,1   ,-3  ,3   ,-1  ,-1  ,-3  ,1   ,3   ,1   ,-1  ,-3  ,-1  ,-3  ,1   ,-3  ,-3  ,-3  ,-3 ,
-3  ,3   ,1   ,3   ,-1  ,1   ,-3  ,1   ,-3  ,1   ,-1  ,-3  ,-1  ,-3  ,-3  ,-3  ,-3  ,-1  ,-1  ,-1  ,1   ,1   ,-3  ,-3 ,
-3  ,1   ,3   ,-1  ,1   ,-1  ,3   ,-3  ,3   ,-1  ,-3  ,-1  ,-3  ,3   ,-1  ,-1  ,-1  ,-3  ,-1  ,-1  ,-3  ,3   ,3   ,-3 ,
-3  ,1   ,-3  ,3   ,-1  ,-1  ,-1  ,-3  ,3   ,1   ,-1  ,-3  ,-1  ,1   ,3   ,-1  ,1   ,-1  ,1   ,-3  ,-3  ,-3  ,-3  ,-3 ,
1   ,1   ,-1  ,-3  ,-1  ,1   ,1   ,-3  ,1   ,-1  ,1   ,-3  ,3   ,-3  ,-3  ,3   ,-1  ,-3  ,1   ,3   ,-3  ,1   ,-3  ,-3 ,
-3  ,-3  ,-3  ,-1  ,3   ,-3  ,3   ,1   ,3   ,1   ,-3  ,-1  ,-1  ,-3  ,1   ,1   ,3   ,1   ,-1  ,-3  ,3   ,1   ,3   ,-3 ,
-3  ,3   ,-1  ,3   ,1   ,-1  ,-1  ,-1  ,3   ,3   ,1   ,1   ,1   ,3   ,3   ,1   ,-3  ,-3  ,-1  ,1   ,-3  ,1   ,3   ,-3 ,
3   ,-3  ,3   ,-1  ,-3  ,1   ,3   ,1   ,-1  ,-1  ,-3  ,-1  ,3   ,-3  ,3   ,-1  ,-1  ,3   ,3   ,-3  ,-3  ,3   ,-3  ,-3 ,
-3  ,3   ,-1  ,3   ,-1  ,3   ,3   ,1   ,1   ,-3  ,1   ,3   ,-3  ,3   ,-3  ,-3  ,-1  ,1   ,3   ,-3  ,-1  ,-1  ,-3  ,-3 ,
-3  ,1   ,-3  ,-1  ,-1  ,3   ,1   ,3   ,-3  ,1   ,-1  ,3   ,3   ,-1  ,-3  ,3   ,-3  ,-1  ,-1  ,-3  ,-3  ,-3  ,3   ,-3 ,
-3  ,-1  ,-1  ,-3  ,1   ,-3  ,-3  ,-1  ,-1  ,3   ,-1  ,1   ,-1  ,3   ,1   ,-3  ,-1  ,3   ,1   ,1   ,-1  ,-1  ,-3  ,-3 ,
-3  ,-3  ,1   ,-1  ,3   ,3   ,-3  ,-1  ,1   ,-1  ,-1  ,1   ,1   ,-1  ,-1  ,3   ,-3  ,1   ,-3  ,1   ,-1  ,-1  ,-1  ,-3 ,
3   ,-1  ,3   ,-1  ,1   ,-3  ,1   ,1   ,-3  ,-3  ,3   ,-3  ,-1  ,-1  ,-1  ,-1  ,-1  ,-3  ,-3  ,-1  ,1   ,1   ,-3  ,-3 ,
-3  ,1   ,-3  ,1   ,-3  ,-3  ,1   ,-3  ,1   ,-3  ,-3  ,-3  ,-3  ,-3  ,1   ,-3  ,-3  ,1   ,1   ,-3  ,1   ,1   ,-3  ,-3 ,
-3  ,-3  ,3   ,3   ,1   ,-1  ,-1  ,-1  ,1   ,-3  ,-1  ,1   ,-1  ,3   ,-3  ,-1  ,-3  ,-1  ,-1  ,1   ,-3  ,3   ,-1  ,-3 ,
-3  ,-3  ,-1  ,-1  ,-1  ,-3  ,1   ,-1  ,-3  ,-1  ,3   ,-3  ,1   ,-3  ,3   ,-3  ,3   ,3   ,1   ,-1  ,-1  ,1   ,-3  ,-3 ,
3   ,-1  ,1   ,-1  ,3   ,-3  ,1   ,1   ,3   ,-1  ,-3  ,3   ,1   ,-3  ,3   ,-1  ,-1  ,-1  ,-1  ,1   ,-3  ,-3  ,-3  ,-3 ,
-3  ,1   ,-3  ,3   ,-3  ,1   ,-3  ,3   ,1   ,-1  ,-3  ,-1  ,-3  ,-3  ,-3  ,-3  ,1   ,3   ,-1  ,1   ,3   ,3   ,3   ,-3 ,
-3  ,-1  ,1   ,-3  ,-1  ,-1  ,1   ,1   ,1   ,3   ,3   ,-1  ,1   ,-1  ,1   ,-1  ,-1  ,-3  ,-3  ,-3  ,3   ,1   ,-1  ,-3 ,
-3  ,3   ,-1  ,-3  ,-1  ,-1  ,-1  ,3   ,-1  ,-1  ,3   ,-3  ,-1  ,3   ,-3  ,3   ,-3  ,-1  ,3   ,1   ,1   ,-1  ,-3  ,-3 ,
-3  ,1   ,-1  ,-3  ,-3  ,-1  ,1   ,-3  ,-1  ,-3  ,1   ,1   ,-1  ,1   ,1   ,3   ,3   ,3   ,-1  ,1   ,-1  ,1   ,-1  ,-3 ,
-1  ,3   ,-1  ,-1  ,3   ,3   ,-1  ,-1  ,-1  ,3   ,-1  ,-3  ,1   ,3   ,1   ,1   ,-3  ,-3  ,-3  ,-1  ,-3  ,-1  ,-3  ,-3 ,
3   ,-3  ,-3  ,-1  ,3   ,3   ,-3  ,-1  ,3   ,1   ,1   ,1   ,3   ,-1  ,3   ,-3  ,-1  ,3   ,-1  ,3   ,1   ,-1  ,-3  ,-3 ,
-3  ,1   ,-3  ,1   ,-3  ,1   ,1   ,3   ,1   ,-3  ,-3  ,-1  ,1   ,3   ,-1  ,-3  ,3   ,1   ,-1  ,-3  ,-3  ,-3  ,-3  ,-3 ,
3   ,-3  ,-1  ,1   ,3   ,-1  ,-1  ,-3  ,-1  ,3   ,-1  ,-3  ,-1  ,-3  ,3   ,-1  ,3   ,1   ,1   ,-3  ,3   ,-3  ,-3  ,-3 };


void PUCCH_baseSEQ_len18(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid)
/*  generate low-PAPR complex sequence for PUCCH , 
*  reference #1:  subclause 5.2.2.2 (Base sequence of length less than 36) of TR38.211
*  reference #2:  table 5.2.2.2-3 of TR38.211
Change History
*  reference version designed by  Duan Weiming in 2020-05-15
*/
{
    retERR_NEQ(SCnum,18)                 // low-PAPR sequence length 18
    retERR_RNG(GRPid,0,29)              // base sequence Group ID
    retERR_CHK(0 > fAlpha)              // cyclic shift value
    MEMCHK(vfCxVECseq, SCnum*2)
    
    // add your codes here....
    int ilen = 18;   int *piQpskIDS = gviPhi_len18  + GRPid*ilen;
    NRseq_cgsQpsk(vfCxVECseq,piQpskIDS , ilen);

    CxVEC_phaseRotateSTD(vfCxVECseq, vfCxVECseq, ilen,  fAlpha );

}



void PUCCH_baseSEQ_len24(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid)
/*  generate low-PAPR complex sequence for PUCCH , 
*  reference #1:  subclause 5.2.2.2 (Base sequence of length less than 36) of TR38.211
*  reference #2:  table 5.2.2.2-4 of TR38.211
Change History
*  reference version designed by  Duan Weiming in 2020-05-15
*/
{
    retERR_NEQ(SCnum,24)                 // low-PAPR sequence length 6
    retERR_RNG(GRPid,0,29)              // base sequence Group ID
    retERR_CHK(0 > fAlpha)              // cyclic shift value
    MEMCHK(vfCxVECseq, SCnum*2)
    
    // add your codes here....
    int ilen = 24;   int *piQpskIDS = gviPhi_len24  + GRPid*ilen;
    NRseq_cgsQpsk(vfCxVECseq,piQpskIDS , ilen);
    CxVEC_phaseRotateSTD(vfCxVECseq, vfCxVECseq, ilen,  fAlpha );


}


int gviOCC_2[2*2] = {
0, 0, 
0, 1 };

int gviOCC_3[3*3] = {
0, 0, 0,
0, 1, 2,
0, 2, 1 };


int gviOCC_4[4*4] = { 
0, 0, 0, 0,
0, 2, 0, 2,
0, 0, 2, 2,
0, 2, 2, 0 };

int gviOCC_5[5*5] ={
0, 0, 0, 0, 0,
0, 1, 2, 3, 4,
0, 2, 4, 1, 3,
0, 3, 1, 4, 2,
0, 4, 3, 2, 1 };

int gviOCC_6[6*6] = {
0, 0, 0, 0, 0, 0,
0, 1, 2, 3, 4, 5,
0, 2, 4, 0, 2, 4,
0, 3, 0, 3, 0, 3,
0, 4, 2, 0, 4, 2,
0, 5, 4, 3, 2, 1 };

int gviOCC_7[7*7] = {
0, 0, 0, 0, 0, 0, 0, 
0, 1, 2, 3, 4, 5, 6, 
0, 2, 4, 6, 1, 3, 5, 
0, 3, 6, 2, 5, 1, 4, 
0, 4, 1, 5, 2, 6, 3, 
0, 5, 3, 1, 6, 4, 2, 
0, 6, 5, 4, 3, 2, 1};

int gviPUCCH1_OCC[2*11] = {
4 ,5 ,6 ,7 ,8 ,9 ,10,11,12,13,14,
2 ,2 ,3 ,3 ,4 ,4 ,5 ,5 ,6 ,6 ,7 };


int PUCCHformat1_occ(float *vfCxOCC_list, int Maxlen,  int OFDMnum, int OCCid)
/*   
Change History
*  reference version (only support no hopping) designed by Duan Weiming in 2020-05-19
*/
{
    ret0ERR_RNG(OFDMnum,4,14)  ret0ERR_LEZ(Maxlen)  MEMCHK(vfCxOCC_list, Maxlen*2)   ret0ERR_RNG(OCCid,0,7)
    int jjj,iFind; int *piVALs, *piOCC; float fPhiScale, fval; float *pfDST;
    piVALs = gviPUCCH1_OCC;  iFind = -1;
    _LOOPUP_LT(jjj,0, 11) { if( OFDMnum == piVALs[jjj]) { iFind = jjj; break;} }  ret0ERR_LT(iFind, 0)
    
    piVALs = gviPUCCH1_OCC + 11;      int OCClen = piVALs[iFind];  ret0ERR_LT(Maxlen, OCClen)
    if( 2 == OCClen  )      { piOCC = gviOCC_2; }
    else if( 3 == OCClen  ) { piOCC = gviOCC_3; }
    else if( 4 == OCClen  ) { piOCC = gviOCC_4; }
    else if( 5 == OCClen  ) { piOCC = gviOCC_5; }
    else if( 6 == OCClen  ) { piOCC = gviOCC_6; }
    else if( 7 == OCClen  ) { piOCC = gviOCC_7; }
    else   { ret0ERR_RNG(OCClen, 2, 7); }

    piOCC += (OCCid%OCClen)*OCClen; 

    fPhiScale = 2.0*PI/(float)OCClen;
    FLT_ZERO(vfCxOCC_list, Maxlen*2);   pfDST = vfCxOCC_list;
    _LOOPUP_LT(jjj,0, OCClen) { fval = fPhiScale*piOCC[jjj]; *pfDST++ = cos(fval); *pfDST++ = sin(fval); }

    return OCClen;
}



void PUCCHformat1_qam(float *vfCxIQ, int iBIT0, int iBIT11)
/*
Change History
*  1st version designed by Duan Weiming in 2020-05-20
*/
{
    float vfCxQPSK_map[4*2] = { 0.7071, 0.7071, 0.7071, -0.7071, -0.7071, 0.7071, -0.7071, -0.7071};  // 00 , 01, 10, 11
    float vfCxBPSK_map[2*2] = { 1, 0, -1, 0 };                //  0,  1

    float *pfIQmap;
    retERR_RNG(iBIT0,0,1)        if( 0 <= iBIT11 ) { retERR_RNG(iBIT11,0,1) }
    if( 0 <= iBIT11 ) {  pfIQmap =  vfCxQPSK_map + (iBIT11*2 + iBIT0)*2; } // QPSK     
    else              {  pfIQmap =  vfCxBPSK_map + iBIT0*2;              } // BPSK        

    vfCxIQ[0] = *pfIQmap++;
    vfCxIQ[1] = *pfIQmap++;

}


void PUCCHformat1_genSEQ(float *vfCxSEQ_list, int SCnum, int OFDMnum,int iBIT0, int iBIT11,int iSLOTcnt, int GRPid, int OCCid, int CellID)
/*   generate complex sequences  for PUCCH format 1  
Change History
*  reference version (only support no hopping mode) designed by Duan Weiming in 2020-05-19
*/
{
    retERR_LTZ(iSLOTcnt)    retERR_RNG(GRPid,0,30-1)   retERR_RNG(OCCid,0,7)
    retERR_RNG(OFDMnum,4,14)                   // OFDM number 对应文章的PUCCH length 
    //retERR_RNG(Modelnum,1,2)                   // m'   // no hoppoing 
    retERR_LIST(SCnum,6,12,18,24,30)           //对应文章的 N RB sc  
    MEMCHK(vfCxSEQ_list, OFDMnum*SCnum*2)
    
    float fAlpha;  int jjj,OCClen, cntSF, OFDMid, SLOTid, iM_cs;  float vfCxIQ[2], vfCxQam[2];  float *pfDST, *pfCxOCC;

    _NEW_INIT()
    _NEW_FLT0(vfCxOCC_list, 8*2)
    _NEW_FLT0(vfCxSEQ_org,  SCnum*2)

    iM_cs  = 0;
    SLOTid = iSLOTcnt%10;    
    OCClen = PUCCHformat1_occ(vfCxOCC_list,  8,   OFDMnum,  OCCid); // Maxlen = 8
    PUCCHformat1_qam(vfCxQam,  iBIT0,  iBIT11);

    pfDST = vfCxSEQ_list;  cntSF = 0;
    _LOOPUP_LT(jjj, 0, OFDMnum) {
        OFDMid = 14 - OFDMnum +  jjj;
        fAlpha = PUCCH_Alpha( OFDMid,  SLOTid,  iM_cs,  CellID);
        PUCCH_BaseSEQ_ITF(pfDST,  SCnum, fAlpha,  GRPid);
        if( 1 == (jjj%2) ) {  // DMRS is inserted every 2 OFDM symbols
            pfCxOCC = vfCxOCC_list + cntSF*2;      cntSF++;
            _CxAmulCxB(vfCxIQ, vfCxQam, pfCxOCC);
            BlockCxMulCONST(pfDST, pfDST, vfCxIQ[0], vfCxIQ[1], SCnum);
        } 
        pfDST += SCnum*2;
    }
  
    _NEW_FREE()


}         





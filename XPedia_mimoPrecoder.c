
#include "PerfMetric_COMM.h"
#include "XPedia_mimoPrecoder.h"



void   MIMO_precoderRST(float* vfCxPM_SBD, int SubBN, int TxN, int LyrN, int isRandomPM)
/* reset precoding matrix for each sub-band
*  vfCxPM_SBD : precoding matrix for each sub-band
*  SubBN      : number of sub-bands
*  TxN        : number of transmitters
*  LyrN       : number of tx layers (1 or 2)  
Change History 
*  1st version de-coupled from MIMO_precoder() by Duan Weiming in 2021-03-18
*/
{

    retERR_LEZ3(SubBN,TxN,LyrN)    retERR_RNG(LyrN,1,2)
    int LyrTX = TxN/LyrN;          retERR_NEQ(LyrTX*LyrN,  TxN)       int jjj,cnt;    float *pfDST;

    MEMCHK(vfCxPM_SBD, SubBN*TxN*LyrN*2) 


    _NEW_INIT()   _NEW_FLT0(vfCxLYRs, LyrN*2)    _NEW3_FLT0(vfRVs, vfsin, vfcos, SubBN*TxN*LyrN)  

    if( isRandomPM ) {
        VEC_rand(vfRVs, SubBN*TxN*LyrN, 0, _2PI_);
        VEC_sincos(vfsin, vfcos, vfRVs, SubBN*TxN*LyrN);
        pfDST = vfCxPM_SBD;  _LOOPUP_LT(jjj,0, SubBN*TxN*LyrN) {  *pfDST++ = vfcos[jjj];  *pfDST++ = vfsin[jjj];   }
        int iTST = 3;


    }  else {
        _LOOPUP_LT(cnt, 0, LyrN) {  
            FLT_ZERO(vfCxLYRs, LyrN*2); vfCxLYRs[cnt*2] = 1.0; 
            CxVEC_clone(vfCxPM_SBD + cnt*LyrTX*LyrN*2, vfCxLYRs, LyrN, LyrTX); 
        }
        if(1 < SubBN) { CxVEC_clone(vfCxPM_SBD + TxN*LyrN*2, vfCxPM_SBD, TxN*LyrN, SubBN-1);   }
    }

    _NEW_FREE()


}


void MIMO_precoder(float *vfCxSCV_TX,float *vfCxPM_SBD, float *vfCxSCs_lyr,   int TxN, int LyrN , int SubBN, int RBnum, int OFDMnum, int isPMok)
/*
Change History
*  1st version designed by Duan Weiming in 2020-12-16
*/
{
    int SCnum = RBnum*12;           retERR_LEZ5( TxN, LyrN, SubBN, RBnum, OFDMnum)          
    int SubBSC = RBnum*12/SubBN;    retERR_NEQ(SubBSC*SubBN, RBnum*12)  
    //int LyrTX = TxN/LyrN;           retERR_NEQ(LyrTX*LyrN,  TxN)

    MEMCHK(vfCxSCV_TX,  OFDMnum*SCnum*TxN*2)       MEMCHK(vfCxSCs_lyr, OFDMnum*SCnum*LyrN*2)     MEMCHK(vfCxPM_SBD,  SubBN*TxN*LyrN*2)


    //float fScale = _DIVOP(1, TxN);  fScale = sqrt(fScale);
    int cnt,iOFDM,jjj;    float *pfPM, *pfHs, *pfHO;      float fScale = 1.0;  
    if( 0 ==  isPMok) {  
        //MIMO_precoderRST( vfCxPM_SBD, SubBN, TxN,  LyrN);   // this row may have problem, removed , why???   commented by Duan Weiming in 2021-03-19
        //_NEW_INIT()   _NEW_FLT0(vfCxLYRs, LyrN*2)
        //_LOOPUP_LT(cnt, 0, LyrN) {  FLT_ZERO(vfCxLYRs, LyrN*2); vfCxLYRs[cnt*2] = 1.0; CxVEC_clone(vfCxPM_SBD + cnt*LyrTX*LyrN*2, vfCxLYRs, LyrN, LyrTX); }
        //if(1 < SubBN) { CxVEC_clone(vfCxPM_SBD + TxN*LyrN*2, vfCxPM_SBD, TxN*LyrN, SubBN-1);   }
        //_NEW_FREE()
    }

    
    _LOOPUP_LT(cnt, 0, SubBN) {
        pfPM = vfCxPM_SBD + cnt*TxN*LyrN*2;
        _LOOPUP_LT(iOFDM, 0, OFDMnum) {
            pfHs = vfCxSCs_lyr + iOFDM*SCnum*LyrN*2 + cnt*SubBSC*LyrN*2;
            pfHO = vfCxSCV_TX  + iOFDM*SCnum*TxN*2  + cnt*SubBSC*TxN*2;
            CxMats_mulFixA(pfHO, pfPM, pfHs, TxN, LyrN, 1, SubBSC);
        }
    }

}



float MIMO_precodingH(float *vfCxSCH_O, float *vfCxSCH_s, float *vfCxPM_SBD , int RxM,  int TxN, int LyrN , int SubBN, int RBnum, int OFDMnum)
/*
Change History
*  1st version designed by Duan Weiming in 2020-12-03
*/
{
    ret0ERR_LEZ6(RxM, TxN, LyrN, SubBN, RBnum, OFDMnum)   int SCnum = RBnum*12;               int SubBSC = RBnum*12/SubBN;       ret0ERR_NEQ(SubBSC*SubBN, RBnum*12)  
    ret0ERR_LIST(TxN,1,2,4,8,16,32,48,64,128)             ret0ERR_LIST(RxM,1,2,4,8,16,32,64)  ret0ERR_RNG(LyrN, 1, 8)            ret0ERR_RNG(RBnum, 4, 100)     

    MEMCHK(vfCxSCH_O, OFDMnum*SCnum*RxM*LyrN*2)
    MEMCHK(vfCxSCH_s, OFDMnum*SCnum*RxM*TxN*2)
    MEMCHK(vfCxPM_SBD, SubBN*TxN*LyrN*2)

    int cnt,iOFDM,jjj;    float *pfPM, *pfHs, *pfHO;
    _LOOPUP_LT(cnt, 0, SubBN) {
        pfPM = vfCxPM_SBD + cnt*TxN*LyrN*2;
        _LOOPUP_LT(iOFDM, 0, OFDMnum) {
            pfHs = vfCxSCH_s + iOFDM*SCnum*RxM*TxN*2  + cnt*SubBSC*RxM*TxN*2;
            pfHO = vfCxSCH_O + iOFDM*SCnum*RxM*LyrN*2 + cnt*SubBSC*RxM*LyrN*2;
            CxMats_mulFixB(pfHO, pfHs, pfPM, RxM, TxN, LyrN, SubBSC);
        }
    }
    float fAvgEs = CxVEC_sumpwr(vfCxSCH_O, OFDMnum*SCnum*RxM*LyrN);

    fAvgEs = fAvgEs/float(OFDMnum*SCnum*RxM);

    return fAvgEs;


}







void CxVEC_quantizePHS(float *vfCxVEC_O,  float *vfCxVEC_S, int Vlen, int BITnum)
/* Quantize the angle of complex vector
Change History
*  1st version designed by Duan Weiming in 2020-12-20
*/
{
    int jjj;  float *pfDST;
    retERR_LTZ(BITnum)  retERR_LEZ(Vlen)   MEMCHK2(vfCxVEC_O, vfCxVEC_S, Vlen*2)
    if( 0 == BITnum ) { if( vfCxVEC_S != vfCxVEC_O) { FLT_CP(vfCxVEC_S, vfCxVEC_O, Vlen*2); }  return; }

    int Qn = (1 << BITnum);   float fstep = _2PI_/(float)Qn;

    _NEW_INIT()   _NEW_FLT0(vfCxREFs, Qn*2)  _NEW3_FLT0(vfPHSs,vfsin,vfcos, Qn)
    VEC_step(vfPHSs, 0, fstep, Qn);
    VEC_sincos(vfsin, vfcos, vfPHSs, Qn);
    pfDST = vfCxREFs;        _LOOPUP_LT(jjj,0, Qn) { *pfDST++ = vfcos[jjj];  *pfDST++ = vfsin[jjj];   }

    CxVEC_quant(vfCxVEC_O, vfCxVEC_S,  Vlen, vfCxREFs, Qn);

    _NEW_FREE()



}



void MIMO_precoderTyII(float *vfCxPM_SBD , float *vfCxHs_list, int TXAntR, int TXAntC, int iNUM, float *pfCxHvecs, float *pfCxVvecs)
/*
Change History
*  1st version designed by Duan Weiming in 2020-12-20
*/
{
    int QuantBITS = 4;
    int cnt,jjj;   float *pfSRC, *pfDST, *pfSRC0, *pfDST0, *pfPM;
    retERR_LEZ3(TXAntR, TXAntC, iNUM)        MEMCHK(vfCxPM_SBD, iNUM*TXAntR*TXAntC*2)         MEMCHK(vfCxHs_list, iNUM*TXAntR*TXAntC*2)
    nzMEMCHK(pfCxHvecs, iNUM*TXAntC*2)
    nzMEMCHK(pfCxVvecs, iNUM*TXAntR*2)

    _NEW_INIT()     
    _NEW3_FLT0(vfCxHs_norm,  vfCxVs_H,   vfCxVs_V , iNUM*TXAntR*TXAntC*2)      _NEW_FLT0(vfAmps, iNUM*TXAntR*TXAntC)
    _NEW_FLT0(vfCxVavg_H,  TXAntC*2)
    _NEW_FLT0(vfCxVavg_V,  TXAntR*2)

    CxVEC_norm(vfCxHs_norm,  vfCxHs_list, iNUM*TXAntR*TXAntC, vfAmps);

    
    _LOOPUP_LT(cnt,0, iNUM) {
        pfPM  = vfCxPM_SBD  + cnt*TXAntR*TXAntC*2;
        pfSRC = vfCxHs_norm + cnt*TXAntR*TXAntC*2;    pfSRC0 = pfSRC;
        pfDST = vfCxVs_H    + cnt*TXAntR*TXAntC*2;    pfDST0 = pfDST;
        _LOOPUP_LT(jjj, 0, TXAntR) {  CxVEC_mulC(pfDST0, pfSRC0, TXAntC, pfSRC0[0], -1.0*pfSRC0[1] ); pfSRC0 += TXAntC*2; pfDST0 += TXAntC*2; }
        CxVECs_avg(vfCxVavg_H, pfDST, TXAntC, TXAntR);
        if(pfCxHvecs) { FLT_CP(vfCxVavg_H, pfCxHvecs + cnt*TXAntC*2, TXAntC*2);   }

        _CxVEC_conj(vfCxVavg_H, TXAntC);
        CxVEC_quantizePHS(vfCxVavg_H, vfCxVavg_H, TXAntC,QuantBITS);

        CxMat_tranposeS(pfSRC, TXAntR,TXAntC);        pfSRC0 = pfSRC;
        pfDST = vfCxVs_V    + cnt*TXAntR*TXAntC*2;    pfDST0 = pfDST;
        _LOOPUP_LT(jjj, 0, TXAntC) {  CxVEC_mulC(pfDST0, pfSRC0, TXAntR, pfSRC0[0], -1.0*pfSRC0[1] ); pfSRC0 += TXAntR*2; pfDST0 += TXAntR*2; }

        CxVECs_avg(vfCxVavg_V, pfDST, TXAntR, TXAntC);
        if(pfCxVvecs) { FLT_CP(vfCxVavg_V, pfCxVvecs + cnt*TXAntR*2, TXAntR*2);   }
        _CxVEC_conj(vfCxVavg_V, TXAntR);
        CxVEC_quantizePHS(vfCxVavg_V, vfCxVavg_V, TXAntR,QuantBITS);

        CxMat_mul(pfPM , vfCxVavg_V, vfCxVavg_H, TXAntR, 1, TXAntC );

    }

    _NEW_FREE()

}

/*
exec(open('PY3ITF_mmimo.py').read());  crcBITS=6120+24; PUSCH_corelink(5.0,crcBITS-24,10,64,100*50,30.0,3,1);    # 10RB+64QAM
....BLER=0.28880@EsN0=5.00dB:16.32dB...NetTBS=1736~7480@QamNUM=1440..ModuType=16~64...avgSE=3.450029..TPmbps=4.968042...1444@5000TTIs...67.06seconds
(0.2888, 16.319265365600586, 1444, 5000, 3.4500288888887645)

....BLER=0.28000@EsN0=5.00dB:16.43dB...NetTBS=1736~7480@QamNUM=1440..ModuType=16~64...avgSE=3.503947..TPmbps=5.045683...1400@5000TTIs...66.01seconds
(0.28, 16.429792642593384, 1400, 5000, 3.503946666666541)

*/


void  MIMO_precoderTypeII(float *vfCxPM_SBD , float *vfCxSCH_s,  int RxM,  int TxN, int LyrN , int SubBN, int RBnum, int TXAntC, int TXxplN, int  isRECsamples)
/*
Change History
*  1st version designed by Duan Weiming bwt. 12-03 and 12-09, 2020
*  modified to support ~4 laysers, by Duan Weiming in 2021-03-14
*/
{
    int cnt,iOFDM,jjj, SampN;           float *pfPM, *pfHs, *pfHO;      int MaxD = MAXOP(RxM, TxN);   //int  isRECsamples = 1;   // record precoder samples

    retERR_LIST(TXxplN,1,2)
    retERR_LEZ6(RxM, TxN, LyrN, SubBN, RBnum,TXAntC)  int SCnum = RBnum*12;                  int SubBSC = RBnum*12/SubBN;         retERR_NEQ(SubBSC*SubBN, RBnum*12)  
    retERR_LIST(TxN,1,2,4,8,16,32,48,64,128)          retERR_LIST(RxM,1,2,4,8,16,32,64)      retERR_RNG(LyrN, 1, MINOP(RxM,TxN))  retERR_RNG(RBnum, 4, 100)     
    int TXAntR = TxN/(TXxplN*TXAntC);                 retERR_NEQ(TxN, TXxplN*TXAntR*TXAntC)

    MEMCHK(vfCxSCH_s, SCnum*RxM*TxN*2)        
    MEMCHK(vfCxPM_SBD, SubBN*TxN*LyrN*2)  

    _NEW_INIT()       
    _NEW_FLT0(vfCxMavg, MaxD*MaxD*2)              _NEW2_FLT0(vfCxM_U,vfCxM_Vt, MaxD*MaxD*2)  _NEW_FLT0(vfDiagS, MaxD)
    _NEW_FLT0(vfCxHvecs, SubBN*TXxplN*TXAntC*2)   _NEW_FLT0(vfCxPMmem, TxN*LyrN*2)
    _NEW_FLT0(vfCxVvecs, SubBN*TXxplN*TXAntR*2)

    float *pfHvecs = vfCxHvecs;
    float *pfVvecs = vfCxVvecs;
    _LOOPUP_LT(cnt, 0, SubBN) {
        pfPM = vfCxPM_SBD + cnt*TxN*LyrN*2;
        pfHs = vfCxSCH_s  + cnt*SubBSC*RxM*TxN*2;
        //CxMats_selfcovavg(vfCxMcovavg, pfHs, RxM, TxN, SubBSC,  1);  //  isConjAmulA = 1 ==> (Hs)'*Hs
        CxVECs_avg(vfCxMavg, pfHs, RxM*TxN, SubBSC);
        //MIMO_precoderTyII(pfPM, pfHs, TXAntR,TXAntC,TXxplN, pfHvecs, pfVvecs); // a bug !!!  pfHs==>vfCxMavg, modified by Duan Weiming in 2020-02-22
        if(1 == LyrN) {  MIMO_precoderTyII(pfPM, vfCxMavg, TXAntR,TXAntC,TXxplN, pfHvecs, pfVvecs); }     // TxN = TXAntR*TXAntC*TXxplN
        else if(4 >= LyrN) {  // (2 == LyrN)  ==>  (4 >= LyrN)
            //ERR_CHK( 2 != TXxplN )
            MIMO_precoderTyII(vfCxPMmem, vfCxMavg, TXAntR,TXAntC,1, pfHvecs, pfVvecs);
            CxMat_fillDiag(pfPM, TXAntR*TXAntC*LyrN, LyrN, vfCxPMmem, TXAntR*TXAntC, 1);  // 2 ==> LyrN, modified to support ~4 laysers, by Duan Weiming in 2021-03-14
        }
        else { ERR_CHK( 4 < LyrN)  } // ( 2 < LyrN ) ==> ( 4 < LyrN )


        pfHvecs += TXxplN*TXAntC*2;
        pfVvecs += TXxplN*TXAntR*2;

    }
    if( isRECsamples ) {    // recording precoder samples for offline analysis , commented by Duan Weiming in 2021-03-13
        int Row  = TXAntR;  _STRx(Row)   
        int Col  = TXAntC;  _STRx(Col)
        int SubB = SubBN;   _STRx_(SubB)
        int xpl  = TXxplN;  _STRx_(xpl)
        STR_new(strlabelH, "CxHvecs_", _STR(SubB), _STR(xpl) , _STR(Col));
        STR_new(strlabelV, "CxVvecs_", _STR(SubB), _STR(xpl) , _STR(Row));
        SampN = gMEM_dump(strlabelH,  vfCxHvecs, SubBN*TXxplN*TXAntC*2, 100,isRECsamples);
        SampN = gMEM_dump(strlabelV,  vfCxVvecs, SubBN*TXxplN*TXAntR*2, 100,isRECsamples);
        if( 99 == SampN ) {
            int iTST = 3;
        }
        
    }
    

    _NEW_FREE()

}


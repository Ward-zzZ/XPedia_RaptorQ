
#include "PerfMetric_COMM.h"
//#include "RadioSignalBase.h"
#include "XPedia_mimo.h"

#include "XPedia_mimoMLD.c"
#include "XPedia_mimoMLDideal.c"
#include "XPedia_mimoPrecoder.c"




void MIMO_layerSPLIT(float *vfData_O,  float *vfData_S,  int LyrSIZE, int SCnum, int LyrNUM)
/*
Change History
*  1st version designe by Duan Weming in 2020-10-05
*/
{
    retERR_LEZ3(LyrSIZE, SCnum, LyrNUM)   MEMCHK2(vfData_S, vfData_O, SCnum*LyrNUM*LyrSIZE)   retERR_LIST(LyrSIZE, 1,2,4,6,8)    
    if( 1 == LyrNUM ) {
        if( vfData_S != vfData_O ) { FLT_CP(vfData_S, vfData_O, SCnum*LyrNUM*LyrSIZE); }
        return;
    }


    _NEW_INIT()    _NEW_FLT0(vfMEM, SCnum*LyrNUM*LyrSIZE)     int jjj,kkk,cnt;  float *pfDST, *pfSRC;


    _LOOPUP_LT(cnt, 0, LyrNUM) {
        pfDST = vfMEM    + cnt*SCnum*LyrSIZE;
        pfSRC = vfData_S + cnt*LyrSIZE;
        _LOOPUP_LT(jjj, 0, SCnum) {
            _LOOPUP_LT(kkk, 0, LyrSIZE) { *pfDST++ = pfSRC[kkk]; }
            pfSRC +=  LyrSIZE * LyrNUM;
        }
    }
    FLT_CP(vfMEM ,  vfData_O,  SCnum*LyrNUM*LyrSIZE);

    _NEW_FREE()
}




void MIMO_equalizer(float *vfllrs, float *vfCxRscs_list, float *vfCxH_scs, int RxM, int TxN, int SCnum , int ModuType, float fNoisePwr, int isLMMSE, int DOFDMnum)
/*
Change History
*  1st version designed by Duan Weiming in 2020-09-16
*  support both 1 layer and 2 layers, by Duan Weiming in 2020-10-21
*  support equalizer wo. deQam if ModuType is 0, by Duan Weiming in 2021-01-23
*/
{
    

    retERR_LEZ4(RxM,TxN,SCnum,DOFDMnum)    float *pfWGH, *pfSRC,*pfDST, *pfLLR,*pfRsc;     int jjj;      
    retERR_RNG(TxN,1,4)                    retERR_LT(RxM,TxN)            retERR_LTZ(fNoisePwr)         retERR_LIST(ModuType,0,2,4,16,64,256)     
    int HSize = RxM*TxN;                   int SubBnum = SCnum/12;       retERR_NEQ(SubBnum*12 , SCnum)       
    int QAMnum = DOFDMnum*SCnum*TxN;       int QAMsize = 2;              if(0 < ModuType) { QAMsize =  _GET_QamBITS(ModuType); }                
    
    MEMCHK(vfCxH_scs, SCnum*RxM*TxN*2)   MEMCHK(vfCxRscs_list, DOFDMnum*SCnum*RxM*2)  MEMCHK(vfllrs, QAMnum*QAMsize)  


    if( 0 == isLMMSE ) {    
        retERR_NEQ(RxM, TxN)   retERR_NEQ(TxN,2)
        _LOOPUP_LT(jjj,0,DOFDMnum ) {  // equlization using LMMSE weights
            pfRsc = vfCxRscs_list + jjj*SCnum*RxM*2;
            pfLLR = vfllrs        + jjj*SCnum*TxN*QAMsize;
            MIMO2x2_MLDideal(pfLLR, pfRsc, vfCxH_scs,  SCnum , ModuType, fNoisePwr );        
        }                        
        return; 
    }

    _NEW_INIT()
    _NEW_FLT0(vfCxSubB_Rvv,  SubBnum*RxM*RxM*2)
    _NEW_FLT0(vfCxSCwghlist, SCnum*HSize*2)  
    _NEW_FLT0(vfCxQams,      DOFDMnum*SCnum*TxN*2)

    CLAIM_VEC(2,vfCxDiag, 1.0,0.0);    vfCxDiag[0] = fNoisePwr;
    pfSRC = vfCxSubB_Rvv;  pfDST = vfCxSubB_Rvv;
    if( 0 < fNoisePwr ) {  _LOOPUP_LT(jjj,0,SubBnum)  {  CxMats_addDiagC(pfDST, pfSRC, vfCxDiag, RxM, 1);  pfSRC += RxM*RxM*2;  pfDST += RxM*RxM*2;}  }
    //else                {  DMRS_SubBrvv(vfCxSubB_Rvv, vfCxDMRS_list, vfCxSEQs_org,  vfCxH_scs, RxM,  SCnum,  SubBnum,  DMRSnum);   }


    LMMSE_Wgh_ORG(vfCxSCwghlist , vfCxH_scs, vfCxSubB_Rvv ,  RxM, TxN, SCnum, SubBnum);
    pfWGH = vfCxSCwghlist;   
    _LOOPUP_LT(jjj,0,DOFDMnum ) {  // equlization using LMMSE weights
        pfSRC = vfCxRscs_list + jjj*SCnum*RxM*2;
        pfDST = vfCxQams      + jjj*SCnum*TxN*2;       // TxN>0

        CxMats_mul(pfDST,pfWGH,pfSRC,TxN,RxM,1,SCnum);
    } 

    if(0 == ModuType ) {  FLT_CP(vfCxQams,vfllrs, QAMnum*QAMsize);   }
    else               {  CxVEC_qamDemod(vfllrs, vfCxQams,  QAMnum,  ModuType,  0.5*fNoisePwr);  }             



    int iTST = 3;   

    _NEW_FREE()



    //svCxM("hh", vfCxH2x2_sc, 56, 4);
    

    /*

    _NEW_INIT()                         _NEW_FLT0(vfCxRvv, RxM*RxM*2)           _NEW_FLT0(vfCxSC_wgh, SCnum*LyrN*RxM*2)   
    _NEW_FLT0(vfQams_sc, SCnum*LyrN*2)  _NEW_FLT0(vfCxH_sc,SCnum*RxM*LyrN*2)    _NEW_FLT0(vfCxR1_sc,  SCnum*2)            _NEW2_FLT0(vfCxHmem0, vfHmem1, 2*56*2)


    float *vfCxHs = vfCxH2x2_sc;  int RxMnew = RxM;  float *vfCxR_sc = vfCxR2_sc;
    if(LyrN < TxN) {    // added to support one layer!!! , by Duan Weiming in 2020-02-21
        vfCxHs = vfCxH_sc;   ERR_CHK(1 != LyrN)
        CxVECs_innerSum(vfCxHs, vfCxH2x2_sc, TxN, SCnum*RxM, 1.0);

        //int  viPickCOL2[2]= {1,3}; CxMat_colsPick(vfCxHs, vfCxH2x2_sc, SCnum, 4,2, viPickCOL2);  // it works!!!
        if( 0 >  isLyrSPLIT ) {
            int iPICK = -1*isLyrSPLIT - 1;
            CxMat_cols(vfCxR1_sc,  vfCxR2_sc,   SCnum, 2, iPICK, 1);  vfCxR_sc = vfCxR1_sc;

            CxMat_cols(vfCxHmem0,     vfCxH2x2_sc, 56, 4, iPICK*2, 2);  RxMnew = 1;
            CxMat_tranpose(vfCxHmem0, vfCxHmem0, 56, 2);
            CxVECs_fft(vfCxHmem0,vfCxHmem0, 56, 2);
            CxVEC_pwr(vfHmem1, vfCxHmem0, 56*2);
            int viMAXpos[2];  float vfMAXval[2];
            VECs_max(viMAXpos, vfMAXval, vfHmem1, 56,2);
            int iTxID = 0;  if( vfMAXval[1] > vfMAXval[0]) { iTxID = 1; }            
            CxMat_cols(vfCxHs,     vfCxH2x2_sc, SCnum, 4, iPICK*2 + iTxID, 1);  RxMnew = 1;
        }
    }
    

    CLAIM_FLT(vfCxNoise,2)  vfCxNoise[0] = fNoisePwr;  vfCxNoise[1]=  0;
    CxMats_addDiagC(vfCxRvv,vfCxRvv, vfCxNoise, RxMnew, 1);
    
    LMMSE_Wgh_ORG(vfCxSC_wgh, vfCxHs, vfCxRvv,  RxMnew, LyrN,  SCnum,  SubBnum); // vfCxH2x2_sc ==> vfCxHs
    
    CxMats_mul(vfQams_sc, vfCxSC_wgh,vfCxR_sc,LyrN,RxMnew,1, SCnum);
    if(isLyrSPLIT && (1 < LyrN) ) {  MIMO_layerSPLIT(vfQams_sc,  vfQams_sc,  2,  SCnum, LyrN);  }

    //int   viDMRSpos[4]   = {7,21,34,48};      float vfCxDMRSseq[8] = {1,0, -1,0,  1,0,  1,0};  int AVGlen = 10;
    //OFDM_commFerrFIX(vfQams_sc, 56,   OFDMnum,   AVGlen, 4, viDMRSpos, vfCxDMRSseq);
    //svCxM("QQ", vfQams_sc, 1, QAMnum);

    if(0 < ModuType) { CxVEC_qamDemod(vfllrs, vfQams_sc,  QAMnum,  ModuType,  fNoisePwr); }
    else             { FLT_CP(vfQams_sc, vfllrs, QAMnum*QAMsize); }                        // added to support equalizer wo. deQam if ModuType is 0, by Duan Weiming in 2021-01-23

    //if( 1 == isLMMSE ) { CxVEC_qamDemod(vfllrs, vfQams_sc,  QAMnum,  ModuType,  fNoisePwr); }
    //else               { FLT_CP(vfQams_sc, vfllrs, QAMnum*2);  } 
    _NEW_FREE()
    int iTST = 3;
    */

}

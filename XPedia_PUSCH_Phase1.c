


#include "XPedia_Uplink.h"




/*  This function implements channel estimation and return estimated average SNR in dB
Change History
*  1st version designed by ??? (supervised by Zhang Weizheng & Duan Weiming ) in 2020-05
*/
/*
float NRcest_dmrs(float *vfCxDMRSfading_list, float  *vfCxDMRSsig_list, float *vfCxSEQs_list, int RXnum,  int SCnum, int DMRSnum)
{
    ret0ERR_LEZ3(RXnum, SCnum, DMRSnum)   MEMCHK3(vfCxDMRSsig_list,vfCxDMRSfading_list,vfCxSEQs_list, DMRSnum*SCnum*RXnum*2)  
    float fSNR_dB;

    // add your codes here !!!


    return fSNR_dB;

} */



void NRcest_2DInterp(float *vfCxDATAfadings_list,  float *vfCxDMRSfading_list, int RXnum, int SCnum, int DMRSnum, int DOFDMnum)
/* This function calcs fadings of data OFDMS symbols by using DMRS fadings
Change History
*  1st version designd by ??? (supervised by Zhang Weizheng & Duan Weiming ) in 2020-05
*/
{
    retERR_LEZ2(RXnum, SCnum)   retERR_NEQ(DMRSnum,2)   retERR_NEQ(DOFDMnum,12)    
    MEMCHK(vfCxDMRSfading_list,  DMRSnum*SCnum*RXnum*2)
    MEMCHK(vfCxDATAfadings_list, DOFDMnum*SCnum*RXnum*2)

    // add your code here !!!


}


float NRmeas_QamSNR(float  *vfCxQams_equalizer,   float *vfCxQams_org,  int QAMnum)
/*  This function calcs  ideal SNR using tx qams and equalized qams
Change History
*  1st version designd by ??? (supervised by Zhang Weizheng & Duan Weiming ) in 2020-05
*/
{
    ret0ERR_LEZ(QAMnum)    MEMCHK2(vfCxQams_org, vfCxQams_equalizer, QAMnum*2)
    float fSNR_dB;

    // add your code here !!!


    return fSNR_dB;

}



void NRofdm_equalizer(float *vfCxQams,  int SCnum, int RXport, int TXport, float *vfCxSCsrc_list,float *vfCxSEQs_org,  float fNoisePwr, float *vfCxHice_list, int ModuType, int isLMMSE)
/*
Change History
*  reference version designed by Duan Weiming in 2020-03-24
*  support lmmse with 1~4 layers, and ideal MLD 2x2 decoder, by Duan Weiming in 2021-01-23
*  support 2~4 layer QR-MLD, added by Duan Weiming in 2021-04-10
*/
{
    
    int DMRSnum = 2;      int DOFDMnum = 12;        int OFDMnum = DOFDMnum + DMRSnum;    retERR_LIST(RXport, 1, 2,4,8,16)   retERR_LIST(TXport, 1,2,3,4) 
    int isDL = 0;         int SubBnum  = SCnum/12;  int HSize = RXport*TXport;           
    int QAMsize = 2;      // lmmse only outputs IQ !!!  
    //if( 0 < ModuType) { retERR_LIST(ModuType,2,4,16,64,256)   QAMsize = _GET_QamBITS(ModuType);  }   // removed by Duan Weiming in 2020-04-10
    if( 0 == isLMMSE ) { retERR_NEQ(RXport,TXport)   retERR_LT(TXport,2)  retERR_LIST(ModuType,2,4,16,64,256)   QAMsize = _GET_QamBITS(ModuType);   }   // support NxN QRMLD only now, added by Duan Weiming in 2021-04-10

    retERR_LEZ(SCnum)     MEMCHK(vfCxSCsrc_list, OFDMnum*SCnum*RXport*2)   MEMCHK(vfCxQams, DOFDMnum*SCnum*TXport*QAMsize)
    int jjj;  float *pfSRC, *pfDST, *pfWGH;       

    _NEW_INIT()
    _NEW_FLT0(vfCxDMRS_list, DMRSnum*SCnum*RXport*2)    
    _NEW_FLT0(vfCxDATA_list, DOFDMnum*SCnum*RXport*2)
    _NEW_FLT0(vfCxHscs_list, DMRSnum*SCnum*HSize*2)

    LTEofdm_disassemble(vfCxDATA_list, vfCxDMRS_list, vfCxSCsrc_list, SCnum, RXport, isDL);  //  get data ofdm symbols and dmrs symbols
    LTEofdm_disassemble(0, vfCxHscs_list, vfCxHice_list, SCnum, HSize, isDL);                //  get ideal channel etstimation !!!   RXport==>HSize, modified by Duan Weiming in 2021-01-23

    int DOFDMhlf = (DOFDMnum>>1);  float *pfQAMs,*pfCxRX, *pfCxHs;
    _LOOPUP_LT(jjj,0, DMRSnum) {   // calc LMMSE weights
        pfQAMs = vfCxQams      + jjj*DOFDMhlf*SCnum*TXport*QAMsize;
        pfCxRX = vfCxDATA_list + jjj*DOFDMhlf*SCnum*RXport*2;
        pfCxHs = vfCxHscs_list + jjj*SCnum*HSize*2;
        //MIMO_equalizer(float *vfllrs, float *vfCxRscs_list, float *vfCxH_scs, int RxM, int TxN, int SCnum , int ModuType, float fNoisePwr, int isLMMSE, int DOFDMnum)
        //QRMLD_mimoDEC(float *vfLLRS, float* vfCxR_list, float* vfCxH_list, int Dim, int ModuType, int SCnum, float fNoisePwr)
        if(0 == isLMMSE) {   // added by Duan Weiming in 2021-04-10
            MIMO_equalizer(pfQAMs,  pfCxRX, pfCxHs, RXport, TXport,  SCnum , ModuType, fNoisePwr, 1, DOFDMhlf); // for testing !!                             
            MIMO_mldDec_ITF(pfQAMs, pfCxRX, pfCxHs,  TXport,  ModuType, SCnum , fNoisePwr, DOFDMhlf);          // QR-Mld testing !!!   

            //QRMLD_mimoDEC( pfQAMs, pfCxRX, pfCxHs,  TXport,  ModuType, SCnum , fNoisePwr, DOFDMhlf);         // for comparison!!
        }  
        else             { MIMO_equalizer(pfQAMs, pfCxRX, pfCxHs, RXport, TXport,  SCnum , 0, fNoisePwr, isLMMSE, DOFDMhlf); }  // ModuType=0 ==> output equalized Qam IQ, not llr!!!, modified by Duan Weiming in 2021-04-10

    }


    _NEW_FREE()


}
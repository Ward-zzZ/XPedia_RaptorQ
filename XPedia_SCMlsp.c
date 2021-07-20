
#include "PerfMetric_COMM.h"
#include "XPedia_SCMlsp.h"

const char* strSCENAlist[4] = {"eSCENA_Umi","eSCENA_Uma","eSCENA_Rma","eSCENA_InH" };    

void   SCM3Dnet_DLSirCDF(float* vfCxCDF, int CDFlen,  float* vfMatGains, int UserN, int iSCENAcase)
/* calculate SIRs cdf in a hexagonal network
*  vfCxCDF         : CDF data { sir0, cdf0, sir1, cdf1, ... }
*  CDFlen          : length of CDF
*  vfMatGains      : the propagation gain matrix ( user_number * 57_cells)
*  UserN           : total number of users
*  iSCENAcase      : 0: eSCENA_Umi, 1:  eSCENA_Uma, 2: eSCENA_Rma, 3: eSCENA_InH
Change History 
*  1st version designed by Duan Weiming in 2021-04-21
*/
{
    
    int ccc, uuu,jjj,cnt,iSID,iPOS; float fGain0, fSigPwr, fInterf, fOffsetDB; float *pfGainDB;

    retERR_RNG(iSCENAcase, 0,3)     retERR_LEZ2(CDFlen,UserN)  
    MEMCHK(vfCxCDF, CDFlen*2)       MEMCHK(vfMatGains, UserN*57)       //MEMCHK(viUsrCIDs, UserN)  

    float vfBSTxPs[4]   = { 44,  49,  49 ,  24  };  // BS tX psd(dBm@20MHz) :            Umi,Uma,Rma,InH 
    float fTXPWR_20MHz  = vfBSTxPs[iSCENAcase];

    float fTXPWRpsd_dB = fTXPWR_20MHz - 10*log10(20.0e6);   //float fTXPWRpsd_dB = 43.0 - 10*log10(18.0e6);
    float fNoisepsd_dB = -174 + 9;                // UT noise figure = 9dBi    
    

    _NEW_INIT() _NEW_FLT0(vfUsrGainV, 57)   _NEW_FLT0(vfSIRs, UserN)     

    _LOOPUP_LT(cnt, 0, UserN) { // for each user        
        pfGainDB  = vfMatGains + cnt*57;
        //iSID      = viUsrCIDs[cnt];
        //fGain0    = pfGainDB[iSID];        
        FLT_CP(pfGainDB,  vfUsrGainV, 57);  
        VEC_addC(vfUsrGainV, 57, fTXPWRpsd_dB - fNoisepsd_dB );
        VEC_mulC(vfUsrGainV, 57, 0.1);   
        VEC_pow10(vfUsrGainV, vfUsrGainV, 57);
        fSigPwr   = VEC_max(&iPOS,vfUsrGainV,57);   
        //if( iPOS != iSID ) {
        //    ERR_NEQ(iPOS, iSID) //fSigPwr   = vfUsrGainV[iSID];    // the same !!!
        //}
        fInterf   = VEC_sum(vfUsrGainV, 57) - fSigPwr + 1.0;  // 1.0 is thermal noise w.r.t 9dBi noise figure!!
        vfSIRs[cnt] = fSigPwr/fInterf;
    }
    
    _LOOPUP_LT(jjj,0, UserN) {  vfSIRs[jjj] = 10*log10(vfSIRs[jjj]);  }  //VEC_10log10(vfSIRs, vfSIRs, UserN);
    PDF_gen( vfCxCDF, vfSIRs, UserN, -10.0, 30.0,  CDFlen, 1, 1);

    GET_GPARAM_INT(gSCM3D_CalibP1_VShapingN)    _STRn(gSCM3D_CalibP1_VShapingN)   char strBUF[200];     
    STR_catX(strBUF, strSCENAlist[iSCENAcase] ,"M",_STR(gSCM3D_CalibP1_VShapingN),"_","CDF_sirs");
    dumpCxM( strBUF , vfCxCDF, 1, CDFlen);

    _NEW_FREE() 

}



float   SCM3Dnet_getCellusers(int* viCell_UserNUN, int* viCell_UserIDs, float* vfMatGains, int UserN, int MaxU, float* vfServCLs, int *viO2I_IDs)
/* grouping users into their servering cell according to coupling loss matrix
*  viCell_UserNUN : number of serving users for each cell
*  viCell_UserIDs : list of serving users IDs for each cell
*  vfMatGains     : coupling loss btw. each user and 57 cells (size
*  UserN          : total number of users
*  MaxU           : max number of serving users in a cell
Change History 
*  1st version designed by Duan Weiming in 2021-05-11
*/
{

    ret0ERR_LEZ2(UserN,MaxU)                ret0ERR_CHK(UserN > 57*MaxU)       int jjj,cnt, iCID;  float *pfGains;  int *piCellusr; // *piCellO2I;
    GET_GPARAM_INT(gSCM3D_CalibP1_O2I_ON)   int isOutdoorONLY = (0 == gSCM3D_CalibP1_O2I_ON);

    MEMCHK(viCell_UserNUN, 57)     MEMCHK(viCell_UserIDs, 57*MaxU)   MEMCHK(vfMatGains, UserN*57)    MEMCHK(vfServCLs,UserN)
    INT_ZERO(viCell_UserNUN, 57);  INT_ZERO(viCell_UserIDs, 57*MaxU);


    _NEW_INIT()     _NEW_INT0(viCELLcnt, 57)   //_NEW_FLT0(vfUsrCLs, UserN) 
    _LOOPUP_LT(cnt, 0, UserN) {   // for each user
        if( viO2I_IDs[cnt] && isOutdoorONLY )  { continue; }   // only for outdoor user !!!
        pfGains   = vfMatGains + cnt*57;
        vfServCLs[cnt] = VEC_max(&iCID, pfGains, 57);
        if ( 106 == cnt ) {
            int iTST = 3;
        }
        piCellusr = viCell_UserIDs + iCID*MaxU;    piCellusr[viCELLcnt[iCID]] = cnt;      
        //piCellO2I = viCell_UserO2I + iCID*MaxU;    piCellO2I[viCELLcnt[iCID]] = viO2I_IDs[cnt];      
        
        viCELLcnt[iCID] += 1;
    }
    INT_CP(viCELLcnt, viCell_UserNUN, 57);

    float fMeanCL = VEC_mean(vfServCLs, UserN);

    _NEW_FREE() 

    
    return fMeanCL;


}


void   Mat_pickX(float* vfMat_pick, float* vfMat_src, int SRCrow, int SRCcol, int PICKrow, int* viRowIDS, int PICKcol, int* viColIDS)
/* pick items in a matrix
*  vfMat_pick : picked matrix
*  vfMat_src  : source matrix
*  SRCrow     : row of source matrix
*  SRCcol     : col of source matrix
*  PICKrow    : picked row
*  viRowIDS   : list of ID for each picked row
*  PICKcol    : picked col
*  viColIDS   : list of ID for each picked col
Change History 
*  1st version designed by Duan Weiming in 2021-05-11
*/
{

    retERR_LEZ4(SRCrow,SRCcol,PICKrow,PICKcol)     int rrr,ccc, iR, iC; float *pfSRC, *pfDST;

    MEMCHK(vfMat_pick, PICKrow*PICKcol)     MEMCHK(vfMat_src, SRCrow*SRCcol)     MEMCHK(viRowIDS, PICKrow) 

    pfDST = vfMat_pick;     

    _LOOPUP_LT(rrr, 0, PICKrow) {
        iR    = viRowIDS[rrr];     ERR_RNG(iR, 0, SRCrow-1)
        pfSRC = vfMat_src + iR*SRCcol;
        _LOOPUP_LT(ccc, 0, PICKcol) {
            iC = viColIDS[ccc];    ERR_RNG(iC, 0, SRCcol-1)
            *pfDST++ = pfSRC[iC];
        }
    }    

}




void   SCM3Dnet_FDran_UplinkBound(float* vfCxPDF_sinr, int PDFlen, float* vfMatGaindB,int UserN, int MaxJointP, int SIMsampN, float fNetwrok_Load, int iSCENAcase, int *viO2I_IDs)
/* calc uplink FDran bound according to coupling loss matrix
*  vfCxPDF_sinr  : CDF of uplink sinr samples , each sample is calculated by randomly picked active users in 19site hexagonal newtork.
*  PDFlen        : length of PDF
*  vfMatGaindB    : coupling loss btw. each user and 57 cells (size
*  UserN         : total number of users
*  MaxJointP     : max number of joint processiong links for each scheduled active user
*  SIMsampN      : number of simulation samples
*  fNetwrok_Load : network load
Change History 
*  1st version designed by Duan Weiming in 2021-05-11
*/
{
    float fULTXpwr_dBm = 23;                  float fNoiseFigure = 7.0;
    GET_GPARAM_FLT(gSCM3D_CalibP1_UE_BWMHz)   float fTxBW_MHz = gSCM3D_CalibP1_UE_BWMHz;    retERR_RNG(fTxBW_MHz, 1.0, 20.0)
    GET_GPARAM_FLT(gSCM3D_CalibP1_PC_Alpha)   float fPC_Alpha = gSCM3D_CalibP1_PC_Alpha;    retERR_RNG(fPC_Alpha, 0, 1.0)
    float fPC_offset = -10.0;                 if( 0.00001 > fPC_Alpha) { fPC_offset = 0.0; }
    float fPC_anchor = 16.0;
    
    float fPwrRoom_dB  = fULTXpwr_dBm - 10*log10(fTxBW_MHz*1.0e6) - (-174.0 + fNoiseFigure);


    retERR_LEZ4(PDFlen,UserN,MaxJointP,SIMsampN)      retERR_CHK(570 > UserN)    retERR_RNG(fNetwrok_Load,0,1)   retERR_RNG(iSCENAcase, 0,3)
    int   MaxU  = MAXOP(10,(UserN/57)*3);             int jjj,cnt,ppp,rrr,ccc,iPICK,iCID,iUsrID,iCellUSR,iPeak,iTST;     float *pfRVs, *pfSigpwr, *pfSRC,*pfDST;  float fSumSINR, fUsrCL,fPeakIntF, fPCval; int *piUsrIDs;
    int   PickN = MAXOP( (int)(fNetwrok_Load*57), 1);  
    float fRest =  fNetwrok_Load*57 - PickN;  if(0 > fRest) { fRest = 0; }
    


    MEMCHK(vfCxPDF_sinr, PDFlen*2)        MEMCHK(vfMatGaindB, UserN*57)         

    _NEW_INIT()                           _NEW_FLT0(vfRestRVs, SIMsampN)        _NEW_FLT0(vfCell_RVs, MaxU)                     _NEW_INT0(viCell_UserIDs,  57*MaxU)                      
    _NEW_INT0(viCell_UserNUN, 57)         _NEW_FLT0(vfMatG_full, UserN*57)      _NEW_FLT0(vfMatG_pick, (PickN+1)*(PickN+1))     _NEW3_INT0(viPickCELL, viPickUsrID,  viIDorg57, 57)         
    _NEW_FLT0(vfInvIntfS,57)              _NEW2_FLT0(vfSINRs, vfSnrIC,57)       _NEW2_FLT0(vfServCLs, vfUsr_PCs ,UserN)         _NEW3_FLT0(vfJSMPsinrs, vfCoMPsinrs, vfBASEsinrs,SIMsampN*(PickN+1))  
    _NEW2_FLT0(vfCellPwrS,vfJMPpwr,57)    _NEW2_FLT0(vfItf_JMP,vfInterfS,57)    _NEW3_FLT0(vfOneBASEsnr,vfOneCoMPsnr, vfCLsamples, SIMsampN*(PickN+1))  

    if(0 < fRest) { VEC_rand(vfRestRVs, SIMsampN, 0, 1.0); }    // randoms (0~1) to determine a fractional load (fRest)
    IVEC_step(viIDorg57,0,1,57);                                // generate cell id list : 0,1,2,...,56

    float fMeanCL = SCM3Dnet_getCellusers( viCell_UserNUN,  viCell_UserIDs,  vfMatGaindB, UserN, MaxU, vfServCLs, viO2I_IDs) + fPC_anchor;  // +fPC_anchor, modified by Duan Weiming in 2021-05-13

    // **********  calc received power for each link (one user to one cell), it assumes that noise power is normalized to 1.0  *************
    //FLT_CP(vfMatGaindB,  vfMatG_full, UserN*57);       VEC_addC(vfMatG_full, UserN*57, fPwrRoom_dB);
    _LOOPUP_LT(cnt, 0, UserN) {   // coupling loss based uplink power control  for each user
        pfSRC  = vfMatGaindB + cnt*57;                     pfDST  = vfMatG_full + cnt*57;     FLT_CP(pfSRC, pfDST, 57);        
        fPCval = (fMeanCL - vfServCLs[cnt])*fPC_Alpha;     fPCval = MAXOP(-23.0, fPCval);     fPCval = MINOP(10.0,  fPCval);
        vfUsr_PCs[cnt] = fPCval;
        VEC_addC(pfDST, 57, fPwrRoom_dB + fPC_offset + fPCval);  // 20dB range for power control : -3dBm ~ 23dBm

    }


    VEC_mulC(vfMatG_full,  UserN*57, 0.1);   
    VEC_pow10(vfMatG_full, vfMatG_full, UserN*57);

    int iCntSAMP = 0;  // number of sinr samples
    float *pfCLsamples = vfCLsamples;
    _LOOPUP_LT(cnt,0, SIMsampN) {
        
        iPICK = PickN;  if(fRest > vfRestRVs[cnt]) {  iPICK += 1; }        // determine number of active cells for current sample

        INT_CP(viIDorg57, viPickCELL, 57);    IVEC_shuffle(viPickCELL,57); // randomly pick active cells for current sample
        
        _LOOPUP_LT(ppp, 0, iPICK) {    // randomly pick one user for each picked cell
            iCID     = viPickCELL[ppp];
            iCellUSR = viCell_UserNUN[iCID];            
            VEC_rand(vfCell_RVs, iCellUSR,0.0, 1.0);             
            VEC_max(&iUsrID, vfCell_RVs,  iCellUSR);
            //viPickUsrID[ppp] = iUsrID;   // a bug !!!, killed by Duan Weiming in 2021-05-11
            viPickUsrID[ppp] = viCell_UserIDs[ iCID*MaxU + iUsrID];   // bugfix, 2012-05-11
            //viPickUEo2i[ppp] = viCell_UserO2I[ iCID*MaxU + iUsrID];   // for testing, 2012-05-14
            *pfCLsamples++   = vfMatGaindB[ viPickUsrID[ppp]*57 + iCID ];  // for debug only !!!
        }
        Mat_pickX(vfMatG_pick, vfMatG_full , UserN, 57,  iPICK, viPickUsrID, iPICK, viPickCELL);
        VECs_sum(vfCellPwrS, vfMatG_pick,iPICK, iPICK);                    // calc received signal power for each picked cell

        FLT_ZERO(vfJMPpwr, iPICK);//Mat_diagGET(vfJMPpwr, vfMatG_pick,iPICK);                          // get power of each serving user 
        _LOOPUP_LT(rrr, 0, iPICK) {  // for each row
            pfSRC = vfMatG_pick + rrr*iPICK;
            _LOOPUP_LT(ccc, 0, iPICK) {  // for each col
                //if( ccc == rrr ) { continue;}
                if( 8.0 <= pfSRC[ccc] ) {      
                    vfJMPpwr[ccc] += pfSRC[ccc]*0.8;   // // joint processing gain !!!
                }
            }
        }


        _LOOPUP_LT(jjj, 0, iPICK) {   // for each user,  calc  sinr in picked cells, and sum sirs together!!!
            pfSigpwr = vfMatG_pick + jjj*iPICK;
            VEC_sub(vfInterfS, vfCellPwrS , pfSigpwr, iPICK);   // calc interference  in each cell for current user
            VEC_addC(vfInterfS, iPICK, 1.0);                    // add noise power

            VEC_sub(vfItf_JMP, vfCellPwrS, vfJMPpwr, iPICK);  
            VEC_addC(vfItf_JMP, iPICK, 1.0);                    // a bug !!! forget to add noise power for JSMP, by Duan Weiming in 2021-05-13!!!

            if( 8.0 <= pfSigpwr[jjj] ) { vfItf_JMP[jjj] -= pfSigpwr[jjj]*0.2; }  // remove signal of target user from interference
            else                       { vfItf_JMP[jjj] -= pfSigpwr[jjj];     }  // remove signal of target user from interference
            
            VEC_inv(vfInvIntfS, vfInterfS, iPICK, 1.0);    VEC_mul(vfSINRs, pfSigpwr,vfInvIntfS, iPICK);       // sinr = signal_power/( interference + noise )
            VEC_inv(vfInvIntfS, vfItf_JMP, iPICK, 1.0);    VEC_mul(vfSnrIC, pfSigpwr,vfInvIntfS, iPICK);       // sinr = signal_power/( interference + noise -SIC )
            
            vfOneBASEsnr[iCntSAMP] = pfSigpwr[jjj];              // single user snr (thermal noise is normalized to 1), for testing!!!            
            vfOneCoMPsnr[iCntSAMP] = VEC_sum(pfSigpwr,iPICK);
            vfBASEsinrs[iCntSAMP]  = vfSINRs[jjj];               
            vfCoMPsinrs[iCntSAMP]  = VEC_sum(vfSINRs, iPICK);;              
            vfJSMPsinrs[iCntSAMP]  = VEC_sum(vfSnrIC, iPICK);;              
            if(vfOneCoMPsnr[iCntSAMP] < vfJSMPsinrs[iCntSAMP]) {
                iTST = 3;
            }
            iCntSAMP++;  // record combined sirs for current user
        }
    }
    int iLoadPERC = (int)(fNetwrok_Load*100+0.5);  _STRn(iLoadPERC)
    int iPCalpha  = (int)(fPC_Alpha*100+0.5);      _STRn(iPCalpha)
    int iTxBW_Mhz = (int)(fTxBW_MHz+0.5);          _STRn(iTxBW_Mhz)   
    GET_GPARAM_INT(gSCM3D_CalibP1_VShapingN)       _STRn(gSCM3D_CalibP1_VShapingN)     char strBUF[200];     
    STR_catX(strBUF, strSCENAlist[iSCENAcase] ,"M",_STR(gSCM3D_CalibP1_VShapingN),"_LOAD",_STR(iLoadPERC),"_TX",_STR(iTxBW_Mhz),"MHz_Alpha",_STR(iPCalpha),"_ulJSMP_","SINRs");    dumpMat( strBUF , vfJSMPsinrs, 1, iCntSAMP);
    STR_catX(strBUF, strSCENAlist[iSCENAcase] ,"M",_STR(gSCM3D_CalibP1_VShapingN),"_LOAD",_STR(iLoadPERC),"_TX",_STR(iTxBW_Mhz),"MHz_Alpha",_STR(iPCalpha),"_ulComB_","SINRs");    dumpMat( strBUF , vfCoMPsinrs, 1, iCntSAMP);
    STR_catX(strBUF, strSCENAlist[iSCENAcase] ,"M",_STR(gSCM3D_CalibP1_VShapingN),"_LOAD",_STR(iLoadPERC),"_TX",_STR(iTxBW_Mhz),"MHz_Alpha",_STR(iPCalpha),"_ulBase_","SINRs");    dumpMat( strBUF , vfBASEsinrs, 1, iCntSAMP);
    STR_catX(strBUF, strSCENAlist[iSCENAcase] ,"M",_STR(gSCM3D_CalibP1_VShapingN),"_LOAD",_STR(iLoadPERC),"_TX",_STR(iTxBW_Mhz),"MHz_Alpha",_STR(iPCalpha),"_oneUser_","SNRs");    dumpMat( strBUF , vfOneBASEsnr, 1, iCntSAMP);
    STR_catX(strBUF, strSCENAlist[iSCENAcase] ,"M",_STR(gSCM3D_CalibP1_VShapingN),"_LOAD",_STR(iLoadPERC),"_TX",_STR(iTxBW_Mhz),"MHz_Alpha",_STR(iPCalpha),"_oneCoMP_","SNRs");    dumpMat( strBUF , vfOneCoMPsnr, 1, iCntSAMP);



    _NEW_FREE() 

}




void   SCM3Dnet_mimoFD(float* vfCxRxOFDMs_pool, float* vfCxTxOFDMs_pool, char* strCIRfile, int RxM, int TxN, int RBnum, int RBfrom, float fNoisePwr, float* vfCxScHs_pool, int iSenderN, int iRecvrM, int TTIcnt)
/* mimo channel filtering in Freq. Domain
*  vfCxRxOFDMs_pool : Pool of OFDMs for each Receiver, each subcarrier carries RxM complex values w.r.t RxM receive antenna
*  vfCxTxOFDMs_pool : Pool of OFDMs for each Transmitter, each subcarrier carries TxN complex values w.r.t TxN antennas
*  RxM              : number of rx antennas for each Receiver
*  TxN              : number of tx antennas for each Transmitter
*  RBnum            : number of used RBs
*  RBfrom           : RB offset
*  vfCxScHs_pool    : pool of ideal channel matrix for each sub-carrier of each link
*  iSenderN         : number of Transimitters
*  iRecvrM          : number of Receivers
Change History 
*  1st version designed by Duan Weiming in 2021-05-17
*/
{

    retERR_LEZ5(RxM,TxN,RBnum,iSenderN,iRecvrM)      int jjj,cnt,rrr,sss,iTTIoffset;  float fSigma, fAvgEsN0, fInv_NoisePwr;
    float *vfCxRxOFDMs, *vfCxTxOFDMs, *pfCxSCH_ice, *pfAvgSINR;
    int SCnum = RBnum*12;      int OFDMnum = 14;     int SCsum = OFDMnum*SCnum; 

    MEMCHK(vfCxRxOFDMs_pool, iRecvrM*SCsum*RxM*2) 
    MEMCHK(vfCxTxOFDMs_pool, iSenderN*SCsum*TxN*2) 
    MEMCHK(vfCxScHs_pool,    iRecvrM*iSenderN*SCsum*RxM*TxN*2) 

    if(0 < fNoisePwr )  {         fSigma = sqrt(0.5*fNoisePwr);  fInv_NoisePwr = 1.0/fNoisePwr;        }  //added by Duan Weiming in 2021-05-20        



    _NEW_INIT() _NEW_FLT0(vfAvgSINR, iRecvrM*iSenderN)   _NEW_FLT0(vfCxRxOFDMmem, SCsum*RxM*2) 
    pfCxSCH_ice  = vfCxScHs_pool;
    pfAvgSINR    = vfAvgSINR;
    _LOOPUP_LT(rrr, 0, iRecvrM) {         // for each receiver
        vfCxRxOFDMs =  vfCxRxOFDMs_pool + rrr*SCsum*RxM*2;
        FLT_ZERO(vfCxRxOFDMs, SCsum*RxM*2);       // added by Duan Weiming in 2021-05-20        
        _LOOPUP_LT(sss, 0, iSenderN) {    // for each transmitter
            iTTIoffset   = TTIcnt + 1000*(rrr*iSenderN + sss);
            vfCxTxOFDMs  = vfCxTxOFDMs_pool + sss*SCsum*TxN*2;
            *pfAvgSINR++ = MIMO_channelFD(vfCxRxOFDMmem, vfCxTxOFDMs,   strCIRfile,   OFDMnum,  RBnum,  RxM,  TxN,   iTTIoffset,  RBfrom,  0, pfCxSCH_ice); // fNoisePwr==>0, modified by Duan Weiming in 2021-05-20
            CxVEC_sum(vfCxRxOFDMs, vfCxRxOFDMmem, SCsum*RxM);   // added by Duan Weiming in 2021-05-20        
            pfCxSCH_ice += SCsum*RxM*TxN*2;
        }
        if(0 < fNoisePwr )  {  // add guassian noise after combination!!!,  added by Duan Weiming in 2021-05-20                    
            fAvgEsN0  = CxVEC_avgpwr(vfCxRxOFDMs, OFDMnum*SCnum*RxM)*fInv_NoisePwr;   // average EsN0 over links
            GaussianVEC_frannor(vfCxRxOFDMs, OFDMnum*SCnum*RxM*2 , fSigma, 1, 0);    // int isADDED= 1, int isABS = 0;
        }

    }

    _NEW_FREE() 

}

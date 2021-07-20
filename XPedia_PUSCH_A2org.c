
#include "XPedia_Uplink.h"

void PUSCHDmrs_config(int *pi_U, int *pi_V, int SLOTid, int OFDMid, int iCellID, int iHoppingMode)
/* this function calc u & v parameter 
iHoppingMode : 0 (no hopping ) , 1 (group hopping) , 2 (sequence hopping)
reference : subclause 6.4.1.1.2 (Sequence generation when transform precoding is enabled) of TS38.211 V15.8.0
Change History
*  reference version designed by Duan Weiming in 2020-05-16
*/
{
	int iRSid = iCellID;    // no higher layer configuration case
	int ifgh ,iV ,iU, Cinit, iRV;   

    int SLOTperFRM = NR_FRAMESLOTS_N;    
    retERR_RNG(OFDMid,0,14-1)    retERR_RNG(SLOTid, 0, SLOTperFRM-1)  
    retERR_CHK(0 > iCellID)      retERR_LIST(iHoppingMode, 0,1,2)
    int MaxCnum = 14*SLOTperFRM;  
    _NEW_INIT()  _NEW_INT0(viC_list,MaxCnum)

	if( 0 == iHoppingMode )       { // no hopping
		ifgh = 0;   iV = 0; 
	}   
	else if( 1 == iHoppingMode  ) {  // group hopping
		iV    = 0;
		Cinit = int((float)iRSid/(float)30); 
		ifgh  = PUCCH_ncs( OFDMid,  SLOTid,  Cinit);  // 
		ifgh  = ifgh % 30;
	}
	else {  // sequence hopping
		ifgh  = 0;
		Cinit = iRSid;		
		NR_GoldenSEQ(viC_list, MaxCnum,  Cinit);
		iV = viC_list[14*SLOTid + OFDMid];

	}
	iU = (ifgh + iRSid)%30; 
	*pi_U = iU;
	*pi_V = iV;

	_NEW_FREE()

}

int PUSCHDmrs_ZCroot(int iU, int iV, int ZCprime)
/*
reference  : subclause 5.2.2.1 (Base sequences of length 36 or larger)
Change History
*  reference version designed by Duan Weiming in 2020-05-16
*/
{
    
	float fQ_0  = (float)ZCprime*(iU+1)/(float)31;
	int   iPow  = ((int)(2.0*fQ_0))%2;
	int   iSign = -1;  if(0 == iPow) { iSign = 1; }
	int   iQ    = int(fQ_0+0.5) + iV*iSign;
	return iQ;
}






void PUSCHDmrs_DFTsOFDM(float *vfCxVECseq, int RBnum, int SLOTid, int OFDMid, int iCellID, int iHoppingMode)
/*  PUSCH demodulation reference signal for DFT-s-OFDM waveform
*   iHoppingMode : 0 (no hopping ) , 1 (group hopping) , 2 (sequence hopping)
*   reference:  subclause 6.4.1.1.2 (Sequence generation when transform precoding is enabled) of TS38.211 V15.8.0
Change History
*  reference version designed by Duan Weiming in 2020-05-16
*/
{
    int SCnum = RBnum*12;         // !!!  to be checked !!!    SCnum = RBnum*12/2 ????  
    MEMCHK(vfCxVECseq, SCnum*2)    retERR_LIST(iHoppingMode,0,1,2)      
    retERR_RNG(RBnum,10,100)       retERR_RNG(SLOTid,0,10-1)     
    retERR_RNG(OFDMid,0,14-1)      retERR_RNG(iCellID,0,NR_MAXCellNUM-1)      int jjj,iU,iV;  float *pfSRC, *pfDST;

    // add your codes here....

    //int ZCprime = 31; int ZCoffset = 1; int ZCroot = GRPid+1; int ZClen = SCnum;
    int ZCoffset = 0;   
    int ZCprime  = getPrime(SCnum);         // Nzc
    int ZClen    = MINOP(SCnum,ZCprime);    
    
    PUSCHDmrs_config(&iU, &iV,  SLOTid, OFDMid, iCellID, iHoppingMode);
    int ZCroot   = PUSCHDmrs_ZCroot( iU, iV, ZCprime); 
    // x(n) = exp(-j*(pi*ZCroot/ZCprime)*m*(m+1)), m = n+ZCoffset;
    AVX_Gen_ZadoffChu_SEQ(vfCxVECseq,  ZClen,  ZCprime,  ZCroot,  ZCoffset );  
    if( ZClen < SCnum) {
    	pfSRC = vfCxVECseq; 
    	pfDST = vfCxVECseq + ZClen*2; 
    	FLT_CP(pfSRC, pfDST, (SCnum-ZClen)*2);
    }

}

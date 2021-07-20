
#include "XPedia_Uplink.h"

int PUCCH_ncs(int OFDMid, int SLOTid, int Cinit)
/*  cacl n_cs defined in subclause 6.3.2.2.2 (Cyclic shift hopping)
*    n_cs(OFDMid, SLOTid) = sum(2^m*c(8*14*SLOTid + 8*OFDMid + m)) for m=0~7
Change History
*  1st version designed by Duan Weiming in 2020-05-15
*/
{    
    int SLOTperFRM = NR_FRAMESLOTS_N;    
    ret0ERR_RNG(OFDMid,0,14-1)    ret0ERR_RNG(SLOTid, 0, SLOTperFRM-1)  ret0ERR_CHK(0 >= Cinit)
    int MaxCnum = 8*14*SLOTperFRM;   
	_NEW_INIT()              _NEW_INT0(viC_list,MaxCnum)
    
    NR_GoldenSEQ(viC_list, MaxCnum,  Cinit);
    int N_cs = 0;  int C_idx,mmm;     
    _LOOPUP_LT(mmm,0,8) {  
    	C_idx  =  8*14*SLOTid + 8*OFDMid + mmm;  ERR_LT(MaxCnum,C_idx)
        N_cs  +=  (1 << mmm)*viC_list[C_idx];
    }

    _NEW_FREE()
    return N_cs;
}

float  PUCCH_Alpha(int OFDMid, int SLOTid, int iM_cs, int CellID)
/*  cacl and return  alpha (cyclic shift for PUCCH)
*  alpha = 2*pi/RBscnum*(iM_cs + n_cs(OFDMid, SLOTid) mod RBscnum )
*      n_cs(OFDMid, SLOTid) = sum(2^m*c(8*14*SLOTid + 8*OFDMid + m)) for m=0~7
*      c(n) :  call function NR_GoldenSEQ()  with Cinit = CellID
Change History
*  reference verson designed by  Duan Weiming in 2020-05-15
*/
{
    int SLOTperFRM = NR_FRAMESLOTS_N;  float fAlpha;  // fAlpha is the syclic shift value 
    ret0ERR_LIST(iM_cs,0,3,6,9);    ret0ERR_RNG(SLOTid,0,SLOTperFRM)   ret0ERR_RNG(OFDMid,0,14-1)  ret0ERR_RNG(CellID,0,NR_MAXCellNUM-1)

    // add your codes here....
    int iM0 = 0;         int RBscnum = 12;
    int N_cs = PUCCH_ncs( OFDMid,  SLOTid,  CellID);
    fAlpha = 2.0*PI/RBscnum*((iM0 + iM_cs + N_cs)%RBscnum);

    return fAlpha;
}




void PUCCH_baseSEQ_len30(float *vfCxVECseq, int SCnum, float fAlpha, int GRPid)
/*  generate low-PAPR complex sequence for PUCCH , defined in subclause 5.2.2 of TR38.211
Change History
*  reference verson designed by  Duan Weiming in 2020-05-15
*/
{
    retERR_NEQ(SCnum,30)    // low-PAPR sequence length range
    retERR_RNG(GRPid,0,29)              // base sequence Group ID
    retERR_CHK(0 > fAlpha)              // cyclic shift value
    MEMCHK(vfCxVECseq, SCnum*2)


    // add your codes here....
    // exp(-j*pi*(u+1)*(n+1)*(n+2)/31)
    int ZCprime = 31; int ZCoffset = 1; int ZCroot = GRPid+1; int ZClen = SCnum;
    // x(n) = exp(-j*(pi*ZCroot/ZCprime)*m*(m+1)), m = n+ZCoffset;
    AVX_Gen_ZadoffChu_SEQ(vfCxVECseq,  ZClen,  ZCprime,  ZCroot,  ZCoffset );
    CxVEC_phaseRotateSTD(vfCxVECseq, vfCxVECseq, SCnum,  fAlpha );

}





#include "XPedia_Uplink.h"





void  NR_GoldenSEQ(int *viVECseq, int VEClen, int Cinit)
/*  This function generates generic pseudo-random sequences which is defined by a length-31 Golden sequence, 
*  reference :  subclause 5.2.1 (Pseudo-random sequence generation) of TS36.211
Change History
*  reference version designed by Duan Weiming in 2020-05-15
*/
{
    retERR_LEZ(VEClen)   MEMCHK(viVECseq, VEClen)  

    // add your codes here
    int jjj;   float fBSPK;        int iCxSEQlen = (VEClen >>1) + 1;  

    _NEW_INIT()    
    _NEW_FLT0(vfCxGoldseq, iCxSEQlen*2)

    GenLTE_GoldSeq_REL(vfCxGoldseq, Cinit, iCxSEQlen);   
 
    _LOOPUP_LT(jjj,0,VEClen) {  viVECseq[jjj] = ((0 > vfCxGoldseq[jjj]) ? 1 : 0 );   }
    
    _NEW_FREE()

}


int  PUSCHDmrs_Cinit(int OFDMid, int SLOTid, int iScrambID)
/* calc Cinit(init value of golden sequence) defined in subclause 6.4.1.1.1.1 of TS38.211
Change History
*  reference version designed by Duan Weiming in 2020-05-15
*/
{
    ret0ERR_RNG(OFDMid, 0, 13)  ret0ERR_RNG(SLOTid,0,9)  ret0ERR_RNG(iScrambID, 0,65535)
    int N_scid = 0;

    int Cinit = ((1<<17)*(14*SLOTid + OFDMid + 1)*(2*iScrambID + 1) + 2*iScrambID + N_scid)%(1<<31);
    return  Cinit;
}



void PUSCHDmrs_OFDM(float *vfCxVECseq, int RBnum, int SLOTid, int OFDMid, int iCellID)
/*  PUSCH demodulation reference signal for OFDM waveform
*   reference:  subclause 6.4.1.1.1 (Sequence generation when transform precoding is disabled) of TS38.211 V15.8.0
Change History
*  reference verson designed by Duan Weiming in 2020-05-15
*/
{
    int SCnum = RBnum*12;         MEMCHK(vfCxVECseq, SCnum*2)       
    retERR_RNG(RBnum,10,100)      retERR_RNG(SLOTid,0,10-1)      
    retERR_RNG(OFDMid,0,14-1)     retERR_RNG(iCellID,0,NR_MAXCellNUM-1)


    // add your codes here....
    int Cinit  = PUSCHDmrs_Cinit( OFDMid, SLOTid,  iCellID);
    GenLTE_GoldSeq_REL(vfCxVECseq, Cinit, SCnum); 
    int jjj;
    _LOOPUP_LT(jjj,0,SCnum*2) { vfCxVECseq[jjj] *= 0.7071; }

    int iTST = 3;

}


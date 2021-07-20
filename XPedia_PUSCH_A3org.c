
#include "XPedia_Uplink.h"




void CxSEQ_papr(float *vfPAPR_list, float *vfCxSEQs_list, int SEQlen, int SEQnum )
/*  calc PAPR( Peak to Average Powr Ratio) of a given complex sequence,  the PAPR(in dB) of each sequence is saved in vfPAPR_list[]
* reference : https://en.wikipedia.org/wiki/Crest_factor : PAPR is the peak amplitude squared (giving the peak power) divided by the RMS value squared (giving the average power).
Change History
*  1st version designed by ???  in 2020-04 (supervised by Zhang Weizheng & Duan Weiming)
*/
{
    retERR_LEZ(SEQlen)    retERR_LEZ(SEQnum)    MEMCHK(vfCxSEQs_list, SEQnum*SEQlen*2)   MEMCHK(vfPAPR_list, SEQnum)

    // add your codes here....  
    // reference only !!!
    int FFTSize = 2048;  int SysSCnum = 1200; int jjj;  float  *vfFDSeqIQ;
    _NEW_INIT()
    _NEW_FLT(vfCxWaveform, FFTSize*2)
    
    _LOOPUP_LT(jjj,0, SEQnum) {
        vfFDSeqIQ = vfCxSEQs_list + jjj*SEQlen*2;
        GenFDSeq_OFDMwaveform(vfCxWaveform, vfFDSeqIQ, SEQlen,  SysSCnum,  FFTSize);
        vfPAPR_list[jjj] =  Calc_PAPRdB_REL(vfCxWaveform, FFTSize);
    }
    _NEW_FREE()


}


#include "XPedia_Uplink.h"



void CxSEQs_xcorr(float *vfMATxcorr, float *vfCxSEQs_list, int SEQlen, int SEQnum )
/*  calc normalized Cross-correlation of each pair of sequences in given sequence group
*  reference : https://en.wikipedia.org/wiki/Cross-correlation :   
Change History
*  1st version designed by ???  in 2020-04 (supervised by Zhang Weizheng & Duan Weiming)
*/
{
    retERR_LEZ(SEQlen)    retERR_LEZ(SEQnum)    MEMCHK(vfCxSEQs_list, SEQnum*SEQlen*2)   MEMCHK(vfMATxcorr, SEQnum*SEQnum)

    // add your codes here....
    
    AVX_CxVEC_XCorr_REL(vfMATxcorr, SEQlen, SEQnum, vfCxSEQs_list, SEQnum, vfCxSEQs_list,  1, 1, 1); //  reference only!!!,  int isConj = 1;   int isNORM=1, int isXCPwr=1;

    int iTST = 3;

}

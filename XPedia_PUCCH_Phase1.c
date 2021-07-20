
#include "XPedia_Uplink.h"




void PUCCHformat0_est(int *viBITS_2, float *vfCxSCsrc_list,float *vfCxSEQs_org,int SCnum, int RXnum, int OFDMnum, int iBitN)
/*  This function detects bits(1 or 2) in PUCCH format 0
Change History
*  1st version designed by ??? (supervised by Zhang Weizheng & Duan Weiming ) in 2020-05
*/
{
	retERR_RNG(OFDMnum,1,2)   retERR_LIST(SCnum,6,12,18,24,30)   retERR_RNG(RXnum,1,2)   retERR_RNG(iBitN,1,2)
	int iBITS;

	// add your codes here !!!


	

}






void PUCCHformat1_est(int *viBITS_2, float *vfCxSCsrc_list,float *vfCxSEQs_org,int SCnum, int RXnum, int OFDMnum, int iBitN)
/*  This function detects bits(1 or 2) in PUCCH format 1
Change History
*  1st version designed by ??? (supervised by Zhang Weizheng & Duan Weiming ) in 2020-05
*/
{
    retERR_RNG(OFDMnum,1,2)   retERR_LIST(SCnum,6,12,18,24,30)   retERR_RNG(RXnum,1,2)   retERR_RNG(iBitN,1,2)
    

    // add your codes here !!!


    

}

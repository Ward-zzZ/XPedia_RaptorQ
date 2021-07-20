
#include "PerfMetric_COMM.h"
#include "XPedia_CODEC.h"


void   TurboEncoder_ITF(int* viRV_bits, int RVlen, int* viSRCbits, int NetTBS, int ModuType, int RvID)
/* turbo encoder (LTE design)
*  viRV_bits : coded bits for given re-trans ID ( RV
*  RVlen     : number of RV bits (number of bits for current transmission or re-trans)
*  viSRCbits : information bits ( additional 24 bits is reserved for CRC attachment)
*  NetTBS    : net TBS
*  ModuType  : modulation type(2,4,16,64,256)
*  RvID      : ID of redundancy version (0,1,2,4)
Change History 
*  1st version designed by Duan Weiming in 2021-03-12
*/
{

    retERR_LEZ3(RVlen,NetTBS,ModuType)   retERR_RNG(RvID,0,3)   retERR_LIST(ModuType,2,4,16,64,256)
    
    MEMCHK(viRV_bits, RVlen) 
    MEMCHK(viSRCbits, NetTBS+24) 

    LTEturbo_encoder( viRV_bits, RVlen,  viSRCbits, NetTBS, ModuType, RvID);

}



void   TurboDecoder_ITF(int* viCRC, float* vfDemodLLR, int QamNUM, int NetTBS, float* vfHARQllrs, int ModuType, int RvID, int* viINFOcrc, int MaxIter)
/* turbo decoder (LTE design)
*  viCRC      : the 1st value is the CRC decision , other 3 integers reserved for future design
*  vfDemodLLR : input LLRs
*  QamNUM     : number of Qam symbols
*  NetTBS     : net TBS
*  vfHARQllrs : harq llr buffer for encoding
*  HARQlen    : reserved Harq buff length
*  ModuType   : modulation type(2,4,16,64,256)
*  RvID       : ID of redundancy version (0,1,2,4)
*  viINFOcrc  : decoded bits
*  MaxIter    : maximum number of iterations configured for decoding
Change History 
*  1st version designed by Duan Weiming in 2021-03-12
*/
{

    retERR_LEZ4(QamNUM,NetTBS,ModuType,MaxIter)  retERR_RNG(RvID,0,3)   retERR_LIST(ModuType,2,4,16,64,256)

    MEMCHK(viCRC, 4) 
    MEMCHK(viINFOcrc, NetTBS+24) 

    LTEturbo_decoder( viCRC, vfDemodLLR,  NetTBS, QamNUM, ModuType, vfHARQllrs,  RvID, MaxIter, viINFOcrc);

    int iTST = 3;

}

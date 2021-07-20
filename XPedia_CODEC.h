/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */



#ifndef __XPEDIA_CODEC_H
#define __XPEDIA_CODEC_H


extern "C" {
    

    
    void   TurboEncoder_ITF(int* viRV_bits, int RVlen, int* viSRCbits, int NetTBS, int ModuType, int RvID);
    void   TurboDecoder_ITF(int* viCRC, float* vfDemodLLR, int QamNUM, int NetTBS, float* vfHARQllrs, int ModuType, int RvID, int* viINFOcrc, int MaxIter);

    // ****************************************************************************************************************************************************************************
    extern void   LTEturbo_encoder(int* viRVbits, int RVlen, int* viINFOcrc, int NetTBS, int ModuType, int RvID);
    extern void   LTEturbo_decoder(int* viCRC, float* vfDemodLLR, int NetTBS, int QamNUM, int ModuType, float* vfHARQ_llr, int RvID, int MaxIter, int* viINFOcrc);
    extern void   LTEturbo_decoderORG(int* viCRC, float* vfDemodLLR, int NetTBS, int QamNUM, int ModuType, float* vfHARQ_llr, int RvID, int MaxIter, int* viINFOcrc, int isRstHarqLLR, int isUptHarqLLR, float *pfMRGllrs);

    // ****************************************************************************************************************************************************************************

    


}



#endif /* __XPEDIA_CODEC_H */

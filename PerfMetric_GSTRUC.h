#ifndef __PERF_METRIC_GSTRUC_H
#define __PERF_METRIC_GSTRUC_H

// *************  parse all defined structures ******************

//#include "RadioSignalSrc.h"
#include "RadioSignalBase.h"
//#ifdef MAC_FLAG
//#include "SDLviewSrc.h"
//#endif



extern "C" {

	int gSTRUC_len(char *strSTRUCtype);
    void NDarray_read(float *vfNDarray,int ilen);


}





#endif /* __PERF_METRIC_GSTRUC_H */
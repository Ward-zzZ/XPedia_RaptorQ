#ifndef __PERF_METRIC_GTSdef_H
#define __PERF_METRIC_GTSdef_H

/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */


#define __GTS_NEW(__str1__) GTS_##__str1__,
#define _TIMESTAMP_NEW(__str1__) GTS_##__str1__##____,





#define __GTS_REG(__func_name_index__)  \
if( GLOBAL_TIMESTAMP_SWITCH_ON ){   \
	if( ( (GTS_##__func_name_index__) < MAX_GLOBAL_TIMESTAMP_NUM ) && ((GTS_##__func_name_index__) >= 0 ) ) { \
		if( gvstGlobalTimeStampList[GTS_##__func_name_index__].nUsed ) {  \
			printf( "    WARNING!!!  TimeStamp <%s> is replaced by <%s>  due to same  index!!! \n", (char *)gvstGlobalTimeStampList[GTS_##__func_name_index__].strName, (const char *)("#__func_name_index__")); \
			gvstGlobalTimeStampList[GTS_##__func_name_index__].strName[0] = 0; \
		} \
		strcpy(gvstGlobalTimeStampList[GTS_##__func_name_index__].strName, (const char  *)(#__func_name_index__) ); \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].lCounter = 0;    \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].lCurrTime = 0;  \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].dSumTime = 0;  \
	}  \
	else{   \
		if(( (GTS_##__func_name_index__) < MAX_GLOBAL_TIMESTAMP_NUM ) && ((GTS_##__func_name_index__) >= 0 )){ \
		printf("    WARNING!!!  <%s,%s,%d> "#__func_name_index__"  (= %d) is invalid !!!  \n", __FILE__,__FUNCTION__,__LINE__, (GTS_##__func_name_index__)); } \
	} \
}




#define __GTS_TICK(__func_name_index__)  \
if( GLOBAL_TIMESTAMP_SWITCH_ON ){   \
	if( 0 == gnGlobalTimesStampList_CHECKED ) { GlobalTimeStamp_Register(); } \
	if( ( (GTS_##__func_name_index__) < MAX_GLOBAL_TIMESTAMP_NUM ) && ((GTS_##__func_name_index__) >= 0 ) ) { \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].lCurrTime = _rdtsc();  \
	}  \
}

#define __GTS_TUCK(__func_name_index__)  \
if( GLOBAL_TIMESTAMP_SWITCH_ON ){   \
	if( ( (GTS_##__func_name_index__) < MAX_GLOBAL_TIMESTAMP_NUM ) && ((GTS_##__func_name_index__) >= 0 ) ) { \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].lCounter += 1; \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].dSumTime += (double)(_rdtsc() -  gvstGlobalTimeStampList[GTS_##__func_name_index__].lCurrTime )*0.001;  \
	}  \
}


#define __GTS_FUNC(__func_name_index__, __call_func__) \
if( GLOBAL_TIMESTAMP_SWITCH_ON ){   \
	if( 0 == gnGlobalTimesStampList_CHECKED ) { GlobalTimeStamp_Register(); } \
	int __isValidGTS__ =  ( ( (GTS_##__func_name_index__) < MAX_GLOBAL_TIMESTAMP_NUM ) && ((GTS_##__func_name_index__) >= 0 ) ); \
	if(__isValidGTS__ ) { gvstGlobalTimeStampList[GTS_##__func_name_index__].lCurrTime = _rdtsc();  } \
	__call_func__; \
	if(__isValidGTS__ ) { \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].lCounter += 1; \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].dSumTime += (double)(_rdtsc() -  gvstGlobalTimeStampList[GTS_##__func_name_index__].lCurrTime )*0.001;  \
	} \
}





#define _TIMESTAMP_REG(__func_name_index__)  \
if( GLOBAL_TIMESTAMP_SWITCH_ON ){   \
	if( 0 == gnGlobalTimesStampList_CHECKED ) { GlobalTimeStamp_Register(); } \
	if( ( (GTS_##__func_name_index__) < MAX_GLOBAL_TIMESTAMP_NUM ) && ((GTS_##__func_name_index__) >= 0 ) ) { \
		if( gvstGlobalTimeStampList[GTS_##__func_name_index__].nUsed ) {  \
			printf( "    WARNING!!!  TimeStamp <%s> is replaced by <%s>  due to same  index!!! \n", (char *)gvstGlobalTimeStampList[GTS_##__func_name_index__].strName, (const char *)("#__func_name_index__")); \
			gvstGlobalTimeStampList[GTS_##__func_name_index__].strName[0] = 0; \
		} \
		strcpy(gvstGlobalTimeStampList[GTS_##__func_name_index__].strName, (const char  *)(#__func_name_index__) ); \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].lCounter = 0;    \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].lCurrTime = 0;  \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].dSumTime = 0;  \
	}  \
	else{   \
		if(( (GTS_##__func_name_index__) < MAX_GLOBAL_TIMESTAMP_NUM ) && ((GTS_##__func_name_index__) >= 0 )){ \
		printf("    WARNING!!!  <%s,%s,%d> "#__func_name_index__"  (= %d) is invalid !!!  \n", __FILE__,__FUNCTION__,__LINE__, (GTS_##__func_name_index__)); } \
	} \
}

#define _TIMESTAMP_TICK(__func_name_index__)  \
if( GLOBAL_TIMESTAMP_SWITCH_ON ){   \
	if( ( (GTS_##__func_name_index__) < MAX_GLOBAL_TIMESTAMP_NUM ) && ((GTS_##__func_name_index__) >= 0 ) ) { \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].lCurrTime = _rdtsc();  \
	}  \
}

#define _TIMESTAMP_TUCK(__func_name_index__)  \
if( GLOBAL_TIMESTAMP_SWITCH_ON ){   \
	if( ( (GTS_##__func_name_index__) < MAX_GLOBAL_TIMESTAMP_NUM ) && ((GTS_##__func_name_index__) >= 0 ) ) { \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].lCounter += 1; \
		gvstGlobalTimeStampList[GTS_##__func_name_index__].dSumTime += (double)(_rdtsc() -  gvstGlobalTimeStampList[GTS_##__func_name_index__].lCurrTime )*0.001;  \
	}  \
}





#define TIMESTAMP_SWITCH_ON(__switch_on__) \
int ____SWITCH_TIMESTAMP_ON____ = __switch_on__;

#define TIMESTAMP_REGISTER(__func_name__) \
long CAT2STRS(__lCounter_,__func_name__) = 0; \
long CAT2STRS(__lCurrTme_,__func_name__) = 0; \
double CAT2STRS(__fSumTme_,__func_name__) = 0; 


#define TIMESTAMP_TRIGGER(__func_name__) \
if(____SWITCH_TIMESTAMP_ON____){ \
	CAT2STRS(__lCurrTme_,__func_name__) = (long)_rdtsc(); \
}


#define TIMESTAMP_SAMPLES(__func_name__) \
if(____SWITCH_TIMESTAMP_ON____){ \
	CAT2STRS(__lCounter_,__func_name__) += 1;  \
	CAT2STRS(__fSumTme_,__func_name__) += (double)(_rdtsc() - CAT2STRS(__lCurrTme_,__func_name__))*0.001; \
}


#define TIMESTAMP_SHOWTOTAL(__func_name__) \
if(____SWITCH_TIMESTAMP_ON____){ \
	printf(" "#__func_name__"_ (total_time) = %f \n",  (float)CAT2STRS(__fSumTme_,__func_name__) ); \
}






#endif /* __PERF_METRIC_GTSdef_H */
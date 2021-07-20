
#ifndef __PERF_METRIC_COMMgdb_H
#define __PERF_METRIC_COMMgdb_H
/* *************************************************************************************************************************************************************************
************   Designed by Duan Weiming at home since 2015...   
*************************************************************************************************************************************************************************  */

//#include "/usr/local/include/fftw3.h"

#ifdef __cplusplus 
extern "C" {   
#endif	

    extern int    gdbVlen;
	extern float* gdbV0 ;extern float* gdbV1;extern float* gdbV2;extern float* gdbV3;extern float* gdbV4;extern float* gdbV5;extern float* gdbV6;extern float* gdbV7;extern float* gdbV8;extern float* gdbV9;
	extern int*   gdbIV0;extern int*  gdbIV1;extern int*  gdbIV2;extern int*  gdbIV3;extern int*  gdbIV4;extern int*  gdbIV5;extern int*  gdbIV6;extern int*  gdbIV7;extern int*  gdbIV8;extern int*  gdbIV9;
	extern short* gdbSV0;extern short* gdbSV1;extern short* gdbSV2;extern short* gdbSV3;extern short* gdbSV4;extern short* gdbSV5;extern short* gdbSV6;extern short* gdbSV7;extern short* gdbSV8;extern short* gdbSV9;

	extern char*  gdbSTR0;extern char* gdbSTR1;extern char* gdbSTR2;extern char* gdbSTR3;extern char* gdbSTR4;extern char* gdbSTR5;extern char* gdbSTR6;extern char* gdbSTR7;extern char* gdbSTR8;extern char* gdbSTR9;

	
	void GDBrst_CHK(int isForceRst);
	//void GDBrst(int isForceRst);
                                                   
	float* GDBnew(int VEClen);
	int*   GDBnewI(int VEClen);
	short* GDBnewS(int VEClen);
	char*  GDBnewSTR(int VEClen);
	char*  GDBnewSTRX(int VEClen, char *strName);
	void   GDBfree();

	int  GDBsumIV(int *viData, int Vlen, int isECHO);
	void GDBmemchk(void *pMEM);
	void GDBmtx( float *vfMtx, int nROW, int nCOL);
	
	void GDBcxm( float *vfMtx, int nROW, int nCOL, int isSimple);
	void GDBfmxcol( float *vfMtx, int nROW, int nCOL, int ColIDX );
	void GDBfmxrow( float *vfMtx, int nROW, int nCOL, int RowIDX );
	void GDBimxrow( int *viMtx, int nROW, int nCOL, int RowIDX );
	void GDBimxcol( int *viMtx, int nROW, int nCOL, int ColIDX );
	void GDB_SaveFileName(char *strGDBFileName );
	void GDB_CxSave(char *strVarName, float *vfCxData, int nCxVECSize, int nVECNum );
	void GDB_IntSave(char *strVarName, int *vnData, int nColPerROW, int nROW );
	void GDB_ShortSave(char *strVarName, short *viData, int VEClen, int nVECNum);
	void GDB_FltSave(char *strVarName, float *vfData, int nColVECSize, int nVECNum);
	void GDB_CxByteSave(char *strVarName, char *vbCxData, int nCxNum );
	void GDBSave_InterFACE(char *strVarName, float *vfData, int VECNum, int VECSize, int DataType);	

	void GDB_svCxM(char *strVarName, float *vfCxMdata, int iRow, int iCol);  
	void GDB_svMat(char *strVarName, float *vfMat, int iRow, int iCol);      
	void GDB_svIMat(char *strVarName, int *viMat,  int iRow, int iCol);      
	void GDB_rst(int iForce);     

	void GDBvec(float *vfData, int Vlen);
    void GDBivec(int *viData, int Vlen);


    #define  svFLTS(__strVarName__, __vfData__, __nNum__ )   GDBSave_InterFACE(__strVarName__, __vfData__, 1, __nNum__, 1)    

    #define  svIVEC(__strName__, __vfVEC__, __VEClen__ )     GDBSave_InterFACE((char*)__strName__, (float*)(__vfVEC__), 1, __VEClen__, 0)
    #define  svVEC(__strName__, __vfVEC__, __VEClen__ )      GDBSave_InterFACE((char*)__strName__, __vfVEC__, 1, __VEClen__, 1)
    #define  svMAT(__strName__, vfMat__, __row__, __col__)   GDBSave_InterFACE((char*)__strName__, vfMat__, __row__, __col__, 1)
    #define  svCxM(__strName__, vfCxM__, __row__, __col__)   GDBSave_InterFACE((char*)__strName__, vfCxM__, __row__, __col__, 2)

	
	
	//void Tst_FFT( int FFTSize,int VecSize, int isFFT, int RepeatNUM);
	//void TST_Func_2Args(char *strTstCase, int VEClen, int VECnum, int nRepeatNUM);
	void gdb_tool(int VEClen, int VECnum);
	                     
	#ifdef __cplusplus 
}
#endif

                                     
#endif // __PERF_METRIC_COMMgdb_H

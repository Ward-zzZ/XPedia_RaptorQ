

exec(open('PY3InterFACE_COMM.py').read()); _mybase = ctypes.CDLL('libXpedia.so');   exec(open('PY3ctypes_comm.py').read());

#      int    SCM3Denv_dropXY(float* vfCxPOS_list, int UsrN, int iSCENAcase , int* viSiteIDS);
SCM3Denv_dropXY = _mybase.SCM3Denv_dropXY;  SCM3Denv_dropXY.argtypes = ( cFLTS  ,cINT  ,cINT  ,cINTS ); SCM3Denv_dropXY.restype = cINT ; 

#      void   SCM3Denv_ghostXYs(float* vfCxPOSx19_list, float* vfCxPOSorg_list, int* viSiteIDS, int DropN, int iSCENAcase);
SCM3Denv_ghostXYs = _mybase.SCM3Denv_ghostXYs;  SCM3Denv_ghostXYs.argtypes = ( cFLTS  ,cFLTS  ,cINTS ,cINT  ,cINT  ); 



#  void   SCM3Denv_genlinkGain(float* vfMatGains, float* vfCxPOSx19_list, float *vfHeights, int *viO2I_IDs, int *viLOS_x19,  int UsrN, float fCarrierGHz, int iSCENAcase)
SCM3Denv_genlinkGain = _mybase.SCM3Denv_genlinkGain;  SCM3Denv_genlinkGain.argtypes = ( cFLTS  ,cFLTS  ,cFLTS ,cINTS ,cINTS ,cINT  ,cFLT  ,cINT  ); 

#  void   SCM3Dnet_DLSirCDF(float* vfCxCDF, int CDFlen,  float* vfMatGains,  int UserN, int iSCENAcase)
SCM3Dnet_DLSirCDF = _mybase.SCM3Dnet_DLSirCDF;  SCM3Dnet_DLSirCDF.argtypes = ( cFLTS  ,cINT  ,cFLTS   ,cINT  ,cINT  ); 


#  void   SCM3Dnet_FDran_UplinkBound(float* vfCxPDF_sinr, int PDFlen, float* vfMatGaindB,int UserN, int MaxJointP, int SIMsampN, float fNetwrok_Load, int iSCENAcase, int *viO2I_IDs)
SCM3Dnet_FDran_UplinkBound = _mybase.SCM3Dnet_FDran_UplinkBound;  SCM3Dnet_FDran_UplinkBound.argtypes = ( cFLTS  ,cINT  ,cFLTS  ,cINT  ,cINT  ,cINT  ,cFLT  ,cINT  ,cINTS  ); 



#  comments: it is dangerous to share global between .so libraries, almost 5 hours to solve the problem related, 
#  the followint related to  libperfmetric.so should be moved to major python file,  by Duan Weiming in 2019-12-12                                                           
#cfg_GPARAM = _perfmetric.cfg_GPARAM; #cfg_GPARAM.argtypes = (cSTR,);   cfg_GPARAM.restype = cINT;

# int cfg_GPARAM(char *strGlobalCONF)
cfg_GPARAM = _mybase.cfg_GPARAM;  cfg_GPARAM.argtypes = (cSTR,);   cfg_GPARAM.restype = cINT;

def cfgGPARAM(strGConfig) : cfg_GPARAM(_str(strGConfig));


# exec(open('PY3ITF_scmLSP.py').read());  UserN=57*200; iSCENAcase=1; M=1; fNetLOAD=0.5;  SCM3Dnet_genLSPs4G(UserN,iSCENAcase, M,fNetLOAD);  # Uma M=1
# exec(open('PY3ITF_scmLSP.py').read());  UserN=57*200; iSCENAcase=0; M=1; fNetLOAD=0.5;  SCM3Dnet_genLSPs4G(UserN,iSCENAcase, M,fNetLOAD);  # Umi M=1
# exec(open('PY3ITF_scmLSP.py').read());  UserN=57*200; iSCENAcase=1; M=10; fNetLOAD=0.5;  SCM3Dnet_genLSPs4G(UserN,iSCENAcase, M,fNetLOAD);  # Uma M=10
# exec(open('PY3ITF_scmLSP.py').read());  UserN=57*200; iSCENAcase=0; M=10; fNetLOAD=0.5;  SCM3Dnet_genLSPs4G(UserN,iSCENAcase, M,fNetLOAD);  # Umi M=10
def SCM3Dnet_genLSPs4G(UserN,iSCENAcase, M, fNetLOAD) :    
    xx = []; getTICKs(xx,'creating lsp data (calibration phase1 of TR38.873) for '+ str(UserN) + 'users');
    vfCxPOS_usrs    = newFLTS(UserN*2);     viSite_usrs = newINTS(UserN);     fCarrierGHz = 2.0;           CDFlen = 400;                vfCxCDF   = newFLTS(CDFlen*2);   vfCxCDF_sinr = newFLTS(CDFlen*2);  
    vfCxPOSx19_list = newFLTS(UserN*19*2);  vfMatGains  = newFLTS(UserN*57);  vfHeights = newFLTS(UserN);  viO2I_IDs = newINTS(UserN);  viLOS_x19 = newINTS(UserN*19); 
    
    
    #cfgGPARAM("gSCM3D_CalibP1_UE_BWMHz=1.0   gSCM3D_CalibP1_O2I_ON=1   ");  # both outdoor and O2I
    cfgGPARAM("gSCM3D_CalibP1_UE_BWMHz=10.0   gSCM3D_CalibP1_O2I_ON=0   ");  # outdoor only!!!
    cfgGPARAM("gSCM3D_CarrierGHz=2.0  gSCM3D_CalibP1_RadioDist=0  gSCM3D_CalibCL_StrongN=9 gSCM3D_CalibP1_PC_Alpha=0.6 ");    
    if 10 == M  : cfgGPARAM("gSCM3D_CalibP1_VShapingN=10 gSCM3D_CalibP1_DwntiltDEG=12 ");
    else        : cfgGPARAM("gSCM3D_CalibP1_VShapingN=1  gSCM3D_CalibP1_DwntiltDEG=0  ");
    SCM3Denv_dropXY(vfCxPOS_usrs,  UserN,  iSCENAcase , viSite_usrs);
    SCM3Denv_ghostXYs(vfCxPOSx19_list, vfCxPOS_usrs, viSite_usrs, UserN,  iSCENAcase);
    SCM3Denv_genlinkGain( vfMatGains,  vfCxPOSx19_list, vfHeights, viO2I_IDs, viLOS_x19,  UserN,  fCarrierGHz,  iSCENAcase);        
    SCM3Dnet_DLSirCDF( vfCxCDF, CDFlen,   vfMatGains,   UserN,  iSCENAcase);
    SCM3Dnet_FDran_UplinkBound( vfCxCDF_sinr, CDFlen, vfMatGains,  UserN, 7, 10000, fNetLOAD, iSCENAcase,viO2I_IDs);


    getTUCKs(xx);  gMEM_free(1); #miQ_close(1);



#UserN=57*200; iSCENAcase=0; M=1;  SCM3Dnet_genLSPs4G(UserN,iSCENAcase, M);
#UserN=57*200; iSCENAcase=0; M=10;  SCM3Dnet_genLSPs4G(UserN,iSCENAcase, M);
#UserN=57*200; iSCENAcase=1; M=1;  SCM3Dnet_genLSPs4G(UserN,iSCENAcase, M);
#UserN=57*200; iSCENAcase=1; M=10;  SCM3Dnet_genLSPs4G(UserN,iSCENAcase, M);
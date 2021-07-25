#######################################################################################################
##              Designed by Duan Weiming since 2017~
#######################################################################################################
import datetime; import os;import math;  import time;  import glob;
import numpy as np;   import ctypes;    from numpy.ctypeslib import ndpointer
import multiprocessing ;  from ctypes import *

cFLTS    = ndpointer(ctypes.c_float, flags="C_CONTIGUOUS");
cINTS    = ndpointer(ctypes.c_int,   flags="C_CONTIGUOUS");
cUINT8  = ndpointer(ctypes.c_uint8,   flags="C_CONTIGUOUS");
cINT     = ctypes.c_int;      cFLT    = ctypes.c_float;      cSTR   = ctypes.c_char_p;
cLONG    = ctypes.c_long;     cDOUBLE = ctypes.c_double;     cUINT  = ctypes.c_uint32;
cVPTR    = ctypes.c_void_p;   pVOID   = ctypes.byref(ctypes.c_void_p());  # know-how 2019-04-01


######################################### added by Ward in 2021-7-20 ##################################
cUINT64 = ctypes.c_uint64;cSizet = ctypes.c_size_t;


def newFLTS(size):
    #return np.zeros(size,dtype=np.float32,order='C');
    vfMEMbuff = np.zeros(size+2, dtype=np.float32, order='C')
    #stampMEMCHK_FLT(vfMEMbuff,size)#
    vfMEMbuff[1] = size
    vfMEMbuff[0] = 20050523
    #vfMEMbuff[0] = size; vfMEMbuff[1] = 20050523;
    return vfMEMbuff[2:size+2]
#######################################################################################################

#  comments: it is dangerous to share global between .so libraries,  removed by Duan Weiming in 2019-12-12
# _perfmetric = ctypes.CDLL('libperfmetric.so')   # load specially-designed library

##################################################################################################
def getTICK() :  start_time = datetime.datetime.now();     return start_time;

def getTUCK(tick_time) :
    elapsed_time = datetime.datetime.now() - tick_time;
    elapsed = elapsed_time.seconds + elapsed_time.microseconds*1e-6;
    #print('@@@@ elapsed ...' + str(elapsed) + 'seconds!!!');
    return elapsed;

def getTUCK_P(tick_time) :
    elapsed = getTUCK(tick_time);
    print('@@@@ elapsed ...' + str(elapsed) + 'seconds!!!');
    return elapsed;

def getTICKs(timer_list, strDISP) :
    timer_list.append(datetime.datetime.now()); timer_list[0]=datetime.datetime.now();
    timer_list.append(strDISP);                 timer_list[1]=strDISP;
    if 0 < len(strDISP) : print('@@@start '+strDISP);

def getTUCKs(timer_list) :
    d_timer = datetime.datetime.now() - timer_list[0];  #timer_list[0] = d_timer;
    timer_list[0] = d_timer.seconds + d_timer.microseconds*1e-6;
    strDISP = timer_list[1];
    if 0 < len(strDISP) : print('@@@finish '+ strDISP + '...elapsed ' + str(timer_list[0]) + ' seconds!!!');

def getTUCKx(timer_list) :
    d_timer = datetime.datetime.now() - timer_list[0];  #timer_list[0] = d_timer;
    timer_list[0] = d_timer.seconds + d_timer.microseconds*1e-6;
    #strDISP = timer_list[1];
    #if 0 < len(strDISP) : print('@@@finishing'+ strDISP + '...elapsed ' + str(timer_list[0]) + ' seconds!!!');
    return timer_list[0];


##################################################################################################


def list2cFLTS(data_list) :
    ilen = len(data_list); xx = newFLTS(ilen);
    for jjj in range(ilen) : xx[jjj] = data_list[jjj];
    return xx

def list_mulC(data_list, val) :
    ilen = len(data_list);
    for jjj in range(ilen) : data_list[jjj] *= val;



##################################################################################################

def MP_cpus() : return multiprocessing.cpu_count();

def MP_newINTS( VEClen) :  return  multiprocessing.Array('i', range(VEClen));

def MP_newFLTS( VEClen) :  return  multiprocessing.Array('d', range(VEClen));


def MP_jobnum( cfglist, MAXjobs) :
    num = len(cfglist);  cpus = MP_cpus();
    if (cpus < num ) :  num = cpus;
    if( MAXjobs < num ) : num = MAXjobs;
    return num;

def MP_slice( cfglist, cntJOB, JOBnum) :
    num = len(cfglist);  Gap = int(num/JOBnum);  lftnum = num - Gap*JOBnum; sliceCFGs = [];
    From = cntJOB*Gap;
    for cfgval in cfglist[From:From+Gap]:  sliceCFGs.append(cfgval);
    if(cntJOB < lftnum) : sliceCFGs.append(cfglist[Gap*JOBnum+cntJOB]);
    return sliceCFGs;

def MP_sliceX( cfglist, cntJOB, JOBnum) :
    num = len(cfglist);  Gap = int(num/JOBnum);  lftnum = num - Gap*JOBnum; sliceCFGs = [];  sliceIDs = [];
    From = cntJOB*Gap;
    #for cfgval in cfglist[From:From+Gap]:  sliceCFGs.append(cfgval);
    #if(cntJOB < lftnum) : sliceCFGs.append(cfglist[Gap*JOBnum+cntJOB]);
    for cfgID in range(From,From+Gap):                  sliceCFGs.append(cfglist[cfgID]); sliceIDs.append(cfgID);
    if(cntJOB < lftnum) :   cfgID = Gap*JOBnum+cntJOB;  sliceCFGs.append(cfglist[cfgID]); sliceIDs.append(cfgID);
    return sliceCFGs, sliceIDs;



# JOBnum = MP_jobnum(cfglist,MAXjobs);
# for cntJOB in range(JOBnum) : slice =  MP_slice( cfglist, cntJOB, JOBnum);


##################################################################################################

def newFLTS(size) :
    #return np.zeros(size,dtype=np.float32,order='C');
    vfMEMbuff = np.zeros(size+2,dtype=np.float32,order='C');
    #stampMEMCHK_FLT(vfMEMbuff,size)#
    vfMEMbuff[1] = size; vfMEMbuff[0] = 20050523;
    #vfMEMbuff[0] = size; vfMEMbuff[1] = 20050523;
    return vfMEMbuff[2:size+2];

def newINTS(size) :
    #return np.zeros(size,dtype=np.int32,order='C');
    vnMEMbuff = np.zeros(size+2,dtype=np.int32,order='C');
    #stampMEMCHK_INT(vnMEMbuff,size) #
    vnMEMbuff[1] = size; vnMEMbuff[0] = 20050523;
    #vnMEMbuff[0] = size; vnMEMbuff[1] = 20050523;
    return vnMEMbuff[2:size+2];


def newBYTES(size) :
    return np.zeros(size,dtype=np.uint8,order='C');

def newSTR(size) :
    return create_string_buffer(size);  # np.zeros(size,dtype=np.int8,order='C');



def newSTRUC(strSTRUCtype) :
    ilen = gSTRUC_len(strSTRUCtype);  #print('...  '+str(strSTRUCtype) +' has len of  '  +str(ilen))
    #if 0 == ilen : print('@@@ERROR!!! '+ str(strSTRUCtype) + ' not defined in PerfMetric_GPARAM.c \n'); return 0;
    #else         : print ('@@@  '+ str(strSTRUCtype) + ' has a size of '+str(ilen)+' integers' )
    if 0 == ilen : print('@@@ERROR!!! '+ str(strSTRUCtype) + ' not defined in PerfMetric_GPARAM.c \n'); return 0;
    return newFLTS(ilen);


def newiSTRUC(strSTRUCtype) :
    ilen = gSTRUC_len(strSTRUCtype);  #print('...  '+str(strSTRUCtype) +' has len of  '  +str(ilen))
    #if 0 == ilen : print('@@@ERROR!!! '+ str(strSTRUCtype) + ' not defined in PerfMetric_GPARAM.c \n'); return 0;
    #else         : print ('@@@  '+ str(strSTRUCtype) + ' has a size of '+str(ilen)+' integers' )
    if 0 == ilen : print('@@@ERROR!!! '+ str(strSTRUCtype) + ' not defined in PerfMetric_GPARAM.c \n'); return 0;
    return newINTS(ilen);



##################################################################################################
def getMEM(vfMEM,offset,nLEN) :
    return vfMEM[offset:offset+nLEN];


def genINTS(Val_list) :
    nLEN = len(Val_list);
    vnMEM = newINTS(nLEN);
    for jjj in range(nLEN) : vnMEM[jjj] = Val_list[jjj];
    return vnMEM;

def ints2flts(vnData) :
    nLEN = len(vnData); vfData = newFLTS(nLEN);
    for jjj in range(nLEN) : vfData[jjj] = vnData[jjj];
    return vfData;

def list2FLTS(listData) :
    vecLEN = len(listData); vecData = newFLTS(vecLEN);
    for jjj in range(vecLEN) :  vecData[jjj] = listData[jjj];
    return vecData;

def list2INTS(listData) :
    vecLEN = len(listData); vecData = newINTS(vecLEN);
    for jjj in range(vecLEN) :
        vecData[jjj] = listData[jjj];
    return vecData;

def list_rng(frm,to,step):
    vfData = np.arange(frm,to,step);
    list_o = [];
    for val in vfData : list_o.append(val);
    return list_o;

##################################################################################################
def Read_txtfile(filename) :
    lines = list(open(filename));
    return lines;

def readFLTS_txtfile(vfData, ilen ,filename, strSplitter) :
    iCNT = 0;
    fp = open(filename, "r");  lines = fp.readlines();  fp.close();
    for line in lines :
        f_list = [float(strVal) for strVal in line.split(strSplitter)];
        for jjj in range(len(f_list)) :
            vfData[iCNT] = f_list[jjj];  iCNT += 1;
            if iCNT >= ilen : break;
        if iCNT >= ilen : break;
    return vfData;


def getFilelen(filename):
    st = os.stat(filename);
    return st.st_size


def rmvFile(filename) :
    if os.path.isfile(filename)  :  os.system('rm  ' + filename);


def rmvFiles(strFilepatt) :
    file_list = glob.glob('./' + strFilepatt); print(file_list);
    for strfile in file_list :  os.system('rm ' + strfile);

# def loadFLTS(strFilename,SampleFrom, SampleNUM) :
#     FileBytes = getFilelen(strFilename);  TotalSamples = FileBytes/4;
#     realSamples = SampleNUM;
#     if ( TotalSamples < SampleFrom+SampleNUM ) : realSamples = TotalSamples-SampleFrom;
#     vfData = newFLTS(realSamples);
#     ReadBinaryFile_Flts(strFilename, vfData, realSamples, SampleFrom);
#     return vfData,realSamples;

def VEC_randn(VEClen,Sigma,Mu) :
    xx = Mu + Sigma*np.random.randn(VEClen);
    return xx;

def loadFLTS(strBinFile, VEClen, offset) :
    fp = open(strBinFile, "rb");    fp.seek(offset*4, os.SEEK_SET)
    data = np.fromfile(fp, dtype='float32',count=VEClen);  # almost 1 hour to get it done : dtype='float' ==> dtype='float32', commented by Duan Weiming in 2019-07-06
    fp.close();
    return data;


#def loadINTS(strFilename,SampleFrom, SampleNUM) :
#    FileBytes = getFilelen(strFilename);  TotalSamples = FileBytes/4;
#    realSamples = SampleNUM;
#    if ( TotalSamples < SampleFrom+SampleNUM ) : realSamples = TotalSamples-SampleFrom;
#    vnData = newINTS(realSamples);
#    ReadBinaryFile_INTS(strFilename, vnData, realSamples, SampleFrom);
#    return vnData,realSamples;

def loadINTS(strBinFile, VEClen, offset) :
    fp = open(strBinFile, "rb");    fp.seek(offset*4, os.SEEK_SET)
    data = np.fromfile(fp, dtype='int32',count=VEClen);  # almost 1 hour to get it done : dtype='float' ==> dtype='float32', commented by Duan Weiming in 2019-07-06
    fp.close();
    return data;


def appendFLTS(strFilename,vfData) :
    fp = open(strFilename,'ab'); 	vfData.tofile(fp);  fp.close();

def appendFLTX(strFilename,vfData, VEClen) :
    fp = open(strFilename,'ab');    vfData[0:VEClen].tofile(fp);  fp.close();


def saveFLTS(strFilename, vfData, VEClen) :
    vfData[0:VEClen].tofile(strFilename); #SaveBinaryFile_Flts(strFilename, vfData, VEClen);

def saveVEC(strFilename, vfData) :
    vfData.tofile(strFilename); #SaveBinaryFile_Flts(strFilename, vfData, VEClen);

def saveINTS(strFilename, vnData, VEClen) :
    vnData[0:VEClen].tofile(strFilename); #SaveBinaryFile_Flts(strFilename, vfData, VEClen);

def saveIVEC(strFilename, vnData) :
    vnData.tofile(strFilename); #SaveBinaryFile_Flts(strFilename, vfData, VEClen);



def svTXT(txtfile, strSave) :                   fp = open(txtfile,'a');  fp.write(strSave); fp.close();
def svTXTline(txtfile, strSave) :               fp = open(txtfile,'a');  fp.write(strSave+'\n'); fp.close();
def svTXTlist(txtfile, listData, listname) :
    fp = open(txtfile,'a');
    if(0< len(listname)) :  fp.write(listname + '=' + str(listData) +';\n');
    else                 :  fp.write(str(listData) +'\n');
    fp.close();

def list2str(listData) :
    strO = ''; ilen = len(listData);
    for jjj in range(ilen) :  strO += str(listData[jjj]) + ' ';
    return strO;


def addTXTlist(txtfile, listData, listname) :
    fp = open(txtfile,'a');
    if(0< len(listname)) :  fp.write(listname + '= [ '+ listname + ' ' + list2str(listData) +' ];\n');
    else                 :  fp.write(str(listData) +'\n');
    fp.close();



##################################################################################################
def getVEC(VEClen) :  vfVEC = newFLTS(VEClen);  return vfVEC;
def _str(strval) : return strval.encode('utf-8');







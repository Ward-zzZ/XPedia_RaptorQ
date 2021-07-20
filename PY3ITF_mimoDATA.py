
#exec(open('PY3InterFACE_COMM.py').read()); _mybase = ctypes.CDLL('libmybase.so'); exec(open('PY3ctypes_comm.py').read());
exec(open('PY3InterFACE_COMM.py').read()); _mybase = ctypes.CDLL('libXpedia.so'); exec(open('PY3ctypes_comm.py').read());

def SCM3Dmimo_genHfile(RBnum,TTIsum,SEGnum,TxN,RxM,XplN) : 
    TTIseg = int(TTIsum/SEGnum);  TTIgap = 10; isTXomni = 1;  strSavName = newSTR(300); #strSavName = ''.zfill(300);     
    strSavTAG = 'MMIMO_nlos'; eSCMcaseID = 4;  
    xx = [];  getTICKs(xx,'creating mimo channels...' )
    if isTXomni :  strSavTAG = strSavTAG + 'OmniAnt';
    SCM3Dmimo_genH(_str(strSavTAG),eSCMcaseID, SEGnum,  RBnum , TTIseg,  TxN,  RxM, XplN, TTIgap, isTXomni,strSavName)    
    getTUCKs(xx);   #print('saving H file : ' + strSavName);
    return strSavName;


strSavFile = SCM3Dmimo_genHfile(10,2400,4,32,2,4)



strSavTAG = 'MMIMO_nlos'; eSCMcaseID = 4;  strSavName = ''.zfill(100);

#RBnum = 6;  SEGnum=20; TTInum = 30*20;  TxN = 4*8; RxM = 1; XplN = 4;  TTIgap = 10; isTXomni = 1;
RBnum = 10;  SEGnum=20; TTInum = 1000;  TxN = 4*8; RxM = 2; XplN = 4;  TTIgap = 10; isTXomni = 1;

xx = [];  getTICKs(xx,'creating mimo channels..(' + str(SEGnum) + 'SEGx' + str(TTInum) + 'TTIx' + str(RBnum*12) + 'SCx' + str(TxN*RxM*XplN) + 'channels)')
if isTXomni :  strSavTAG = strSavTAG + 'OmniAnt';

#SCM3DmimoH_QuaDriGa(_str(strSavTAG),_str(strLSPfile), SEGnum,  RBnum , TTInum,  TxN,  RxM, XplN, TTIgap, isTXomni)
SCM3Dmimo_genH(_str(strSavTAG),eSCMcaseID, SEGnum,  RBnum , TTInum,  TxN,  RxM, XplN, TTIgap, isTXomni,_str(strSavName))

getTUCKs(xx)





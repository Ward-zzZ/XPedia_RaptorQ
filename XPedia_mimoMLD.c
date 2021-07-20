
#include "PerfMetric_COMM.h"
#include "XPedia_mimoMLD.h"

void   Print_intMat(int* vfRlMats_A, int iRow, int iCol, int MATnum)
/* matrix Print  Mat_O = Mat_A 
*  vfRlMats_A : list of matrix A (iRow x iCol)
*  iRow       : row number of matrix A
*  iCol       : col number of matrix A
*  MATnum     : number of matrix
Change History 
*  1st version designed by Xiao ZiXiong in 2021-04-07
*/
{
    //retERR_LEZ3(iRow,iCol,MATnum)    
    int rrr,ccc,cnt; int *pfRlM_A; 

    //MEMCHK(vfRlMats_A, MATnum*iRow*iCol)   
    
    _LOOPUP_LT(cnt, 0, MATnum) {  // Mat_O = Mat_A
        _isPrintF("%d*%d", iRow, iCol);
        pfRlM_A = vfRlMats_A + cnt*iRow*iCol;

        _LOOPUP_LT(rrr,0, iRow) {
            _isPrintF("\n");
            _LOOPUP_LT(ccc,0, iCol) {
                _isPrintF("%d ", pfRlM_A[0]);
                pfRlM_A += 1;
            }
        }
    } 
    
}

void   Print_Mat(float* vfRlMats_A, int iRow, int iCol, int MATnum)
/* matrix Print  Mat_O = Mat_A 
*  vfRlMats_A : list of matrix A (iRow x iCol)
*  iRow       : row number of matrix A
*  iCol       : col number of matrix A
*  MATnum     : number of matrix
Change History 
*  1st version designed by Xiao ZiXiong in 2021-04-07
*/
{
    //retERR_LEZ3(iRow,iCol,MATnum)    
    int rrr,ccc,cnt; float *pfRlM_A; 

    //MEMCHK(vfRlMats_A, MATnum*iRow*iCol)   
    
    _LOOPUP_LT(cnt, 0, MATnum) {  // Mat_O = Mat_A
        _isPrintF("%d*%d", iRow, iCol);
        pfRlM_A = vfRlMats_A + cnt*iRow*iCol;

        _LOOPUP_LT(rrr,0, iRow) {
            _isPrintF("\n");
            _LOOPUP_LT(ccc,0, iCol) {
                _isPrintF("%f ", pfRlM_A[0]);
                pfRlM_A += 1;
            }
        }
    } 
    
}

void   RlMat_copy_REF(float* vfRlMats_O, float* vfRlMats_A, int iRow, int iCol, int MATnum)
/* real matrix copy   Mat_O = Mat_A 
*  vfRlMats_O : list of output matrix (iRow x iCol)
*  vfRlMats_A : list of matrix A (iRow x iCol)
*  iRow       : row number of matrix A
*  iCol       : col number of matrix A
*  MATnum     : number of matrix
Change History 
*  1st version designed by Xiao ZiXiong in 2021-03-26
*/
{

    //retERR_LEZ3(iRow,iCol,MATnum)    
    int rrr,ccc,cnt; float *pfRlM_A, *pfRlM_O; 

    //MEMCHK(vfRlMats_O, MATnum*iRow*iCol)     MEMCHK(vfRlMats_A, MATnum*iRow*iCol)    


    _LOOPUP_LT(cnt, 0, MATnum) {  // Mat_O = Mat_A
        pfRlM_O = vfRlMats_O + cnt*iRow*iCol;
        pfRlM_A = vfRlMats_A + cnt*iRow*iCol;

        _LOOPUP_LT(rrr,0, iRow) {
            _LOOPUP_LT(ccc,0, iCol) {
                pfRlM_O[0] = pfRlM_A[0];

                pfRlM_O += 1;
                pfRlM_A += 1;
            }
        }
    }
}
void   RlMat_add_REF(float* vfRlMats_O, float* vfRlMats_A, float* vfRlMats_B, int iRow, int iCol, int MATnum)
/* real matrix addition   Mat_O = Mat_A + Mat_B
*  vfRlMats_O : list of output matrix (iRow x iCol)
*  vfRlMats_A : list of matrix A (iRow x iCol)
*  vfRlMats_B : list of matrix B (iRow x iCol)
*  iRow       : row number of matrix A
*  iCol       : col number of matrix B
*  MATnum     : number of matrix
Change History 
*  1st version designed by Xiao ZiXiong in 2021-03-26
*/
{

    //retERR_LEZ3(iRow,iCol,MATnum)    
    int rrr,ccc,cnt; float *pfRlM_A, *pfRlM_B , *pfRlM_O; 

    //MEMCHK(vfRlMats_O, MATnum*iRow*iCol)     MEMCHK(vfRlMats_A, MATnum*iRow*iCol)     MEMCHK(vfRlMats_B, MATnum*iRow*iCol) 


    _LOOPUP_LT(cnt, 0, MATnum) {  // Mat_O = Mat_A + Mat_B
        pfRlM_O = vfRlMats_O + cnt*iRow*iCol;
        pfRlM_A = vfRlMats_A + cnt*iRow*iCol;
        pfRlM_B = vfRlMats_B + cnt*iRow*iCol;

        _LOOPUP_LT(rrr,0, iRow) {
            _LOOPUP_LT(ccc,0, iCol) {
                pfRlM_O[0] = pfRlM_A[0] + pfRlM_B[0];

                pfRlM_O += 1;
                pfRlM_A += 1;
                pfRlM_B += 1;
            }
        }
    }
}

void   RlMat_sub_REF(float* vfRlMats_O, float* vfRlMats_A, float* vfRlMats_B, int iRow, int iCol, int MATnum)
/* real matrix subtraction   Mat_O = Mat_A - Mat_B
*  vfRlMats_O : list of output matrix (iRow x iCol)
*  vfRlMats_A : list of matrix A (iRow x iCol)
*  vfRlMats_B : list of matrix B (iRow x iCol)
*  iRow       : row number of matrix A
*  iCol       : col number of matrix B
*  MATnum     : number of matrix
Change History 
*  1st version designed by Xiao ZiXiong in 2021-03-26
*/
{

    //retERR_LEZ3(iRow,iCol,MATnum)    
    int rrr,ccc,cnt; float *pfRlM_A, *pfRlM_B, *pfRlM_O; 

    //MEMCHK(vfRlMats_O, MATnum*iRow*iCol)     MEMCHK(vfRlMats_A, MATnum*iRow*iCol)     MEMCHK(vfRlMats_B, MATnum*iRow*iCol) 

    _LOOPUP_LT(cnt, 0, MATnum) {  // Mat_O = Mat_A - Mat_B
        pfRlM_O = vfRlMats_O + cnt*iRow*iCol;
        pfRlM_A = vfRlMats_A + cnt*iRow*iCol;
        pfRlM_B = vfRlMats_B + cnt*iRow*iCol;

        _LOOPUP_LT(rrr,0, iRow) {
            _LOOPUP_LT(ccc,0, iCol) {
                pfRlM_O[0] = pfRlM_A[0] - pfRlM_B[0];

                pfRlM_O += 1;
                pfRlM_A += 1;
                pfRlM_B += 1;
            }
        }
    }
}

void   RlMatNum_mul_REF(float* vfRlMats_O, float* vfRlMats_A, float vfRlNum_B, int iRow, int iCol)
/* real matrix multiplication   Mat_O = Mat_A * Num_B
*  vfRlMats_O : output matrix (iRow x iCol)
*  vfRlMats_A : real matrix A (iRow*iCol)
*  vfRlNum_B  : real number B 
*  iRow       : row number of matrix A
*  iCol       : col number of matrix A
Change History 
*  1st version designed by Xiao ZiXiong in 2021-03-26
*/
{

    //retERR_LEZ2(iRow,iCol)    
    int rrr,ccc; float val, *pfRlM_A, *pfRlM_O; 

    //MEMCHK(vfRlMats_O, iRow*iCol)     MEMCHK(vfRlMats_A, iRow*iCol)    

    pfRlM_O = vfRlMats_O;
    pfRlM_A = vfRlMats_A;

    _LOOPUP_LT(rrr,0, iRow) {
        _LOOPUP_LT(ccc,0, iCol) {
            val = pfRlM_A[0]*vfRlNum_B;
            pfRlM_O[0] = val;
            pfRlM_A += 1;
            pfRlM_O += 1;
        }
    }

}

void   RlVEC_dot_REF(float* vfRlDOT, float* vfRlV_A, float* vfRlV_B, int Vlen)
/* dot product of two real vectors
*  vfRlDOT : dot product
*  vfRlV_A : real vector A
*  vfRlV_B : real vector B
*  Vlen    : vector length
Change History 
*  1st version designed by Xiao ZiXiong in 2021-03-25
*/
{

    //retERR_LEZ(Vlen)      
    int jjj;  float *pfA, *pfB;  float fSum, fA, fB;
    //MEMCHK(vfRlDOT, 1)     MEMCHK(vfRlV_A, Vlen)     MEMCHK(vfRlV_B, Vlen) 

    pfA = vfRlV_A;   fSum = 0; 
    pfB = vfRlV_B;   
    _LOOPUP_LT(jjj, 0, Vlen) {
        fA = *pfA++; 
        fB = *pfB++;

        fSum += fA*fB;
    }
    *vfRlDOT = fSum;
}

void   CxVEC_dot_REF(float* vfCxDOT, float* vfCxV_A, float* vfCxV_B, int Vlen)
/* dot product of two complex vectors
*  vfCxDOT : dot product
*  vfCxV_A : complex vector A
*  vfCxV_B : complex vector B
*  Vlen    : vector length
Change History 
*  1st version designed by Duan Weiming in 2021-03-16
*/
{

    //retERR_LEZ(Vlen)      
    int jjj;  float *pfA, *pfB;  float fSumI, fSumQ, fAi,fAq, fBi,fBq;
    //MEMCHK(vfCxDOT, 2)     MEMCHK(vfCxV_A, Vlen*2)     MEMCHK(vfCxV_B, Vlen*2) 

    pfA = vfCxV_A;   fSumI = 0; 
    pfB = vfCxV_B;   fSumQ = 0;
    _LOOPUP_LT(jjj, 0, Vlen) {
        fAi = *pfA++;   fAq = *pfA++;
        fBi = *pfB++;   fBq = *pfB++;

        fSumI += fAi*fBi - fAq*fBq;
        fSumQ += fAi*fBq + fAq*fBi;
    }
    vfCxDOT[0] = fSumI;
    vfCxDOT[1] = fSumQ;
}

void   RlMat_tranpose_REF(float* vfRlM_trp, float* vfRlM_src, int iRow, int iCol)
/* real matrix tranpose
*  vfRlM_trp : tranpose real matrix
*  vfRlM_src : source real matrix
*  iRow      : row number of source matrix
*  iCol      : col number of source matrix
Change History 
*  1st version designed by Xiao ZiXiong in 2021-03-25
*/
{

    //retERR_LEZ2(iRow,iCol)    
    int rrr, ccc;   float *pfDST, *pfSRC;
    //MEMCHK(vfRlM_trp, iCol*iRow) 
    //MEMCHK(vfRlM_src, iRow*iCol) 

    pfDST = vfRlM_trp;
    _LOOPUP_LT(ccc, 0, iCol) {      // for each row of tranpsoe matrix
        pfSRC = vfRlM_src + ccc;
        _LOOPUP_LT(rrr, 0, iRow) {  // for each col of tranpose matrix
            pfDST[0] = pfSRC[0];   // real 
            pfSRC   += iCol;
            pfDST   += 1;
        }
    }
}

void   CxMat_tranpose_REF(float* vfCxM_trp, float* vfCxM_src, int iRow, int iCol)
/* complex matrix tranpose
*  vfCxM_trp : tranpose complex matrix
*  vfCxM_src : source complex matrix
*  iRow      : row number of matrix A
*  iCol      : col number of matrix B
Change History 
*  1st version designed by Duan Weiming in 2021-03-16
*/
{

    //retERR_LEZ2(iRow,iCol)    
    int rrr, ccc;   float *pfDST, *pfSRC;
    //MEMCHK(vfCxM_trp, iCol*iRow*2) 
    //MEMCHK(vfCxM_src, iRow*iCol*2) 

    pfDST = vfCxM_trp;
    _LOOPUP_LT(ccc, 0, iCol) {      // for each row of tranpsoe matrix
        pfSRC = vfCxM_src + ccc*2;
        _LOOPUP_LT(rrr, 0, iRow) {  // for each col of tranpose matrix
            pfDST[0] = pfSRC[0];   // real 
            pfDST[1] = pfSRC[1];   // real 
            pfSRC   += iCol*2;
            pfDST   += 2;
        }
    }
}

void   RlMat_mul_REF(float* vfRlMats_O, float* vfRlMats_A, float* vfRlMats_B, int iRow, int iJoint, int iCol, int MATnum)
/* real matrix multiplication   Mat_O = Mat_A * Mat_B
*  vfRlMats_O : list of output matrix (iRow x iCol)
*  vfRlMats_A : list of matrix A (iRow*iJoint)
*  vfRlMats_B : list of matrix B (iJoint*iCol)
*  iRow       : row number of matrix A
*  iJoint     : col number of matrix A ,also the row number of matrix B
*  iCol       : col number of matrix B
*  MATnum     : number of matrix
Change History 
*  1st version designed by Xiao ZiXiong in 2021-03-25
*/
{

    //retERR_LEZ4(iRow,iJoint,iCol,MATnum)    
    int rrr,ccc,cnt,jjj; float *pfRlM_A, *pfRlM_B , *pfRlM_O, *pfRlA, *pfRlB, *pfRlO; 

    //MEMCHK(vfRlMats_O, MATnum*iRow*iCol)     MEMCHK(vfRlMats_A, MATnum*iRow*iJoint)     MEMCHK(vfRlMats_B, MATnum*iJoint*iCol) 

    _NEW_INIT()   _NEW_FLT(vfRlM_trB, iCol*iJoint)

    for(cnt=0;cnt<MATnum;cnt++) {  // Mat_O = Mat_A * Mat_B
        pfRlM_O = vfRlMats_O + cnt*iRow*iCol;
        pfRlM_A = vfRlMats_A + cnt*iRow*iJoint;
        pfRlM_B = vfRlMats_B + cnt*iJoint*iCol;

        RlMat_tranpose_REF(vfRlM_trB, pfRlM_B, iJoint, iCol);  // tranpose of matrix B

        for(rrr=0;rrr<iRow;rrr++) {
            for(ccc=0;ccc<iCol;ccc++) {
                pfRlA = pfRlM_A   + rrr*iJoint;
                pfRlB = vfRlM_trB + ccc*iJoint;
                RlVEC_dot_REF(pfRlM_O, pfRlA, pfRlB, iJoint); 
                pfRlM_O += 1;
            }
        }
    }
    _NEW_FREE()
}

void   CxMat_mul_REF(float* vfCxMats_O, float* vfCxMats_A, float* vfCxMats_B, int iRow, int iJoint, int iCol, int MATnum)
/* complex matrix multiplication   Mat_O = Mat_A * Mat_B
*  vfCxMats_O : list of output matrix (iRow x iCol)
*  vfCxMats_A : list of matrix A (iRow*iJoint)
*  vfCxMats_B : list of matrix B (iJoint*iCol)
*  iRow       : row number of matrix A
*  iJoint     : col number of matrix A ,also the row number of matrix B
*  iCol       : col number of matrix B
*  MATnum     : number of matrix
Change History 
*  1st version designed by Duan Weiming in 2021-03-16
*/
{

    //retERR_LEZ4(iRow,iJoint,iCol,MATnum)   
    int rrr,ccc,cnt,jjj; float *pfCxM_A, *pfCxM_B , *pfCxM_O, *pfCxA, *pfCxB, *pfCxO; 

    //MEMCHK(vfCxMats_O, MATnum*iRow*iCol*2)     MEMCHK(vfCxMats_A, MATnum*iRow*iJoint*2)     MEMCHK(vfCxMats_B, MATnum*iJoint*iCol*2) 

    _NEW_INIT()   _NEW_FLT(vfCxM_trB, iCol*iJoint*2)

    for(cnt=0;cnt<MATnum;cnt++)  {  // Mat_O = Mat_A * Mat_B
        pfCxM_O = vfCxMats_O + cnt*iRow*iCol*2;
        pfCxM_A = vfCxMats_A + cnt*iRow*iJoint*2;
        pfCxM_B = vfCxMats_B + cnt*iJoint*iCol*2;

        CxMat_tranpose_REF(vfCxM_trB, pfCxM_B, iJoint, iCol);  // tranpose of matrix B

        for(rrr=0;rrr<iRow;rrr++) {
            for(ccc=0;ccc<iCol;ccc++) {
                pfCxA = pfCxM_A   + rrr*iJoint*2;
                pfCxB = vfCxM_trB + ccc*iJoint*2;
                CxVEC_dot_REF(pfCxM_O, pfCxA, pfCxB, iJoint); 
                pfCxM_O += 2;
            }
        }
    }
    _NEW_FREE()
}

void   RlMat_QRdec_REF(float* vfRlM_Q, float* vfRlM_R, float* vfRlM_src, int iRow, int iCol)
/* real matrix QRdecomposition 
*  vfRlM_Q    : orthogonal matrix Q
*  vfRlM_R    : upper triangular matrix R
*  vfRlM_src  : source real matrix
*  iRow       : row number of source matrix
*  iCol       : col number of source matrix
Change History 
*  1st version designed by Xiao ZiXiong in 2021-03-28
*/
{

    //retERR_LEZ2(iRow,iCol)    
    int rrr,ccc,cnt,jjj,jRow,jCol; float *pfSRC, *pfRlQ, *pfRlR, *pfRltry, *pfRltrz, *pfRlz; float normY;

    //MEMCHK(vfRlM_Q, iRow*iRow)     MEMCHK(vfRlM_R, iRow*iCol)     MEMCHK(vfRlM_src, iRow*iCol) 

    _NEW_INIT()   _NEW_FLT(vfRlM_trR, iCol*iRow) _NEW_FLT(vfRlM_trY, 1*iRow) _NEW_FLT(vfRlM_trz, 1*iRow) 
    _NEW_FLT(vfRlM_z, 1*iRow) _NEW_FLT(vfVal, 1) _NEW_FLT(vfQ0, iRow*iRow) _NEW_FLT(vfQ1, iRow*iRow) 
    _NEW_FLT(vfeye, iRow*iRow) _NEW_FLT(vfR0, iRow*iCol)
    RlMat_copy_REF(vfR0, vfRlM_src, iRow, iCol, 1);
    
    _LOOPUP_LT(cnt,0, iRow) {
        vfRlM_trY[cnt] = 0;
        vfRlM_trz[cnt] = 0;
        vfRlM_z[cnt]   = 0;
    } 
    _LOOPUP_LT(jRow,0, iRow) {
        _LOOPUP_LT(jCol,0, iRow) {
            if(jRow == jCol){
                vfQ0[jRow*iRow + jCol]  = 1;
                vfeye[jRow*iRow + jCol] = 1;
            }
            else{
                vfQ0[jRow*iRow + jCol]  = 0;
                vfeye[jRow*iRow + jCol] = 0;
            }
        }
    } 
    //
    //_isPrintF("\neye\n");
    //Print_Mat(vfeye, iRow, iRow, 1); 
    //
    RlMat_tranpose_REF(vfRlM_trR, vfRlM_src, iRow, iCol);// tranpose of source matrix
    _LOOPUP_LT(rrr, 0, iRow-1) { 
        pfRltry = vfRlM_trR + rrr*iRow + rrr;
        //
        //_isPrintF("\npfRltry%d\n",rrr);
        //Print_Mat(pfRltry, iRow-rrr, 1, 1); 
        //
        normY = 0;
        _LOOPUP_LT(ccc,0, iRow - rrr) {
            normY += pfRltry[0]*pfRltry[0];
            pfRltry += 1;
        }
        normY = sqrt(normY);

        vfRlM_trY[rrr] = normY;
        //
        //_isPrintF("\nvfRlM_trY%d\n",rrr);
        //Print_Mat(vfRlM_trY, iRow, 1, 1); 
        //
        pfRltrz = vfRlM_trz;
        pfRlz = vfRlM_trz;//
        RlMat_sub_REF(pfRltrz, vfRlM_trR + rrr*iRow, vfRlM_trY, 1, iRow, 1);

        _LOOPUP_LT(jjj,0, rrr) {
            pfRltrz[jjj] = 0;
        }
        //
        //_isPrintF("\npfRltrz%d\n",rrr);
        //Print_Mat(pfRltrz, iRow, 1, 1); 
        //

        RlMat_tranpose_REF(pfRlz, pfRltrz, 1, iRow);//
        
        RlVEC_dot_REF(vfVal, pfRltrz, pfRlz, iRow);
        
        RlMat_mul_REF(vfQ1, pfRlz, pfRltrz, iRow, 1, iRow, 1);
        
        RlMatNum_mul_REF(vfQ1, vfQ1, 2/vfVal[0], iRow, iRow);
        
        RlMat_sub_REF(vfQ1, vfeye, vfQ1, iRow, iRow, 1);
        
        RlMat_mul_REF(vfRlM_Q, vfQ0, vfQ1, iRow, iRow, iRow, 1);
        
        RlMat_copy_REF(vfQ0, vfRlM_Q, iRow, iRow, 1);
        
        RlMat_mul_REF(vfRlM_R, vfQ1, vfR0, iRow, iRow, iCol, 1);
        
        RlMat_tranpose_REF(vfRlM_trR,vfRlM_R,iRow,iCol);

        //
        //_isPrintF("\nvfRlM_R%d\n",rrr);
        //Print_Mat(vfRlM_R, iRow, iCol, 1); 
        //
        RlMat_copy_REF(vfR0, vfRlM_R, iRow, iCol, 1);

    }
    _NEW_FREE()
}

void   RlNum_max_REF(float* vfRlN, float* vfRlN_A, float* vfRlN_B, int lenA, int lenB)
/* maximal element of A and B
*  vfRlN      : maximum
*  vfRlN_A    : vector A
*  vfRlN_A    : vector B
*  lenA       : length of vector A
*  lenB       : length of vector B
Change History 
*  1st version designed by Xiao ZiXiong in 2021-03-30
*/
{
    //retERR_LEZ2(lenA,lenB)    
    int rrr,ccc; float maxA, maxB;

    //MEMCHK(vfRlN_A, lenA)     MEMCHK(vfRlN_B, lenB) 
    maxA = vfRlN_A[0]; maxB = vfRlN_B[0];
    if(lenA>1){
    _LOOPUP_LT(rrr,1, lenA) {
        if (vfRlN_A[rrr]>maxA)
            maxA = vfRlN_A[rrr];        
    }
    }
    if(lenB>1){
    _LOOPUP_LT(ccc,1, lenB) {
        if (vfRlN_B[rrr]>maxB)
            maxB = vfRlN_B[rrr];    
    }
    }
    if (maxA>maxB)
        vfRlN[0] = maxA;
    else
        vfRlN[0] = maxB;
}



void recur_sd(float* Lam0, float* Lam1, float* y, float* x, float* bitX, float dc, float* R, int i, int* constel, int* moduMap, float* maxL, int bitLen, int m)
/* soft output sphere decoder
*  Lam0       : output llrs on bits which is 0
*  Lam1       : output llrs on bits which is 1
*  y          : rx vector
*  x          : assumptive tx vector
*  bitX       : bits of assumptive tx vector
*  dc         : the distance which have been produced 
*  R          : QRdecomposition of H
*  i          : the level of recursion (LyrN*2 -1)
*  constel    : constel of the modulation
*  moduMap    : contains values of bit sequence
*  maxL       : maximum of llrs which have been produced 
*  bitLen     : bitLen of the modulation
*  m          : the length of rx vector
Change History 
*  1st version designed by Xiao ZiXiong, Jiang Yi in 2021-03-30
*/
{   
     int t, c, k, ii, jj; float Epsi1, Lam, dc1;
    _NEW_INIT()   _NEW_FLT(vfLi, 1*bitLen) _NEW_FLT(maxLi, 1) _NEW_FLT(maxLam, 1) _NEW_FLT(maxLamt, 1) _NEW_FLT(maxLam1, 1) _NEW_FLT(Epsit, 1)
    _LOOPUP_LT(t,0, pow(2,bitLen)) {
        //
        _isPrintF("\n-%d-\n",i );
        //
        x[i] = constel[t];
        //_LOOPUP_LT(j,0, 2^bitLen) {
        //  if (x[i] == moduMap[j*(bitLen+1)]){
        _LOOPUP_LT(c,0, bitLen) {
            bitX[i*bitLen+c] = moduMap[t*(bitLen+1)+c+1];
        }
        //  }
        //}
        if (i>0){

            _LOOPUP_LT(k,0, bitLen) {
        //
                _isPrintF("\n%d\n",i*bitLen+k);
                //
                if (bitX[i*bitLen+k])
                    vfLi[k] = Lam1[i*bitLen+k] ;
                else
                    vfLi[k] = Lam0[i*bitLen+k] ;
            } 
            
            RlNum_max_REF(maxLi, vfLi, maxL, bitLen, 1);

            RlNum_max_REF(maxLamt, Lam0, Lam1, bitLen*i, bitLen*i);

            RlNum_max_REF(maxLam, maxLamt, maxLi, 1, 1);

            RlVEC_dot_REF(Epsit, R+i*m+i, x + i, m - i);

            Epsi1 = y[i] - Epsit[0];
            Epsi1 = Epsi1*Epsi1;
            dc1   = dc + Epsi1;

            if (dc1<maxLam[0]){
                recur_sd(Lam0, Lam1, y, x, bitX, dc1, R, i-1, constel, moduMap, maxLi, bitLen, m);
            }
        }
        else{
            RlVEC_dot_REF(Epsit, R+i*m+i, x + i, m - i);
            
            Epsi1 = y[i] - Epsit[0];
            Epsi1 = Epsi1*Epsi1;
            Lam = dc + Epsi1;
            _LOOPUP_LT(ii,0, m) {
                _LOOPUP_LT(jj,0, bitLen) {
                    if (bitX[ii*bitLen+jj]){
                        if(Lam1[ii*bitLen+jj]>Lam){
                            Lam1[ii*bitLen+jj] = Lam;
                        }
                        }
                    else{
                        if(Lam0[ii*bitLen+jj]>Lam){
                            Lam0[ii*bitLen+jj] = Lam;
                        }   
                    }
                }
            }
        }
    }
    _NEW_FREE()         // free all local memories
}



void   MIMO_mldDec(float* vfllrs, float* vfCxR_list, float* vfCxH_list, int LyrN, int SCnum, int ModuType, float fNoisePwr)
/* MLD mimo decoder
*  vfllrs     : output llrs
*  vfCxR_list : rx complex vector for each sub-carrier
*  vfCxH_list : H complex matrix for each sub-carrier
*  LyrN       : mimo layers
*  SCnum      : number of sub-carriers
*  ModuType   : modulation type. 4(Qpsk), 16(16Qam), 64(64Qam),256(256Qam)
*  fNoisePwr  : noise power on each sub-carrier
Change History 
*  1st version designed by Xiao ZiXiong, Jiang Yi in 2021-03
*/
{
    //
    _isPrintF("\nY0\n");
    Print_Mat(vfCxR_list, LyrN, 2, 1);
    //
    _isPrintF("\nH0\n");
    Print_Mat(vfCxH_list, LyrN, LyrN*2, 1); 
    //
    //retERR_LEZ4(LyrN,SCnum,ModuType,fNoisePwr)     //retERR_RNG(ModuType,4,16,64,256)   retERR_RNG(LyrN,2,4,8);      
    int jjj,cnt; 
    //int QamB  = _GET_QamBITS(ModuType);             // get bit number for given ModuType
    //int MaxN  = 1;        _LOOPUP_LT(jjj,0, LyrN) { MaxN *= ModuType; }      // max number of combinations
    //int BITsc = LyrN*QamB;                                                   // bits per sub-carrier

    //MEMCHK(vfllrs,     SCnum*LyrN*QamB) 
    //MEMCHK(vfCxR_list, SCnum*LyrN*2) 
    //MEMCHK(vfCxH_list, SCnum*LyrN*LyrN*2) 


    _NEW_INIT()   _NEW_FLT(vfRlM_Q, LyrN*2*LyrN*2)  _NEW_FLT(vfRlM_R, LyrN*2*LyrN*2)  _NEW_FLT(vfRlM_diagSignR, LyrN*2*LyrN*2)
    _NEW_FLT(vfRlM_temp, LyrN*2*LyrN*2) _NEW_FLT(vfRlM_temp1, LyrN*2*LyrN*2) _NEW_FLT(vfRlV_y, LyrN*2) _NEW_FLT(vfRlV_x, LyrN*2)
    
    //_NEW_INT0(viBITids_grp, BITsc*MaxN)       // example to allocate integer memory    
    //_NEW_FLT0(vfMinDST_lst, BITsc*2)          // example to allocate float  memory
    float val, Lam0[LyrN*2*4], Lam1[LyrN*2*4], Lamt[LyrN*2*4]; int i, q, bitLen, iModuMapRow, moduMap[80], constel[16];

    if(ModuType == 4){
        val = sqrt(2);
        RlMatNum_mul_REF(vfCxR_list, vfCxR_list, val, 1, SCnum*LyrN*2);//y = y*sqrt(2);
        int moduMap0[4] = {2,0,0,1};
        for(i=0;i<4;i++){
            moduMap[i] = moduMap0[i];
        }
        int constel0[2] = {2, 0};
        for(i=0;i<2;i++){
            constel[i] = constel0[i];
        }
        q = 1;
        bitLen =1;
        //int iModuMapRow = 2 , iModuMapcol = 2;
        for(i=0;i<LyrN*2;i++)
        {
            Lam0[i] = Lam1[i] = 20;
        }
    }
    if(ModuType == 16){
        val = sqrt(10);
        RlMatNum_mul_REF(vfCxR_list, vfCxR_list, val, 1, SCnum*LyrN*2);//y = y*sqrt(10);
        //int moduMap[4][3] = {{4,0,0},{6,0,1},{2,1,0},{0,1,1}};
        int moduMap0[12] = {4,0,0,6,0,1,2,1,0,0,1,1};
        for(i=0;i<12;i++){
            moduMap[i] = moduMap0[i];
        }
        int constel0[4] = {4,6,2,0};
        for(i=0;i<4;i++){
            constel[i] = constel0[i];
        }
        q = 3;
        bitLen =2;
        //int iModuMapRow = 4 , iModuMapcol = 3;
        for(i=0;i<LyrN*2*2;i++)
        {
            Lam0[i] = Lam1[i] = 30;
        }
    }
    if(ModuType ==64){
        val = sqrt(42);
        RlMatNum_mul_REF(vfCxR_list, vfCxR_list, val, 1, SCnum*LyrN*2);//y = y*sqrt(42);
        int moduMap0[32] = {10,0,0,0,8,0,0,1,12,0,1,0,14,0,1,1,4,1,0,0,6,1,0,1,2,1,1,0,0,1,1,1};
        for(i=0;i<32;i++){
            moduMap[i] = moduMap0[i];
        }
        int constel0[8] = {10,8,12,14,4,6,2,0};
        for(i=0;i<8;i++){
            constel[i] = constel0[i];
        }
        q = 7;
        bitLen =3;
        //int iModuMapRow = 8 , iModuMapcol = 4;

        for(i=0;i<LyrN*2*3;i++)
        {
            Lam0[i] = Lam1[i] = 40;
        }
    }
    if(ModuType == 256){
        val = sqrt(170);
        RlMatNum_mul_REF(vfCxR_list, vfCxR_list, val, 1, SCnum*LyrN*2);//y = y*sqrt(170);   
        int moduMap0[80] = {20,0,0,0,0,22,0,0,0,1,18,0,0,1,0,16,0,0,1,1,26,0,1,0,0,24,0,1,0,1,28,0,1,1,0,
        30,0,1,1,1,10,0,1,1,1,8,1,0,0,1,12,1,0,1,0,14,1,0,1,1,4,1,1,0,0,6,1,1,0,1,2,1,1,1,0,0,1,1,1,1};
        for(i=0;i<80;i++){
            moduMap[i] = moduMap0[i];
        }
        //int iModuMapRow = 16 , iModuMapcol = 5;
        int constel0[16] = {20,22,18,16,26,24,28,30,10,8,12,14,4,6,2,0};
        for(i=0;i<16;i++){
            constel[i] = constel0[i];
        }
        q = 15;
        bitLen =4;
        for(i=0;i<LyrN*2*4;i++)
        {
            Lam0[i] = Lam1[i] = 50;
        }
    }
    _NEW_FLT(bitX, LyrN*2*bitLen) _NEW_FLT(Lam,LyrN*2*bitLen) _NEW_FLT(maxL,1)
    float *pfllrs, *pfCxR_list , *pfCxH_list, *plam;
    pfllrs = vfllrs; pfCxR_list = vfCxR_list; pfCxH_list = vfCxH_list;
    //float addX[LyrN][2]; //ones(size(H,2),1)*q*(1+1j)
    float addX[LyrN*2];
    int j,kkk,iii,ttt,ii,jj;
    for(i=0;i<LyrN*2;i++) 
    {
        addX[i] = q;
    }
    //
    //  float* pfaddX;
    //  pfaddX = addX;
    //  _isPrintF("\nq*(1+1j)\n");
    //  Print_Mat(addX, LyrN, 2, 1); 
    //
    //float y[LyrN*2][1], M[LyrN*2][LyrN*2], addY[LyrN][2];
    float y[LyrN*2], M[LyrN*2*LyrN*2], addY[LyrN*2];
    //float* pfaddY;
    //pfaddY = addY;
    //
    //_isPrintF("\nY1\n");
    //Print_Mat(pfCxR_list, LyrN, 2, 1);
    //
    //_isPrintF("\nH1\n");
    //Print_Mat(pfCxH_list, LyrN, LyrN*2, 1); 
    //
    //
    //_isPrintF("\npfCxR_list\n");
    //_isPrintF("\n%p\n",pfCxR_list);
    //
    _LOOPUP_LT(kkk,0, SCnum) {
        maxL[0] = 0;
        pfllrs = pfllrs + kkk*LyrN*bitLen*2; pfCxR_list = pfCxR_list + kkk*LyrN*2; pfCxH_list = pfCxH_list + kkk*LyrN*LyrN*2;
        //
        //_isPrintF("\npfCxR_list\n");
        //_isPrintF("\n%p\n",pfCxR_list);
        //

        //RlMatNum_mul_REF(pfCxR_list, pfCxR_list, val, LyrN, 2);//y = y*sqrt(val);
        //
        //_isPrintF("\nY\n");
        //Print_Mat(pfCxR_list, LyrN, 2, 1);
        //
        //_isPrintF("\nH\n");
        //Print_Mat(pfCxH_list, LyrN, LyrN*2, 1); 
        //
        CxMat_mul_REF(addY, pfCxH_list, addX, LyrN, LyrN, 1, 1); //H*ones(size(H,2),1)*q*(1+1j)
        //
        //_isPrintF("\naddY\n");
        //Print_Mat(addY, LyrN, 2, 1); 
        //  
        for(i=0;i<LyrN*2;i++) //y = (y+H*ones(size(H,2),1)*q*(1+1j));y = [real(y); imag(y)];
        {
            if(i%2)
                y[i/2+LyrN] = pfCxR_list[i] + addY[i]; 
            else
                y[i/2] = pfCxR_list[i] + addY[i]; 
                
        }
        //float* pfy;
        //pfy = y;
        //
        //_isPrintF("\ny\n");
        //Print_Mat(y, LyrN*2, 1, 1); 
        //  
        for(i=0;i<LyrN;i++)//M = [real(H) -imag(H); imag(H) real(H)];
        {
            for(j=0;j<LyrN*2;j++)
            {
                if(j%2){
                    M[i*LyrN*2+j/2+LyrN] = -pfCxH_list[i*LyrN*2+j];
                    M[(i+LyrN)*LyrN*2+j/2] = pfCxH_list[i*LyrN*2+j];
                }
                else{
                    M[i*LyrN*2+j/2] = pfCxH_list[i*LyrN*2+j]; 
                    M[(i+LyrN)*LyrN*2+j/2+LyrN] = pfCxH_list[i*LyrN*2+j];
                }
            }
        }
        //
        //float* pfM;
        //pfM = M;
        //_isPrintF("\nM\n");
        //Print_Mat(M, LyrN*2, LyrN*2, 1); 
        //
        //[Q,R] = qr(M);
        RlMat_QRdec_REF(vfRlM_Q, vfRlM_R, M, LyrN*2, LyrN*2);
        //
        //_isPrintF("\nQ\n");
        //Print_Mat(vfRlM_Q, LyrN*2, LyrN*2, 1); 
        //
        //
        //_isPrintF("\nR\n");
        //Print_Mat(vfRlM_R, LyrN*2, LyrN*2, 1); 
        //
        _LOOPUP_LT(iii,0, LyrN*2*LyrN*2) {
            vfRlM_diagSignR[iii] = 0;
        }
        _LOOPUP_LT(ttt,0, LyrN*2) {
            if (vfRlM_R[ttt*LyrN*2 + ttt]>0){
                vfRlM_diagSignR[ttt*LyrN*2 + ttt] = 1;
            }
            else{
                vfRlM_diagSignR[ttt*LyrN*2 + ttt] = -1;     
            }
        }
        //
        RlMat_mul_REF(vfRlM_temp, vfRlM_diagSignR, vfRlM_R, LyrN*2, LyrN*2, LyrN*2, 1);
        
        RlMat_copy_REF(vfRlM_R, vfRlM_temp, LyrN*2, LyrN*2, 1);
        
        RlMat_tranpose_REF(vfRlM_temp, vfRlM_Q, LyrN*2, LyrN*2);
        
        RlMat_mul_REF(vfRlM_temp1, vfRlM_diagSignR, vfRlM_temp, LyrN*2, LyrN*2, LyrN*2, 1);
    
        RlMat_mul_REF(vfRlV_y, vfRlM_temp1, y, LyrN*2, LyrN*2, 1, 1);
        //
        _isPrintF("\nR\n");
        Print_Mat(vfRlM_R, LyrN*2, LyrN*2, 1); 
        //
        //
        _isPrintF("\ny\n");
        Print_Mat(vfRlV_y, LyrN*2, 1, 1); 
        //
        _isPrintF("\nLam0\n");
        Print_Mat(Lam0, LyrN*2, bitLen, 1); 
        //
        //
        _isPrintF("\nLam1\n");
        Print_Mat(Lam1, LyrN*2, bitLen, 1); 
        //
        //
        _isPrintF("\nconstel\n");
        Print_intMat(constel, 1, pow(2,bitLen), 1); 
        //
        //
        _isPrintF("\nmoduMap\n");
        Print_intMat(moduMap, pow(2,bitLen), (bitLen + 1), 1); 
        //
        //sd
        recur_sd(Lam0, Lam1, vfRlV_y, vfRlV_x, bitX, 0, vfRlM_R, LyrN*2 - 1, constel, moduMap, maxL, bitLen, LyrN*2);
        //
        _isPrintF("\nLam0\n");
        Print_Mat(Lam0, LyrN*2, bitLen, 1); 
        //
        //
        _isPrintF("\nLam1\n");
        Print_Mat(Lam1, LyrN*2, bitLen, 1); 
        //
        RlMat_sub_REF(Lamt, Lam0, Lam1, LyrN*2, bitLen, 1);//L = Lam0 - Lam1
        RlMatNum_mul_REF(Lamt, Lamt, 1/val, 1, bitLen*LyrN*2);//L = L/sqrt(val);
        //
        _isPrintF("\nLamt\n");
        Print_Mat(Lamt, LyrN*2, bitLen, 1); 
        //
        float* pLam;
        pLam = Lam;
        

        _LOOPUP_LT(ii,0, LyrN){
            _LOOPUP_LT(jj,0, bitLen){
                //_isPrintF("\n%d\n",((jj%2)*LyrN+ii)*bitLen+(jj/2));
                pLam[ii*2*bitLen + jj*2] = Lamt[ii*bitLen + jj];//Lamt[((jj%2)*LyrN+ii)*bitLen+(jj/2)];//Lamt[(jj%2)*LyrN+ii][(jj/2)];
            }
        }
        _LOOPUP_LT(ii,LyrN, 2*LyrN){
            _LOOPUP_LT(jj,0, bitLen){
                pLam[(ii - LyrN)*2*bitLen + jj*2 + 1] = Lamt[ii*bitLen + jj];
            }
        }
        //
        _isPrintF("\nLam\n");
        Print_Mat(Lam, LyrN, bitLen*2, 1); 
        //
        RlMat_copy_REF(pfllrs, Lam, LyrN, 2*bitLen, 1); 
    
    }
    _NEW_FREE()         // free all local memories

}



#define ___GET_QamBITS__(__MT)  ((((__MT)>>1)&0x1)*1+(((__MT)>>2)&0x1)*2+(((__MT)>>3)&0x1)*3+(((__MT)>>4)&0x1)*4+(((__MT)>>6)&0x1)*6+(((__MT)>>8)&0x1)*8+(((__MT)>>10)&0x1)*10)

void   MIMO_mldDec_ITF(float *vfLLRS, float* vfCxR_list, float* vfCxH_list, int LyrN, int ModuType, int SCnum, float fNoisePwr, int OFDMnum)
/*
*  OFDMnum   : number of OFDM symbols sharing same H
*/
{
    float *pfllrs, *pfCxRs, *pfCxHs;   int cnt;
    int QamB  = ___GET_QamBITS__(ModuType);             // get bit number for given ModuType

    _LOOPUP_LT(cnt, 0, OFDMnum) {
        pfllrs = vfLLRS     + cnt*SCnum*LyrN*QamB;
        pfCxRs = vfCxR_list + cnt*SCnum*LyrN*2;
        MIMO_mldDec(pfllrs, pfCxRs,  vfCxH_list,  LyrN, SCnum, ModuType, fNoisePwr);
    }

}


/*
int main(void)
{
    int SCnum = 1, LyrN = 2, ModuType = 16; float val = 10, fNoisePwr = 100;
    _NEW_INIT()   _NEW_FLT(vfllrs, LyrN*2*LyrN*2) _NEW_FLT(vfCxT_list, LyrN*2) _NEW_FLT(vfCxR_list, LyrN*2) _NEW_FLT(vfCxH_list, LyrN*2*LyrN)
    vfCxT_list[0] = -1, vfCxT_list[1] = 1, vfCxT_list[2] = 1, vfCxT_list[3] = -1;
    //
    _isPrintF("\nx\n");
    Print_Mat(vfCxT_list, LyrN, 2, 1);

    vfCxH_list[0] = -0.5, vfCxH_list[1] = -0.1, vfCxH_list[2] = 1, vfCxH_list[3] = 1, vfCxH_list[4] = -1, vfCxH_list[5] = -1, vfCxH_list[6] = -1, vfCxH_list[7] = -1;

    //
    _isPrintF("\nH\n");
    Print_Mat(vfCxH_list, LyrN, LyrN*2, 1); 
    //
    RlMatNum_mul_REF(vfCxT_list, vfCxT_list, (1/sqrt(val)), LyrN, 2);
    //
    _isPrintF("\nval=%f\n",(1/sqrt(val)));
    _isPrintF("\nx\n");
    Print_Mat(vfCxT_list, LyrN, 2, 1); 
    //  
    CxMat_mul_REF(vfCxR_list, vfCxH_list, vfCxT_list, LyrN, LyrN, 1, 1);
    //
    _isPrintF("\ny\n");
    Print_Mat(vfCxR_list, LyrN, 2, 1); 
    //  
    MIMO_mldDec(vfllrs, vfCxR_list, vfCxH_list, LyrN, SCnum, ModuType, fNoisePwr);
    
    
    return 0;
}
*/
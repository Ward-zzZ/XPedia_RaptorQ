#include "PerfMetric_COMM.h"

#include "XPedia_AMCsmp.h"

void CxMat_pickCOLS(float *vfCxM_pick, float *vfCxM_src, int iRow, int iCol, int PickN, int iFrom)
/* pick columns of a complex matrix
*  vfCxM_pick : complex matrix composd of picked columns
*  vfCxM_src  : source complex matrix
*  iRow       : row number of source matrix
*  iCol       : col number of source matrix
*  PickN      : number of picked columns
*  iFrom      : the starting index of picked columns
Change History
*  1st version designed by Duan Weiming in 2021-03-17
*/
{

  retERR_LEZ3(iRow, iCol, PickN) retERR_RNG(iFrom, 0, iCol - 1) retERR_CHK((iFrom + PickN) > iCol)

      MEMCHK(vfCxM_pick, iRow * PickN * 2) MEMCHK(vfCxM_src, iRow * iCol * 2)

          int SRCcol = iCol * 2;
  int SRCfrom = iFrom * 2;
  int DSTcol = PickN * 2;
  int DSTfrom = 0;
  int MATrow = iRow;
  int COLcpy = DSTcol;
  int CloneN = 1;

  Mat_colcopy(vfCxM_pick, vfCxM_src, SRCcol, SRCfrom, DSTcol, DSTfrom, MATrow, COLcpy, CloneN);
  int iTST = 3;
}

void Mat_pickCOLS(float *vfMat_pick, float *vfMat_src, int iRow, int iCol, int PickN, int iFrom)
/* pick columns of a real matrix
*  vfMat_pick : real matrix composd of picked columns
*  vfMat_src  : source real matrix
*  iRow       : row number of source matrix
*  iCol       : col number of source matrix
*  PickN      : number of picked columns
*  iFrom      : the starting index of picked columns
Change History
*  1st version designed by Duan Weiming in 2021-03-17
*/
{

  retERR_LEZ3(iRow, iCol, PickN) retERR_RNG(iFrom, 0, iCol - 1) retERR_CHK((iFrom + PickN) > iCol)

      MEMCHK(vfMat_pick, iRow * PickN) MEMCHK(vfMat_src, iRow * iCol)

          int SRCcol = iCol;
  int SRCfrom = iFrom;
  int DSTcol = PickN;
  int DSTfrom = 0;
  int MATrow = iRow;
  int COLcpy = DSTcol;
  int CloneN = 1;

  Mat_colcopy(vfMat_pick, vfMat_src, SRCcol, SRCfrom, DSTcol, DSTfrom, MATrow, COLcpy, CloneN);
  int iTST = 3;
}

void CxHs_merge(float *vfCxHs_full, float *vfCxHs_part, int RxM, int MaxN, int LyrN, int LyrBias, int MATnum)
/* merge partial H  into one full H
*  vfCxHs_full : list of full H
*  vfCxHs_part : list of partial H
*  RxM         : number of receive channels
*  MaxN        : max number of layers
*  LyrN        : layer number of partial H
*  LyrBias     : layer offset (the start column in full H)
*  MATnum      : number of H
Change History
*  1st version designed by Duan Weiming in 2021-03-15
*/
{

  retERR_LEZ4(RxM, MaxN, LyrN, MATnum) retERR_RNG(LyrBias, 0, MaxN - 1) retERR_CHK((LyrBias + LyrN) > MaxN)

      MEMCHK(vfCxHs_full, MATnum * RxM * MaxN * 2)
          MEMCHK(vfCxHs_part, MATnum * RxM * LyrN * 2) int isPULL = 0; // push partial H into  full H
  int isTranpose = 0;
  int iRbias = 0;
  int iCbias = LyrBias;
  CxMats_pullORG(vfCxHs_part, RxM, LyrN, vfCxHs_full, RxM, MaxN, iRbias, iCbias, isTranpose, isPULL, MATnum);

  int iTST = 3;
}

GMEM_REG(gfSMPctrl_PMsBUF)

void SMP_init(int *viMPCs_list, int MPClen, int NetTBS, int QamNUM, int iModuType, float fEsN0_dB, int BSnum, int RXnum, int PMslen, int iAMC_ON)
/* initilization for Symm. & Sync. Multi-Point transmission control
*  viMPCs_list : list of MPC param. groups
*  MPClen      : length of each group of AMC params
*  NetTBS      : net TBS
*  QamNUM      : number of Qams
*  iModuType   : Modulation Type (2,4,16,64,256)
*  fEsN0_dB    : refrence EsN0 in dB
*  RXnum       : number of receive channels
*  BSnum       : number of BS
*  PMslen      : reserved memory length for each Precoding matrix
Change History
*  1st version designed by Duan Weiming in 2021-03-15~2021-03-18
*/
{
  //int iAMC_ON = 1;   //retERR_CHK( PMslen < SubBN*TXnum*LyrN*2)
  retERR_LEZ5(MPClen, NetTBS, QamNUM, BSnum, PMslen) int iBUFFlen_PMs = PMslen * (MAX_MEAS_DLY + 10);
  float *pfGmem;
  int jjj, cnt;
  stAMC *psAMC;
  int *pMPCmem;

  MEMCHK(viMPCs_list, BSnum * MPClen)
  INT_ZERO(viMPCs_list, BSnum * MPClen);

  _NEW_INIT()
  _NEW_FLT0(vfCxPM_SBD, PMslen) //MIMO_precoderRST( vfCxPM_SBD,  SubBN, TXnum,  LyrN);

  _LOOPUP_LT(cnt, 0, BSnum)
  {
    pMPCmem = viMPCs_list + cnt * MPClen;
    *pMPCmem++ = 1;
    *pMPCmem++ = cnt;
    psAMC = (stAMC *)pMPCmem;
    AMC_init(pMPCmem, NetTBS, QamNUM, iModuType, fEsN0_dB, RXnum, iAMC_ON);

    GMEM_NEW(pfGmem, gfSMPctrl_PMsBUF, iBUFFlen_PMs)
    stRingBUF_init((int *)&psAMC->m_RingBUF_PMs, pfGmem, iBUFFlen_PMs, 0.0);
    _LOOPUP_LT(jjj, 0, MAX_MEAS_DLY + 10) { stRingBUF_push((int *)&psAMC->m_RingBUF_PMs, vfCxPM_SBD, PMslen); }
  }

  _NEW_FREE()
}

int SMP_control(int *viMPCs_list, int MPClen, float *vfCxPM_SBD, int *viINFOs_list, int MaxTBS, int *viCRC_list, float *vfSNR_list, float *vfCxPMsmeas, int PMslen, int SubBN, int TxN, int isPMok, int *viTransblock, int LyrN, int BSnum, int iSNRdlyTTI, int iPMIdlyTTI, int *viCRCblock, int *viNetTBs)
/* Symm. & Sync. Multi-Point transmission control
*  viMPCs_list  : list of MPC param. groups
*  MPClen       : length of each group of AMC params
*  viINFOs_list : CxHs_part
*  MaxTBS       : max length of TBS
*  viCRC_list   : ACK/NACK for each BS
*  vfSNR_list   : measured SNR  for each BS
*  vfCxPMsmeas  : precoding matrix for each BS
*  PMslen       : reserved memory length for each precoding matrix (equal or bigger than real size of Precoding matrix)
*  isPMok       : Precoding matrice are ready or not ?
*  LyrN         : number of layers
*  BSnum        : number of BS
*  iSNRdlyTTI   : delayed TTIs for  SNR meas report
*  iPMIdlyTTI   : delayed TTIs for PMI meas report
Change History
*  1st version designed by Duan Weiming in 2021-03-16~2021-03-19
*/
{
  //int iSNRdlyTTI  = 0;  // no delay for up-bound!!!
  ret0ERR_LEZ3(MPClen, MaxTBS, BSnum) ret0ERR_LT(MPClen, (sizeof(stAMC) >> 2)) ret0ERR_RNG(BSnum, 1, 3) ret0ERR_RNG(iSNRdlyTTI, 0, MAX_MEAS_DLY) ret0ERR_RNG(iPMIdlyTTI, 0, MAX_MEAS_DLY) int jjj, cnt;
  int *pMPCmem, *piCWBITs;
  float fEsN0_meas;
  int iNACK;
  stAMC *psAMC;
  float *pfCxPMsrc, *pfCxPMuse, *pfCxPMout;
  float fScaling;
  GET_GPARAM_INT(gMIMO_RandomPrecoding_ON)

  MEMCHK(viMPCs_list, BSnum * MPClen)
  MEMCHK(viINFOs_list, BSnum * MaxTBS)
  MEMCHK(viCRC_list, BSnum)
  MEMCHK(vfSNR_list, BSnum) MEMCHK(vfCxPMsmeas, BSnum * PMslen)

      _NEW_INIT() _NEW_FLT0(vfCxPMsnew, PMslen)

          int iLyrPerBS = MAXOP((LyrN / BSnum), 1);
  if (iLyrPerBS * BSnum < LyrN)
  {
    iLyrPerBS += 1;
  }
  int SumN = 0;
  int iLyrN0;
  int BSuse = 0;
  //
  _LOOPUP_LT(cnt, 0, BSnum)
  {
    pfCxPMsrc = vfCxPMsmeas + cnt * PMslen;
    pfCxPMuse = pfCxPMsrc;
    pfCxPMout = vfCxPM_SBD + cnt * PMslen;
    pMPCmem = viMPCs_list + cnt * MPClen;
    piCWBITs = viINFOs_list + cnt * MaxTBS;
    fEsN0_meas = vfSNR_list[cnt];
    // iNACK      =  viCRC_list[cnt];
    iNACK = viCRCblock[cnt];

    iLyrN0 = MINOP(iLyrPerBS, LyrN - SumN);
    *pMPCmem++ = iLyrN0;
    *pMPCmem++ = SumN;
    SumN += iLyrN0;
    psAMC = (stAMC *)pMPCmem;
    if (0 == iLyrN0)
    {
      AMC_rst((int *)psAMC);
      continue;
    }

    // //succeed after 4 times trans
    // if (iNACK == 0)
    // {
    //   viTransblock[psAMC->m_Transtimes]++;
    // }
    // //number of TB with different re-trans times
    // if (iNACK == 1)
    // {
    //   viTransblock[4+psAMC->m_Transtimes]++;
    // }

    // //succeed after 4 times trans
    // if (iNACK == 1 && psAMC->m_Transtimes == MAX_TRANSTIMES - 1)
    // {
    //   viTransblock[1]++;
    // }
    // //number of TB with different re-trans times
    // if (iNACK == 0 && psAMC->m_Transtimes == MAX_TRANSTIMES - 1)
    // {
    //   viTransblock[0]++;
    // }
    //succeed after 4 times trans
    if (iNACK == 1 && psAMC->m_Transtimes == 0)
    {
      viTransblock[1]++;
    }
    //number of TB with different re-trans times
    if (iNACK == 0 && psAMC->m_Transtimes == 0)
    {
      viTransblock[0]++;
    }
    //AMC_control((int*)psAMC, piCWBITs, MaxTBS,  iNACK,  fEsN0_meas, iSNRdlyTTI,LyrN);   // iLyrN0 ==> LyrN !!!  it is a bug !!!
    AMC_control((int *)psAMC, piCWBITs, MaxTBS, viCRC_list[cnt], fEsN0_meas, iSNRdlyTTI, iLyrN0);

    if (0 == isPMok)
    {
      FLT_ZERO(pfCxPMsrc, PMslen);
      MIMO_precoderRST(pfCxPMsrc, SubBN, TxN, iLyrN0, 0);
    } // isRandomPM = 0

    if (gMIMO_RandomPrecoding_ON)
    {
      pfCxPMuse = vfCxPMsnew;
      MIMO_precoderRST(pfCxPMuse, SubBN, TxN, iLyrN0, 1);
    } // isRandomPM = 1
    // rediculous!!! it is supposed that precoding matrix shall not be normalized here!!!! ,  commented by Duan Weiming in 2021-05-21
    //fScaling = 1.0/sqrt(SubBN*TxN*iLyrN0);   VEC_mulC(pfCxPMsrc, SubBN*TxN*iLyrN0*2, fScaling); // normalize precoding matrix, incorrect design !!! , added by Duan Weiming in 2021-05-21
    if (1 < iLyrN0)
    {
      fScaling = 1.0 / sqrt(iLyrN0);
      VEC_mulC(pfCxPMuse, SubBN * TxN * iLyrN0 * 2, fScaling);
    } // does it work correctly ??? , added by Duan Weiming in 2021-05-21

    stRingBUF_push((int *)&psAMC->m_RingBUF_PMs, pfCxPMuse, PMslen);
    if (isPMok)
    {
      stRingBUF_pop((int *)&psAMC->m_RingBUF_PMs, pfCxPMout, PMslen, iPMIdlyTTI, 1);
    } // 1 : isBlkITEM
    else
    {
      FLT_CP(pfCxPMuse, pfCxPMout, PMslen);
    } // added for bug fix , by Duan Weiming in 2021-03-19
    BSuse++;
  }

  pMPCmem = viMPCs_list + 0 * MPClen;
  MEM_5INT(pMPCmem, RvID0, RVlen0, NetTBS0, QamType0, iMCS0)
  pMPCmem = viMPCs_list + 1 * MPClen;
  MEM_5INT(pMPCmem, RvID1, RVlen1, NetTBS1, QamType1, iMCS1)

  *viNetTBs = NetTBS0;
  *(viNetTBs + 1) = NetTBS1;

  if ((iMCS0 != iMCS1) || (QamType0 != QamType1) || (NetTBS0 != NetTBS1))
  {
    int iTST = 3;
  }

  _NEW_FREE()

  return BSuse;
}

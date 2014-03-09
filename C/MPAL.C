/* ******************************************************************** */
/* MPEG AUDIO MMIO PROC - MAIN SOURCE CODE                              */
/* ENCODE: LAYER-2 L2 COMP                                              */
/*                                                                      */
/*                                                        Version 1.0.0 */
/*                                Copyrights(c) 1999-2000, Yuuriru Mint */
/*                         TEAM MMOS/2 TOKYO Multimedia Communications! */
/* ******************************************************************** */
/* Watcom C/C++ 10.0 英語版 + Warp 4 Toolkit                            */
/* Library: MMPM2.LIB LUCIER.LIB (2.3) LLCDIOCT.LIB                     */
/* ******************************************************************** */
#define INCL_ESC_NO_NETWORK
#define INCL_ESC_NO_WARP4
#include <LUCIER.H>

#include "MMIOPROC.H"

#define  FOURCC_MMIOPROC_DEF        FOURCC_MMIOPROC_MPAL
#define  NAME_DEF                   NAME_MPAL
#define  NAMEJ_DEF                  NAMEJ_MPAL
#define  EXT_DEF                    EXT_MPAL
#define  SUPPORTFLAG_DEF            SUPPORTFLAG_MPAL

/* ******************************************************************** */
/* メイン関数                                                           */
/* ******************************************************************** */
LONG EXPENTRY _export MMIOENTRY_MPAL(PVOID pVoid,USHORT usMsg,LONG mp1,LONG mp2)  {
LONG              lRC=MMIO_ERROR;
MMIOINFO          *pMMInfo=NULL;
PMMFORMATINFO     pMMFmtInfo;

   pMMInfo=(PMMIOINFO)pVoid;

   switch(usMsg)  {
   /* ***************************************************************** */
   /* オープン                                                          */
   /* ***************************************************************** */
   case MMIOM_OPEN:
      if(!pMMInfo)   break;
      pMMInfo->pExtraInfoStruct=(PVOID)(MPA_EFLAG_LAY_2|MPA_EFLAG_DOUBLIZECOMP);
      lRC=MMIOENTRY(pVoid, usMsg, mp1, mp2);
      break;
   /* ***************************************************************** */
   /* このサービスのフォーマット情報を返す                              */
   /* ***************************************************************** */
   case MMIOM_GETFORMATINFO:
      lRC=MMIOENTRY(pVoid, usMsg, mp1, mp2);
      pMMFmtInfo=(PMMFORMATINFO)mp1;
      if(!pMMFmtInfo) break;
      pMMFmtInfo->fccIOProc    = FOURCC_MMIOPROC_DEF;
      pMMFmtInfo->ulFlags      = SUPPORTFLAG_DEF;
      strcpy((PSZ)pMMFmtInfo->szDefaultFormatExt,EXT_DEF);
      if(EscReadyForJapanese())  pMMFmtInfo->lNameLength=sizeof(NAMEJ_DEF)+1;
      else  pMMFmtInfo->lNameLength=sizeof(NAME_DEF)+1;
      break;
   /* ***************************************************************** */
   /* このサービスのフォーマット名を返す                                */
   /* ***************************************************************** */
   case MMIOM_GETFORMATNAME:
      lRC=0L;
      if(!mp1) break;

      if(EscReadyForJapanese())  lRC=sizeof(NAMEJ_DEF);
      else  lRC=sizeof(NAME_DEF);
      if(lRC>=mp2)   { strcpy((PCHAR)mp1,EXT_DEF); lRC=sizeof(EXT_DEF); }
      else  {
         if(EscReadyForJapanese())  strcpy((PCHAR)mp1,NAMEJ_DEF);
         else  strcpy((PCHAR)mp1,NAME_DEF);
      }

      break;
   /* ***************************************************************** */
   /* ファイルの自動認識を行うチェックルーチン (ライトのみなので非サポ) */
   /* ***************************************************************** */
   case MMIOM_IDENTIFYFILE:
      lRC=MMIO_ERROR;
      break;
   /* ***************************************************************** */
   /* 一般処理                                                          */
   /* ***************************************************************** */
   default:
      lRC=MMIOENTRY(pVoid, usMsg, mp1, mp2);
      break;
   }
return lRC; }


/* ******************************************************************** */
/* MPEG AUDIO MMIO PROC - MAIN SOURCE CODE                              */
/* ENCODE: LAYER-1                                                      */
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

#define  FOURCC_MMIOPROC_DEF        FOURCC_MMIOPROC_MPA1
#define  NAME_DEF                   NAME_MPA1
#define  NAMEJ_DEF                  NAMEJ_MPA1
#define  EXT_DEF                    EXT_MPA1
#define  SUPPORTFLAG_DEF            SUPPORTFLAG_MPA1

/* ******************************************************************** */
/* メイン関数                                                           */
/* ******************************************************************** */
LONG EXPENTRY _export MMIOENTRY_MPA1(PVOID pVoid,USHORT usMsg,LONG mp1,LONG mp2)  {
LONG              lRC=MMIO_ERROR;
MMIOINFO          *pMMInfo=NULL;
MPAOPTIONS        MpaOpt;

   pMMInfo=(PMMIOINFO)pVoid;

   switch(usMsg)  {
   /* ***************************************************************** */
   /* オープン                                                          */
   /* ***************************************************************** */
   case MMIOM_OPEN:
      if(!pMMInfo)   break;
      MpaOpt.ulStructLen=sizeof(MPAOPTIONS);
      MpaOpt.ulFlags=MPA_EFLAG_LAY_1;
      pMMInfo->pExtraInfoStruct=(PVOID)&MpaOpt;
      lRC=MMIOENTRY(pVoid, usMsg, mp1, mp2);
      break;
   /* ***************************************************************** */
   /* このサービスのフォーマット情報を返す                              */
   /* このサービスのフォーマット名を返す                                */
   /* ***************************************************************** */
   case MMIOM_GETFORMATINFO:
      return EscDefMMIOGetFormatInfo((PMMFORMATINFO)mp1, FOURCC_MMIOPROC_DEF, MMIO_IOPROC_FILEFORMAT, MEDIATYPE, SUPPORTFLAG_DEF, NAME_DEF, NAMEJ_DEF, EXT_DEF);
   case MMIOM_GETFORMATNAME:
      return EscDefMMIOGetFormatName((PCHAR)mp1,mp2,NAME_DEF,NAMEJ_DEF,EXT_DEF);
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


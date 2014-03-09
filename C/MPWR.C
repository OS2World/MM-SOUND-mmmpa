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

#define  FOURCC_MMIOPROC_DEF        FOURCC_MMIOPROC_MPWR
#define  NAME_DEF                   NAME_MPWR
#define  NAMEJ_DEF                  NAMEJ_MPWR
#define  EXT_DEF                    EXT_MPWR
#define  SUPPORTFLAG_DEF            SUPPORTFLAG_MPWR

/* ******************************************************************** */
/* メイン関数                                                           */
/* ******************************************************************** */
LONG EXPENTRY _export MMIOENTRY_MPWR(PVOID pVoid,USHORT usMsg,LONG mp1,LONG mp2)  {
LONG              lRC=MMIO_ERROR;
MMIOINFO          *pMMInfo=NULL;
PMMFORMATINFO     pMMFmtInfo;
HMMIO hmmio;

   pMMInfo=(PMMIOINFO)pVoid;

   switch(usMsg)  {
   /* ***************************************************************** */
   /* オープン                                                          */
   /* ***************************************************************** */
   case MMIOM_OPEN:
      if(!pMMInfo)   break;
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
      if(!mp1 && !mp2)  break;
      if(!mp1) {
         hmmio=mp2;
         goto IDENTCHECK;
      }  else  {
         PCHAR    pText;
         ULONG    ulSize;
         pText=(PCHAR)mp1;
         ulSize=strlen(pText);
         if(ulSize>5 && ulSize<257)  {
            RIFFAUDIOHEADER   RiffAudio;
            CHAR              szBuffer[CCHMAXPATH];
            ULONG             ulBytesRead;
            MMIOINFO          MMInfo;
            strcpy(szBuffer,pText);
            strupr(szBuffer);
            if(strstr(szBuffer,".WAV"))  {
               lRC=MMIO_SUCCESS;
               MMInfo.ulFlags=MMIO_NOIDENTIFY;
               hmmio=mmioOpen((PCHAR)mp1,&MMInfo,MMInfo.ulFlags);
               IDENTCHECK:
               if(hmmio)   {
                  ulBytesRead=mmioRead(hmmio,(PVOID)&RiffAudio,sizeof(RIFFAUDIOHEADER));
                  if(ulBytesRead==sizeof(RIFFAUDIOHEADER))   {
                     if(RiffAudio.ulRiffCode==ESC_RIFFCODE) {
                        if(RiffAudio.ulWaveHeaderCode==ESC_MPACODE) {
                           if(RiffAudio.ulWaveHeaderFmtCode==ESC_FMTCODE) {
                              if(RiffAudio.ulDataCode==ESC_DATACODE) {
                                 if(RiffAudio.WAVEHeader.usFormatTag==ESC_DATATYPE_MPA)   {
                                    lRC=MMIO_SUCCESS;
                  }  }  }  }  }  }
                  if(mp2)  break;
                  else {
                     mmioClose(hmmio,0);
                  }
               }
            }
         }
      }
      break;
   /* ***************************************************************** */
   /* 一般処理                                                          */
   /* ***************************************************************** */
   default:
      lRC=MMIOENTRY(pVoid, usMsg, mp1, mp2);
      break;
   }
return lRC; }


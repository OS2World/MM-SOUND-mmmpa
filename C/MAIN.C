/* ******************************************************************** */
/* MPEG AUDIO MMIO PROC - MAIN SOURCE CODE                              */
/* DECODE: LAYER-1/2/3                                                  */
/* ENCODE: LAYER-1/2                                                    */
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

#define  FOURCC_MMIOPROC_DEF        FOURCC_MMIOPROC
#define  NAME_DEF                   NAME
#define  NAMEJ_DEF                  NAMEJ
#define  EXT_DEF                    EXT
#define  SUPPORTFLAG_DEF            SUPPORTFLAG

/* ******************************************************************** */
/* メイン関数                                                           */
/* ******************************************************************** */
LONG EXPENTRY _export MMIOENTRY(PVOID pVoid,USHORT usMsg,LONG mp1,LONG mp2)  {
LONG              lRC=MMIO_ERROR,ulSize,lRC2,rc,ulBack;
MMIOINFO          MMInfo,*pMMInfo=NULL;
PEXTENDMMIOINFO   pExMMInfo=NULL;
PMMFORMATINFO     pMMFmtInfo;
FOURCC            fourcc;
HMMIO             hmmio;
PCHAR             pText,pszErrorStatus;
CHAR              szBuffer[257];
PMPAOPTIONS       pMpaOpt;

   pMMInfo=(PMMIOINFO)pVoid;

   switch(usMsg)  {
   /* ***************************************************************** */
   /* オープン                                                          */
   /* ***************************************************************** */
   case MMIOM_OPEN:
      if(!pMMInfo)   break;
      pszErrorStatus="Unknown error.";
      /* ************************************************************** */
      /* 判別                                                           */
      /* ************************************************************** */
      if(!pMMInfo->fccChildIOProc)  {
         if (pMMInfo->ulFlags & MMIO_CREATE) {
            if(mmioDetermineSSIOProc((PCHAR)mp1,pMMInfo,&fourcc,NULL))
               fourcc = FOURCC_DOS;
         }  else  {
            if(mmioIdentifyStorageSystem((PCHAR)mp1,pMMInfo,&fourcc))
               return MMIO_ERROR;
         }
         if (!fourcc)  return MMIO_ERROR;
         else  pMMInfo->fccChildIOProc = fourcc;
      }
      /* ************************************************************** */
      /* 宛先ファイルのオープン                                         */
      /* ************************************************************** */
      memset(&MMInfo,0,sizeof(MMIOINFO));
      memcpy(&MMInfo,pMMInfo,sizeof(MMInfo));
      MMInfo.ulFlags|=MMIO_NOIDENTIFY;
      MMInfo.pIOProc = NULL;
      MMInfo.fccIOProc = pMMInfo->fccChildIOProc;
      /* 削除命令 */
      if (pMMInfo->ulFlags & MMIO_DELETE) {
         hmmio=mmioOpen((PCHAR)mp1,&MMInfo,MMInfo.ulFlags);
         if (!hmmio)  {                         
            pMMInfo->ulErrorRet = MMIOERR_DELETE_FAILED;                   
            return MMIO_ERROR;
         }  else  {
            return MMIO_SUCCESS;
         }
      }

      pExMMInfo=EscAllocMem(sizeof(EXTENDMMIOINFO));
      memset(pExMMInfo,0,sizeof(EXTENDMMIOINFO));

      pExMMInfo->mmDecodedAudioHdr.mmXWAVHeader.WAVEHeader.usChannels=2;
      pExMMInfo->mmDecodedAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec=44100L;
      pExMMInfo->mmDecodedAudioHdr.mmXWAVHeader.WAVEHeader.usBitsPerSample=16;
      ClcWaveInfoFromBasicInfo(&pExMMInfo->mmDecodedAudioHdr, 1000);

      pExMMInfo->mmEncodedAudioHdr.mmXWAVHeader.WAVEHeader.usChannels=2;
      pExMMInfo->mmEncodedAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec=44100L;
      pExMMInfo->mmEncodedAudioHdr.mmXWAVHeader.WAVEHeader.usBitsPerSample=16;
      ClcWaveInfoFromBasicInfo(&pExMMInfo->mmEncodedAudioHdr, 1000);

      if(DosLoadModule(szBuffer,sizeof(szBuffer),"MPAPROC",&pExMMInfo->hmod))   {
         if(DosLoadModule(szBuffer,sizeof(szBuffer),"MPAPROC.DLL",&pExMMInfo->hmod))  {
            EscFreeMem(pExMMInfo);
            return MMIO_ERROR;
         }
      }
      hmodMpaTable=pExMMInfo->hmod;

      /* MPEG AUDIO ユーザー設定オプションを獲得 */
      if(pMMInfo->pExtraInfoStruct) {
         pMpaOpt=(PMPAOPTIONS)pMMInfo->pExtraInfoStruct;
         if(pMpaOpt->ulStructLen>=sizeof(MPAOPTIONS))    {
            pExMMInfo->ulEncodeFlag=pMpaOpt->ulFlags;
         }
      }

      /* 対象ファイル名を保存 */
      if(mp1)  {
         strcpy(pExMMInfo->szMpaFileName,(PCHAR)mp1);
      }
      /* 圧縮／圧縮解除命令 */
      if(pMMInfo->ulFlags & MMIO_WRITE || pMMInfo->ulFlags & MMIO_READWRITE) {
         pExMMInfo->fEncode=TRUE;
         pExMMInfo->fAlreadyOpened=FALSE;
      }
      if(pMMInfo->ulFlags & MMIO_READ) {
         /* ファイルの簡易チェック */
         if(!MpaCheckFileIsMPA((PCHAR)mp1,NULL)) {
            DosFreeModule(pExMMInfo->hmod);
            EscFreeMem(pExMMInfo);
            return MMIO_ERROR;
         }
         /* デコード可能 */
         pExMMInfo->fDecode=TRUE;
         pExMMInfo->fAlreadyOpened=FALSE;
      }
      if(!pExMMInfo)  break;
      pMMInfo->pExtraInfoStruct=(PVOID)pExMMInfo;

      lRC=MMIO_SUCCESS;
      break;                  
   /* ***************************************************************** */
   /* クローズ                                                          */
   /* ***************************************************************** */
   case MMIOM_CLOSE:
      if(!pMMInfo)   break;
      pExMMInfo=pMMInfo->pExtraInfoStruct;
      if(!pExMMInfo)  break;

      if(pExMMInfo->fDecode)  {
         MpaCloseDecoder( pExMMInfo->lhMpa);
         MpaDestroyDecoder( pExMMInfo->lhMpa);
      }
      if(pExMMInfo->fEncode)  {
         MpaCloseEncoder( pExMMInfo->lhMpa);
         MpaDestroyEncoder( pExMMInfo->lhMpa);
      }
      DosFreeModule(pExMMInfo->hmod);

      EscFreeMem(pExMMInfo);
      pMMInfo->pExtraInfoStruct=NULL;
      lRC=MMIO_SUCCESS;
      break;
   /* ***************************************************************** */
   /* ファイルの自動認識を行うチェックルーチン (ライトのみなので非サポ) */
   /* ***************************************************************** */
   case MMIOM_IDENTIFYFILE:
      if(MpaCheckFileIsMPA((PCHAR)mp1,mp2))   lRC=MMIO_SUCCESS;
      else  lRC=MMIO_ERROR;
      break;
   /* ***************************************************************** */
   /* ヘッダを読みとる                                                  */
   /* ***************************************************************** */
   case MMIOM_GETHEADER:
      lRC=0L;
      if(!pMMInfo)   break;
      pExMMInfo=pMMInfo->pExtraInfoStruct;
      if(!pExMMInfo)  break;

      if(mp2<sizeof(MMAUDIOHEADER))  {
         pMMInfo->ulErrorRet=MMIOERR_INVALID_BUFFER_LENGTH;
         break;
      }
      if(!mp1)  {
         pMMInfo->ulErrorRet=MMIOERR_INVALID_STRUCTURE;
         break;
      }
      /* オープンされていない場合は、オープン操作を行う */
      if(!pExMMInfo->fDecode) return 0L;
      if(!pExMMInfo->fAlreadyOpened)   {
         pExMMInfo->fAlreadyOpened=TRUE;
         if(MpaCreateDecoder( &pExMMInfo->lhMpa, 0L))  {
            pExMMInfo->fDecode=FALSE;
            return MMIO_ERROR;
         }
         if(MpaQueryIdletimeDriveCheckstate(pExMMInfo->lhMpa)) DosSetPriority(PRTYS_THREAD,PRTYC_IDLETIME,0L,0L);
         if(MpaOpenDecoder( pExMMInfo->lhMpa, pExMMInfo->szMpaFileName))   {
            pExMMInfo->fDecode=FALSE;
            return MMIO_ERROR;
         }
         if(MpaQueryIdletimeDriveCheckstate(pExMMInfo->lhMpa)) DosSetPriority(PRTYS_THREAD,PRTYC_REGULAR,0L,0L);
         MpaGetHeader(pExMMInfo->lhMpa, &pExMMInfo->mmDecodedAudioHdr);
         MpaGetHeader(pExMMInfo->lhMpa, &pExMMInfo->mmMMIOAudioHdr);
         if(pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec!=44100L)   {
            pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec=44100L;
         }
      }
      /* ヘッダの読みとり命令 */
      memcpy( (PMMAUDIOHEADER)mp1, &pExMMInfo->mmMMIOAudioHdr, sizeof(MMAUDIOHEADER));
      lRC=sizeof(MMAUDIOHEADER);
      break;
   /* ***************************************************************** */
   /* ヘッダを書き込む                                                  */
   /* ***************************************************************** */
   case MMIOM_SETHEADER:
      lRC=0L;
      if(!pMMInfo)   break;
      if(!mp1)  {
         pMMInfo->ulErrorRet=MMIOERR_INVALID_STRUCTURE;
         break;
      }

      pExMMInfo=pMMInfo->pExtraInfoStruct;
      if(!pExMMInfo)  break;
      memcpy(&pExMMInfo->mmDecodedAudioHdr, (PCHAR)mp1, sizeof(MMAUDIOHEADER));
      memcpy(&pExMMInfo->mmMMIOAudioHdr, (PMMAUDIOHEADER)mp1, sizeof(MMAUDIOHEADER));
      MpaGetHeader(pExMMInfo->lhMpa, &pExMMInfo->mmEncodedAudioHdr);
      lRC=sizeof(MMAUDIOHEADER);
      break;
   /* ***************************************************************** */
   /* ヘッダサイズを返す                                                */
   /* ***************************************************************** */
   case MMIOM_QUERYHEADERLENGTH:
      lRC=sizeof(MMAUDIOHEADER);
      break;
   /* ***************************************************************** */
   /* 読みとり(アプリ側からみて)                                        */
   /* ***************************************************************** */
   case MMIOM_READ:
      lRC=0L;
      if(!pMMInfo)   break;
      pExMMInfo=pMMInfo->pExtraInfoStruct;
      if(!pExMMInfo)  break;
      if(!mp2) return 0L;
      /* オープンされていない場合は、オープン操作を行う */
      if(!pExMMInfo->fDecode) return 0L;
      if(!pExMMInfo->fAlreadyOpened)   {
         if(MpaCreateDecoder( &pExMMInfo->lhMpa, 0L))  {
            pExMMInfo->fDecode=FALSE;
            return 0L;
         }
         if(MpaOpenDecoder( pExMMInfo->lhMpa, pExMMInfo->szMpaFileName))   {
            pExMMInfo->fDecode=FALSE;
            return 0L;
         }
         pExMMInfo->fAlreadyOpened=TRUE;
         MpaGetHeader(pExMMInfo->lhMpa, &pExMMInfo->mmDecodedAudioHdr);
         MpaGetHeader(pExMMInfo->lhMpa, &pExMMInfo->mmMMIOAudioHdr);
         if(pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec!=44100L)   {
            pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec=44100L;
         }
      }
      /* ***************************************************************** */
      /* 読みとり命令                                                      */
      /* ***************************************************************** */
      if(MpaQueryIdletimeDriveCheckstate(pExMMInfo->lhMpa)) DosSetPriority(PRTYS_THREAD,PRTYC_IDLETIME,0L,0L);

      /* 周波数変換 ～ このサービスで出力する周波数と違う場合 */
      if(pExMMInfo->mmDecodedAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec!=pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec)   {
        /* 最適な読みとりサイズを計算 */
         if(!pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec)  pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec=44100L;
         pExMMInfo->ldSrc.ulSize=mp2
            * pExMMInfo->mmDecodedAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec
            / pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec;
         pExMMInfo->ldSrc.ulSize&=0xFFFFFFFCL;
         pExMMInfo->ldSrc.pBuffer=EscAllocMem(pExMMInfo->ldSrc.ulSize);
      }  else  {
         pExMMInfo->ldSrc.pBuffer=(PCHAR)mp1;
         pExMMInfo->ldSrc.ulSize=mp2;
      }
      pExMMInfo->ldSrc.pStruct=&pExMMInfo->mmDecodedAudioHdr;

      /* ここで読みとり */
      lRC=MpaRead( pExMMInfo->lhMpa, (PCHAR)pExMMInfo->ldSrc.pBuffer, pExMMInfo->ldSrc.ulSize);
      /* ここで読みとり完了 */

      /* 周波数変換 ～ このサービスで出力する周波数と違う場合 */
      if(pExMMInfo->mmDecodedAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec!=pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec)   {
         if(pExMMInfo->ldSrc.ulSize==lRC)    ulBack=mp2;
         else ulBack=0L;
         pExMMInfo->ldSrc.ulSize=lRC;
         pExMMInfo->ldDest.pStruct=&pExMMInfo->mmMMIOAudioHdr;
         rc=CnvWaveFreq( &pExMMInfo->ldDest, &pExMMInfo->ldSrc, (PVOID)pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec);
         /* メモリーを受け渡し */
         if(!rc)  {
            if(pExMMInfo->ldDest.ulSize>mp2) pExMMInfo->ldDest.ulSize=mp2;
            memcpy((PCHAR)mp1,pExMMInfo->ldDest.pBuffer,pExMMInfo->ldDest.ulSize);
            if(ulBack)    lRC=ulBack;
            else  {
               lRC=pExMMInfo->ldDest.ulSize;
            }
            EscFreeMem(pExMMInfo->ldDest.pBuffer);
         }  else  {
            if(lRC>mp2) lRC=mp2;
         }
         /* 作業メモリーの解放 */
         EscFreeMem(pExMMInfo->ldSrc.pBuffer);
      }
      if(MpaQueryIdletimeDriveCheckstate(pExMMInfo->lhMpa)) DosSetPriority(PRTYS_THREAD,PRTYC_REGULAR,0L,0L);
      break;
   /* ***************************************************************** */
   /* 読みとり(アプリ側からみて)                                        */
   /* ***************************************************************** */
   case MMIOM_WRITE:                   
      lRC=0L;
      if(!pMMInfo)   break;
      pExMMInfo=pMMInfo->pExtraInfoStruct;
      if(!pExMMInfo)  break;
      if(!mp2) return 0L;
      if(!pExMMInfo->fEncode) return 0L;
      /* オープンされていない場合は、オープン操作を行う */
      if(!pExMMInfo->fAlreadyOpened) {
         if(pExMMInfo->mmDecodedAudioHdr.mmXWAVHeader.WAVEHeader.usChannels<=1)  { pExMMInfo->ulEncodeFlag&=0xFFFFF0FFL; pExMMInfo->ulEncodeFlag|=MPA_EFLAG_MD_MONORAL; }
         if(MpaCreateEncoder( &pExMMInfo->lhMpa, pExMMInfo->ulEncodeFlag))  {
            pExMMInfo->fEncode=FALSE;
            return 0L;
         }
         if(MpaOpenEncoder( pExMMInfo->lhMpa, pExMMInfo->szMpaFileName))   {
            pExMMInfo->fEncode=FALSE;
            return 0L;
         }
         MpaGetHeader(pExMMInfo->lhMpa, &pExMMInfo->mmEncodedAudioHdr);
         pExMMInfo->fAlreadyOpened=TRUE;
      }
      /* 指定ビット数／チャンネル／周波数に変換する */
      pExMMInfo->ldSrc.pStruct=&pExMMInfo->mmMMIOAudioHdr;
      pExMMInfo->ldSrc.pBuffer=(PCHAR)mp1;                
      pExMMInfo->ldSrc.ulSize=mp2;
      pExMMInfo->ldDest.pStruct=&pExMMInfo->mmEncodedAudioHdr;
      pExMMInfo->ldDest.pBuffer=(PCHAR)mp1;
      pExMMInfo->ldDest.ulSize=mp2;
      /* ビット数を変換(16BITS) */
      if(MpaQueryIdletimeDriveCheckstate(pExMMInfo->lhMpa)) DosSetPriority(PRTYS_THREAD,PRTYC_IDLETIME,0L,0L);
      if(pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.usBitsPerSample!=16)  {
         if(CnvWaveBitsTo16B(&pExMMInfo->ldDest, &pExMMInfo->ldSrc, NULL))    return 0L;
         if(!pExMMInfo->ldDest.pBuffer)   return 0L;
         pExMMInfo->ldSrc.pStruct=&pExMMInfo->mmEncodedAudioHdr;
         pExMMInfo->ldSrc.pBuffer=pExMMInfo->ldDest.pBuffer;
         pExMMInfo->ldSrc.ulSize=pExMMInfo->ldDest.ulSize;
      }
      /* サンプル周波数を変換(44100Hz,48kHz,38kHz) */
      if(pExMMInfo->mmMMIOAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec!=pExMMInfo->mmEncodedAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec) {
         switch(pExMMInfo->ulEncodeFlag & 0x0000000F) {
         case 0:
         case MPA_EFLAG_SPS_44KHZ:
            rc=CnvWaveFreqTo44K( &pExMMInfo->ldDest, &pExMMInfo->ldSrc, NULL);
            break;
         default:
         case MPA_EFLAG_SPS_48KHZ:
         case MPA_EFLAG_SPS_33KHZ:
            rc=CnvWaveFreq( &pExMMInfo->ldDest, &pExMMInfo->ldSrc, (PVOID)pExMMInfo->mmEncodedAudioHdr.mmXWAVHeader.WAVEHeader.ulSamplesPerSec);
            break;
         }
         if(rc)   {
            EscFreeMem(pExMMInfo->ldSrc.pBuffer);
            return 0L;
         }
         if(pExMMInfo->ldSrc.pBuffer!=mp1)
            EscFreeMem(pExMMInfo->ldSrc.pBuffer);
         if(!pExMMInfo->ldDest.pBuffer)   return 0L;
      }

      /* 書き込み開始 */
      lRC=MpaWrite( pExMMInfo->lhMpa, (PCHAR)pExMMInfo->ldDest.pBuffer, pExMMInfo->ldDest.ulSize);

      if(MpaQueryIdletimeDriveCheckstate(pExMMInfo->lhMpa)) DosSetPriority(PRTYS_THREAD,PRTYC_REGULAR,0L,0L);
      /* 一時使用メモリーを解放 */
      if(pExMMInfo->ldDest.pBuffer!=mp1)  {
         EscFreeMem(pExMMInfo->ldDest.pBuffer);
      }
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
   /* その他                                                            */
   /* ***************************************************************** */
   default: 
      if(pMMInfo)  {
         pExMMInfo=pMMInfo->pExtraInfoStruct;
         hmmio=pExMMInfo->hmmioSS;
      }  else  {
         hmmio=NULL;
      }
      return EscDefMMIOProc(pMMInfo, usMsg, mp1, mp2, hmmio);
   }  /* end of switch */
return lRC; }


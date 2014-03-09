#define INCL_ESC_NO_NETWORK
#define INCL_ESC_NO_WARP4
#include <LUCIER.H>

#include "dialog.h"

#define ESC_MMIO_SETUP_FLAGNAME     "MULTIMEDIA I/O SERVICE INSTALL SCRIPT PACKAGE"

HWND EXPENTRY _export INSERTMMSETUPPAGE(PMCI_DEVICESETTINGS_PARMS pMCIDevSettings);
MRESULT EXPENTRY _export MMSETUPPAGEDLGPROC (HWND hwnd, USHORT msg,MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY _export MMSETUPPAGEDLGPROC2(HWND hwnd, USHORT msg,MPARAM mp1, MPARAM mp2);

ULONG EscWriteProfileInt(HINI hini, PSZ pszApp, PSZ pszKey, INT   value)   {
ULONG rc;
CHAR  szValue[34];
   sprintf(szValue,"%ld",value);
   rc=PrfWriteProfileString(hini,pszApp,pszKey,szValue);
return rc; }

ULONG EscWriteProfileWindowText(HINI hini, PSZ pszApp, PSZ pszKey, HWND  hwnd, ULONG ulID)   {
ULONG rc;
PCHAR  pszBuffer;
   pszBuffer=malloc(2048);
   pszBuffer[0]=0;
   if(ulID) {
      WinQueryWindowText(WinWindowFromID(hwnd,ulID),2046,pszBuffer);
   }  else  {
      WinQueryWindowText(hwnd,2046,pszBuffer);
   }
   rc=PrfWriteProfileString(hini,pszApp,pszKey, pszBuffer);
   free(pszBuffer);
return rc; }

ULONG EscSetDlgItemTextFromProfile(HINI hini, PSZ pszApp, PSZ pszKey, HWND  hwnd, ULONG ulID, PCHAR pszDefault)   {
ULONG rc;
PCHAR  pszBuffer;
   pszBuffer=malloc(2048);
   pszBuffer[0]=0;
   rc=PrfQueryProfileString(hini,pszApp,pszKey, pszDefault, pszBuffer, 2046);
   if(ulID) {
      WinSetWindowText(WinWindowFromID(hwnd,ulID),pszBuffer);
   }  else  {
      WinSetWindowText(hwnd,pszBuffer);
   }
   free(pszBuffer);
return rc; }

ULONG EscWriteProfileButtonCheckstate(HINI hini, PSZ pszApp, PSZ pszKey, HWND  hwnd, ULONG ulID)   {
ULONG rc;
   rc=EscWriteProfileInt(hini,pszApp,pszKey, WinQueryButtonCheckstate(hwnd, ulID) );                                       
return rc; }

ULONG EscWriteProfileLboxSelectedItem(HINI hini, PSZ pszApp, PSZ pszKey, HWND  hwnd)   {
ULONG rc;
   rc=EscWriteProfileInt(hini,pszApp,pszKey, WinQueryLboxSelectedItem(hwnd) );
return rc; }

ULONG EscInsertLboxItems(HWND hwnd, ULONG index, PCHAR *papsz)   {
ULONG rc,i;
   for(i=0;papsz[i];i++)   {
      rc=WinInsertLboxItem(hwnd,index,papsz[i]);
   }
return rc; }



BOOL  fForeground;
HWND    hwndMenu;
HWND  hwndList;
PFNWP ListWndProc,SysWndProc;
BOOL   fJapanese;

HMODULE  hMod;
HWND  hwndPage,hwndPage2,hwndPage3,hwndNotebook;

HWND EXPENTRY _export INSERTMMSETUPPAGE(PMCI_DEVICESETTINGS_PARMS pMCIDevSettings)    {
CHAR  szTabText[CCHMAXPATH];  /* タブ・ストリング用バッファー */
ULONG ulPageId,ulPageId2;
UCHAR LoadError[256]="";
HAB   hab;

   if(DosLoadModule(LoadError,sizeof(LoadError),"MPAPAGE.DLL",&hMod))  {
      DosLoadModule(LoadError,sizeof(LoadError),"MPAPAGE",&hMod);
   }
   fJapanese=EscReadyForJapanese();
   hwndNotebook=pMCIDevSettings->hwndNotebook;

   hab=WinQueryAnchorBlock(HWND_DESKTOP);
   /* 最初のページを設定 */       
   if(fJapanese)  hwndPage=WinLoadSecondaryWindow(pMCIDevSettings->hwndNotebook,pMCIDevSettings->hwndNotebook, (PFNWP)MMSETUPPAGEDLGPROC,hMod,ID_DIALOG_JPN ,(PVOID)pMCIDevSettings);
   else    hwndPage = WinLoadSecondaryWindow(pMCIDevSettings->hwndNotebook,pMCIDevSettings->hwndNotebook, (PFNWP)MMSETUPPAGEDLGPROC,hMod,ID_DIALOG ,(PVOID)pMCIDevSettings);
   if (!hwndPage) {
      return NULL;
   }
   ulPageId = (ULONG)WinSendMsg( pMCIDevSettings->hwndNotebook, BKM_INSERTPAGE,(ULONG)NULL,MPFROM2SHORT( BKA_AUTOPAGESIZE|BKA_MAJOR|BKA_STATUSTEXTON, BKA_LAST ) );
   WinSendMsg(pMCIDevSettings->hwndNotebook, BKM_SETPAGEWINDOWHWND, MPFROMP( ulPageId ), MPFROMLONG( hwndPage ) );

   if(fJapanese)  {
      PrfQueryProfileString( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_TITLE, "MPEGオーディオ", szTabText, sizeof(szTabText));
      WinSendMsg(pMCIDevSettings->hwndNotebook, BKM_SETSTATUSLINETEXT, MPFROMLONG(ulPageId), MPFROMP(szTabText)); // "2ページ中の1ページ目"
   }  else  {
      PrfQueryProfileString( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_TITLE, "MPEG Audio", szTabText, sizeof(szTabText));
      WinSendMsg(pMCIDevSettings->hwndNotebook, BKM_SETSTATUSLINETEXT, MPFROMLONG(ulPageId), MPFROMP(szTabText)); // "1 of 2"
   }
   WinSendMsg( pMCIDevSettings->hwndNotebook, BKM_SETTABTEXT,MPFROMP( ulPageId ), szTabText );
   WinSetWindowText(hwndPage,szTabText);

   /* 製品情報のページを設定 */       
   if(fJapanese)  hwndPage2   = WinLoadSecondaryWindow(pMCIDevSettings->hwndNotebook,pMCIDevSettings->hwndNotebook,(PFNWP)MMSETUPPAGEDLGPROC2,hMod,ID_DIALOG2_JPN ,(PVOID)pMCIDevSettings);
   else    hwndPage2   = WinLoadSecondaryWindow(pMCIDevSettings->hwndNotebook,pMCIDevSettings->hwndNotebook,(PFNWP)MMSETUPPAGEDLGPROC2,hMod,ID_DIALOG2 ,(PVOID)pMCIDevSettings);
   if (hwndPage2) {
      ulPageId2 = (ULONG)WinSendMsg( pMCIDevSettings->hwndNotebook, BKM_INSERTPAGE,(ULONG)NULL,MPFROM2SHORT( BKA_AUTOPAGESIZE|BKA_MINOR|BKA_STATUSTEXTON, BKA_LAST ) );
      WinSendMsg(pMCIDevSettings->hwndNotebook, BKM_SETPAGEWINDOWHWND, MPFROMP( ulPageId2 ), MPFROMLONG( hwndPage2 ) );
      if(fJapanese)  {
         strcpy(szTabText,"製品情報");
         WinSendMsg(pMCIDevSettings->hwndNotebook, BKM_SETSTATUSLINETEXT, MPFROMLONG(ulPageId2), MPFROMP("2ページ中の2ページ目"));
      }  else  {
         strcpy(szTabText,"Product Information");
         WinSendMsg(pMCIDevSettings->hwndNotebook, BKM_SETSTATUSLINETEXT, MPFROMLONG(ulPageId2), MPFROMP("2 of 2"));
      }
      WinSendMsg( pMCIDevSettings->hwndNotebook, BKM_SETTABTEXT,MPFROMP( ulPageId2 ), szTabText );
      WinSetWindowText(hwndPage2,szTabText);
   }
return( hwndPage );  }
     
typedef struct {
  HWND hwndHelpInstance;
} MMPAGEINFO, * PMMPAGEINFO;
       

ULONG    LoadProfile(HWND hwnd)  {
ULONG id;
CHAR  szBuffer[8];

   if(fJapanese)  {
      EscSetDlgItemTextFromProfile(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_TITLE, hwnd, ID_TEXT_TABNAME, "MPEGオーディオ");
   }  else  {
      EscSetDlgItemTextFromProfile(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_TITLE, hwnd, ID_TEXT_TABNAME, "MPEG Audio");
   }

   /* DISKCACHE */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_DISKCACHE, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_DISKCACHE,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_DISKCACHE,1); break;
   }
   /* FRAMESKIP */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_FRAMESKIP, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_FRAMESKIP,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_FRAMESKIP,1); break;
   }
   /* PHYMODEL */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_PHYMODEL, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_MODEL1,0); WinCheckButton(hwnd,ID_CHK_MODEL2,1); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_MODEL1,1); WinCheckButton(hwnd,ID_CHK_MODEL2,0); break;
   case 2:   WinCheckButton(hwnd,ID_CHK_MODEL1,0); WinCheckButton(hwnd,ID_CHK_MODEL2,1); break;
   }
   /* LCHANNELONLY */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_LCHANNELONLY, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_LCHONLY,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_LCHONLY,1); break;
   }
   /* NOCHECK */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_NOCHECK, 0)) {                     
   default:  WinCheckButton(hwnd,ID_CHK_NOCHECK,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_NOCHECK,1); break;
   }
   /* EMPHASIS */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_EMPHASIS, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_EMPHASIS,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_EMPHASIS,1); break;
   case 3:   WinCheckButton(hwnd,ID_CHK_EMPHASIS,1); break;
   }
   /* EXTENSION */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_EXTENSION, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_EXTENSION,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_EXTENSION,1); break;
   }
   /* ERRORPROTECTION */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_ERRORPROTECTION, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_ERRORPROTECT,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_ERRORPROTECT,1); break;
   }
   /* COPYRIGHT */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_COPYRIGHTED, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_COPYRIGHTED,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_COPYRIGHTED,1); break;
   }
   /* ORIGINAL */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_ORIGINAL, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_ORIGINAL,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_ORIGINAL,1); break;
   }
   /* MONORAL */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_MONORAL, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_MONORAL,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_MONORAL,1); break;
   }
   /* ANTIALIAS */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_ANTIALIAS, 1)) {
   default:  WinCheckButton(hwnd,ID_CHK_ANTIALIAS,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_ANTIALIAS,1); break;
   }
   /* ASCII */
   switch(PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_ASCII, 0)) {
   default:  WinCheckButton(hwnd,ID_CHK_ASCII,0); break;
   case 1:   WinCheckButton(hwnd,ID_CHK_ASCII,1); break;
   }
   /* DISKCACHE */
   id=PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_DISKCACHEMODE, 0);
   WinSendMsg(WinWindowFromID(hwnd, ID_LB_DISKCACHE), LM_SELECTITEM, MPFROMSHORT(id), MPFROMSHORT(TRUE));
   /* PRIORITY */
   id=PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMMON_PRIORITY, 0);
   WinSendMsg(WinWindowFromID(hwnd, ID_LB_PRIORITY), LM_SELECTITEM, MPFROMSHORT(id), MPFROMSHORT(TRUE));
   /* COMP PRIORITY */
   id=PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_STANDARDLEVEL, 0);
   WinSendMsg(WinWindowFromID(hwnd, ID_LB_COMPPRIORITY), LM_SELECTITEM, MPFROMSHORT(id), MPFROMSHORT(TRUE));
   /* QUICKDECOMPRESS */
   id=PrfQueryProfileInt( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_QUICKDECOMPRESS, 0);
   WinSendMsg(WinWindowFromID(hwnd, ID_LB_QUICK), LM_SELECTITEM, MPFROMSHORT(id), MPFROMSHORT(TRUE));
   /* EFFECT */
   szBuffer[0]=0;
   PrfQueryProfileString(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_EFFECT, "", szBuffer, 7);
   if(EscStrEq(szBuffer,"WVOL")) id=1;
   else if(EscStrEq(szBuffer,"WCHD")) id=2;
   else if(EscStrEq(szBuffer,"WCCH")) id=3;
   else if(EscStrEq(szBuffer,"WAVR")) id=4;
   else if(EscStrEq(szBuffer,"WMBL")) id=5;
   else if(EscStrEq(szBuffer,"WHAL")) id=6;
   else if(EscStrEq(szBuffer,"WFBK")) id=7;
   else if(EscStrEq(szBuffer,"WNIZ")) id=8;
   else if(EscStrEq(szBuffer,"WRVB")) id=9;
   else if(EscStrEq(szBuffer,"WDLY")) id=10;
   else if(EscStrEq(szBuffer,"WECH")) id=11;
   else id=0;
   WinSendMsg(WinWindowFromID(hwnd, ID_LB_EFFECT), LM_SELECTITEM, MPFROMSHORT(id), MPFROMSHORT(TRUE));

return NO_ERROR; }

ULONG    SaveProfile(HWND hwnd)  {
CHAR  szBuffer[8];
   EscWriteProfileWindowText( hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_TITLE, hwnd, ID_TEXT_TABNAME);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_PHYMODEL, hwnd, ID_CHK_MODEL1);
   if(WinQueryButtonCheckstate(hwnd, ID_CHK_MODEL2)) EscWriteProfileInt(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_PHYMODEL, WinQueryButtonCheckstate(hwnd, ID_CHK_MODEL2)*2 );
   EscWriteProfileLboxSelectedItem(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_QUICKDECOMPRESS, WinWindowFromID(hwnd, ID_LB_QUICK));
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_ANTIALIAS, hwnd, ID_CHK_ANTIALIAS);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_DISKCACHE, hwnd, ID_CHK_DISKCACHE);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_FRAMESKIP, hwnd, ID_CHK_FRAMESKIP);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_LCHANNELONLY, hwnd, ID_CHK_LCHONLY);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_NOCHECK, hwnd, ID_CHK_NOCHECK);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_EMPHASIS, hwnd, ID_CHK_EMPHASIS);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_EXTENSION, hwnd, ID_CHK_EXTENSION);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_ERRORPROTECTION, hwnd, ID_CHK_ERRORPROTECT);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_COPYRIGHTED, hwnd, ID_CHK_COPYRIGHTED);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_ORIGINAL, hwnd, ID_CHK_ORIGINAL);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_MONORAL, hwnd, ID_CHK_MONORAL);
   EscWriteProfileButtonCheckstate(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_ASCII, hwnd, ID_CHK_ASCII);
   EscWriteProfileLboxSelectedItem(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMMON_PRIORITY, WinWindowFromID(hwnd, ID_LB_PRIORITY));
   EscWriteProfileLboxSelectedItem(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_COMP_STANDARDLEVEL, WinWindowFromID(hwnd, ID_LB_COMPPRIORITY));
   EscWriteProfileLboxSelectedItem(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_DISKCACHEMODE, WinWindowFromID(hwnd, ID_LB_DISKCACHE));

   switch(WinQueryLboxSelectedItem(WinWindowFromID(hwnd, ID_LB_EFFECT))) {
   default:
      strcpy(szBuffer,"");
      break;
   case 1:
      strcpy(szBuffer,"WVOL");
      break;
   case 2:
      strcpy(szBuffer,"WCHD");
      break;
   case 3:
      strcpy(szBuffer,"WCCH");
      break;
   case 4:
      strcpy(szBuffer,"WAVR");
      break;
   case 5:
      strcpy(szBuffer,"WMBL");
      break;
   case 6:
      strcpy(szBuffer,"WHAL");
      break;
   case 7:
      strcpy(szBuffer,"WFBK");
      break;
   case 8:
      strcpy(szBuffer,"WNIZ");
      break;
   case 9:
      strcpy(szBuffer,"WRVB");
      break;
   case 10:
      strcpy(szBuffer,"WDLY");
      break;
   case 11:
      strcpy(szBuffer,"WECH");
      break;
   }
   PrfWriteProfileString(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_EFFECT, szBuffer);
// EscWriteProfileLboxSelectedItem(hiniMpaProfile, MPA_PRF_APPLNAME, MPA_PRF_DECOMP_EFFECT, WinWindowFromID(hwnd, ID_LB_EFFECT));
return NO_ERROR; }


MRESULT EXPENTRY _export MMSETUPPAGEDLGPROC (HWND hwnd, USHORT msg,MPARAM mp1, MPARAM mp2)  {
PMMPAGEINFO       pMMPageInfo;                                                                
static HAB        hab;
static   HWND     hwndStatus;
static   BOOL     fChange=FALSE;
PCHAR papszPriority[2][3]={{"DEFAULT","IDLETIME",NULL},{"標準状態のまま","アイドルタイム [推奨]",NULL}};
PCHAR papszCompPriority[2][5]={{"DEFAULT","HQ","QUICK DE-COMP","TELEPHONE LINE",NULL},{"標準状態のまま","音質最優先","圧縮解除処理速度優先","電話回線速度",NULL}};
PCHAR papszEffect[2][13]={{"NO Effect & NO Filter","Volume","Channel Delay","Channel Change","Average","Marble Hall","Hall","Feedback","Noize","Reverb","Delay","Echo",NULL},{"フィルターなし[推奨]","電子ボリューム","チャンネル遅延","左右チャンネル交換","隣接平滑効果","大理石ホール効果","ホール効果","フィードバック効果","雑音効果","リバーブ","ディレイ","エコー",NULL}};
PCHAR papszQuick[2][6]={{"DEFAULT","Quick De-compress (*2)","Fast De-compress (*4)","Draft De-compress (*8)","Super-draft De-compress (*16)",NULL},{"標準圧縮解除","高速圧縮解除 [推奨]","全速圧縮解除","ドラフト圧縮解除","超ドラフト圧縮解除",NULL}};
PCHAR papszHelpTitle[2]={"HELP FOR MMMPA","ＭＭＭＰＡ取扱説明書"};
PCHAR papszDiskCache[2][9]={{"RIFF WAVE Audio - CDDA","RIFF WAVE Audio - MUSIC (1/2)","WDF Compression 1st (1/4) [推奨]","WDF Compression 2nd (1/7)","MPEG Audio Layer-2 - 384kbps","MPEG Audio Layer-2 - 128kbps","MPEG Audio Layer-2 - 64kbps",NULL},{"RIFF WAVEｵｰﾃﾞｨｵ 最高品質","RIFF WAVEｵｰﾃﾞｨｵ 音楽品質","WDFファースト圧縮 (1/4)","WDFセカンド圧縮 (1/7)","MPEGｵｰﾃﾞｨｵ ﾚｲﾔｰ2 - 384kbps","MPEGｵｰﾃﾞｨｵ ﾚｲﾔｰ2 - 128kbps","MPEGｵｰﾃﾞｨｵ ﾚｲﾔｰ2 - 64kbps",NULL}};

ULONG    i;
CHAR     szBuffer[40];

   pMMPageInfo = (PMMPAGEINFO) WinQueryWindowPtr(hwnd, QWL_USER);      

   switch(msg) {
   case WM_INITDLG:
      fForeground=FALSE;
      fChange=TRUE;
      hab=WinQueryAnchorBlock(HWND_DESKTOP);
      /* ページの初期化 */
      pMMPageInfo = (PMMPAGEINFO) malloc(sizeof(MMPAGEINFO));
      WinSetWindowPtr (hwnd, QWL_USER, pMMPageInfo);
      pMMPageInfo->hwndHelpInstance = EscInitializeHelp(hwnd,"MMMPA.INF",papszHelpTitle[fJapanese]);

      WinSendMsg(WinWindowFromID(hwnd, ID_LB_PRIORITY), LM_DELETEALL, NULL, NULL);
      EscInsertLboxItems(WinWindowFromID(hwnd,ID_LB_PRIORITY), LIT_END, &papszPriority[fJapanese][0]);
      WinSendMsg(WinWindowFromID(hwnd, ID_LB_PRIORITY), LM_SELECTITEM, MPFROMSHORT(0), MPFROMSHORT(TRUE));
      WinSendMsg(WinWindowFromID(hwnd, ID_LB_COMPPRIORITY), LM_DELETEALL, NULL, NULL);
      EscInsertLboxItems(WinWindowFromID(hwnd,ID_LB_COMPPRIORITY), LIT_END, &papszCompPriority[fJapanese][0]);
      WinSendMsg(WinWindowFromID(hwnd, ID_LB_COMPPRIORITY), LM_SELECTITEM, MPFROMSHORT(0), MPFROMSHORT(TRUE));

      WinSendMsg(WinWindowFromID(hwnd, ID_LB_QUICK), LM_DELETEALL, NULL, NULL);
      EscInsertLboxItems(WinWindowFromID(hwnd,ID_LB_QUICK), LIT_END, &papszQuick[fJapanese][0]);
      WinSendMsg(WinWindowFromID(hwnd, ID_LB_QUICK), LM_SELECTITEM, MPFROMSHORT(0), MPFROMSHORT(TRUE));

      WinSendMsg(WinWindowFromID(hwnd, ID_LB_DISKCACHE), LM_DELETEALL, NULL, NULL);
      EscInsertLboxItems(WinWindowFromID(hwnd,ID_LB_DISKCACHE), LIT_END, &papszDiskCache[fJapanese][0]);
      WinSendMsg(WinWindowFromID(hwnd, ID_LB_DISKCACHE), LM_SELECTITEM, MPFROMSHORT(0), MPFROMSHORT(TRUE));

      WinSendMsg(WinWindowFromID(hwnd, ID_LB_EFFECT), LM_DELETEALL, NULL, NULL);
      EscInsertLboxItems(WinWindowFromID(hwnd,ID_LB_EFFECT), LIT_END, &papszEffect[fJapanese][0]);
      WinSendMsg(WinWindowFromID(hwnd, ID_LB_EFFECT), LM_SELECTITEM, MPFROMSHORT(0), MPFROMSHORT(TRUE));

      LoadProfile(hwnd);
      WinStartTimer(hab, hwnd, 0L, 1000L);
      break;
   case WM_TIMER:
      i=EscQueryBusyLevel();
      if(i>1000)  {
         WinSetDlgItemText( hwnd, ID_SS_CPUBUSY , "Unknown");
      }  else  {
         sprintf(szBuffer,"%ld.%ld",i/10,i%10);
         WinSetDlgItemText( hwnd, ID_SS_CPUBUSY , szBuffer);
      }
      break;
   case WM_DESTROY:
      WinStopTimer(hab, hwnd, 0L);
      SaveProfile( hwnd);
      if(pMMPageInfo)   {
         WinDestroyHelpInstance (pMMPageInfo->hwndHelpInstance);
         free (pMMPageInfo);
      }
      break;
   case WM_COMMAND:
      /* すべてのコマンドの処理 */
      switch(SHORT1FROMMP(mp1))  {
      case ID_BUTTON_HELP:
         WinPostMsg(hwnd,WM_HELP,0,0);
         break;
      case ID_BUTTON_SAVE:
         SaveProfile( hwnd);
         break;
      case ID_BUTTON_DEFAULT:
         WinCheckButton(hwnd,ID_CHK_MODEL1,0);
         WinCheckButton(hwnd,ID_CHK_MODEL2,1);
         WinCheckButton(hwnd,ID_CHK_LCHONLY,0);
         WinCheckButton(hwnd,ID_CHK_NOCHECK,0);
         WinCheckButton(hwnd,ID_CHK_EMPHASIS,0);
         WinCheckButton(hwnd,ID_CHK_EXTENSION,0);
         WinCheckButton(hwnd,ID_CHK_ERRORPROTECT,0);
         WinCheckButton(hwnd,ID_CHK_COPYRIGHTED,0);
         WinCheckButton(hwnd,ID_CHK_ORIGINAL,0);
         WinCheckButton(hwnd,ID_CHK_MONORAL,0);
         WinCheckButton(hwnd,ID_CHK_ANTIALIAS,1);
         break;
      case ID_BUTTON_UNDO:
         LoadProfile( hwnd);
         break;
      default:
         break;
      }
      return ((MRESULT) FALSE);
   case MM_TABHELP:
      /* タブのヘルプの表示 */
      if (pMMPageInfo->hwndHelpInstance) {
//       EscViewHelp(pMMPageInfo->hwndHelpInstance,MPFROMSHORT(WinQueryWindowUShort(hwnd, QWS_ID)));
      }
      break;
   case WM_HELP:
      if (pMMPageInfo->hwndHelpInstance) {
         if(fJapanese) EscViewHelpContents(pMMPageInfo->hwndHelpInstance,HM_HELP_CONTENTS);
         else EscViewHelpContents(pMMPageInfo->hwndHelpInstance,HM_HELP_CONTENTS);
      }
      return ((MRESULT)TRUE);
   case WM_TRANSLATEACCEL:
      return (WinDefWindowProc (hwnd, msg, mp1, mp2));
      break;
   }
return WinDefSecondaryWindowProc(hwnd,msg,mp1,mp2);   }   

MRESULT EXPENTRY _export MMSETUPPAGEDLGPROC2(HWND hwnd, USHORT msg,MPARAM mp1, MPARAM mp2)  {
PMMPAGEINFO pMMPageInfo;
   pMMPageInfo = (PMMPAGEINFO) WinQueryWindowPtr(hwnd, QWL_USER);
   switch(msg) {
   case WM_INITDLG:
      break;
   case WM_CLOSE:
      return ((MRESULT) FALSE);
   }
return (WinDefSecondaryWindowProc(hwnd, msg, mp1, mp2)); }



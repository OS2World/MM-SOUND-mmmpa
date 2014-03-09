/* ******************************************************************** */
/* MPEG AUDIO MMIO PROC - MAIN SOURCE CODE                              */
/* ENCODE: LAYER-2                                                      */
/*                                                                      */
/*                                                        Version 1.0.0 */
/*                                Copyrights(c) 1999-2000, Yuuriru Mint */
/*                         TEAM MMOS/2 TOKYO Multimedia Communications! */
/* ******************************************************************** */
/* Watcom C/C++ 10.0 �p��� + Warp 4 Toolkit                            */
/* Library: MMPM2.LIB LUCIER.LIB (2.3) LLCDIOCT.LIB                     */
/* ******************************************************************** */
#define INCL_ESC_NO_NETWORK
#define INCL_ESC_NO_WARP4
#include <LUCIER.H>

#include "MMIOPROC.H"

#define  FOURCC_MMIOPROC_DEF        FOURCC_MMIOPROC_MPA2
#define  NAME_DEF                   NAME_MPA2
#define  NAMEJ_DEF                  NAMEJ_MPA2
#define  EXT_DEF                    EXT_MPA2
#define  SUPPORTFLAG_DEF            SUPPORTFLAG_MPA2

/* ******************************************************************** */
/* ���C���֐�                                                           */
/* ******************************************************************** */
LONG EXPENTRY _export MMIOENTRY_MPA2(PVOID pVoid,USHORT usMsg,LONG mp1,LONG mp2)  {
LONG              lRC=MMIO_ERROR;
MMIOINFO          *pMMInfo=NULL;
MPAOPTIONS        MpaOpt;

   pMMInfo=(PMMIOINFO)pVoid;

   switch(usMsg)  {
   /* ***************************************************************** */
   /* �I�[�v��                                                          */
   /* ***************************************************************** */
   case MMIOM_OPEN:
      if(!pMMInfo)   break;
      MpaOpt.ulStructLen=sizeof(MPAOPTIONS);
      MpaOpt.ulFlags=MPA_EFLAG_LAY_2;
      pMMInfo->pExtraInfoStruct=(PVOID)&MpaOpt;
      lRC=MMIOENTRY(pVoid, usMsg, mp1, mp2);
      break;
   /* ***************************************************************** */
   /* ���̃T�[�r�X�̃t�H�[�}�b�g����Ԃ�                              */
   /* ���̃T�[�r�X�̃t�H�[�}�b�g����Ԃ�                                */
   /* ***************************************************************** */
   case MMIOM_GETFORMATINFO:
      return EscDefMMIOGetFormatInfo((PMMFORMATINFO)mp1, FOURCC_MMIOPROC_DEF, MMIO_IOPROC_FILEFORMAT, MEDIATYPE, SUPPORTFLAG_DEF, NAME_DEF, NAMEJ_DEF, EXT_DEF);
   case MMIOM_GETFORMATNAME:
      return EscDefMMIOGetFormatName((PCHAR)mp1,mp2,NAME_DEF,NAMEJ_DEF,EXT_DEF);
   /* ***************************************************************** */
   /* �t�@�C���̎����F�����s���`�F�b�N���[�`�� (���C�g�݂̂Ȃ̂Ŕ�T�|) */
   /* ***************************************************************** */
   case MMIOM_IDENTIFYFILE:
      lRC=MMIO_ERROR;
      break;
   /* ***************************************************************** */
   /* ��ʏ���                                                          */
   /* ***************************************************************** */
   default:
      lRC=MMIOENTRY(pVoid, usMsg, mp1, mp2);
      break;
   }
return lRC; }

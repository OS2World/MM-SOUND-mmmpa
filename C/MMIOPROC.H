
/* ******************************************************************** */
/* MMIO SERVICE - MULTIMEDIA SUB SYSTEM DEVELOPERS INCLUDE HEADER       */
/* TEAM MMOS/2 TOKYO Multimedia Communications!                         */
/* ******************************************************************** */

/* ******************************************************************** */
/* DEFINED LAYER-1/2/3 READ                                             */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC   mmioFOURCC('M','P','A',' ')
#define  MEDIATYPE         MMIO_MEDIATYPE_AUDIO
#define  TEXT_MMIOPROC     "MPEG Audio-1 Layer 1/2/3 MMIO Ver 1.0.0"
#define  NAME              "MPEG Audio-1 Layer 1/2/3"
#define  NAMEJ             "MPEGオーディオ１"
#define  EXT               "MPA"
#define  APPNAME           "MPAPROC"

#define  SUPPORTFLAG       MMIO_CANREADTRANSLATED | MMIO_CANREADWRITETRANSLATED \
                         | MMIO_CANREADUNTRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                         | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED RIFF WAVE MPEG AUDIO READ                                    */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MPWR mmioFOURCC('M','P','W','R')
#define  NAME_MPWR            "MPEG Audio-1 Layer 1/2/3"
#define  NAMEJ_MPWR           "MPEGオーディオ１ レイヤー 1/2/3"
#define  EXT_MPWR             "WAV"

#define  SUPPORTFLAG_MPWR       MMIO_CANREADTRANSLATED | MMIO_CANREADWRITETRANSLATED \
                              | MMIO_CANREADUNTRANSLATED | MMIO_CANREADWRITEUNTRANSLATED

/* ******************************************************************** */
/* DEFINED RIFF WAVE MPEG AUDIO LAYER-3 WRITE                           */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MPW3 mmioFOURCC('M','P','W','3')
#define  NAME_MPW3            "MPEG Audio-1 Layer 3"
#define  NAMEJ_MPW3           "MPEGオーディオ１ レイヤー3"
#define  EXT_MPW3             "WAV"

#define  SUPPORTFLAG_MPW3       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED RIFF WAVE MPEG AUDIO LAYER-2 WRITE                           */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MPW2 mmioFOURCC('M','P','W','2')
#define  NAME_MPW2            "MPEG Audio-1 Layer 2"
#define  NAMEJ_MPW2           "MPEGオーディオ１ レイヤー2"
#define  EXT_MPW2             "WAV"

#define  SUPPORTFLAG_MPW2       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED RIFF WAVE MPEG AUDIO LAYER-1 WRITE                           */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MPW1 mmioFOURCC('M','P','W','1')
#define  NAME_MPW1            "MPEG Audio-1 Layer 1"
#define  NAMEJ_MPW1           "MPEGオーディオ１ レイヤー1"
#define  EXT_MPW1             "WAV"

#define  SUPPORTFLAG_MPW1       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-3 WRITE                                                */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MPA3 mmioFOURCC('M','P','A','3')
#define  NAME_MPA3            "MPEG Audio-1 Layer 3"
#define  NAMEJ_MPA3           "MPEGオーディオ１ レイヤー3"
#define  EXT_MPA3             "MP3"

#define  SUPPORTFLAG_MPA3       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-2 WRITE                                                */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MPA2 mmioFOURCC('M','P','A','2')
#define  NAME_MPA2            "MPEG Audio-1 Layer 2"
#define  NAMEJ_MPA2           "MPEGオーディオ１ レイヤー2"
#define  EXT_MPA2             "MP2"

#define  SUPPORTFLAG_MPA2       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-2 WRITE (TELEPHONE LINE SPEED)                         */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MP2S mmioFOURCC('M','P','2','S')
#define  NAME_MP2S            "MPEG Audio-1 Layer 2 384kbps"
#define  NAMEJ_MP2S           "MPEGオーディオ１ レイヤー2 高品質(384kbps)"
#define  EXT_MP2S             "MP2"

#define  SUPPORTFLAG_MP2S       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-2 WRITE (TELEPHONE LINE SPEED)                         */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MP2C mmioFOURCC('M','P','2','C')
#define  NAME_MP2C            "MPEG Audio-1 Layer 2 128kbps"
#define  NAMEJ_MP2C           "MPEGオーディオ１ レイヤー2 標準圧縮(128kbps)"
#define  EXT_MP2C             "MP2"

#define  SUPPORTFLAG_MP2C       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-2 WRITE (TELEPHONE LINE SPEED)                         */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MP2T mmioFOURCC('M','P','2','T')
#define  NAME_MP2T            "MPEG Audio-1 Layer 2 32kbps"
#define  NAMEJ_MP2T           "MPEGオーディオ１ レイヤー2 電話回線通過(32kbps)"
#define  EXT_MP2T             "MP2"

#define  SUPPORTFLAG_MP2T       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-2 WRITE (44kHz SPS)                                    */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MP2U mmioFOURCC('M','P','2','U')
#define  NAME_MP2U            "MPEG Audio-1 Layer 2 33kHz"
#define  NAMEJ_MP2U           "MPEGオーディオ１ レイヤー2 特殊周波数(33kHz)"
#define  EXT_MP2U             "MP2"

#define  SUPPORTFLAG_MP2U       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-2 WRITE (33kHz SPS)                                    */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MP2V mmioFOURCC('M','P','2','V')
#define  NAME_MP2V            "MPEG Audio-1 Layer 2 44kHz"
#define  NAMEJ_MP2V           "MPEGオーディオ１ レイヤー2 標準周波数(44kHz)"
#define  EXT_MP2V             "MP2"

#define  SUPPORTFLAG_MP2V       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-2 WRITE (48kHz SPS)                                    */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MP2W mmioFOURCC('M','P','2','W')
#define  NAME_MP2W            "MPEG Audio-1 Layer 2 48kHz"
#define  NAMEJ_MP2W           "MPEGオーディオ１ レイヤー2 特殊周波数(48kHz)"
#define  EXT_MP2W             "MP2"

#define  SUPPORTFLAG_MP2W       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-1 WRITE                                                */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MPA1 mmioFOURCC('M','P','A','1')
#define  NAME_MPA1            "MPEG Audio-1 Layer 1"
#define  NAMEJ_MPA1           "MPEGオーディオ１ レイヤー1"
#define  EXT_MPA1             "MPA"

#define  SUPPORTFLAG_MPA1       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-1 WRITE (33kHz SPS)                                    */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MP1U mmioFOURCC('M','P','1','U')
#define  NAME_MP1U            "MPEG Audio-1 Layer 1 33kHz"
#define  NAMEJ_MP1U           "MPEGオーディオ１ レイヤー1 特殊周波数(33kHz)"
#define  EXT_MP1U             "MP2"

#define  SUPPORTFLAG_MP1U       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-1 WRITE (44kHz SPS)                                    */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MP1V mmioFOURCC('M','P','1','V')
#define  NAME_MP1V            "MPEG Audio-1 Layer 1 44kHz"
#define  NAMEJ_MP1V           "MPEGオーディオ１ レイヤー1 標準周波数(44kHz)"
#define  EXT_MP1V             "MP2"

#define  SUPPORTFLAG_MP1V       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-1 WRITE (48kHz SPS)                                    */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MP1W mmioFOURCC('M','P','1','W')
#define  NAME_MP1W            "MPEG Audio-1 Layer 1 48kHz"
#define  NAMEJ_MP1W           "MPEGオーディオ１ レイヤー1 特殊周波数(48kHz)"
#define  EXT_MP1W             "MP2"

#define  SUPPORTFLAG_MP1W       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-1 WRITE                                                */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MPAL mmioFOURCC('M','P','A','L')
#define  NAME_MPAL            "MPEG Audio-1 MPAL Compression"
#define  NAMEJ_MPAL           "MPEGオーディオ１ エムパル"
#define  EXT_MPAL             "MPL"

#define  SUPPORTFLAG_MPAL       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-1 WRITE                                                */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MPLS mmioFOURCC('M','P','L','S')
#define  NAME_MPLS            "MPEG Audio-1 MPAL Compression (192kbps)"
#define  NAMEJ_MPLS           "MPEGオーディオ１ エムパル 高品質(192kbps)"
#define  EXT_MPLS             "MPL"

#define  SUPPORTFLAG_MPLS       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* DEFINED LAYER-1 WRITE                                                */
/* ******************************************************************** */
#define  FOURCC_MMIOPROC_MPLT mmioFOURCC('M','P','L','T')
#define  NAME_MPLT            "MPEG Audio-1 MPAL Compression (16kbps)"
#define  NAMEJ_MPLT           "MPEGオーディオ１ エムパル 電話回線通過(16kbps)"
#define  EXT_MPLT             "MPL"

#define  SUPPORTFLAG_MPLT       MMIO_CANREADWRITETRANSLATED | MMIO_CANREADWRITEUNTRANSLATED \
                              | MMIO_CANWRITEUNTRANSLATED | MMIO_CANWRITETRANSLATED

/* ******************************************************************** */
/* extendmmioinfo structure                                             */
/* ******************************************************************** */
typedef struct _EXTENDMMIOINFO {
   HMMIO          hmmioSS;
   LHANDLE        lhMpa;
   HMODULE        hmod;

   CHAR           szMpaFileName[CCHMAXPATH];

   ULONG          ulEncodeFlag;   

   MMAUDIOHEADER  mmDecodedAudioHdr;
   MMAUDIOHEADER  mmEncodedAudioHdr;

   MMAUDIOHEADER  mmMMIOAudioHdr;

   BOOL           fDecode,fEncode,fAlreadyOpened;
   LLDATA         ldSrc,ldDest;
}  EXTENDMMIOINFO,   *PEXTENDMMIOINFO;


#define ESC_DATATYPE_MPA   0x2FB

/* ******************************************************************** */
/* FUNCTION DEFINE                                                      */
/* ******************************************************************** */
LONG EXPENTRY _export MMIOENTRY(PVOID pVoid,USHORT usMsg,LONG mp1,LONG mp2);

/* ******************************************************************** */
/* USER SETUP STRUCTURE                                                 */
/* ******************************************************************** */
typedef struct _MPAOPTIONS {
   ULONG          ulStructLen;               /* sizeof(MPAOPTIONS) */
   ULONG          ulFlags;                   /* MPA_EFLAG_???? */
}  MPAOPTIONS,   *PMPAOPTIONS;




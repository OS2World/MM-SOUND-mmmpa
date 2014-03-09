@ECHO OFF
CLS
REM PRINT OUT THE NOTE
ECHO  ______________________________________________________________________________
ECHO  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ECHO  MMMPA - TM2LABO MPEG AUDIO - Netscape Communicator / Navigator Plug-in
ECHO  ______________________________________________________________________________
ECHO  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ECHO  ____________________________________
ECHO  Language           Japanese, English
ECHO  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ECHO  ____
ECHO  NOTE   MPEG Audio support service. You can play the MPEG Audio file on the
ECHO  ~~~~   Netscape Communicator or Navigator for OS/2.
ECHO         This service is freeware but please send the impression to us.
ECHO  ____   
ECHO  SPEC   Decode - MPEG Audio Layer 1,2,3
ECHO  ~~~~   File type support - BINARY,ASCII
ECHO                           _____________________________________________________
ECHO                           TEAM MMOS/2 TOKYO Multimedia Communications!
ECHO                                                http://www7.big.or.jp/~os2warp/ 
ECHO                                                       mailto:os2warp@big.or.jp 
ECHO                           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
REM END OF THE NOTE
PAUSE
CD RES
INSTPLUG.EXE
CD ..
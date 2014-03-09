@ECHO OFF
CLS
if EXIST "LSWKEYIN.EXE" LSWKEYIN.EXE /ABOUT /TIMER:10000
REM PRINT OUT THE NOTE
ECHO  ______________________________________________________________________________
ECHO  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ECHO  MMMPA - TM2LABO MPEG AUDIO Multimedia I/O Extender
ECHO  ______________________________________________________________________________
ECHO  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ECHO  ____________________________________
ECHO  Language                     English
ECHO  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ECHO  ____
ECHO  NOTE   MPEG Audio support service. You can play and convert the audio file 
ECHO  ~~~~   directly. Possible: CD-DA to MPA (With 'MMCDDA' service).
ECHO         This service is freeware but please send the impression to us.
ECHO  ____   
ECHO  SPEC   Decode - MPEG Audio Layer 1,2,3
ECHO  ~~~~   Encode - MPEG Audio Layer 1,2
ECHO         File type support - BINARY,ASCII
ECHO  _____  
ECHO  LOOK!  After install, start the 'Multimedia-Setup' and RELAY some EXT (.MPA 
ECHO  ~~~~~  .MP2 and .MP3) to the Digital-Audio.
ECHO                           _____________________________________________________
ECHO                           TEAM MMOS/2 TOKYO Multimedia Communications!
ECHO                                                http://www7.big.or.jp/~os2warp/ 
ECHO                                                       mailto:os2warp@big.or.jp 
ECHO                           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
REM END OF THE NOTE
PAUSE
CD ENG
MINSTALL.EXE
CD ..
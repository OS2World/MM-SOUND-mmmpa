#define INNC_ESC_NO_NETWORK
#define INNC_ESC_NO_WARP4
#define INNC_ESC_NO_PM
#define INNC_ESC_NO_MM
#include <LUCIER.H>

VOID main()   {
CHAR szBuffer[CCHMAXPATH];
ULONG rc;
HINI  hini;
HAB   hab;
   hab=WinQueryAnchorBlock(HWND_DESKTOP);

   puts("Are you ready for uninstall \"MPEG Audio Multimedia Setup Program\" ?");
   puts("Type \"YES\" =");
   gets(szBuffer);
   if(EscStrEq(szBuffer,"YES")) {
      rc=EscQuerySystemDirectory(ESC_QUERY_SYSTEMDIR_MMOS2,szBuffer,sizeof(szBuffer));
      strcat(szBuffer,"MMPM.INI");
      if(rc)   {
         puts("Uninstall Error (Directory error) !");
         exit(3);
      }
      hini=PrfOpenProfile(hab,szBuffer);
      rc=PrfWriteProfileData(hini,"STPM_SettingsPage:7","MPAPAGE",NULL,0);
      PrfCloseProfile(hini);
      if(!rc)   {
         puts("Uninstall Error (Profile Error) !");
         exit(2);
      }
      puts("Uninstall O.K.");
   }  else  {
      puts("Uninstall canceled.");
      exit(1);
   }
exit(0); }


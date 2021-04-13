void red ();
void purple();
void blue();
void yellow();
void green();
void reset ();
void highlight(char *word, char *line,int iflag);
void bprint(int k);
void Hfile(char *filename);   // highlight file




// TO Execute Asci color on windows execute following in cmd
// reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f
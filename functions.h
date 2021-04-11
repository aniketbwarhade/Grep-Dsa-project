char *capitalTosmall(char *str);
int readLine(int fd, char *line);
int dotpresent(char *str);
int dashpresent(char *str);
int search(char *word,char *line,int iflag,int wflag);
void highlight(char *word, char *line);
char* kmpstrstr(char* txt, char* pat);
// char* kmpstrstr(char* X, char* Y);
char *kmpstrcasestr(char *str, char *pattern);


// MINGW32-make  to run makefile inside mingw
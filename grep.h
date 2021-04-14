// options flag

void addFilesRecursively(char *basePath, list *l);
void roflag(char *word, char *line,int iflag);
int switch_Hflag(char *word,char *argv,list *l,int iflag,int wflag);
int switch_hflag(char *word,char *argv,list *l,int iflag,int wflag,int Hflag,int cflag,int oflag);
int switch_lflag(char *word,char *argv,list *l);
int switch_oflag(char *word,char *argv,list *l,int Hflag,int j);
int switch_nflag(char *word,char *argv,list *l,int Hflag,int j,int iflag);
int switch_cflag(char *word,char *argv,list *l,int Hflag,int j);
int switch_wflag(char *word,char *argv,list *l,int Hflag,int j,int iflag,int wflag,int cflag,int oflag);
int switch_vflag(char *word,char *argv,list *l,int Hflag,int j,int iflag,int wflag,int cflag);
int switch_mflag(char *word,char *argv,list *l,int Hflag,int j,int oflag,int iflag,int wflag,int cflag,int vflag,int bflag,int mval);
int switch_bflag(char *word,char *argv,list *l,int Hflag,int j,int oflag,int iflag,int wflag,int cflag);
int switch_iflag(char *word,char *argv,list *l,int Hflag,int j,int nflag,int oflag,int iflag,int bflag,int wflag,int cflag,int vflag);
int switch_fflag(char *word,char *argv,list *l,char* fval,int Hflag,int j,int oflag,int iflag,int wflag,int cflag);
int switch_rflag(char *word,char **argv,int argc,list *l,int lflag,int Hflag,int oflag,int bflag,int vflag,int iflag,int wflag,int cflag);
int switch_defaultflag(char *word,char *argv,list *l,int Hflag,int j,int iflag,int wflag,int cflag,int oflag);
int switch_eflag(char *word,char *argv,int e,list *l,char **expr,int Hflag,int j,int iflag,int wflag,int cflag,int oflag);







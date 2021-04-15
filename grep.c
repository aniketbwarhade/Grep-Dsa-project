#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include "list.h"
#include "functions.h"
#include "highlight.h"
void addFilesRecursively(char *basePath, list *l) {
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    if (!dir) 
        return;
    while ((dp = readdir(dir)) != NULL) {
        if(dp->d_type==DT_DIR){
             if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
                    strcpy(path, basePath);
                    strcat(path, "/");
                    strcat(path, dp->d_name);
                    addFilesRecursively(path,l);
             }
        }
        else{
            strcpy(path, basePath);
        	strcat(path, "/");
        	strcat(path, dp->d_name);
            if(path[strlen(path)-1]=='t' && path[strlen(path)-2]=='x' && path[strlen(path)-3]=='t')
                insert(l,path);
        }
    }
    

    closedir(dir);
}

// oflag for -r -i -o function to highlight word in line rather than enter word
void roflag(char *word, char *line,int iflag) {
	int h, i =0, j = strlen(word);
	char *str;
    if(iflag==1)
	    str = kmpstrcasestr(line, word);
    else
	    str = kmpstrstr(line, word);

	h = strlen(str);
	h = strlen(line) - h;
	while(line[i] != '\0') {
		if(i == h) {
			while(j) {
				red();
				printf("%c", line[i]);
				reset();
				j--;
                i++;
			}
		}
        i++;
	}
	printf("\n");
}

int switch_lflag(char *word,char *argv,list *l){
     char line[1024];
     while(!isempty(*l)) {
        char *fileName;
        int fd;
        fileName = pop(l);
        fd = open(fileName, O_RDONLY);
        if(fd == -1) {
            printf("%s: %s: No such file or directory\n", argv, fileName);
            continue;
        }
        while(readLine(fd, line)) {
            if(kmpstrstr(line, word) != NULL) {
                purple();
                printf("%s\n", fileName);
                reset();
                break;	
            }	   	 
        }
        close(fd);
    }
    return 0;
}

int switch_Hflag(char *word,char *argv,list *l,int iflag,int wflag){
    char line[1024];
    while(!isempty(*l)){
        char* fileName=pop(l);
        int fd=open(fileName,O_RDONLY);
        if(fd == -1) {
            printf("%s: %s: No such file or directory\n", argv, fileName);
            continue;
        }
        while(readLine(fd,line)){
            if(search(word,line,iflag,wflag)){
                Hfile(fileName);
                highlight(word,line,iflag);
            }
        }
        close(fd);
    }
    return 0;
}

int switch_hflag(char *word,char *argv,list *l,int iflag,int wflag,int Hflag,int cflag,int oflag){
    char line[1024];
    while(!isempty(*l)) {
			char *fileName = pop(l);
			int fd = open(fileName, O_RDONLY);
			if(fd == -1) {
				printf("%s: %s: No such file or directory\n", argv, fileName);
				continue;
			}
			while(readLine(fd, line)) {
    	 		if(search(word, line, iflag, wflag) == 1) {
    	 			if(Hflag)
    	 				Hfile(fileName);				
    	 			if(!cflag) {
    	 				if(!oflag)	
  	    		 			highlight(word, line,iflag);
  	    		 		else
  	    		 			printf("%s\n", word);
  	    		 	}
    			}	   	 
   	 		}
   	 		close(fd);
   	 	}
   	 return 0;
}

int switch_oflag(char *word,char *argv,list *l,int Hflag,int j){
    char line[1024];
    while(!isempty(*l)){
            char *fileName=pop(l);
            int fd=open(fileName,O_RDONLY);
            if(fd == -1) {
				printf("%s: %s: No such file or directory\n", argv, fileName);
				continue;
			}
            while(readLine(fd,line)){
                if(kmpstrstr(line,word)!=NULL){
                    if(j!=1 || Hflag==1){
                        Hfile(fileName);
                    }
                    red();
                    printf("%s\n",word);
                }
            }
            close(fd);
            reset();
        }
        return 0;
}

int switch_nflag(char *word,char *argv,list *l,int Hflag,int j,int iflag){
    char line[1024];
    while(!isempty(*l)) {
        char *fileName = pop(l);
        int fd = open(fileName, O_RDONLY);
        if(fd == -1) {
            printf("%s: %s: No such file or directory\n", argv, fileName);
            continue;
        }
        int n = 0;
        while(readLine(fd, line)) {
            n++;
            if(kmpstrstr(line, word) != NULL) {
                if(j != 1 || Hflag)
                    Hfile(fileName);
                green();
                printf("%d", n);
                blue();
                printf(":");
                reset();
                highlight(word,line,iflag);
            }	   	 
        }
        close(fd);
	}
		return 0;
}

int switch_cflag(char *word,char *argv,list *l,int Hflag,int j){
     char line[1024];
     while(!isempty(*l)){
        char *fileName=pop(l);
        int fd=open(fileName,O_RDONLY);
        if(fd<0){
            printf("%s: %s no such file or directory :\n",argv,fileName);
            continue;
        }
        int c=0;
        while(readLine(fd,line)){
            if(kmpstrstr(line,word)){
                c++;
            }
        }
        if(j!=1 || Hflag){
            Hfile(fileName);
        }
        printf("%d",c);

    }
    return 0;
}

int switch_wflag(char *word,char *argv,list *l,int Hflag,int j,int iflag,int wflag,int cflag,int oflag){
    char line[1024];
    while(!isempty(*l)){
        char *fileName=pop(l);
        int c=0;
        int fd=open(fileName,O_RDONLY);
        if(fd<0){
            printf("%s: %s no such file or directory :\n",argv,fileName);
            continue;
        }
        while(readLine(fd, line)) {
            if(search(word, line, iflag, wflag)) {
                if(!cflag) {
                    if(j != 1 || Hflag)
                        Hfile(fileName);
                    if(!oflag)	
                        highlight(word, line,iflag);
                    else
                        printf("%s\n", word);
                }
                c++;
            }
        }
        if(cflag) {
            if(j != 1 || Hflag)
                Hfile(fileName);
            printf("%d\n", c);
        }
        close(fd);
    }
    return 0;
}

int switch_vflag(char *word,char *argv,list *l,int Hflag,int j,int iflag,int wflag,int cflag){
    char line[1024];
    while(!isempty(*l)){
            char *fileName=pop(l);
            int c=0;
            int fd=open(fileName,O_RDONLY);
            if(fd<0){
                printf("%s: %s no such file or directory :\n",argv,fileName);
                continue;
            }
            while(readLine(fd,line)){
                if(!search(word,line,iflag,wflag)){
                    c++;
                    if(j != 1 || Hflag) {
						if(!cflag)
    						Hfile(fileName);
    				}
  	    		 	if(!cflag) {
    	 				printf("%s\n", line);
  	    		 	}
                    
                }
            }
            if(cflag){
                if(j!=1 || Hflag)
                    Hfile(fileName);
                printf("%d\n",c);
            }
            close(fd);
        }
        return 0;
}

int switch_mflag(char *word,char *argv,list *l,int Hflag,int j,int oflag,int iflag,int wflag,int cflag,int vflag,int bflag,int mval){
    char line[1024];
    while(!isempty(*l)) {
			char *fileName = pop(l);
			int fd = open(fileName, O_RDONLY);
			int q = 0;
			int k = 0;
			if(fd == -1) {
				printf("%s: %s: No such file or directory\n", argv, fileName);
				continue;
			}
			int i = 0;
			while(readLine(fd, line)) {
				if(search(word, line, iflag, wflag) && i < mval && !vflag) {
					i++;
					if(!cflag) {
						if(j != 1 || Hflag)
							Hfile(fileName);
						if(bflag)
							Hbyte_offset(k);
    	 				if(!oflag)	
  	    	 				highlight(word, line,iflag);
  	    	 			else
  	    	 				printf("%s\n", word);
  	    	 		}
  	    	 	}
  	    	 	else if(!(search(word, line, iflag, wflag)) && q < mval && vflag) {
  	    	 		q++;
					if(!cflag) {
						if(j != 1 || Hflag)
							Hfile(fileName);
						if(bflag)
							Hbyte_offset(k);
    	 				if(!oflag)	
  	    	 				highlight(word, line,iflag);
  	    	 			else
  	    	 				printf("%s\n", word);
  	    	 		}
  	    	 	}
  	    	  k = k + strlen(line) + 1; 	    	 		
  	    	}
  	    	if(cflag && vflag) {
  	    		Hfile(fileName);
  	    		printf("%d\n", q);
  	    	}
  	    	if(cflag && !vflag) {
  	    		Hfile(fileName);
  	    		printf("%d\n", i);
  	    	}
  	    	k = 0; 
  	    	close(fd);
  	    	i = 0;
  	    	q = 0;
  	    }
  	   
  	    return 0;
}

int switch_bflag(char *word,char *argv,list *l,int Hflag,int j,int oflag,int iflag,int wflag,int cflag){
    char line[1024];
    while(!isempty(*l)) {
        char *fileName = pop(l);
        int fd = open(fileName, O_RDONLY);
        if(fd == -1) {
            printf("%s: %s: No such file or directory\n", argv, fileName);
            continue;
        }
        int i = 0;
        while(readLine(fd, line)) {
            if(search(word, line, iflag, wflag)) {
                if(j != 1 || Hflag)
                    Hfile(fileName);
                green();
                printf("%d", i);
                blue();
                printf(":");
                reset();
                if(!cflag) {
                    if(!oflag)	
                        highlight(word, line,iflag);
                    else
                        printf("%s\n", line);
                }
            }
            i = i + strlen(line) + 1;
        }
        close(fd);
   	}
   	return 0;
}

int switch_iflag(char *word,char *argv,list *l,int Hflag,int j,int nflag,int oflag,int iflag,int bflag,int wflag,int cflag,int vflag){
    char line[1024];
    if(wflag) {
        int k = 0, c = 0, f = 0;
        while(!isempty(*l)) {
            char *fileName = pop(l);
            int fd = open(fileName, O_RDONLY);
            if(fd == -1) {
                printf("%s: %s: No such file or directory\n", argv, fileName);
                continue;
            }
            while(readLine(fd, line)) {
                if((search(word, line, iflag, wflag)) && (!vflag)) {
                    c++;		
                    if(j != 1 || Hflag) {
                        if(!cflag)
                            Hfile(fileName);
                    }
                    if(bflag){
                        Hbyte_offset(k);
                    }
                    if(!cflag){
                        highlight(word,line,iflag);
                    }
                }
                else if((!search(word, line, iflag, wflag)) && vflag) {
                    f++;
                    if(bflag)
                        Hbyte_offset(k);
                    if(j != 1 || Hflag) {
                        if(!cflag)
                            Hfile(fileName);
                    }
                    if(!cflag)
                        printf("%s\n", line);
                }
                k = k + strlen(line) + 1;
            }
            if(cflag && vflag) {
                Hfile(fileName);
                printf("%d\n", f);
            }
            if(cflag && !vflag) {
                Hfile(fileName);
                printf("%d\n", c);
            }
            c = 0;
            f = 0;
            close(fd);
            k = 0;
        }
        return 0;
    }
    else {
        int i = 0, m = 0;
        int k = 0;
        while(!isempty(*l)) {
            char *fileName = pop(l);
            int fd = open(fileName, O_RDONLY);
            if(fd == -1) {
                printf("%s: %s: No such file or directory\n", argv, fileName);
                continue;
            }
            while(readLine(fd, line)) {   	 			
                if(vflag) {
                    if(!(search(word, line , iflag, wflag))) {
                        m++;
                        if(cflag == 0) {
                            if(nflag) {
                                green();
                                printf("%d", m);
                                blue();
                                printf(":");
                                reset();
                                if(!cflag) {
                                    if(!oflag)	
                                        highlight(word, line,iflag);
                                    else
                                        printf("%s\n", word);
                                }
                            }
                            if(j != 1 || Hflag)
                                Hfile(fileName);
                            if(bflag)
                                Hbyte_offset(k);
                            if(!cflag) {
                                printf("%s\n", line);
                            }
                        }
                        
                    }
                }		
                else {
                    if(search(word, line, iflag, wflag)) {	
                        if(!cflag) {
                            if(j != 1 || Hflag)
                                Hfile(fileName);
                            if(bflag)
                                Hbyte_offset(k);
                            if(!cflag) {
                                if(!oflag)	
                                    highlight(word, line,iflag);
                                else
                                    printf("%s\n", word);
                            }
                        }
                        i++;
                    }
                }
                k = k + strlen(line) + 1;
            }
            if((cflag) && vflag) {
                if(Hflag || j != 1)
                    Hfile(fileName);
                printf("%d\n", m);
            }
            if((cflag) && !vflag) {
                if(Hflag || j != 1)
                    Hfile(fileName);
                printf("%d\n", i);
            }
            i = 0,m=0; 	
            k = 0;
            close(fd);
        }
    }
   	return 0; 
}

int switch_fflag(char *word,char *argv,list *l,char* fval,int Hflag,int j,int oflag,int iflag,int wflag,int cflag){
    char expr[1024];
    char line[1024];
    int expfile=open(fval,O_RDONLY);
        while(!isempty(*l)){
            char *fileName=pop(l);
            int fd=open(fileName,O_RDONLY);
            if(fd<0){
                printf("%s: %s no such file or directory :\n",argv,fileName);
                continue;
            }
            while(readLine(fd,line)){
                int n=0;
                while(readLine(expfile,expr)){
                    if(search(expr,line,iflag,wflag)){
                        n++;
                        if(n==1){
                            if(Hflag || j!=1){
                                Hfile(fileName);
                            }
                            if(!cflag){
                                if(!oflag){
                                   printf("%s\n",line);
                                }
                                else{
                                    printf("%s\n",expr);
                                }
                            }
                        }

                    }
                }
                lseek(expfile, 0, SEEK_SET);
            }

            close(fd);
        }
        close(expfile);
        return 0;
}

int switch_rflag(char *word,char **argv,int argc,list *l,int lflag,int Hflag,int oflag,int bflag,int vflag,int iflag,int wflag,int cflag){
    int j=0,i=0;
    char line[1024];
    init(l);
    addFilesRecursively(argv[argc-1],l);
    if(lflag) {
        return switch_lflag(word,argv[0],l);
    }
    while(!isempty(*l)) {
        char *fileName = pop(l);
        int fd = open(fileName, O_RDONLY);
        if(fd == -1) {
            printf("%s: %s: No such file or directory\n", argv[0], fileName);
            continue;
        }
        while(readLine(fd, line)) {
            if(search(word, line, iflag, wflag) == 1 && !(vflag)) {
                i++;
                if(!cflag)
                    Hfile(fileName);
                if(bflag && !cflag) {
                    green();
                    printf("%d", j);
                    blue();
                    printf(":");
                    reset();
                }
                if(!cflag) {
                    if(!oflag)	
                        highlight(word, line,iflag);
                    else{ 
                        roflag(word,line,iflag) ;  
                    }

                }
            }	
            else if(!(search(word, line, iflag, wflag)) && vflag) {
                i++;
                Hfile(fileName);
                if(bflag && !cflag) {
                    green();
                    printf("%d", j);
                    blue();
                    printf(":");
                    reset();
                }
    
                if(!cflag) {
                    if(!oflag)	
                        highlight(word, line,iflag);
                    else
                        roflag(word,line,iflag) ;
                }
            }

            j = j + strlen(line) + 1;
        }
        j = 0;
        if(cflag) {
            Hfile(fileName);
            printf("%d\n", i);
        }
        i = 0;
        close(fd);
    }
    return 0;
}


int switch_defaultflag(char *word,char *argv,list *l,int Hflag,int j,int iflag,int wflag,int cflag,int oflag){
    char line[1024];
    while(!isempty(*l)){
        char *fileName=pop(l);
        int fd=open(fileName,O_RDONLY);
        if(fd==-1){
            printf("%s: %s: No such file or directory\n", argv, fileName);
            continue;
        }
        else{
            while(readLine(fd,line)){
                if(search(word,line,iflag,wflag)==1){
                    if(j != 1 || Hflag)
                        Hfile(fileName);				
                    if(!cflag) {
                        if(!oflag)	
                            highlight(word, line,iflag);
                        else
                            printf("%s\n", line);
                    }
                }
            }
        }

    }

    return 0;
}

int switch_eflag(char *word,char *argv,int e,list *l,char **expr,int Hflag,int j,int iflag,int wflag,int cflag,int oflag){
      char line[1024];
        while(!isempty(*l)){
            char *fileName=pop(l);
            int fd=open(fileName,O_RDONLY);
            if(fd<0){
                printf("%s: %s: No such file or directory\n", argv, fileName);
                continue;
            }
            while(readLine(fd,line)){
                int i=0,n=0;
                while(i<e){
                    if(search(expr[i],line,iflag,wflag)==1){
                        n++;
                        if(n==1){
                            if(Hflag || j!=1){
                                Hfile(fileName);
                            }
                            if(!cflag){
                                if(!oflag){
                                    printf("%s\n",line);
                                }
                                else{
                                    printf("%s\n",expr[i]);
                                }
                            }
                        }
                    }
                    i++;
                }
            }
            close(fd);
        }
        return 0;
}
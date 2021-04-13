#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include "list.h"
#include<fcntl.h>
#include "functions.h"
#include"highlight.h"
#include "grep.h"
int main(int argc,char **argv){
    char *fileName;
    list l;
    char word[50];
    int fd,i,j;
    char line[1024],expr[1024];
    int opt;
    int iflag=0,cflag=0,fflag=0,hflag=0,bflag=0,Hflag=0,nflag=0,lflag=0,wflag=0,rflag=0,oflag=0,eflag=0,vflag=0,Eflag=0,flag=1;
    while((opt=getopt(argc,argv,"siwvcHonlhm:bqre:f:"))!=-1){
        switch(opt){
            case 'i':
                iflag=1;
                break;
            case 'c':
                cflag=1;
                break;
            case 'f':
                fflag=1;
                break;
            case 'h':
                hflag=1;
                break;
            case 'H':
                Hflag=1;
                break;
            case 'n':
                nflag=1;
                break;
            case 'b':
                bflag=1;
                break;
            case 'l':
                lflag=1;
                break;
            case 'w':
                wflag=1;
                break;
            case 'o':
                oflag=1;
                break;
            case 'r':
                rflag=1;
                break;
            case 'e':
                eflag=1;
                break;
            case 'v':
                vflag=1;
                break;
            default:
                flag=1;
                break;
        }
    }
    strcpy(word,argv[argc-2]);
    init(&l);
    if(rflag){
        int j=0,i=0;
        init(&l);
        addFilesRecursively(argv[argc-1],&l);
        while(!isempty(l)) {
   			fileName = pop(&l);
   			fd = open(fileName, O_RDONLY);
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
    if(fflag==1){
        i=3;
        flag=0;
    }
    else
        i=1;
    j=0;
    while(i<argc){
        if(dotpresent(argv[i]) && !dashpresent(argv[i])){
            insert(&l,argv[i]);
            j++;
        }
        else if(!dotpresent(argv[i])&&!dashpresent(argv[i])){
            strcpy(word,argv[i]);
        }
        else if(dashpresent(argv[i])){
            flag=0;
        }
        i++;
    }
    if(flag==1){
        while(!isempty(l)){
            fileName=pop(&l);
            fd=open(fileName,O_RDONLY);
            if(fd==-1){
                printf("%s: %s: No such file or directory\n", argv[0], fileName);
				continue;
            }
            else{
                while(readLine(fd,line)){
                    if(search(word,line,iflag,wflag)==1){
                        if(j != 1 || Hflag)
    		 			    Hfile(fileName);				
    		 		    if(!cflag) {
    	 				    if(!iflag)	
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
    
    if(fflag){
        int expfile=open(optarg,O_RDONLY);
        while(!isempty(l)){
            fileName=pop(&l);
            fd=open(fileName,O_RDONLY);
            if(fd<0){
                printf("%s: %s no such file or directory :\n",argv[0],fileName);
                continue;
            }
            while(readLine(fd,line)){
                int n=0;
                while(readLine(expfile,expr)){
                    int s=search(expr,line,iflag,wflag);
                    if(s){
                        n++;
                        if(n==1){
                            if(Hflag || j!=1)
                                Hfile(fileName);
                            if(!cflag){
                                if(!oflag){
                                    highlight(expr,line,iflag);
                                }
                                else{
                                    red();
                                    printf("%s\n",expr);
                                    reset();
                                }
                            }
                        }

                    }
                }
                lseek(expfile, 0, SEEK_SET);
            }

            close(fd);
            close(expfile);
        }
        return 0;
    }
    
    if(iflag) {
        if(wflag) {
            int k = 0, c = 0, f = 0;
            while(!isempty(l)) {
                fileName = pop(&l);
                fd = open(fileName, O_RDONLY);
                if(fd == -1) {
                    printf("%s: %s: No such file or directory\n", argv[0], fileName);
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
                            bprint(k);
                        }
                        if(!cflag){
                            printf("%s\n", line);
                        }
                    }
                    else if((!search(word, line, iflag, wflag)) && vflag) {
                        f++;
                        if(bflag)
                            bprint(k);
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
                    printf("%d\n", i);
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
            while(!isempty(l)) {
                fileName = pop(&l);
                fd = open(fileName, O_RDONLY);
                if(fd == -1) {
                    printf("%s: %s: No such file or directory\n", argv[0], fileName);
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
                                        if(!iflag)	
                                            highlight(word, line,iflag);
                                        else
                                            printf("%s\n", line);
                                    }
                                }
                            }
                            if(j != 1 || Hflag)
                                Hfile(fileName);
                            if(bflag)
                                bprint(k);
                            if(!cflag) {
                                if(!iflag)	
                                    highlight(word, line,iflag);
                                else
                                    printf("%s\n", line);
                            }
                        }
                    }		
                    else {
                        if(search(word, line, iflag, wflag)) {	
                            if(!cflag) {
                                if(j != 1 || Hflag)
                                    Hfile(fileName);
                                if(bflag)
                                    bprint(k);
                                if(!cflag) {
                                    if(!iflag)	
                                        highlight(word, line,iflag);
                                    else
                                        printf("%s\n", line);
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
                i = 0; 	
                k = 0;
                close(fd);
            }
        }
   		return 0; 
	}
    if(vflag){
        while(!isempty(l)){
            fileName=pop(&l);
            int c=0;
            fd=open(fileName,O_RDONLY);
            if(fd<0){
                printf("%s: %s no such file or directory :\n",argv[0],fileName);
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
    if(wflag){
        while(!isempty(l)){
            fileName=pop(&l);
            int c=0;
            fd=open(fileName,O_RDONLY);
            if(fd<0){
                printf("%s: %s no such file or directory :\n",argv[0],fileName);
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

    if(cflag){
        while(!isempty(l)){
            fileName=pop(&l);
            fd=open(fileName,O_RDONLY);
            if(fd<0){
                printf("%s: %s no such file or directory :\n",argv[0],fileName);
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
    return 0;
}




#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include "list.h"
#include<fcntl.h>
#include "functions.h"
#include"highlight.h"
int main(int argc,char **argv){
    char *fileName;
    list l;
    char word[50];
    int fd,i,j;
    char line[1024],expr[1024];
    int opt;
    int iflag=0,cflag=0,fflag=0,hflag=0,Hflag=0,nflag=0,lflag=0,wflag=0,oflag=0,eflag=0,vflag=0,Eflag=0,flag=1;
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
            case 'l':
                lflag=1;
                break;
            case 'w':
                wflag=1;
                break;
            case 'o':
                oflag=1;
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
  	    	 				    highlight(word, line);
  	    	 			    else
  	    	 				    printf("%s\n", line);
  	    	 		    }
                    }
                }
            }

        }


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
                                    highlight(expr,line);
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

    }
    return 0;
}




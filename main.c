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
    list l;
    char word[50];
    int  i,j,mval;
    char fval[50];
    char **expr;
    expr=(char **)malloc(sizeof(char *)*20);
    for(int k=0;k<20;k++){
        expr[k]=(char *)malloc(sizeof(char)*40);
    }
    int opt,e=0;
    int iflag=0,cflag=0,fflag=0,hflag=0,bflag=0,mflag=0,Hflag=0,nflag=0,lflag=0,wflag=0,rflag=0,oflag=0,eflag=0,vflag=0,Eflag=0,flag=1;
    while((opt=getopt(argc,argv,"siwvcHonlhbqr:e:f:m:"))!=-1){
        switch(opt){
            case 'i':
                iflag=1;
                break;
            case 'c':
                cflag=1;
                break;
            case 'f':
                fflag=1;
                strcpy(fval,optarg);
                break;
            case 'm':
                mflag=1;
                mval=atoi(optarg);
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
                strcpy(expr[e++],optarg);
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
        return switch_rflag(word,argv,argc,&l,lflag,Hflag,oflag,bflag,vflag,iflag,wflag,cflag);
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
        return switch_defaultflag(word,argv[0],&l,Hflag,j,iflag,wflag,cflag,oflag);
    }
    if(fflag){
        return switch_fflag(word,argv[0],&l,fval,Hflag,j,oflag,iflag,wflag,cflag);
    }
    
    if(iflag) {
        return switch_iflag(word,argv[0],&l,Hflag,j,nflag,oflag,iflag,bflag,wflag,cflag,vflag);    
	}
    if(bflag) {
        return switch_bflag(word,argv[0],&l,Hflag,j,oflag,iflag,wflag,cflag);
   	}	 		
    if(mflag) {
        return switch_mflag(word,argv[0],&l,Hflag,j,oflag,iflag,wflag,cflag,vflag,bflag,mval);
	}
    if(vflag){
        return switch_vflag(word,argv[0],&l,Hflag,j,iflag,wflag,cflag); 
    }
    if(lflag) {
        return switch_lflag(word,argv[0],&l);
	}
   	 
    if(wflag){
        return switch_wflag(word,argv[0],&l,Hflag,j,iflag,wflag,cflag,oflag);
    }

    if(cflag){
        return switch_cflag(word,argv[0],&l,Hflag,j);
    }
    if(nflag) {
        return switch_nflag(word,argv[0],&l,Hflag,j,iflag);
   	}
    if(eflag){
        return switch_eflag(word,argv[0],e,&l,expr,Hflag,j,iflag,wflag,cflag,oflag);
    }
    if(oflag){
        return switch_oflag(word,argv[0],&l,Hflag,j);
    }
    if(hflag) {
        return switch_hflag(word,argv[0],&l,iflag,wflag,Hflag,cflag,oflag);
	}
    if(Hflag){
        return switch_Hflag(word,argv[0],&l,iflag,wflag);
    }
    return 0;
}




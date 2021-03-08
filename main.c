#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<unistd.h>
#include<fcntl.h>
#include "grep.h"
int main(int argc,char **argv){
    char fileName[50];
    strcpy(fileName,argv[argc-1]);
    char word[50];
    strcpy(word,argv[argc-2]);
     int fd;
    char line[1024];
    fd=open(fileName,O_RDONLY);
    int opt;
    int iflag=0,cflag=0,fflag=0,hflag=0,Hflag=0,nflag=0,lflag=0,wflag=0,oflag=0,eflag=0,vflag=0,Eflag=0;
    printf("%d",cflag);
    while((opt=getopt(argc,argv,"icfhHnlwoevE")!=-1)){
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
            
        }
    }
    if(iflag==1){
        optiflag(fd,word);
    }
    // if(fd!=-1){
    //     while(readLine(fd,line)){
    //         if(find(word,line)==1)
    //             printf("%s",line);
    //     }
    // }
    // else{
    //     printf("file can't open");
    // }    
    // close(fd);
return 0;
}
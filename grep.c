#define _GNU_SOURCE
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <dirent.h>
#include<fcntl.h>
#include "grep.h"
void openDir(char *base) 
{ 
    struct dirent *de;  // Pointer for directory entry 
    DIR *dr = opendir(base); 
    if (dr == NULL)  
    { 
        printf("Could not open current directory" ); 
        return ;
    } 
    while ((de = readdir(dr)) != NULL) 
            printf("%s\n", de->d_name); 
  
    closedir(dr);     
    return ; 
} 
int readLine(int fd, char *line) {
    int i =0;
    char ch;
    while(read(fd, &ch, 1) ) {
    	if(ch != '\n')
			line[i++] = ch;
		else if(ch == '\n') {
			line[i] = '\0';
			return i + 1;
		}
	}
	line[i] = '\0';
    return i;    
}
int find(char *word, char *line) {
    if((strstr(line, word)) != NULL) 
        return 1;
    else
        return 0;
}

// int main(){
//     // char base[]="C:\Users\anike\Desktop\Dsa-project";
//     // openDir(base);
//     int fd;
//     char line[1024];
//     fd=open("C:/Users/anike/Desktop/Dsa-project/abc.txt",O_RDONLY);
//     if(fd!=-1){
//         while(readLine(fd,line)){
//             if(find("aniket",line)==1)
//                 printf("%s",line);
//         }
//     }
//     else{
//         printf("file can't open");
//     }    
//     close(fd);
//     return 0;
// }
char smallTocapital(char a){
    return a-32;
}
void optiflag(int fd,char *word){
    char line[1024];
    while(readLine(fd,line)){
        if((strcasestr(line,word))!=NULL){
            printf("%s",line);
        }
        
    }
}
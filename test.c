#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

void listFilesRecursively(char *basePath, list *l) {
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
                    listFilesRecursively(path,l);
             }
        }
        else{
            strcpy(path, basePath);
        	strcat(path, "/");
        	strcat(path, dp->d_name);
            if(path[strlen(path)-1]=='t')
                insert(l,path);
        }
    }
    

    closedir(dir);
}

int main(){
    list l;
    init(&l);

    listFilesRecursively("C:/Users/anike/Documents/text files",&l);
    char *path;
    
    while(!isempty(l)){
        path=pop(&l);
        printf("%s\n",path);
    }
    return 0;
}
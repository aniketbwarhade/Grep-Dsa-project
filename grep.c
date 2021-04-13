#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
            if(path[strlen(path)-1]=='t')
                insert(l,path);
        }
    }
    

    closedir(dir);
}

// oflag for -r -i -o function
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
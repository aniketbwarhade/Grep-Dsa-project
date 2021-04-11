#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include "functions.h"
// function to convert all string alphabet in lower case
char *capitalTosmall(char *str){
    for(int i=0;i<strlen(str);i++){
        if(str[i]>=65 && str[i]<=90){
            str[i]+=32;
        }
    }
    return str;
}
// function to convert all string alphabet in upper case
char *smallTocapital(char *str){
    for(int i=0;i<strlen(str);i++){
        if(str[i]>=97 && str[i]<=122){
            str[i]-=32;
        }
    }
    return str;
}
// to read line in file 
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
// to check weather "." is present or not
int dotpresent(char *str) {
	for(int i = 0; i < strlen(str); i++) {
		if(str[i] == '.') {
			return 1;
		}
	}
	return 0;
}
// to check weather "-" is present or not
int dashpresent(char *str) {
	int i;
	for(i = 0; i < strlen(str); i++) {
		if(str[i] == '-')
			return 1;
	}
	return 0;
}

// implement strcasestr using kmp algorithm

char *kmpstrcasestr(char *str, char *pattern) {
    char capitalLetterline[1024];
    char word[512];
    strcpy(word,pattern);
    strcpy(capitalLetterline,str);
    strcpy(word,smallTocapital(word));
    strcpy(capitalLetterline,smallTocapital(capitalLetterline));
    return kmpstrstr(capitalLetterline,word);
}

void computeLPSArray(char* pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;
  
    lps[0] = 0; // lps[0] is always 0
  
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];
  
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
char* kmpstrstr(char* txt, char* pat)
{
	int M = strlen(pat);
    int N = strlen(txt);
	if (*pat == '\0' || M == 0)
        return txt;
 
    // Base Case 2: X is NULL or X's length is less than that of Y's
    if (*txt == '\0' || M > N)
        return NULL;
    
  
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];
  
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
  
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            i++;
            j++;
            
        }
        if (j == M) {
            return txt+i-j;
            // j = lps[j - 1]; if we want to find all occurences of pattern
        }
  
        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
	return NULL;
}
  
int search(char *word,char *line,int iflag,int wflag){
    int i,j,k;
    char str[512][256];

    if((iflag==0) && (wflag==0)){
        if(kmpstrstr(line,word)!=NULL){
            return 1;
        }
        else    
            return 0;
    }
    if((iflag==1) && (wflag==0)){
        if(kmpstrcasestr(line,word)!=NULL){
            return 1;
        }
        else
            return 0;
    }
    if((iflag==0) && (wflag==1)){
        i=0,j=0,k=0;
        while(i<strlen(line)+1){
            if((line[i]>=65 && line[i]<=90) || (line[i]>=97 && line[i]<=122) ){
                str[j][k]=line[i];
                i++;
                k++;
            }
            else{
                str[j][k]='\0';
                j++;
                i++;
                k=0;
            }
        }
        for(i = 0; i < j; i++) {
   	 		if(strcmp(word, str[i]) == 0)
   	 			return 1;
   	 	}
   	 		return 0;
    }
    if(iflag==1 && wflag==1){
        char smallLetterline[1024];
        char patn[512];
        strcpy(smallLetterline, line);
        strcpy(patn, word);
		strcpy(word, capitalTosmall(patn));
		strcpy(smallLetterline, capitalTosmall(smallLetterline));
		while(i < strlen(smallLetterline) + 1) {
   	 			if((smallLetterline[i] >= 97 && smallLetterline[i] <= 122)) {
   	 				str[j][k] = smallLetterline[i];
   	 				i++;
   	 				k++;
   	 			}
   	 			else {
   	 				str[j][k] = '\0';
   	 				j++;
   	 				i++;
   	 				k = 0;
   	 			}
   	 		}
   	 		for(i = 0; i < j; i++) {
   	 			if(strcmp(word, str[i]) == 0)
   	 				return 1;
   	 		}
   	 		return 0;
    }
    return 0;

}

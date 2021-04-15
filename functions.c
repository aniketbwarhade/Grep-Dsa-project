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
        i=0,j=0,k=0;
        char smallLetterline[1024];
        char patn[512];
        strcpy(smallLetterline, line);
        strcpy(patn, word);
		strcpy(patn, capitalTosmall(patn));
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
            if(strcmp(patn, str[i]) == 0)
                return 1;
        }
        return 0;
    }
    return 0;
}


void printHelp() {
		printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
		printf("Search for PATTERNS in each FILE.\n");
		printf("Example: grep -i 'hello world' menu.txt main.txt\n");
		printf("PATTERNS can contain multiple patterns separated by newlines.\n\n");

		printf("Pattern selection and interpretation:\n");	
		printf("\t-G, --basic-regexp        PATTERNS are basic regular expressions\n"); //default
  		printf("\t-e, --regexp=PATTERNS     use PATTERNS for matching\n");
  		printf("\t-f, --file=FILE           take PATTERNS from FILE\n");
  		printf("\t-i, --ignore-case         ignore case distinctions\n");
  		printf("\t-w, --word-regexp         match only whole words\n");

		printf("Miscellaneous:\n");
  		printf("\t-v, --invert-match        select non-matching lines\n");
      	printf("\t--help                display this help text and exit\n\n");

		printf("Output control:\n");
  		printf("\t-m, --max-count=NUM       stop after NUM selected lines\n");
  		printf("\t-b, --byte-offset         print the byte offset with output lines\n");
  		printf("\t-n, --line-number         print line number with output lines\n");
  		printf("\t-H, --with-filename       print file name with output lines\n");
  		printf("\t-h, --no-filename         suppress the file name prefix on output\n");
  		printf("\t-o, --only-matching       show only nonempty parts of lines that match\n");
  		printf("\t-q, --quiet, --silent     suppress all normal output\n");
  		printf("\t-r, --recursive           like --directories=recurse\n");
  		printf("\t-L, --files-without-match  print only names of FILEs with no selected lines\n");
  		printf("\t-l, --files-with-matches  print only names of FILEs with selected lines\n");
 		printf("\t-c, --count               print only a count of selected lines per FILE\n");

		printf("Context control:\n");
  		printf("\t-B, --before-context=NUM  print NUM lines of leading context\n");
  		printf("\t-A, --after-context=NUM   print NUM lines of trailing context\n");
  		printf("\t-C, --context=NUM         print NUM lines of output context\n");

		printf("When FILE is '-', read standard input.  With no FILE, read '.' if\n");
		printf("recursive, '-' otherwise.  With fewer than two FILEs, assume -h.\n");
		printf("Exit status is 0 if any line (or file if -L) is selected, 1 otherwise;\n");
		printf("\tif any error occurs and -q is not given, the exit status is 2.\n\n");

		printf("Report bugs to: bug-grep@gnu.org\n");
		printf("GNU grep home page: <http://www.gnu.org/software/grep/>\n");
		printf("General help using GNU software: <https://www.gnu.org/gethelp/>\n");
		return;
}
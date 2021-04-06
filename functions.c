#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ctype.h>
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
char *capitalTosmall(char *str){
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
// Ansi color
// use of ansi color code to highlight search string in differnt color
void red () {
  printf("\033[1;31m");
}

void purple() {
	printf("\033[0;35m");
}

void blue() {
	printf("\033[0;34m");
}

void yellow() {
	printf("\033[0;33m");
}

void green() {
	printf("\033[0;32m");
}

void reset () {
  printf("\033[0m");
}

// this function is available in c we can use by defining #include _GNU_SOURCE and including string.h but in vscode not run so function is directly taken from google
char *strcasestr(const char *str, const char *pattern) {
    size_t i;

    if (!*pattern)
        return (char*)str;

    for (; *str; str++) {
        if (toupper((unsigned char)*str) == toupper((unsigned char)*pattern)) {
            for (i = 1;; i++) {
                if (!pattern[i])
                    return (char*)str;
                if (toupper((unsigned char)str[i]) != toupper((unsigned char)pattern[i]))
                    break;
            }
        }
    }
    return NULL;
}
// kmp algorithm to find substring in string
char* kmpstrstr(const char* X, const char* Y)
{
	int m=strlen(X);
	int n=strlen(Y);

    // Base Case 1: Y is NULL or empty
    if (*Y == '\0' || n == 0)
        return X;
 
    // Base Case 2: X is NULL or X's length is less than that of Y's
    if (*X == '\0' || n > m)
        return NULL;
 
    // next[i] stores the index of next best partial match
    int next[n + 1];
 
    for (int i = 0; i < n + 1; i++)
        next[i] = 0;
 
    for (int i = 1; i < n; i++)
    {
        int j = next[i + 1];
 
        while (j > 0 && Y[j] != Y[i])
            j = next[j];
 
        if (j > 0 || Y[j] == Y[i])
            next[i + 1] = j + 1;
    }
 
    for (int i = 0, j = 0; i < m; i++)
    {
        if (*(X + i) == *(Y + j))
        {
            if (++j == n)
                return (X + i - j + 1);
        }
        else if (j > 0) {
            j = next[j];
            i--;    // since i will be incremented in next iteration
        }
    }
 
    return NULL;
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
char* KMPSearch(char* txt, char* pat)
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
            j++;
            i++;
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
        if(KMPSearch(line,word)!=NULL){
            return 1;
        }
        else    
            return 0;
    }
    if((iflag==1) && (wflag==0)){
        if(strcasestr(line,word)!=NULL){
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
        strcpy(smallLetterline, line);
		strcpy(word, capitalTosmall(word));
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

}
void highlight(char *word, char *line) {
	int h, i =0, j = strlen(word);
	char *str;
	str = strstr(line, word);
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
		else {
			printf("%c", line[i]);
			i++;
		}
	}
	printf("\n");
}

void bprint(int k) {
	green();
	printf("%d", k);
	blue();
	printf(":");
	reset();
}

void Hprint(char *filename) {
	purple();
    printf("%s", filename);
    blue();
    printf(":");
    reset();
}	
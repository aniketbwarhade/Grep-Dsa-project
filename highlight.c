#include<stdio.h>
#include<string.h>
#include "functions.h"

// Ansi color
// use of ansi enscape  code to highlight and give style to search string in differnt color and different style

// \033 is an ascii value of ESC sequence in octal
void reset () {
  printf("\033[0m");
}
void red () {
  printf("\033[1;31m");
}

void purple() {
	printf("\033[1;35m");
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



void highlight(char *word, char *line) {
	int h, i =0, j = strlen(word);
	char *str;
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

void Hfile(char *filename) {
	purple();
    printf("%s ", filename);
    blue();
    printf(": ");
    reset();
}	

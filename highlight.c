// Ansi color
// use of ansi color code to highlight search string in differnt color
#include<stdio.h>
#include<string.h>
#include "functions.h"
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

void reset () {
  printf("\033[0m");
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

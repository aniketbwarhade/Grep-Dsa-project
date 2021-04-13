grep: main.o functions.o highlight.o list.o grep.o
	gcc functions.o main.o  highlight.o list.o grep.o -o grep 
main.o : main.c 
		gcc -c main.c -Wall 
functions.o : functions.c functions.h
		gcc -c functions.c -Wall 
highlight.o : highlight.c highlight.h
		gcc -c highlight.c -Wall
list.o : list.c list.h
		gcc -c list.c -Wall
grep.o : grep.c grep.h
		gcc -c grep.c -Wall
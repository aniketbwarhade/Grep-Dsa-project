grep: main.o functions.o highlight.o list.o 
	gcc functions.o main.o  highlight.o list.o -o grep 
main.o : main.c
		gcc -c main.c -Wall 
functions.o : functions.c
		gcc -c functions.c -Wall 
highlight.o : highlight.c
		gcc -c highlight.c 
list.o : list.c 
		gcc -c list.c -Wall
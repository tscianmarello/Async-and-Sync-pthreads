all: threadpart1 threadpart2

threadpart1: threadpart1.c
	gcc -o threadpart1 threadpart1.c -lpthread

threadpart2: threadpart2.c
	gcc -o threadpart2 threadpart2.c -lpthread


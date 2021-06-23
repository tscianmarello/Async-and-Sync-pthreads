#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

//In order to compile, you must use gcc and run the following command:
//gcc -o name thread.c -lpthread

int SharedVariable = 0;

/*
Changed the function type from void to void * and the parameter from int to void * due to the pthread_create rules. The last argument of
of the pthread_create function call must be type void *. Since the program is using a for loop to create the threads, then an int cannot be passed
because in C an int does not necessarily occupy the same space as a void *. 
*/
void *SimpleThread(void *which) 
{
	int num, val;
	//The variable which is stored in a pointer *x.
	int *x = which;
	
	for(num = 0; num < 20; num++) {
		if (random() > RAND_MAX / 2)
			usleep(10);
	
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", *x, val);
		SharedVariable = val + 1; 
		}
		val = SharedVariable;
		printf("Thread %d sees final value %d\n", *x, val); 
}


int main(int argc, char *argv[])
{
	//Variable that will hold the user input of threads.
	int threadNum;
	//The pthread variable.
	pthread_t *thr;
	//Initialized variable that stores the current thread number in the for loop below.
	int i;

	//Check if there are either less than or more than 2 arguments. 
	if(argc != 2)
	{
		//If there are more than or less than 2 arguments then statement is printed and program returns 0 to exit.
		printf("Please provide an integer as an argument");
		return 0;
	}
	//If there are 2 arguments, the second argument is stored in threadNum.
	threadNum = strtol(argv[1], NULL, 10);

	//Then it checks if the threadNum is greater than 0. This is to prevent random garbage from being inputted.
	if(threadNum <= 0)
	{
		//If the threadNum is 0 or less, then program prints statement and exits.
		printf("Please a value above 1.\n");
		return 0;
	}
	else
	{
		//If the number of arguments is 2 and the inputted number is greater than 0, then a pointer b is initialized with the 
		//dynamically allocated block of memory with the size of an int that is explicitly casted to the int pointer and then 
		//adjusted by the user input.
		int *b = (int *)malloc(sizeof(int)*threadNum);
		//For loop that iterates from 0 to the user input and stores the vlaue of i at the current b array from above so that it
		//can be passed as the last argument in pthread_create
		for(i = 0; i < threadNum; i++)
		{
			b[i]= i;
		}
		//Initialize a phtread_t of the inputted user value.
		pthread_t thr[threadNum];
		//For loop that iterates from 0 to the total user input that creates a thread with the following 4 arguments:
		//pthread_create(thread_pointer, thread_pointer_attributes, function, initial value for thread)
		//The first argument takes the first value of the address of the thread array (&thr[i], where i is started at 0).
		//The second argument takes any attributes for the thread pointer. In this case NULL is passed since no attributes were needed.
		//The third argument takes the function, SimpleThread.
		//The fourth argument takes the initial value for the thread which is the address of the array b.
		for(i = 0; i < threadNum; i++)
		{
			pthread_create(&thr[i], NULL, SimpleThread, (void *)&b[i]);
		}
		//The for loop joins each thread and waits for the other to end.
		for(i = 0; i < threadNum; i++)
		{
			pthread_join(thr[i], NULL);
		}
	}
	exit(0);
}

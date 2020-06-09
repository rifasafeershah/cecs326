//Rifa Safeer Shah
//CECS 326 LAB 1
//Threads in C
//June 5 2020

/** 
	Q Explain what pthread is doing in this program. Be specific.
	A 	The pthread has a header library for the the C programming language.
		It includes types and procedure calls. 
		In this case, pthreads are the main thread and the sleeping thread.
		The sleeping thread carry outs its task until it is stopped by the main thread.
		In this program we use the Enter Key to do so.
	
	Q Explain why the sleeping thread can print its periodic messages while the main thread is waiting for keyboard input.
	A	I think the reason for this might be related to the category of the processes.
		When the program starts the initial child thread is sleeping for 3 seconds.
		Once it is done with that task it moves tothe main method.
		The main thread waits for 3 seconds to starts computing.
	
*/

#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Creating a thread. */
static void *child(void *ignored) {
	/* An infinite loop */
	while(1) {
		sleep(3);
		
		/* Prints the status of the child. */
		printf("Child is done sleeping 3 seconds.\n");
		//return NULL;
	} // Ends while-loop
	
	return NULL;
} // End of child class

/* Main runner. */
int main(int argc, char *argv[]) {
	pthread_t child_thread;
	
	int code;
	
	/* Enter key pressed by the user */
	char enterkey;
	
	/* Start of the child thread */
	code = pthread_create(&child_thread, NULL, child, NULL);
	
	if(code) {
		fprintf(stderr, "pthread_create failed with code %d\n", code);
	} // Ends if-statement
	
	while ((enterkey = getchar()) == '\n') {
		/* Kills the thread. */
		pthread_cancel(child_thread);
		
		sleep(5);
		
		/* Prints status of the parent. */
		printf("Parent is done sleeping 5 seconds.\n");
		
		/* The child thread not killed. */
		if (pthread_cancel(child_thread)) {
			fprintf(stderr, "The child thread was not successfully killed.");
		} // Ends if-statement
		
		/* The child thread was killed. */
		else {
			printf("The child thread was successfully killed.");
		} // Ends else-statement
		
		return 0;
	} // Ends while-loop
} //End of main class

//project source code (process manager/parent)

//send in information into the worker

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>


#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define RESET "\x1B[0m"

bool flag = true;
int thread_counter = 0; // counts the num of threads we have
char * fileName;



int main(int argc, char *argv[]){
	
	// struct timeval start, end;
	// gettimeofday(&start, NULL);

	// for(int loop=0; loop<5; loop++){
	// printf("loop #%d\n", loop);
	// thread_counter = 0;
	// flag = true;




	//checks if there is the correct number of input arguments
	if(argc != 3){
		fprintf(stderr, "Invalid input. Please input a text file and the number of parts you want the file broken into.\n");
		return 0;
	}

	//create the file name
	fileName = (char*)malloc(sizeof(char*));
	strcat(fileName, argv[1]);
	
	fileName[sizeof(fileName)-4] = '_';
	FILE * inFile = fopen(argv[1], "r");
	int splits = atoi(argv[2]);
	if(splits<1){
		fprintf(stderr, RED "Error:" RESET "Number of parts needs to be greater than 0. \n");
	}
	if(inFile == NULL){
		fprintf(stderr, RED "Error:" RESET "%s.\n", strerror(errno));
		return 0;
	}

	//finds the size of the file
	fseek(inFile, 0L, SEEK_END);
	int sz = ftell(inFile);
	fseek(inFile, 0L, SEEK_SET);
	if(sz==0){
		fprintf(stderr, RED "Error:" RESET "File is empty. There is nothing to compress.\n");
		return 0;
	}
	if(atoi(argv[2]) > sz){
		fprintf(stderr, RED "Error:" RESET "Number of parts is greater than the number of elements in the file. \n");
		return 0;
	}

	//gets the string from the file
	char * my_string = (char*)malloc((sz+1)*sizeof(char*));	//printf("bye\n");
	fgets(my_string,sz+1,inFile);
	
	//=====================================================================
	//Got string, start here
	//======================================================================

	int length = strlen(my_string);

	int length_per_thread = length/splits + length%splits;
	int remain = length%splits;

	char * ptr = my_string; //the string we're compressing
	int buffer_counter = 0;
	char * buffer = (char*)malloc(length_per_thread+1); //buffer stores substrings

	//set up for forking
	int status;
	pid_t id;
	pid_t parent;
	char* process[6];
	char * threadcount = (char*)malloc(log10(splits)+1);
	char * flagstr = (char*)malloc(1);
	char * childprogram = "./compressR_worker_LOLS";

	for (int i = 0; i < length; ++i) {
		if (buffer_counter < length_per_thread) {
			buffer[buffer_counter] = my_string[i];
			++buffer_counter;
		}
		else { // buffer counter == length per thread
			buffer[buffer_counter] = '\0';
			buffer_counter = 0;
			length_per_thread = length_per_thread-remain;
			remain = 0;
			
			//forking
			id = fork();
			waitpid(id, &status, 0);
			if (id == -1){
				exit(1); //fork failed
			} 
			if (id > 0)
			{
				waitpid(id, &status, 0);
			 }else{
				parent = getppid();
				process[0] = "./compressR_worker_LOLS";
				process[1] = fileName;
				process[2] = buffer;
				sprintf(threadcount, "%d", thread_counter);
				process[3] = threadcount;
				sprintf(flagstr, "%d", flag);
				process[4] = flagstr;
				process[5] = NULL;
				execvp(process[0], process);
				printf("ERROR: execvp failed\n");
			}

			++thread_counter;
			memset(buffer,0,strlen(buffer));
			buffer[buffer_counter] = my_string[i];
			++buffer_counter;
		}
	}	
	
	if(thread_counter==0){
		flag=false;	//this sets a flag for single compression (related to naming files)
		printf("FLAGSET\n");
	}
	//forking
	id = fork();
	waitpid(id, &status, 0);
	if (id == -1){
		exit(1); //fork failed
	} 
	if (id > 0)
	{
		waitpid(id, &status, 0);
	 }
	else{
		parent = getppid();
		process[0] = "./compressR_worker_LOLS";
		process[1] = fileName;
		process[2] = buffer;
		sprintf(threadcount, "%d", thread_counter);
		process[3] = threadcount;
		sprintf(flagstr, "%d", flag);
		process[4] = flagstr;
		process[5] = NULL;
		execvp(process[0], process);
		//fileName, buffer, thread_counter, flag, (char*) NULL);
		printf("ERROR: execvp failed\n");
	}

	free(fileName);
	free(my_string);
	free(buffer);
	free(threadcount);
	free(flagstr);



	// wait(1);


	// }

	// gettimeofday(&end, NULL);
	// printf("mean time for execution of test A: %f seconds\n", ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000.0))/5);


}












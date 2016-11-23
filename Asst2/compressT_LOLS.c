//project source code (threads)

//calls upon itself 

//INIT AND DESTORY THREADS

//existing compressions, complain and overwrite

#include <pthread.h>
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

pthread_t * threads;
bool flag = true;
int thread_counter = 0; // counts the num of threads we have
char * fileName;

void *compress_substr(void* substr) {
	//variables for compressing the string
	int strlength = strlen((char*)substr);
	char *string; // = (char*)malloc(strlength);
	string = (char*)substr;
	char curr = string[0];
	int count=0;
	
	//sets count if the curr character is an alphabetical letter
	if(isalpha(curr)){
		count=1;
	}
	
	//file management
	int digits;
	if(thread_counter==0){
		digits = 1;
	}
	else{
		digits = log10(thread_counter)+1;
	}
	char * endofstring = "\0";
	char * strnum = (char*)malloc(digits);
	char * outputname = (char*)malloc(sizeof(fileName)+6+digits);
	strcat(outputname, fileName);
	strcat(outputname, "_LOLS");
	if(flag){
		sprintf(strnum, "%d", thread_counter);
		strcat(outputname, strnum);
		strcat(outputname, endofstring);
	}
	else{
		strcat(outputname, endofstring);
	}
	FILE *output;
	output = fopen(outputname, "r");
	
	//errror checking for already existing files
	if(output != NULL){
		fprintf(stderr, RED "Error: " RESET "Compressed file already exists: %s..." GRN "OVERWRITING\n" RESET, outputname);
	}
	output = fopen(outputname, "w");

	char * charnum = (char*)malloc(log10(strlength)+1);

	for(int i=1; i<strlength;i++){
		//ignores non-alphabetical characters
		if(!isalpha(string[i])){
			fprintf(stderr, "Incompressible character: %c\n", string[i]);
			continue;
		}
		//checks if the letters are the same
		if(curr==string[i]){
			count++;
		}
		else{
			if(count>2){
				sprintf(charnum, "%d", count);
				fputs(charnum, output);
				fputc(curr, output);
			}
			if(count==2){
				fputc(curr, output);
				fputc(curr, output);
			}
			if(count==1){
				fputc(curr, output);
			}
			
			count=1;
			curr = string[i];
		}
	}
	if(count>2){
		sprintf(charnum, "%d", count);
		fputs(charnum, output);
		fputc(curr, output);
	}
	if(count==2){
		fputc(curr, output);
		fputc(curr, output);
	}
	if(count==1){
			fputc(curr, output);
	}

	fclose(output);
	printf("%s\n", outputname);
	free(strnum);
	free(outputname);
	free(charnum);
	
	pthread_exit("child_returned_string");

	return "child_returned_string";
}

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

	//find length of the file
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
	char * my_string = (char*)malloc((sz+1)*sizeof(char*));
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

	//set up the list of threads so we can access it
	threads = malloc(sizeof(pthread_t)*splits);

	void *result;

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
			
			if (pthread_create(&threads[thread_counter], NULL, &compress_substr, (void *) buffer) == 0) {
				pthread_join(*threads, &result); // results is returned. you can cast using (string)result later
			}

			++thread_counter;
			memset(buffer,0,strlen(buffer));
			buffer[buffer_counter] = my_string[i];
			++buffer_counter;
		}
	}	
	
	if(thread_counter==0){
		flag=false;	//this sets a flag for single compression (related to naming files)
	}

	if (pthread_create(&threads[thread_counter], NULL, &compress_substr, (void *) buffer) == 0) {
		pthread_join(*threads, &result); // results is returned. you can cast using (string)result later
	}

	free(fileName);
	free(my_string);
	free(buffer);
	free(threads);

	// wait(1);

	// }

	// gettimeofday(&end, NULL);
	// printf("mean time for execution of test A: %f seconds\n", ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000.0))/5);



}












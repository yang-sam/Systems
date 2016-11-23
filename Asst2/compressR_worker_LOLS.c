//project source code (process worker/child)
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

int main(int argc, char *argv[]){
	//argv[1] = fileName
	//argv[2] = string
	//argv[3] = thread_counter
	//argv[4] = flag
	bool flag;
	if(atoi(argv[4])==1){
		flag=true;
	}
	else{
		flag=false;
	}
	int thread_counter = atoi(argv[3]);
	char* fileName = (char*)malloc(sizeof(argv[1]));
	strcpy(fileName, argv[1]);


	//variables for compressing the string
	char *string = (char*)malloc(sizeof(argv[2]));
	strcpy(string, argv[2]);
	int strlength = strlen(string);
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
	free(string);
	free(fileName);
	free(strnum);
	free(outputname);
	free(charnum);
	
	return 1;

}
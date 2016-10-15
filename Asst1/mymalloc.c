#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "mymalloc.h"
#define red "\x1B[31m"
#define grn "\x1B[32m"
#define reset "\x1B[0m"

//fprintf(stderr, "%s: %d\n ", __FILE__, __LINE__);

static char myblock[5000];
static bool init = false;
static void* point[5000];
static int psize[5000];


bool checkspace(int size){
	int count;
	int openspace = 0;
	for(count = 0; openspace < size; count++){
		if(myblock[count] == '0'){
			openspace++;
		}
		else{
			openspace = 0;
		}
		if(openspace == size){
			//space found
			return true;
		}
		if(count == 4999){
			break;
		}
	}
	//space not found
	return false;
}

void * mymalloc(size_t size, char * f, int l){
	int count = 0;
	//initializing the myblock array, will only occur once
	if(!init){
		for(count = 0; count < 5000; count++){
			myblock[count] = '0';
			point[count] = 0;
			psize[count] = 0;
		}
		init = true;
	}
	//check to see if size is greater than size of memory
	if(size > 5000){
		fprintf(stderr, "Size desired is OVER 5000!! "grn"%s: "red"%d\n"reset, f, l);
		// printf("size desired is OVER 5000!!!\n");
		return 0;
	}
	//check to see if you're dumb
	if(size == 0){
		fprintf(stderr, "no... you're dumb "grn"%s: "red"%d\n"reset, f, l);
		return 0;
	}
	//finding openspace to be returned as available memory for malloc
	int openspace = 0;
	for(count = 0; openspace < size; count++){
		if(myblock[count] == '0'){
			openspace++;
		}
		else{
			openspace = 0;
		}
		if(openspace == size){
			break;	//yay your space has been found;
		}
		if(count == 4999){
			fprintf(stderr, "there was not enough memory available "grn"%s: "red"%d\n"reset, f, l);
			return 0;
		}
	}
	// printf("size of openspace %d, count value %d\n", openspace, count);
	//if loop exits and not enough free space
	// if(openspace != size){
	// 	printf("there was not enough memory available\n");
	// 	return 0;
	// }

	//marking the space as used

	int spacestart = count-size+1;
	for(count=spacestart; count<spacestart+size; count++){
		myblock[count] = '1';
	}
	point[spacestart] = &myblock[spacestart];
	psize[spacestart] = size;
	//returning the end woohoo
	void * toReturn = &myblock[spacestart];
	// printf("start point of pointer %d\n", point[5]);
	// printf("number of spaces %d\n", psize[spacestart]);
	// printf("for kicks and giggles %d\n", spacestart);
	// printf("myblock check 300 - %c, and of 200 - %c\n", myblock[300], myblock[299]);
	// printf("congrats scrub\n");
	
	return toReturn;

}

void myfree(void *toFree, char * f, int l){

	//find the index of the pointer
	int index, count;
	if(toFree==0){
		fprintf(stderr, "Already freed or not a pointer "grn"%s: "red"%d\n"reset, f, l);
	}

	for(index=0; index<5000; index++){
		if(point[index] == toFree){
			// printf("address found\n");
			break;
		}
	}
	// printf("index value %d\n", index);
	//if pointer not found
	if(index==5000){
		fprintf(stderr, "Already freed or not a pointer "grn"%s: "red"%d\n"reset, f, l);
	}
	//if the pointer is already freed
	if(myblock[index]=='0'){
		fprintf(stderr, "Already freed or not a pointer "grn"%s: "red"%d\n"reset, f, l);
	}

	//clear the pointer
	for(count=index; count<index+psize[index]; count++){
		myblock[count]='0';
	}
	point[index] = 0;
	psize[index] = 0;
	// int i = 0;
	// for(i = 0; i < 3; i++){
	// 	printf("value at index %s\n", myblock[i]);
	// }
	
 	return;

}

void startover(){
	int count;
	for(count=0; count<5000; count++){
		myblock[count]='0';
	}
}

void memcheck(){
	int i;
	printf("memcheck\n");
	for(i = 0; i<20; i++){
		printf(" %c ", myblock[i]);
	}
	printf("\n\n");
	return;
}
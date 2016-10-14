#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "mymalloc.h"

typedef struct node_{
	struct node * next;
	void * test;
}node;

int main(int argc, char *argv[]){
	/* Test A: 3000 1 byte malloced, then 3000 1 byte freed*/
	int count;
	void * hisam[3000];
	for(count = 0; count < 3000; count++){
		hisam[count] = malloc(1);
	}
	printf("3000 bytes malloced\n");
	memcheck();
	for(count = 0; count < 3000; count++){
		free(hisam[count]);
	}
	printf("3000 bytes freed\n");
	memcheck();


	/*Test B: 3000 malloced and freed immediately 1 bytes*/
	for(count = 0; count < 3000; count++){
		hisam[count] = malloc(1);
		free(hisam[count]);
	}
	printf("3000 bytes malloced and freed\n");
	memcheck();


	/*Test C: Randomly 3000 mallocs and frees*/
	int mallocCount = 0;
	int freeCount = 0;
	int check[3000];
	int ran = 0;
	int location = rand()%3000;
	//initializing array
	for(count = 0; count<3000; count++){
		check[count] = 0;
	}

	while(mallocCount<3000 || freeCount<3000){
		// printf("location %d\n", location);
		ran = rand()%2;
		// printf("rnad: %d\n", ran);
		location = rand()%3000;
		if(mallocCount==freeCount){
			ran=0;
		}
		if(mallocCount==3000){
			ran=1;
		}

		//malloc
		if(ran==0){
			// printf("i made it!\n");
			// printf("check[location] = %d\n", check[location]);
			while(check[location]!=0){
				location = rand()%3000;
				// printf("check[location] = %d\n, location: %d", check[location], location);

			}
			// printf("i left\n");
			hisam[location] = malloc(1);
			mallocCount++;
			check[location]=1;
			// printf("malloc\n");
		}
		//freedom
		else{
			while(check[location]!=1){
				location = rand()%3000;
			}
			free(hisam[location]);
			freeCount++;
			check[location]=0;
			// printf("free\n");
		}	
	}
		printf("value of malloccount: %d, freecount %d\n", mallocCount, freeCount);
}

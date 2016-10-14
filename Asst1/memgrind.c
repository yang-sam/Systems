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
	//test for part a
	int count;
	void * hisam[3000];
	for(count = 0; count < 3000; count++){
		hisam[count] = malloc(1);
	}
	printf("3000 bytes malloced\n");
	for(count = 0; count < 3000; count++){
		free(hisam[count]);
	}
	printf("3000 bytes freed\n");

}
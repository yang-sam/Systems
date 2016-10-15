#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "mymalloc.h"
#include <time.h>

void * hisam[3000];
void resetsam();
void testA();
void testB();
void testC();
void testD();
void testE();
void testF();

int main(int argc, char *argv[]){
	int count;
	struct timeval start, end;
	resetsam();
	
	//testA 100 times
	gettimeofday(&start, NULL);
	for(count=0; count<100; count++){
		resetsam();
		testA();
	}
	gettimeofday(&end, NULL);
	printf("mean time for execution of test A: %f seconds\n", ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000.0))/100);

	//testB 100 times
	gettimeofday(&start, NULL);
	for(count=0; count<100; count++){
		resetsam();
		testB();
	}
	gettimeofday(&end, NULL);
	printf("mean time for execution of test B: %f seconds\n", ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000.0))/100);

	//testC 100 times
	gettimeofday(&start, NULL);
	for(count=0; count<100; count++){
		resetsam();
		testC();
	}
	gettimeofday(&end, NULL);
	printf("mean time for execution of test C: %f seconds\n", ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000.0))/100);

	//testD 100 times
	gettimeofday(&start, NULL);
	for(count=0; count<100; count++){
		resetsam();
		testD();
	}
	gettimeofday(&end, NULL);
	printf("mean time for execution of test D: %f seconds\n", ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000.0))/100);
	
	//testE 100 times
	gettimeofday(&start, NULL);
	for(count=0; count<100; count++){
		resetsam();
		testE();
	}
	gettimeofday(&end, NULL);
	printf("mean time for execution of test E: %f seconds\n", ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000.0))/100);

	//testF 100 times
	gettimeofday(&start, NULL);
	for(count=0; count<100; count++){
		resetsam();
		testF();
	}
	gettimeofday(&end, NULL);
	printf("mean time for execution of test F: %f seconds\n", ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000.0))/100);


}

void resetsam(){
	int count;
	for(count=0; count<3000; count++){
		hisam[count]=0;
	}
	return;
}

/* Test A: 3000 1 byte malloced, then 3000 1 byte freed*/
void testA(){
	startover();
	int count;
	for(count = 0; count < 3000; count++){
		hisam[count] = malloc(1);
	}
	// printf("3000 bytes malloced\n");
	// memcheck();
	for(count = 0; count < 3000; count++){
		free(hisam[count]);
	}
	// printf("3000 bytes freed\n");

}

/*Test B: 3000 malloced and freed immediately 1 bytes*/
void testB(){
	startover();
	int count;
	for(count = 0; count < 3000; count++){
		hisam[count] = malloc(1);
		free(hisam[count]);
	}
	// printf("3000 bytes malloced and freed\n");

}

/*Test C: Randomly 3000 mallocs and frees*/
void testC(){
	startover();
	int count;
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
	// printf("value of malloccount: %d, freecount %d\n", mallocCount, freeCount);

}

/*Test D: Randomly choose between a randomly-sized malloc() or free 6000 times*/
void testD(){
	startover();
	int count;
	int mallocCount = 0;
	int freeCount = 0;
	int check[3000];
	int ran = 0;
	int location = rand()%3000;
	int ranval;
	int sum;
	int size[3000];
	//initializing array
	for(count = 0; count<3000; count++){
		check[count] = 0;
		size[count] = 0;
	}
	//memcheck();
	//startover();
	//memcheck();
	while(mallocCount<3000 || freeCount<3000){
		// printf("location %d\n", location);
		// printf("\n");
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
			//printf("i made it!\n");
			// printf("check[location] = %d\n", check[location]);
			while(check[location]!=0){
				location = rand()%3000;
				// printf("check[location] = %d\n, location: %d", check[location], location);

			}
			// printf("i left\n");
			ranval = rand()%100+1;
			//printf("checkspace: %d\n", checkspace(ranval));
			if(!checkspace(ranval)){
				ran=1;
				//printf("check mallocCount: %d  freeCount: %d\n", mallocCount, freeCount);
			}
			else{
				hisam[location] = malloc(ranval);
				size[location] = ranval;
				sum+=ranval;
				mallocCount++;
				check[location]=1;
			}



			//printf("malloc\n");
		}
		//freedom
		if(ran==1){
			while(check[location]!=1){
				location = rand()%3000;
				//printf("stuck\n");
			}
			free(hisam[location]);
			sum-=size[location];
			freeCount++;
			size[location] = 0;
			check[location] = 0;
			//printf("free\n");
		}
	}
	//printf("value of malloccount: %d, freecount %d\n", mallocCount, freeCount);



}

/*Test E: Free pointers using addition to the address of the beginning of memory*/
void testE(){
	startover();
	int count;
	int counter = -1;
	counter++;
	hisam[counter]=malloc(sizeof(void*));

	while(hisam[counter]!=0 && checkspace(sizeof(void*))){
		counter++;
		hisam[counter]=malloc(sizeof(void*));
		// printf("malloc %d\n", counter);
	}

	// printf("counter: %d\n", counter);

	for(count=sizeof(void*); count/sizeof(void*)<counter; count=count+sizeof(void*)){
		free(hisam[0]+count);
		// printf("free %lu\n", count/sizeof(void*));
	}

}

/*Test E: Test whether the */
void testF(){
	startover();
	int count;
	int outcount;
	for(outcount=0; outcount<100; outcount++){
			for(count=0; count<4; count++){
		hisam[count]=malloc(12);
	}
		free(hisam[1]);
		free(hisam[2]);
		hisam[4]=malloc(20);
		free(hisam[0]);
		free(hisam[3]);
		free(hisam[4]);
	}
	
}

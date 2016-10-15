#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)


void * mymalloc(size_t size, char * f, int l);
void myfree(void *toFree, char * f, int l);
bool checkspace(int size);
void startover();

#endif

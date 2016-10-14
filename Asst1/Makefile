all:
	gcc memgrind.c mymalloc.c -o memgrind
memgrind.o:
	gcc -c memgrind.c
mymalloc.o:
	gcc -c mymalloc.c mymalloc.h

clean:
	rm memgrind 

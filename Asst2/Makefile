all:
	gcc compressT_LOLS.c -pthread -o compressT_LOLS
	gcc compressR_LOLS.c -o compressR_LOLS
	gcc compressR_worker_LOLS.c -o compressR_worker_LOLS
	
compressT_LOLS.o:
	gcc -pthread -c compressT_LOLS.c

compressR_LOLS.o:
	gcc -c compressR_LOLS.c

compressR_worker_LOLS.o:
	gcc -c compressR_worker_LOLS.c

clean:
	rm compressT_LOLS
	rm compressR_LOLS
	rm compressR_worker_LOLS
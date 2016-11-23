//project documentation
//Christie Chang cc1173
//Samuel Yang sy369

Makefile
This compiles the program by using the "make" command. To clear the executables, use the command "make clean"

compressT_LOLS.c
main()
The main method takes in the file input and the number of parts. Error checking on the file checks that the file exists, has read access, and whether a compressed file already exists (sends error message and then overwrites the file). After the file is fine, the string is extracted from the file. The string is then split into the indicated number of parts and a thread is created to process each string segment. Each thread is joined to the main method so that the program doesn't complete before the threads are all done processing.

compress_substr()
This method is what the threads execute to compress the strings. It skips over every non-alphabetical character and writes the compressed number and character to a new file. If there are only one or two characters of the same type, then they are outputted normally and not compressed.



compressR_LOLS.c
main()
The main method takes in the file input and the number of parts. Error checking on the file checks that the file exists, has read access, and whether a compressed file already exists (sends error message and then overwrites the file). After the file is fine, the string is extracted from the file. The string is then split into the indicated number of parts and the process is forked each time to create a child process to process each string segment. The parent process waits for the child process to finish so that all children processes are completed before the program ends.



compressR_worker_LOLS.c
main()
This main method is what the children processes execute to compress the strings. It skips over every non-alphabetical character and writes the compressed number and character to a new file. If there are only one or two characters of the same type, then they are outputted normally and not compressed.



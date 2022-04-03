#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd_line_parser.h"
void printIntegers(long int arr[], size_t size)
{
    for (size_t i = 0; i < size; i++){
        printf("%ld", arr[i]);
        if(i<size-1)
        	printf(" - ");
    }

    printf("\n");
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./%s int1 int2 int3...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
 
   	long int arrOut[argc-1];
	cmdLineIntegerParser2(argc,argv,arrOut);
    printIntegers(arrOut, argc - 1);
    exit(EXIT_SUCCESS);
}
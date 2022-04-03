#include "cmd_line_parser.h"

int cmdLineIntegerParser(int argc, char* argv[],long int* arrOut){
    for (int i = 0; i < argc-1; ++i) {
        arrOut[i] = strtol(argv[i+1], NULL, 10);
    }
    return 0;
}

//robust version
int cmdLineIntegerParser2(int argc, char* argv[],long int* arrOut){
    for (int i = 0; i < argc-1; ++i) {
        long int num;
	    char *endptr, *str = argv[i+1];
	    errno = 0;
	    long ret = strtol(str, &endptr, 10);
	    if (str == endptr) {
	        fprintf(stderr, "%s: not a decimal number\n", str);
	        exit(1);
	    } else if ('\0' != *endptr) {
	        fprintf(stderr, "%s: extra characters at end of input: %s\n", str, endptr);
	        exit(1);
	    } else if ((LONG_MIN == ret || LONG_MAX == ret) && ERANGE == errno) {
	        fprintf(stderr, "%s out of range of type long\n", str);
	        exit(1);
	    } else if (errno != 0 && ret == 0) {
	        fprintf(stderr, "%s no conversion was performed\n", str);
	        exit(1);
	    } else {
	        arrOut[i] = ret;
	        //printf("num: %ld\n", num);
	    }
    }
    return 0;
}
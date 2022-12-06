#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT "input.txt"

#define BV(x) ( 1 << x)
#define MESSAGE 14 //14


int count(char* a, size_t len){
	unsigned int map = 0, set_bit;
	for (int i = 0; i < len; ++i) {
		set_bit = BV((a[i]-96));
		if(map & set_bit) return 1;
		map |= set_bit;
	}
	return 0;
}

int process(char* stream, size_t len){
	char buf[MESSAGE+1] = {0};
	for (int i = 0; i < len; ++i) {
		/* code */
		buf[i%MESSAGE] = stream[i];
		if(i > MESSAGE-1 && !count(buf,MESSAGE)){
			printf("Found buf: %s\n", buf);
			return i+1;
		}
	}
	return -1;
}

int main(){
	FILE * fp;
    char * line = NULL;
    size_t len = 0, result;
    ssize_t read;
    char buf[8] = {0}; 

    fp = fopen(INPUT, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    //would make more sense to process this byte by byte and remove process alogether
    while ((read = getline(&line, &len, fp)) != -1) {
    	printf("(%d) %s\n", read, line);
    	result = process(line,read);
    	printf("Solution: %zu\n", result);

    }


    fclose(fp);
    if (line)
        free(line);

}

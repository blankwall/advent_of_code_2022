#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT "input.txt"

char* get_token(size_t clock_cycle, int x){
	return clock_cycle%40 == x || clock_cycle%40 == x+1 ||
						clock_cycle%40 == x-1 ? "#" : "." ;	
}

size_t inc_clock(){
	static size_t clock_cycle;
	clock_cycle++;
	if(clock_cycle%40 == 0) printf("\n");
	return clock_cycle;
}

int process_instruction(char* instruction, int* xreg){
	static size_t clock_cycle,offset,x=1;
	
	
	printf("%s",get_token(clock_cycle,x));


	if(!strcmp(instruction, "noop")){
		clock_cycle = inc_clock();
	} else {
		clock_cycle = inc_clock();	
		printf("%s",get_token(clock_cycle,x));
		x += atoi(strchr(instruction, ' ')+1);
		clock_cycle = inc_clock();
	}

	*xreg = x;
	return clock_cycle;
}


int main(){
	FILE * fp;
    char * line = NULL, *hold;
    size_t len = 0, result;
    int xreg, prev_reg;
    ssize_t read;
    char buf[8] = {0}; 
    char* current = NULL;
    fp = fopen(INPUT, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    size_t cycle, target=20,sum=0;


    while ((read = getline(&line, &len, fp)) != -1) {
    	line[read-1] = 0;
    	cycle = process_instruction(line, &xreg);
    }

    fclose(fp);
    if (line)
        free(line);

}

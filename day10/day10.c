#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT "test.txt"

int process_instruction(char* instruction, int* xreg){
	static int x = 1, to_add;
	static size_t clock_cycle;
	char* space;

	if(!strcmp(instruction, "noop")){
		clock_cycle++;
	} else {
		x += atoi(strchr(instruction, ' ')+1);
		clock_cycle += 2;
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
    	prev_reg = xreg;
    	cycle = process_instruction(line, &xreg);
    	if(cycle >= target){
    		// printf("%d xreg %d ", xreg,prev_reg);
    		// xreg = cycle == target ? xreg : prev_reg;
    		printf("Cycle (%zu) %d\n",cycle, prev_reg);
    		sum += (target * prev_reg);
    		target += 40;
    	}
    	// printf("%s\n", line);

    }

    printf("%zu\n", sum);
    fclose(fp);
    if (line)
        free(line);

}

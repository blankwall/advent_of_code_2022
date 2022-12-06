#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

#define INPUT "input.txt"

#define MULTIPLE 4

size_t elements = 0;

char** create_buff(size_t len){
	elements = len/MULTIPLE; //4 spaces for each element

	char** ret = calloc(elements,sizeof(char*));
	for (int i = 0; i < elements; ++i)
	{
		ret[i] = calloc(1, SIZE);
	}
	return ret;

}

void parse_line(char** t, char* line, size_t len){
	size_t char_index = -1;
	char buf[2] = {0};

	for(int i =0 ; i < len; ++i){
		if(i%4 == 0) char_index++;

		if(isalpha(line[i])){
			buf[0] = line[i];
			strcat(t[char_index], buf);
		}

	}

}

int* extract_digits(char* str){
	size_t len = strlen(str);
	char buf[3] = {0};
	int* ret = calloc(3,sizeof(int));
	int* cur = ret;

	for(int i=0; i <len; ++i){
		if(isdigit(str[i])){
			buf[0] = str[i];
			if(i+1 < len)
				buf[1] = isdigit(str[i+1]) ? str[++i] : 0 ;
			*cur++ = atoi(buf);
		}
		memset(buf,0,3);
	}
	return ret;
}


int main(){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    ssize_t f=0;
    // range* input;
    char** input_hold=NULL, val;
    stack** stacks;
    int* proc, quan, stackfrom,stackto;

    fp = fopen(INPUT, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char begin = 1;

    while ((read = getline(&line, &len, fp)) != -1) {
    	if(read == 1 && begin) {
    		printf("Creating stacks\n");
    		begin = 0;
    		stacks = calloc(elements, sizeof(stack*));
    		for (int i = 0; i < elements; ++i) {
    			stacks[i] = stack_load(input_hold[i]);
    		}

    	}
	    
	    line[read] = 0; // remove the new line
	    if(read == 1) continue;

    	if(begin){
	    	if(!input_hold) {
	    		input_hold = create_buff(read);
	    	}
	    	parse_line(input_hold, line, len);
	    } else {
	    	proc = extract_digits(line);
	    	quan = proc[0];
	    	stackfrom = proc[1]-1;
	    	stackto = proc[2]-1 ;
	    	for (int i = 0; i < quan; ++i) {
	    		val = pop(stacks[stackfrom]);
	    		push(stacks[stackto], val);

	    	}
	    }
    }

    char* result = calloc(2, elements);
    char* opt = result;

    for (int i = 0; i < elements; ++i) {
    	printstack(stacks[i]);
    	*opt++ = pop(stacks[i]);

    }
    printf("Solution: %s\n", result);

    fclose(fp);
    if (line)
        free(line);

}

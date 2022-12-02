#include <stdlib.h>
#include <stdio.h>

int main(){

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    ssize_t max_cals1 = 0;
    ssize_t max_cals2 = 0;
    ssize_t max_cals3 = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    ssize_t current_elf = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
    	line[read] = 0;
    	if(read == 1) {
    		if(current_elf > max_cals1){
    			max_cals1 = current_elf;
    		} else  if(current_elf > max_cals2){
    			max_cals2 = current_elf;
    		} else if(current_elf > max_cals3){
    			max_cals3 = current_elf;
    		}
    		current_elf = 0;
    		continue;
    	}
    	ssize_t f;
    	sscanf(line, "%zd",&f);
        current_elf += f;
    }

    fclose(fp);
    if (line)
        free(line);

    // printf("Max: %zd\n", max_cals1+max_cals2+max_cals3);
    exit(EXIT_SUCCESS);

}

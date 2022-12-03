#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT "input.txt"

int is_in(char* a, char* b, int lenb){
	for (int i = 0; i < strlen(a); ++i) {
		for (int j = 0; j < lenb; ++j){
			if(b[j] == a[i]) {
				return b[j];
			}
		}
	}
}


size_t calculate_sack(char** a){

	size_t result;
	char map[128] = {0}, myfound;
	char* part1 = a[0];
	char* part2 = a[1];
	char* part3 = a[2];
	char found[128];
	int found_index;

	for (int i = 0; i < strlen(part1); ++i) {
		map[part1[i]] = 'a';
	}

	for (int i = 0; i < strlen(part2); ++i) {
		if(map[part2[i]] == 'a'){
			found[found_index++] = part2[i];
		}
	}

	myfound = is_in(part3, found, found_index);
	return (tolower(myfound)-96) + (isupper(myfound) ? 26 : 0);;
}


int main(){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    ssize_t f=0;
    char** buf3 = calloc(3,sizeof(char*));
    for (int i = 0; i < 3; ++i)
    {
    	buf3[i] = calloc(1, 4096);
    }
    size_t index = 0;

    fp = fopen(INPUT, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	line[read] = 0; // remove the new line
    	sscanf(line, "%s",buf3[index++]);
    	if(index == 3){
    		f += calculate_sack(buf3);
    		index = 0;
    	}
    }

    printf("result: %zu\n", f);
    fclose(fp);
    if (line)
        free(line);

}

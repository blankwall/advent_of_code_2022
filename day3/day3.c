#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT "input.txt"



size_t calculate_sack(char* a){
	size_t len = strlen(a);
	char* part1 = calloc(1, len), found;
	char* part2 = calloc(1, len);
	char map[128] = {0};

	strncpy(part1, a, len/2);
	strncpy(part2, a+len/2, len/2);

	for (int i = 0; i < len/2; ++i) map[part1[i]] = 'a';
	
	for (int i = 0; i < len/2; ++i) {
		if(map[part2[i]] == 'a'){
			found = part2[i];
			break;
		}
	}

	return (tolower(found)-96) + (isupper(found) ? 26 : 0);;
}


int main(){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    ssize_t f=0;
    char* buf = calloc(1,4096);

    fp = fopen(INPUT, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	line[read] = 0; // remove the new line
    	sscanf(line, "%s",buf);
    	f += calculate_sack(buf);
    }

    printf("result: %zu\n", f);
    fclose(fp);
    if (line)
        free(line);

}

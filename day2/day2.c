#include <stdlib.h>
#include <stdio.h>

#define INPUT "input.txt"

size_t convert(char a){
	if(a < 68){
		return (size_t) a-64;
	} else{
		return (size_t) a-87;
	}
}

size_t play_round(char a, char b){
	switch(a) {
		case 1:
			if(b == 1) return 3;
			else if(b == 2) return 6;
			else if (b == 3) return 0;
			break;
		case 2:
			if(b == 1) return 0;
			else if(b == 2) return 3;
			else if (b == 3) return 6;
			break;
		case 3:
			if(b == 1) return 6;
			else if(b == 2) return 0;
			else if (b == 3) return 3;
			break;
	}
}

size_t calculate_round(char a, char b){
	static size_t overall_score;
	size_t elf = convert(a);
	size_t me = convert(b);

	overall_score += play_round(elf,me)+me;
	return overall_score;
}


int main(){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    ssize_t f;
    char buf[2];

    fp = fopen(INPUT, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
    	line[read] = 0; // remove the new line
    	sscanf(line, "%c %c",&buf[0], &buf[1]);
    	f = calculate_round(buf[0], buf[1]);
    }

    printf("result: %zu\n", f);
    fclose(fp);
    if (line)
        free(line);

}

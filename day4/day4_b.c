#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT "input.txt"

typedef struct range {
    unsigned char lower;
    unsigned char upper;
}range;

int contained(range* r1, range* r2){
    return (r1->lower <= r2->lower) &&  (r1->upper >= r2->lower) ||
        (r2->lower <= r1->lower) &&  (r2->upper >= r1->lower);
}

range* extract_range(char* data, int first){
    range* result = calloc(2, sizeof(range));
    char* occurence = strchr(data, ',');
    *occurence++ = 0;

    sscanf(data, "%d-%d", &result[0].lower, &result[0].upper);
    sscanf(occurence, "%d-%d", &result[1].lower, &result[1].upper);
    return result;
}

int main(){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    ssize_t f=0;
    range* input;

    fp = fopen(INPUT, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        line[read] = 0; // remove the new line
        input = extract_range(line,1);
        f += contained(&input[0], &input[1]);
        free(input);
    }

    printf("result: %zu\n", f);
    fclose(fp);
    if (line)
        free(line);

}

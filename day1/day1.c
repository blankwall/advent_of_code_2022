#include <stdlib.h>
#include <stdio.h>

struct int_array {
	size_t* items;
	size_t len;
	size_t max;
};

#define MAX_SIZE 4096

typedef struct int_array vint;

vint* nvint(size_t size){
	if(size > MAX_SIZE) size = MAX_SIZE;
	vint* tmp = calloc(1, sizeof(vint));
	tmp->items = calloc(size, sizeof(size_t));
	tmp->max = size;
	return tmp;
}

vint* vsum(vint* it){
	size_t sum = 0;
	for (int i = 0; i < it->len; ++i)
    	sum += it->items[i];
   	return sum;
}

void add_vint(vint* root, size_t val){
	if(root->len + 1 >= root->max){
		printf("Size error");
		exit(-1);
	}
	root->items[root->len++] = val;
}

void print_vint(vint* myv){
	for (int i = 0; i < myv->len; ++i) {
		printf("%d\n", myv->items[i]);
	}
}

int maxelf(vint** calories, size_t entries, size_t* avoid){
	size_t maxsum = 0, nsum, seen;
	for(int i = 0; i < entries; ++i){
		seen = 0;
		nsum = vsum(calories[i]);
		for (int l = 0; l < 3; ++l) if(nsum == avoid[l]) seen = 1;
		if(!seen) maxsum = nsum > maxsum ? nsum : maxsum;
	}
	return maxsum;
}

int main(){
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    ssize_t f;

    fp = fopen("input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // ssize_t current_elf = 0;
    vint* current_elf = nvint(MAX_SIZE);
    vint** elves = calloc(4096, sizeof(vint*)); //holds 4096 ptrs
    vint** ptr = elves; 

    while ((read = getline(&line, &len, fp)) != -1) {
    	line[read] = 0;
    	if(read == 1) {
    		// printf("Next elf current len: %d\n", current_elf->len);
    		*ptr = current_elf;
    		ptr++;
    		current_elf = nvint(MAX_SIZE);
    		continue;
    	}
    	sscanf(line, "%zd",&f);
        add_vint(current_elf, f);
    }

    fclose(fp);
    if (line)
        free(line);

    size_t* avoidel = calloc(3, sizeof(size_t));

    avoidel[0] = maxelf(elves,ptr-elves, avoidel);
    avoidel[1] = maxelf(elves,ptr-elves, avoidel);
    avoidel[2] = maxelf(elves,ptr-elves, avoidel);
    printf("%d\n", avoidel[0]);
    printf("%d\n", avoidel[1]);
    printf("%d\n", avoidel[2]);
    printf("Result: %d", avoidel[0]+avoidel[1]+avoidel[2]);


}

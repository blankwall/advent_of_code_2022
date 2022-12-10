#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT "input.txt"

typedef struct grid { 
	int** grid;
	size_t gridlen;
	size_t row_len;
}grid;

grid* mygrid;


void make_grid(){
	mygrid = calloc(1,sizeof(grid));
	mygrid->grid = calloc(4096, sizeof(int*));
}
void add_grid(char* data, size_t len){
	int* new_row = calloc(len, sizeof(int));
	int* row_walk = new_row;

	for (int i = 0; i < len; ++i) 
		*row_walk++ = data[i] - 0x30;
	
	mygrid->grid[mygrid->gridlen++] = new_row;
	mygrid->row_len = len;
}
void print_grid(){
	for (int i = 0; i < mygrid->gridlen; ++i)
	{
		for (int j= 0; j < mygrid->gridlen; ++j){
			printf("%d ", mygrid->grid[i][j]);
		}
		printf("\n");
		/* code */
	}
}

int can_see(int row, int col){
	//FROM TOP
	//FROM BOTTOM
	//FROM LEFT
	//FROM RIGHT

	int top = row;
	int current_val = mygrid->grid[row][col];
	int can_see = 0, sum=1;

	while(top-- > 0){
		can_see++;
		if(mygrid->grid[top][col] >= current_val) {
			break;
		}
	}

	sum *= can_see;
	can_see = 0;

	// if(can_see) return can_see;

	top = row; 
	while(++top < mygrid->gridlen){
		can_see++;
		if(mygrid->grid[top][col] >= current_val) {
			break;
		}
	}

	sum *= can_see;
	can_see = 0;
	// if(can_see) return can_see;


	top = col; 
	while(++top < mygrid->row_len){
		can_see++;
		if(mygrid->grid[row][top] >= current_val) {
			break;
		}
	}

	sum *= can_see;
	can_see = 0;
	// if(can_see) return can_see;

	top = col; 
	while(top-- > 0){
		can_see++;
		if(mygrid->grid[row][top] >= current_val) {
			break;
		}
	}

	sum *= can_see;
	can_see = 0;

	return sum;
}

size_t process_grid(){
	size_t total_trees = 0, var;

	for (int i = 1; i < mygrid->gridlen-1; ++i) {
		for (int j= 1; j < mygrid->gridlen-1; ++j){
			if((var = can_see(i,j)) > total_trees)
				total_trees = var;
		}
		// printf("\n");
		/* code */
	}
	printf("%zu\n", total_trees);
	return total_trees;
}



int main(){
	FILE * fp;
    char * line = NULL, *hold;
    size_t len = 0, result;
    ssize_t read;
    char buf[8] = {0}; 
    char* current = NULL;
    fp = fopen(INPUT, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    make_grid();

    while ((read = getline(&line, &len, fp)) != -1) {
    	line[read-1] = 0;
    	add_grid(line,read-1);
        // printf("(%zd) %s %zd\n", read, line, mygrid->row_len);

    }
    // print_grid();
    printf("%zd %zd\n", mygrid->gridlen, mygrid->row_len);
    printf("%d %d \n", mygrid->grid[1][2], can_see(1,2));
    process_grid();

    fclose(fp);
    if (line)
        free(line);

}

#include "stack.h"

void push(stack* st, unsigned char val){
	if(st->top+1 >= SIZE ){
		printf("Stack FULL\n");
		return;
	}
	st->buf[st->top++] = val;
}
unsigned char pop(stack* st){
	if(!st->top) return 0;
	return st->buf[--st->top];

}

stack* stack_load(char* data){
	size_t len = strlen(data);
	stack* st = calloc(1, sizeof(stack));

	for (int i = len; i >= 0; --i)
	{
		push(st, data[i]);
	}
	return st;
}

void printstack(stack* st){

	for (int i = st->top-1; i > 0; --i)
	{
		if(i == st->top-1) printf("TOP -> ");
		printf("%c ", st->buf[i]);
	}
	printf(" <- BOTTOM \n");
}

// int  main(int argc, char const *argv[])
// {
// 	stack* i = load("IHGFEDCBA");
// 	printstack(i);
// }
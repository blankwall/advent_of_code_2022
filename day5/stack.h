#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 128

typedef struct stack{
	unsigned char buf[SIZE];
	unsigned char top;
}stack;

void push(stack*, unsigned char);
unsigned char pop(stack*);
void printstack(stack*);
stack* stack_load(char* data);

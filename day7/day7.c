#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT "input.txt"

#define SIZE 128
#define MAX 100000

typedef struct Filenode {
    unsigned int size;
    char* name;
    struct Filenode* next[SIZE];
    struct Filenode* parent;
    unsigned int len;
    size_t dir_size;
 } Filenode;

char* directories[4096];
char dir_walk = 0;
size_t total_size;
 
// A 
// 	-> B  -> d.txt 
// 	-> C 
// 	-> D  -> e.txt 
// 	-> a.txt 
// 	-> b.txt

// A

 // IMPLEMENT CD and finish challenge :thunbs up:


 Filenode* root_node;
 Filenode* current_node;

 char* process_input[4096];
 size_t p_len;

 Filenode* create_node(char* name, size_t size, Filenode* prnt){
 	Filenode* tmp = calloc(1, sizeof(Filenode));
 	// printf("Creating: %s\n", name);
 	tmp->name = strdup(name);
 	tmp->size = size;
 	tmp->parent = prnt;
 	return tmp;
 }

 void add_node(Filenode* rnode, Filenode* to_add){
 	if(!rnode) rnode = to_add;

 	rnode->next[rnode->len++] = to_add;
 }


 Filenode* is_node_in(Filenode* rnode, char* name){
 	static Filenode* found = NULL;

 	Filenode* walk = root_node;


 	if(!rnode ) {
 		found = NULL;
 		return 0;
 	}

 	if(found) return found;

 	if(!rnode->name) return 0;

 	//Is it the root directory?
	if(!strcmp(rnode->name, name)){
		found = rnode;
		return rnode;
	}

	for (int i = 0; i < rnode->len; ++i) {
		/* code */
		// printf("Comparing: %s %s\n",rnode->next[i]->name, name);
		if(!strcmp(rnode->next[i]->name, name)){
			// printf("Found me!\n");
			found = rnode->next[i];
			return rnode->next[i];
		}
		else if(rnode->next[i]->size == 0){
			// printf("recursing: %s\n", rnode->next[i]->name);
			is_node_in(rnode->next[i], name);
		}
	}

	return found;
	//otherwise for each new directory, recursively call as if you were the root
	//check files here;
 }

 void print_filenode(Filenode* rnode, char* tabs){
 	if(!rnode) return;
 	char* tmp = strdup(tabs);

 	printf("%s %s\n", tabs, rnode->name);

 	strcat(tmp, "   ");

 	for (int i = 0; i < rnode->len; ++i) {
		/* code */
		if(rnode->next[i]->size == 0){
			print_filenode(rnode->next[i], tmp);
		} else {
			printf("%s %s (%zu)\n", tmp, rnode->next[i]->name, rnode->next[i]->size);
		}
	}
 }

 Filenode* get_node(Filenode* rnode, char* name){
 	Filenode* tmp = is_node_in(rnode, name);
 	is_node_in(0,0);
 	return tmp;
 }

 void add_input(char* in){
 	process_input[p_len++] = strdup(in);
 }

 void process_ls(){
 	Filenode* r;
 	char* size, *name;
 	size_t sz;
 	for (int i = 0; i < p_len; ++i)
 	{	
 		size = process_input[i];
 		name = strchr(size, ' ');
 		*name = 0;
 		name++;
 		sz = atoi(size);

 		if(!sz && (r = get_node(current_node, name))){
 			printf("", r);
 		} else {
 			sz = !strcmp(size, "dir") ? 0 : atoi(size);
 			r = create_node(name,sz, current_node);
 			add_node(current_node, r);
 		}
 		free(process_input[i]);
 		process_input[i] = NULL;
 	}
 	p_len = 0;
 }

size_t get_directory_size(Filenode* rnode){
	size_t cur = 0;
	if(!rnode) return 0;
 	// printf("%s\n" , rnode->name);

 	if(rnode->dir_size) return rnode->dir_size;

 	for (int i = 0; i < rnode->len; ++i) {
		/* code */
		if(rnode->next[i]->size == 0){
			 cur += rnode->next[i]->dir_size ? rnode->next[i]->dir_size : get_directory_size(rnode->next[i]);
		} else {
			cur += rnode->next[i]->size;
		}
	}
	rnode->dir_size = cur;
	return cur;
}

void collect_dirs(Filenode* rnode, size_t a, int* b){
	if(!rnode) return;

 	if(get_directory_size(rnode)){
 		total_size += rnode->dir_size;
 		if(a && rnode->dir_size >= a){
 			// printf("%zd -- %zd %d\n", rnode->dir_size, a, rnode->dir_size >= a);
 			if(rnode->dir_size < *b) *b = rnode->dir_size;
 			// directories[dir_walk++] = strdup(rnode->name);
 		}
 	}
 	for (int i = 0; i < rnode->len; ++i) {
		if(rnode->next[i]->size == 0){
			 collect_dirs(rnode->next[i],a,b);
		}
	}
}


int main(){
	FILE * fp;
	Filenode* var;
    char * line = NULL, *hold;
    size_t len = 0, result;
    ssize_t read;
    char buf[8] = {0}; 
    char* current = NULL;
    fp = fopen(INPUT, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    root_node = create_node("/", 0,0); //directories have a 0 size; 
    // Filenode* a = create_node("b.txt", 1234), *b;
    // add_node(root_node,a);
    // a = create_node("a", 0);
    // add_node(root_node,a);
    // b = create_node("b", 0);
    // add_node(a,b);

    // printf("%p\n", is_node_in(root_node, "b"));
    // exit(1);

    current_node = root_node;

    while ((read = getline(&line, &len, fp)) != -1) {
    	line[read-1] = 0;
    	if(line[0] == '$'){
    		if(p_len && !strcmp(current, "ls")){
    			process_ls();
    		}
	     	if((hold =strstr(line, "cd"))){
	     		var=get_node(current_node, hold+3);
	     		// printf("CD %s %p\n", hold+3, var=get_node(current_node, hold+3));
	     		hold += 3;
	     		if(!strcmp(hold, "..")){
	     			current_node = current_node->parent;
	     		}
	     		else if((var)) current_node = var;
	     		// printf("After cd current_dir = %s\n", current_node->name);
	     		current = "cd";

	     	} else if((hold =strstr(line, "ls"))){
	     		// printf("LS command --> ");
	     		current = "ls";
	     	}
	     } else {
	     	add_input(line);
	     }
        // printf("(%zd) %s\n", read, line);

    }

    char tabs[4096] = {0};

    // Filenode* e = get_node(root_node, "a");

    // printf("%d\n",get_directory_size(e));
	// print_filenode(root_node,tabs);

	collect_dirs(root_node,0, &len);
	// printf("%d\n", root_node->dir_size);

	size_t max_space = 70000000;
	size_t min_space = 30000000;
	size_t unused = max_space - root_node->dir_size;
	size_t min_dir =  min_space-unused;

	collect_dirs(root_node, min_dir, &min_space);
	printf("\nMin size: %zd\n", min_dir);


	printf("Min dir %zd\n", min_space);
    fclose(fp);
    if (line)
        free(line);

}

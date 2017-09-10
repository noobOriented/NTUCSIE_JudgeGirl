#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct node {
	char c;
	struct node *next, *prev;
} Node;

typedef struct list{
	Node *head, *tail;
	int length;
} List;

void initList(List *str) {
	str->head = NULL;
	str->tail = NULL;
	str->length = 0;
}

void insert_left(List *str, char c) {
	str->length++;
    Node *new = (Node*)malloc(sizeof(Node));
    assert(new != NULL);
    new->c = c;
    new->prev = NULL;
    if(str->head == NULL) {
    	new->next = NULL;
    	str->head = new;
    	str->tail = new;
    }else{
	    new->next = str->head;
	    str->head->prev = new;
	    str->head = new;
    }
}

void insert_right(List *str, char c) {
	str->length++;
    Node *new = (Node*)malloc(sizeof(Node));
    assert(new != NULL);
    new->c = c;
    new->next = NULL;
    if(str->head == NULL){
    	new->prev = NULL;
    	str->head = new;
    	str->tail = new;
    }else{
    	new->prev = str->tail;
    	str->tail->next = new;
    	str->tail = new;
    }
}

void insert(List *str, int n, char c) {
	if(n == 1){
		insert_left(str, c);
		return;
	}
	if(n > str->length){
		insert_right(str, c);
		return;
	}
	str->length++;
	Node *current = str->head;
	for(int i = 0; i < n-2; ++i){
		current = current->next;
	}
    Node *new = (Node*)malloc(sizeof(Node));
    assert(new != NULL);
    new->c = c;
    new->next = current->next;
    new->prev = current;
    current->next = new;
    new->next->prev = new;
}

void delete_left(List *str) {
	str->length--;
	Node *tmp = str->head;
	if(str->head->next == NULL){
		str->head = NULL;
		str->tail = NULL;
	}else{
		str->head = str->head->next;
		str->head->prev = NULL;
	}
	free(tmp);
	tmp = NULL;
}

void delete_right(List *str) {
	str->length--;
	Node *tmp = str->tail;
	if(str->tail->prev == NULL){
		str->head = NULL;
		str->tail = NULL;
	}else{
		str->tail = str->tail->prev;
		str->tail->next = NULL;
	}
	free(tmp);
	tmp = NULL;
}

void delete(List *str, int n) {
	if(n == 1){
		delete_left(str);
		return;
	}
	if(n >= str->length){
		delete_right(str);
		return;
	}
	str->length--;
	Node *current = str->head;
	for(int i = 0; i < n - 1; ++i) {
		current = current->next;
	}
	current->prev->next = current->next;
	current->next->prev = current->prev;
	free(current);
	current = NULL;
}

void printList(List *str){
	Node *current = str->head;
	while(current != NULL) {
		printf("%c ", current->c);
		current = current->next;
	}
}

void printLongestSequence(List *str){
	if(str->head == NULL){
		printf("0");
		return;
	}
	int i = 0, max = 0;
	Node *current = str->head;
	char c = current->c;
	while(current != NULL){
		if(current->c == c){
			i++;
			if(i > max)
				max = i;
		}else{
			i = 1;
			c = current->c;
		}
		current = current->next;
	}
	if(max == 1){
		printList(str);
		printf("1");
		return;
	}
	i = 0;
	current = str->head;
	c = current->c;
	while(current != NULL){
		if(current->c == c){
			i++;
			if(i == max){
				printf("%c ", c);
			}
		}else{
			i = 1;
			c = current->c;
		}
		current = current->next;
	}
	printf("%d", max);
}

int main() {
	List str;
	char c, command[7], pos[6];
	initList(&str);
	while(scanf("%s ", command) != EOF) {
		scanf("%s ", pos);
		if(command[0] == 'i'){
			scanf("%c", &c);
			if(pos[0] == 'l')
				insert_left(&str, c);
			else if(pos[0] == 'r')
				insert_right(&str, c);
			else
				insert(&str, atoi(pos), c);
		}else{
			if(pos[0] == 'l')
				delete_left(&str);
			else if(pos[0] == 'r')
				delete_right(&str);
			else
				delete(&str, atoi(pos));
		}
	}
	printLongestSequence(&str);
	return 0;
}
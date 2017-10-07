#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef struct comm {
/*  0: GOTO
	10~15: IF (==, !=, >, <, >=, <=)
	20~24: ASSIGNMENT (+, -, *, /, %)
	30: PRINT
	40: STOP
	*/
	int type;
	// index of variable or line to goto
	int x, y, z;
} Command;



int n_var = 0, line = 1, n_line = 0, stop = 0;;
char name_var[100][8];
int value_var[100];
char inputStr[8];
Command *command[1000];

int find_var_index(){
	for(int i = 0; i < n_var; ++i){
		if(!strcmp(inputStr, name_var[i]))
			return i;
	}
	return -1;
}

Command* build_GOTO(){
	Command *c = (Command*) malloc(sizeof(Command));
	assert(c != NULL);
	c->type = 0;
	scanf("%d", &(c->x));
	return c;
}

Command* build_IF(){
	Command *c = (Command*) malloc(sizeof(Command));
	assert(c != NULL);
	scanf("%s ", inputStr);
	c->x = find_var_index();
	scanf("%s ", inputStr);
	if(inputStr[0] == '=')
		c->type = 10;
	else if(inputStr[0] == '!')
		c->type = 11;
	else if(inputStr[0] == '>'){
		if(inputStr[1] == '=')
			c->type = 14;
		else
			c->type = 12;
	}
	else if(inputStr[0] == '<'){
		if(inputStr[1] == '=')
			c->type = 15;
		else
			c->type = 13;
	}
	scanf("%s ", inputStr);
	c->y = find_var_index();
	scanf("%s ", inputStr);
	scanf("%d", &(c->z));
	return c;
}

Command* build_ASSIGNMENT(){
	Command *c = (Command*) malloc(sizeof(Command));
	assert(c != NULL);
	c->x = find_var_index(inputStr);
	scanf("%s ", inputStr);
	scanf("%s ", inputStr);
	c->y = find_var_index();
	scanf("%s ", inputStr);
	if(inputStr[0] == '+')
		c->type = 20;
	else if(inputStr[0] == '-')
		c->type = 21;
	else if(inputStr[0] == '*')
		c->type = 22;
	else if(inputStr[0] == '/')
		c->type = 23;
	else
		c->type = 24;
	scanf("%s", inputStr);
	c->z = find_var_index();
	return c;
}

Command* build_PRINT(){
	Command *c = (Command*) malloc(sizeof(Command));
	assert(c != NULL);
	c->type = 30;
	scanf("%s", inputStr);
	c->x = find_var_index();
	return c;
}

Command* build_STOP(){
	Command *c = (Command*) malloc(sizeof(Command));
	assert(c != NULL);
	c->type = 40;
	return c;
}

void do_GOTO(Command *c) {
	line = c->x;
}

void do_IF(Command *c) {
	int flag = 0, a = value_var[c->x], b = value_var[c->y];
	switch(c->type){
		case 10:
			flag = (a == b);
			break;
		case 11:
			flag = (a != b);
			break;
		case 12:
			flag = (a > b);
			break;
		case 13:
			flag = (a < b);
			break;
		case 14:
			flag = (a >= b);
			break;
		case 15:
			flag = (a <= b);
			break;
	}
	if(flag)
		line = c->z;
	else
		line++;
}

void do_ASSIGNMENT(Command *c) {
	int a = value_var[c->y], b = value_var[c->z];
	switch(c->type){
		case 20:
			value_var[c->x] = a + b;
			break;
		case 21:
			value_var[c->x] = a - b;
			break;
		case 22:
			value_var[c->x] = a * b;
			break;
		case 23:
			value_var[c->x] = a / b;
			break;
		case 24:
			value_var[c->x] = a % b;
			break;
	}
	line++;
}

void do_PRINT(Command *c) {
	printf("%d\n", value_var[c->x]);
	line++;
}

void do_STOP() {
	stop = 1;
}

void do_command(Command *c){
	int type = c->type;
	if(type == 0)
		do_GOTO(c);
	else if(type < 20)
		do_IF(c);
	else if(type < 30)
		do_ASSIGNMENT(c);
	else if(type == 30)
		do_PRINT(c);
	else
		do_STOP();
}

int main() {
	// scan variable value
	while(1){
		scanf("%s ", inputStr);
		if(!strcmp("END", inputStr))
			break;
		strcpy(name_var[n_var], inputStr);
		scanf("%s ", inputStr);
		scanf("%d ", &value_var[n_var]);
		n_var++;
	}
	// build command list
	while(scanf("%s ", inputStr) != EOF){
		if(!strcmp("GOTO", inputStr)) {
			command[n_line] = build_GOTO();
		}
		else if(!strcmp("IF", inputStr)) {
			command[n_line] = build_IF();
		}
		else if(!strcmp("PRINT", inputStr)) {
			command[n_line] = build_PRINT();
		}
		else if(!strcmp("STOP", inputStr)) {
			command[n_line] = build_STOP();
		}
		else {
			command[n_line] = build_ASSIGNMENT();
		}
		n_line++;
	}
	// run program
	while(!stop) {
		do_command(command[line - 1]);
	}
	return 0;
}


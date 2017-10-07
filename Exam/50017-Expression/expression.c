#include "expression.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>


int expressionEval(char *str, int *idx) {
	char c = str[(*idx)++], symbol;
	if(isdigit(c)) {
		return c - '0';
	}else if(c == '-') {
		return -expressionEval(str, idx);
	}else if(c == '(') {
		int a = expressionEval(str, idx);
		symbol = str[(*idx)++];
		int b = expressionEval(str, idx);
		if(str[(*idx)++] != ')' || a == INT_MIN || b == INT_MIN)
			return INT_MIN;
		if(symbol == '+')
			return a + b;
		if(symbol == '-')
			return a - b;
		if(symbol == '*')
			return a * b; 
		if(symbol == '/') {
			if(b == 0)
				return INT_MIN;
			return a / b;
		}
		else
			return INT_MIN;
	}
}

int expression(char *string) {
	int idx = 0, ans = expressionEval(string, &idx);
	if(*(string + idx) != '\0') {
		return INT_MIN;
	}
	return ans;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char licenses[32][8];

int getHyphen(char *str) {
	if(str[2] == '-') return 2;
	if(str[3] == '-') return 3;
	return 0;
}

int allAlphabetDigit(char *str, int hyphen) {
	for(int i = 0; i < 7; ++i) {
		if(i != hyphen && !isalnum(str[i]))
			return 0;
	}
}

int checkSum(char *str) {
	int sum = 0;
	for(int i = 0; i < 7; ++i) {
		if(isdigit(str[i]))
			sum += str[i] - '0';
	}
	return sum % 7;
}

int checkSame(char *str) {
	int count;
	for (int i = 0; i < 6; ++i) {
		count = 1;
		for (int j = i + 1; j < 7; ++j) {
			if(str[j] == str[i])
				count++;
			if(count == 3)
				return 0;
		}
	}
	return 1;
}

int checkConsecutiveFour(char *str) {
	for (int i = 0; i < 6; ++i) {
		if(str[i] == '4' && str[i + 1] == '4')
			return 0;
	}
	return 1;
}

int isValid(char *str) {
	int hyphen = getHyphen(str);
	if(!hyphen) return 0;
	if(!allAlphabetDigit(str, hyphen)) return 0;
	if(!checkSum(str)) return 0;
	if(!checkSame(str)) return 0;
	if(!checkConsecutiveFour(str)) return 0;
	return 1;
}

int cmpfunc (const void * a, const void * b) {
	char *s1 = (char*) a;
	char *s2 = (char*) b;
	int d = getHyphen(s1) - getHyphen(s2);
	if(d != 0) return d;
	return strcmp(s1, s2);
}

int main() {
	int N, count = 0;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%s", licenses[count]);
		if(isValid(licenses[count]))
			count++;
	}
	qsort(licenses, count, sizeof(licenses[0]), cmpfunc);
	for(int i = 0; i < count; ++i) {
		printf("%s\n", licenses[i]);
	}
}
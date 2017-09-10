#include <stdio.h>
#include <ctype.h>

int main() {
	int n, has_digit;
	char c;
	while((c = getchar()) != '\0') {
		if(isdigit(c)) {
			has_digit = 1;
			n *= 10;
			n += c - '0';
		} else if(has_digit){
				printf("%d\n", n);
				has_digit = 0;
				n = 0;
		}
	}
	return 0;
}
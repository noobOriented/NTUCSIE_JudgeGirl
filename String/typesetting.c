#include <stdio.h>
#include <string.h>

void printSpace(int n){
	for(int i = 0; i < n; ++i){
		printf(" ");
	}
}

int main() {
	int m,length, line_length = 0, n = 0, finish = 0;
	scanf("%d\n", &m);
	char input[m/2 + 2][m + 1];
	while(!finish){
		if(scanf("%s", input[n]) == EOF) {
			finish = 1;
			length = m;
		}else
			length = strlen(input[n]);
		if(line_length + length + 1 > m) {
			if(n == 1){
				printf("%s", input[0]);
				printSpace(m - line_length);
				printf("\n");
				strcpy(input[0], input[n]);
			}else if(n > 1) {
				int n_space = (m - line_length)/(n-1), remain_space = (m - line_length)%(n-1);
				for(int i = 0; i < remain_space; ++i) {
					printf("%s", input[i]);
					printSpace(n_space + 2);
				}
				for(int i = remain_space; i < n - 1; ++i) {
					printf("%s", input[i]);
					printSpace(n_space + 1);
				}
				printf("%s\n", input[n - 1]);
				strcpy(input[0], input[n]);
			}
			n = 1;
			line_length = length;
		}
		else {
			n++;
			line_length += length;
			if(n > 1)
				line_length++;
		}
	}

	return 0;
}
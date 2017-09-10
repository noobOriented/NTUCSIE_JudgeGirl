#include <stdio.h>
#include <string.h>

int main() {
	int len, n;
	char a, b;
	char alphabet[26], input[100001];
	scanf("%s", input);
	len = strlen(input);
	scanf("%d", &n);
	for(int i = 0; i < 26; ++i) {
		alphabet[i] = 'A' + i;
	}
	for(int i = 0; i < n; ++i) {
		scanf("%c %c", a, b);
		for(int j = 0; j < 26; ++j) {
			if(alphabet[j] == b)
				alphabet[j] = a;
		}
	}
	for(int i = 0; i < len; ++i) {
		printf("%c", alphabet[input[i] - 'A']);
	}
	return 0;
}
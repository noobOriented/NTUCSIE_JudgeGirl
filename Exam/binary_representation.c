#include <stdio.h>

int main() {
	char str[33];
	int n, a, k = 27, rest = 0;
	scanf("%s", str);
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &a);
		if(rest) {
			printf("%c", str[(rest + (a >> k)) & 31]);
			k -= 5;
		}
		while(k >= 0) {
			printf("%c", str[(a >> k) & 31]);
			k -= 5;
		}
		rest = (a << (-k)) & 31;
		k += 32;
	}
	return 0;
}
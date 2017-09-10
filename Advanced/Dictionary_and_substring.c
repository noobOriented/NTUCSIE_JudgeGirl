#include <stdio.h>
#include <string.h>

char dict[200][51], query[51];

int isSubstring(char *a, char *b) {
	int la = strlen(a), lb = strlen(b);
	for(int i = 0; i <= lb - la; ++i) {
		if(!strncmp(a, b + i, la))
			return 1;
	}
	return 0;
}

int main() {
	int N, Q, ans;
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%s", dict[i]);
	}
	scanf("%d", &Q);
	for(int i = 0; i < Q; ++i) {
		scanf("%s", query);
		ans = 0;
		for(int j = 0; j < N; ++j) {
			if(isSubstring(query, dict[j]))
				ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
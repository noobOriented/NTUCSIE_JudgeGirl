#include <stdio.h>
#include <limits.h>

int N, min = INT_MAX;
unsigned int words[32], collect_all = 1<<27 - 1;
int cost[32];

void select(int i, unsigned int mask, int sum) {
	if(sum >= min)
		return;
	if(mask & 67108863) {
		min = sum;
		return;
	}
	if(i == N)
		return;
	select(i + 1, mask | words[i], sum + cost[i]);
	select(i + 1, mask, sum);
}

int main() {
	char c;
	scanf("%d\n", &N);
	for(int i = 0; i < N; ++i) {
		while ((c = getchar()) != ' ') {
			words[i] |= 1 << (c - 'a');
		}
		scanf("%d\n", &cost[i]);
	}
	select(0, 0, 0);
	printf("%d", min);
}
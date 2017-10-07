#include <stdio.h>
#include <limits.h>

#define ALL_MASK (1 << 26) - 1

int N, min = INT_MAX;
int words[32];
int cost[32];

void select(int i, int mask, int sum) {
	if(sum >= min)
		return;
	if(mask == ALL_MASK) {
		min = sum;
		return;
	}
	if(i == N)
		return;
	int new_mask = mask | words[i];
	if(new_mask > mask)
		select(i + 1, new_mask, sum + cost[i]);
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
	printf("%d\n", min);
}
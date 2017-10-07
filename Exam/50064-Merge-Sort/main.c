#include <stdio.h>
#include <limits.h>

int N;
int a[16], next[16], head;
FILE *f[16], *f2;

int extract_min() {
	int min = INT_MAX, min_idx = -1, prev = -1, min_prev = -1;
	for(int i = head; i != -1; prev = i, i = next[i]) {
		if(a[i] < min) {
			min = a[i];
			min_idx = i;
			min_prev = prev;
		}
	}
	if(min_idx == -1)
		return 0;
	printf("%d\n", min);
	if(fread(&a[min_idx], 4, 1, f[min_idx]) != 1) {
		fclose(f[min_idx]);
		if(min_idx == head)
			head = next[head];
		else
			next[min_prev] = next[min_idx];
	}
	return 1;
}

int main() {
	scanf("%d", &N);
	char file_name[16];
	for(int i = 0; i < N; ++i) {
		scanf("%s", file_name);
		f[i] = fopen(file_name, "rb");
		fread(&a[i], 4, 1, f[i]);
		next[i] = i + 1;
	}
	head = 0;
	next[N-1] = -1;
	while(extract_min()) {
	}
}
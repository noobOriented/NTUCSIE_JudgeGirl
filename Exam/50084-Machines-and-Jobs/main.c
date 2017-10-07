#include <stdio.h>
#define max(x, y) (x > y? x : y)

int ready_machine[512] = {0}, ready_job[512], top[512] = {0}, Q[512];
int id[512][512], time[512][512];

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	for(int i = 0; i < N; ++i) {
		scanf("%d %d", &ready_job[i], &Q[i]);
		for (int j = 0; j < Q[i]; ++j) {
			scanf("%d %d", &id[i][j], &time[i][j]);
		}
	}
	int flag = 1;
	while(flag) {
		flag = 0;
		for(int i = 0; i < N; ++i) {
			int first_ready = 1000000, first_j = -1;
			for(int j = 0; j < M; ++j) {
				if(top[j] == Q[j])
					continue;
				if (i != id[j][top[j]]) {
					continue;
				}
				int	ready = max(ready_job[j], ready_machine[i]) + time[j][top[j]];
				if(ready < first_ready) {
					first_j = j;
					first_ready = ready;
				}
			}
			if(first_j == -1)
				continue;
			flag = 1;
			ready_job[first_j] = first_ready;
			ready_machine[i] = first_ready;
			top[first_j]++;
		}
	}
	for(int i = 0; i < M; ++i)
		printf("%d\n", ready_job[i]);
}
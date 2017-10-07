#include <stdio.h>
#define max(x, y) (x > y? x : y)

int ready_machine[512] = {0}, ready_job[512], tail[512];
int id[512][512], time[512][512];

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	for(int i = 0; i < M; ++i) {
		scanf("%d %d", &ready_job[i], &tail[i]);
		for (int j = tail[i] - 1; j >= 0; --j) {
			scanf("%d %d", &id[i][j], &time[i][j]);
		}
	}
	while(1) {
		int first_ready = 1000000, first_j = -1;
		int first_i = -1;
		for(int j = 0; j < M; ++j) {
			if(tail[j] == 0)
				continue;
			int i = id[j][tail[j] - 1];
			int	ready = max(ready_job[j], ready_machine[i]) + time[j][tail[j] - 1];
			if(ready < first_ready) {
				first_j = j;
				first_i = i;
				first_ready = ready;
			}
		}
		if(first_j == -1)
			break;
		ready_job[first_j] = first_ready;
		ready_machine[first_i] = first_ready;
		tail[first_j]--;
	}
	for(int i = 0; i < M; ++i)
		printf("%d\n", ready_job[i]);
}
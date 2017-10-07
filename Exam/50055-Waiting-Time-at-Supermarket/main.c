#include <stdio.h>
#include <stdlib.h>

int N, M;
#define MAXHEAP 1024
 
int heap[MAXHEAP];
int num = 0;

int removeMin() {
	num--;
	int i = 0, j = 1, min = heap[0], last = heap[num];
	while(j <= num) {
		if(j + 1 <= num && heap[j] > heap[j + 1]) {
			j++;
		}
		if(last > heap[j])
			heap[i] = heap[j];
		else
			break;
		i = j;
		j = (i << 1) + 1;
	}
	heap[i] = last;
	return min;
}

void add(int key) {
	int i = num, j = (i - 1) >> 1;
	while(j >= 0 && heap[j] > key) {
		heap[i] = heap[j];
		i = j;
		j = (j - 1) >> 1;
	}
	heap[i] = key;
	num++;
}


int main() {
	int N, M, time, spent, waiting_time = 0;
	scanf("%d %d", &N, &M);
	for(int i = 0; i < M; ++i) {
		scanf("%d %d", &time, &spent);
		if(num < N)
			add(time + spent);
		else {
			int min = removeMin();
			if(min > time){
				waiting_time += min - time;
				add(min + spent);
			}else
				add(time + spent);
		}
	}
	printf("%d\n", waiting_time);
}
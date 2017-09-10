#include <stdio.h>
#include <stdlib.h>

int N, M;
#define MAXHEAP 1024
 
struct Heap {
    int ary[MAXHEAP];
    int num;
};

void initialize(struct Heap *heap) {
	heap->num = 0;
}

int removeMin(struct Heap *heap) {
	heap->num--;
	int i = 0, j, min = heap->ary[0], last = heap->ary[heap->num];
	while(2 * i + 1 <= heap->num) {
		if(2 * i + 2 > heap->num || heap->ary[2 * i + 1] < heap->ary[2 * i + 2]) {
			j = 2 * i + 1;
		}else{
			j = 2 * i + 2;
		}
		if(last > heap->ary[j])
			heap->ary[i] = heap->ary[j];
		else
			break;
		i = j;
	}
	heap->ary[i] = last;
	return min;
}

void add(struct Heap *heap, int i) {
	int j = heap->num;
	while(heap->ary[(j - 1) / 2] > i && j > 0) {
		heap->ary[j] = heap->ary[(j - 1) / 2];
		j = (j - 1) / 2;
	}
	heap->ary[j] = i;
	heap->num++;
}


int main() {
	struct Heap counter;
	initialize(&counter);
	int N, M, time, spent, min, waiting_time = 0;
	scanf("%d %d", &N, &M);
	for(int i = 0; i < M; ++i) {
		scanf("%d %d", &time, &spent);
		if(counter.num < N)
			add(&counter, time + spent);
		else {
			min = removeMin(&counter);
			if(min > time){
				waiting_time += min - time;
				add(&counter, min + spent);
			}else
				add(&counter, time + spent);
		}
	}
	printf("%d", waiting_time);
	return 0;
}
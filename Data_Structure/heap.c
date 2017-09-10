#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void initialize(struct Heap *heap) {
	heap->num = 0;
}

int removeMin(struct Heap *heap) {
	if(isEmpty(heap)){
		printf("Heap is empty.\n");
		exit(1);
	}
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
	if(isFull(heap)) {
		printf("Heap is full.\n");
		exit(1);
	}
	int j = heap->num;
	while(heap->ary[(j - 1) / 2] > i && j > 0) {
		heap->ary[j] = heap->ary[(j - 1) / 2];
		j = (j - 1) / 2;
	}
	heap->ary[j] = i;
	heap->num++;
}

int isFull(struct Heap *heap) {
	return heap->num == MAXHEAP;
}

int isEmpty(struct Heap *heap) {
	return heap->num == 0;
}
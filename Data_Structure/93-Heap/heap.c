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
	int i = 0, j = 1, min = heap->ary[0], last = heap->ary[heap->num];
	while(j <= heap->num) {
		if(j + 1 <= heap->num && heap->ary[j] > heap->ary[j + 1]) {
			j++;
		}
		if(last > heap->ary[j])
			heap->ary[i] = heap->ary[j];
		else
			break;
		i = j;
		j = (i << 1) + 1;
	}
	heap->ary[i] = last;
	return min;
}

void add(struct Heap *heap, int key) {
	if(isFull(heap)) {
		printf("Heap is full.\n");
		exit(1);
	}
	int i = heap->num, j = (i - 1) >> 1;
	while(j >= 0 && heap->ary[j] > key) {
		heap->ary[i] = heap->ary[j];
		i = j;
		j = (j - 1) >> 1;
	}
	heap->ary[i] = key;
	heap->num++;
}

int isFull(struct Heap *heap) {
	return heap->num == MAXHEAP;
}

int isEmpty(struct Heap *heap) {
	return heap->num == 0;
}
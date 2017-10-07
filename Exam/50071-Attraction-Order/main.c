#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "attraction.h"

int N, M;

void get_order_direction(Attraction *a, int *result_order, int *result_dir) {
	// 靠下
	int order = a->y, direction = 0;
	// 靠右
	if(N - 1 - a->x < order) {
		order = N - 1 - a->x;
		direction = 1;
	}
	// 靠上
	if(N - 1 - a->y < order) {
		order = N - 1 - a->y;
		direction = 2;
	}
	// 靠左
	if(a->x < order) {
		order = a->x;
		direction = 3;
	}
	*result_order = order;
	*result_dir = direction;
}

int order_a, order_b, dir_a, dir_b;

int att_cmp(const void *c, const void *d) {
	Attraction *a = (Attraction*) c;
	Attraction *b = (Attraction*) d;
	get_order_direction(a, &order_a, &dir_a);
	get_order_direction(b, &order_b, &dir_b);
	if(order_a == order_b) {
		if(dir_a == dir_b) {
			switch(dir_a) {
				case 0:
					return a->x > b->x? 1 : -1;
				case 1:
					return a->y > b->y? 1 : -1;
				case 2:
					return a->x < b->x? 1 : -1;
				case 3:
					return a->y < b->y? 1 : -1;
			}
		}
		return dir_a > dir_b? 1 : -1;
	}
	return order_a > order_b? 1 : -1;
}

int main(int argc, char const *argv[]) {
	FILE *f;
	scanf("%d %d", &N, &M);
	f = fopen(argv[1], "rb");
	Attraction *att = (Attraction*) malloc(sizeof(Attraction) * M);
	fread(att, sizeof(Attraction), M, f);
	fclose(f);

	qsort(att, M, sizeof(Attraction), att_cmp);

	for(int i = 0; i < M; ++i) {
		printf("%d %d\n", att[i].x, att[i].y);
	}

	return 0;
}
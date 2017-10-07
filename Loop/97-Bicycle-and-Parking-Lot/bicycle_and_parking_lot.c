#include <stdio.h>
#include <limits.h>

int n, m;
int x[10], y[10], c[10], bik[10];

int abs(int x) {
	return x > 0? x: -x;
}

int get_dist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void put_bike(int bx, int by) {
	int dist, min_i, min_dist = INT_MAX;
	for (int i = 0; i < n; ++i) {
		if(bik[i] < c[i]) {
			dist = get_dist(bx, by, x[i], y[i]);
			if(dist < min_dist) {
				min_i = i;
				min_dist = dist;
			} else if(dist == min_dist) {
				if(x[i] < x[min_i]) {
					min_i = i;
					min_dist = dist;
				} else if (x[i] == x[min_i] && y[i] < y[min_i]) {
					min_i = i;
					min_dist = dist;
				}
			}
		}
	}
	++bik[min_i];
}


int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d %d", &x[i], &y[i], &c[i]);
		bik[i] = 0;
	}
	scanf("%d", &m);
	int bx, by;
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &bx, &by);
		put_bike(bx, by);
	}

	for (int i = 0; i < n; ++i) {
		printf("%d\n", bik[i]);
	}
	return 0;
}
#include <stdio.h>
#include <stdbool.h>

bool g[1024][1024];
int x[1024][2], N, M, Q, L, head_i = 0;

void initGrid() {
	L = 0;
	int sx, sy, ex, ey;
	scanf("%d %d %d %d\n", &sx, &sy, &ex, &ey);
	if(sx == ex) {
		if(sy < ey) {
			for(int i = sy; i <= ey; ++i) {
				g[sx][i] = 1;
				x[L][0] = sx;
				x[L][1] = i;
				L++;
			}
		} else {
			for(int i = sy; i >= ey; --i) {
				g[sx][i] = 1;
				x[L][0] = sx;
				x[L][1] = i;
				L++;
			}
		}
	} else {
		if(sx < ex) {
			for(int i = sx; i <= ex; ++i) {
				g[i][sy] = 1;
				x[L][0] = i;
				x[L][1] = sy;
				L++;
			}
		} else {
			for(int i = sx; i >= ex; --i) {
				g[i][sy] = 1;
				x[L][0] = i;
				x[L][1] = sy;
				L++;
			}
		}
	}
}


bool move() {
	int D;
	int sx = x[head_i][0], sy = x[head_i][1];
	scanf("%d", &D);
	switch(D) {
		case 0:
			if(++sx == N) return 0;
			break;
		case 1:
			if(--sx == -1) return 0;
			break;
		case 2:
			if(++sy == M) return 0;
			break;
		case 3:
			if(--sy == -1) return 0;
			break;
	}
	head_i--;
	if(head_i < 0) head_i += L;
	g[x[head_i][0]][x[head_i][1]] = 0;
	if(g[sx][sy]){
		g[x[head_i][0]][x[head_i][1]] = 1;
		return 0;
	}
	x[head_i][0] = sx;
	x[head_i][1] = sy;
	g[sx][sy] = 1;
	return 1;
}

void printGrid() {
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < M; ++j) {
			printf("%d", g[i][j]);
		}
		printf("\n");
	}
}

int main() {
	scanf("%d %d\n", &N, &M);
	initGrid();
	scanf("%d", &Q);
	for(int i = 0; i < Q && move(); ++i) {
	}
	printGrid();
	return 0;
} 
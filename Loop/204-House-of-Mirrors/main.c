#include <stdio.h>

int W, D, x, y, direction;
int g[100][100] = {0};

int main() {
	scanf("%d %d", &W, &D);
	for(int i = 0; i < D; ++i) {
		for (int j = 0; j < W; ++j) {
			scanf("%d", &g[i][j]);
		}
	}
	for(int i = 0; i < D; ++i) {
		x = i;
		y = D - 1;
		direction = 0;
		while(true) {

		}
	}
}
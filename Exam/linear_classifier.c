#include <stdio.h>
#include <string.h>

int N, M, T, Q, y;
int x[16][16], w[16][16];

void init() {
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < M; ++j) {
			w[i][j] = 1;
		}
	}
}

void train() {
	int score = 0;
	scanf("%d", &y);
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < M; ++j) {
			scanf("%d", &x[i][j]);
			score += w[i][j] * x[i][j];
		}
	}
	if(y && !(score >= T)) {
		for(int i = 0; i < M; ++i) {
			for(int j = 0; j < M; ++j) {
				if(x[i][j])
					w[i][j] *= 2;
			}
		}
	}
	else if(!y && (score >= T)) {
		for(int i = 0; i < M; ++i) {
			for(int j = 0; j < M; ++j) {
				if(x[i][j] && w[i][j] > 1)
					w[i][j] /= 2;
			}
		}
	}
}

int predict() {
	int score = 0;
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < M; ++j) {
			scanf("%d", &y);
			score += w[i][j] * y;
		}
	}
	return score >= T;
}

int main() {
	scanf("%d %d", &N, &M);
	T = 2 * M * M;
	init();
	for(int i = 0; i < N; ++i)
		train();
	scanf("%d", &Q);
	for(int i = 0; i < Q; ++i)
		printf("%d\n", predict());
	return 0;
}
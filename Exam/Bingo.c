#include <stdio.h>

char name[10][65];
int loc[10][65536];
int board[10][256][256];

int n, m;

int win(int id, int i, int j) {
	int k, win = 1;
	for(k = 0; k < m && win; ++k){
		if(!board[id][i][k])
			win = 0;
	}
	if(win)
		return 1;
	win = 1;
	for(k = 0; k < m && win; ++k){
		if(!board[id][k][j])
			win = 0;
	}
	if(win)
		return 1;
	win = 1;
	if(i == j){
		for(k = 0; k < m && win; ++k){
			if(!board[id][k][k])
				win = 0;
		}
		if(win)
			return 1;
	}
	win = 1;
	if(i + j == m - 1){
		for(k = 0; k < m && win; ++k){
			if(!board[id][k][m-1-k])
				win = 0;
		}
		if(win)
			return 1;		
	}
	return 0;
}

int bingo(int id, int x) {
	int l = loc[id][x], i = l / m, j = l % m;
	board[id][i][j] = 1;
	return win(id, i, j);
}

int main(int argc, char const *argv[]) {
	int x, finish = 0;
	scanf("%d %d", &n, &m);
	for(int id = 0; id < n; ++id){
		scanf("%s", name[id]);
		for (int i = 0; i < m; ++i) {
			for(int j = 0; j < m; ++j){
				scanf("%d", &x);
				loc[id][x] = i * m + j;
			}
		}
	}
	while(!finish) {
		scanf("%d", &x);
		for(int id = 0; id < n; ++id){
			if(bingo(id, x)){
				if(!finish)
					printf("%d", x);
				printf(" %s", name[id]);
				finish = 1;
			}
		}
	}
	return 0;
}
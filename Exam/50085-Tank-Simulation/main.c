#include <stdio.h>

int N, M, L, W, O;
int grid[512][512] = {0}, x_tank = 0, y_tank = 0;


int can_move(int command) {
	int count = 0;
	switch(command) {
		case 1:
			if(x_tank + W == M)
				return 0;
			for(int i = y_tank; i < y_tank + L; ++i) {
				if(grid[i][x_tank + W] == 2)
					count++;
				if(count == 2)
					return 0;
			}
			break;
		case 3:
			if(x_tank == 0)
				return 0;
			for(int i = y_tank; i < y_tank + L; ++i) {
				if(grid[i][x_tank - 1] == 2)
					count++;
				if(count == 2)
					return 0;
			}
			break;
		case 2:
			if(y_tank + L == N)
				return 0;
			for(int j = x_tank; j < x_tank + W; ++j) {
				if(grid[y_tank + L][j] == 2)
					count++;
				if(count == 2)
					return 0;
			}
			break;
		case 4:
			if(y_tank == 0)
				return 0;
			for(int j = x_tank; j < x_tank + W; ++j) {
				if(grid[y_tank - 1][j] == 2)
					count++;
				if(count == 2)
					return 0;
			}
			break;
		case 5:
			if(x_tank + W == M || y_tank + L == N)
				return 0;
			for(int j = x_tank + 1; j <= x_tank + W; ++j) {
				if(grid[y_tank + L][j] == 2)
					count++;
				if(count == 2)
					return 0;
			}
			for(int i = y_tank + 1; i < y_tank + L; ++i) {
				if(grid[i][x_tank + W] == 2)
					count++;
				if(count == 2)
					return 0;
			}
	}
	return 1;
}


void move(int command) {
	int count = 0;
	switch(command) {
		case 1:
			for(int i = y_tank; i < y_tank + L; ++i) {
				grid[i][x_tank] = 0;
				grid[i][x_tank + W] = 1;
			}
			x_tank++;
			break;
		case 3:
			for(int i = y_tank; i < y_tank + L; ++i) {
				grid[i][x_tank + W - 1] = 0;
				grid[i][x_tank - 1] = 1;
			}
			x_tank--;
			break;
		case 2:
			for(int j = x_tank; j < x_tank + W; ++j) {
				grid[y_tank][j] = 0;
				grid[y_tank + L][j] = 1;
			}
			y_tank++;
			break;
		case 4:
			for(int j = x_tank; j < x_tank + W; ++j) {
				grid[y_tank + L - 1][j] = 0;
				grid[y_tank - 1][j] = 1;
			}
			y_tank--;
			break;
		case 5:
			for(int j = x_tank + 1; j <= x_tank + W; ++j) {
				grid[y_tank][j - 1] = 0;
				grid[y_tank + L][j] = 1;
			}
			for(int i = y_tank + 1; i < y_tank + L; ++i) {
				grid[i][x_tank] = 0;
				grid[i][x_tank + W] = 1;
			}
			x_tank++;
			y_tank++;
	}
}



int main() {
	scanf("%d %d %d %d", &N, &M, &L, &W);
	scanf("%d", &O);
	int x, y;
	for(int i = 0; i < L; ++i) {
		for(int j = 0; j < W; ++j) {
			grid[i][j] = 1;
		}
	}
	for(int i = 0; i < O; ++i) {
		scanf("%d %d", &x, &y);
		grid[y][x] = 2;
	}
	int command, count;

	while(scanf("%d", &command) != EOF) {
		count = 0;
		if(!command) {
			for(int i = 0; i < N; ++i) {
				for(int j = 0; j < M; ++j)
					putchar(grid[i][j] + '0');
				puts("");
			}
		}else if(can_move(command))
			move(command);
	}
}
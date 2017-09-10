#include <stdio.h>

int n, Awin, tie, Bwin;
int board[4][4];

void Apick(int i, int score);
void Bpick(int j, int score);

void Apick(int i, int score) {
	int tmp, picked = 0;
	for(int j = 0; j < n; ++j) {
		if(board[i][j]) {
			picked = 1;
			tmp = board[i][j];
			board[i][j] = 0;
			Bpick(j, score + tmp);
			board[i][j] = tmp;
		}
	}
	if(!picked) {
		if(score > 0)
			Awin++;
		else if(score < 0)
			Bwin++;
		else
			tie++;
	}

}

void Bpick(int j, int score) {
	int tmp, picked = 0;
	for(int i = 0; i < n; ++i) {
		if(board[i][j]) {
			picked = 1;
			tmp = board[i][j];
			board[i][j] = 0;
			Apick(i, score - tmp);
			board[i][j] = tmp;
		}
	}
	if(!picked) {
		if(score > 0)
			Awin++;
		else if(score < 0)
			Bwin++;
		else
			tie++;
	}
}

int main() {
	while(scanf("%d", &n) != EOF) {
		Awin = 0;
		Bwin = 0;
		tie = 0;
		for(int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &board[i][j]);
			}
		}
		Apick(0, 0);
		printf("%d %d %d\n", Awin, Bwin, tie);
	}
	return 0;
}
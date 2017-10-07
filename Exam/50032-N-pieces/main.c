#include <stdio.h>

int n, m, k;
int row[16], col[16], d1[32], d2[32];
int g[16][16];

int isvalid(int i, int j) {
	return row[i] < k && col[j] < k && d1[i+j] < k && d2[i-j+16] < k;
}

int place(int i, int j, int num) {
	if(num == m) {
		for(int k = 0; k < n; ++k) {
			for (int l = 0; l < n; ++l)
				printf("%c", g[k][l]? 'o':'.');
			printf("\n");
		}
		return 1;
	}
	if(j == n)
		++i, j = 0;
	if(i == n)
		return 0;
	if(isvalid(i, j)) {
		row[i]++, col[j]++, d1[i+j]++, d2[i-j+16]++;
		g[i][j] = 1;
		if(place(i, j+1, num+1))
			return 1;
		g[i][j] = 0;
		row[i]--, col[j]--, d1[i+j]--, d2[i-j+16]--;
	}
	return place(i, j+1, num);
}


int main() {
	while(scanf("%d %d %d", &n, &m, &k) == 3) {
		memset(row, 0, sizeof(row));
		memset(col, 0, sizeof(col));
		memset(d1, 0, sizeof(d1));
		memset(d2, 0, sizeof(d2));
		memset(g, 0, sizeof(g));
		if(!place(0, 0, 0))
			printf("N\n");
	}
}
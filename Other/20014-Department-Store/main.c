#include <stdio.h>
#include <limits.h>
#include <string.h>

#define max(x, y) x > y? x : y
#define min(x, y) x < y? x : y

int w[1024], r[1024], dp[2][1024], group_cost[1024][1024];

void compute_dp(int flag, int n_left, int n_right, int i_left, int i_right) {
	int n_mid = (n_left + n_right) / 2,
		i_best,
		i_right2 = min(i_right, n_mid-1);
	int cost, min = INT_MAX;
	for(int i = max(i_left, r[n_mid]); i <= i_right2; ++i) {
		cost = dp[flag][i] + group_cost[i][n_mid];
		if(cost < min) {
			min = cost;
			i_best = i;
		}
	}
	dp[!flag][n_mid] = min;
	r[n_mid] = i_best;
	// divide & conquer
	if(n_left <= n_mid - 1)
		compute_dp(flag, n_left, n_mid - 1, i_left, i_best);
	if(n_mid + 1 <= n_right)
		compute_dp(flag, n_mid + 1, n_right, i_best, i_right);
}

int main() {
	int N, M;
	while(scanf("%d %d", &N, &M) == 2) {
		for(int n = 0; n < N; ++n)
			scanf("%d", &w[n]);
		for(int left = 0; left < N; ++left) {
			int lsum = 0, rsum = 0;
			int i = left, cost = 0;
			group_cost[left][left] = 0;
			for(int right = left + 1; right <= N; ++right) {
				while(i < right && lsum - rsum + w[i] < 0) {
					cost += lsum - rsum + w[i];
					lsum += w[i], rsum -= w[i+1];
					i++;
				}
				group_cost[left][right] = cost;
				rsum += w[right];
				cost += w[right] * (right - i);
			}
			group_cost[left][left+1] = 0;
		}

		for(int n = 2; n <= N; ++n) {
			dp[1][n] = group_cost[0][n];
			r[n] = 1;
		}

		for(int m = 2; m <= M; ++m) {
			dp[m % 2][m] = 0;
			compute_dp((m - 1) & 1, m+1, N, m-1, N-1);
		}
		printf("%d\n", dp[M % 2][N]);
	}
}
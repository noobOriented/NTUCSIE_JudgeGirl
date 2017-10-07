#include <stdio.h>
#include <limits.h>
#include <string.h>

#define max(x, y) x > y? x : y
#define min(x, y) x < y? x : y

int V, P, dist, min;
int x[512], sum[512], r[512], dp[2][512];

int group_dist(int left, int right) {
	int mid2 = left + right;
	if(mid2 % 2)
		return sum[right] + sum[left] - 2 * sum[mid2/2] - x[mid2/2];
	return sum[right] + sum[left] - 2 * sum[mid2/2];
}

void compute_dp(int flag, int n_left, int n_right, int i_left, int i_right) {
	int n_mid = (n_left + n_right) / 2,
		i_best,
		i_right2 = min(i_right, n_mid-1);
	min = INT_MAX;
	for(int i = max(i_left, r[n_mid]); i <= i_right2; ++i) {
		dist = dp[flag][i] + group_dist(i, n_mid);
		if(dist < min) {
			min = dist;
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
	while(scanf("%d %d", &V, &P) == 2) {
		sum[0] = 0;
		// S[n] = x[0] + x[1] + ... + x[n-1]
		for(int i = 0; i < V; ++i) {
			scanf("%d", &x[i]);
			sum[i+1] = sum[i] + x[i];
		}
		for(int n = 2; n <= V; ++n) {
			dp[1][n] = group_dist(0, n);
			r[n] = 1;
		}

		for(int p = 2; p <= P; ++p) {
			dp[p%2][p] = 0;
			compute_dp((p - 1)%2, p+1, V, p-1, V-1);
		}
		printf("%d\n", dp[P%2][V]);
	}
}
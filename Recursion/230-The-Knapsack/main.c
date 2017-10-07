#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define min(x, y) x < y? x : y
#define max(x, y) x > y? x : y
int W, N, wv[32][2], sum = 0, DP[1 << 14];
 
int cmp(const void *a, const void *b) {
    int wa = *(int*) a;
    int wb = *(int*) b;
    return wa > wb;
}
 
int main() {
    scanf("%d %d", &N, &W);
    memset(DP, 0, sizeof(DP));
    for(int i = 0; i < N; ++i)
        scanf("%d %d", &wv[i][0], &wv[i][1]);
 
    qsort(wv, N, sizeof(wv[0]), cmp);
 
    for(int i = 0; i < N; ++i) {
        int weight = wv[i][0], value = wv[i][1];
        sum += weight;
        for(int j = min(W, sum); j >= weight; --j)
            DP[j] = max(DP[j], DP[j - weight] + value);
    }
    int sol = 0;
    for(int i = 0; i <= W; ++i)
        sol = max(sol, DP[i]);
    printf("%d\n", sol);
}
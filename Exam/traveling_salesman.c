#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
 
bool has_path[128][128] = {0};
int next[128], dist[128][128], n, min;
 
void permutation(int min_i, int i, int now, int sum) {
    if(sum >= min)
        return;
    if (i == n) {
        if(has_path[now][0] && sum + dist[now][0] < min)
            min = sum + dist[now][0];
        return;
    }
    int j, previous;
    j = next[min_i];
    previous = min_i;
    if(has_path[now][min_i])
        permutation(j, i + 1, min_i, sum + dist[now][min_i]);
    while(j != -1) {
        if(has_path[now][j]) {
            next[previous] = next[j];
            permutation(min_i, i + 1, j, sum + dist[now][j]);
            next[previous] = j;
        }
        previous = j;
        j = next[j];
    }
}
 
int main() {
    scanf("%d\n", &n);
    int row_col_min, reduce = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j)
            scanf("%d", &dist[i][j]);
    }
    memset(has_path, 0, sizeof(has_path));
    for(int i = 0; i < n; ++i) {
        row_col_min = INT_MAX;
        for(int j = 0; j < n; ++j) {
            if(dist[i][j] > 0) {
                has_path[i][j] = 1;
                if(dist[i][j] < row_col_min)
                    row_col_min = dist[i][j];
            }
        }
        for(int j = 0; j < n; ++j)
            dist[i][j] -= row_col_min;
        reduce += row_col_min;
    }
    for(int j = 0; j < n; ++j) {
        row_col_min = INT_MAX;
        for(int i = 0; i < n; ++i) {
            if(has_path[i][j] && dist[i][j] < row_col_min)
                row_col_min = dist[i][j];
        }
        for(int i = 0; i < n; ++i)
            dist[i][j] -= row_col_min;
        reduce += row_col_min;
    }
    for (int i = 0; i < n - 1; ++i)
        next[i] = i + 1;
    next[n-1] = -1;
    min = INT_MAX;
    permutation(1, 1, 0, reduce);
    printf("%d", min);
    return 0;
}
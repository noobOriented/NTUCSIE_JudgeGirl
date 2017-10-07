#include <stdio.h>
#include <string.h>

#define MAX_L 128
#define max(x, y) (x > y? x : y)

int lx, ly, LCS[MAX_L][MAX_L] = {0}, g[MAX_L][MAX_L];
char X[MAX_L], Y[MAX_L];
char output[MAX_L];



void dfs(int i, int j, int idx) {
    if(g[i][j])
        return;
    g[i][j] = 1;
    if(idx < 0) {
        printf("%s\n", output);
        return;
    }
    if(i == 0 || j == 0)
        return;
    if(X[i - 1] == Y[j - 1]) {
        output[idx] = X[i - 1];
        dfs(i - 1, j - 1, idx - 1);
        return;
    }
    if(LCS[i][j] == LCS[i - 1][j])
        dfs(i - 1, j, idx);
    if(LCS[i][j] == LCS[i][j - 1])
        dfs(i, j - 1, idx);
}
 
int main() {
    scanf("%s%s", X, Y);
    lx = strlen(X), ly = strlen(Y);
    for(int i = 1; i <= lx; ++i) {
        for(int j = 1; j <= ly; ++j) {
            if(X[i - 1] == Y[j - 1]) {
                LCS[i][j] = LCS[i - 1][j - 1] + 1;
            }
            else {
                LCS[i][j] = max(LCS[i][j - 1], LCS[i - 1][j]);
            }
        }
    }
    printf("%d\n", LCS[lx][ly]);
    output[LCS[lx][ly]] = '\0';
    dfs(lx, ly, LCS[lx][ly] - 1);
}
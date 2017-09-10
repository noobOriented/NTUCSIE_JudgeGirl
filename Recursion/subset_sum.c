#include <stdio.h>
int n, k;
int a[15], table[16][300];

int subset(int i, int sum){
    if(sum == 0)
        return 1;
    if(sum < 0 || i < 0)
        return 0;
    if (table[i][sum] != -1)
        return table[i][sum];
    return table[i][sum] = (subset(i - 1, sum - a[i]) + subset(i - 1, sum));
}

int main(){
    int i;
    memset(table, -1, sizeof(table));
    scanf("%d", &n);
    for (i = 0; i < n; ++i){
        scanf("%d", &a[i]);
    }
    while (scanf("%d", &k) != EOF){
        printf("%d\n", subset(n - 1, k));
    }
    return 0;
}
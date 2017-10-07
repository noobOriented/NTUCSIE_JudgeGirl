#include <stdio.h>
int a[20], k, N, M;
 
int pick(int i, int sum, int picked){
    if(sum > M)
        return 0;
    if(i == N)
        return picked >= k;
    return pick(i+1, sum, picked) + pick(i+1, sum + a[i], picked + 1);
}
 
int main() {
    scanf("%d%d%d",&k,&N,&M);
    int i;
    for(i = 0; i < N; ++i)
        scanf("%d", &a[i]);
    printf("%d\n", pick(0, 0, 0));
    return 0;
}
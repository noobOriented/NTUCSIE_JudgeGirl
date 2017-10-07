#include <stdio.h>
#include <stdlib.h>
 
int ary[16], sol[16], next[16], friends[16][16] = {0}, n, min;
 
void permutation(int min_i, int i, int dist){
    if(dist >= min)
        return;
    if (i == n){
        min = dist;
        for(int j = 0; j < n; ++j)
            sol[j] = ary[j];
        return;
    }
    int j, k, previous, new_dist;
    j = next[min_i];
    previous = min_i;
    ary[i] = min_i;
    new_dist = dist;
    for(k = 0; k < i; ++k) {
        if(friends[ary[k]][min_i]) {
            if(i - k > new_dist) {
                new_dist = i - k;
                break;
            }
        }
    }
    permutation(j, i + 1, new_dist);
    while(j != -1){
        new_dist = dist;
        for(k = 0; k < i; ++k) {
            if(friends[ary[k]][j]) {
                if(i - k > new_dist) {
                    new_dist = i - k;
                    break;
                }
            }
        }
        ary[i] = j;
        next[previous] = next[j];
        permutation(min_i, i + 1, new_dist);
        next[previous] = j;
        previous = j;
        j = next[j];
    }
}
 
int main(){
    int i, m;
    char a, b;
    scanf("%d %d\n", &n, &m);
    for(i = 0; i < m; ++i) {
        scanf("%c %c\n", &a, &b);
        friends[a - 'A'][b - 'A'] = 1;
        friends[b - 'A'][a - 'A'] = 1;
    }
    for (i = 0; i < n - 1; ++i)
        next[i] = i + 1;
    next[n-1] = -1;
    min = n;
    permutation(0, 0, 0);
    printf("%d\n", min);
    for (i = 0; i < n - 1; ++i)
        printf("%c ", sol[i] + 'A');
    printf("%c\n", sol[n - 1] + 'A');
    return 0;
}
#include <stdio.h>
#include <string.h>

char ary[16], sol[16];
int next[16], friends[16] = {0}, n, min;

static inline int max(int x, int y) {
    return x > y ? x : y;
}

int get_lower_bound(int pos, int mask) {
    if(pos == n)
        return 0;
    for(int j = 0; j < pos; ++j) {
        int v = ary[j];
        if(friends[v] & mask) {
            return pos - j + __builtin_popcount(friends[v] & mask) - 1;
        }
    }
    return 0;
}

void dfs(int min_i, int pos, int dist, int mask){
    dist = max(dist, get_lower_bound(pos, mask));
    if(dist >= min)
        return;
    if (pos == n){
        min = dist;
        memcpy(sol, ary, n * sizeof(char));
        return;
    }
    for(int i = min_i, prev; i != -1; prev = i, i = next[i]) {
        ary[pos] = i;
        if(i == min_i) {
            dfs(next[min_i], pos + 1, dist, mask ^ (1 << i));
        } else {
            next[prev] = next[i];
            dfs(min_i, pos + 1, dist, mask ^ (1 << i));
            next[prev] = i;
        }
    }
}
 
int main(){
    int m;
    char a, b;
    scanf("%d %d\n", &n, &m);
    for(int i = 0; i < m; ++i) {
        scanf("%c %c\n", &a, &b);
        friends[a - 'A'] |= 1 << (b - 'A');
        friends[b - 'A'] |= 1 << (a - 'A');
    }
    for(int i = 0; i < n - 1; ++i)
        next[i] = i + 1;
    next[n - 1] = -1;
    min = n;
    dfs(0, 0, 0, (1 << n) - 1);
    printf("%d\n", min);
    for(int i = 0; i < n; ++i)
        printf("%c%c", sol[i] + 'A', i == n - 1? '\n' : ' ');
    return 0;
}

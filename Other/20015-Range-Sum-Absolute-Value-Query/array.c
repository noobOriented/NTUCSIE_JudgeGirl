#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define left(x) (2 * x + 1)
#define right(x) (2 * x + 2)

int N, M;
int a[1 << 18], node_sum[1 << 19];

inline int abs(int x) {
    return x < 0? -x : x;
}


void construct(int x, int lidx, int ridx) {
    if(lidx == ridx) {
        node_sum[x] = abs(a[lidx]);
        return;
    }
    int mid = (lidx + ridx) / 2;
    construct(left(x), lidx, mid);
    construct(right(x), mid + 1, ridx);
    node_sum[x] = node_sum[left(x)] + node_sum[right(x)];
}

void printArray() {
    for(int i = 0; i < N; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void printNode(int x, int lidx, int ridx) {
    if(lidx == ridx) {
        printf("%d ", node_sum[x]);
        return;
    }
    int mid = (lidx + ridx) / 2;
    printNode(left(x), lidx, mid);
    printNode(right(x), mid + 1, ridx);
}

int L, R, total;
void rangeSum(int x, int lidx, int ridx) {
    if(L <= lidx && ridx <= R) {
        total += node_sum[x];
        return;
    }
    int mid = (lidx + ridx) / 2;
    if(L <= mid)
        rangeSum(left(x), lidx, mid);
    if(R > mid)
        rangeSum(right(x), mid + 1, ridx);
}

int add;
void update(int x, int lidx, int ridx) {
    if(lidx == ridx) {
        a[lidx] += add;
        node_sum[x] = abs(a[lidx]);
        return;
    }
    int mid = (lidx + ridx) / 2;
    if(L <= mid)
        update(left(x), lidx, mid);
    if(R > mid)
        update(right(x), mid + 1, ridx);
    node_sum[x] = node_sum[left(x)] + node_sum[right(x)];
}

int main() {
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; ++i)
        scanf("%d", &a[i]);
    int root = 0;
    construct(root, 0, N - 1);
    int query;
    for(int i = 0; i < M; ++i) {
        scanf("%d", &query);
        if(query) {
            scanf("%d %d %d", &L, &R, &add);
            update(root, 0, N - 1);
        } else {
            scanf("%d %d", &L, &R);
            total = 0;
            rangeSum(root, 0, N - 1);
            printf("%d\n", total);
        }
    }
}

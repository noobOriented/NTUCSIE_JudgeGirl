/* 


DP(n, W) =      max   { DP(n-1, W - i * w) + i * v}
          0 =< i <= min(W/w, c)

從上式可看出 DP(n, W) 只與 W, W - w, W - 2w...有關

將計算改為照 W / w 的餘數的順序

W = jw + r

DP(n, jw + r) = DP(n-1, (j-i) * w + r) + i * v   0 <= i <= min(j, c)

            let j-i = k & max(0, j - c) <= k <= j

              = DP(n-1, k * w + r) + (j - k) * v
              = DP(n-1, k * w + r) - k * v + j * v
              = y[k] + j * v

計算順序上，先固定r，初始化一個新的Deque，從小的j 開始計算
每次都將y 放入Deque(因 k 可以 = j)
維護Deque 之遞減性，其頭點即為最大值
又因k需 >= j - c ，每次取出頭點時，可以順便清理 k < j - c的點
因其下限 j - c 隨 j 遞增，一但一小於此下限在更大的下限時也用不到了

*/




#include <stdio.h>
#include <assert.h>
#include <string.h>

#define min(x, y) x < y? x : y
#define MAX_M 1 << 20

int head, tail;
int x[MAX_M], y[MAX_M];

void init() {
    head = 0;
    tail = -1; // empty
}

void push(int new_x, int new_y) {
    // 維護遞減性質
    while(head <= tail && new_y >= y[tail])
        tail--;
    tail++;
    x[tail] = new_x;
    y[tail] = new_y;
}

void pop(int x_min) {
    // 檢查最小值是否 >= c
    if(x[head] < x_min)
        head++;
}


int M, N, DP[MAX_M];

int main() {
    scanf("%d %d", &M, &N);
    memset(DP, 0, sizeof(DP));

    int v, w, c;
    for(int i = 0; i < N; ++i) {
        scanf("%d %d %d", &v, &w, &c);
        // 剩餘重量 / weight 之商為j 餘數為r 
	    for(int r = 0; r < w; ++r) {
            init();
            int max_j = (M - r) / w, sum_v = 0, sum_w = r;
            for(int j = 0; j <= max_j; ++j) {
                push(j, DP[sum_w] - sum_v);
                pop(j - c);
                DP[sum_w] = y[head] + sum_v;
                sum_v += v;
                sum_w += w;
            }
        }
    }
    printf("%d\n", DP[M]);
}
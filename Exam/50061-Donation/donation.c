#include <stdio.h>
#include <stdlib.h>
 
int n, max;
int donation[64], remain_donation[64], hate[64][64];
 
//i 已放入的人, list 為待檢查之名單，n_list為其大小
void indepenent(int i, int list[], int n_list, int total_donation) {
    if (i == n || n_list == 0) {
        if(total_donation > max)
            max = total_donation;
        return;
    }
    //剩下的人全捐也不夠
    if(total_donation + remain_donation[i] <= max)
        return;
    //若決定加入此人，名單只留下此人不討厭的
    int new_list[n_list], new_n = 0;
    for(int j = 1; j < n_list; ++j) {
        if(!hate[list[0]][list[j]]) {
            new_list[new_n] = list[j];
            new_n++;
        }
    }
    //嘗試放入或不放，若放則使用新名單，不放則list僅去掉此人
    indepenent(i + 1, new_list, new_n, total_donation + donation[list[0]]);
    indepenent(i, list + 1, n_list - 1, total_donation);
}
 
int main() {
    int list[64];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &donation[i]);
        list[i] = i;
    }
    remain_donation[n - 1] = donation[n - 1];
    for(int i = n - 1; i > 0; --i) {
        remain_donation[i - 1] = remain_donation[i] + donation[i - 1];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &hate[i][j]);
        }
    }
    max = 0;
    indepenent(0, list, n, 0);
    printf("%d\n", max);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int n, m;
int a[100], friends[100][100];

//i 已放入的人, list 為待檢查之名單，n_list為其大小
int indepenent(int i, int list[], int n_list){
    if (i == m) {
        for (int j = 0; j < m - 1; ++j) {
            printf("%d ", a[j]);
        }
        printf("%d\n", a[m - 1]);
        return 1;
    }
    //人不夠了
    if(i + n_list < m)
    	return 0;
    a[i] = list[0];
    //若決定加入此人，名單只留下與此人不認識的
    int new_list[100], new_n = 0;
    for(int j = 1; j < n_list; ++j) {
    	if(!friends[list[0]][list[j]]) {
    		new_list[new_n] = list[j];
    		new_n++;
    	}
    }
    //答案是放入或不放，若放則使用新名單，不放則list僅去掉此人
    return indepenent(i + 1, new_list, new_n) || indepenent(i, list + 1, n_list - 1);
}
 
int main() {
	int list[100];
    while(scanf("%d %d\n", &n, &m) != EOF) {
	    for (int i = 0; i < n; ++i) {
	    	list[i] = i;
	    	for (int j = 0; j < n; ++j) {
	        	scanf("%d", &friends[i][j]);
	        }
	    }
	    if(!indepenent(0, list, n))
	    	printf("no solution\n");
	}
    return 0;
}
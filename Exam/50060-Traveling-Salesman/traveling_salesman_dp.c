#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
 
int main() {
	int i, j, k;
    int dist[16][16], n, min, g[1 << 13][16];
    scanf("%d\n", &n);
    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j)
            scanf("%d", &dist[i][j]);
    }
    //建表g，i為路徑包含之點集的bitset, j為起點，g[i][j]為從j出發經i路徑到達n-1之最短距離
    //初始化g, i = 0為空集合, 故直接從j 到達 n - 1
    for(j = 0; j < n - 1; ++j) {
    	g[0][j] = dist[n - 1][j];
    }
    //路徑不需包含n - 1，窮舉所有路徑，從小到大保證遞回需要的位置都已算過
    for(i = 1; i < (1 << (n - 1)) - 1; ++i) {
    	for(j = 0; j < n - 1; ++j) {
    		//路徑不包含起終點，若j屬於i則不用考慮
    		if((i >> j) & 1)
    			continue;
    		//從路徑中窮舉下一目的地k找出最短路徑，k需屬於i, 並在起點為k, 剔除k的路徑中找解
    		min = INT_MAX;
    		for(k = 0; (1 << k) <= i; ++k) {
    			if((i & (1 << k)) && g[i ^ (1 << k)][k] + dist[j][k] < min)
    				min = g[i ^ (1 << k)][k] + dist[j][k];
    		}
    		g[i][j] = min;
    	}
    }
    //答案為g[1 << (n - 1) - 1][n - 1]
	min = INT_MAX;
	for(k = 0; (1 << k) <= i; ++k) {
		if(g[i ^ (1 << k)][k] + dist[j][k] < min)
			min = g[i ^ (1 << k)][k] + dist[j][k];
	}
    printf("%d", min);
    return 0;
}
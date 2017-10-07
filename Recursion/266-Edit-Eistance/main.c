#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
char list[128][16];
int min, min_i, min_j;
 
#define min(x, y) x < y? x : y
 
int distance(int index1, int index2, int i, int j, int currentdist){
    if (currentdist > min)
        return currentdist;
    if (list[index1][i] == '\0')
        return strlen(list[index2]) - j + currentdist;
    if (list[index2][j] == '\0')
        return strlen(list[index1]) - i + currentdist;
    if (list[index1][i] == list[index2][j])
        return distance(index1, index2, i + 1, j + 1, currentdist);
    return min(distance(index1, index2, i, j + 1, currentdist + 1), distance(index1, index2, i + 1, j, currentdist + 1));

}
 
int main(){
    int i, j, dis, n = 0;
    min = 1024;
    while(scanf("%s", list[n]) != EOF){
        ++n;
    }
    for (i = 0; i < n - 1; ++i){
        for (j = i + 1; j < n; ++j){
            dis = distance(i, j, 0, 0, 0);
            if (dis < min){
                min = dis;
                min_i = i;
                min_j = j;
            }
        }
    }
    printf("%d %d %d\n", min, min_i + 1, min_j + 1);
    return 0;
}
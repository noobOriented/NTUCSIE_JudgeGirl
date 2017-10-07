#include <stdio.h>
 
int input[9][9], mine[9][9] = {0}, solved = 0;
int conflict(int y, int x);
 
int plant_mine(int i, int j){
    if (i) {
        if(j > 1 && conflict(i-1, j-2))
            return 0;
        else if (i > 1 && conflict(i-2, 8))
            return 0;
    }
    
    if(j > 8)
        j = 0, ++i;

    if (i == 9) {
        if(conflict(7, 8))
            return 0;
        for (j = 0; j < 9; ++j){
            if(conflict(8, j))
                return 0;
        }
        return 1;
    }
    mine[i][j] = 0;
    if(plant_mine(i, j+1))
        return 1;
    mine[i][j] = 1;
    return plant_mine(i, j+1);    
}
 
int conflict(int y, int x){
    int sum = 0, up = y-1, down = y+1, left = x-1, right = x+1, i, j;
    if(up < 0)
        up = 0;
    if(down > 8)
        down = 8;
    if(left < 0)
        left = 0;
    if(right > 8)
        right = 8;
    for(i = up; i <= down; ++i){
        for(j = left; j <= right; ++j){
            sum += mine[i][j];
        } 
    }
    return (sum != input[y][x]);
}
int main(){
    int i, j;
    for (i = 0; i < 9; ++i){
        for (j = 0; j < 9; ++j)
            scanf("%d", &input[i][j]);
    }

    if (plant_mine(0, 0)){
        for (i = 0; i < 9; ++i){
            for (j = 0; j < 9; ++j){
                printf("%d%c", mine[i][j], j < 8? ' ': '\n');
            }
        }
    } else
        printf("no solution\n");
}
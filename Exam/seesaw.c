#include <stdio.h>
 
int cmpfunc (const void * a, const void * b) {
   return *(int*)a - *(int*)b;
}
 
int n, mid;
int w[17], next[17], left[8], right[8];

int possible(int min_i, int i_left, int i_right, int diff_torque){
    int i = min_i, j;
    // 左邊較小
    if(diff_torque <= 0){
        j = i_right;
        //用小的塞滿右邊
        while(j < mid){
            diff_torque -= w[i] * (mid - j);
            ++j;
            i = next[i];
        }
        i = next[i];
        j = 1;
        while(i != -1){
            diff_torque += w[i] * j;
            if (diff_torque >= 0)
                return 1;
            ++j;
            i = next[i];
        }
    }else{
        j = i_left;
        while(j < mid){
            diff_torque += w[i] * (mid - j);
            ++j;
            i = next[i];
        }
        i = next[i];
        j = 1;
        while(i != -1){
            diff_torque -= w[i] * j;
            if (diff_torque <= 0)
                return 1;
            ++j;
            i = next[i];
        }
    }
    return 0;
}

int balance(int min_i, int i_left, int i_right, int diff_torque){
    int i, previous;
    if (diff_torque == 0 && i_left == mid && i_right == mid) {
        for (i = 0; i < mid; ++i){
            printf("%d ", left[i]);
        }
        printf("_^_");
        for (i = mid - 1; i >= 0; --i){
            printf(" %d", right[i]);
        }
        printf("\n");
        return 1;
    }
    if(!possible(min_i, i_left, i_right, diff_torque))
        return 0;
    if(diff_torque <= 0){
        if(i_left == mid)
            return 0;
        i = next[min_i], previous = min_i;
        left[i_left] = w[min_i];
        if(balance(i, i_left + 1, i_right, diff_torque + w[min_i] * (mid - i_left)))
            return 1;
        while(i != -1){
            if(w[i] == w[previous]){
                previous = i;
                i = next[i];
                continue;
            }
            left[i_left] = w[i];
            next[previous] = next[i];
            if(balance(min_i, i_left + 1, i_right, diff_torque + w[i] * (mid - i_left)))
                return 1;
            next[previous] = i;
            previous = i;
            i = next[i];
        }
    }
    else {
        if(i_right == mid)
            return 0;
        i = next[min_i], previous = min_i;
        right[i_right] = w[min_i];
        if(balance(i, i_left, i_right + 1, diff_torque - w[min_i] * (mid - i_right)))
            return 1;
        while(i != -1){
            if(w[i] == w[previous]){
                previous = i;
                i = next[i];
                continue;
            }
            right[i_right] = w[i];
            next[previous] = next[i];
            if(balance(min_i, i_left, i_right + 1, diff_torque - w[i] * (mid - i_right)))
                return 1;
            next[previous] = i;
            previous = i;
            i = next[i];
        }
    }
    return 0;
}
 
 
int main(){
    int i;
    while(scanf("%d", &n) != EOF){
        for (i = 0; i < n; ++i)
            scanf("%d", &w[i]);
        qsort(w, n, sizeof(int), cmpfunc);
        for (i = 0; i < n - 1; ++i)
            next[i] = i + 1;
        next[n - 1] = -1;
        mid = (n - 1) / 2;
        if(!balance(0, 0, 0, 0))
            printf("N\n");
    }
    return 0;
}
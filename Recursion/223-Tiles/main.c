#include <stdio.h>

int L, M;
void print_center(int id, int l, int x, int y);
 
void tiles(int l, int x){
    if (x > (L - M))
        return;
    print_center(1, l, x, x);
    if (l > 2)
        tiles(l >> 1, x + (l >> 2));
}
 
void print_center(int id, int l, int x, int y){
    if (l == 2){
        printf("%d %d %d\n", id, x, y);
        return;
    }
    int half_l = l >> 1, quad_l = l >> 2;
    print_center(id, half_l, x, y);
    if(id != 1)
        print_center(3, half_l, x + quad_l, y + quad_l);
    if(id != 2)
        print_center(4, half_l, x - quad_l, y + quad_l);
    if(id != 3)
        print_center(1, half_l, x - quad_l, y - quad_l);
    if(id != 4)
        print_center(2, half_l, x + quad_l, y - quad_l);
}
 
int main(){
    scanf("%d %d", &L, &M);
    tiles(L, L >> 1);
    return 0;
}
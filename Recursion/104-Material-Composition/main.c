#include <stdio.h>
int DA, DB, DC, EA, EB, EC, FA, FB, FC;
int composeD(int na, int nb, int nc);
int composeE(int na, int nb, int nc);
int composeF(int na, int nb, int nc);
 
int composeD(int na, int nb, int nc){
    if (na == 0 && nb == 0 && nc == 0)
        return 1;
    if (na < 0 || nb < 0 || nc < 0)
        return 0;
    return composeD(na - DA, nb - DB, nc - DC) || composeE(na, nb, nc);
}
int composeE(int na, int nb, int nc){
    if (na == 0 && nb == 0 && nc == 0)
        return 1;
    if (na < 0 || nb < 0 || nc < 0)
        return 0;
    return composeE(na - EA, nb - EB, nc - EC) || composeF(na, nb, nc);
}
int composeF(int na, int nb, int nc){
    if (na == 0 && nb == 0 && nc == 0)
        return 1;
    if (na < 0 || nb < 0 || nc < 0)
        return 0;
    return composeF(na - FA, nb - FB, nc - FC);
}
 
void do_n_time(int n){
    if (n == 0)
        return;
    int a, b, c;
    scanf("%d%d%d", &a,&b,&c);
    if(composeD(a, b, c))
        printf("yes\n");
    else
        printf("no\n");
    do_n_time(n-1);
}
 
int main(){
    int n;
    scanf("%d%d%d%d%d%d%d%d%d", &DA, &DB, &DC, &EA, &EB, &EC, &FA, &FB, &FC);
    scanf("%d", &n);
    do_n_time(n);
}
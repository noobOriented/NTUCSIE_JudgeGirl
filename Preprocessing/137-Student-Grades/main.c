#include <stdio.h>
int tmp;

int main() {
    int n = 0, a;
    double gpa = 0, sum = 0;
    #ifdef HUNDRED
        while(scanf("%d", &a) != EOF) {
            printf("%d ", a);
            sum += a;
            n++;
        }
        printf("%.1lf\n", sum / n);
    #endif
    #ifdef APLUS
        while(scanf("%d", &a) != EOF) {
            if(a < 60){
                printf("F ");
                sum += 50;
            }else if(a < 63) {
                printf("C- ");
                gpa += 1.7;
                sum += 60;
            }else if(a < 67) {
                printf("C ");
                gpa += 2.0;
                sum += 65;
            }else if(a < 70) {
                printf("C+ ");
                gpa += 2.3;
                sum += 68;
            }else if(a < 73) {
                printf("B- ");
                gpa += 2.7;
                sum += 70;
            }else if(a < 77) {
                printf("B ");
                gpa += 3.0;
                sum += 75;
            }else if(a < 80) {
                printf("B+ ");
                gpa += 3.3;
                sum += 78;
            }else if(a < 85) {
                printf("A- ");
                gpa += 3.7;
                sum += 82;
            }else if(a < 90) {
                printf("A ");
                gpa += 4.0;
                sum += 87;
            }else {
                printf("A+ ");
                gpa += 4.3;
                sum += 95;
            }
            n++;
        }
        printf("%.1lf %.1lf\n", gpa / n, sum / n);
    #endif
    return 0;
}
#include <stdio.h>
#include <math.h>
 
int main(){
    long long int a, b, c, d, e, f;
    long long int i, j;
    scanf("%lld %lld %lld", &a, &b, &c);
    for (i = 0; i <= 100; i--) {
        if (i * i * i + a * i * i + b * i + c == 0) {
        	d = -i;
        	e = (a + i - sqrt((a + i)*(a + i) - 4 * (b + a*i + i*i)))/2;
        	f = a - d - e; // f >= e
        	break;
        }
        else if(-i * i * i + a * i * i - b * i + c == 0) {
        	d = i;
        	e = (a - i - sqrt((a - i)*(a - i) - 4 * (b - a*i + i*i)))/2;
        	f = a - d - e; // f >= e
        	break;        	
        }
    }
    if(d <= e)
    	printf("%d %d %d", d, e, f);
    else if(d <= f)
    	printf("%d %d %d", e, d, f);
    else
    	printf("%d %d %d", e, f, d);
    return 0;
}
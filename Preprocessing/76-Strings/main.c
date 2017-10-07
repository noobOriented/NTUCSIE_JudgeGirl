#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main() {
    int n = 0;
    char str[65][100];
    memset(str, '\0', sizeof(str));
    while(fgets(str[n], 100, stdin) != NULL)
        n++;
    qsort(str, n, 100, strcmp);
    for(int i = 0; i < n; ++i)
        printf("%s", str[i]);
    return 0;
}
#include <stdio.h>
#include <ctype.h>

char *str;

float parser() {
    if(isdigit(*str) || *str == '-') {
        float output;
        sscanf(str, "%f", &output);
        while(isdigit(*str) || *str == '.' || *str == '-')
            str++;
        str++;
        return output;
    } else if(*str == '(') {
        float a, b, p;
        str++;
        sscanf(str, "%f", &p);
        while(isdigit(*str) || *str == '.' || *str == '-')
            str++;
        str++;
        a = parser();
        b = parser();
        str++;
        return p * (a + b) + (1.f - p) * (a - b);
    }
    return 0;
}


int main() {
  	char buffer[256];
  	while(fgets(buffer, 256, stdin)){
        str = buffer;
        printf("%.2f\n", parser());
  	}
  	return 0;
}
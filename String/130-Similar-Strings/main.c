#include <stdio.h>
#include <string.h>

int similar_type1(char a[], char b[], int length) {
	int j = -1, flag = 0;
	for(int i = 0; i < length; ++i){
		if(a[i] != b[i]){
			if(j == -1)
				j = i;
			else if(!flag && a[i] == b[j] && a[j] == b[i])
				flag = 1;
			else
				return 0;
		}
	}
	if(j != -1 && !flag)
		return 0;
	return 1;
}

int similar_type2(char a[], char b[], int length) {
	int flag = 0;
	for(int i = 0; i < length; ++i){
		if(a[i] != b[i + flag]){
			if(!flag && a[i] == b[i+1])
				flag = 1;
			else
				return 0;
		}
	}
	return 1;
}

int similar(char a[], char b[]){
	int la = strlen(a), lb = strlen(b);
	if(la == lb)
		return similar_type1(a, b, la);
	else if(la + 1 == lb)
		return similar_type2(a, b, la);
	else if(lb + 1 == la)
		return similar_type2(b, a, lb);
	return 0;
}

int main() {
    int i, j, n;
    char a[81], b[81];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
    	scanf("%s", a);
    	scanf("%s", b);
    	if (similar(a, b))
    		printf("yes\n");
    	else
    		printf("no\n");
    }
	return 0;
}
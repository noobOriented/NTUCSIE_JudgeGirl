#include <stdio.h>

int main(void) {
	int x[4], y[4];
	int n, j, tmp, equalEdge, perpendicular;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		equalEdge = 1;
		perpendicular = 1;
		for(j = 0; j < 4; ++j)
			scanf("%d %d", &x[j], &y[j]);
		for(j = 3; j > 0; --j){
			x[j] -= x[0];
			y[j] -= y[0];
		}
		//判斷是否為平行四邊形，且對角線為 0, 1, 順序即為 0 -> 2 -> 1 -> 3
		if(x[2] + x[3] == x[1] && y[2] + y[3] == y[1]){
			tmp = x[1];
			x[1] = x[2];
			x[2] = tmp;
			tmp = y[1];
			y[1] = y[2];
			y[2] = tmp;
		}//判斷是否為平行四邊形，且對角線為 0, 3, 順序即為 0 -> 1 -> 3 -> 2
		else if(x[1] + x[2] == x[3] && y[1] + y[2] == y[3]){
			tmp = x[2];
			x[2] = x[3];
			x[3] = tmp;
			tmp = y[2];
			y[2] = y[3];
			y[3] = tmp;
		}//判斷是否為平行四邊形，且對角線為 0, 2, 順序即為 0 -> 1 -> 2 -> 3
		else if(x[1] + x[3] == x[2] && y[1] + y[3] == y[2]){
		}//非平行四邊形，放棄後續判斷
		else{
			equalEdge = 0;
			perpendicular = 0;
		}
		if(equalEdge)
			equalEdge = (x[1]*x[1] + y[1]*y[1]) == (x[3]*x[3] + y[3]*y[3]);
		if(perpendicular)
			perpendicular = (x[1]*x[3] + y[1]*y[3] == 0);
		if(equalEdge){
			if(perpendicular)
				printf("square\n");
			else
				printf("diamond\n");
		}else if(perpendicular)
			printf("rectangle\n");
		else
			printf("other\n");
	}
	return 0;
}
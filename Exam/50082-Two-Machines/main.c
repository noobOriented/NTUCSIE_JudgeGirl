#include <stdio.h>

int main() {
	int arrive, A, B, completeA = 0, completeB = 0;
	while(scanf("%d %d %d", &arrive, &A, &B) == 3) {
		if(arrive >= completeA) // A待機，等arrive
			completeA = arrive + A;
		else //A正在做，等他做完
			completeA = completeA + A;
		if(completeA >= completeB) // B待機，等A
			completeB = completeA + B;
		else //B正在做，等他做完
			completeB = completeB + B;
		printf("%d\n", completeB);
	}
	return 0;
}
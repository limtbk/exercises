#include <stdio.h>
#include <stdlib.h>

int main() {
	int a = 0;
	int b = 1;
	int sum = 0;
	while (!(b>4000000)) {
		int c = a+b;
		a = b;
		b = c;
		if (c%2==0) {
			sum+=c;
		}
	}
	printf("\n%d\n", sum);
	return 0;
}
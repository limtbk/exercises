#include <stdio.h>
#include <stdlib.h>

int isPrime(int num) {
	int a = num;
	int max = a;
	int i = 2;
	while (i <= max) {
		if (a%i==0) {
			a = a/i;
		} else {
			i = i + ((i==2)?1:2);
		}
		max = a / i;
	}
	int result = (a == num) || (2 == num);
	return result;
}

int main() {
	int num = 2;
	int result;
	for (int i = 1; i <= 10001; i++) {
		while (!isPrime(num)) {
			num = num + ((num==2)?1:2);
		}
		result = num;
		num = num + ((num==2)?1:2);
	}
	printf("%i\n", result);
	return 0;
}
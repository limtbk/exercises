#include <stdio.h>
#include <stdlib.h>

int main() {
	long long int a = (long long)600851475143;
	long long int max = a;
	long long int i = 2;

	while (i <= max) {
		if (a%i==0) {
			printf("\n%lli\n", i);
			a = a/i;
		}
		max = a / i;
		i = i + ((i==2)?1:2);
	}

	printf("\n%lli\n", a);
	return 0;
}
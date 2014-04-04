#include <stdio.h>
#include <stdlib.h>

int main() {
	long long int sqsum = 0;
	long long int sumsq = 0;

	for (int i = 1; i <= 100; i++) {
		sqsum += i*i;
		sumsq += i;
	}
	sumsq = sumsq*sumsq;
	printf("%lli\n", sumsq-sqsum);
	return 0;
}
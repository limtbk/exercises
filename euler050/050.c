#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a>b)?(a):(b))

#define MAX_NUM 1000000

int genPrime(char *notPrime) {
	notPrime[0] = 1;
	notPrime[1] = 1;
	int primeCount = 0;

	int current = 2;
	while (current<MAX_NUM) {
		while ((notPrime[current]) && (current<MAX_NUM)) {
			current += (current<=2)?1:2;
		}
		if (current<MAX_NUM) {
			primeCount++;
			int npindex = current*2;
			while (npindex<MAX_NUM) {
				notPrime[npindex] = 1;
				npindex +=current;
			}
			current += (current<=2)?1:2;
		}
	}
	return primeCount;
}

int main() {
	char *notPrime = malloc(MAX_NUM * sizeof(char));
	for (int i = 0; i < MAX_NUM; i++) {
		notPrime[i] = 0;
	}
	int primesCount = genPrime(notPrime);
	int	*primes = malloc(primesCount * sizeof(int));
	int j = 0;
	for (int i = 0; i < MAX_NUM; i++) {
		if (!notPrime[i]) {
			primes[j] = i;
			j++;
		}
	}

	int left = 0;
	int right = 0;

	int sum = 0;
	int maxSum = 0;
	int maxSumLeft = 0;
	int maxSumRight = 0;
	while ((sum + primes[right] < MAX_NUM) && (right < primesCount)) {
		sum += primes[right];
		if ((!notPrime[sum]) && (right - left > maxSumRight - maxSumLeft)) {
			maxSumLeft = left;
			maxSumRight = right;
			maxSum = sum;
		}
		right++;
	}
	right--;

	int willContinue = 1;
	while (willContinue) {
		willContinue = 0;
		sum -= primes[left];
		left++;
		while (right - left > maxSumRight - maxSumLeft) {
			sum -= primes[right];
			right--;
		}
		while ((sum < MAX_NUM) && (right < primesCount)) {
			willContinue = 1;
			if ((!notPrime[sum]) && (right - left > maxSumRight - maxSumLeft)) {
				maxSumLeft = left;
				maxSumRight = right;
				maxSum = sum;
			}
			right++;
			sum += primes[right];
		}
		
	}

	printf("[%i] %i = ", maxSumRight - maxSumLeft + 1, maxSum);
	for (int i = maxSumLeft; i <= maxSumRight; i++) {
		printf("%i", primes[i]);
		if (i<maxSumRight) {
			printf(" + ");
		}
	}
	printf("\n");

	free(notPrime);
	free(primes);
	return 0;
}
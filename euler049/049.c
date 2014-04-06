#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a>b)?(a):(b))
#define MIN(a, b) ((a<b)?(a):(b))
#define MAX_NUM 10000

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

int pow10(int p) {
	int result = 1;
	for (int i = 0; i < p; i++) {
		result = result*10;
	}
	return result;
}


int getDigit(int num, int digitNum) {
	return (num/pow10(digitNum))%10;
}

int	setDigit(int num, int digitNum, int digit) {
	return num + ((digit%10) - getDigit(num, digitNum))* pow10(digitNum);
}

int permuteNumberWithArray(int num, int *parr) {
	int n = 0;
	for (int i = 0; i < 4; i++) {
		n = setDigit(n, i, getDigit(num, parr[i]));
	}
	return n;
}

int delta(int a, int b) {
	return MAX(a, b) - MIN(a, b);
}

void check3delta(int *arr, int count) {
	for (int i = 0; i < count-2; i++) {
		for (int j = i+1; j < count-1; j++) {
			for (int k = j+1; k < count; k++) {
				// printf("%i, %i, %i\n", i, j, k);
				if ((delta(arr[i], arr[j])==delta(arr[j], arr[k])) || (delta(arr[i], arr[k])==delta(arr[j], arr[k])) || (delta(arr[i], arr[k])==delta(arr[i], arr[j]))) {
					printf("%i, %i, %i\n", arr[i], arr[j], arr[k]);
				}
			}			
		}
	}
}

int main() {
	char *notPrime = malloc(MAX_NUM * sizeof(char));
	char *marked = malloc(MAX_NUM * sizeof(char));
	for (int i = 0; i < MAX_NUM; i++) {
		notPrime[i] = 0;
	}
	int primesCount = genPrime(notPrime);
	memcpy(marked, notPrime, MAX_NUM * sizeof(char));
	int	*primes = malloc(primesCount * sizeof(int));
	int j = 0;
	int f4index = 0;
	for (int i = 0; i < MAX_NUM; i++) {
		if (!notPrime[i]) {
			primes[j] = i;
			if (!f4index && (i>=1000)) {
				f4index = j;
			}
			j++;
		}
	}

	// printf("%i %i\n", f4index, primes[f4index]);

	int *permuteArr = malloc(24*4*sizeof(int));
	int permuteNumber = 0;
	for (int i0 = 0; i0 < 4; i0++) {
		for (int i1 = 0; i1 < 4; i1++) {
			if (i0 != i1) {
				for (int i2 = 0; i2 < 4; i2++) {
					if ((i0 != i2) && (i1 != i2)) {
						for (int i3 = 0; i3 < 4; i3++) {
							if ((i0 != i3) && (i1 != i3) && (i2 != i3)) {
								permuteArr[permuteNumber*4+0] = i0;
								permuteArr[permuteNumber*4+1] = i1;
								permuteArr[permuteNumber*4+2] = i2;
								permuteArr[permuteNumber*4+3] = i3;
								// printf("%i - %i %i %i %i\n", permuteNumber, i0, i1, i2, i3);
								permuteNumber++;
							}
						}
					}
				}
			}
		}
	}

	for (int i = f4index; i < primesCount; i++) {
		int num = primes[i];
		int *narr = malloc(24*sizeof(int));
		int narri = 0;
		if (!marked[num]) {
			for (int j = 0; j < 24; j++) {
				int n = permuteNumberWithArray(num, &permuteArr[j*4]);
				if (!marked[n] && (n>=1000)) {
					narr[narri] = n;
					narri++;
					// printf("%i, ", n);
				}
				marked[n] = 1;
			}
		}
		if (narri>0) {
			// printf("\n");
		}
		if (narri>2) {
			check3delta(narr, narri);
		}
		free(narr);
	}

	free(marked);
	free(notPrime);
	free(primes);
	return 0;
}
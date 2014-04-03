#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a>b)?(a):(b))

int lcm(int a, int b) {
	int result = 1;
	int max = MAX(a, b);
	int ta = a;
	int tb = b;
	int i = 2;
	while (i <= max) {
		if ((ta%i==0) || (tb%i==0)) {
			if (ta%i==0)
				ta = ta/i;
			if (tb%i==0)
				tb = tb/i;
			result = result*i;
		} else {
			i = i + ((i==2)?1:2);
		}
		max = MAX(ta, tb) / i;
	}
	result = result * ((ta==tb)?ta:ta*tb);
	return result;
}

int gcd(int a, int b) {
	int result = (a*b)/lcm(a, b);
}

int main() {
	int r = 1;
	for (int i = 1; i <= 20; i++) {
		r = lcm(r, i);
	}
	printf("%i\n", r);
	return 0;
}
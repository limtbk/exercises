#include <stdio.h>
#include <stdlib.h>

int isPalindrome(int num) {
	int result = 0;
	int tmp = num;
	int antiNum = 0;
	if (tmp%10) {
		while (tmp && (!result)) {
			antiNum = antiNum*10 + tmp%10;
			result = result || (tmp == antiNum);
			tmp = tmp/10;
			result = result || (tmp == antiNum);
		}
	}
	return result;
}

int main() {
	int max = 0;
	for (int i = 999; i > 99; i--)
		for (int j = i; j > 99; j--) {
			int num = i*j;
			if (isPalindrome(num)) {
				if (max < num) {
					max = num;
				}
			}
		}
	printf("%i\n", max);
	return 0;
}
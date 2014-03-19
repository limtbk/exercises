#include <stdio.h>
#include <stdlib.h>

int isLeapYear(int year) {
	if (year % 100) {
		if (year % 4) {
			return 0;
		} else {
			return 1;
		}
	} else {
		if (year % 400) {
			return 0;
		} else {
			return 1;
		}
	}
}

int daysForMonth(int year, int month) {
	int leapMonths[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
	int nonLeapMonths[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (isLeapYear(year)) {
		return leapMonths[month];
	} else {
		return nonLeapMonths[month];
	}
}

int main() {

	int year = 1900;
	int month = 0; //jan
	int dow = 0; //monday
	int count = 0;

	while (year<2001) {
		//calculate
		if ((dow == 6) && (year > 1900)) {
			// printf("%i %i %i\n", year, month, dow);
			count++;
		}

		dow = (dow + daysForMonth(year, month)) % 7;

		month = (month+1)%12;
		if (0 == month)
		{
			year++;
		}
	} 

	printf("%i/n", count);
	return 0;
}
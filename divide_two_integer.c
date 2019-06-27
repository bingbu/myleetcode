/*
 * https://leetcode.com/problems/divide-two-integers/
 * Reference - https://www.cnblogs.com/Dinging006/p/9382657.html
 */
#include <stdio.h>
#include <stdbool.h>

int divide(int dividend, int divisor){
	long long dividend_low, divisor_high;
	unsigned long long low, high;
	int i;
	unsigned int quotient = 0;
	bool neg = false;

	if (divisor == 1)
		return dividend;

	if (divisor == -1 && dividend != -2147483648)
		return dividend * (-1);

	if (dividend == -2147483648 && divisor == -1)
		return 2147483647;

	if (divisor == -2147483648 && dividend != -2147483648)
		return 0;
	if (divisor == dividend == -2147483648)
		return 1;

	dividend_low = dividend;
	divisor_high = divisor;
	if (dividend < 0) {
		dividend_low = dividend + 0xffffffff00000000;
		dividend_low = ~(dividend_low) + 0x1;
		dividend_low &= (0x100000000 - 1);
		neg = !neg;
	}

	if (divisor < 0) {
		divisor_high = divisor + 0xffffffff00000000;
		divisor_high = ~(divisor_high) + 0x1;
		divisor_high &= (0x100000000 - 1);
		neg = !neg;
	}

	low = dividend_low;
	high = (unsigned long long)divisor_high << 32;

	for ( i = 0; i < 32; i++) {
		quotient <<= 1;
		low = low << 1;
		if ((low >> 32) >= (high >> 32)) {
			low = low - high + 0x1;
			quotient += 0x1;
		}
	}

	if (neg)
		quotient *= -1;

	return quotient;
}

int main(int argc, char *argv[])
{
	printf("%d\n", divide(64, 3));
	printf("%d\n", divide(-3002 , -3));
	printf("%d\n", divide(-2147483648 , -3));
	printf("%d\n", divide(7, -3));
	printf("%d\n", divide(-2147483648, -1109186033));
	printf("%d\n", divide(-2147483648, -2147483648));
	printf("%d\n", divide(-2147483647, -2147483648));

	return 0;
}


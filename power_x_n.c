/*
 * https://leetcode.com/problems/powx-n/
 */
#include <stdio.h>
#include <stdlib.h>

double myPow(double x, int n)
{
	int i;
	double ret = 1.000;

        if (n==0)
		return 1;

	/* x^n = x^2 * x ^ (n/2):
	 - n is even number, x^n = (x^2) ^ (n/2)
	 - n is odd number, x^n = (x^2) ^ (n/2) * x
	 */
        for(i = n; i; i /= 2) {
        	if (i & 0x1)
			ret *= x;
		x *= x;
        }

	if (n < 0)
		return 1/ret;

	return ret;
}
int main(int argc, char *argv[])
{
        printf("%lf\n", myPow(2.00000, 10));
        printf("%lf\n", myPow(0.00001, 2147483647));
        printf("%lf\n", myPow(2.00000, -2));
	return 0;
}

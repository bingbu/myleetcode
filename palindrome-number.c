/*
 * https://leetcode.com/problems/palindrome-number/
 */

#include <stdio.h>
#include <stdbool.h>

static long long int reverse(int num)
{
	int i;
	/*Be careful the data range of the reserved value
	it is likely out of the range the int32 */
	long long int res;

	res = 0;
	for (i = 0; i < 12; i++)
	{
		res *= 10;
		res += num % 10;
		num = num / 10;
		if (!num)
			break;
	}

	return res;
}
bool isPalindrome(int x)
{
	unsigned int s;
	int tmp, xl, xh;
	int i;

	if (x < 0)
		return false;

	s = 0;
	tmp = x;
	do {
		s++;
		tmp /=10;
	} while (tmp);

	if (s == 1 || !(x / 10))
		return true;

	xh = x;
	tmp = 1;
	for (i = 0; i < s / 2; i++) {
		tmp *= 10;
		xh /= 10;
	}
	xl = x - xh * tmp;
	if (s % 2)
		xh /= 10;

	if (reverse(xh) == xl)
		return true;

	return false;
}


int main(int argc, char *argv[])
{
	int num;

	printf("Please input an integer:\n");
	scanf("%d", &num);
	if (isPalindrome(num))
		printf("Yes!\n");
        else
		printf("No!");

	return 0;
}

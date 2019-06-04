/*
* Edit in DevCpp 5.11 with TDM-GCC 4.9.2 32bit
*/
#include <stdio.h>

long long int reverse(int num)
{
	int i;
	/*Be careful the data range of the reserved value
	it is likely out of the range the int32 */
	long long int res;

	printf("%d\n", num);
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

int main(int argc, char *argv[])
{
	int num;
	printf("please input your num:\n");
	scanf("%d", &num);
	printf("%lld", reverse(num));
}

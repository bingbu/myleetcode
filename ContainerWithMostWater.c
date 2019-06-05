/*
 * https://leetcode.com/problems/container-with-most-water/
 */
#include <stdio.h>

#define MIN(a, b)  			((a) > (b) ? (b) : (a))
#define	ARRAY_SIZE(arr) 	(sizeof(arr) / sizeof((arr)[0]))

int maxArea(int* height, int heightSize)
{
	int cap = 0;
	int i, j;
	int ai, aj, con, res;
	
	if (heightSize < 2)
		return 0;

	res = 0;
	for (i = 1; i < heightSize; i++)
	{
		ai = *(height + i);
		for (j = 0; j < i; j++)
		{
			printf("%d %d\n", ai, aj);
			aj = *(height + j);
			con = (MIN(ai, aj)) * (i - j);
			res = (res < con) ? con : res;
		}
	}
	return res;
}

int maxArea_better(int* height, int heightSize)
{
	int cap = 0;
	int i, j;
	int ai, aj, con, res;
	
	if (heightSize < 2)
		return 0;
	
	i = 0;
	j = heightSize - 1;
	res = 0;
	while (i < j)
	{
		ai = *(height + i);
		aj = *(height + j);
		con = (MIN(ai, aj)) * (j - i);
		res = (res < con) ? con : res;
		if (ai < aj)
			i++;
		else
			j--;
	}
	return res;
}


int main(int argc, char *argv[])
{
	int size;
	int array[] = {1,8,6,2,5,4,8,3,7};
	size = maxArea_better(array, ARRAY_SIZE(array));
	printf("%d\n", size);
	return 0;
}

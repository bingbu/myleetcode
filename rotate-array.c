/*
 * https://leetcode.com/problems/rotate-array/
 */
#include <stdio.h>
#include <stdlib.h>

void rotate(int* nums, int numsSize, int k)
{
	int i, shift;

	shift = k % numsSize;
	int *tmp = malloc(shift * sizeof(int));
	if (!tmp)
		return;

	for (i = 0; i < shift; i++)
                *(tmp + i) = nums[numsSize - shift + i];

	for (i = numsSize - 1 ; i >= shift; i--)
		*(nums + i) = nums[i - shift];

	for (i = 0; i < shift; i++)
                nums[i] = *(tmp + i);
}

int main(int argc, char *argv[])
{
	int i;
	unsigned int nums[] = {1,2,3,4,5,6,7,8,9,10};

	int numsSize = sizeof(nums)/sizeof(int);
	rotate(nums, numsSize, 5);
	for (i = 0; i < numsSize; i++)
                printf("%d ", nums[i]);

	return 0;
}

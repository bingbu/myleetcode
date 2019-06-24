/**
 * https://leetcode.com/problems/two-sum/
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

int* twoSum(const int* nums, int numsSize, int target, int* returnSize)
{
	int i, j;
	int *res;

	res = NULL;
	for (i = 0; i < numsSize - 1; i++) {
		for (j = i + 1; j < numsSize; j++) {
			if (nums[i] + nums[j] == target) {
				res = malloc(2 * sizeof(int));
				if (!res)
					return NULL;
				res[0] = i;
				res[1] = j;
				break;
			}
		}
	}

	*returnSize = 2;
	return res;
}

int main(int argc, char *argv[])
{
	int i;
	int nums[] = {-2, 7, 11, 15, 3, 45, 2, 3, 4, 13, 12, 35, 69, 0};
	int target = 67;
	int returnSize;
	int *res;

	res = twoSum(nums, sizeof(nums)/sizeof(int), target, &returnSize);
	if (!res) {
		printf("NOT FOUND\n!!!!");
		return -1;
	}

	for (i = 0; i < returnSize; i++) {
		printf("%d ", res[i]);
	}

	free(res);
	printf("\n");

	return 0;
}

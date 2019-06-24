/*
 * https://leetcode.com/problems/3sum-closest/
 */
#include <stdio.h>

#define abs(x)    ((x) < 0 ? (-1 * (x)) : (x))

int threeSumClosest(int* nums, int numsSize, int target)
{
	int i, j, k, sum, ret;
	unsigned int gap;

	i = 0;
	gap = abs(nums[0] + nums[1] + nums[2] - target);
	ret = nums[0] + nums[1] + nums[2];
	while (i < numsSize) {
		j = 0;
		k = numsSize - 1;
		while (j < i && i < k) {
			sum = nums[i] + nums[j] + nums[k];
			if (abs(sum - target) < gap) {
				gap = abs(sum - target);
				ret = sum;
			}

			if (k - 1 == i) {
				k = numsSize - 1;
				j++;
				continue;
			}

			k--;
		}
		i++;
	}
	return ret;
}

int main(int argc, char *argv[])
{
	int nums[] = {1,2,4,8,16,32,64,128};

	printf("%d\n", threeSumClosest(nums, sizeof(nums)/sizeof(nums[0]), 82));
	return 0;
}


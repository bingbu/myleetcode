/*
 * leetcode 26
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int removeDuplicates(int* nums, int numsSize) {
	int i, j, t, n;
	int *p = nums;

	if (!nums)
		return 0;

	n = numsSize;
	t = nums[0];

	for (i = 1, j = 0; i < numsSize; i++){
		if (nums[i] == t) {
			n--;
		}
		else {
			t = nums[i];
			nums[++j] = t;
		}
	}

	return n;
}
int main(int argc, char *argv[]) {
	int input[10] = {1, 1, 1, 2, 2, 2, 2, 2, 4, 4};
	int i;
	for (i = 0; i < 10; i++){
		printf("%d ", input[i]);
	}
	printf("\n");

	int size = removeDuplicates(input, 10);
	printf("length shrinked to %d\n", size);
	for (i = 0; i < size; i++){
		printf("%d ", input[i]);
	}
	printf("\n");
	return 0;
}

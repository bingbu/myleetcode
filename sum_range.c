#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct group {
	int begin;
	int end;
};

char** summaryRanges(int* nums, int numsSize, int* returnSize) {
	int i, j, grp_num = 1;

	if (!nums || !returnSize || numsSize == 0) return NULL;

	if (numsSize == 1) {
		char **s = malloc(sizeof(char *));
		s[0] = malloc(256 * sizeof(char));
		sprintf(s[0], "%d", nums[0]);
		printf("%s \n", s[0]);
		*returnSize = 1;
		return s;
	}

	for (i = 1; i < numsSize; i++ ){
		if (nums[i] - nums[i-1] != 1){
			grp_num++;
		}
	}

	printf("grp_num = %d \n", grp_num);
	*returnSize = grp_num;

	struct group *record = malloc(grp_num * sizeof(struct group));
	char **result = malloc(grp_num * sizeof(char *));

	for (j = 0; j < grp_num; j++ ) {
		result[j] = malloc(256 * sizeof(char));
	}
	record[0].begin = nums[0];
	for (i = 1, j = 0; i < numsSize, j < grp_num; i++ ) {
		if (nums[i] - nums[i-1] != 1){
			record[j].end = nums[i-1];
			j++;
			if (j != grp_num)
				record[j].begin = nums[i];
		}
	}

	for (j = 0; j < grp_num; j++ ) {
		if (record[j].begin == record[j].end)
			sprintf(result[j], "%d", record[j].begin);
		else
			sprintf(result[j], "%d->%d", record[j].begin, record[j].end);
	}

	return (char **)result;
}

int main(int argc, char *argv[]) {
	//int test[11] = {-1, 0, 3, 4, 5, 7, 8, 9, 10, 12, 13};
	int test[1] = {-1};
	int returnSize;
	char **res;
	int i;
	for (i = 0; i < sizeof(test)/sizeof(int); i++ ){
		printf("%d ", test[i]);
	}
	printf("\n");
	res = summaryRanges(test, sizeof(test)/sizeof(int), &returnSize);
	printf("Dump\n");
	for (i = 0; i< returnSize; i++)
		printf("%s \n", res[i]);

}

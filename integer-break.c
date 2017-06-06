/*
 * leetcode 343
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* for any num larger than 4
 * 2*i > 9 <--> 3 * (i - 3) > i
 *
 *
 */
int integerBreak(int n) {
	switch(n) {
	case 2:
		return 1;
	case 3:
		return 2;
	case 4:
		return 4;
	case 5:
		return 6;
	case 6:
		return 9;
	default:
		return 3 * integerBreak(n - 3);
	}
}

int main(int argc, char *argv[]) {
	int n;
	printf("please help input the value:\n");
	scanf("%d", &n);;
	printf("%d\n", integerBreak(n));
}

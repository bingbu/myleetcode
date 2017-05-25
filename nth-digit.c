/*
 * leetcode 400
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findNthDigit(int n) {
	long int s, i, t;
	char str[128];
	char res[2];
	res[1] = '\0';
	s = i = 1;
	while (n > 9 * s * i) {
		n -= 9 * s * i;
		s = s * 10;
		i++;
	}
	t = s + (n - 1)/i;
	sprintf(str, "%ld", t);
	n = n % i;
	if (n == 0) n = i;
	res[0] = str[n-1];
	return atoi(res);
}

int main(int argc, char *argv[]) {
	int n, s;
	printf("pls specify the n:\n");
	scanf("%d", &n);
	s = findNthDigit(n);
	printf("%d\n", s);
	return 0;
}

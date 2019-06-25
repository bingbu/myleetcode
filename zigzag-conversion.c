/*
 * https://leetcode.com/problems/zigzag-conversion/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *convert(char *s, int numRows)
{
	char *ret, *tmp;
	unsigned int *index;

	int len = 0;
	int i, j, k = 0;
        int x = 2 * (numRows - 1);

	if (numRows == 1)
		return s;

        tmp = s;
	while(*tmp++ != '\0')
		len++;

	ret = malloc(len + 1);
	index = malloc((len + 1) * sizeof(int));
	if (!index)
		return NULL;

	for (i = 0; i < numRows; i++) {
		for (j = 0; j + i < len; j += x) {
			index[k] = j + i;
			k++;
			if (k >= len)
				break;
			if (i != 0 && i != numRows - 1 && j + x - i < len) {
				index[k] = j + x - i;
				k++;
			}
		}
	}

	for (i = 0; i < len; i++)
		ret[i] = s[index[i]];

	ret[len] = '\0';
	return ret;
}

int main(int argc, char *argv[])
{
	printf("%s\n", convert("AB", 1));
	printf("%s\n", convert("PAYPALISHIRING", 3));
	printf("%s\n", convert("PAYPALISHIRING", 4));

	return 0;
}


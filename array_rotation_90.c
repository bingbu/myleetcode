/*
* Edit in DevCpp 5.11 with TDM-GCC 4.9.2 32bit
*/
#include <stdio.h>
#include <stdlib.h>

void rotation(const int *array, int row, int col)
{
	int i, j;
	int r, c;
	int *temp;
	
	temp = malloc(sizeof(int) * row * col);
	if (!temp)
		return;

	for (i = 0; i < col; i++) {
		for (j = 0; j < row; j++) {
			//row is very important
			*(temp + i * row + j)  = *(array + (row - 1 - j) * col + i);
			printf("%d\t", *(temp + i * row + j));
		}
		printf("\n");
	}

	free(temp);
	return;
}

int main(int argc, char *argv[])
{
	int row, col, len;
	int i, j;
	int *array, *start;
	printf("please input the row and col (not larger than 32):\n");
	scanf("%d%d", &row, &col);
	
	len = row * col;
	printf("array[%d][%d] len %d:\n", row, col, len);
	array = malloc(sizeof(int) * row * col);
	if (!array)
		return -1;

	start = array;
	for (i = 0; i < len; i++)
		*start++ = i;
	
	start = array;
	printf("input...\n");
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
			printf("%d\t", *start++);
		printf("\n");
	}

	printf("output...\n");
	rotation(array, row, col);	
	free(array);
}

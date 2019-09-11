/*
* ICG RCG test: image rotation and flip
*/
#include <stdio.h>
#include <stdlib.h>

int rotate_flip(int *buf, unsigned int w, unsigned int h)
{
	int *tmp, *dest;
	int *last;
	int pos, i, j;

	unsigned int size = w * h;
	dest = malloc(sizeof(int) * size);
	if (!tmp)
		return -1;

	tmp = dest;
	last = buf + size - 1;
	pos = 0;
	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++)
			*tmp++ = *(last - i - j * w);
	}
	memcpy(buf, dest, size * sizeof(int));
}


#define WIDTH 	4
#define HEIGHT 	6
#define SIZE	24
int main(int argc, char* argv[])
{
	unsigned int i;
	int array[SIZE] = {};

	for (i = 0; i < SIZE; i++)
		array[i] = i + 1;

	printf("\nBefore:\n");
	for (i = 0; i < SIZE; i++)
		printf("%d ", array[i]);
	rotate_flip(array, WIDTH, HEIGHT);

	printf("\nAfter:\n");
	for (i = 0; i < SIZE; i++)
		printf("%d ", array[i]);

}

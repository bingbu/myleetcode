#include <stdio.h>

#define SIZE  5
int array[SIZE] = {5, 5, 4, 4, 2};

void dump(int *tmp) {
	int i;
	for (i = 0; i < SIZE; i++) {
		printf("%d ", tmp[i]);
	}
	printf("dump end\n");
}

int main() {
	int tmp[10], tmp1[10];
	int i, j, s;
	for (i = 0; i < SIZE; i++) {
		tmp[i] = array[i] * (i + 1);
	}

	dump(tmp);

	for (i = 0; i < SIZE - 1; i++) {
		for (j = 0; j < SIZE - i - 1 ; j++) {
			if ( tmp[j] > tmp[j + 1]) {
				printf("swap %d with %d\n", j, j+1);
				s = tmp[j];
				tmp[j] = tmp[j + 1];
				tmp[j + 1] = s;
				s = array[j];
				array[j] = array[j + 1];
				array[j + 1] = s;
			}
		}
	}

	dump(tmp);
	dump(array);

	return 0;
}

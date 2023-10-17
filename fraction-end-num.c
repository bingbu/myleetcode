#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	unsigned long long int s = 1;
	unsigned int n = 200;

	if (argc > 1)
		n = atoi(argv[1]);

	printf("input n = %u\n", n);
	if (n > 10000) {
		printf("%d is too large, exit.\n", n);
		return 0;
	}
		
	while (n > 0) {
		s *= n;
		printf("s = %llu n = %u\n", s, n);
		while (!(s % 10))
			s /= 10;

		s %= 100000000;
		n--;
	}
	
	printf("result = %llu\n", s);

	return 0;
}

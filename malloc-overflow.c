#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[]) {
	char *p = malloc(1024 - 8);
	char *p2 = malloc(1024 - 8);

	memset(p, 'A', 1024-8);
	memset(p2, 'B', 1024-8);

	p[1024 - 8] = '\0';

	free(p2);
}

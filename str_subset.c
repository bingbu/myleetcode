/*Given a string, which can be split into many sub string with character ','
* programming to return the nth sub string.
* For example-  input: “a,bb,ccc,dddd”, n = 1, result = bb
*/
#include <stdio.h>
#include <stdbool.h>

char *s_strsep(char **str, const char *delim)
{
	char *s;
	int c, sc;
	char *tok;
	const char *sp;

	s = *str;
	if (s == NULL)
		return NULL;

	for (tok = s;;) {
		c = *s++;
		sp = delim;
		do {
			if (c == (sc = *sp++)) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				*str = s;
				return tok;
			}
		} while (sc != 0); //this loop is needed to return last string
	}
}

char *substr(char **str, const char *delim, int index) {
	int i = 0;
	char *s;

	while((s = s_strsep(str, delim)) != NULL)
	{
		if (i++ == index)
			return s;
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	char str[] = "aa,oobb,dfccc,dfd";
	char *buf = str;
	char *s;

	if ((s = substr(&buf, ",", 2)) != NULL)
		printf("%s", s);
	else
		printf("not found\n");

	return 0;
}

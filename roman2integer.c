/*
 * https://leetcode.com/problems/roman-to-integer/
 */
#include <stdio.h>

static int r2v (char str)
{
	int v;
	switch(str) {
		case 'I':
			v = 1;
			break;
		case 'V':
			v = 5;
			break;
		case 'X':
			v = 10;
			break;
		case 'L':
			v = 50;
			break;
		case 'C':
			v = 100;
			break;
		case 'D':
			v = 500;
			break;
		case 'M':
			v = 1000;
			break;
		default:
			printf("Wrong Input!\n");
			break;
	}
	return v;
}
int romanToInt(const char *s)
{
	int val = 0;
	unsigned char first = 1;
	while(*s != '\0') {
		val += r2v(*s);
		if (!first) {
			r2v(*(s-1));
			if (r2v(*s) > r2v(*(s-1))) {
				val -= 2 * r2v(*(s-1));
			}
		}
		s++;
		first = 0;
	};
	return val;
}

int main(int argc, char *argv[])
{
	printf("%d\n", romanToInt("MCMXCIV"));
}


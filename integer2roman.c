/*
 * https://leetcode.com/problems/integer-to-roman/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char table[4][10][5] = {
        {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
        {"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
        {"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
        {"M", "MM", "MMM"},
};

/*can not use the global buffer for roman
 * char roman[16];
 */

char *intToRoman(int num)
{
        int i = 3;
        int g = 1000;
        int j;
        char s[5] = "";

        char *roman;
        roman = malloc(16);
        if (!roman)
                return NULL;
        strncpy(roman, "", 1);

        while (i >= 0)
        {
                j = num / g;
                num -= j * g;
                g /= 10;
                if (j)
                        strcat(roman, table[i][j - 1]);
                i--;
        }
        return roman;
}

int main(int argc, char *argv[])
{
	printf("%s\n", intToRoman(1994));

	return 0;
}

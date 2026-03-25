/*
Given two strings, str1, and str2, where str1 contains exactly one character more than str2, find the indices of the characters in str1 that can be removed to make str1 equal to str2. Return the array of indices in increasing order. If it is not possible, return the array [-1]. 
Note: Use 0-based indexing.
Example
str1 = "abdgggda" str2 = "abdggda"
Any "g" character at positions 3, 4, or 5 can be deleted to obtain str2. Return [3, 4, 5].
*/

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

/*
 * Complete the 'getRemovableIndices' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. STRING str1
 *  2. STRING str2
 */
/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
int* getRemovableIndices(char* str1, char* str2, int* result_count) {
    int n = strlen(str1);
    int m = strlen(str2);
    int *res;
    
    if (n != m + 1) {
        int *a = (int*)malloc(sizeof(int));
        if (!a)
            return NULL;
        *a = -1;
        *result_count = 1;
        return a;
    }
    
    bool *left_ok = (bool *)malloc(n * sizeof(bool));
    left_ok[0] = true;
    for (int i = 1; i < n; i++) {
        left_ok[i] = left_ok[i - 1] && (str1[i - 1] == str2[i - 1]);
    }
    
    bool *right_ok = (bool *)malloc(n * sizeof(bool));
    right_ok[n - 1] = true;
    for (int i = n - 1; i > 0; i--) {
        right_ok[i - 1] = right_ok[i] && (str1[i] == str2[i - 1]);
    }
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (left_ok[i] && right_ok[i])
            count++;
    }
    
    if (count == 0) {
        free(left_ok);
        free(right_ok);
        *result_count = 1;
        res = (int*)malloc(sizeof(int));
        *res = -1;
        return res;
    }
    
    res = (int*)malloc(sizeof(int) * count);
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (left_ok[i] && right_ok[i])
            res[idx++] = i;
    }
    
    free(left_ok);
    free(right_ok);
    *result_count = count;
    
    return res; 
}

int main()
{
    char* str1 = readline();

    char* str2 = readline();

    int result_count;
    int* result = getRemovableIndices(str1, str2, &result_count);

    for (int i = 0; i < result_count; i++) {
        printf("%d", *(result + i));

        if (i != result_count - 1) {
            printf("\n");
        }
    }

    printf("\n");

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = (char*)malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        char* tmp = (char*)realloc(data, alloc_length);
        if (!tmp) {
            free(data);
            return NULL;
        }
        data = tmp;
    }

    if (data_length > 0 && data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        char* shrunk = (char*)realloc(data, data_length);
        if (shrunk) data = shrunk;
    } else {
        char* grown = (char*)realloc(data, data_length + 1);
        if (grown) {
            data = grown;
            data[data_length] = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

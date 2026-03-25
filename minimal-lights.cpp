/*
Question 2 – Minimum streets lights：
Problem Statement -: Street Lights are installed at every position along a 1-D road of length n. 
Locations[] (an array) represents the coverage limit of these lights. 
The ith light has a coverage limit of locations[i] that can range from the position max((i – locations[i]), 1) to min((i + locations[i]), n ) (Closed intervals). Initially all the lights are switched off. 
Find the minimum number of fountains that must be switched on to cover the road. 

Question 6 – Disk Space Analysis：
Problem Statement -:  You are given an array, You have to choose a contiguous subarray of length ‘k’, 
and find the minimum of that segment, return the maximum of those minimums.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <climits>
#include <cstdlib>
#include <cstring>
using namespace std;

class Solution {
public:
        int minLights(int n, vector<int>& locations) {
                vector<int> coverage(n + 1, 0);
                for (size_t i = 0; i < locations.size(); i++) {
                        int left = max((int)(i + 1 - locations[i]), 1);
                        int right = min((int)(i + 1 + locations[i]), n);
                        coverage[left]++;
                        if (right + 1 <= n)
                                coverage[right + 1]--;
                }
                for (size_t i = 1; i <= n; i++)
                        coverage[i] += coverage[i - 1];
                
                int count = 0;
                for (size_t i = 1; i <= n; i++) {
                        if (coverage[i] == 0)
                                count++;
                }
                return count;
        }

        /*
        Question 6 – Disk Space Analysis：
        Problem Statement -:  You are given an array, You have to choose a contiguous subarray of length ‘k’, 
        and find the minimum of that segment, return the maximum of those minimums.
        */
        int minimalofSubArrays(vector<int>& arr, int k) {
                int n = arr.size();
                vector<int> left(n), right(n);
                stack<int> st;
                // 左边第一个更小元素
                for (int i = 0; i < n; i++) {
                        while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();
                        left[i] = st.empty() ? -1 : st.top();
                        st.push(i);
                }
                while (!st.empty()) st.pop();
                // 右边第一个更小元素
                for (int i = n - 1; i >= 0; i--) {
                        while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();
                        right[i] = st.empty() ? n : st.top();
                        st.push(i);
                }
                int result = INT_MIN;
                for (int i = 0; i < n; i++)
                        if (right[i] - left[i] - 1 >= k)
                                result = max(result, arr[i]);
                return result;
        }

        int minimalofSubArraysII(vector<int>& arr, int k) {
                int n = arr.size(), result = INT_MIN;
                for (int i = 0; i <= n - k; i++) {
                        int win_min = *min_element(arr.begin() + i, arr.begin() + i + k);
                        result = max(result, win_min);
                }
        return result;
        }

        /*
        Question 10 : Minimum Occurrence
        Problem Statement – Given a sting , return the character that appears the minimum number of times in the string.
        The string will contain only ascii characters, from the ranges (“a”-”z”,”A”-”Z”,0-9), and case matters .
        If there is a tie in the minimum number of times a character appears in the string return the character that appears first in the string.
        */
        char minimalOccurrence(string S) {
                size_t freq[128] = {0};
                size_t n = S.size();

                if (n == 0)
                        return '\0';

                for (size_t i = 0; i < n; i++) {
                        char c = S[i];
                        freq[c]++;
                }
                
                char minChar = '\0';
                size_t minFreq = SIZE_MAX;
                for (size_t i = 0; i < n; i++) {
                        char c = S[i];
                        if (freq[c] && freq[c] < minFreq) {
                                minFreq = freq[c];
                                minChar = c;
                        }
                }

                return minChar;
        }

        size_t calculateOneBits(size_t n) {
                size_t count = 0;
                while (n) {
                        count++;
                        n &= (n - 1);
                }
                return count;
        }
        int* maxSlidingWindow(int* nums, int n, int k, int* returnSize) {
                int *result = malloc(sizeof(int) * (n - k + 1));
                int *dq = malloc(sizeof(int) * n);

                int l = 0, r = 0;
                int idx = 0;

                for (int i = 0; i < n; i++) {

                        // 移除过期元素
                        if (l < r && dq[l] <= i - k)
                                l++;

                        // 保持单调递减
                        while (l < r && nums[dq[r - 1]] < nums[i])
                                r--;

                        dq[r++] = i;

                        if (i >= k - 1)
                                result[idx++] = nums[dq[l]];
                }

                *returnSize = idx;
                return result;
        }
};

int main() {
        Solution s;
        vector<int> locations = {1, 2, 1, 0, 1};
        int n = 5;
        cout << "Minimum number of lights needed: " << s.minLights(n, locations) << endl;

        vector<int> arr = {10, 20, 30, 50, 10, 70, 30};
        int k = 3;
        cout << "Maximum of minimums of subarrays of size " << k << ": " << s.minimalofSubArrays(arr, k) << endl;

        string S = "hello world hh";
        cout << "Character with minimum occurrence: " << s.minimalOccurrence(S) << endl;

        int num = 5846472; // Binary of 5846472 is 1011001010110100001000, which has 11 one bits
        cout << "Number of 1 bits in " << num << ": " << s.calculateOneBits(num) << endl;

        return 0;
}

#if 0
/* ----------------------------------------------------------------
 * C language implementations (three approaches)
 * ---------------------------------------------------------------- */

/*
 * Approach 1 - Monotone stack  O(n) time / O(n) space
 *
 * For each element arr[i], find the max window where arr[i] is minimum:
 *   left[i]  = nearest strictly-smaller index to the left  (-1 if none)
 *   right[i] = nearest strictly-smaller index to the right ( n if none)
 * span = right[i] - left[i] - 1; if span >= k, arr[i] is a candidate.
 */
static int maxmin_stack(const int *arr, int n, int k)
{
	int *left, *right, *stk;
	int top, result, i;

	if (!arr || n == 0 || k <= 0 || k > n)
		return INT_MIN;

	left   = (int *)malloc(n * sizeof(int));
	right  = (int *)malloc(n * sizeof(int));
	stk    = (int *)malloc(n * sizeof(int));
	top    = -1;
	result = INT_MIN;

	/* nearest smaller to the left */
	for (i = 0; i < n; i++) {
		while (top >= 0 && arr[stk[top]] >= arr[i])
			top--;
		left[i] = (top < 0) ? -1 : stk[top];
		stk[++top] = i;
	}

	/* nearest smaller to the right */
	top = -1;
	for (i = n - 1; i >= 0; i--) {
		while (top >= 0 && arr[stk[top]] >= arr[i])
			top--;
		right[i] = (top < 0) ? n : stk[top];
		stk[++top] = i;
	}

	for (i = 0; i < n; i++)
		if (right[i] - left[i] - 1 >= k && arr[i] > result)
			result = arr[i];

	free(left);
	free(right);
	free(stk);
	return result;
}

/*
 * Approach 2 - Sliding window + monotone deque  O(n) time / O(k) space
 *
 * Deque (simulated with array) stores indices in non-decreasing value order.
 * Front always holds the current window minimum.
 */
static int maxmin_deque(const int *arr, int n, int k)
{
	int *dq;
	int head, tail, result, i;

	if (!arr || n == 0 || k <= 0 || k > n)
		return INT_MIN;

	dq     = (int *)malloc(n * sizeof(int));
	head   = 0;
	tail   = 0;
	result = INT_MIN;

	for (i = 0; i < n; i++) {
		/* evict index that fell outside window left edge */
		if (head < tail && dq[head] <= i - k)
			head++;
		/* maintain non-decreasing order */
		while (head < tail && arr[dq[tail - 1]] >= arr[i])
			tail--;
		dq[tail++] = i;
		/* once first full window formed, record its minimum */
		if (i >= k - 1 && arr[dq[head]] > result)
			result = arr[dq[head]];
	}

	free(dq);
	return result;
}

/*
 * Approach 3 - Brute force  O(n*k) time / O(1) space
 */
static int maxmin_brute(const int *arr, int n, int k)
{
	int result = INT_MIN, i, j, win_min;

	for (i = 0; i <= n - k; i++) {
		win_min = arr[i];
		for (j = i + 1; j < i + k; j++)
			if (arr[j] < win_min)
				win_min = arr[j];
		if (win_min > result)
			result = win_min;
	}
	return result;
}
#endif
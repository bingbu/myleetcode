/*
Given two integer arrays nums1 and nums2, return the maximum length 
of a subarray that appears in both arrays.
Use DP (dynamic programming).
Using single array can save space.
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findLength(const vector<int>& nums1, const vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<int> dp(m + 1, 0);
        int maxLength = 0;

        for (int i = n - 1; i >= 0; --i) {
            // Must traverse from left to right to avoid overwriting unused values
            for (int j = 0; j < m; ++j) {
                if (nums1[i] == nums2[j]) {
                    dp[j] = dp[j + 1] + 1;
                    maxLength = max(maxLength, dp[j]);
                } else {
                    dp[j] = 0;  // reset
                }
            }
        }
        return maxLength;
    }

    int findLength2(const vector<int>& nums1, const vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int maxLength = 0;

        // traverse from left to right
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    maxLength = max(maxLength, dp[i][j]);
                }
            }
        }
        return maxLength;
    }
};

int main() {
    Solution sol;
    vector<int> test1_nums1 = {1,2,3,2,1};
    vector<int> test1_nums2 = {3,2,1,4,7};
    cout << "Test 1: " << sol.findLength(test1_nums1, test1_nums2) << endl;  // Expected: 3
    cout << "Test 1: " << sol.findLength2(test1_nums1, test1_nums2) << endl;  // Expected: 3

    vector<int> test2_nums1 = {0,0,0,0,0};
    vector<int> test2_nums2 = {0,0,0,0,0};
    cout << "Test 2: " << sol.findLength(test2_nums1, test2_nums2) << endl;  // Expected: 5
    cout << "Test 2: " << sol.findLength2(test2_nums1, test2_nums2) << endl;  // Expected: 5

    vector<int> test3_nums1 = {1,2,3,4,5};
    vector<int> test3_nums2 = {6,7,8,9,10};
    cout << "Test 3: " << sol.findLength(test3_nums1, test3_nums2) << endl;  // Expected: 0
    cout << "Test 3: " << sol.findLength2(test3_nums1, test3_nums2) << endl;  // Expected: 0

    return 0;
}
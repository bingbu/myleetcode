/* 1879. Minimum XOR Sum of Two Arrays */
/* 二分图最小权匹配 (Hungarian Algorithm) */
/* Difficulty: Hard */
#include <iostream>
#include <vector>
#include <algorithm>
#include <intrin.h>  // For __popcnt on MSVC
using namespace std;

class Solution {
public:
    int minimumXORSum(const vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int size = 1 << n;  // Total number of states
        vector<int> dp(size, INT_MAX);
        dp[0] = 0;  // Base case: no elements chosen

        for (int mask = 0; mask < size; ++mask) {
            int i = __builtin_popcount(mask); // GCC/Clang intrinsic: count set bits
            //int i = __popcnt(mask);  // MSVC intrinsic: count set bits
            for (int j = 0; j < n; ++j) {
                if (!(mask & (1 << j))) {  // If j-th element in nums2 is not chosen
                    int new_mask = mask | (1 << j);
                    dp[new_mask] = min(dp[new_mask], dp[mask] + (nums1[i] ^ nums2[j]));
                }
            }
        }
        return dp[size - 1];  // All elements chosen
    }
};

int main() {
    Solution sol;
    vector<int> nums1_1 = {1, 2};
    vector<int> nums2_1 = {2, 3};
    cout << "Test 1: " << sol.minimumXORSum(nums1_1, nums2_1) << endl;  // Expected: 2

    vector<int> nums1_2 = {1, 0, 3};
    vector<int> nums2_2 = {5, 3, 4};
    cout << "Test 2: " << sol.minimumXORSum(nums1_2, nums2_2) << endl;  // Expected: 8

    vector<int> nums1_3 = {0, 1, 2, 3, 4};
    vector<int> nums2_3 = {5, 4, 3, 2, 1};
    cout << "Test 3: " << sol.minimumXORSum(nums1_3, nums2_3) << endl;  // Expected: 5

    return 0;
}
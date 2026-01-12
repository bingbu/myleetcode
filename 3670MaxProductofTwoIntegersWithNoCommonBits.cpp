// 3670. Maximum Product of Two Integers With No Common Bits
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

class Solution {
public:
    // SOS DP: O(n + 2^k*k) preprocess, O(n) query
    // 这个对于我来说太难了……
    long long maxProduct(vector<int>& nums) {
        if (nums.size() < 2) return 0;
        
        int maxNum = *max_element(nums.begin(), nums.end());
        if (maxNum == 0) return 0;
        
        // Find highest bit
        int bits = 0;
        for (int i = 31; i >= 0; --i) {
            if (maxNum & (1 << i)) { bits = i + 1; break; }
        }
        
        int dpSize = 1 << bits;
        vector<int> dp(dpSize, 0);
        
        // Initialize: keep max value for each pattern
        for (int num : nums) {
            dp[num] = max(dp[num], num);
        }
        
        // SOS DP: dp[mask] = max among all subsets of mask
        for (int i = 0; i < bits; ++i) {
            for (int mask = 0; mask < dpSize; ++mask) {
                if (mask & (1 << i)) {
                    dp[mask] = max(dp[mask], dp[mask ^ (1 << i)]);
                }
            }
        }
        
        long long maxProd = 0;
        int fullMask = dpSize - 1;
        for (int num : nums) {
            if (num == 0) continue;
            int complement = fullMask ^ num;
            int compatible = dp[complement];
            if (compatible > 0 && compatible != num) {
                maxProd = max(maxProd, (long long)num * compatible);
            }
        }
        
        return maxProd;
    }
};

int main() {
    Solution sol;
    
    vector<int> test1 = {1,2,3,4,5,6,7};
    cout << "Test 1: " << sol.maxProduct(test1) << endl;

    vector<int> test2 = {4, 5, 6};
    cout << "Test 2: " << sol.maxProduct(test2) << endl;

    vector<int> test3 = {64,8,32};
    cout << "Test 3: " << sol.maxProduct(test3) << endl;

    cout << "\n--- Performance Test ---" << endl;
    vector<int> large_test;
    for (int i = 1000000; i > 900000; --i) {
        large_test.push_back(i);
        large_test.push_back(i);
    }
    cout << "Dataset: " << large_test.size() << " elements" << endl;
    
    auto start = chrono::high_resolution_clock::now();
    long long result = sol.maxProduct(large_test);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Result: " << result << " (Time: " << duration.count() << " µs)" << endl;

    return 0;
}
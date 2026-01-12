/* 
* 3804. Number of Centered Subarrays
* https://leetcode.com/problems/number-of-centered-subarrays/
* Given an integer array nums.
* A subarray of nums is called centered if the sum of its elements
* is equal to at least one element within that same subarray.
* Return the number of centered subarrays of nums.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

class Solution {
public:
    // O(n²) with hash map
    int centeredSubarrays(vector<int>& nums) {
        int result = 0;
        int n = nums.size();
        
        for (int start = 0; start < n; ++start) {
            long long sum = 0;
            unordered_map<long long, int> freq;
            
            for (int end = start; end < n; ++end) {
                sum += nums[end];
                freq[nums[end]]++;
                
                if (freq.count(sum)) {
                    result++;
                }
            }
        }
        return result;
    }
};

int main() {
    Solution sol;

    vector<int> test0 = {-1, 1, 0};
    cout << "Test 0:" << sol.centeredSubarrays(test0) << endl; // Expected: 5

    vector<int> test1 = {2, -3};
    cout << "Test 1:" << sol.centeredSubarrays(test1) << endl; // Expected: 2

    vector<int> test2;
    for (int i = 0; i < 1024; ++i) {
        test2.push_back(5);
    }
    cout << "Test 2:" << sol.centeredSubarrays(test2) << endl; // Expected: 1024

    return 0;
}
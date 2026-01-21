/*
Given an array of positive integers nums and a positive integer
target, return the minimal length of a subarray whose sum is greater
than or equal to target. If there is no such subarray, return 0 instead.
*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int l = 0;
        int sum = 0;
        int n = nums.size();
        int min = n + 1;
        for (int r = 0; r < n; ++r) {
            sum += nums[r];
            while (sum >= target) {
                min =  (r - l + 1 < min) ? (r - l + 1) : min;
                sum -= nums[l++];
            }
        }
        return min == (n + 1) ? 0 : min;
    }

    int minSubArrayLenBad(int target, vector<int>& nums) {
		size_t n = nums.size();
        int l = 0;
		int sum = 0;
		int min = n + 1;

        for (int num : nums) {
            if (num >= target) return 1;
            sum += num;
        }

        if (sum < target) return 0;

        for (int r = l; r < n; ++r) {
			sum = sumRange(nums, l, r);
			if (sum >= target) {
				if (r - l + 1 <= min) {
					min = r - l + 1;
                }
				l++;
                r = l - 1;
			}
        }
        return min == n + 1 ? 0 : min;
    }
private:
    int sumRange(const vector<int>& nums, int l, int h) {
        int sum = 0;
        for (int i = l; i <= h; ++i) {
            sum += nums[i];
        }
        return sum;
    }
};

int main() {
    Solution sol;

    vector<int> test1 = {2,3,1,2,4,3};
    int target1 = 7;
    cout << "Test 1: " << sol.minSubArrayLen(target1, test1) << endl;  // Expected: 2

    vector<int> test2 = {1,4,4};
    int target2 = 4;
    cout << "Test 2: " << sol.minSubArrayLen(target2, test2) << endl;  // Expected: 1

    vector<int> test3 = {1,1,1,1,1,1,1,1};
    int target3 = 11;
    cout << "Test 3: " << sol.minSubArrayLen(target3, test3) << endl;  // Expected: 0

    return 0;
}
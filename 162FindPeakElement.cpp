/* A peak element is an element that is strictly greater than its neighbors.*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] > nums[mid + 1]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main() {
    Solution sol;
    vector<int> test1 = {1, 2, 3, 1};
    cout << "Test 1: Peak Index = " << sol.findPeakElement(test1) << endl;  // Expected: 2

    vector<int> test2 = {1, 2, 1, 3, 5, 6, 4};
    cout << "Test 2: Peak Index = " << sol.findPeakElement(test2) << endl;  // Expected: 5

    vector<int> test3 = {1};
    cout << "Test 3: Peak Index = " << sol.findPeakElement(test3) << endl;  // Expected: 0

    vector<int> test4 = {3, 2, 1};
    cout << "Test 4: Peak Index = " << sol.findPeakElement(test4) << endl;  // Expected: 0

    vector<int> test5 = {1, 2, 3};
    cout << "Test 5: Peak Index = " << sol.findPeakElement(test5) << endl;  // Expected: 2

    return 0;
}
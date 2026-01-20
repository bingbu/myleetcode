/*
27. Remove Element
Given an integer array nums and an integer val, remove all occurrences of val
in nums in-place. The order of the elements may be changed. 
Then return the number of elements in nums which are not equal to val.
*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        int n = nums.size();
        for (int fast = 0; fast < n; ++fast) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                ++slow;
            }
        }
        return slow;
    }
};
// Tests
int main() {
    Solution sol;
    vector<int> nums1 = {3, 2, 2, 3};
    int val1 = 3;
    int len1 = sol.removeElement(nums1, val1);
    cout << "Test 1: New length = " << len1 << ", Elements = ";
    for (int i = 0; i < len1; ++i) {
        cout << nums1[i] << " ";
    }
    cout << endl;

    vector<int> nums2 = {0,1,2,2,3,0,4,2};
    int val2 = 2;
    int len2 = sol.removeElement(nums2, val2);
    cout << "Test 2: New length = " << len2 << ", Elements = ";
    for (int i = 0; i < len2; ++i) {
        cout << nums2[i] << " ";
    }
    cout << endl;

    return 0;
}
    
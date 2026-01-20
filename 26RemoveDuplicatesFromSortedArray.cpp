/* Remove Duplicates from Sorted Array*/

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        int slow = 0;
        for (int fast = 1; fast < n; ++fast) {
            if (nums[fast] != nums[slow]) {
                nums[++slow] = nums[fast];
            }
        }
        return slow + 1;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {1,1,2};
    int len1 = sol.removeDuplicates(nums1);
    cout << "Test 1: New length = " << len1 << ", Elements = ";
    for (int i = 0; i < len1; ++i) {
        cout << nums1[i] << " ";
    }
    cout << endl;

    vector<int> nums2 = {0,0,1,1,1,2,2,3,3,4};
    int len2 = sol.removeDuplicates(nums2);
    cout << "Test 2: New length = " << len2 << ", Elements = ";
    for (int i = 0; i < len2; ++i) {
        cout << nums2[i] << " ";
    }
    cout << endl;

    return 0;
}
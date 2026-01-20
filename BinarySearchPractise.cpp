/* Binary search practice */

#include <iostream>
#include <vector>
using namespace std;

class NumArray {

public:
    int binarySearch(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] == target) {
                return mid;
            } 
            
            if (nums[mid] > target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return -1; // Target not found
    }

    int binarySearch2(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] == target) {
                return mid;
            } 
            
            if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1; // Target not found
    }
};

int main() {
    vector<int> nums = {-10, -3, 0, 5, 9};
    NumArray numArray;    
    int target1 = 0;
    cout << "Index of " << target1 << ": " << numArray.binarySearch(nums, target1) << endl;  // Expected: 2
    cout << "Index of " << target1 << ": " << numArray.binarySearch2(nums, target1) << endl;  // Expected: 2

    int target2 = -3;
    cout << "Index of " << target2 << ": " << numArray.binarySearch(nums, target2) << endl;  // Expected: 1
    cout << "Index of " << target2 << ": " << numArray.binarySearch2(nums, target2) << endl;  // Expected: 1

    int target3 = 9;
    cout << "Index of " << target3 << ": " << numArray.binarySearch(nums, target3) << endl;  // Expected: 4
    cout << "Index of " << target3 << ": " << numArray.binarySearch2(nums, target3) << endl;  // Expected: 4

    int target4 = 7;
    cout << "Index of " << target4 << ": " << numArray.binarySearch(nums, target4) << endl;  // Expected: -1 (not found)
    cout << "Index of " << target4 << ": " << numArray.binarySearch2(nums, target4) << endl;  // Expected: -1 (not found)

    return 0;
}
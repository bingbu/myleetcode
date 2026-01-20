/* 283. Move Zeroes */
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int l = 0;
		int n = nums.size();
        for (int r = 0; r < n; ++r) {
            if (nums[r] != 0) {
				nums[l] = nums[r];
                if (l != r) {
                    nums[r] = 0;
                }
                ++l;
            }
        }
    }
};

int main() {
    Solution sol;
    
    vector<int> test1 = {0,1,0,3,12};
    sol.moveZeroes(test1);
    cout << "Test 1: ";
    for (int num : test1) {
        cout << num << " ";
    }
    cout << endl;  // Expected: [1,3,12,0,0]

    vector<int> test2 = {0,0,1};
    sol.moveZeroes(test2);
    cout << "Test 2: ";
    for (int num : test2) {
        cout << num << " ";
    }
    cout << endl;  // Expected: [1,0,0]

    vector<int> test3 = {4,2,4,0,0,3,0,5,1,0};
    sol.moveZeroes(test3);
    cout << "Test 3: ";
    for (int num : test3) {
        cout << num << " ";
    }
    cout << endl;  // Expected: [4,2,4,3,5,1,0,0,0,0]

    return 0;
}
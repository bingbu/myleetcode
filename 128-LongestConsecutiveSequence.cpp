/*
* Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
* Write an algorithm that runs in O(n) time.
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) 
            return 0;

        // deduplication with unordered_set or sort to save memory
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }


        int longest_streak = 0;
        for (const int& num : num_set) {
            // only start counting if 'num - 1' is not in the set, meaning 'num' is the start of a sequence
            if (num_set.find(num - 1) == num_set.end()) {
                int current_num = num;
                int current_streak = 1;
                // Find the length of the sequence starting from 'num'
                while (num_set.find(current_num + 1) != num_set.end()) {
                    current_num += 1;
                    current_streak += 1;
                }
                // record the maximum length found and update longest_streak
                longest_streak = max(longest_streak, current_streak);
            }
        }
        return longest_streak;
    }
};

int main() {
    Solution sol;
    vector<int> test1 = {100, 4, 200, 1, 3, 2};
    cout << "--------Test 1: " << sol.longestConsecutive(test1) << endl;  // Expected: 4

    vector<int> test2 = {0, -1};
    cout << "--------Test 2: " << sol.longestConsecutive(test2) << endl;  // Expected: 2

    vector<int> test3 = {9,1,4,7,3,-1,0,5,8,-1,6};
    cout << "--------Test 3: " << sol.longestConsecutive(test3) << endl;  // Expected: 7

    return 0;
}
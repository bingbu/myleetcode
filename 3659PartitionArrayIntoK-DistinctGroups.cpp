// 3659. Partition Array Into K-Distinct Groups
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool partitionArray(vector<int>& nums, int k) {
        unordered_map<int, int> umap;
        size_t n = nums.size();

        if ((n != 1 && n < k) || n % k != 0) {
            return false;
        }
        // Count frequency of each element
        for (const int& num : nums) {
            umap[num]++;
        }
        for (const auto& entry : umap) {
            if (entry.second > (n / k)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution sol;
    vector<int> test1 = {1, 2, 3, 3};
    int k1 = 2;
    cout << "Test 1: " << (sol.partitionArray(test1, k1) ? "True" : "False") << endl;  // Expected: True

    vector<int> test2 = {1, 2, 3, 4};
    int k2 = 3;
    cout << "Test 2: " << (sol.partitionArray(test2, k2) ? "True" : "False") << endl;  // Expected: False
    vector<int> test3 = {1, 1, 2, 2, 3, 3};
    int k3 = 3;
    cout << "Test 3: " << (sol.partitionArray(test3, k3) ? "True" : "False") << endl;  // Expected: True

    vector<int> test4 = {1, 1, 1, 2, 2, 2};
    int k4 = 2;
    cout << "Test 4: " << (sol.partitionArray(test4, k4) ? "True" : "False") << endl;  // Expected: False

    vector<int> test5 = {74, 104, 74};
    int k5 = 3;
    cout << "Test 5: " << (sol.partitionArray(test5, k5) ? "True" : "False") << endl;  // Expected: False

    return 0;
}
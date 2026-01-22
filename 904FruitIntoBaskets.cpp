/*
904. Fruit Into Baskets
Double-pointer / Sliding Window
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> countMap;
        int left = 0, maxFruits = 0;
        int n = fruits.size();

        for (int right = 0; right < n; ++right) {
            countMap[fruits[right]]++;
            while (countMap.size() > 2) { // 2 bastkets is full now
                countMap[fruits[left]]--; // clear 1 basket
                if (countMap[fruits[left]] == 0) {
                    countMap.erase(fruits[left]);
                }
                left++;
            }
            if (right - left + 1 > maxFruits)
                maxFruits = right - left + 1;
        }

        return maxFruits;
    }

    // O(1) without hash map
    int totalFruit2(vector<int>& fruits) {
        int n = fruits.size();
        int left = 0, maxFruits = 0;
        int type1 = -1, type2 = -1;
        int count1 = 0, count2 = 0;

        for (int right = 0; right < n; ++right) {
            int f = fruits[right];

            if (count1 == 0) type1 = f;
            if (count2 == 0) type2 = f;

            if (f == type1) {
                count1++;
            } else if (f == type2) {
                count2++;
            }

            if (f != type1 && f != type2) {
                // clear 1 basket
                while (count1 > 0 && count2 > 0) {
                        if (fruits[left] == type1) {
                            count1--;
                        } else {
                            count2--;
                        }
                        left++;
                }
                // start new basket
#if 1
                if (count1 == 0) {
                    type1 = f;
                    count1 = 1;
                } else {
                    type2 = f;
                    count2 = 1;
                }
#else
                right--; // redo this fruit in next iteration
#endif
            }

            maxFruits = max(maxFruits, right - left + 1);
        }
        return maxFruits;
    }
};

int main() {
    Solution sol;

    vector<int> test1 = {1,2,1};
    cout << "Test 1: " << sol.totalFruit(test1) << endl;  // Expected: 3

    vector<int> test2 = {0,1,2,2};
    cout << "Test 2: " << sol.totalFruit(test2) << endl;  // Expected: 3

    vector<int> test3 = {1,2,3,2,2};
    cout << "Test 3: " << sol.totalFruit(test3) << endl;  // Expected: 4

    vector<int> test4 = {3,3,3,1,2,1,1,2,3,3,4};
    cout << "Test 4: " << sol.totalFruit(test4) << endl;  // Expected: 5

    return 0;
}
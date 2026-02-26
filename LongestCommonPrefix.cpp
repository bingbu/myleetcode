#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty())
            return "";

        if (strs.size() == 1)
            return strs[0];

        int min_length = strs[0].size();
        for (int i = 1; i < strs.size(); ++i) {
            if (strs[i].size() < min_length) {
                min_length = strs[i].size();
            }
        }

        for (int i = 0; i < min_length; ++i) {
            char current_char = strs[0][i];
            for (int j = 1; j < strs.size(); ++j) {
                if (strs[j][i] != current_char) {
                    return strs[0].substr(0, i);
                }
            }
        }
        return strs[0].substr(0, min_length);
    }
};

int main() {
    Solution sol;
    vector<string> test1 = {"flower", "flow", "flight"};
    cout << "Test 1: " << sol.longestCommonPrefix(test1) << endl;  // Expected: "fl"

    vector<string> test2 = {"dog", "racecar", "car"};
    cout << "Test 2: " << sol.longestCommonPrefix(test2) << endl;  // Expected: ""

    vector<string> test3 = {"ab", "abc", "abcd", "abcde"};
    cout << "Test 3: " << sol.longestCommonPrefix(test3) << endl;  // Expected: "ab"

    return 0;
}
// 1544. Make The String Great

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string makeGood(string s) {
        string res;
        for (const char& ch : s) {
            if (!res.empty() && abs(res.back() - ch) == 32) {
                res.pop_back();
            } else {
                res.push_back(ch);
            }
        }
        return res;
    }
    string makeGood2(string s) {
        for (size_t i = 0; i < s.size(); ) {
            if (i > 0 && abs(s[i-1] - s[i]) == 32) {
                s.erase(i-1, 2);  // Delete last two characters
                if (i > 0) --i;   // backtrack one position
            } else {
                ++i;
            }
        }
        return s;
    }
};

int main() {
    Solution sol;
    string test1 = "leEeetcode";
    cout << "Test 1: " << sol.makeGood(test1) << endl;  // Expected: "leetcode"
    cout << "Test 1: " << sol.makeGood2(test1) << endl;  // Expected: "leetcode"

    string test2 = "abBAcC";
    cout << "Test 2: " << sol.makeGood(test2) << endl;  // Expected: ""
    cout << "Test 2: " << sol.makeGood2(test2) << endl;  // Expected: ""

    string test3 = "s";
    cout << "Test 3: " << sol.makeGood(test3) << endl;  // Expected: "s"
    cout << "Test 3: " << sol.makeGood2(test3) << endl;  // Expected: "s"
    return 0;
}
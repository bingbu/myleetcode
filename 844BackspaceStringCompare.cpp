/*
* Given two strings s and t, return true if they are equal when both are
* typed into empty text editors. '#' means a backspace character.
* Note that after backspacing an empty text, the text will continue empty.
*/

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool backspaceCompare(string& s, string& t) {
        // Use slow-fast pointer to process strings
        auto processString = [](string& str) {
            int slow = 0;
            size_t n = str.size();
            for (int fast = 0; fast < n; ++fast) {
                if (str[fast] != '#') {
                    str[slow] = str[fast];
                    slow++;
                } else if (slow > 0) { // for backspace at the beginning
                    slow--;
                }
            }
            //C++ STL容器的通用设计理念：容量只增不减（除非显式请求）
            str.resize(slow);
        };

        processString(s);
        processString(t);

        return s == t;
    }

};

int main() {
    Solution sol;

    string test1_s = "ab#c";
    string test1_t = "ad#c";
    cout << "Test 1: " << (sol.backspaceCompare(test1_s, test1_t) ? "True" : "False") << endl;  // Expected: True
    string test2_s = "ab##";
    string test2_t = "c#d#";
    cout << "Test 2: " << (sol.backspaceCompare(test2_s, test2_t) ? "True" : "False") << endl;  // Expected: True
    string test3_s = "a#c";
    string test3_t = "b";
    cout << "Test 3: " << (sol.backspaceCompare(test3_s, test3_t) ? "True" : "False") << endl;  // Expected: False
    return 0;
}
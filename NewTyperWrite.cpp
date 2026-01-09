// 1974. Minimum Time to Type Word Using Special Typewriter
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int minTimeToType(string word) {
        int total_time = 0;
        char current_char = 'a';
        for (const char& target_char : word) {
            int direct_distance = (target_char - current_char) > 0 ? (target_char - current_char) : (current_char - target_char);
            int circular_distance = 26 - direct_distance;
            total_time += min(direct_distance, circular_distance) + 1;  // +1 for typing the character
            current_char = target_char;
        }
        return total_time;
    }
};

int main() {
    Solution sol;
    string test1 = "abc";
    cout << "Test 1: " << sol.minTimeToType(test1) << endl;  // Expected: 5

    string test2 = "bza";
    cout << "Test 2: " << sol.minTimeToType(test2) << endl;  // Expected: 7

    string test3 = "zjpc";
    cout << "Test 3: " << sol.minTimeToType(test3) << endl;  // Expected: 34

    return 0;
}
/*
* 2525. Categorize Box According to Criteria
*/
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string categorizeBox(int length, int width, int height, int mass) {
        string categories[] = {"Neither", "Bulky", "Heavy", "Both"};

        unsigned long long volume = (unsigned long long)length * width * height;
        unsigned int bulky = (length >= 10000 || width >= 10000 || height >= 10000 || volume >= 1000000000ULL) ? 1 : 0;
        unsigned int heavy = (mass >= 100) ? 1 : 0;

        return categories[bulky + (heavy << 1)];
    }
};

int main() {
    Solution sol;
    cout << "Test 1: " << sol.categorizeBox(1000, 35, 700, 300) << endl;  // Expected: "Heavy"
    cout << "Test 2: " << sol.categorizeBox(200, 50, 800, 50) << endl;    // Expected: "Neither"
    cout << "Test 3: " << sol.categorizeBox(10000, 10000, 10000, 50) << endl; // Expected: "Bulky"
    cout << "Test 4: " << sol.categorizeBox(15000, 20000, 30000, 150) << endl; // Expected: "Both"
    return 0;
}
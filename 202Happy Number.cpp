/*
202. Happy Number
*/

#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> seen;
        while (n != 1) {
            if (seen.count(n)) {
                return false;
            }
            seen.insert(n);
            n = getNext(n);
        }
        return true;
    }
    // same algorithm as problem 142 Linked List Cycle II
    // 无论是不是快乐数，计算过程都会进入一个循环
    bool isHappy_FloydPollard(int n) {
        int slow = n;
        int fast = getNext(n);

        while (fast != 1 && slow != fast) {
            slow = getNext(slow); // 1 step
            fast = getNext(getNext(fast));  // 2 steps
        }

        return fast == 1;
    }

private:
    int getNext(int n) {
        int sum = 0;
        while (n > 0) {
            int r = n % 10;
            sum += r * r;
            n = n / 10;
        }
        return sum;
    }
};

int main() {
    Solution sol;
    int number = 19; // Example input
    if (sol.isHappy(number)) {
        cout << number << " is a happy number." << endl;
    } else {
        cout << number << " is not a happy number." << endl;
    }

    int number2 = 6; // Example input
    if (sol.isHappy_FloydPollard(number2)) {
        cout << number2 << " is a happy number." << endl;
    } else {
        cout << number2 << " is not a happy number." << endl;
    }
    return 0;
}
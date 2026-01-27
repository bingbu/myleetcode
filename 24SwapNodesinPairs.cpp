/*
Given a linked list, swap every two adjacent nodes and return its head.
You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)
*/

#include <iostream>
using namespace std;

class Solution {public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
    };
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode** pp = &head;

        // Traverse the list in pairs (as a sublist of 2 nodes)
        while (*pp != nullptr && (*pp)->next != nullptr) {
            ListNode* left = *pp;
            ListNode* right = (*pp)->next;

            // Swap 2 nodes in pair
            left->next = right->next;
            right->next = left;
            // Update the head of the current pair
            *pp = right;

            // Move pp to the next sublist(pair)
            pp = &(left->next);
        }
        return head;
    }
};


int main() {
    Solution sol;
    // Example usage:
    Solution::ListNode* head = new Solution::ListNode(1);
    head->next = new Solution::ListNode(2);
    head->next->next = new Solution::ListNode(3);
    head->next->next->next = new Solution::ListNode(4);

    Solution::ListNode* swappedHead = sol.swapPairs(head);

    // Print the modified list
    Solution::ListNode* current = swappedHead;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;

    // Clean up memory
    current = swappedHead;
    while (current != nullptr) {
        Solution::ListNode* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
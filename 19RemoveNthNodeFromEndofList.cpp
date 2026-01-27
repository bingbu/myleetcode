/*
19. Remove Nth Node From End of List
*/

#include <iostream>
using namespace std;

class Solution {
public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode** left = &head;
        ListNode** right = &head;

        while (n-- > 0 && *right != nullptr) {
            right = &((*right)->next);
        }

        while (*right != nullptr) {
            left = &((*left)->next);
            right = &((*right)->next);
        }

        ListNode* temp = *left;
        *left = (*left)->next;
        delete temp;
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
    head->next->next->next->next = new Solution::ListNode(5);
    // Print the list
    Solution::ListNode* current = head;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;

    int n = 3;
    Solution::ListNode* modifiedHead = sol.removeNthFromEnd(head, n);

    // Print the modified list
    current = modifiedHead;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;

    // Clean up memory
    current = modifiedHead;
    while (current != nullptr) {
        Solution::ListNode* temp = current;
        current = current->next;
        delete temp;
    }
    return 0;
}
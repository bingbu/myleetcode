/* 206. Reverse Linked List*/
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode** pp = &head;
        ListNode* prev = nullptr;
        while (*pp != nullptr) {
            ListNode* next = (*pp)->next;
            (*pp)->next = prev;
            prev = *pp;
            *pp = next;
        }
        return prev;
    }
};

int main() {
    Solution sol;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);

    ListNode* reversedHead = sol.reverseList(head);
    ListNode* current = reversedHead;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;
    return 0;
}
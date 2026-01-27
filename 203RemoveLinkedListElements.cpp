/*
Given the head of a linked list and an integer val, remove all the nodes of the linked list that has Node.val == val, and return the new head.
*/

#include <iostream>
#include <vector>
using namespace std;

class solution {
public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode* removeElements(ListNode* head, int val) {
        ListNode** pHead = &head; // Pointer to pointer to save memory

        while (*pHead != nullptr) {
            if ((*pHead)->val == val) {
                ListNode* temp = *pHead;
                *pHead = (*pHead)->next;
                delete temp;
            } else {
                pHead = &((*pHead)->next);
            }
        }
        return head;
    }
};

int main() {
    solution sol;
    // Example usage:
    solution::ListNode* head = new solution::ListNode(1);
    head->next = new solution::ListNode(2);
    head->next->next = new solution::ListNode(6);
    head->next->next->next = new solution::ListNode(3);
    head->next->next->next->next = new solution::ListNode(4);
    head->next->next->next->next->next = new solution::ListNode(5);
    head->next->next->next->next->next->next = new solution::ListNode(6);

    int val = 6;
    solution::ListNode* newHead = sol.removeElements(head, val);

    // Print the modified list
    solution::ListNode* current = newHead;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;

    // Clean up memory
    current = newHead;
    while (current != nullptr) {
        solution::ListNode* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
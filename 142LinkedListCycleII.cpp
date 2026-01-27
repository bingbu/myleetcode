/*
142. Linked List Cycle II
*/
#include <unordered_set>
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    // Method 1: Hash Table
    ListNode *detectCycle(ListNode *head) {
        std::unordered_set<ListNode*> nodes;
        ListNode* current = head;
        while (current != nullptr) {
            if (nodes.find(current) != nodes.end()) {
                return current;
            }
            nodes.insert(current);
            current = current->next;
        }
        return nullptr;
    }

    bool hasCycle(ListNode *head) {
        std::unordered_set<ListNode*> nodes;
        ListNode* current = head;
        while (current != nullptr) {
            if (nodes.find(current) != nodes.end()) {
                return true;
            }
            nodes.insert(current);
            current = current->next;
        }
        return false;
    }

    // Method 2: Floyd's Tortoise and Hare - https://wuli.wiki/changed/FloydC.html
    bool hasCycle2(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }

    ListNode *detectCycle2(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // Find meeting point in the cycle (if any)
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                // Second phase: find the entrance to the cycle
                ListNode* entry = head;
                while (entry != slow) {
                    entry = entry->next;
                    slow = slow->next;
                }
                return entry;
            }
        }
        return nullptr;
    }
};

int main() {
    Solution sol;
    // Example usage:
    ListNode* head = new ListNode(3);
    head->next = new ListNode(2);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(-4);
    head->next->next->next->next = head->next; // Create a cycle

    ListNode* cycleStart = sol.detectCycle(head);
    if (cycleStart) {
        cout << "Cycle starts at node with value: " << cycleStart->val << endl;
    } else {
        cout << "No cycle detected." << endl;
    }

    return 0;
}
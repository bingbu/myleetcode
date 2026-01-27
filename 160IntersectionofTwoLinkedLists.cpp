/*
160. Intersection of Two Linked Lists#
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

    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* a = headA;
        ListNode* b = headB;

        while (a != b) {
            /*
            * consider the 2 linked lists as a whole,
            * find the common node between (A + B) and (B + A)
            */
            a = (a == nullptr) ? headB : a->next;
            b = (b == nullptr) ? headA : b->next;
        }

        return a;
    }
};

int main() {
    Solution sol;
    // Example usage:
    Solution::ListNode* headA = new Solution::ListNode(4);
    headA->next = new Solution::ListNode(1);
    Solution::ListNode* intersect = new Solution::ListNode(8);
    intersect->next = new Solution::ListNode(4);
    intersect->next->next = new Solution::ListNode(5);
    headA->next->next = intersect;

    Solution::ListNode* headB = new Solution::ListNode(5);
    headB->next = new Solution::ListNode(0);
    headB->next->next = new Solution::ListNode(1);
    headB->next->next->next = intersect;

    Solution::ListNode* intersectionNode = sol.getIntersectionNode(headA, headB);
    if (intersectionNode != nullptr) {
        cout << "Intersection at node with value: " << intersectionNode->val << endl;
    } else {
        cout << "No intersection." << endl;
    }

    // Clean up memory (not shown here for brevity)

    return 0;
}
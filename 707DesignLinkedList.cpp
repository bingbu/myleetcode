/*
Design your implementation of the linked list. You can choose to use a singly or doubly linked list.
A node in a singly linked list should have two attributes: val and next. val is the value of the current node, and next is a pointer/reference to the next node.
If you want to use the doubly linked list, you will need one more attribute prev to indicate the previous node in the linked list. Assume all nodes in the linked list are 0-indexed.
*/

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
};

class MyLinkedList {
public:
        MyLinkedList() {
            head = nullptr;
        }

        int get(int index) {
            ListNode** pp = &head;
            int count = 0;
            while (*pp != nullptr) {
                if (count == index) {
                    return (*pp)->val;
                }
                pp = &((*pp)->next);
                count++;
            }
            return -1;
        }

        void addAtHead(int val) {
            ListNode* newNode = new ListNode(val);
            newNode->next = head;
            head = newNode;
        }

        void addAtTail(int val) {
            ListNode** pp = &head;

            if (*pp == nullptr) {
                *pp = new ListNode(val);
                return;
            }

            while ((*pp)->next != nullptr) {
                pp = &((*pp)->next);
            }

            ListNode* newNode = new ListNode(val);
            (*pp)->next = newNode;
        }

        void addAtIndex(int index, int val) {
            ListNode** pp = &head;
            int count = 0;
            while (*pp != nullptr) {
                if (count == index) {
                    ListNode* newNode = new ListNode(val);
                    newNode->next = *pp;
                    *pp = newNode;
                    return;
                }
                pp = &((*pp)->next);
                count++;
            }
            // add as tail
            if (count == index) {
                ListNode* newNode = new ListNode(val);
                *pp = newNode;
            }
        }

        void deleteAtIndex(int index) {
            ListNode** pp = &head;
            int count = 0;
            while (*pp != nullptr) {
                if (count == index) {
                    ListNode* temp = *pp;
                    *pp = (*pp)->next;
                    delete temp;
                    return;
                }
                pp = &((*pp)->next);
                count++;
            }
        }
        void printList() {
            ListNode* current = head;
            while (current != nullptr) {
                cout << current->val << " ";
                current = current->next;
            }
            cout << endl;
        }
private:
    ListNode* head;
};

int main() {
    MyLinkedList* obj = new MyLinkedList();
    obj->addAtTail(1);
    obj->printList();
    obj->get(0);
    obj->addAtHead(7);
    obj->printList();
    obj->addAtHead(2);
    obj->printList();
    obj->addAtHead(1);
    obj->printList();
    obj->addAtIndex(3, 0);
    obj->printList();
    obj->deleteAtIndex(2);
    obj->printList();
    obj->addAtHead(6);
    obj->printList();
    obj->addAtTail(4);
    obj->printList();
    obj->get(4);
    obj->addAtHead(4);
    obj->printList();
    obj->addAtIndex(5, 0);
    obj->printList();
    obj->addAtHead(6);
    obj->printList();
    int param_1 = obj->get(1);
    cout << "Value at index 1: " << param_1 << endl;
    obj->deleteAtIndex(1);
    param_1 = obj->get(1);
    cout << "Value at index 1 after deletion: " << param_1 << endl;
    obj->printList();
    delete obj;
    return 0;
}
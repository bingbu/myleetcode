/*
 * leetcode 19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct ListNode {
	int val;
	struct ListNode *next;
};

struct indexed_listnode {
	int index;
	struct ListNode *node;
};


struct ListNode * create() {
	unsigned int size, i;
	struct ListNode *head, *current;

	printf("Please specify the list size : ");
	scanf("%ud",&size);
	if (!size) {
		printf("you cannot create a empty list, now exit.\n");
		return;
	}

	head = (struct ListNode *)malloc(sizeof(struct ListNode) * size);
	current = head;
	for (i = 0; i < size; i++) {
		if (i + 1 == size)
			current->next = NULL;
		else
			current->next = current + 1;
		current->val = (i+1) * 3;
		current = current->next;

	}

	return head;
}
void display(struct ListNode *head)
{
	while(head != NULL)
	{
		if(head->next)
			printf("%d--->", head->val);
		else
			printf("%d", head->val);

		head = head->next;
	}

	printf("\n");

}

struct ListNode* find(struct indexed_listnode *head, int n) {
	struct indexed_listnode *entry = head;
	while(entry->index != n) {
		entry++;
	}
	return entry->node;
}
struct ListNode* removeNthFromEnd_one_pass(struct ListNode* head, int n) {
	/*consider the gap between the pointer and the end*/
	/*|start-------first-------------end|
	  |start---------------second----first(end)|
	  second now stay at the pointer
	*/
	int i;
	struct ListNode *first, *second;

	first = second = head;
	for (i = 0; i < n; i++) {
		/* n > list_size */
		if(!first) {
			return head;
		}
		first = first->next;
	}

	/*n == list_size, so remove the 1st*/
	if (!first) {
		return head->next;
	}
	while(first->next != NULL) {
		first = first->next;
		second = second->next;
	}
	second->next = second->next->next;

	return head;
}

struct ListNode* removeNthFromEnd_not_best(struct ListNode* head, int n) {
	int i;
	int size;
	struct ListNode *entry = head;
	struct ListNode *res, *tmp;
	struct indexed_listnode *indexed_entry, *indexed_head;

	if (!head) {
		printf("invalid parameter!\n");
		return NULL;
	}

	for (i = 0; entry->next != NULL; i++) {
		entry = entry->next;
	}

	size = i+1;

	if (n > size || n <= 0) {
		printf("invalid parameter!\n");
		return head;
	}

	if (n == size) {
		tmp = head->next;
		free(head);
		return tmp;
	}
	if (n == 1) {
		entry = head;
		while (entry->next != NULL) {
			tmp = entry;
			entry = entry->next;
		}
		free(tmp->next);
		tmp->next = NULL;
		return head;
	}

	indexed_head = (struct indexed_listnode *)malloc(sizeof(struct indexed_listnode) * size);
	indexed_entry = indexed_head;
	entry = head;
	for (i = 0; i < size; indexed_entry++, i++) {
		indexed_entry->index = i;
		indexed_entry->node = entry;
		entry = entry->next;
	}
	find(indexed_head, (size-n-1))->next = find(indexed_head, (size-n+1));

	return head;
}


int main(int argc, char *argv[]) {
	struct ListNode *list;
	struct ListNode *list1;
	unsigned int n;

	list = create();
	display(list);
	printf("Please specify the 'n' value : ");
	scanf("%ud",&n);
	list1 = removeNthFromEnd_one_pass(list, n);
	printf("Remove done:\n");
	display(list1);

	return 0;
}


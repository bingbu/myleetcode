/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* addTwoNumbers(const struct ListNode* l1, const struct ListNode* l2)
{
	struct ListNode *l, *tmp, *head;
	int sum, s;

	sum = 0;
	s = 0;
	l = malloc(sizeof(struct ListNode));
	if (!l) 
		return NULL;
	head = l;

	while (l1 || l2) {
		sum = 0;
		sum += s;
		if (l1) {
			sum += l1->val;
			l1 = l1->next;
		}

		if (l2) {
			sum += l2->val;
			l2 = l2->next;
		}

		l->val = sum % 10;
		s = sum / 10;
		if (l1 || l2) {
			tmp = malloc(sizeof(struct ListNode));
			if (tmp) {
				l->next = tmp;
				l = l->next;
			}
		}
	}
	l->next = NULL;
	if (s) {
		tmp = malloc(sizeof(struct ListNode));
		if (tmp)
			tmp->val = s;
			tmp->next = NULL;
			l->next = tmp;
	}

	return head;
}

struct ListNode *list_gen()
{
	unsigned int i;
	struct ListNode *l, *next, *head;
	unsigned int size;
	printf("Generating random lists...\n");

	for (i = 0; i < 10; i++)
		size = rand() % 50;

	l = malloc(sizeof(struct ListNode));
	head = l;
	if (!l)
		return NULL;

	while (l) {
		l->val = rand() % 10;
		printf("%d", l->val);
		if (!size--) {
				l->next = NULL;
				break;
		}
		printf("->");
		next = malloc(sizeof(struct ListNode));
		if (next) {
			l->next = next;
			l = l->next;
		}
	}
	printf("\n");

	return head;
}
struct ListNode *list_gen5()
{
	struct ListNode *l;
	l = malloc(sizeof(struct ListNode));
	l->val = 5;
	l->next = NULL;
	printf("\n");

	return l;
}

int main(int argc, char *argv[])
{
	struct ListNode *l;
	l = addTwoNumbers(list_gen(), list_gen());
	
	printf("Calculate output:\n");
	while (l) {
		printf("%d->", l->val);
		l = l->next;
	}
	printf("\n");
	return 0;
}

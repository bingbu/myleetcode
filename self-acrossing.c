/*
 * leetcode 335
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct position {
	int x;
	int y;
	struct position *next;
};

struct step {
	int x;
	int y;
};

static dump(struct position * list) {

	printf("%p %d %d %p\n", list, list->x, list->y, list->next);
	do {
		list = list->next;
		printf("%p %d %d %p\n", list, list->x, list->y, list->next);
	} while(list->next != NULL);
}

static bool find_dup(struct position *list) {
	struct position *p1, *p2;
	p1 = list;
	while( p1 != NULL && p1->next != NULL) {
		p2 = p1->next;
		do {
			if (p2->x == p1->x && p2->y == p1->y){
				printf("Bingo!! %p == %p [%d, %d] found!\n", p2, p1, p2->x, p2->y);
				return true;
			}
			p2 = p2->next;
		}  while(p2 != NULL);
		p1 = p1->next;
	}

	return false;
}

/*
case 1:
┌───┐
│   │
└───┼──>
    │

case 2:
┌───┐
│   │
|   ^
|   |
|___|

case 3:
┌───┐
│   │<---
|   |   |
|       |
|_______|

 */
bool isSelfCrossing_best(int* x, int size)
{
	for(int i = 3; i < size; i++)
	{
		if(x[i]>=x[i-2]
		   && x[i-1]<=x[i-3]) return true;

		if(i>=4 && x[i-1]==x[i-3]
		   && x[i]+x[i-4]>=x[i-2]) return true;

		if(i>=5 && x[i-2]-x[i-4]>=0
		   && x[i]>=x[i-2]-x[i-4]
		   && x[i-1]>=x[i-3]-x[i-5]
		   && x[i-1]<=x[i-3]) return true;
	}
	return false;
}

bool isSelfCrossing(int* x, int xSize) {
	struct position *track_head;
	struct position *track_head_f;
	struct position *track_p, *track_tmp;
	struct step steps[4] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
	int i, j;

	/*initial the start point - (0, 0)*/
	track_head_f = track_head = calloc(1, sizeof(struct position));
	track_head->x = 0;
	track_head->y = 0;
	track_head->next = NULL;

	track_tmp = track_head;
	for (i = 0; i < xSize; i++) {
		for (j = 0; j < x[i]; j++) {
			track_p = calloc(1, sizeof(struct position));
			if (track_p) {
				track_tmp->next = track_p;
				track_p->x += track_tmp->x + steps[i%4].x;
				track_p->y += track_tmp->y + steps[i%4].y;
				track_tmp = track_p;
			}
		}
	}

	track_tmp->next = NULL;

	printf("Dump:\n");
	dump(track_head);

	return find_dup(track_head);

}

int main(int argc, char *argv[]) {
	int node[4] = {1, 1, 1, 1};
	int i;
	for (i = 0; i < sizeof(node)/sizeof(int); i++){
		printf("%d ", node[i]);
	}
	printf("\n");

	isSelfCrossing(node, 4);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NODE{
	int data;
	struct NODE *next;
};

struct MASTER{
	//tra=0 == queue, tra=1 == stack
	int size, tra;
	struct NODE *first, *rear;
	struct MASTER *next;
};

typedef struct NODE node;
typedef struct MASTER master;	

void start (master *head) {
	head->tra = 0;
	head->size = 0;
	head->first = NULL;
	head->rear = head->first;
	head->next = NULL;
}

int main () {
	master *head;

	start(head);
	printf("tra: %d\n", head->tra);


	return 0;
}
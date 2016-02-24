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
	head->tra = head->size = 0;
	head->first = (node *) malloc(sizeof(node));
	head->rear = (node *) malloc(sizeof(node));
	if(!head->first || !head->rear)
		exit(1);
	head->rear = head->first;
}		

void transform (master *head, int position) {
	int i=0;
	while(i!=position && head!=NULL) {
		head = head->next;
		i++;
	}
	if(i!=position) {
		printf("invalid position\n");
		return;
	}
	if (head->tra == 0)
		head->tra++;
	else
		head->tra--;
}


node* stack_push (node *head, int value) {
	if(!head) {
		head->data = value;
		head->next = NULL;
	}
	else {
		node *temp = (node *) malloc(sizeof(node));
		if(!temp)
			exit(2);
		temp->data = value;
		temp->next = head;
		return temp;
	}
}

node* enqueue (node *rear, int value) {
	node *temp = (node *) malloc(sizeof(node));
	temp->data = value;
	temp->next = NULL;
	rear->next = temp;
	return temp;
}

void add_data (master *head, int position, int value) {
	int i=0;
	while(i!=position && head!=NULL) {
		head = head->next;
		i++;
	}
	if(i!=position) {
		printf("invalid position\n");
		return;
	}
	if(head->rear == head->first && head->size == 0) {
		head->rear->data = value;
		head->size++;
	}
	else if(head->tra == 1) {
		head->first = stack_push(head->first, value);
		head->size++;
	}
	else if (head->tra == 0) {
		head->rear = enqueue(head->rear, value);
		head->size++;
	}
}

void print_pos (master *head, int position) {
	int i=0;
	while(i!=position && head!=NULL) {
		head = head->next;
		i++;
	}
	if(i!=position) {
		printf("invalid position\n");
		return;
	}
	if(head->size == 0) {
		printf("empty list\n");
		return;
	}
	printf("there are %d elements on this list\n", head->size);
	printf("the list on position %d is: ", position);
	while(head->first != NULL) {
		printf("%d, ", head->first->data);
		head->first = head->first->next;
	}
	printf("\n");
}



int main () {
	int value, position, caso=0;
	char choice[5];
	master *head = (master *) malloc(sizeof(master));
	if(!head)
		exit(1);
	start(head);
	while(scanf(" %s", choice) != EOF) {
		if(!strcmp(choice, "ADD")) {
			scanf("%d %d", &position, &value);
			add_data(head, position, value);
		}
		if(!strcmp(choice, "PRI")) {
			scanf("%d", &position);
			print_pos(head, position);
		}
		if(!strcmp(choice, "TRA")) {
			scanf("%d", &position);
			transform(head, position);
		}




	}
	return 0;
}
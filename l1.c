#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NODE {
	int data, tra;
	struct NODE *next; 
	struct NODE *below;
};
 
typedef struct NODE node;

void start (node *head) {
	head->tra = 1;
	head->below = NULL;
	head->next = NULL;
}

//add no final da fila
void enqueue (node *head, int value) {
	while (head->next != NULL) 
		head = head->next;
	node *temp = (node*) malloc (sizeof(node)); 
	if(!temp) 
		return;	
	temp->tra = head->tra;
	temp->data = value;
	temp->next = NULL;
	head->next = temp;
}
//add no começo da pilha
void stack_push (node *head, int value) {
	node *temp = (node *) malloc(sizeof(node));
	if (!temp) 
		return;
	temp->tra = head->tra;
	temp->data = head->data;
	temp->data = value;
	temp->next = head->next;
	head->next = temp;
}
void add_data (node *head) {
	int position, value, i=0;
	scanf("%d %d", &position, &value);
	while(i != position) {
		if(head->below != NULL) {
			i++;
			head = head->below;
		}
		else
			return;
	}
	if(i == position) {
		if(head->tra > 0) //se for fila
			enqueue(head, value);
		else //pilha
			stack_push(head, value);
	}
}

void TRA (node *head) {
	int position, i=0, j=0, valorhead;
	scanf("%d", &position);
	while(i != position) {
		if(head->below != NULL) {
			i++;
			head = head->below;
		}
		else 
			return;
	}
	while(head->next != NULL) {
		if (j==0) {
			head->tra = head->tra * (-1);
			valorhead = head->tra;
		}
		else 
			head->tra = valorhead;
		j++;
		head = head->next;
	}
}

void update_tra (node *head, int position) {
	int i=0, headtra;
	while(i!=position){
		if(head->below != NULL)
			head = head->below;
		else
			return;
	}
	if(i==position) {
		headtra = head->tra;
		while(head->next!=NULL){
			head->tra = headtra;
			head = head->next;
		}
	}

}

void node_deleter (node *head) {
	int position, i=0;
	scanf("%d", &position);
	while(i != position) {
		if(head->below != NULL){
			i++;
			head = head->below;
		}
		else 
			return;
	}
	if(i == position) {
	    if (head->next!=NULL) {
	        node *temp = (node *) malloc(sizeof(node));
	        if(!temp)
	        	exit(4);
	        temp = head;
	        temp = temp->next;
	        head->next = temp->next;
	        free(temp);
    	}
    }
}

int tamanho (node *head) {
	int i=0;
	while(head->next!=NULL) {
		head = head->next;
		i++;
	}
	return i;
}

int is_it_empty (node *head) {
	int i = -1; //it's null
	if(head->next!=NULL) {
		i = 1;
		return i;
	}
	else
		return i;
}


node* split (node *head, int position) {
	node *temphead = (node *) malloc(sizeof(node));
	temphead = head;
	int metade, j=0;
	metade = tamanho(temphead)/2;
	while(j!=metade) {
		if(temphead->next != NULL) {
			temphead = temphead->next;
			j++;
		}
		else
			return;
	}
	if(temphead!=NULL) {
		node *temphead2 = (node *) malloc(sizeof(node));
		if(!temphead2)
			exit(4);
		temphead2 = temphead->next;
		temphead->next = NULL;
		return temphead2;
	}
}

void split_master (node *head, int position) {
	int i=0;
	while(i != position) {
		if(head->below != NULL) {
			i++;
			head = head->below;
		}
		else 
			return;
	}
	if (position == i) {
		node *temp = (node *) malloc(sizeof(node));
		if(is_it_empty(head) > 0) {
			if(head->below == NULL) {
				temp = split(head, position);
				head->below = temp;
			}
			else {
				temp = head->below;
				head->below = split(head, position);
				head->below->below= temp;
			}
			stack_push(head->below, head->below->data);
		}
		else {
			stack_push(head, 1);
			if(head->below == NULL) {
				temp = split(head, position);
				head->below = temp;
			}
			else {
				temp = head->below;
				head->below = split(head, position);			
				head->below->below= temp;
			}
			head = head->below; //won't glitch out
			if (head->next!=NULL) { //just in case (...)
		        node *temp2 = (node *) malloc(sizeof(node));
		        if(!temp2)
		        	exit(4);
		        temp2 = head;
		        temp2 = temp2->next;
		        head->next = temp2->next;
		        free(temp2);
			}
		}
	}
}

//JUST FOR DEBUGGING!!!
void print_list(node *head) {
	int i=0, position, j=0; // 0 == head 
	printf("position to print:\n");
	scanf("%d", &position);
	while(j != position) {
		if(head->below != NULL){
			j++;
			head = head->below;
		}
		else {
			printf("posição invalida, fora da lista\n");
			return;
		}
	}
	if(j == position) {
		printf("Here's the freaking list you asked for, paguso:\n");
		while (head->next != NULL) {
			if(i!=0) //o head n pode ser printado, pq nulo
				printf("%d ==> ", head->data);
			head = head->next;
			i++;
		}
		if(i==0)
			printf("Well, it's fucking empty, you happy?!");
		else
			printf("%d <== END OF THE FUCKING LIST", head->data);
		printf("\n\n");
	}
}

//JUST FOR DEBUGGING REASONS!!
void how_many (node *head) {
	int i = 0;
	while(head->below != NULL) {
		head = head->below;
		i++;
	}
	printf("there are %d nodes below\n", i);
}

node* merge (node *head, int pos2) {
	int i=0;
	node *temphead2 = (node *) malloc(sizeof(node));
	while(i != pos2) {
		if(head->below != NULL) {
			i++;
			head = head->below;
		}
		else 
			return;
	}
	temphead2 = head; // ->next
	head= NULL;
	return temphead2;
}

void merge_master (node *head, node *head2, int pos1) {
	int i=0;
	while(i != pos1) {
		if(head->below != NULL) {
			i++;
			head = head->below;
		}
		else 
			return;
	}
	while(head->next != NULL)
		head = head->next;
	head->next = head2;
}

void merge_node_deleter_pos2(node *head, node *head2, int posicao) {
	int i=0;
	node *temp = (node *) malloc(sizeof(node));
	//if pos 2 > pos 1, ele deleta o node da pos2
    while(i<(posicao-1)) {
        if(head->below!=NULL) {
            head = head->below;
            i++;
        }
    }
    if(head->below !=NULL) {
        temp = head2->below;
        head->below = temp;
        head2->below = NULL;
    }
}

node* merge_node_deleter_head (node *head) {
        node *temp = (node *) malloc(sizeof(node));
        if(head->below != NULL)
		head = head->below;
        return head;
}

void merge_node_deleter_pos1 (node *head, int position) {
	int i=0;
	node *anterior = (node *) malloc(sizeof(node));
	if (!anterior)
		exit(4);
	while(i!=position-1) {
		anterior = head;
		head = head->below;
		i++;
	}
	anterior->below = head->below;
}	

void finish_him (node *head) {
	while(head->below != NULL) {
		if(head->next == NULL)
			printf("? ");
		else
			printf("%d ", head->next->data);
		head = head->below;
	}
	if(head->next!=NULL)
		printf("%d\n\n", head->next->data);
	else
		printf("?\n\n");
}

int main() {
	node *head;
	head = (node *) malloc (sizeof(node));
	char choice[4];
	int position, pos1, pos2, caso=0;
	if (!head)
		exit(1);
	start(head);
	while (scanf(" %s", choice)!=EOF) {
		if(strcmp(choice, "ADD")==0) {
			add_data(head);
		}
		else if (strcmp(choice, "DEL") == 0) {
			node_deleter(head);
		}
		else if (strcmp(choice, "TRA") == 0) {
			TRA(head);
		}
		else if (strcmp(choice, "SPL") == 0) {
			scanf("%d", &position);
			split_master(head, position);
		}
		else if (strcmp(choice, "MER") == 0) {
			scanf("%d %d", &pos1, &pos2);
			if(pos1!=pos2) {
				node *head2 = (node *) malloc(sizeof(node));
				head2 = merge(head, pos2);
				merge_master(head, head2->next, pos1);
				update_tra(head, pos1);
				if (pos2 == 0)
					head = merge_node_deleter_head(head);
				else if (pos2>pos1)
					merge_node_deleter_pos2(head, head2, pos2);
				else if (pos1>pos2)
					merge_node_deleter_pos1(head, pos1);
				free(head2);
			}
		}
		else if (strcmp(choice, "END") == 0) {
			printf("caso %d: ", caso);
			finish_him(head);
			node *novohead = (node *) malloc(sizeof(node));
			if(!novohead)
				exit(1);
			head = novohead;
			start(head);
			caso++;
		}
	}
	printf("\n");
	return 0;
}

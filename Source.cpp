#include<iostream>
#include<stdio.h>

struct Employee {
	int id;
	char* name;
};

struct Node {
	Employee* info;
	Node* next;
};

Node* createNode(Employee* e) {
	Node* n = new Node;
	n->info = e;
	n->next = NULL;

	return n;
}

/* Insert at the beginning of the list. */
void insertBefore(Node*& lst, Node* n) {
	if (lst == NULL) {
		lst = n;
	}
	else {
		n->next = lst;
		lst = n;
	}
}
/* Insert at the end of the list */
void insertAfter(Node*& lst, Node* n) {
	if (lst == NULL) {
		lst = n;
	}
	else {
		Node* tmp = lst;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		n->next = tmp->next;
		tmp->next = n;
	}
}

/* Insert after a value given */
void insertBetween(Node*& lst, Node* n, int val) {
	if (lst == NULL) {
		lst = n;
	}
	else {
		Node* tmp = lst;
		while (tmp->next != NULL && tmp->info->id != val) {
			tmp = tmp->next;
		}
		n->next = tmp->next;
		tmp->next = n;
	}
}

/* delete a node with a value given*/
void deleteNode(Node*& lst) {
	if (lst) {
		printf("ID to delete: ");
		int id;
		scanf("%d", &id);

		if (lst->info->id == id) {
			Node* toDel = lst;
			lst = toDel->next;
			free(toDel->info->name);
			free(toDel);
		}
		else {
			Node* tmp = lst;
			while (tmp->next != NULL && tmp->next->info->id != id) {
				tmp = tmp->next;
			}
			if (tmp->next != NULL) {
				Node* toDel = tmp->next;
				tmp->next = toDel->next;
				free(toDel->info->name);
				free(toDel);
			}
			else {
				printf("No values found.");
			}
		}
	}
}

/* Printing the list */
void printList(Node* lst) {
	if (lst == NULL) {
		printf("NULL list.\n");
	}
	else {
		Node* tmp = lst;
		printf("\nList elements: \n");

		while (tmp->next != NULL) {
			printf("id: %d Name: %s. \n", tmp->info->id, tmp->info->name);
			tmp = tmp->next;
		}
		printf("id: %d Name: %s. \n", tmp->info->id, tmp->info->name);
	}
}

void main() {
	Node* lst = nullptr;

	Node* node = NULL;

	for (int i = 0; i < 3; i++) {
		Employee* e = new Employee;

		printf("ID: ");
		scanf("%d", &e->id);

		printf("Name: ");
		char aux[20];
		scanf("%s", &aux);
		e->name = (char*)malloc(strlen(aux) + 1);
		strcpy(e->name, aux);

		node = createNode(e);
		//insertBefore(lst, node);
		insertAfter(lst, node);

	}

	Employee* e = new Employee;

	printf("ID: ");
	scanf("%d", &e->id);

	printf("Name: ");
	char aux[20];
	scanf("%s", &aux);
	e->name = (char*)malloc(strlen(aux) + 1);
	strcpy(e->name, aux);

	node = createNode(e);

	insertBetween(lst, node, 3);

	printList(lst);

	deleteNode(lst);

	printList(lst);
}
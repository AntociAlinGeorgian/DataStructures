#include<iostream>
#include<stdio.h>

struct Employee {
	int id;
	char* name;
};

struct Node {
	Employee* info;
	Node* next;
	Node* prev;
};

Node* createNode(Employee* e) {
	Node* n = new Node;
	n->info = e;
	n->prev = NULL;
	n->next = NULL;

	return n;
}

void insertBefore(Node*& lst, Node* node) {
	if (lst == NULL) {
		lst = node;
	}
	else {
		lst->prev = node;
		node->next = lst;
		lst = node;
	}
}

void insertAfter(Node*& lst, Node* node) {
	if (lst == NULL) {
		lst = node;
	}
	else {
		Node* tmp = lst;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = node;
		node->prev = node;
	}
}

void printList(Node* lst) {
	if (lst) {
		Node* tmp = lst;
		while (tmp->next != NULL) {
			printf("ID: %d - Name: %s \n", tmp->info->id, tmp->info->name);
			tmp = tmp->next;
		}
		printf("ID: %d - Name: %s \n", tmp->info->id, tmp->info->name);
	}
}

void readFromFile(Node*& lst) {
	FILE* f = fopen("Text.txt","r");
	if (f) {
		while (!feof(f)) {
			Employee* e = new Employee;

			fscanf(f, "%d", &e->id);
			char aux[100];
			fscanf(f, "%s", &aux);

			e->name = (char*)malloc(strlen(aux) + 1);
			strcpy(e->name, aux);

			Node* n = createNode(e);

			//insertBefore(lst, n);
			insertAfter(lst, n);
		}
	}
}

void insertBetween(Node*& lst) {
	
		Node* tmp = lst;

		Node* node = nullptr;
		Employee* e = new Employee;
		int id;

		printf("Insert:\n");
		printf("ID: ");
		scanf("%d", &e->id);

		char aux[20];
		printf("Name: ");
		scanf("%s", &aux);
		e->name = (char*)malloc(strlen(aux) + 1);
		strcpy(e->name, aux);

		node = createNode(e);

		printf("Insert after id: ");
		scanf("%d", &id);

		while (tmp->next != NULL && tmp->info->id != id) {
			tmp = tmp->next;
		}
		if (tmp->next == NULL) {
			node->next = tmp->next;
			node->prev = tmp;
			tmp->next = node;
		}
		else {
			node->next = tmp->next;
			node->prev = tmp;
			tmp->next->prev = node;
			tmp->next = node;
		}
}

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
				if (toDel->next != NULL) {
					toDel->next->prev = tmp;
				}
				free(toDel->info->name);
				free(toDel);
			}
		}
	}
}

void main() {
	Node* lst = nullptr;

	readFromFile(lst);

	printList(lst);

	//insertBetween(lst);

	//printList(lst);

	deleteNode(lst);

	printList(lst);
}
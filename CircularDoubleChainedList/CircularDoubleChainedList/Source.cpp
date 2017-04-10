#include<iostream>
#include<stdint.h>

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
	n->next = NULL;
	n->prev = NULL;

	return n;
}

void insertBefore(Node*& lst, Node* n) {
	if (lst == NULL) {
		n->next = n;
		n->prev = n;
		lst = n;
	}
	else {
		n->next = lst;
		n->prev = lst->prev;
		lst->prev = n;
		n->prev->next = n;
		lst = n;
	}
}

void insertAfter(Node*& lst, Node* n) {
	if (lst == NULL) {
		n->next = n;
		n->prev = n;
		lst = n;
	}
	else {
		n->next = lst;
		n->prev = lst->prev;
		lst->prev = n;
		n->prev->next = n;
	}
}

void readList(Node* lst) {
	if (lst) {
		Node* tmp = lst;
		Node* first = lst;
		while (tmp->next != first) {
			printf("%d. %s\n", tmp->info->id, tmp->info->name);
			tmp = tmp->next;
		}
		printf("%d. %s\n", tmp->info->id, tmp->info->name);
	}
}

void readFromFile(Node*& lst) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Employee* e = new Employee;
			fscanf(f,"%d", &e->id);
			char aux[100];
			fscanf(f,"%s", &aux);
			e->name = (char*)malloc(strlen(aux) + 1);
			strcpy(e->name, aux);

			Node* n = createNode(e);

			//insertBefore(lst, n);
			insertAfter(lst, n);
		}
	}
}

void deleteNode(Node*& lst, int id) {
	if (lst) {
		Node* tmp = lst;
		Node* first = lst;

		int deleted = 0;

		if (first->info->id == id && first->next!=first && first->prev!=first) {
			free(lst);
			lst = NULL;
			deleted = 1;
		}
		
		if (deleted == 0) {
			while (tmp->next != first && tmp->next->info->id != id) {
				tmp = tmp->next;
			}

			if (tmp->next->info->id == id) {
				Node* toDel = tmp->next;
				tmp->next = toDel->next;
				toDel->next->prev = tmp;
				free(toDel);
			}
		}
		
	}
}
void main() {
	Node* lst = nullptr;
	readFromFile(lst);
	readList(lst);

	deleteNode(lst,2);

	readList(lst);
}
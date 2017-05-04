#include<iostream>
#include<stdio.h>

struct Elev {
	int id;
	//char* info;
};

struct Nod {
	Elev* info;
	Nod* next;
};

Nod* creareNod(Elev* e) {
	Nod* n = new Nod;
	n->info = e;
	n->next = NULL;
	return n;
}

void inserare(Nod*& stiva, Nod* n) {
	if (stiva == NULL) {
		stiva = n;
	}
	else {
		n->next = stiva;
		stiva = n;
	}
}

Nod* extragere(Nod** stiva) {
	Nod* tmp = (*stiva);
	(*stiva) = tmp->next;
	return tmp;
}

void citire(Nod*& stiva) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Elev* e = new Elev;
			fscanf(f, "%d", &e->id);
			Nod* n = creareNod(e);
			inserare(stiva, n);
		}
	}
}

void parcurgere(Nod* stiva) {
	if (stiva) {
		while (stiva != NULL) {
			Nod* tmp = extragere(&stiva);
			printf("%d\n", tmp->info->id);
		}
	}
}

void main() {
	Nod* stiva = nullptr;
	citire(stiva);
	parcurgere(stiva);
}
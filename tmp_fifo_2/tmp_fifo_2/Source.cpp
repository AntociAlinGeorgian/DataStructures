#include<iostream>
#include<stdio.h>

struct Elev {
	int id;
	char* nume;
};

struct Nod {
	Elev* info;
	Nod* next;
};

struct Coada {
	Nod* prim;
	Nod* ultim;
};

Nod* creareNod(Elev* e) {
	Nod* n = new Nod;
	n->info = e;
	n->next = NULL;
	return n;
}

void insertNod(Coada*& coada, Nod* n) {
	if (coada->prim == NULL) {
		coada->prim = coada->ultim = n;
	}
	else {
		coada->ultim->next = n;
		coada->ultim = n;
	}
}

Nod* extragere(Coada** coada) {
	Nod* extras = (*coada)->prim;
	(*coada)->prim = extras->next;
	return extras;
}

void citireFisier(Coada*& coada) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Elev* e = new Elev;
			fscanf(f, "%d", &e->id);
			char aux[10];
			fscanf(f, "%s", &aux);
			e->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(e->nume, aux);

			Nod* n = creareNod(e);
			insertNod(coada, n);
		}
	}
}

void parcurgere(Coada* coada) {
	if (coada) {
		while (coada->prim != NULL) {
			Nod* tmp = extragere(&coada);
			printf("%d. %s \n", tmp->info->id, tmp->info->nume);
		}
	}
}

void main() {
	Coada* coada = new Coada;
	coada->prim = coada->ultim = NULL;
	citireFisier(coada);
	parcurgere(coada);
}
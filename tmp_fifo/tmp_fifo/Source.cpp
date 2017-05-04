#include<iostream>
#include<stdio.h>

struct Stud {
	int id;
	char* nume;
};

struct Nod {
	Stud* info;
	Nod* next;
};

struct FIFO {
	Nod* prim;
	Nod* ultim;
};

Nod* creareNod(Stud* s) {
	Nod* n = new Nod;
	n->info = s;
	n->next = NULL;
	return n;
}

void initCoada(FIFO*& f) {
	f->prim = f->ultim = NULL;
}

void inserareNod(FIFO*& f, Nod* n) {
	if (f->prim == NULL) {
		f->prim = f->ultim = n;
	}
	else {
		f->ultim->next = n;
		f->ultim = n;
	}
}

Nod* extragereNod(FIFO** f) {
	Nod* extrage = (*f)->prim;
	(*f)->prim = extrage->next;
	return extrage;
}

void citire(FIFO*& fifo) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Stud* s = new Stud;
			fscanf(f,"%d", &s->id);
			char aux[20];
			fscanf(f, "%s", &aux);
			s->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(s->nume, aux);

			Nod* n = creareNod(s);
			inserareNod(fifo, n);
		}
	}
}

void afisare(FIFO* f) {
	if (f) {
		while (f->prim != NULL) {
			Nod* tmp = extragereNod(&f);
			printf("%d. %s\n", tmp->info->id, tmp->info->nume);
		}
	}
}

void main() {
	FIFO* f = new FIFO;
	initCoada(f);
	citire(f);
	afisare(f);
}
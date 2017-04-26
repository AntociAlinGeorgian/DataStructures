#include<stdio.h>
#include<iostream>

enum tipAngajat {
	PROF, MED
};

union tipOreLucrate {
	double nrOreGarda;
	int nrOreNorma;
};

struct Angajat {
	char* nume;
	tipAngajat profesie;
	tipOreLucrate oreLucrate;
};

struct Nod {
	Angajat* info;
	Nod* next;
};

struct Coada {
	Nod* prim;
	Nod* ultim;
};


void initCoada(Coada*& coada) {
	coada->prim = coada->ultim = NULL;
}


Nod* creareNod(Angajat* a) {
	Nod* n = new Nod;
	n->info = a;
	n->next = NULL;
	return n;
}

bool emptyCoada(Coada* c) {
	if (c->prim == NULL) {
		return true;
	}
	else {
		return false;
	}
}


void inserareCoada(Coada*& coada, Nod* nou) {
	if (emptyCoada(coada) != NULL) {
		coada->prim = coada->ultim = nou;
	}
	else {
		coada->ultim->next = nou;
		coada->ultim = nou;
	}
}

Nod* extragereNod(Coada** coada) {
	Nod* extrage = (*coada)->prim;
	(*coada)->prim = extrage->next;
	return extrage;
}

void citireFisier(Coada*& coada) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Angajat* a = new Angajat;

			char aux[10];
			fscanf(f, "%s", &aux);
			a->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(a->nume, aux);

			int tipAng;
			fscanf(f, "%d", &tipAng);

			switch (tipAng) {
			case 0:
				a->profesie = PROF;
				fscanf(f, "%d", &a->oreLucrate.nrOreNorma);
				break;
			case 1:
				a->profesie = MED;
				fscanf(f, "%lf", &a->oreLucrate.nrOreGarda);
				break;
			}

			Nod* n = creareNod(a);
			inserareCoada(coada, n);
		}
		fclose(f);
	}

}

void parcurgereCoada(Coada* c) {
	while (!emptyCoada(c)) {
		Nod* tmp = extragereNod(&c);
		printf("%s \n", tmp->info->nume);
	}
}

void stergereNume(Coada*& coada, char* nume) {
	if (!emptyCoada(coada)) {
		if (strcmp(coada->prim->info->nume, nume) == 0) {
			Nod* sterge = coada->prim;
			coada->prim = sterge->next;
			free(sterge);
		}
	}

	Nod* lista = coada->prim;
	while (lista->next != NULL && (strcmp(lista->next->info->nume, nume) != 0)) {
		lista = lista->next;
	}

	if (lista->next) {
		Nod* sterge = lista->next;
		lista->next = sterge->next;
		free(sterge);
	}
}

void main() {
	Coada* c = new Coada;
	initCoada(c);

	citireFisier(c);

	stergereNume(c, "Costel");

	parcurgereCoada(c);
}


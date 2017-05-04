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

void initCoada(Coada*& c) {
	c->prim = c->ultim = NULL;
}

bool emptyCoada(Coada* c) {
	if (c->prim == NULL) {
		return true;
	}
	else {
		return false;
	}
}

Nod* creareNod(Angajat* a) {
	Nod* n = new Nod;
	n->info = a;
	n->next = NULL;
	return n;
}

void inserareCoada(Coada*& c, Nod* n) {
	if (c->prim==NULL) {
		c->prim = c->ultim = n;
	}
	else {
		c->ultim->next = n;
		c->ultim = n;
	}
}

Nod* extragereNod(Coada** c) {
	Nod* extrage = (*c)->prim;
	(*c)->prim = extrage->next;
	return extrage;
}

void parcurgereLista(Coada* c) {
	if (c) {
		Nod* tmp = c->prim;
		while (tmp!=NULL) {
			printf("%s \n", tmp->info->nume);
			tmp = tmp->next;
		}
	}
}

void citireFisier(Coada*& c) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Angajat* a = new Angajat;
			
			char aux[20];
			fscanf(f, "%s", &aux);
			a->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(a->nume, aux);

			int prof;
			fscanf(f, "%d", &prof);

			switch (prof) {
			case 0:
				a->profesie = MED;
				fscanf(f, "%ld", &a->oreLucrate.nrOreGarda);
				break;
			case 1:
				a->profesie = PROF;
				fscanf(f, "%d", &a->oreLucrate.nrOreNorma);
				break;
			}

			Nod* n = creareNod(a);
			inserareCoada(c, n);
			
		}
		fclose(f);
	}
}

void stergereNod(Coada*& c, char* nume) {
	if (c) {
		//verificam primul nod
		if (strcmp(c->prim->info->nume, nume) == 0) {
			Nod* deExtras = c->prim;
			c->prim = deExtras->next;
			free(deExtras);
		}
		Nod* lista = c->prim;
		while (lista->next != NULL && (strcmp(lista->next->info->nume, nume) != 0)) {
			lista = lista->next;
		}
		if (lista->next != NULL) {
			Nod* sterge = lista->next;
			lista->next = sterge->next;
			free(sterge);
		}
	}
}

void main() {
	Coada* c = new Coada;
	initCoada(c);
	citireFisier(c);
	stergereNod(c, "Andrei");
	parcurgereLista(c);
}
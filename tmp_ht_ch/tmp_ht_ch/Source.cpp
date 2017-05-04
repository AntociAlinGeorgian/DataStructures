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

struct HashTable {
	int dim;
	Nod** vector;
};

Nod* creareNod(Stud* s) {
	Nod* nod = new Nod;
	nod->info = s;
	nod->next = NULL;
	return nod;
}

HashTable* initHT(int dim) {
	HashTable* ht = new HashTable;
	ht->dim = dim;
	ht->vector = (Nod**)malloc(sizeof(Nod*)*dim);

	for (int i = 0; i < ht->dim; i++) {
		ht->vector[i] = NULL;
	}

	return ht;
}

int fhash(int dim, char* nume) {
	return(nume[0] % dim);
}

void inserarLista(Nod*& lst, Nod* n) {
	if (lst == NULL) {
		lst = n;
	}
	else {
		Nod* tmp = lst;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = n;
	}
}

void inserareHT(HashTable*& ht, Nod* n) {
	int poz = fhash(ht->dim,n->info->nume);

	Nod* lst = ht->vector[poz];
	inserarLista(lst, n);
	ht->vector[poz] = lst;
}

void citireFisier(HashTable*& ht) {
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
			inserareHT(ht, n);
		}
	}
}

void afisareHT(HashTable* ht) {
	if (ht) {
		for (int i = 0; i < ht->dim; i++) {
			Nod* lista = ht->vector[i];
			while (lista != NULL) {
				printf("%d. %s \n", lista->info->id, lista->info->nume);
				lista = lista->next;
			}
		}
	}
}

void main() {
	HashTable* ht = initHT(27);
	citireFisier(ht);
	afisareHT(ht);
}
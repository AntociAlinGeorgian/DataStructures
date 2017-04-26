#include<iostream>
#include<stdio.h>

enum Furnizor {
	Telekom, Orange, Upc
};

struct Abonat {
	char* nume;
	float valoareAbonament;
	Furnizor tipFurnizor;
};

struct Nod {
	Abonat* info;
	Nod* next;
};

struct HT {
	int dimHT;
	Nod** vector;
};

int fhash(char* nume, int dim) {
	return(nume[0] % dim);
}

Nod* creareNod(Abonat* a) {
	Nod* nod = new Nod;
	nod->info = a;
	nod->next = NULL;
	return nod;
}

void inserareNod(Nod*& lista, Nod* n) {
	if (lista == NULL) {
		lista = n;
	}
	else {
		Nod* tmp = lista;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = n;
	}
}

HT* initHT(int dim) {
	HT* ht = new HT;
	ht->dimHT = dim;
	ht->vector = (Nod**)malloc(sizeof(Nod*)*ht->dimHT);

	for (int i = 0; i < ht->dimHT; i++) {
		ht->vector[i] = NULL;
	}

	return ht;
}

void inserareHT(HT*& ht, Nod* n) {
	int poz = fhash(n->info->nume, ht->dimHT);

	Nod* lista = ht->vector[poz];
	inserareNod(lista, n);

	ht->vector[poz] = lista;
}

void citireFisier(HT*& ht) {
	FILE* f = fopen("Text.txt", "r");

	if (f) {
		while (!feof(f)) {
			Abonat* a = new Abonat;

			char aux[10];
			fscanf(f, "%s", &aux);
			a->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(a->nume, aux);

			fscanf(f, "%f", &a->valoareAbonament);

			fscanf(f, "%d", &a->tipFurnizor);
			

			Nod* n = creareNod(a);
			inserareHT(ht, n);
		}
	}
}

void parcurgereHT(HT* ht) {
	if (ht) {
		for (int i = 0; i < ht->dimHT; i++) {
			Nod* lista = ht->vector[i];
			
			while (lista != NULL) {
				printf("%s - %5.2f \n",ht->vector[i]->info->nume,ht->vector[i]->info->valoareAbonament);
				lista = lista->next;
			}
		}
	}
}

void main() {
	HT* ht = initHT(21);
	citireFisier(ht);
	parcurgereHT(ht);
}
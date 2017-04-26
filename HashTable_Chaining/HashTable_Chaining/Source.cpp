#include<iostream>
#include<stdio.h>

enum Furnizor{
	TELEKOM,ORANGE,UPC
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

struct HashTable {
	Nod** vector;
	int dimHT;
};

int fhash(char* nume, int dimHT) {
	return nume[0] % dimHT;
}

HashTable* initHT(int dim) {
	HashTable* ht = new HashTable;
	ht->dimHT = dim;
	ht->vector = (Nod**)malloc(sizeof(Nod*)*dim);

	for (int i = 0; i < ht->dimHT; i++) {
		ht->vector[i] = NULL;
	}

	return ht;
}

Nod* creareNod(Abonat* a) {
	Nod* n = new Nod;
	n->info = a;
	n->next = NULL;
	return n;
}

void inserareNod(Nod*& lst, Nod* nod) {
	if (lst == NULL) {
		lst = nod;
	}
	else {
		Nod* tmp = lst;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = nod;
	}
}


void inserareHT(HashTable*& ht, Nod* n) {
	int poz = fhash(n->info->nume, ht->dimHT);

	Nod* lista = ht->vector[poz];
	inserareNod(lista, n);

	ht->vector[poz] = lista;
}

void citireFisier(HashTable*& ht) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Abonat* a = new Abonat;
			char aux[100];

			fscanf(f, "%s", &aux);
			a->nume = (char*)malloc(sizeof(aux) + 1);
			strcpy(a->nume, aux);

			fscanf(f, "%f", &a->valoareAbonament);
			fscanf(f, "%d", &a->tipFurnizor);

			Nod* n = creareNod(a);
			inserareHT(ht, n);
		}
	}
	fclose(f);
}


void afisareHT(HashTable* ht) {
	for (int i = 0; i < ht->dimHT; i++) {
		Nod* lista = ht->vector[i];
		while (lista != NULL) {
			printf("%s - %5.2f \n", lista->info->nume, lista->info->valoareAbonament);
			lista = lista->next;
		}
	}
}

void main() {
	HashTable* ht = initHT(15);
	citireFisier(ht);
	afisareHT(ht);
}

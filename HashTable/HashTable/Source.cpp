#include<iostream>
#include<stdio.h>

struct Student {
	char* nume;
	int nota;
};

struct Nod {
	Student* info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dimHT;
};

//functia hash
int fhash(int nota, int dim) {
	return nota%dim;
}

Nod* creareNod(Student* s) {
	Nod* n = new Nod;
	n->info = s;
	n->next = NULL;

	return n;
}

HashTable* initHT(int dim) {
	HashTable* ht = new HashTable;
	ht->vector = (Nod**)malloc(sizeof(Nod*)*dim);
	ht->dimHT = dim;

	for (int i = 0; i < ht->dimHT; i++) {
		ht->vector[i] = NULL;
	}
	return ht;
}

void inserareHT(HashTable*& ht, Nod* nod) {
	int poz = fhash(nod->info->nota, ht->dimHT);

	if (ht->vector[poz] == NULL) {
		ht->vector[poz] = nod;
	}
	else {
		while (poz < ht->dimHT && ht->vector[poz] != NULL) {
			//parcurgem vectorul pornind de la pozitia in care am gasit cheia in jos
			poz++;
		}
		if (poz == ht->dimHT) {
			//daca am ajuns la finalul vectorului
			poz = fhash(nod->info->nota, ht->dimHT);
			while (poz > 0 && ht->vector[poz] != NULL) {
				//parcurgem vectorul pornind de la pozitia in care am gasit cheia in jos
				poz--;

				if (poz == 0) {
					//daca ajungem la inceputul vectorului apare coliziunea de tip linear probing
					//si nu putem insera elementul pentru ca vectorul este ocupat in totalitate
					printf("\nColiziune!");
				}
				else {
					ht->vector[poz] = nod;
				}
			}
		}
		else {
			ht->vector[poz] = nod;
		}
	}
}
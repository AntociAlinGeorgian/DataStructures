#include<stdio.h>
#include<iostream>

struct Stud {
	int id;
	char* nume;
};

struct Nod {
	Stud* info;
	Nod* next;
};

struct HashTable {
	int dimHT;
	Nod** vector;
};

Nod* creareNod(Stud* info) {
	Nod* nou = new Nod;
	nou->info = info;
	nou->next = NULL;
	return nou;
}

int fhash(int dim, char* nume) {
	return(nume[0] % dim);
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

void inserareHT(HashTable*& ht, Nod* nod) {
	int poz = fhash(ht->dimHT, nod->info->nume);

	if (ht->vector[poz] == NULL) {
		ht->vector[poz] = nod;
	}
	else {
		while (ht->vector[poz] != NULL && poz < ht->dimHT) {
			poz++;
		}
		if (poz == ht->dimHT) {
			int poz = fhash(ht->dimHT, nod->info->nume);
			while (ht->vector[poz] != NULL && poz > 0) {
				poz--;
			}
			if (poz == 0) {
				printf("Coliziune! \n");
			}
			else {
				ht->vector[poz] = nod;
			}
		}
		else {
			ht->vector[poz] = nod;
		}
	}
}


void citireFisier(HashTable*& ht) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Stud* s = new Stud;
			fscanf(f, "%d", &s->id);

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
		for (int i = 0; i < ht->dimHT; i++) {
			if (ht->vector[i] != NULL) {
				printf("%d. %s\n",ht->vector[i]->info->id,ht->vector[i]->info->nume);
			}
		}
	}
}

void stergereID(HashTable*& ht, int id) {
	if (ht) {
		for (int i = 0; i < ht->dimHT; i++) {
			if (ht->vector[i] != NULL) {
				if (ht->vector[i]->info->id == id) {
					free(ht->vector[i]->info->nume);
					free(ht->vector[i]);
					ht->vector[i] = NULL;
				}
			}
		}
	}
}

void main() {
	HashTable* ht = initHT(21);
	citireFisier(ht);
	stergereID(ht, 6);
	afisareHT(ht);
}
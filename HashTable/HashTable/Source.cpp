#include<iostream>
#include<stdio.h>

struct Student {
	int nota;
	char* nume;
};

struct Nod {
	Student* info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dimHT;
};

int fhash(int nota, int dim) {
	return(nota%dim);
}

Nod* creareNod(Student* stud) {
	Nod* nod = new Nod;
	nod->info = stud;
	nod->next = NULL;
	return nod;
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
			poz++;
		}
		if (poz == ht->dimHT) {
			int poz = fhash(nod->info->nota, ht->dimHT);
			while (poz > 0 && ht->vector[poz] != NULL) {
				poz--;
			}
			if (poz == 0) {
				printf("coliziune!\n");
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
			Student* s = new Student;
			char aux[100];

			fscanf(f, "%s", &aux);
			s->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(s->nume, aux);

			fscanf(f, "%d", &s->nota);

			Nod* n = creareNod(s);
			inserareHT(ht, n);
		}
	}
}

void parcurgere(HashTable* ht) {
	if (ht) {
		for (int i = 0; i < ht->dimHT; i++) {
			if (ht->vector[i] != NULL) {
				printf("%d. %s - %d \n", i, ht->vector[i]->info->nume, ht->vector[i]->info->nota);
			}
		}
	}
}


void cautare(HashTable* ht, int nota) {
	int poz = fhash(nota, ht->dimHT);
	bool gasit = false;

	if (ht->vector[poz] != NULL) {
		if (ht->vector[poz]->info->nota == nota) {
			printf("%d. %s - %d \n", poz, ht->vector[poz]->info->nume, ht->vector[poz]->info->nota);
			gasit = true;
		}
	}
	else {
		while (poz < ht->dimHT && ht->vector[poz] != NULL) {
			if (ht->vector[poz]->info->nota == nota) {
				printf("%d. %s - %d \n", poz, ht->vector[poz]->info->nume, ht->vector[poz]->info->nota);
				gasit = true;
			}
			else {
				poz++;
			}
		}
		if (gasit == false) {
			int poz = fhash(nota, ht->dimHT);
			while (poz > 0 && ht->vector[poz] != NULL) {
				if (ht->vector[poz]->info->nota == nota) {
					printf("%d. %s - %d \n", poz, ht->vector[poz]->info->nume, ht->vector[poz]->info->nota);
					gasit = true;
				}
				else {
					poz--;
				}
			}
		}
	}
	if (gasit == false) {
		printf("Nu exista");
	}
}

void stergereNod(HashTable*& ht, int nota) {
	int poz = fhash(nota, ht->dimHT);
	bool gasit = false;

	if (ht->vector[poz] != NULL) {
		if (ht->vector[poz]->info->nota == nota) {
			free(ht->vector[poz]);
			ht->vector[poz] = NULL;
			gasit = true;
		}
	}
	else {
		while (poz < ht->dimHT && ht->vector[poz] != NULL) {
			if (ht->vector[poz]->info->nota == nota) {
				free(ht->vector[poz]);
				ht->vector[poz] = NULL;
				gasit = true;
			}
			else {
				poz++;
			}
		}
		if (poz == ht->dimHT) {
			int poz = fhash(nota, ht->dimHT);

			while (poz > 0 && ht->vector[poz] != NULL) {
				if (ht->vector[poz]->info->nota == nota) {
					free(ht->vector[poz]);
					ht->vector[poz] = NULL;
					gasit = true;
				}
				else {
					poz--;
				}
			}
		}
	}
	if (gasit == false) {
		printf("nu s-a gasit.");
	}
}

void main() {
	HashTable* ht = initHT(20);
	citireFisier(ht);
	parcurgere(ht);

	cautare(ht, 11);

	stergereNod(ht,5);
	parcurgere(ht);
}
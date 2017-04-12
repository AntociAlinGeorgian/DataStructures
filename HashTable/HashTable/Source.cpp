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

Nod* cautareHT(HashTable* ht, int nota) {
	Nod* nodGasit = nullptr;
	int poz = fhash(nota, ht->dimHT);

	if (ht->vector[poz] != NULL) {
		if (ht->vector[poz]->info->nota == nota) {
			nodGasit = ht->vector[poz];
		}
	}
	else {
		while (poz < ht->dimHT && ht->vector[poz] != NULL) {
			if (ht->vector[poz]->info->nota == nota) {
				nodGasit = ht->vector[poz];
			}
			else {
				poz++;
			}
		}
		if (nodGasit == nullptr) {
			int poz = fhash(nota, ht->dimHT);
			
			while (poz > 0 && ht->vector[poz] != NULL) {
				if (ht->vector[poz]->info->nota == nota) {
					nodGasit = ht->vector[poz];
				}
				else {
					poz--;
				}
			}
		}
	}
	if (nodGasit != nullptr) {
		printf("Rezultat: %d: %s - %d", poz, nodGasit->info->nume, nodGasit->info->nota);
		return nodGasit;
	}
	else {
		return nullptr;
	}
}

void afisareHT(HashTable* ht) {
	for (int i = 0; i < ht->dimHT; i++) {
		if (ht->vector[i] != NULL) {
			printf("%d. %s - %d\n", i, ht->vector[i]->info->nume, ht->vector[i]->info->nota);
		}
	}
}

void citireFisier(HashTable*& ht) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Student* stud = new Student;
			char aux[100];
			fscanf(f, "%s", &aux);
			stud->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(stud->nume, aux);
			fscanf(f, "%d", &stud->nota);

			Nod* nod = creareNod(stud);
			inserareHT(ht, nod);
		}
	}
}

void stergereHT(HashTable*& ht, int nota) {
	bool gasit = false;
	int poz = fhash(nota, ht->dimHT);

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
		if (gasit == false) {
			int poz = fhash(nota, ht->dimHT);
			while (poz > ht->dimHT && ht->vector[poz] != NULL) {
				if (ht->vector[poz]->info->nota == nota) {
					free(ht->vector[poz]);
					ht->vector[poz] == NULL;
					gasit = true;
				}
				else {
					poz--;
				}
			}
		}
	}
	if (gasit == false) {
		printf("nu exista aceasta nota.\n");
	}
	else {
		printf("Notele %d au fost sterse.\n",nota);
	}

}

void main() {
	HashTable* ht = initHT(27);
	citireFisier(ht);
	afisareHT(ht);

	//cautareHT(ht, 5);

	stergereHT(ht, 5);

	afisareHT(ht);
}
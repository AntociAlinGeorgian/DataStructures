#include<stdio.h>
#include<iostream>

enum Post {
	MTV, UTV, KissFM
};

struct Prezentator {
	int id;
	char* nume;
	Post postTV;
	int nrCalificative;
	int* calificative;
};

struct Nod {
	Prezentator* info;
	Nod* next;
};

struct HT {
	int dimHT;
	Nod** vector;
};

int fhash(int dimHT, char* nume) {
	return(nume[0]%dimHT);
}

Nod* creareNod(Prezentator* p) {
	Nod* nod = new Nod;
	nod->info = p;
	nod->next = NULL;
	return nod;
}

HT* initHT(int dim) {
	HT* ht = new HT;
	ht->dimHT = dim;
	ht->vector = (Nod**)malloc(sizeof(Nod*)*dim);

	for (int i = 0; i < ht->dimHT; i++) {
		ht->vector[i] = NULL;
	}

	return ht;
}

void inserareNod(HT*& ht, Nod* nod) {
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
				printf("coliziune\n");
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

void citireFisier(HT*& ht) {
	FILE* f = fopen("Text.txt", "r");

	if (f) {
		while (!feof(f)) {
			Prezentator* p = new Prezentator;
			fscanf(f, "%d", &p->id);

			char aux[20];
			fscanf(f, "%s", &aux);
			p->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(p->nume, aux);

			int aux1;
			fscanf(f, "%d", &aux1);
			if (aux1 == 1) {
				p->postTV = MTV;
			}
			else if (aux1 == 2) {
				p->postTV = UTV;
			}
			else if (aux1 == 3) {
				p->postTV = KissFM;
			}

			fscanf(f, "%d", &p->nrCalificative);

			p->calificative = (int*)malloc(sizeof(int)*p->nrCalificative);

			for (int i = 0; i < p->nrCalificative; i++) {
				fscanf(f, "%d", &p->calificative[i]);
			}
			

			Nod* n = creareNod(p);
			inserareNod(ht, n);
		}
	}
}

void parcurgereHT(HT* ht) {
	for (int i = 0; i < ht->dimHT; i++) {
		if (ht->vector[i] != NULL) {
			printf("%d. %s ,", ht->vector[i]->info->id, ht->vector[i]->info->nume);
			if (ht->vector[i]->info->postTV == KissFM) {
				printf("KissFM");
			}
			if (ht->vector[i]->info->postTV == UTV) {
				printf("UTV");
			}
			if (ht->vector[i]->info->postTV == MTV) {
				printf("MTV");
			}

			printf(", calificative[ ");
			for (int j = 0; j < ht->vector[i]->info->nrCalificative; j++) {
				printf("%d ", ht->vector[i]->info->calificative[j]);
			}
			printf("] \n");
		}
	}
}

void main() {
	HT* ht = initHT(21);
	citireFisier(ht);
	parcurgereHT(ht);
}
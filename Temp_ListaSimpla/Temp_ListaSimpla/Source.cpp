#include<iostream>
#include<stdio.h>

struct Elev {
	int id;
	char* nume;
};

struct Nod {
	Elev* info;
	Nod* next;
};

Nod* creareNod(Elev* e) {
	Nod* n = new Nod;
	n->info = e;
	n->next = NULL;
	return n;
}

void inserareInceput(Nod*& lst, Nod* nod) {
	if (lst == NULL) {
		lst = nod;
	}
	else {
		nod->next = lst;
		lst = nod;
	}
}

void inserareFinal(Nod*& lst, Nod* nod) {
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

void citireFisier(Nod*& lst) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Elev* e = new Elev;

			fscanf(f, "%d", &e->id);
			char aux[19];
			fscanf(f, "%s", &aux);
			e->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(e->nume, aux);

			Nod* n = creareNod(e);
			//inserareInceput(lst, n);
			inserareFinal(lst, n);
		}
	}
}

void inserareDupaID(Nod*& lst, Nod* n, int id) {
	if (lst == NULL) {
		lst = n;
	}
	else {
		Nod* tmp = lst;
		while (tmp->next != NULL && tmp->info->id!=id) {
			tmp = tmp->next;
		}
		n->next = tmp->next;
		tmp->next = n;
	}
}

void afisareLista(Nod* lst) {
	if (lst) {
		while (lst->next != NULL) {
			printf("id: %d, nume: %s\n", lst->info->id, lst->info->nume);
			lst = lst->next;
		}
		printf("id: %d, nume: %s\n", lst->info->id, lst->info->nume);
	}
}


void stergereNod(Nod*& lst, int id) {
	if (lst) {
		if (lst->info->id == id) {
			Nod* deSters = lst;
			lst = deSters->next;
			free(deSters->info->nume);
			free(deSters);
		}
		else {
			Nod* tmp = lst;
			while (tmp->next != NULL && tmp->next->info->id != id) {
				tmp = tmp->next;
			}
			if (tmp->next != NULL) {
				Nod* deSters = tmp->next;
				tmp->next = deSters->next;
				free(deSters->info->nume);
				free(deSters);
			}
		}
	}
}

void main() {
	Nod* lst = nullptr;
	citireFisier(lst);

	/*Elev* e1 = new Elev;
	scanf("%d", &e1->id);
	char aux1[10];
	scanf("%s", &aux1);
	e1->nume = (char*)malloc(strlen(aux1) + 1);
	strcpy(e1->nume, aux1);

	Nod* n = creareNod(e1);
	inserareDupaID(lst, n, 2);*/

	stergereNod(lst, 3);
	afisareLista(lst);


}
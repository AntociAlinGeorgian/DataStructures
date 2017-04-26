#include<iostream>
#include<stdio.h>

struct Elev {
	int id;
	char* nume;
};

struct Nod {
	Elev* info;
	Nod* next;
	Nod* prev;
};

Nod* creareNod(Elev* e) {
	Nod* nod = new Nod;
	nod->info = e;
	nod->next = NULL;
	nod->prev = NULL;
	return nod;
}

void inserareNod(Nod*& lst, Nod* nod) {
	if (lst == NULL) {
		lst = nod;
	}
	else {
		nod->next = lst;
		lst->prev = nod;
		lst = nod;
	}
}

void inserareSfarsit(Nod*& lst, Nod* nod) {
	if (lst == NULL) {
		lst = nod;
	}
	else {
		Nod* tmp = lst;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = nod;
		nod->prev = tmp;
	}
}

void citireFisier(Nod*& lst) {
	FILE* f = fopen("Text.txt","r");
	if (f) {
		while (!feof(f)) {
			Elev* e = new Elev;

			fscanf(f, "%d", &e->id);

			char aux[10];
			fscanf(f, "%s", &aux);
			e->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(e->nume, aux);

			Nod* n = creareNod(e);
			//inserareNod(lst, n);
			inserareSfarsit(lst, n);
		}
	}
}

void parcurgereLista(Nod* lst) {
	if (lst) {
		while (lst->next != NULL) {
			printf("%d -  %s\n", lst->info->id, lst->info->nume);
			lst = lst->next;
		}
		printf("%d -  %s\n", lst->info->id, lst->info->nume);
	}
}

void inserareInterior(Nod*& lst, Nod* nod, int id) {
	if (lst == NULL) {
		lst = nod;
	}
	else {
		Nod* tmp = lst;
		while (tmp->next != NULL&& tmp->info->id != id) {
			tmp = tmp->next;
		}
		if (tmp->next == NULL) {
			nod->next = tmp->next;
			nod->prev = tmp;
			tmp->next = nod;
		}
		else {
			nod->next = tmp->next;
			nod->prev = tmp;
			tmp->next->prev = nod;
			tmp->next = nod;
		}
	}
}

void stergereNod(Nod*& lst, int id) {
	if (lst) {
		if (lst->info->id == id) {
			Nod* deSters = lst;
			lst = deSters->next;
			free(deSters);
		}
		else {
			Nod* tmp = lst;
			while (tmp->next != NULL && tmp->next->info->id != id) {
				tmp = tmp->next;
			}
			if (tmp->next!=NULL) {
				Nod* deSters = tmp->next;
				tmp->next = deSters->next;
				if (deSters->next != NULL) {
					deSters->next->prev = tmp;
				}
				
				free(deSters);
			}
		}
	}
}

void main() {
	Nod* lst = nullptr;
	citireFisier(lst);

	/*Elev* e = new Elev;

	scanf("%d", &e->id);

	char aux[10];
	scanf("%s", &aux);
	e->nume = (char*)malloc(strlen(aux) + 1);
	strcpy(e->nume, aux);

	Nod* n = creareNod(e);
	inserareInterior(lst, n, 4);*/

	stergereNod(lst, 1);
	parcurgereLista(lst);
}
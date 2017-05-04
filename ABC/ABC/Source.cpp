#include<iostream>
#include<stdio.h>


struct Medic {
	int id;
	char* nume;
};

struct ABC {
	Medic* info;
	ABC* right;
	ABC* left;
};

ABC* creareNod(Medic* m) {
	ABC* nod = new ABC;
	nod->info = m;
	nod->left = NULL;
	nod->right = NULL;
	return nod;
}

void inserare(ABC*& arbore, ABC* nod) {
	if (arbore == NULL) {
		arbore = nod;
	}
	else {
		if (strcmp(arbore->info->nume, nod->info->nume) > 0) {
			inserare(arbore->left,nod);
		}
		else if (strcmp(arbore->info->nume, nod->info->nume) < 0) {
			inserare(arbore->right, nod);
		}
		else {
			inserare(arbore->right, nod);
		}
	}
}

void parcurgereInOrdine(ABC* arbore) {
	if (arbore) {
		parcurgereInOrdine(arbore->left);
		printf("%s - %d\n", arbore->info->nume, arbore->info->id);
		parcurgereInOrdine(arbore->right);
	}
}

void parcurgerePreOrdine(ABC* arbore) {
	if (arbore) {
		printf("%s - %d\n", arbore->info->nume, arbore->info->id);
		parcurgerePreOrdine(arbore->left);
		parcurgerePreOrdine(arbore->right);
	}
}

void parcurgerePostOrdine(ABC* arbore) {
	if (arbore) {
		parcurgerePostOrdine(arbore->left);
		parcurgerePostOrdine(arbore->right);
		printf("%s - %d\n", arbore->info->nume, arbore->info->id);
	}
}

void citireFisier(ABC*& arbore) {
	FILE* f = fopen("Text.txt", "r");
	if (f) {
		while (!feof(f)) {
			Medic* m = new Medic;
			fscanf(f, "%d", &m->id);
			char aux[10];
			fscanf(f, "%s", &aux);
			m->nume = (char*)malloc(strlen(aux) + 1);
			strcpy(m->nume, aux);

			ABC* nod = creareNod(m);
			inserare(arbore, nod);
		}
	}
}

//stergere logica - stergere pentru 2 descendenti
void stergeLogica(ABC*& radacina, ABC*& sleft) {
	//caut cel mai mare nod din subarborele stang
	if (sleft->right) {
		stergeLogica(radacina, sleft->right);
	}
	else {
		Medic* tmp = radacina->info;
		radacina->info = sleft->info;
		ABC* nodTmp = sleft;
		sleft = sleft->left;
		free(tmp->nume);
		free(tmp);
		free(sleft);
		free(nodTmp);
	}
}


//stergere nod arbore 
void stergereNod(ABC*& arbore, char* cheie) {
	if (arbore) {
		if (strcmp(arbore->info->nume, cheie) > 0) {
			stergereNod(arbore->left, cheie);
		}
		else if(strcmp(arbore->info->nume, cheie)<0) {
			stergereNod(arbore->right, cheie);
		}
		else {
			//1. Este nod frunza (nu are niciun descendent)
			if (arbore->right == NULL && arbore->left == NULL) {
				//dezaloc memoria de jos in sus si apoi anunt ca nodul a devenit null
				free(arbore->info->nume);
				free(arbore->info);
				free(arbore);
				arbore = NULL;
			}
			else {
				//2. sterg nod cu un descendent
				if (arbore->left != NULL && arbore->right == NULL) {
					//salvez nodul ce trebuie sters intr-un tmp
					ABC* sters = arbore;
					//construiesc legatura pe stanga sa nu pierd copilul nodului pe care vreau sa il sterg
					arbore = arbore->left;
					free(sters->info->nume);
					free(sters->info);
					free(sters);
				}
				else if (arbore->left == NULL && arbore->right != NULL) {
					ABC* sters = arbore;
					arbore = arbore->right;
					free(sters->info->nume);
					free(sters->info);
					free(sters);
				}
				else {
					stergeLogica(arbore, arbore->left);
				}
			}
		}
	}
}

void main() {
	ABC* arbore = nullptr;
	citireFisier(arbore);
	//parcurgereInOrdine(arbore);
	//parcurgerePostOrdine(arbore);
	parcurgerePreOrdine(arbore);
}
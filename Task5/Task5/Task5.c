#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Nod Nod;//de ce
typedef struct Santier Santier;

struct Santier
{
	char* numeProiect;
	int nrMuncitori;
	float suprafata;
};

struct Nod
{
	Santier santier;
	Nod* next;//adresa urmatorului nod
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata)
{
	Santier santier;
	santier.numeProiect = (char*)malloc(strlen(numeProiect)+1);
	strcpy(santier.numeProiect, numeProiect);
	santier.nrMuncitori = nrMuncitori;
	santier.suprafata = suprafata;
	return santier;
}

Nod* inserareInceput(Nod* lista, Santier santier)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->santier = santier;
	nod->next = lista;
	return nod;
}

void afisareSantier(Santier santier)
{
	printf("Santierul este intitulat %s, are %d muncitori si o suprafata %5.2f \n",santier.numeProiect,santier.nrMuncitori,santier.suprafata);
}

void afisareLista(Nod* lista)
{
	while (lista != NULL)
	{
		afisareSantier(lista->santier);
		lista = lista->next;//trecem la urmatorul din lista
	}
}

int nrNoduri(Nod* lista)
{
	Nod* copieLista;
	int ap = 0;
	copieLista = lista;
	while (copieLista != NULL)
	{
		ap++;
		copieLista = copieLista->next;
	}
	return ap;
}

void stergereNod(Nod** lista, int x)
{
	if (nrNoduri(*lista) >= x)
	{
		int nrNod = 0;
		Nod* nodCurent;
		Nod* nodPrecedent;
		nodCurent = (*lista);
		nodPrecedent = NULL;
		int ok = 0;//Nu am sters inca nodul
		while (nodCurent != NULL && ok == 0)
		{
			if (nrNod == x)
			{
				ok = 1;
				if (nodPrecedent != NULL)
				{
					nodPrecedent->next = nodCurent->next;
				}
				else
				{
					(*lista) = nodCurent->next;
				}
				free(nodCurent->santier.numeProiect);
				free(nodCurent);
			}
			nrNod++;
			nodPrecedent = nodCurent;
			nodCurent = nodCurent->next;
		}
	}
}

void inserareSortat(Nod** lista, Nod* nod)
{
	Nod* copieLista;
	copieLista = (*lista);
	for (Nod* i = copieLista; i != NULL; i = i->next)
	{
		for (Nod* j = i->next; j != NULL; j = j->next)
		{
			if (i->santier.nrMuncitori > j->santier.nrMuncitori)
			{
				Santier aux;
				aux = i->santier;
				i->santier = j->santier;
				j->santier = aux;
			}
		}
	}
	
	copieLista = (*lista);
	Nod* prev = copieLista;

	if (copieLista == NULL)
	{
		copieLista = nod;
		copieLista->next = NULL;
	}
	else
	{
		while (copieLista->next != NULL && copieLista->next->santier.nrMuncitori < nod->santier.nrMuncitori)
		{
			copieLista = copieLista->next;
		}
		nod->next = copieLista->next;
		copieLista->next = nod;
	}
	(*lista) = prev;
}

void salvareInVector(Nod* lista, Santier** vector, int* nrSantiereFavorabile)
{
	(*nrSantiereFavorabile) = 0;
	for (Nod* i = lista; i != NULL; i = i->next)
	{
		if (i->santier.suprafata >= 200)
			(*nrSantiereFavorabile)++;
	}

	(*vector) = (Santier*)malloc(sizeof(Santier) * (*nrSantiereFavorabile));
	int j = 0;
	for (Nod* i = lista; i != NULL; i = i->next)
	{
		if (i->santier.suprafata >= 200)
		{
			(*vector)[j].numeProiect = (char*)malloc(strlen(i->santier.numeProiect)+1);
			strcpy((*vector)[j].numeProiect, i->santier.numeProiect);
			(*vector)[j].nrMuncitori = i->santier.nrMuncitori;
			(*vector)[j].suprafata = i->santier.suprafata;
			j++;
		}
	}
}

void interschimbarePozitii(Nod** lista, int poz1, int poz2)
{
	if (poz1 != poz2)
	{
		int nrElemLista = 0;
		for (Nod* i = (*lista); i != NULL; i = i->next)
		{
			nrElemLista++;
		}
		
		if (poz1 <= nrElemLista && poz2 <= nrElemLista && poz1 >= 0 && poz2 >= 0)
		{
			Nod* copie1;
			Nod* copie2;
			int nr1 = 0;
			int nr2 = 0;
			copie1 = (*lista);	
			copie2 = (*lista);
			while (nr1 != poz1)
			{
				copie1 = copie1->next;
				nr1++;
			}

			while (nr2 != poz2)
			{
				copie2 = copie2->next;
				nr2++;
			}

			Santier aux;
			aux = copie1->santier;
			copie1->santier = copie2->santier;
			copie2->santier = aux;
		}
	}
}

int  main() 
{
	Nod* lista=NULL;
	Santier s1 = initializareSantier("Santier 1", 5, 200);
	Santier s2 = initializareSantier("Santier 2", 10, 500);
	Santier s3 = initializareSantier("Santier 3", 3, 100);

	lista = inserareInceput(lista, s1);
	lista = inserareInceput(lista, s2);
	lista = inserareInceput(lista, s3);

	//STERGERE NOD
	/*stergereNod(&lista, 2);
	printf("\n");
	afisareLista(lista);*/

	//INSERARE NOD SORTAT
	Santier s4 = initializareSantier("Santier 4", 7, 100);
	Nod* nodInserat;
	nodInserat = (Nod*)malloc(sizeof(Nod));
	nodInserat->santier = s4;
	nodInserat->next = NULL;
	inserareSortat(&lista, nodInserat);
	afisareLista(lista);


	//SALVARE INTR-UN VECTOR
	//NUMAI SANTIERELE CARE AU suprafata >=200
	Santier* vector;
	int nrSantiereFavorabile;
	salvareInVector(lista, &vector, &nrSantiereFavorabile);
	printf("\n");
	for (int i = 0; i < nrSantiereFavorabile; i++)
	{
		printf("\nNumarul santierului este: %d\n", i);
		afisareSantier(vector[i]);
	}

	//Interschimbare pozitii
	int poz1, poz2;
	poz1 = 1;
	poz2 = 2;
	interschimbarePozitii(&lista, poz1, poz2);
	printf("\nAfisare lista cu pozitiile intreschimbate\n");
	afisareLista(lista);
}
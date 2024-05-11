#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Santier Santier;
struct Santier {
	char* numeProiect;
	int nrMuncitori;
	float suprafata;
};

typedef struct NodLdi NodLdi;
struct NodLdi {
	NodLdi* prev;
	NodLdi* next;
	Santier info;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	NodLdi* prim;
	NodLdi* ultim;
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata)
{
	Santier s;
	s.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
	strcpy(s.numeProiect, numeProiect);
	s.nrMuncitori = nrMuncitori;
	s.suprafata = suprafata;
	return s;
}


void inserareInceput(ListaDubla* lista, Santier santier)
{
	NodLdi* aux = malloc(sizeof(NodLdi));
	aux->info = santier;
	aux->next = lista->prim;
	aux->prev = NULL;
	if (lista->prim != NULL)
	{
		lista->prim->prev = aux;
	}
	else
	{
		//Daca nu ai noduri in lista
		lista->ultim = aux;
	}
	lista->prim = aux;
}

void inserareDupaInceput(ListaDubla* lista, Santier santier)
{
	
}

void afisareSantier(Santier santier)
{
	printf("\nProiectul este %s avand %d muncitori si suprafata %5.2f m^2",santier.numeProiect,santier.nrMuncitori,santier.suprafata);
}

void afisareLista(ListaDubla lista)
{
	if (lista.ultim == NULL)
	{
		printf("\nNu exista elemente in lista");
		return;
	}	
	else
	{
		for (NodLdi* i = lista.prim; i!= NULL; i = i->next)
		{
			afisareSantier(i->info);
		}
	}
}

void stergereDupaIndex(ListaDubla* lista, int index)
{
	ListaDubla aux = (*lista);
	int nr = 0;
	for (NodLdi* i = aux.prim; i != NULL; i = i->next)
	{
		nr++;
	}
	if (index > nr)
	{
		printf("\nIndexul este mai mare decat elementele din lista");
		return;
	}
	else
	{
		nr = 0;
		NodLdi* nod = lista->prim;
		while (nod != NULL)
		{
			if (nr == index)
			{
				if (nod->prev == NULL && nr == index)//e primul nod
				{
					if (nod->next == NULL)
					{
						lista->prim = NULL;
						lista->ultim = NULL;
					}
					else
					{
						nod->next->prev = NULL;
						lista->prim = nod->next;
					}
				}
				else
					if (nod->next == NULL && nr == index)//e ultimul nod
					{
						nod->prev->next = NULL;
						lista->ultim = nod;
					}
					else
					{
						nod->prev->next = nod->next;
						nod->next->prev = nod->prev;
					}
				free(nod->info.numeProiect);
				free(nod);
				nod = NULL;
				return;
			}
			nr++;
			if (nod->next != NULL)
				nod = nod->next;
			else
				nod = NULL;
		}
	}
}

int main()
{
	Santier s1 = initializareSantier("Santier 1", 10, 300);
	Santier s2 = initializareSantier("Santier 2", 12, 400);
	Santier s3 = initializareSantier("Santier 3", 15, 200);

	/*afisareSantier(s1);
	afisareSantier(s2);
	afisareSantier(s3);*/

	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	printf("Afisare lista initiala:");
	inserareInceput(&lista, s1);
	inserareInceput(&lista, s2);
	inserareInceput(&lista, s3);
	afisareLista(lista);

	/*int index = 5;
	printf("\n\nStergere index 1");
	stergereDupaIndex(&lista, index);
	afisareLista(lista);

	printf("\n\nStergere index 1, a doua oara");
	stergereDupaIndex(&lista, index);
	afisareLista(lista);

	index = 0;
	printf("\n\nStergere index 0");
	stergereDupaIndex(&lista, index);
	afisareLista(lista);*/

	Santier s4 = initializareSantier("Santier 4", 11, 350);
	inserareDupaMuncitori(lista, s4);
}
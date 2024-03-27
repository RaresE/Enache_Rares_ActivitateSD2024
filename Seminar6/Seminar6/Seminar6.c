//lista dublu inlantuita este o structura de date omogena cu 3 elemente
//pointer cu adresa nodului precedent, informatia utila, pointer care retine adresa urmatorului nod
//Ultimul nod are null la adresa urmatorului nod si primul tot null
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Santier Santier;
typedef struct NodLdi NodLdi;
typedef struct ListaDubla ListaDubla;

struct Santier {
	char* numeProiect;
	int nrMuncitori;
	float suprafata;
};

struct NodLdi {
	NodLdi* prev;
	NodLdi* next;
	Santier info;
};

struct ListaDubla {
	NodLdi* prim;
	NodLdi* ultim;
};

void inserareInceput(ListaDubla* lista, Santier s)
{
	NodLdi* aux = malloc(sizeof(NodLdi));
	aux->info = s;
	aux->next = lista->prim;
	aux->prev = NULL;
	if (lista->prim != NULL)
	{
		lista->prim->prev = aux; 
	}
	else
	{
		lista->ultim = aux;
	}
	lista->prim = aux;
}

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
	Santier santier;
	santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
	strcpy(santier.numeProiect, numeProiect);
	santier.nrMuncitori = nrMuncitori;
	santier.suprafata = suprafata;
	return santier;
}

void afisareSantier(Santier santier)
{
	printf("Santierul %s are %d muncitori si %5.2f m^2 suprafata\n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}

void afisareLdi(ListaDubla lista)
{
	//afisare de la primul la ultimul 
	for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next)
	{
		afisareSantier(nod->info);
	}
	printf("\n");
}

//numele santierului cu densitatea cea mai mare de muncitori pe m^2

float densitateMuncitori(Santier santier) {
	if (santier.suprafata > 0)
		return santier.nrMuncitori / santier.suprafata;
	else
		return 0;
}

int calcNrTotalMuncitori(ListaDubla lista)
{
	int suma = 0;
	for (NodLdi* i = lista.prim; i != NULL; i = i->next)
	{
		suma += i->info.nrMuncitori;
	}
	return suma;
}

int calcNrTotalMuncitoriSuprafata(ListaDubla lista, float suprafataMax)
{
	int suma = 0;
	for (NodLdi* i = lista.prim; i != NULL; i = i->next)
	{
		if(i->info.suprafata<suprafataMax)
			suma += i->info.nrMuncitori;
	}
	return suma;
}

// stergere santier cu un nume dat
void stergereSantierDupaNume(ListaDubla* lista, const char* numeSantier)
{
	NodLdi* nod = lista->prim;
	while (nod != NULL)
	{
		if (strcmp(nod->info.numeProiect, numeSantier) == 0)
		{
			if (nod->prev == NULL)//e primul nod
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
			{
				if (nod->next == NULL)
				{
					nod->prev->next = NULL;
					lista->ultim = nod->prev;
				}
				else
				{
					nod->prev->next = nod->next;
					nod->next->prev = nod->prev;
				}
			}

			free(nod->info.numeProiect);
			free(nod);
			nod = NULL;
		}
		else
			nod = nod->next;
	}
}

void stergereCompleta(ListaDubla* lista)
{
	if (lista != NULL)
	{
		NodLdi* aux = lista->prim;
		while (aux != NULL)
		{
			free(aux->info.numeProiect);
			NodLdi* temp = aux->next;
			free(aux);
			aux = temp;
		}
		lista->prim = NULL;
		lista->ultim = NULL;
	}
}

int main() {
	Santier s1 = initializareSantier("Santier 1", 10, 300);
	Santier s2 = initializareSantier("Santier 2", 12, 400);
	Santier s3 = initializareSantier("Santier 3", 15, 200);

	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	//in inserare punem -> fiind transmisa prin adresa
	inserareInceput(&lista, s1);
	inserareInceput(&lista, s2);
	inserareInceput(&lista, s3);
	
	afisareLdi(lista);

	/*stergereSantierDupaNume(&lista, "Santier 2");
	afisareLdi(lista);

	stergereSantierDupaNume(&lista, "Santier 1");
	afisareLdi(lista);

	stergereSantierDupaNume(&lista, "Santier 3");
	afisareLdi(lista);*/

	printf("Numarul total de muncitori este: %d", calcNrTotalMuncitori(lista));
	printf("\nNumarul total de muncitori conditionat de suprafata este: %d", calcNrTotalMuncitoriSuprafata(lista, 350));

	stergereCompleta(&lista);
	afisareLdi(lista);

	//inserare inceput
	//inserare sfarsit
}
#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>

typedef struct Rezervare Rezervare;
struct Rezervare
{
	int id;
	char* numeClient;
	int nrPersoane;
};

typedef struct Nod Nod;
struct Nod 
{
	Rezervare info;
	Nod* stanga;
	Nod* dreapta;
};

Rezervare citireRezervare(FILE* f)
{
	Rezervare r;
	char aux[30];
	fscanf(f, "%d",&r.id);
	fscanf(f, "%s", &aux);
	r.numeClient = malloc(strlen(aux) + 1);
	strcpy(r.numeClient, aux);
	fscanf(f, "%d", &r.nrPersoane);
	return r;
}

Nod* inserareInArbore(Nod* arbore, Rezervare rez)
{
	if (arbore != NULL)
	{
		if (arbore->info.id < rez.id)
		{
			arbore->dreapta = inserareInArbore(arbore->dreapta, rez);
		}
		else
		{
			arbore->stanga = inserareInArbore(arbore->stanga, rez);
		}
	}
	else
	{
		Nod* temp = (Nod*)malloc(sizeof(Nod));
		temp->info = rez;
		temp->dreapta = NULL;
		temp->stanga = NULL;
		arbore = temp;
	}
	return arbore;
}

void citireFisier(const char* numeFisier, Nod** radacina)
{
	int nrRezervari;
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", &nrRezervari);
	for (int i = 0; i < nrRezervari; i++)
	{
		Rezervare rez;
		rez = citireRezervare(f);
		*radacina = inserareInArbore(*radacina, rez);
	}
}

//RSD-preordine
//SDR-postordine
//SRD-inordine

void afisareRezervare(Rezervare r)
{
	printf("\nRezervarea cu ID-ul %d a fost facuta de %s pentru %d persoane", r.id, r.numeClient, r.nrPersoane);
}

void afisareArborePreordine(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareRezervare(arbore->info);
		afisareArborePreordine(arbore->stanga);
		afisareArborePreordine(arbore->dreapta);
	}
}

void afisareArboreInOrdine(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareArboreInOrdine(arbore->stanga);
		afisareRezervare(arbore->info);
		afisareArboreInOrdine(arbore->dreapta);
	}
}

void afisareArborePostOrdine(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareArborePostOrdine(arbore->stanga);
		afisareArborePostOrdine(arbore->dreapta);
		afisareRezervare(arbore->info);
	}
}

Rezervare cautareRezervareDupaId(Nod* rad, int id)
{
	if (rad)
	{
		if (rad->info.id < id)
		{
			return cautareRezervareDupaId(rad->dreapta, id);
		}
		else
		{
			if (rad->info.id > id)
			{
				return cautareRezervareDupaId(rad->stanga, id);
			}
			else
			{
				return rad->info;
			}
		}
	}
	else
	{
		Rezervare r;
		r.id = -1;
		r.numeClient = NULL;
		r.nrPersoane = -1;
		return r;
	}
}

int calculNrTotalPersoane(Nod* rad)
{
	if (rad)
	{
		int rPersoane = rad->info.nrPersoane;
		int sPersoane = calculNrTotalPersoane(rad->stanga);
		int dPersoane = calculNrTotalPersoane(rad->dreapta);
		int suma = rPersoane + sPersoane + dPersoane;
		return suma;
	}
	else
	{
		return 0;
	}
}

void main()
{
	Nod* radacina = NULL;
	citireFisier("Source.txt", &radacina);
	//afisareArborePreordine(radacina);
	//afisareArboreInOrdine(radacina);
	afisareArborePostOrdine(radacina);

	printf("\nCautare\n");
	afisareRezervare(cautareRezervareDupaId(radacina, 8));
	printf("\nNumar total persoane %d", calculNrTotalPersoane(radacina));
	return 0;
}
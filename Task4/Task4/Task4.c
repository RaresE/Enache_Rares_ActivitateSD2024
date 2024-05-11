#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Masina Masina;
struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

Masina* adaugareInVector(Masina* masini, Masina masina, int* nrMasini)
{
	Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < (*nrMasini); i++)
	{
		aux[i] = masini[i];
	}
	aux[(*nrMasini)] = masina;
	(*nrMasini)++;
	if (masini != NULL)
		free(masini);
	return aux;
}

Masina* citireFisier(const char* numeFisier,int* nrMasini)
{
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";
	
	Masina* masini = NULL;
	(*nrMasini) = 0;
	while (fgets(buffer, 100, file) != NULL)
	{
		char* element = strtok(buffer, delimitare);
		struct Masina m;
		m.id = atoi(element);
		element = strtok(NULL, delimitare);
		m.producator = (char*)malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);
		masini = adaugareInVector(masini, m, nrMasini);
		//printf("\nId-ul masinii este %d, producatorul este %s, masina avand %d usi, pretul %5.2f",m.id,m.producator,m.nrUsi,m.pret);
	}
	fclose(file);
	return masini;
}

void citireMatrice(const char* numeFisier, Masina*** masini,int* nrColoane,int nrLinii)
{
	FILE* file = fopen(numeFisier, "r");
	if (file == NULL)
	{
		printf("Eroare la deschiderea fisierului!");
		return;
	}

	char buffer[100];
	char delimitare[] = ",\n";
	(*masini) = (Masina**)malloc(sizeof(Masina*) * nrLinii);
	if (*masini == NULL)
	{
		printf("Eroare la alocarea memoriei!");
		fclose(file);
		return;
	}
	for (int i = 0; i < nrLinii; i++)
	{
		(*masini)[i] = NULL;
	}
	int nr = 0;
	while (fgets(buffer,100,file)!=NULL) {
		Masina m;
		char* element = strtok(buffer, delimitare);
		m.id = atoi(buffer);
		element = strtok(NULL, delimitare);
		m.producator = (char*)malloc(strlen(element) + 1);
		strcpy(m.producator, element);	
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);
		
		//(*masini)[m.nrUsi-2] = adaugareInVector((*masini)[m.nrUsi], m, &(nrColoane[m.nrUsi - 2]));

		int index = m.nrUsi - 2;
		(*masini)[index] = (Masina*)malloc(sizeof(Masina));
		(*masini)[index][index] = m;
		nrColoane[index]++;
	}
	return masini;
}

void afisareMatrice(Masina** matrice,int nrLinii, int* nrCol)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrCol[i]; j++)
		{
			printf("Masina nr. %d \n", i);
			printf("ID: %d \n", matrice[i][j].id);
			printf("Producator: %s \n", matrice[i][j].producator);
			printf("Numar usi: %d \n", matrice[i][j].nrUsi);
			printf("Pret: %5.2f \n", matrice[i][j].pret);
		}
		printf("\n");
	}
}

int main()
{
	/*Masina* masini=NULL;
	int nrMasini = 0;
	
	masini = citireFisier("masini.txt", &nrMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		printf("\nId-ul masinii este %d, producatorul este %s, masina avand %d usi, pretul %5.2f", masini[i].id, masini[i].producator, masini[i].nrUsi, masini[i].pret);
	}*/
	Masina** m1 = NULL;
	int nrLinii = 3;
	int* nrColoane;
	nrColoane = (int*)malloc(sizeof(int) * nrLinii);
	for (int i = 0; i < nrLinii; i++)
		nrColoane[i] = 0;
	citireMatrice("masini.txt",&m1,nrColoane,nrLinii);
	afisareMatrice(m1,nrLinii,nrColoane);
}
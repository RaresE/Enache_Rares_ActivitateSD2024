#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = masini[i]; //shallow copy
	}
	aux[*nrMasini] = m;
	(*nrMasini)++; // ++ are prioritate mai mare decat dereferentierea => prioritizam *nrMasini
	if (masini != NULL) {
		free(masini); //stregem doar vectorul, pointerii raman
	}
	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) { //nrMasini este deja un pointer care are adresa => nu trebuie sa ii mai dam adresa
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";

	//am creat un vector de masini
	struct Masina* masini = NULL;
	(*nrMasini) = 0;

	while (fgets(buffer, 100, file) != NULL) { //cand ajunge la finalul fisierului si nu mai are ce citi, returneaza null
		char* element = strtok(buffer, delimitare); // este bine ca separatoarele sa fie stocate intr-o variabila
		struct Masina m; //am construit masina m
		m.id = atoi(element); //cast de la string to int
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		m.nrUsi = atoi(element);
		m.pret = atof(element);
		masini = adaugareInVector(masini, m, nrMasini);
	}
	fclose(file);
	return masini;
}

void citireMatrice(const char* numeFisier, int nrLinii, int* nrColoane, struct Masina** matrice) {  
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";

	while (fgets(buffer, 100, file) != NULL) { 
		char* element = strtok(buffer, delimitare); 
		struct Masina m; 
		m.id = atoi(element); 
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);
		matrice[m.nrUsi-2] = adaugareInVector(matrice[m.nrUsi-2], m,  &(nrColoane[m.nrUsi - 2]));
	}
	fclose(file);
}

void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrCol) {
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

float pretMediu(struct Masina** matrice, int nrLinii, int* nrColoane, int nrUsi) {
	if (nrUsi < 2 && nrUsi>4)
		return 0;
	float pretTotal = 0;
	int index = nrUsi - 2;
	if (nrColoane[index] == 0)
		return 0;
	for (int i = 0; i < nrColoane[index]; i++)
	{
		pretTotal += matrice[index][i].pret;
	}
	return pretTotal / nrColoane[index];
}

struct Masina cautareMasinaID(struct Masina** matrice, int nrLinii, int* nrCol, int id) {
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrCol[i]; j++)
		{
			if (matrice[i][j].id == id)
				return matrice[i][j];
		}
	}

	struct Masina m;
	m.id = -1;
	m.producator = "";
	m.nrUsi = 0;
	m.pret = 0.0;
	return m;
}



void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrCol) 
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrCol[i]; j++)
		{
			free((*matrice)[i][j].producator);	
		}
		free((*matrice)[i]);
	}
	free((*nrCol));
	(*nrCol) = NULL;
	free((*matrice));
	(*matrice) = NULL;
}

int main() {

	struct Masina** matrice;
	int nrLinii = 3;
	int* nrCol;
	nrCol = (int*)malloc(sizeof(int) * nrLinii);
	matrice = (struct Masina**)malloc(sizeof(struct Masina*) * nrLinii);
	for (int i = 0; i < nrLinii; i++)
	{
		nrCol[i] = 0;
		matrice[i] = NULL;
	}

	citireMatrice("masini.txt", nrLinii, nrCol, matrice);
	afisareMatrice(matrice, nrLinii,nrCol);
	printf("Pretul mediu este: %5.2f",pretMediu(matrice, nrLinii, nrCol, 2));
	struct Masina masina_cautata;
	masina_cautata=cautareMasinaID(matrice, nrLinii, nrCol, 2);
	printf("ID: %d \n", masina_cautata.id);
	printf("Producator: %s \n", masina_cautata.producator);
	printf("Numar usi: %d \n", masina_cautata.nrUsi);
	printf("Pret: %5.2f \n", masina_cautata.pret);

	dezalocareMatrice(&matrice, nrLinii, &nrCol);

	/*printf("---------------------------------");
	struct Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireFisier("masini.txt", &nrMasini);
	for (int i = 0; i < nrMasini; i++) {
		printf("Masina nr. %d \n", i);
		printf("ID: %d \n", masini[i].id);
		printf("Producator: %s \n", masini[i].producator);
		printf("Numar usi: %d \n", masini[i].nrUsi);
		printf("Pret: %d \n", masini[i].pret);
		printf("\n");
	}*/
}
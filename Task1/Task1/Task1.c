#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>


typedef struct BateriiDispozitive BateriiDispozitive;

struct BateriiDispozitive {
	char* denumire;
	int nrBaterii;
	int* procentajBaterie;
};

void citireBaterie(BateriiDispozitive* b1)
{
	char buffer[100];
	printf("\nIntroduceti denumirea dispozitivului: ");
	scanf("%s",buffer);	
	(*b1).denumire = (char*)malloc(strlen(buffer) + 1);
	strcpy((*b1).denumire, buffer);
	printf("\nIntroduceti numarul de baterii necesare pentru dispozitiv: ");
	scanf("%d", &((*b1).nrBaterii));
	b1->procentajBaterie = (int*)malloc(sizeof(int) * b1->nrBaterii);
	for (int i = 0; i < (*b1).nrBaterii; i++)
	{
		printf("\nIntroduceti procentajul bateriei %d: ", i);
		scanf("%d", &((*b1).procentajBaterie[i]));
	}
}

void afisareBaterie(BateriiDispozitive b)
{
	printf("\nDenumirea dispozitivului este: %s", b.denumire);
	printf("\nNumarul de baterii necesare pentru dispozitiv este: %d", b.nrBaterii);
	printf("\nProcentajul fiecarei baterii este: ");
	for (int i = 0; i < b.nrBaterii; i++)
	{
		printf("\nBateria %d are procentajul %d%%", i, b.procentajBaterie[i]);
	}
} 

void dezalocare(BateriiDispozitive b)
{
	free(b.denumire);
	free(b.procentajBaterie);
}

int sumaProcentaj(BateriiDispozitive b)
{
	int sum;
	sum = 0;
	for (int i = 0; i < b.nrBaterii; i++)
	{
		sum = sum + b.procentajBaterie[i];
	}
	return sum;
}

void modificareDenumire(BateriiDispozitive* b, const char* denumireNoua)
{
	free((*b).denumire);
	(*b).denumire = (char*)malloc(strlen(denumireNoua) + 1);
	strcpy((*b).denumire, denumireNoua);
}

int main()
{
	BateriiDispozitive b1;
	citireBaterie(&b1);
	afisareBaterie(b1);

	int suma;
	suma = sumaProcentaj(b1);
	printf("\n\nProcentajul adunat al bateriilor dispozitivului este: %d%%", suma);

	char denumireNoua[100];
	printf("\n\nIntroduceti noua denumire a dispozitivului: ");
	scanf("%s", &denumireNoua);
	modificareDenumire(&b1,denumireNoua);
	afisareBaterie(b1);
	dezalocare(b1);
}
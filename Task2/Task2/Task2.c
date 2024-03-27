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
	scanf("%s", buffer);
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

BateriiDispozitive initializareBaterie(const char* denumire, int nr, int* procentaj)
{
	BateriiDispozitive b;
	b.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(b.denumire, denumire);
	b.nrBaterii = nr;
	b.procentajBaterie = (int*)malloc(sizeof(int) * b.nrBaterii);
	for (int i = 0; i < b.nrBaterii; i++)
	{
		b.procentajBaterie[i] = procentaj[i];
	}
	return b;
}

void copiereInVector(BateriiDispozitive** vector, int* nrDisp,BateriiDispozitive* disp,int nrDispozitive, int procent)
{
	int nrDispFavorabile=0;
	for (int i = 0; i < nrDispozitive; i++)
	{
		int ok = 0;//Presupunem ca dispozitivul nu are baterii cu procentajul peste 20%
		for (int j = 0; j < disp[i].nrBaterii; j++)
		{
			if (disp[i].procentajBaterie[j] > 20)
				ok = 1;
		}
		if(ok==1)
			nrDispFavorabile++;
	}

	if (nrDispFavorabile > 0)
	{
		(*vector) = (BateriiDispozitive*)malloc(sizeof(BateriiDispozitive) * nrDispFavorabile);
		for (int i = 0; i < nrDispozitive; i++)
		{
			int ok = 0;
			for (int j = 0; j < disp[i].nrBaterii; j++)
			{
				if (disp[i].procentajBaterie[j] > 20)
					ok = 1;
			}
			if (ok == 1)
			{
				(*vector)[(*nrDisp)] = initializareBaterie(disp[i].denumire, disp[i].nrBaterii, disp[i].procentajBaterie);
				(*nrDisp)++;
			}
		}
	}
}

void afisareVector(BateriiDispozitive* vector, int nrDisp)
{
	for (int i = 0; i < nrDisp; i++)
	{
		printf("\n---------------------------------------");
		afisareBaterie(vector[i]);
	}
}

BateriiDispozitive* copiereConditionata(BateriiDispozitive* vector, int nrDisp, int* nrDispConditionate)
{
	int nrDispFavorabile=0;
	for (int i = 0; i < nrDisp; i++)
	{
		if (vector[i].nrBaterii > 2)//Dispozitivele care au mai mult de 2 baterii
			nrDispFavorabile++;
	}

	BateriiDispozitive* vectorCond;
	vectorCond = (BateriiDispozitive*)malloc(sizeof(BateriiDispozitive) * nrDispFavorabile);
	for (int i = 0; i < nrDisp; i++)
	{
		if (vector[i].nrBaterii > 2)
		{
			vectorCond[(*nrDispConditionate)] = initializareBaterie(vector[i].denumire,vector[i].nrBaterii,vector[i].procentajBaterie);
			(*nrDispConditionate)++;
		}
	}
	return vectorCond;
}

void dezalocareVector(BateriiDispozitive** vector, int* nrDisp)
{
	for (int i = 0; i < (*nrDisp); i++)
	{
		free((*vector)[i].denumire);
		free((*vector)[i].procentajBaterie);
	}
	free(*vector);
	(*nrDisp) = 0;
	(*vector) = NULL;
}

BateriiDispozitive* concatVectori(BateriiDispozitive** vectorConcatenat, int* nrConcatenat, BateriiDispozitive* v1, int nr1, BateriiDispozitive* v2, int nr2)
{
	int x;
	x = nr1 + nr2;
	(*nrConcatenat) = 0;
	(*vectorConcatenat) = (BateriiDispozitive*)malloc(sizeof(BateriiDispozitive) * x);
	for (int i = 0; i < nr1; i++)
	{
		(*vectorConcatenat)[(*nrConcatenat)] = initializareBaterie(v1[i].denumire, v1[i].nrBaterii, v1[i].procentajBaterie);
		(*nrConcatenat)++;
	}

	for (int i = 0; i < nr2; i++)
	{
		(*vectorConcatenat)[(*nrConcatenat)] = initializareBaterie(v2[i].denumire, v2[i].nrBaterii, v2[i].procentajBaterie);
		(*nrConcatenat)++;
	}
	return (*vectorConcatenat);
}
	
int main()
{
	BateriiDispozitive b1;
	int procentaj[] = {10, 20};
	b1 = initializareBaterie("Telefon",2,procentaj);
	dezalocare(b1);
	//afisareBaterie(b1);

	/*int suma;
	suma = sumaProcentaj(b1);
	printf("\n\nProcentajul adunat al bateriilor dispozitivului este: %d%%", suma);

	char denumireNoua[100];
	printf("\n\nIntroduceti noua denumire a dispozitivului: ");
	scanf("%s", &denumireNoua);
	modificareDenumire(&b1, denumireNoua);
	afisareBaterie(b1);*/

	int nrDispozitive = 5;
	BateriiDispozitive* disp;
	disp = (BateriiDispozitive*)malloc(sizeof(BateriiDispozitive)* nrDispozitive);
	int procentaj1[] = { 10, 20, 40};
	int procentaj2[] = { 60, 50};
	int procentaj3[] = { 10, 10};
	disp[0] = initializareBaterie("Laptop", 3, procentaj1);
	disp[1] = initializareBaterie("Mouse", 3, procentaj1);
	disp[2] = initializareBaterie("Lanterna", 3, procentaj1);
	disp[3] = initializareBaterie("Telecomanda", 2, procentaj3);
	disp[4] = initializareBaterie("Controller", 2, procentaj2);

	//Copiere in vector cu o anumita conditie
	BateriiDispozitive* vector;
	int nrDisp=0;
	copiereInVector(&vector, &nrDisp, disp, nrDispozitive, 20);//copiaza dispozitivele care au cel putin o baterie peste 20%
	//afisareVector(vector, nrDisp);

	//Copiere in vector cu o alta conditie
	BateriiDispozitive* vectorConditionat;
	int nrDispConditionate=0;
	vectorConditionat = copiereConditionata(vector, nrDisp, &nrDispConditionate);
	//afisareVector(vectorConditionat, nrDispConditionate);

	//Concatenare vectori 7 
	BateriiDispozitive* vectorConcat;
	int nrConcat=0;
	vectorConcat = concatVectori(&vectorConcat, &nrConcat, vector, nrDisp, vectorConditionat, nrDispConditionate);
	afisareVector(vectorConcat, nrConcat);

	dezalocareVector(&vector,&nrDisp);
	dezalocareVector(&vectorConditionat, &nrDispConditionate);
}
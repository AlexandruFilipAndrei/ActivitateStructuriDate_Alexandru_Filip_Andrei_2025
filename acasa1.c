#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraPersoana {
	int id;
	char* nume;
	int varsta;
	float inaltime;

};

typedef struct StructuraPersoana Persoana;

void afisarePersona(Persoana persoana)
{
	printf("ID: %d\n", persoana.id);
	printf("NUME: %s\n", persoana.nume);
	printf("Varsta: %d\n", persoana.varsta);
	printf("Inaltime: %.2f\n\n", persoana.inaltime);
}

void afisareVectorPersoane(Persoana* persoane, int nrPersoane) {
	for (int i = 0; i < nrPersoane; i++)
		afisarePersona(persoane[i]);
}

Persoana citirePersoanaFisier(FILE* file) {
	char text[100];
	char separator[3] = ",\n";
	fgets(text, 100, file);
	char* aux;
	Persoana p1;
	aux = strtok(text, separator);
	p1.id = atoi(aux);
	aux = strtok(NULL, separator);
	p1.nume = malloc(strlen(aux) + 1);
	strcpy_s(p1.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, separator);
	p1.varsta = atoi(aux);
	aux = strtok(NULL, separator);
	p1.inaltime = atof(aux);

	return p1;
}

void adaugaPersoanaVector(Persoana** persoane, int* nrPersoane, Persoana persoanaNoua) {
	Persoana* aux = (Persoana*)malloc(sizeof(Persoana) * ((*nrPersoane)+1));
	for (int i = 0; i < *nrPersoane; i++)
		aux[i] = (*persoane)[i];

	aux[(*nrPersoane)] = persoanaNoua;
	(*nrPersoane)++;
	free(*persoane);
	(*persoane) = aux;
}

Persoana* citireVectorPersoaneFisier(const char* Fisier, int* nrPersoaneCitite)
{
	FILE* file = fopen(Fisier, "r");
	Persoana* persoane = NULL;
	do {
		adaugaPersoanaVector(&persoane, nrPersoaneCitite, citirePersoanaFisier(file));

	} while (!feof(file));
	fclose(file);
	return persoane;
}

void dezalocare(Persoana** vector, int* nrPersoane)
{
	for (int i = 0; i < *nrPersoane; i++)
	{
		free((*vector)[i].nume);
	}
	free(*vector);
	*vector = NULL;
	*nrPersoane = 0;
}

int main()
{
	Persoana* persoane = NULL;
	int nrPersoane = 0;
	persoane = citireVectorPersoaneFisier("persoane.txt", &nrPersoane);
	afisareVectorPersoane(persoane, nrPersoane);
	dezalocare(&persoane, &nrPersoane);

	return 0;
}
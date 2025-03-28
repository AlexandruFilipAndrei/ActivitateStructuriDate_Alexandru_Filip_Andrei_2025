#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista dublu inlantuita

//creare structura pentru Lista Dubla 

struct Nod {
	Masina info;
	struct Nod* urmator;
	struct Nod* precedent;
};
typedef struct Nod Nod;

struct Lista {
	Nod* prim;
	Nod* ultim;
};
typedef struct Lista Lista;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasiniInceput(Lista list) {
	Nod* p = list.prim;
	while (p)
	{
		afisareMasina(p->info);
		p = p->urmator;
	}
}

void adaugaMasinaInLista(Lista* list, Masina masinaNoua) {
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = masinaNoua;
	p->precedent = list->ultim;
	p->urmator = NULL;
	if (list->ultim)
		list->ultim->urmator = p;
	else
		list->prim = p;
	list->ultim = p;
}

void adaugaLaInceputInLista(Lista* list, Masina masinaNoua) {
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = masinaNoua;
	p->urmator = list->prim;
	p->precedent = NULL;
	if (list->prim)
	{
		list->prim->precedent = p;
	}
	else
	{
		list->ultim = p;
	}
	list->prim = p;



}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Lista list;
	list.prim = NULL;
	list.ultim = NULL;
	while (!feof(f))
	{
		//adaugaMasinaInLista(&list, citireMasinaDinFisier(f));
		adaugaLaInceputInLista(&list, citireMasinaDinFisier(f));
	}
	fclose(f);
	return list;
}

void dezalocareLDMasini(Lista* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	Nod* p = lista->prim;
	while (p->urmator != NULL)
	{
		free(p->info.numeSofer);
		free(p->info.model);
		p = p->urmator;
		free(p->precedent);

	}
	free(p->info.numeSofer);
	free(p->info.model);
	free(p);
	lista->prim = NULL;
	lista->ultim = NULL;

}

float calculeazaPretMediu(Lista lista) {
	//calculeaza pretul mediu al masinilor din lista.
	Nod* aux = lista.prim;
	float suma = 0;
	float cnt = 0;
	while (aux)
	{
		suma += aux->info.pret;
		cnt++;
		aux = aux->urmator;
	}
	return suma / cnt;
}

void stergeMasinaDupaID(Lista* lista, int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	Nod* aux = lista->prim;
	while (aux) {
		if (aux->info.id == id)
		{
			if (aux->precedent)
			{
				aux->precedent->urmator = aux->urmator;
			}
			else
			{
				lista->prim = aux->urmator;
			}

			if (aux->urmator)
			{
				aux->urmator->precedent = aux->precedent;
			}
			else
			{
				lista->ultim = aux->precedent;
			}

			free(aux->info.model);
			free(aux->info.numeSofer);
			free(aux);
			return 0;
		}
		aux = aux->urmator;

	}

}

char* getNumeSoferMasinaScumpa(Lista lista) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	float pretMax = 0;
	char* numeSofer = NULL;
	Nod* aux = lista.prim;
	while (aux)
	{
		if (aux->info.pret > pretMax)
		{
			pretMax = aux->info.pret;
			if (numeSofer)
			{
				free(numeSofer);
			}
			numeSofer = (char*)malloc(strlen(aux->info.numeSofer) + 1);
			strcpy_s(numeSofer, strlen(aux->info.numeSofer) + 1, aux->info.numeSofer);
		}
		aux = aux->urmator;
	}
	return numeSofer;
}

int main() {

	Lista list;
	list = citireLDMasiniDinFisier("masini.txt");
	//afisareListaMasiniInceput(list);
	//float pretMediu = calculeazaPretMediu(list);

	//printf("%f", pretMediu);
	stergeMasinaDupaID(&list, 5);
	afisareListaMasiniInceput(list);
	printf("%s", getNumeSoferMasinaScumpa(list));

	dezalocareLDMasini(&list);

	return 0;
}
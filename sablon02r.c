#include<stdio.h>
#include<malloc.h>

struct Telefon {
	int id;
	int memorie;
	char* producator;
	float pret;
	char serie;
};
struct Telefon initializare(int id,int memorie, char* producator,float pret,char serie) {
	struct Telefon s;
	s.id = id;
	s.memorie = memorie;
	s.producator = (char*)malloc(strlen(producator) + 1);
	strcpy_s(s.producator, strlen(producator) + 1, producator);
	s.pret = pret;
	s.serie = serie;
	return s;
}

void afisare(struct Telefon s) {
	if (s.producator != NULL) {
		printf("\nTelefonul are urmatoarele specificatii: \n");
		printf("ID: %d \n", s.id);
		printf("Memorie: %d \n", s.memorie);
		printf("Producator: %s \n", s.producator);
		printf("Pret: %.2f \n", s.pret);
		printf("Serie: %c \n", s.serie);
	}

}

void afisareVector(struct Telefon* vector, int nrElemente) {
	for (int i = 0;i < nrElemente;i++)
		afisare(vector[i]);
}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Telefon *vectorNou=NULL;
	vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
	for (int i = 0;i <  nrElementeCopiate;i++)
	{
		if (vector[i].producator != NULL)
		{
			vectorNou[i].producator = (char*)malloc(sizeof(strlen(vector[i].producator) + 1));
			strcpy_s(vectorNou[i].producator, strlen(vector[i].producator) + 1, vector[i].producator);
		}
		vectorNou[i] = vector[i];
			
	}

	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	for (int i = 0;i < (*nrElemente);i++)
	{
		if((*vector)[i].producator!=NULL)
			free((*vector)[i].producator);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void pesteprag(struct Telefon* vector, char nrElemente, float prag, struct Telefon** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0;i < nrElemente;i++)
		if (vector[i].pret > prag)
		{
			(*dimensiune)++;
		}
	if ((*vectorNou) != NULL)
	{
		free(*vectorNou);
	}
	(*vectorNou) = (struct Telefon*) malloc(sizeof(struct Telefon) * (*dimensiune));
	int aux = 0;
	for(int i=0;i< nrElemente;i++)
		if (vector[i].pret > prag)
		{
			if (vector[i].producator != NULL)
			{
				(*vectorNou)[aux] = vector[i];
				(*vectorNou)[aux].producator = (char*)malloc(strlen(vector[i].producator)+1);
				strcpy_s((*vectorNou)[aux].producator, strlen(vector[i].producator) + 1, vector[i].producator);
				aux++;

			}
		}

}

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Telefon s;
	for(int i=0;i<nrElemente;i++)
		if (strcmp(vector[i].producator, conditie) == 0)
		{
			s = vector[i];
			s.producator = (char*)malloc(strlen(vector[i].producator) + 1);
			strcpy_s(s.producator, strlen(vector[i].producator) + 1, vector[i].producator);
			return s;
		}
	printf("Nu a fost gasit niciun telefon care sa indeplineasca conditia");
	return s;
}
	


int main() {

	int nrelemente = 3;
	struct Telefon tel=initializare(3, 1024, "Nokia", 4200.50, 'C');
	struct Telefon* Telefoane=NULL;
	Telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrelemente);
	Telefoane[0] = initializare(1, 256, "Samsung", 2000.50, 'A');
	Telefoane[1] = initializare(2, 512, "Apple", 3100.50, 'B');
	Telefoane[2] = initializare(3, 1024, "Nokia", 4200.50, 'C');
	//afisareVector(Telefoane, nrelemente);
	
	struct Telefon* Telefoane2 = NULL;
	Telefoane2 = (struct Telefon*)malloc(sizeof(struct Telefon) * 2);
	Telefoane2=copiazaPrimeleNElemente(Telefoane, nrelemente, 2);
	afisareVector(Telefoane2,2);
	int dimensiune = 0;
	pesteprag(Telefoane, nrelemente, 2000, &Telefoane2, &dimensiune);
	afisareVector(Telefoane2, dimensiune);


	tel= getPrimulElementConditionat(Telefoane, nrelemente, "Samsung");

	afisare(tel);
	dezalocare(&Telefoane, &nrelemente);

	return 0;
}
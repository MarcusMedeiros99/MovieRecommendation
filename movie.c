#include "movie.h"
#include <malloc.h>
#include <string.h>

/*Struct que representa um filme no programa*/
struct movie {
	char* name;/*Nome do filme*/
	int year;/*Ano do filme*/
	char** gender;/*Ponteiro que irá representar o vetor de gêneros que o filme contém*/
	int nGenders;/*Número de gêneros que o filme contém*/
	VECTOR* synopsis;/*Vetor com as palavras da sinopse*/
};

Movie* createMovie(char* name, int year, char** gender, int nGenders, VECTOR* synopsis, int* error) {
	Movie* novo = (Movie*) malloc(sizeof(Movie));

	if (novo) {
		novo->name = (char*) malloc(50 * sizeof(char));
		if (novo->name) strcpy(novo->name, name);
		novo->year = year;
		novo->gender = (char**) malloc(nGenders*sizeof(char*));

		for (int i = 0; i < nGenders; i++) {
			novo->gender[i] = (char *) malloc(TAM_STR*sizeof(char));

			if (!gender[i]) {
				for (int j = 0; j < i; j++) free(novo->gender[j]);
				free(novo);

				*error = TRUE;
				return NULL;
			}
			strcpy(novo->gender[i], gender[i]);	
		}
		mergesort(synopsis, 0, VECTOR_size(synopsis)-1);
		novo->synopsis = synopsis;
		novo->nGenders = nGenders;

		*error = FALSE;
		return novo;
	}

	*error = TRUE;
	return NULL;
}

char* getName(Movie* m, int* error) {
	if (m) {
		*error = FALSE;
		return m->name;
	}
	*error = TRUE;
	return NULL;
}
int getYear(Movie* m, int* error) {
	if (m) {
		*error = FALSE;
		return m->year;
	}
	*error = TRUE;
	return -1;
}
char** getGender(Movie* m, int* error) {
	if (m) {
		*error = FALSE;
		return (char**) m->gender;
	}
	*error = TRUE;
	return NULL;
}

int getNGenders(Movie* m, int* error) {
	if (m) {
		*error = FALSE;
		return m->nGenders;
	}
	*error = TRUE;
	return -1;
}

VECTOR* getSynopsis(Movie* m, int* error) {
	if (m) {
		*error = FALSE;
		return m->synopsis;
	}
	*error = TRUE;
	return NULL;
}

void printMovie(Movie* m, int* error) {
	if (m){
		printf("Title: %s\n", m->name);
		printf("Year: %d\n", m->year);
		printf("Gender(s): ");
		for (int i = 0; i < m->nGenders; i++) {
			printf("%s ", m->gender[i]);
		}
		printf("\n\n");
	}
}

boolean containsGender(Movie* m, char* gender, int* error) {
	for (int i = 0; i < m->nGenders; i++) {
		if (!strcmp(gender, m->gender[i])) return TRUE;
	}
	return FALSE;
}

void destroyMovie(Movie* m, int* error) {
	if (m) {
		for (int i = 0; i < m->nGenders; ++i)
		{
			if(m->gender[i])free(m->gender[i]);
		}
		free(m->synopsis);
		free(m);
		*error = FALSE;
	}
	else {
		*error = TRUE;
	}
}
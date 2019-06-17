#include "graph.h"
#include "movie.h"
#include <malloc.h>
#include <string.h>
#include "Merge and Match/merge_and_match.h"

#define MAX_GENDERS 100

#ifndef BOOLEAN

#define BOOLEAN

#define TRUE 1
#define FALSE 0

typedef int boolean;

#endif

typedef struct node {
	struct node* next;
	Movie* m;
	int i;
} Node;

typedef struct list {
	Node* begin;
	Movie* m;
	struct list* next;
	int i;
} List;

struct graph {
	List* nodes;
	char** genders;
	int nGenders;
	int nNodes;
};

Graph* createGraph(int* error) {
	Graph* g = (Graph*) malloc(sizeof(Graph));

	if (g) {
		g->nodes = (List*) malloc(sizeof(List));
		g->nNodes = 0;
		g->nGenders = 0;
		g->genders = (char**) malloc(MAX_GENDERS*sizeof(char*));

		if (g->genders) {
			for (int i = 0; i < MAX_GENDERS; i++) {
				g->genders[i] = (char*) malloc(TAM_STR*sizeof(char));
				if (!g->genders[i]) {
					*error = TRUE;
				}
			}
		}
		if (g->nodes) {
			g->nodes->begin = (Node*) malloc(sizeof(Node));
			g->nodes->next = NULL;
			g->nodes->i = -1;

			if (g->nodes->begin) {
				g->nodes->begin->next = NULL;
				g->nodes->begin->i = -1;
				
				

				*error = FALSE;

				return g;
			}
			free(g->nodes);
		}
		free(g);
	}
	*error = TRUE;
	return NULL;
}

Movie* getMovieByI(Graph* g, int i, int* error) {
	List* l = g->nodes->next;
	for (int j = 0; j < g->nNodes; j++) {
		if (l->i != i) l = l->next;
	}
	return l->m;
}

void insertMovieAux(List* l, List* newList, Movie* m,int* error) {
	Node* newMovie = (Node*) malloc(sizeof(Node));
	Node* oldMovie = (Node*) malloc(sizeof(Node));

	if(newMovie && oldMovie) {
		newMovie->m = m;
		newMovie->i = newList->i;

		newMovie->next = l->begin->next;
		l->begin->next = newMovie;

		oldMovie->m = l->m;
		oldMovie->i = l->i;

		oldMovie->next = newList->begin->next;
		newList->begin->next = oldMovie;

		*error = FALSE;
		return;
	}
	*error = TRUE;
	return;

}

int getNMovies(Graph* g, int* error) {
	if (g) {
		*error = FALSE;
		return g->nNodes;
	}
	*error = TRUE;
	return -1;
}

//funtion for inserting a movie in the graph. For simplicity, it assumes the movie wasn't inserted before
void insertMovie(Graph* g, Movie* m, int* error) {
	List* newList = (List*) malloc(sizeof(List));

	if (newList) {
		newList->begin = (Node*) malloc(sizeof(Node));
		newList->next = NULL;
		newList->m = m;
		newList->i = g->nNodes;

		if (newList->begin) {
			newList->begin->next = NULL;
			newList->begin->i = -1;

			newList->next = g->nodes->next;
			g->nodes->next = newList;

			boolean* jaInseriu = (boolean*) malloc( (g->nNodes + 1) * sizeof(boolean));
			if (jaInseriu) {
				for (int i = 0; i < g->nNodes + 1; i++) {
					jaInseriu[i] = FALSE;
				}
				jaInseriu[0] = TRUE;
			}
			else {
				*error = TRUE;
				return;

			}

			char strI[TAM_STR];
			char str[TAM_STR];
			List* l = g->nodes->next;
			int nGenders = getNGenders(m, error);
			
			for (int i = 0; i < g->nNodes + 1; i++) {
				int nGendersI = getNGenders(l->m, error);
				for (int j = 0; j < nGenders; j++) {
					for (int k = 0; k < nGendersI; k++) {		
						strcpy(str, getGender(m, error)[j]);
						strcpy(strI, getGender(l->m, error)[k]);
						if (!strcmp(str, strI) && ! jaInseriu[i]) {
							insertMovieAux(l, newList, m, error);
							jaInseriu[i] = TRUE;
						}
					}
				}
				l = l->next;
			}


			for (int i = 0; i < nGenders; i++) {
				int jaExiste = FALSE;
				for (int j = 0; j < g->nGenders; j++) {
					if (!strcmp(getGender(m, error)[i], g->genders[j])) jaExiste = TRUE;
				}
				if (!jaExiste) strcpy(g->genders[g->nGenders++],getGender(m, error)[i]);
			}

			g->nNodes++;

			*error = FALSE;
			return;
		}
	}
	*error = TRUE;
}

double similarity(Graph *g, int e1, int e2, int* error) {
	if (g && e1 < g->nNodes && e2 < g->nNodes) {
		VECTOR* intersec = VECTOR_create();
		VECTOR* unio = VECTOR_create();
		VECTOR* sinopse1;
		VECTOR* sinopse2;

		List* l1 = g->nodes->next;
		List* l2 = g->nodes->next;
		for (int i = 0; i < g->nNodes; i++) {
			if(l1->i != e1 ) l1 = l1->next;
			if(l2->i != e2) l2 = l2->next;
		}

		sinopse1 =  getSynopsis(l1->m, error);
		sinopse2 = getSynopsis(l2->m, error);
		

		merge_and_match(sinopse1, sinopse2, unio, intersec);

		*error = FALSE;
		return (double) intersec->vId / (double) unio->vId;
	}
	*error = TRUE;
	return -1;
}


int* listSimilar(Graph* g, int movie, int* error) {
	int* movies = (int *) malloc( (g->nNodes) * sizeof(int));
	double* sim = (double *) malloc( (g->nNodes)* sizeof(double));
	if (movies && sim) {

		for (int i = 0; i < g->nNodes; i++) movies[i] = i;

		for (int i = 0; i < g->nNodes; i++) {
			sim[i] = similarity(g, movie, i, error);
			int aux = movies[i];
			int j = i - 1;
			while (j >= 0 && sim[aux] > sim[movies[j]]){
				movies[j+1] = movies[j];
				j--;
			}
			movies[j+ 1] = aux;
		}
		*error = FALSE;
		return movies;
	}
	*error = TRUE;
	if (movies) free(movies);
	if (sim) free(sim);
	return NULL;
}

void dispMostSimilar(Graph* g, int movie, int* error) {
	if (g) {
		int* sim = listSimilar(g, movie, error);
		printf("%s\n", getName(getMovieByI(g, sim[1], error), error) );
		free(sim);
	}
}

void dispLeastSimilar(Graph* g, int movie, int* error) {
	if (g) {
		int* sim = listSimilar(g, movie, error);
		printf("%s\n", getName(getMovieByI(g, sim[g->nNodes - 1], error), error) );
	}
}

void displayAllOfAGender(Graph* g, int gender, int* error) {
	int k = 0;
	List *l = g->nodes->next;
		for (int i = 0; i < g->nNodes; i++) {
			if (containsGender(l->m, g->genders[gender], error)) {
				printf("[%d] %s\n", k++, getName(l->m, error));
				Node* n = l->begin->next;
				while (n != NULL) {
					if (containsGender(n->m, g->genders[gender], error)) printf("[%d] %s\n", k++, getName(n->m, error));
					n = n->next;
				}
				break;
			}
			l = l->next;
		}
}

void printGraph(Graph* g, int* error) {
	if (g) {
		List* l = g->nodes->next;
		for (int i = 0 ; i < g->nNodes; i++) {
			Node* n = l->begin;
			printf("%d : ", l->i);
			while(n->next != NULL) {
				n = n->next;
				n->next != NULL ? printf("(%d,%d),", l->i, n->i) : printf("(%d,%d)", l->i, n->i);
			}
			printf("\n");
			l = l->next;
		}
	}
}

void printMenu() {
	printf("MENU\n");
	printf("1 - Most recommended based on a movie\n");
	printf("2 - Least recommended based on a movie\n");
	printf("3 - Display all genders\n");
	printf("4 - Display all of same gender\n");
	printf("5 - Display all of a gender\n");
	printf("6 - Display all movies\n");
	printf("7 - Display details of a movie\n");
	printf("8 - Leave\n");
	printf("\n");

}

//display all movies that have at least one gender in common
void displayAllOfSameGender(Graph*g, int movie, int* error) {
	if (g && movie < g->nNodes) {
		List* l = g->nodes->next;
		while (l->i != movie) l = l->next;
		Node* n = l->begin->next;
		int k = 0;
		while (n != NULL) {
			printf("[%d] %s\n", k++, getName(n->m, error));
			n = n->next;
		}
		*error = FALSE;
		return;
	}
	*error = TRUE;
}

void displayGenders(Graph *g, int* error) {
	if (g) {
		for (int i = 0; i < g->nGenders; i++) {
			printf("[%d] %s\n", i, g->genders[i]);
		}
		*error = FALSE;
		return;
	}
	*error = TRUE;
}

void dispMoviesAux(List* l, int*error) {
	if (l == NULL) return;
	dispMoviesAux(l->next, error);
	printf("[%d] %s\n",  l->i, getName(l->m, error));
}

void displayMovies(Graph* g, int* error) {
	*error = FALSE;
	if (g) {
		dispMoviesAux(g->nodes->next, error);
		printf("\n");
		return;
	}
	*error = TRUE;
}

void destroyAux(Node* n, int* error) {
	if (!n) {
		*error = FALSE;
		return;
	}
	destroyAux(n->next, error);
	free(n);
}

void destroyLists(List* l, int* error) {
	if (!l) {
		*error = FALSE;
		return;
	}
	destroyAux(l->begin, error);
	destroyLists(l->next, error);
	destroyMovie(l->m, error);
	free(l);
}

void destroyGraph(Graph* g, int* error) {
	if (g) {
		destroyLists(g->nodes, error);
		for (int i = 0; i < g->nNodes; i++) free(g->genders[i]);
		free(g->genders);
		free(g);

		*error = FALSE;
		return;
	}
	*error = TRUE;
}
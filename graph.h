#ifndef GRAPH_H

#define GRAPH_H
#include "movie.h"

typedef struct graph Graph;

Graph* createGraph (int* error);
void insertMovie (Graph* g, Movie* m, int* error);
Movie* getMovieByI(Graph* g, int i, int* error);
int getNMovies (Graph* g, int* error);
void destroyGraph (Graph *g, int* error);
double similarity(Graph* g, int e1, int e2, int* error);
void printGraph(Graph* g, int* error);
void displayMovies(Graph* g, int* error);
void displayGenders(Graph* g, int* error);
void displayAllOfAGender(Graph* g, int gender, int* error);
void displayAllOfSameGender(Graph* g, int movie, int* error);
void dispMostSimilar(Graph* g, int movie, int* error);
void dispLeastSimilar(Graph* g, int movie, int* error);
void printMenu();


#endif
#ifndef MOVIE_H
#define MOVIE_H

#define N_GENDERS 6
#define TAM_STR 20
#include "Merge and Match/merge_and_match.h"

#ifndef BOOLEAN

#define BOOLEAN

#define TRUE 1
#define FALSE 0

typedef int boolean;

#endif

typedef struct movie Movie;

/*Função que cria um filme.
PARÂMETROS: char* name -- nome do filme a ser criado
			int year -- ano do filme
			char** gender -- vetor contendo os gêneros do filme
			int nGenders -- número de gêneros que contém o filme
			VECTOR* synopsis -- vetor contendo as palavras da sinopse
			int* error -- flag de erro
RETORNO:	Movie* -- ponteiro para o filme criado*/
Movie* createMovie(char* name, int year, char** gender, int nGenders, VECTOR* synopsis, int* error);

/*Função que permite recuperar o nome de um filme.
PARÂMETROS: Movie* m -- ponteiro para o filme a ser recuperado o nome
			int* error -- flag de erro
RETORNO:	char* -- o nome do filme*/
char* getName(Movie* m, int* error);

/*Função que permite recuperar o ano de um filme.
PARÂMETROS: Movie* m -- ponteiro para o filme a ser recuperado o ano
			int* error -- flag de erro
RETORNO:	int -- o ano do filme*/
int getYear(Movie* m, int* error);

/*Função que permite recuperar o vetor de generos de um filme.
PARÂMETROS: Movie* m -- ponteiro para o filme a serem recuperados os generos
			int* error -- flag de erro
RETORNO:	char** -- ponteiro para o vetor de generos*/
char** getGender(Movie* m, int* error);

/*Função que permite recuperar o número de generos que o filme tem.
PARÂMETROS:	Movie* m -- ponteiro para o filme a serem recuperados o número de generos
			int* error -- flag de erro
RETORNO:	int -- o número de generos*/
int getNGenders(Movie* m, int* error);

/*Função que permite recuperar o vetor de palavras da sinopse de um filme.
PARÂMETROS:	Movie* m -- ponteiro para o filme a serem recuperados o número de generos
			int* error -- flag de erro
RETORNO:    VECTOR* -- ponteiro para o vetor de sinopse*/
VECTOR* getSynopsis(Movie* m, int* error);

/*Função que imprime um filme na tela.
PARÂMETROS:	Movie* m -- ponteiro para o filme a ser exibido
			int* error -- flag de erro*/
void printMovie(Movie* m, int* error);

/*Função que verifica se um filme pertence a um determinado gênero.
PARÂMETROS:	Movie* m -- ponteiro para o filme
			char* gender -- genero a ser verificado
			int* error -- flag de erro
RETORNO:	boolean -- retorna TRUE se o filme é do genero e FALSE se não é*/
boolean containsGender(Movie* m, char* gender, int* error);

/*Função que libera um filme da memória.
PARÂMETROS:	Movie* m -- ponteiro para o filme a ser desalocado
			int* error -- flag de erro*/
void destroyMovie(Movie* m, int* error);

#endif
#ifndef MM_H
#define MM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct vector VECTOR;

struct vector
{
	char v[20000][100];
	int vId;
};

/*Função que transforma uma string em lowercase
PARÂMETRO: char* -- string a ser transformada
RETORNO: char* -- String em lowercase*/
char* strlwr(char *str);

/*Função que ordena um vetor do tipo VECTOR* em ordem alfabética.
PARÂMETROS:	VECTOR* v -- vetor a ser ordenado
			int beg -- a posição do início do vetor
			int end -- a posição do final do vetor*/
void mergesort (VECTOR* v, int beg, int end);

/*Fnção que recebe dois vetores e separa suas palavras em dois outros vetores, um de merge(união das palavras dos dois vetores)
e um de match(intersecção das palavras/ palavras iguais nos dois vetores).
PARÂMETROS:	VECTOR *sinopse1 e VECTOR *sinopse2 -- vetores a serem comparados
			VECTOR *merge -- vetor que receberá a união dos dois vetores comparados
			VECTOR *match -- vetor que receberá a intersecção dos dois vetores comparados*/
void merge_and_match(VECTOR *sinopse1, VECTOR *sinopse2, VECTOR *merge, VECTOR *match);

/*Função que permite a inserção de uma palavra no vetor.
PARÂMETROS: VECTOR *vc -- vetor a ser inserida a palavra
			char *word -- palavra a ser inserida no vetor*/
void VECTOR_insert(VECTOR *vc, char *word);

/*Função que cria um vetor, alocando-o dinamicamente.
RETORNO: VECTOR* -- ponteiro para o vetor criado*/
VECTOR* VECTOR_create();

/*Função que libera um vetor da memória.
PARÂMETRO: VECTOR* vc -- vetor a ser liberado*/
void VECTOR_free(VECTOR* vc);

/*Função que retorna o tamanho do vetor.
PARÂMETRO: VECTOR* vc -- vetor a ser recuperado o tamanho
RETORNO:   int -- tamanho do vetor*/
int VECTOR_size(VECTOR* vc);

/*Função que imprime na tela todo o conteúdo de um vetor.
PARÂMETRO: VECTOR* vc -- vetor a ser exibido*/
void VECTOR_print(VECTOR *vc);





#endif
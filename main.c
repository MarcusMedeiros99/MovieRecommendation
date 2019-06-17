#include "graph.h"
#include "movie.h"
#include "Merge and Match/merge_and_match.h"
#include <string.h>
#include <stdlib.h>

int mallocError();

int main() {
	
	int error;
	Graph* g = createGraph(&error);

	char* nome = (char *) malloc(100* sizeof(char));
	char* aux = (char* ) malloc(10* sizeof(char));
	int year;
	char** genders = (char **) malloc(N_GENDERS * sizeof(char*));
	char* synopsisWord = (char* ) malloc(100* sizeof(char));

	char url[] = "meus_filmes_prediletos.txt";
	FILE* arq = fopen(url, "r");

	if (genders && nome && synopsisWord) {
		for (int i = 0; i < N_GENDERS; i++) {
			genders[i] = (char *) malloc(sizeof(char));
			if (!genders[i]) return mallocError();
		}
	}
	else return mallocError();

	while (TRUE) {
		//BEGIN - reading name and year
		fscanf(arq, "nome: %[^\n]\n", nome);
		fgets(aux, 6, arq);
		fscanf(arq, "%d", &year);
		//END - reading name and year

		int ch;
		VECTOR* vec = VECTOR_create();
		fgetc(arq);
		fgets(aux, 10, arq);
		int i = 0;
		int j = 0;
		int nGenders;

		
			//BEGIN - reading the genders
			while(TRUE) {
				ch = fgetc(arq);
				if (ch != ',' && ch != '\n') {
					if (!(ch == ' ' && j == 0 )) {
						isalpha(ch) ? (genders[i][j] = toupper(ch) ): (genders[i][j] = ch);
						j++;
					}
				}
				else if (ch == ',') {
					genders[i][j] = '\0';
					j = 0;
					i++;
				}
				else if (ch == '\n') {
					genders[i][j] = '\0';
					nGenders = i + 1;
					break;
				}
			}
			//END - reading the genders
		
		fgets(aux, 10, arq);

		//BEGIN - reading the synopsis
			while (TRUE) {
				i = 0;
				while (TRUE) {
					ch = fgetc(arq);
					if (isalpha(ch)) {
						synopsisWord[i] = toupper(ch);
					}
					else if (isdigit(ch) || ch == '-' || ch == '\'') synopsisWord[i] = ch;
					else if (ch == ' ' || ch == '\n') {
						synopsisWord[i] = '\0';
						break;
					}
					else if (ch == ':' || ch == '.' || ch == ';'|| ch == ')' || ch == ','){
						synopsisWord[i] = '\0';
					}
					else if (ch == EOF) break;
					i++;
				}
				VECTOR_insert(vec, synopsisWord);
				if (ch == '\n' || ch == EOF) break;
			}
		//END - reading the synopsisWord
		

		Movie* m = createMovie(nome, year, genders, nGenders, vec, &error);
		insertMovie(g, m, &error);
		//printf("[%d]", getNMovies(g, &error) - 1);
		//printf(" %s\n", getName(m, &error));
		
		if (ch == EOF) break;
		else fgetc(arq);
		
	}	

	fclose(arq);
	
	int op;
	while (op != 8) {
		printMenu();
		printf("Enter the number of your option: ");
		scanf("%d", &op);
		switch (op) {
		case (1):
			printf("Select movie\n");
			scanf("%d", &op);
			dispMostSimilar(g, op, &error); 
			op = 0;
			break;
		case (2):
			printf("select movie\n");
			scanf("%d", &op);
			dispLeastSimilar(g, op, &error); 
			op = 0;
			break;
		case (3):
			displayGenders(g, &error);
			break;
		case (4):
			printf("Select movie: ");
			scanf("%d", &op);
			displayAllOfSameGender(g, op, &error);
			op = 0;
			break;
		case (5):
			printf("Select gender: ");
			scanf("%d", &op);
			displayAllOfAGender(g, op, &error);
			op = 0;
			break;
		case (6):
			displayMovies(g, &error);
			break;
		case (7):
			printf("Select movie: ");
			scanf("%d", &op);
			printMovie(getMovieByI(g, op, &error), &error);
			op = 0;
			break;
		case (8):
			break;
		default:
			printf("Invalid option! Try again\n");
		}

	}

	printf("Leaving...\n");

	free(nome);
	free(aux);
	free(genders);
	free(synopsisWord);

	destroyGraph(g, &error);

	return 0;
}

int mallocError() {
	printf("malloc returned NULL\n");
	return 1;
}
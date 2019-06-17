#include "merge_and_match.h"


char* strlwr(char *str){
  char *p = (char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}

void mergesort (VECTOR* v, int beg, int end) {
	if (end <= beg) return;

	int center = (int)((end+beg)/2.0);

	mergesort(v, beg, center);
	mergesort(v, center+1, end);

	VECTOR* aux = (VECTOR*) malloc(sizeof(VECTOR) * (end-beg+1) );
	
	int i = beg;	
	int j = center+1;
 	int k = 0;	

	while (i <= center && j <= end) {
		if (strcmp(v->v[i], v->v[j]) <= 0) {
			strcpy(aux->v[k], v->v[i]);
			i++;
		} 
		else {
			strcpy(aux->v[k], v->v[j]);
			j++; 
		}
		k++; 
	}

	while (i <= center) {
		strcpy(aux->v[k], v->v[i]);
		i++; k++;
	}
	while (j <= end) {
		strcpy(aux->v[k], v->v[j]);
		j++; k++;
	}	
	for (i = beg, k = 0; i <= end; i++, k++) {
		strcpy(v->v[i], aux->v[k]);
	}

	free(aux); 
}

void merge_and_match(VECTOR *sinopse1, VECTOR *sinopse2, VECTOR *merge, VECTOR *match){
	int aux1 = 0, aux2 = 0;

	while((aux1 < sinopse1->vId) && (aux2 < sinopse2->vId)){
		if (strcmp(sinopse1->v[aux1], sinopse2->v[aux2]) < 0)
		{
			VECTOR_insert(merge, sinopse1->v[aux1]);
			aux1++;
		}
		else if (strcmp(sinopse1->v[aux1], sinopse2->v[aux2]) == 0)
		{
			VECTOR_insert(merge, sinopse1->v[aux1]);
			VECTOR_insert(match, sinopse1->v[aux1]);
			aux1++;
			aux2++;
		}
		else{
			VECTOR_insert(merge, sinopse2->v[aux2]);
			aux2++;
		}

	}

	while(aux1 < sinopse1->vId){
		VECTOR_insert(merge, sinopse1->v[aux1]);
		aux1++;
	}
	while(aux2 < sinopse2->vId){
		VECTOR_insert(merge, sinopse2->v[aux2]);
		aux2++;
	}
}

void VECTOR_insert(VECTOR *vc, char *word){
	strcpy(vc->v[vc->vId], word);
	vc->vId++;
}

VECTOR* VECTOR_create(){
	VECTOR *vc = (VECTOR*)malloc(sizeof(VECTOR));
	vc->vId = 0;
	return vc;
}

void VECTOR_free(VECTOR* vc){
	free(vc);
}

int VECTOR_size(VECTOR* vc){
	return vc->vId;
}

void VECTOR_print(VECTOR *vc){
	for (int i = 0; i < vc->vId; ++i)
	{
		printf("%s\n", vc->v[i]);
	}
	printf("--------------\n");
}
#include "merge_and_match.h"

int main(int argc, char const *argv[])
{
	VECTOR* v1 = VECTOR_create();
	VECTOR* v2 = VECTOR_create();

	VECTOR_insert(v1, "caqui");
	VECTOR_insert(v1, "abacate");
	VECTOR_insert(v1, "banana");
	VECTOR_insert(v1, "doce");
	VECTOR_insert(v1, "limao");

	VECTOR_insert(v2, "abacate");
	VECTOR_insert(v2, "carambora");
	VECTOR_insert(v2, "maca");
	VECTOR_insert(v2, "morango");
	VECTOR_insert(v2, "banana");


	mergesort(v1, 0, VECTOR_size(v1)-1);
	mergesort(v2, 0, VECTOR_size(v2)-1);

	VECTOR* merge = VECTOR_create();
	VECTOR* match = VECTOR_create();

	merge_and_match(v1, v2, merge, match);

	VECTOR_print(v1);
	VECTOR_print(v2);
	VECTOR_print(merge);
	VECTOR_print(match);


	VECTOR_free(v1);
	VECTOR_free(v2);
	VECTOR_free(merge);
	VECTOR_free(match);
	return 0;
}
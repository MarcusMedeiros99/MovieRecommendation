all:
	gcc -c movie.c -o movie.o
	gcc -c graph.c -o graph.o
	gcc -c ./Merge\ and\ Match/merge_and_match.c -o ./merge_and_match.o
	gcc -c main.c -o main.o
	gcc movie.o graph.o main.o merge_and_match.o -o main
run:
	./main

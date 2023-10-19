all: red-black_trees.o main.o
	gcc red-black_trees.o main.o -o main

run:
	./main

red-black_trees.o: red-black_trees.c
	gcc -c red-black_trees.c

main.o: main.c
	gcc -c main.c

clean: 
	rm main red-black_trees.o main.o

.PHONY: all clean run 
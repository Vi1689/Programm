all: comp

comp: CAOD_laba3.o binary_heap.o
	gcc -Wall CAOD_laba3.o binary_heap.o -o main
CAOD_laba3.o: CAOD_laba3.c
	gcc -c CAOD_laba3.c
binary_heap.o: binary_heap.c
	gcc -c binary_heap.c
clean: 
	rm CAOD_laba3.o binary_heap.o main
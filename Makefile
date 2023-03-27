comp: main.o IntVector.o
	gcc -Wall IntVector.o main.o -o main
IntVector.o: IntVector.c
	gcc -c IntVector.c
main.o: main.c
	gcc -c main.c
clean: 
	rm IntVector.o main.o main
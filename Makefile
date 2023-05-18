all: main

main: KP_proga.o calc.o stack.o check.o
	gcc -Wall $^ -o $@

KP_proga.o:
	gcc -c KP_proga.c -o KP_proga.o

calc.o:
	gcc -c calc.c -o calc.o

stack.o:
	gcc -c stack.c -o stack.o

check.o:
	gcc -c check.c -o check.o

clean:
	rm stack.o calc.o KP_proga.o main check.o

.PHONY: all clean run
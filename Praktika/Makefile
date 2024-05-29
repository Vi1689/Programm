APP_NAME = main

all:
	gcc -Wall -g qwe.c -o $(APP_NAME)
	clang-format -i ./$(APP_NAME)

clear:
	rm $(APP_NAME)

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(APP_NAME)

.PHONY: all clear valgrind
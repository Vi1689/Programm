NAME = 18
LIB = normal
APP_NAME = main
APP_NAME_GDB = gdb

all: gdb
	g++ -g -std=c++20 -Wall -Werror -fsanitize=address -static-libasan $(LIB)/$(NAME).cpp -o $(LIB)/$(APP_NAME)
	clang-format -i $(LIB)/$(NAME).cpp

run:
	./$(LIB)/$(APP_NAME)

clean: 
	rm $(LIB)/$(APP_NAME) $(LIB)/$(APP_NAME_GDB)

gdb:
	g++ -g -std=c++20 $(LIB)/$(NAME).cpp -o $(LIB)/$(APP_NAME_GDB) -lm

gdb_run:
	gdb $(LIB)/$(APP_NAME_GDB)

valgrind:
	g++ -Wall -Werror -std=c++20 $(LIB)/$(NAME).cpp -o $(LIB)/$(APP_NAME)
	valgrind --tool=memcheck --leak-check=yes  -s ./$(LIB)/$(APP_NAME)

.PHONY: all clean run gdb gdb_run valgrind
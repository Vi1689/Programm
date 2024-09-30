NAME = 11
LIB = normal
APP_NAME = main
APP_NAME_GDB = gdb

all: $(LIB)/$(NAME).o gdb
	g++ -Wall -Werror $(LIB)/$(NAME).o -o $(LIB)/$(APP_NAME)
	clang-format -i $(LIB)/$(NAME).cpp

$(LIB)/$(NAME).o: $(LIB)/$(NAME).cpp
	g++ -c $(LIB)/$(NAME).cpp -o $(LIB)/$(NAME).o

run:
	./$(LIB)/$(APP_NAME)

clean: 
	rm $(LIB)/$(APP_NAME) $(LIB)/$(NAME).o $(LIB)/$(APP_NAME_GDB)

gdb:
	g++ -g $(LIB)/$(NAME).cpp -o $(LIB)/$(APP_NAME_GDB) -lm

gdb_run:
	gdb $(LIB)/$(APP_NAME_GDB)

valgrind:
	valgrind --tool=memcheck --leak-check=yes  -s ./$(LIB)/$(APP_NAME)

.PHONY: all clean run gdb gdb_run valgrind
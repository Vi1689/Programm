APP_NAME = kursach
GDB_NAME = gdb

all: gdb form
	g++ -Wall -O3 $(APP_NAME)/$(APP_NAME).cpp -o $(APP_NAME)/$(APP_NAME)

show:
	gnuplot $(APP_NAME)/$(APP_NAME).gp

form:
	clang-format -i $(APP_NAME)/$(APP_NAME).cpp

run:
	./$(APP_NAME)/$(APP_NAME)

clear: 
	rm $(APP_NAME)/$(APP_NAME) $(APP_NAME)/$(GDB_NAME)

gdb:
	g++ -g $(APP_NAME)/$(APP_NAME).cpp -o $(APP_NAME)/$(GDB_NAME)

gdb_run:
	gdb $(APP_NAME)/$(GDB_NAME)

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(APP_NAME)/$(APP_NAME)

.PHONY: all clear run gdb gdb_run valgrind form show

APP_NAME = lab_5
GDB_NAME = gdb
OPT = -fopenmp -lm

SRC = $(wildcard $(APP_NAME)/*.c)
OBJ = $(patsubst $(APP_NAME)/%.c, $(APP_NAME)/%.o, $(SRC))

all: form $(APP_NAME)/$(APP_NAME).a
	gcc -Wall -pg $(OPT) $(APP_NAME)/$(APP_NAME).a -o $(APP_NAME)/$(APP_NAME)

show:
	gnuplot $(APP_NAME)/$(APP_NAME).gp

form:
	clang-format -i $(APP_NAME)/*.c

$(APP_NAME)/$(APP_NAME).a: $(OBJ)
	ar rcs $@ $^

$(APP_NAME)/%.o: $(APP_NAME)/%.c
	gcc -c $^ -o $@

gdb:
	gcc -g $(OPT) $(APP_NAME)/$(APP_NAME).c -o $(APP_NAME)/$(GDB_NAME)

gdb_run:
	gdb $(APP_NAME)/$(GDB_NAME)

run:
	./$(APP_NAME)/$(APP_NAME)

clear:
	rm $(APP_NAME)/*.o $(APP_NAME)/*.a $(APP_NAME)/$(APP_NAME) $(APP_NAME)/$(GDB_NAME)

valgrind:
	valgrind --tool=memcheck --leak-check=full -s ./$(APP_NAME)/$(APP_NAME)

.PHONY: all clear run valgrind form show

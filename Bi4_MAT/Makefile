APP_NAME = laba_2
GDB_NAME = gdb

all: $(APP_NAME).o gdb
	g++ $(APP_NAME).o -o $(APP_NAME)

$(APP_NAME).o: $(APP_NAME).cpp
	g++ -c $(APP_NAME).cpp -o $(APP_NAME).o

run:
	./$(APP_NAME)

clean: 
	rm $(APP_NAME).o $(APP_NAME) $(GDB_NAME)

gdb:
	g++ -g $(APP_NAME).cpp -o $(GDB_NAME)

gdb_run:
	gdb $(GDB_NAME)

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(APP_NAME)

.PHONY: all clean run gdb gdb_run valgrind
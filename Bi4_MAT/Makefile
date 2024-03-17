APP_NAME = laba_4
GDB_NAME = gdb

all: $(APP_NAME)/$(APP_NAME).o gdb
	g++ $(APP_NAME)/$(APP_NAME).o -o $(APP_NAME)/$(APP_NAME)

$(APP_NAME)/$(APP_NAME).o: $(APP_NAME)/$(APP_NAME).cpp
	g++ -c $(APP_NAME)/$(APP_NAME).cpp -o $(APP_NAME)/$(APP_NAME).o

run:
	./$(APP_NAME)/$(APP_NAME)

clean: 
	rm $(APP_NAME)/$(APP_NAME).o $(APP_NAME)/$(APP_NAME) $(APP_NAME)/$(GDB_NAME)

gdb:
	g++ -g $(APP_NAME)/$(APP_NAME).cpp -o $(APP_NAME)/$(GDB_NAME)

gdb_run:
	gdb $(APP_NAME)/$(GDB_NAME)

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(APP_NAME)/$(APP_NAME)

.PHONY: all clean run gdb gdb_run valgrind
APP_NAME = main
LIB_STATIC = kursach
LIB_DYNAMIC = oke


all: $(LIB_STATIC)/$(LIB_STATIC).o gdb $(LIB_STATIC)/$(LIB_DYNAMIC).o
	g++ $(LIB_STATIC)/$(LIB_STATIC).o  $(LIB_STATIC)/$(LIB_DYNAMIC).o -o $(LIB_STATIC)/$(APP_NAME)

run:
	./$(LIB_STATIC)/$(APP_NAME)

$(LIB_STATIC)/$(LIB_STATIC).o: $(LIB_STATIC)/$(LIB_STATIC).cpp
	g++ -c $(LIB_STATIC)/$(LIB_STATIC).cpp -o $(LIB_STATIC)/$(LIB_STATIC).o

$(LIB_STATIC)/$(LIB_DYNAMIC).o: $(LIB_STATIC)/$(LIB_DYNAMIC).cpp
	g++ -c $(LIB_STATIC)/$(LIB_DYNAMIC).cpp -o $(LIB_STATIC)/$(LIB_DYNAMIC).o

clean: 
	rm $(LIB_STATIC)/$(APP_NAME) $(LIB_STATIC)/$(LIB_STATIC).o $(APP_NAME) $(LIB_STATIC)/$(LIB_DYNAMIC).o

gdb:
	g++ -g $(LIB_STATIC)/$(LIB_STATIC).cpp $(LIB_STATIC)/$(LIB_DYNAMIC).cpp -o $(APP_NAME)

gdb_run:
	gdb main

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(APP_NAME)

.PHONY: all clean run gdb gdb_run valgrind
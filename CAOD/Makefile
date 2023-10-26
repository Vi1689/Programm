APP_NAME = main
LIB_STATIC = laba_2
LIB_DYNAMIC = trie_tree


all: $(LIB_STATIC)/$(LIB_STATIC).o gdb $(LIB_STATIC)/$(LIB_DYNAMIC).o
	gcc $(LIB_STATIC)/$(LIB_STATIC).o  $(LIB_STATIC)/$(LIB_DYNAMIC).o -o $(LIB_STATIC)/$(APP_NAME)

run:
	./$(LIB_STATIC)/$(APP_NAME)

$(LIB_STATIC)/$(LIB_STATIC).o: $(LIB_STATIC)/$(LIB_STATIC).c
	gcc -c $(LIB_STATIC)/$(LIB_STATIC).c -o $(LIB_STATIC)/$(LIB_STATIC).o

$(LIB_STATIC)/$(LIB_DYNAMIC).o: $(LIB_STATIC)/$(LIB_DYNAMIC).c
	gcc -c $(LIB_STATIC)/$(LIB_DYNAMIC).c -o $(LIB_STATIC)/$(LIB_DYNAMIC).o

clean: 
	rm $(LIB_STATIC)/$(APP_NAME) $(LIB_STATIC)/$(LIB_STATIC).o $(APP_NAME) $(LIB_STATIC)/$(LIB_DYNAMIC).o

gdb:
	gcc -g $(LIB_STATIC)/$(LIB_STATIC).c $(LIB_STATIC)/$(LIB_DYNAMIC).c -o $(APP_NAME)

gdb_run:
	gdb main

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(APP_NAME)

.PHONY: all clean run gdb gdb_run valgrind
APP_NAME = kursach
GBD_NAME = gdb

all : $(APP_NAME).o gdb $(GBD_NAME).o
	g++ $(APP_NAME).o -o $(APP_NAME) -lsfml-graphics -lsfml-window -lsfml-system

run : 
	./$(APP_NAME)

$(APP_NAME).o : $(APP_NAME).cpp
	g++ -c $(APP_NAME).cpp -o $(APP_NAME).o -lsfml-graphics -lsfml-window -lsfml-system

$(GBD_NAME).o:
	g++ -g $(APP_NAME).cpp -o $(GBD_NAME) -lsfml-graphics -lsfml-window -lsfml-system

clean: 
	rm $(APP_NAME) $(APP_NAME).o $(GBD_NAME)

gdb_run:
	gdb $(GBD_NAME)

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(GBD_NAME)

.PHONY: all clean run gdb gdb_run valgrind
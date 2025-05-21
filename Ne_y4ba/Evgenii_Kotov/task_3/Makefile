APP_NAME=main

all: $(APP_NAME).o
	g++ -Wall -Wextra -Werror $^ -O3 -o $(APP_NAME)
	clang-format -i *.cpp

$(APP_NAME).o: $(APP_NAME).cpp 
	g++ -c $^ -o $@

gdb:
	g++ -g -Wall -Wextra -Werror $(APP_NAME).cpp -o $(APP_NAME);

valgrind:
	valgrind --tool=memcheck --leak-check=yes -s ./$(APP_NAME)

clean:
	rm *.o $(APP_NAME)
CXX = gcc
CXXFLAGS = -Wall -O2 -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
CLIENT_APP = client
SERVER_APP = server
LIB_NETWORK = my_network
LIB_INFO_PROT = info_protection

all: $(CLIENT_APP) $(SERVER_APP)
	clang-format -i */*.h
	clang-format -i */*.c
	clang-format -i *.c

$(CLIENT_APP): $(CLIENT_APP).o $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(SERVER_APP): $(SERVER_APP).o $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

src/%.o: src/%.c include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind:
	valgrind --tool=memcheck --leak-check=yes  -s ./$(SERVER_APP)

clean:
	rm -f $(OBJ) $(CLIENT_APP).o $(CLIENT_APP) $(SERVER_APP).o $(SERVER_APP)

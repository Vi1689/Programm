CXX = g++
CXXFLAGS = -Wall -O2 -Iinclude
LDFLAGS = -lgmpxx -lgmp

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
APP_NAME = main
LIB_NAME = info_protection

all: $(APP_NAME)
	clang-format -i */*.hpp
	clang-format -i */*.cpp
	clang-format -i *.cpp

$(APP_NAME): $(APP_NAME).o $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(APP_NAME).o: $(APP_NAME).cpp include/$(LIB_NAME).hpp
	$(CXX) -c $(APP_NAME).cpp -Iinclude

src/%.o: src/%.cpp include/$(LIB_NAME).hpp
	$(CXX) -c $< -o $@ -Iinclude

run:
	./$(APP_NAME)

clean:
	rm -f $(OBJ) $(APP_NAME).o $(APP_NAME)

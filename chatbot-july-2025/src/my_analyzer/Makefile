LIB_NAME=libanalyzer
INCLUDE_PATH=./../../include
OBJ_PATH=./../../build/my_analyzer
LIB_PATH=./../../lib

FORM=clang-format -i

CC=gcc -Wall -Wextra -Werror -l$(LIB_PATH)/database -l$(LIB_PATH)/my_parse -I $(INCLUDE_PATH)

SRC_SP=$(wildcard *.c)
OBJ_SP=$(patsubst %.c, $(OBJ_PATH)/%.o, $(SRC_SP))

all: $(LIB_PATH)/$(LIB_NAME).a
	$(FORM) *.c
	$(FORM) $(INCLUDE_PATH)/my_analyzer/*.h

$(LIB_PATH)/$(LIB_NAME).a: $(OBJ_SP)
	ar rcs $@ $^

$(OBJ_PATH)/%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ_SP) $(LIB_PATH)/$(LIB_NAME).a

.PHONY: all clean

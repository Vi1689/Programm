CC := gcc
CFLAGS := -Wall -Wextra -Werror
LIB_NAME := libhashtable.a
INCLUDE := -I../../../include/
SRC_DIR := src
OBJ_DIR := ../../../build/hashtable
LIB_DIR := ../../../lib

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(LIB_DIR)/$(LIB_NAME)

$(LIB_DIR)/$(LIB_NAME): $(OBJ_FILES) | $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)/$(LIB_NAME)

.PHONY: all clean
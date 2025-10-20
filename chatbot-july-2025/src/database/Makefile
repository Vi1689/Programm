CC := gcc
CFLAGS := -Wall -Wextra -Werror
LIB_NAME := libdatabase.a
INCLUDE := -I../../include/
SRC_DIR := src
OBJ_DIR := ../../build/database
LIB_DIR := ../../lib

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(LIB_DIR)/$(LIB_NAME)

$(LIB_DIR)/$(LIB_NAME): $(OBJ_FILES) | $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) ht_make
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

ht_make : 
	$(MAKE) -C ./hashtable

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)/$(LIB_NAME)
	$(MAKE) -C ./hashtable clean

.PHONY: all clean
GCC = gcc

FLAGS = -Wall -Wextra -Werror -g
LNCURSES_FLAGS = -lncurses -lform -pthread

BUILD_DIR = ../../build/ui
LIB_DIR = ../../lib
INC_DIR = ../../include

SRC_AUTH = $(wildcard authentication/*.c)
SRC_CHAT = $(wildcard chat/*.c)

OBJ_AUTH = $(patsubst authentication/%.c, $(BUILD_DIR)/%.o, $(SRC_AUTH))
OBJ_CHAT = $(patsubst chat/%.c, $(BUILD_DIR)/%.o, $(SRC_CHAT))
OBJECTS = $(OBJ_AUTH) $(OBJ_CHAT)

all: $(LIB_DIR)/libui.a format

$(LIB_DIR)/libui.a: $(OBJECTS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: authentication/%.c
	@mkdir -p $(BUILD_DIR)
	$(GCC) $(FLAGS) -I$(INC_DIR) -c $< -o $@ $(LNCURSES_FLAGS)

$(BUILD_DIR)/%.o: chat/%.c
	@mkdir -p $(BUILD_DIR)
	$(GCC) $(FLAGS) -I$(INC_DIR) -c $< -o $@ $(LNCURSES_FLAGS)

clean:
	rm -f $(BUILD_DIR)/*.o $(LIB_DIR)/libui.a

rebuild: clean format all

format:
	clang-format -i authentication/*.c chat/*.c $(INC_DIR)/ui/*.h
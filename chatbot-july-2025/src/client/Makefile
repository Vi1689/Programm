GCC = gcc
FLAGS = -Wall -Wextra -Werror
FLAGS_NCURSES = -lncurses -lform -lsodium

SRC_DIR = .
LIB_DIR = ../../lib
BIN_DIR = ../../bin
INC_DIR = ../../include
BUILD_DIR = ../../build/client

SRC_CLIENT = main.c send_message_to_server.c start_client.c
OBJ_CLIENT = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC_CLIENT))

all: $(BIN_DIR)/client

$(BIN_DIR)/client: $(OBJ_CLIENT)
	@mkdir -p $(BIN_DIR)
	$(GCC) $(FLAGS) $^ ../../build/error_handler.o \
		-L$(LIB_DIR) -lui -lmy_network \
		$(FLAGS_NCURSES) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(GCC) $(FLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(BIN_DIR)/client

rebuild: clean format all

format:
	clang-format -i *.c $(INC_DIR)/client/*.h
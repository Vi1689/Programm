CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

SRC_DIR = .
BUILD_DIR = ../../build/server
BIN_DIR = ../../bin
LIB_DIR = ../../lib

INCLUDE_PATHS = -I../../include \
                -I../../include/database \
                -I../../include/my_analyzer \
                -I../../include/my_parse \
                -I../../include/my_network \
                -I../../include/server_parallelism \
                -I../../include/server \
                -I../../include/client \
                -I../error_handler

SRCS = cleanup_server.c \
       init_server.c \
       restart_server.c \
       run_server_loop.c \
       signal_handler.c \
       udp_listener.c \
       main.c

OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/server

.PHONY: all clean rebuild format

all: $(TARGET)

LIBS = -lparallelism -lanalyzer -lparse -lmy_network -ldatabase -lhashtable -lsodium

$(TARGET): $(OBJS) ../../build/error_handler.o | $(BIN_DIR)
	$(CC) $(LDFLAGS) -L$(LIB_DIR) $(OBJS) ../../build/error_handler.o $(LIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

FORMAT_SRCS = $(wildcard $(SRC_DIR)/*.c)
FORMAT_HDRS = $(wildcard $(SRC_DIR)/*.h)

format:
	find ../.. -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +


clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

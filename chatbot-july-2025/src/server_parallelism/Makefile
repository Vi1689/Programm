CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -pthread

BUILD_DIR = ../../build/server_parallelism
LIB_DIR = ../../lib

INCLUDE_PATHS = -I../../include \
                -I../../include/database \
                -I../../include/my_analyzer \
                -I../../include/my_parse \
                -I../../include/my_network \
                -I../../include/server_parallelism \
                -I../../include/client

PARALLELISM_LIB_NAME = parallelism

PARALLELISM_LIB_A = $(LIB_DIR)/lib$(PARALLELISM_LIB_NAME).a

PARALLELISM_SRCS = \
    add_task.c \
    thread_pool_destroy.c \
    threads_init.c \
    worker.c

PARALLELISM_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(PARALLELISM_SRCS))

FORMAT_CMD = clang-format -i

.PHONY: all format clean

all: $(PARALLELISM_LIB_A)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(PARALLELISM_LIB_A): $(PARALLELISM_OBJS)
	ar rcs $@ $^


format:
	$(FORMAT_CMD) $(PARALLELISM_SRCS) \
	              $(wildcard ../../include/database/*.h) \
	              $(wildcard ../../include/my_analyzer/*.h) \
	              $(wildcard ../../include/my_parse/*.h) \
	              $(wildcard ../../include/*.h) \
	              $(wildcard ../../include/my_network/*.h) \
	              $(wildcard ../../include/server_parallelism/*.h) \
	              $(wildcard ../../include/client/*.h)

clean:
	rm -f $(PARALLELISM_OBJS) $(PARALLELISM_LIB_A)
	rm -rf $(BUILD_DIR)
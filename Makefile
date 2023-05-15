APP_NAME = KP_proga
CODER = stack

SRC_DIR = src

APP_PATH = $(SRC_DIR)/$(APP_NAME)

all: $(APP_PATH)

$(APP_PATH): $(SRC_DIR)/$(CODER).o $(SRC_DIR)/$(APP_NAME).o
	gcc -Wall $^ -o $@
$(SRC_DIR)/%.o: %.c
	gcc -c $@
clean: 
	rm  $(SRC_DIR)/*.o $(APP_PATH)
run: 
	./$(APP_PATH)

.PHONY: all clean run
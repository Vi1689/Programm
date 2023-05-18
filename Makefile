APP_MAIN = main
APP_CALC = calc
APP_CHECK = check
APP_STACK = stack
APP_KP = KP_proga

SRC_DIR = src
LIB_STATIC = proga
LIB_DIR = libproga

APP_PATH = $(SRC_DIR)/$(LIB_STATIC)/$(APP_MAIN)

all: $(APP_PATH)

$(APP_PATH): $(SRC_DIR)/$(LIB_DIR)/$(APP_CALC).o $(SRC_DIR)/$(LIB_DIR)/$(APP_CHECK).o $(SRC_DIR)/$(LIB_DIR)/$(APP_STACK).o $(SRC_DIR)/$(LIB_STATIC)/$(APP_KP).o 
	gcc -Wall $^ -o $@

$(SRC_DIR)/$(LIB_DIR)/%.o: %.c
	gcc -c -Wall -I src $< -o $@

$(SRC_DIR)/$(LIB_STATIC)/$(APP_KP).o: $(SRC_DIR)/$(LIB_STATIC)/$(APP_KP).c
	gcc -c -Wall -I src $< -o $@

clean:
	rm $(SRC_DIR)/$(LIB_DIR)/*.o $(SRC_DIR)/$(LIB_STATIC)/*.o $(APP_PATH)

.PHONY: all clean
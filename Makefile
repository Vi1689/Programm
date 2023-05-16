APP_NAME = main
PROCESS = process
INPUT_OUTPUT = input_output
CHECK = check
STRINGS = strings

LABA4_INCLUDE = laba4/include

APP_PATH = laba4/$(APP_NAME)/$(APP_NAME)

all: $(APP_PATH)

$(APP_PATH): $(LABA4_INCLUDE)/$(PROCESS).o $(LABA4_INCLUDE)/$(INPUT_OUTPUT).o $(LABA4_INCLUDE)/$(CHECK).o $(LABA4_INCLUDE)/$(STRINGS).o laba4/$(APP_NAME)/laba-4.o
	gcc -Wall $^ -o $@
$(LABA4_INCLUDE)/%.o: %.c
	gcc -c $@
laba4/$(APP_NAME)/%.o: %.c
	gcc -c $@
clean: 
	rm  $(LABA4_INCLUDE)/*.o $(APP_PATH) laba4/$(APP_NAME)/*.o
run: 
	./$(APP_PATH)

.PHONY: all clean run
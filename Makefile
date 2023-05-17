APP_NAME = main
PROCESS = process
INPUT_OUTPUT = input_output
CHECK = check
STRINGS = strings

LABA4_INCLUDE = laba4/include
TEST = laba4/test

APP_PATH = laba4/$(APP_NAME)/$(APP_NAME)
TEST_PATH = $(TEST)/test

GG = -Wall -I laba4 -Ithirdparty -MMD

all: $(APP_PATH)

$(APP_PATH): $(LABA4_INCLUDE)/$(PROCESS).o $(LABA4_INCLUDE)/$(INPUT_OUTPUT).o $(LABA4_INCLUDE)/$(CHECK).o $(LABA4_INCLUDE)/$(STRINGS).o laba4/$(APP_NAME)/laba-4.o
	gcc $(GG) $^ -o $@
$(LABA4_INCLUDE)/%.o: %.c
	gcc -c $@
laba4/$(APP_NAME)/%.o: %.c
	gcc -c $@
clean: 
	rm  $(LABA4_INCLUDE)/*.o $(APP_PATH) laba4/$(APP_NAME)/*.o $(TEST)/*.o $(TEST)/*.d
run: 
	./$(APP_PATH)

test: $(TEST_PATH)

$(TEST_PATH): $(TEST)/test_check.o $(TEST)/test_process.o $(TEST)/test_strings.o $(TEST)/main.c
	gcc $(GG) $^ -o $@

laba4/test/%.o: %.c
	gcc  -c -I laba4 $@

test_run: $(TEST_PATH)
	./$(TEST_PATH)

.PHONY: all clean run
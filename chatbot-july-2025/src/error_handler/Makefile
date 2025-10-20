CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCLUDE := -I../../include
RESULT := ../../build/error_handler.o
all : $(RESULT)

$(RESULT) :
	$(CC) $(CFLAGS) $(INCLUDE) -c error_handler.c -o $@ 

clean :
	rm $(RESULT)
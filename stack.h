#ifndef __stack__
#define __stack__

struct stack {
    float* a;
    int top;
    int size;
    int maxsize;
};

struct stack_char {
    char* a;
    int top;
    int size;
    int maxsize;
};

struct stack* stack_create(int maxsize);
void stack_free(struct stack* s);
int stack_size(struct stack* s);
int stack_push(struct stack* s, float value);
float stack_pop(struct stack* s);

struct stack_char* stack_create_char(int maxsize);
void stack_free_char(struct stack_char* s);
int stack_size_char(struct stack_char* s);
int stack_push_char(struct stack_char* s, char value);
int stack_pop_char(struct stack_char* s);

#endif
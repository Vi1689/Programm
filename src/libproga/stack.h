#ifndef __stack__
#define __stack__

struct stack {
    float* a;
    int top;
    int size;
    int maxsize;
};

struct stack* stack_create(int maxsize);
void stack_free(struct stack* s);
int stack_size(struct stack* s);
float stack_top(struct stack* s);
int stack_push(struct stack* s, float value);
float stack_pop(struct stack* s);

#endif
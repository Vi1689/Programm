#include "IntVector.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    IntVector* a = int_vector_new(1);
    printf("Vector a : data : %p size : %ld capacity : %ld\nVector a : ",
           a->data,
           int_vector_get_size(a),
           int_vector_get_capacity(a));
    IntVector* b = int_vector_copy(a);
    for (int i = 0; i < 10; ++i) {
        int_vector_push_back(a, i);
        int_vector_push_back(b, 10 - i);
    }
    for (int i = 0; i < 10; ++i) {
        printf("%d ", int_vector_get_item(a, i));
    }
    printf("\nVector b : ");
    for (int i = 0; i < 10; ++i) {
        printf("%d ", int_vector_get_item(b, i));
    }
    printf("\nVector b : data : %p size : %ld capacity : %ld\n",
           b->data,
           b->size,
           b->capacity);
    int_vector_resize(b, 100);
    printf("Vector b : data : %p size : %ld capacity : %ld\n",
           b->data,
           int_vector_get_size(b),
           int_vector_get_capacity(b));
    int_vector_push_back(b, 33);
    printf("Vector b : data : %p size : %ld capacity : %ld\n",
           b->data,
           b->size,
           b->capacity);
    printf("Vector b : ");
    for (int i = 0; i < int_vector_get_size(b); ++i) {
        printf("%d ", int_vector_get_item(b, i));
    }
    int_vector_reserve(a, 100);
    printf("\nVector a : data : %p size : %ld capacity : %ld\n",
           a->data,
           a->size,
           a->capacity);
    int_vector_resize(a, 0);
    printf("Vector a : data : %p size : %ld capacity : %ld\n",
           a->data,
           a->size,
           a->capacity);
    int_vector_push_back(a, 33);
    printf("Vector a : data : %p size : %ld capacity : %ld\n",
           a->data,
           a->size,
           a->capacity);
    int_vector_pop_back(a);
    printf("Vector a : data : %p size : %ld capacity : %ld\n",
           a->data,
           a->size,
           a->capacity);
    int_vector_resize(a, 10);
    for (int i = 0; i < 10; ++i) {
        int_vector_set_item(a, i, 10 - i);
        printf("%d ", int_vector_get_item(a, i));
    }
    printf("\nVector a : data : %p size : %ld capacity : %ld\n",
           a->data,
           a->size,
           a->capacity);
    int_vector_free(a);
    int_vector_free(b);
}
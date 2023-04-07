#include "IntVector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

IntVector*
int_vector_new(size_t initial_capacity) // Создает массив нулевого размера.
{   
    IntVector* temp = malloc(sizeof(IntVector));
    if (!temp) {
        return NULL;
    }
    temp->data = malloc(sizeof(int) * initial_capacity);
    temp->size = 0;
    temp->capacity = initial_capacity;
    if (!temp->data) {
        free(temp);
        return NULL;
    }
    return temp;
}

IntVector*
int_vector_copy(const IntVector* v) // Указатель на копию вектора v. NULL, если
                                    // не удалось выделить память.
{
    IntVector* temp = malloc(sizeof(IntVector));
    if (!temp) {
        return NULL;
    }
    temp->data = malloc(sizeof(int) * v->capacity);
    if (!temp->data) {
        free(temp);
        return NULL;
    }
    memcpy(temp->data, v->data, sizeof(int) * v->capacity);
    temp->size = v->size;
    temp->capacity = v->capacity;
    return temp;
}

void int_vector_free(
        IntVector* v) // Освобождает память, выделенную для вектора v.
{
    free(v->data);
    free(v);
}

int int_vector_get_item(
        const IntVector* v,
        size_t index) // элемент под номером index. В случае выхода за границы
                      // массива поведение не определено.
{
    return v->data[index];
}

void int_vector_set_item(
        IntVector* v,
        size_t index,
        int item) // Присваивает элементу под номером index значение item. В
                  // случае выхода за границы массива поведение не определено.
{
    v->data[index] = item;
}

size_t int_vector_get_size(const IntVector* v) // размер вектора.
{
    return v->size;
}

size_t int_vector_get_capacity(const IntVector* v) // емкость вектора.
{
    return v->capacity;
}

int int_vector_push_back(
        IntVector* v,
        int item) // Добавляет элемент в конец массива. При необходимости
                  // увеличивает емкость массива. Для простоты в качестве
                  // коэффициента роста можно использовать 2.
{
    if (v->size < v->capacity) {
        v->data[v->size] = item;
        v->size++;
    } else {
        if(!(v->capacity)){
            v->capacity = 1;
        }
        int* temp = realloc(v->data, sizeof(int) * v->capacity * 2);
        if (!temp) {
            return -1;
        }
        v->capacity *= 2;
        v->data = temp;
        v->data[v->size] = item;
        v->size++;
    }
    return 0;
}

void int_vector_pop_back(
        IntVector* v) // Удаляет последний элемент из массива. Нет эффекта, если
                      // размер массива равен 0.
{
    if (v->size != 0) {
        v->size--;
    }
}

int int_vector_shrink_to_fit(
        IntVector* v) // Уменьшает емкость массива до его размера. 0 в случае
                      // успешного изменения емкости, -1 в случае ошибки.
{
    if (v->size < v->capacity) {
        v->capacity = v->size;
        int* temp = realloc(v->data, sizeof(int) * v->size);
        if (!temp) {
            return -1;
        }
        v->data = temp;
        return 0;
    }
    return -1;
}

int int_vector_resize(
        IntVector* v,
        size_t new_size) // Изменяет размер массива.Если новый размер массива
                         // больше исходного, то добавленные элементы
                         // заполняются нулями.Если новый размер массива меньше
                         // исходного, то перевыделение памяти не происходит.
// Для уменьшения емкости массива в этом случае следует использовать функцию
// int_vector_shrink_to_fit. 0 в случае успеха, -1 в случае ошибки. Если не
// удалось изменить размер, массив остается в исходном состоянии.
{
    if (v->size < new_size) {
        int* temp = realloc(v->data, sizeof(int) * new_size);
        if (!temp) {
            return -1;
        }
        v->data = temp;
        int_vector_reserve(v, new_size);
        for (int i = v->size; i < new_size; ++i) {
            v->data[i] = 0;
        }
    }
    v->size = new_size;
    int_vector_shrink_to_fit(v);
    return 0;
}

int int_vector_reserve(
        IntVector* v,
        size_t new_capacity) // Изменить емкость массива.Нет эффекта, если новая
                             // емкость меньше либо равна исходной.Нет эффекта,
                             // если новая емкость меньше либо равна исходной.
{
    if (v->capacity < new_capacity) {
        v->capacity = new_capacity;
        int* temp = realloc(v->data, sizeof(int) * new_capacity);
        if (!temp) {
            return -1;
        }
        v->data = temp;
        return 0;
    }
    return -1;
}
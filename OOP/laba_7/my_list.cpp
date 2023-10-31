#include "my_list.h"

int list::size()
{
    return count;
}

list::list(int _key, std::string _value)
{
    node = list_create(_key, _value);
    begin = node;
    end = node;
    count++;
}

list::list()
{
    node = list_create(rand() % 100, "rand");
    begin = node;
    end = node;
    count++;
}

void list::add_begin(int _key, std::string _value)
{
    struct Node* nodee = list_create(_key, _value);
    node = begin;
    nodee->prev = node;
    if (node != nullptr) {
        node->next = nodee;
    }
    if (end == nullptr) {
        end = nodee;
    }
    begin = nodee;
    node = nodee;
    count++;
}

void list::add_end(int _key, std::string _value)
{
    struct Node* nodee = list_create(_key, _value);
    node = end;
    nodee->next = node;
    if (node != nullptr) {
        node->prev = nodee;
    }
    if (begin == nullptr) {
        begin = nodee;
    }
    end = nodee;
    node = nodee;
    count++;
}

void list::lookup(int _key)
{
    struct Node* nodee = begin;
    for (int i = 0; i < count; ++i) {
        if (nodee->key == _key) {
            std::cout << nodee->value << "\n";
            return;
        }
        nodee = nodee->prev;
    }
    throw "Нет такого ключа";
    // std::cout << "Нет такого ключа" << "\n";
}

void list::lookup(std::string _value)
{
    struct Node* nodee = begin;
    for (int i = 0; i < count; ++i) {
        if (nodee->value == _value) {
            std::cout << nodee->key << "\n";
            return;
        }
        nodee = nodee->prev;
    }
    throw "Нет такого ключа";
    // std::cout << "Нет такого значения" << "\n";
}

void list::free_list()
{
    struct Node* nodee = end;
    for (int i = 0; i < count; ++i) {
        struct Node* nodee = end;
        end = end->next;
        delete nodee;
    }
    count = 0;
}

void list::delete_node(int _key)
{
    struct Node* nodee = begin;
    for (int i = 0; i < count; ++i) {
        if (_key == nodee->key) {
            if (nodee->next == nullptr && nodee->prev == nullptr) {
                begin = nullptr;
                end = nullptr;
                delete nodee;
                count--;
                return;
            } else if (nodee->next == nullptr) {
                nodee->prev->next = nullptr;
                begin = nodee->prev;
                delete nodee;
                count--;
                return;
            } else if (nodee->prev == nullptr) {
                nodee->next->prev = nullptr;
                end = nodee->next;
                delete nodee;
                count--;
                return;
            } else {
                nodee->next->prev = nodee->prev;
                nodee->prev->next = nodee->next;
                delete nodee;
                count--;
                return;
            }
        } else {
            nodee = nodee->prev;
        }
    }
    throw "Нет такого ключа";
    // std::cout << "Такого ключа нет\n";
}

void list::delete_node(std::string _value)
{
    struct Node* nodee = begin;
    for (int i = 0; i < count; ++i) {
        if (_value == nodee->value) {
            if (nodee->next == nullptr && nodee->prev == nullptr) {
                begin = nullptr;
                end = nullptr;
                delete nodee;
                count--;
                return;
            } else if (nodee->next == nullptr) {
                nodee->prev->next = nullptr;
                begin = nodee->prev;
                delete nodee;
                count--;
                return;
            } else if (nodee->prev == nullptr) {
                nodee->next->prev = nullptr;
                end = nodee->next;
                delete nodee;
                count--;
                return;
            } else {
                nodee->next->prev = nodee->prev;
                nodee->prev->next = nodee->next;
                delete nodee;
                count--;
                return;
            }
        } else {
            nodee = nodee->prev;
        }
    }
    throw "Нет такого ключа";
    // std::cout << "Такого значения нет\n";
}

void list::print()
{
    struct Node* nodee = begin;
    for (int i = 0; i < count; ++i) {
        std::cout << nodee->key << " " << nodee->value << "\n";
        nodee = nodee->prev;
    }
    std::cout << "\n";
}

/*
stack::stack(int _key, std::string _value) : list(_key, _value)
{
}

stack::stack() : list()
{
}
*/

void stack::add(int _key, std::string _value)
{
    add_end(_key, _value);
}

void stack::print()
{
    list::print();
}

void stack::delete_node()
{
    struct Node* nodee = end;
    if (!nodee) {
        throw "Нечего удалять";
    }
    if (nodee->next == nullptr && nodee->prev == nullptr) {
        begin = nullptr;
        end = nullptr;
        delete nodee;
        count--;
    } else {
        nodee->next->prev = nullptr;
        end = nodee->next;
        delete nodee;
        count--;
    }
}

/*
queue::queue(int _key, std::string _value) : list(_key, _value)
{
}

queue::queue() : list()
{
}
*/

void queue::add(int _key, std::string _value)
{
    add_end(_key, _value);
}

void queue::print()
{
    list::print();
}

void queue::delete_node()
{
    struct Node* nodee = begin;
    if (!nodee) {
        throw "Нечего удалять";
    }
    if (nodee->next == nullptr && nodee->prev == nullptr) {
        begin = nullptr;
        end = nullptr;
        delete nodee;
        count--;
    } else {
        nodee->prev->next = nullptr;
        begin = nodee->prev;
        delete nodee;
        count--;
    }
}
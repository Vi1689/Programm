#pragma once

#include <iostream>
#include <string>

class list {
protected:
    struct Node {
        int key;
        std::string value;
        struct Node* next;
        struct Node* prev;
    };
    struct Node* node;
    int count = 0;
    struct Node* begin;
    struct Node* end;

public:
    list(int _key, std::string _value);

    list();

    void add_begin(int _key, std::string _value);

    void add_end(int _key, std::string _value);

    void lookup(int _key);

    void lookup(std::string _value);

    void delete_node(int _key);

    void delete_node(std::string _value);

    void print();

    int size();

    ~list()
    {
        free_list();
    }

private:
    struct Node* list_create(int _key, std::string _value)
    {
        // struct Node* nodee = (Node*)malloc(sizeof(Node));
        struct Node* nodee = new Node;
        nodee->key = _key;
        nodee->value = _value;
        nodee->next = nullptr;
        nodee->prev = nullptr;
        return nodee;
    }
    void free_list();
};

class stack : public list {
public:
    stack(int _key, std::string _value) : list(_key, _value)
    {
    }

    stack() : list()
    {
    }

    void add(int _key, std::string _value);

    void print();

    void delete_node();
};

class queue : public list {
public:
    queue(int _key, std::string _value) : list(_key, _value)
    {
    }

    queue() : list()
    {
    }

    void add(int _key, std::string _value);

    void print();

    void delete_node();
};
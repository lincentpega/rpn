#ifndef ALGORITHMS_LAB_3_STACK_H
#define ALGORITHMS_LAB_3_STACK_H

#include "binary_number.h"

struct NodeStack
{
    BinaryNumber m_item;
    NodeStack* m_next;
};


class Stack
{
private:
    NodeStack* m_top;

public:
    Stack() : m_top(nullptr) {}
    ~Stack() {
        empty();
    }
    void push(BinaryNumber);
    int size();
    void empty();
    BinaryNumber pop();

};

#endif //ALGORITHMS_LAB_3_STACK_H

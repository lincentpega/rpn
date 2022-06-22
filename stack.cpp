#include "stack.h"

#include <iostream>
#include <new>


void Stack::push(BinaryNumber item) {
    NodeStack* p;

    try {
        p = new NodeStack;
    }
    catch(std::bad_alloc &e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
    p->m_item = item;
    p->m_next = m_top;

    m_top = p;
}

int Stack::size() {
    if (m_top == nullptr)
        return 0;
    else
    {
        NodeStack* p = m_top;
        int count = 0;

        while (p != nullptr)
        {
            count++;
            p = p->m_next;
        }
    }
}

void Stack::empty() {
    NodeStack* p;
    NodeStack* p2;

    p = m_top;

    while (p != nullptr)
    {
        p2 = p; // сделать копию из p
        p = p->m_next; // перейти на следующий элемент стека
        delete p2; // удалить память, выделенную для предыдущего элемента
    }
    m_top = nullptr; // поправить вершину стека
}

BinaryNumber Stack::pop() {
    // проверка, пуст ли стек?
    if (m_top == nullptr)
        std::cerr << "Zero size of stack" << std::endl;

    NodeStack* p2; // дополнительный указатель
    BinaryNumber item;
    item = m_top->m_item;

    // перенаправить указатели m_top, p2
    p2 = m_top;
    m_top = m_top->m_next;

    // Освободить память, выделенную под 1-й элемент
    delete p2;

    // вернуть item
    return item;
}

#ifndef DS_STACK_H
#define DS_STACK_H

#include <iostream>
#include <typeinfo>
#include "../global/status.h"

using namespace std;

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

template <typename ElemType>
class Stack
{
private:
    int size_;
    ElemType *base;
    ElemType *top;

public:
    Stack();

    ~Stack();

    Status Clear();

    Status Empty();

    int Length();

    Status GetTop(ElemType &);

    Status Push(ElemType);

    Status Pop(ElemType &);

    Status Traverse(Status (*visit)(ElemType));
};

#endif
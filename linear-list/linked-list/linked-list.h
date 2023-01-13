#ifndef DS_LINEAR_LIST_LINKED_LIST_H
#define DS_LINEAR_LIST_LINKED_LIST_H

#include <iostream>
#include "../../global/status.h"
using namespace std;

typedef int ElemType;

struct LNode
{
    ElemType data;
    LNode *prior;
    LNode *next;
};

class LinkedList
{
private:
    int length_;  // 链表当前的长度
    int size_;    // 当前为链表分配的存储空间
    LNode *dummy; // 头结点的作用是使所有链表（包括空表）的头指针非空，并使对单链表的插入、删除操作不需要区分是否为空表或是否在第一个位置进行，从而与其他位置的插入、删除操作一致

public:
    LinkedList();
    ~LinkedList();
    void Clear();
    bool Empty();
    int Length();
    Status GetElem(int, ElemType &);
    int LocateElem(ElemType, Status (*compare)(ElemType, ElemType));
    Status PriorElem(ElemType, ElemType &);
    Status NextElem(ElemType, ElemType &);
    Status Insert(int, ElemType);
    Status Delete(int, ElemType &);
    Status Traverse(Status (*visit)(ElemType));
};

#endif
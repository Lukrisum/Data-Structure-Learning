#ifndef DS_LINEAR_LIST_SQ_LIST_H
#define DS_LINEAR_LIST_SQ_LIST_H

#include <iostream>
#include "../../global/status.h"
using namespace std;

typedef int ElemType;
#define LIST_INIT_SIZE 100 // 线性表存储空间的初始分配量
#define LIST_INCREMENT 10  // 线性表存储空间的分配增量

class SqList
{
private:
    int length_; // 顺序表当前的长度
    int size_;   // 当前为顺序表分配的存储容量

public:
    ElemType *elem;
    SqList();
    ~SqList();
    void Clear();
    bool Empty();
    int Length();
    Status GetElem(int, ElemType);
    int LocateElem(ElemType, Status (*compare)(ElemType, ElemType));
    Status PriorElem(ElemType, ElemType &);
    Status NextElem(ElemType, ElemType &);
    Status Insert(int, ElemType);
    Status Delete(int, ElemType&);
    Status Traverse(Status (*visit)(ElemType));
};

#endif
#include <iostream>
#include "../../global/status.h"
#include "./sq-list.h"
#include <vector>
using namespace std;

SqList::SqList()
{
    elem = new (std::nothrow) int[LIST_INIT_SIZE];
    if (!elem)
    {
        exit(OVERFLOW);
    }
    length_ = 0;
    size_ = LIST_INIT_SIZE;
}

SqList::~SqList()
{
    if (elem)
    {
        delete[] elem;
    }
}

void SqList::Clear()
{
    length_ = 0;
}

bool SqList::Empty()
{
    return length_ == 0;
}

int SqList::Length()
{
    return length_;
}

Status SqList::GetElem(int i, ElemType e)
{
    if (i < 1 || i > length_)
    {
        return ERROR;
    }
    e = elem[i - 1];
    return OK;
}

int SqList::LocateElem(ElemType e, Status (*compare)(ElemType, ElemType))
{
    for (int i = 0; i < length_ - 1; i++)
    {
        if (compare(elem[i], e))
        {
            return i + 1;
        }
    }
    return 0;
}

Status SqList::PriorElem(ElemType cur_e, ElemType &pre_e)
{
    int i = LocateElem(cur_e, [](ElemType a, ElemType b)
                       { return a == b ? TRUE : FALSE; });
    if (!i || i == 1)
    {
        return ERROR;
    }
    pre_e = elem[i - 1];
    return OK;
}

Status SqList::NextElem(ElemType cur_e, ElemType &next_e)
{
    int i = LocateElem(cur_e, [](ElemType a, ElemType b)
                       { return a == b ? TRUE : FALSE; });
    if (!i || i == length_)
    {
        return ERROR;
    }
    next_e = elem[i + 1];
    return OK;
}

Status SqList::Insert(int i, ElemType e)
{
    if (i < 1 || i > length_ + 1)
    {
        return ERROR;
    }

    if (length_ >= size_)
    {
        ElemType *old_data = elem;
        elem = new (std::nothrow) int[size_ + LIST_INCREMENT];
        if (!old_data)
        {
            exit(OVERFLOW);
        }
        for (int i = 0; i < length_; i++)
        {
            elem[i] = old_data[i];
        }
        size_ += LIST_INCREMENT;
        delete[] old_data;
    }
    ElemType *q = &elem[i - 1];
    for (ElemType *p = &elem[length_ - 1]; p >= q; p--)
    {
        *(p + 1) = *p;
    }
    *q = e;
    length_++;
    return OK;
}

Status SqList::Delete(int i, ElemType &e)
{
    if (i < 1 || i > length_)
    {
        return ERROR;
    }
    ElemType *p = &elem[i - 1];
    e = *p;
    ElemType *q = elem + length_ - 1;
    for (p++; p <= q; p++)
    {
        *(p - 1) = *p;
    }
    length_--;
    return OK;
}

Status SqList::Traverse(Status (*visit)(ElemType))
{
    for (int i = 0; i < length_; i++)
    {
        Status code = visit(elem[i]);
        if (code != OK)
        {
            return code;
        }
    }
    return OK;
}

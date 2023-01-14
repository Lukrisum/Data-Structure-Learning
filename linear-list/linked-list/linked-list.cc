#include <iostream>
#include "../../global/status.h"
#include "./linked-list.h"

using namespace std;

LinkedList::LinkedList() {
    dummy = new(std::nothrow) LNode;
    if (!dummy) {
        exit(OVERFLOW);
    }
    dummy->prior = NULL;
    dummy->next = NULL;
    length_ = 0;
    size_ = 0;
};

LinkedList::~LinkedList() {
    // deleting null pointer has no effect
    delete dummy;
};

void LinkedList::Clear() {
    length_ = 0;
};

bool LinkedList::Empty() {
    return length_ == 0;
};

int LinkedList::Length() {
    return length_;
};

Status LinkedList::GetElem(int i, ElemType &e) {
    if (i < 1 || i > length_) {
        return ERROR;
    }
    LNode *cur = dummy->next;
    while (--i > 0) {
        cur = cur->next;
    }
    e = cur->data;
    return OK;
};

int LinkedList::LocateElem(ElemType e, Status (*compare)(ElemType, ElemType)) {
    LNode *cur = dummy->next;
    int i = 1;
    while (cur != NULL) {
        if (compare(cur->data, e)) {
            return i;
        }
        cur = cur->next;
        i++;
    }
    return 0;
};

Status LinkedList::PriorElem(ElemType e, ElemType &pre_e) {
    int i = LocateElem(e, [](ElemType a, ElemType b) { return a == b ? TRUE : FALSE; });
    if (!i || i == 1) {
        return ERROR;
    }
    GetElem(i - 1, pre_e);
    return OK;
};

Status LinkedList::NextElem(ElemType e, ElemType &next_e) {
    int i = LocateElem(e, [](ElemType a, ElemType b) { return a == b ? TRUE : FALSE; });
    if (!i || i == length_ - 1) {
        return ERROR;
    }
    GetElem(i + 1, next_e);
    return OK;
};

Status LinkedList::Insert(int i, ElemType e) {
    if (i < 1 || i > length_ + 1) {
        return ERROR;
    }
    LNode *cur = dummy;
    while (--i > 0) {
        cur = cur->next;
    }
    LNode *new_node = new LNode();
    new_node->data = e;
    new_node->next = cur->next;
    new_node->prior = cur;
    cur->next = new_node;
    if (cur->next)
        cur->next->prior = new_node;
    length_++;
    return OK;
};

Status LinkedList::Delete(int i, ElemType &e) {
    if (i < 1 || i > length_) {
        return ERROR;
    }
    LNode *cur = dummy;
    while (--i > 0) {
        cur = cur->next;
    }
    cur->next = cur->next->next;
    e = cur->data;
    length_--;
    return OK;
};

Status LinkedList::Traverse(Status (*visit)(ElemType)) {
    LNode *cur = dummy->next;
    while (cur != NULL) {
        Status code = visit(cur->data);
        if (code != OK) {
            return code;
        }
        cur = cur->next;
    }
    return OK;
};

int main() {
    LinkedList l;
    l.Insert(1, 1);
    l.Insert(2, 2);
    l.Insert(3, 3);
    l.Insert(4, 4);
    cout << l.LocateElem(4, [](ElemType a, ElemType b) { return a == b ? TRUE : FALSE; });
}

#include <iostream>
#include "./stack.h"
#include <bits/stdc++.h>
using namespace std;

template <typename ElemType>
Stack<ElemType>::Stack()
{
    base = new (std::nothrow) ElemType[STACK_INIT_SIZE];
    if (!base)
        exit(OVERFLOW);
    top = base;
    size_ = STACK_INIT_SIZE;
};

template <typename ElemType>
Stack<ElemType>::~Stack()
{
    // deleting null pointer has no effect
    delete[] base;
};

//
template <typename ElemType>
Status Stack<ElemType>::Clear()
{
    top = base;
    return OK;
};

template <typename ElemType>
Status Stack<ElemType>::Empty()
{
    return top - base == 0 ? TRUE : FALSE;
};

//
template <typename ElemType>
int Stack<ElemType>::Length()
{
    return top - base;
};

template <typename ElemType>
Status Stack<ElemType>::GetTop(ElemType &e)
{
    if (top == base)
        return ERROR;
    e = *top;
    return OK;
};

template <typename ElemType>
Status Stack<ElemType>::Push(ElemType e)
{
    if (top - base >= size_)
    {
        ElemType *old_base = base;
        base = new (std::nothrow) ElemType[size_ + STACK_INCREMENT];
        if (!base)
        {
            exit(OVERFLOW);
        }
        top = base + size_;
        size_ += STACK_INCREMENT;
        delete[] old_base;
    }
    *top++ = e;
    return OK;
};

template <typename ElemType>
Status Stack<ElemType>::Pop(ElemType &e)
{
    if (top == base)
        return ERROR;
    e = *--top;
    return OK;
};

template <typename ElemType>
Status Stack<ElemType>::Traverse(Status (*visit)(ElemType))
{
    for (ElemType *p = base; p <= top; ++p)
    {
        Status code = visit(*p);
        if (code != OK)
            return code;
    }
    return OK;
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

int i = 0;
int len = 0;

TreeNode *buildT(char a[])
{
    if (a[i] == '#')
    {
        i++;
        return NULL;
    }
    TreeNode *root = new TreeNode();
    root->val = a[i++] - '0';
    root->left = buildT(a);
    root->right = buildT(a);
    return root;
}

//     1
//   2     _
//  3  4
// _ _   5

void prior(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    cout << root->val << " ";
    prior(root->left);
    prior(root->right);
}

main()
{
    TreeNode *root = new TreeNode();
    char a[] = {'1', '2', '3', '#', '#', '4', '#', '#', '5', '#', '#'};
    len = 7;
    root = buildT(a);
    cout << endl;
    Stack<TreeNode *> s;
    prior(root);
    cout << endl;
    while (root != NULL || !s.Empty())
    {
        while (root != NULL)
        {
            cout << root->val << " ";
            s.Push(root);
            root = root->left;
        }
        if (!s.Empty())
        {
            s.Pop(root);
            root = root->right;
        }
    }
}

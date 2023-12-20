#include "node.h"
#include <iostream>
#include <cassert>

std::size_t list_length(const node * headptr)
{
    std::size_t ans = 0;
    for (auto p = headptr; p != nullptr; p = p->link())
        ++ans;

    return ans;
}

void list_clear(node * & headptr)
{
    while (headptr != nullptr)
    {
        node * temp = headptr;
        headptr = headptr->link();
        delete temp;
    }
}

void list_head_insert(node * & headptr, const node::value_type & entry)
{
    headptr = new node(entry, headptr);
}

void list_print(const node * headptr)
{
    for (const node * p = headptr; p != nullptr; p = p->link())
        std::cout << p->data() << " ";
    std::cout << std::endl;
}

void list_head_remove(node * & headptr)
{
    node * temp = headptr;
    headptr = headptr->link();
    delete temp;
}

node * list_search(node * headptr, const node::value_type & target)
{
    node * p;
    for (p = headptr; p != nullptr && p->data() != target; p = p->link())
        ;
    return p;

}

const node * list_search(const node * headptr, const node::value_type & target)
{
    const node * p;
    for (p = headptr; p != nullptr && p->data() != target; p = p->link())
        ;
    return p;

}

node * list_locate(node * headptr, std::size_t pos)
{
    assert(pos > 0);

    node * p;
    std::size_t i(0);

    for (p = headptr; p != nullptr && (++i < pos); p = p->link() )
        ;
    return p;
}

const node * list_locate(const node * headptr, std::size_t pos)
{
    assert(pos > 0);

    const node * p;
    std::size_t i(0);

    for (p = headptr; p != nullptr && (++i < pos); p = p->link() )
        ;
    return p;
}

void list_insert(node *prevptr, const node::value_type & entry)
{
    assert(prevptr != nullptr);

    prevptr->set_link(new node (entry, prevptr->link()));

}

void list_remove(node *prevptr)
{
    assert(prevptr != nullptr && prevptr->link() != nullptr);

    node * temp = prevptr->link();

    prevptr->set_link(temp->link());

    delete temp;
}

void list_copy(const node * sourceptr, node * & headptr, node * & tailptr)
{
    headptr = tailptr = nullptr;

    // source list is empty
    if (sourceptr == nullptr)
        return;

    // copy first node to copy list
    list_head_insert(headptr, sourceptr->data());
    tailptr = headptr;

    for (const node * p = sourceptr->link(); p != nullptr; p = p->link())
    {
        list_insert(tailptr, p->data());
        tailptr = tailptr->link();
    }
}

void list_reverse(node * &head_ptr) {
    int i=0;
    node * p = head_ptr;
    while (p != nullptr) {
        node * temp = p->link();
        if (i==0) {
            p->set_link(nullptr);
        }
        else {
            p->set_link(head_ptr);
            head_ptr = p;
        }
        p = temp;
        ++i;
    }
}

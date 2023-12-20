#ifndef NODE_H
#define NODE_H
#include <cstdlib>


class node
{
public:

    // TYPEDEFS and CONSTANTS
    typedef int value_type;

    // CONSTRUCTOR & DESTRUCTOR
    node(const value_type & init_data = value_type(),
         node * init_link = nullptr)
    {
        _data = init_data;
        _link = init_link;
    }

    // MEMBER FUNCTIONS

    // pre: none
    // post: returns a COPY of the value stored in _data
    value_type data() const
    {
        return _data;
    }

    // pre: none
    // post: returns the (const) pointer stored in _link
    const node * link() const
    {
        return _link;
    }
    node * link()
    {
        return _link;
    }

    // pre: none
    // post: stores a copy of new_data in _data
    void set_data(const value_type & new_data)
    {
        _data = new_data;
    }


    // pre: none
    // post: stores new_link in _link
    void set_link(node * new_link)
    {
        _link = new_link;
    }



private:
    value_type _data;
    node *     _link;
    // CLASS INVARIANTS:
    //  _data stores a value of value_type
    //  _link stores a pointer to the next node in a linked list
};

// TOOLKIT FUNCTIONS TO MANIPULATE LINKED LISTS

// NOTE: these are nonmember functions, i.e. NOT parts of the class NODE

// pre: headptr is the address of the first node in a linked list
// post: returns the length of that linked list
std::size_t list_length(const node * headptr);

// pre: headptr is the address of a the first node of a linked list
// post: every node on this linked list has been returned to the heap
//       & headptr is set to nullptr
void list_clear(node * & headptr);


// pre: headptr points to the head of a linked list
// post: a new node with value entry has been inserted at the head of the list
//       headptr now points to the newly created node
void list_head_insert(node * & headptr, const node::value_type & entry);

// pre: headptr points to the head of a linked list
// post: values stored in this linked list have been outputted in order
void list_print(const node * headptr);

// pre: headptr points to the head of a linked list
// post: the first node has been returned to the heap
//       headptr is now the address of the next node in the list or nullptr if
//       there is no next node
void list_head_remove(node * & headptr);

// pre: headptr points to the head of a linked list
// post: returns a pointer to the first node on this linked list containing target
//       or nullptr if target is not on this list
node * list_search(node * headptr, const node::value_type & target);
const node * list_search(const node * headptr, const node::value_type & target);

// pre: headptr points to the head of a linked list
//      pos > 0 (first node is at position 1)
// post: returns pointer to the node at position pos or nullptr if no node at that
//       position

node * list_locate(node * headptr, std::size_t pos);
const node * list_locate(const node * headptr, std::size_t pos);

// pre: prevptr points to a node in a linked list (i.e, prevptr != nullptr)
// post: a new node has been inserted AFTER the node that prevptr points to


void list_insert(node * prevptr, const node::value_type & entry);

// pre: prevprtr points a node in a linked list (i.e., prevptr != nullptr)
//      AND this node is NOT the last node in the list
// post: removes the node following the node prevptr points to
void list_remove(node * prevptr);

// pre: source_ptr points to the head of a linked list
// post: a copy of the linked list has been created; headptr points to the first node
//       in the copy; tailptr points to the last node in the copy
void list_copy(const node * source_ptr, node * & headptr, node * & tailptr);

void list_reverse(node * &head_ptr);

#endif // NODE_H

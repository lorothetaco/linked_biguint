#include "BIGUINT.h"
#include "node.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include <string>
#include <cstring>

// CONSTRUCTORS & DESTRUCTORS
BIGUINT::BIGUINT(std::size_t n) {
    // getting the number of digits in n
    int size;
    if (n == 0) {
        size = 1;
    } else {
        size = log10(n) + 1;
    }

    _data = new node(n % 10, nullptr);
    n /= 10;
    int i = 1;
    for (node * p = _data; i < size; p = p->link(), ++i) {
        list_insert(p, n % 10);
        n /= 10;
    }
}

BIGUINT::BIGUINT (const std::string & s) {
    _data = new node(0);
    int num = 0;
    for(char c: s) {
        num = c - '0';
        list_insert(_data, num);
    }
    list_head_remove(_data);
}

BIGUINT::BIGUINT(const BIGUINT & b) {
    _data = nullptr;
    int size = list_length(b._data);

    node * p;
    std::size_t i(0);
    for (p = _data; p != nullptr && (++i < size); p = p->link())
        ;
    list_copy(b._data, _data, p);
}

BIGUINT::~BIGUINT() {
    list_clear(_data);
}

// CONSTANT FUNCTIONS
BIGUINT::digit_type BIGUINT::operator [] (size_type pos) const {
    // making a temporary linked list
    node * temp_head;
    node * temp_tail;
    std::size_t i(0);
    for (temp_tail = _data; temp_tail != nullptr && (++i < list_length(_data)); temp_tail = temp_tail->link())
        ;
    list_copy(_data, temp_head, temp_tail);

    // reversing the temporary linked list so I have the least significant digit at the right
    list_reverse(temp_head);

    // locating the pos thingy
    const node * p = list_locate(temp_head, pos+1);
    return p->data();
}

BIGUINT::size_type BIGUINT::size() const {
    return list_length(_data);
}

int BIGUINT::compare(const BIGUINT & n) const {
    if (size() < n.size())
        return -1;
    else if (size() > n.size())
        return 1;
    else {
        node * temp_head;
        node * temp_tail;
        std::size_t i(0);
        for (temp_tail = _data; temp_tail != nullptr && (++i < list_length(_data)); temp_tail = temp_tail->link())
            ;
        list_copy(_data, temp_head, temp_tail);
        list_reverse(temp_head);

        node * n_head;
        node * n_tail;
        std::size_t j(0);
        for (n_tail = _data; n_tail != nullptr && (++j < list_length(n._data)); n_tail = n_tail->link())
            ;
        list_copy(n._data, n_head, n_tail);
        list_reverse(n_head);

        node * q = n_head;
        for (node * p = temp_head; p != nullptr; p = p->link()) {
            if (p->data() > q->data())
                return 1;
            else if (p->data() < q->data())
                return -1;
            q = q->link();
        }
        return 0;
    }
}

// MODIFICATION FUNCTIONS
void BIGUINT::operator = (const BIGUINT & source) {
    int size = list_length(source._data);
    list_clear(_data);
    _data = new node[size];

    node * p;
    std::size_t i(0);
    for (p = _data; p != nullptr && (++i < size); p = p->link())
        ;
    list_copy(source._data, _data, p);
}

void BIGUINT::ls (size_type n) {
    if (n == 0) {
        return;
    }
    else {
        for (int i=0; i<n; ++i) {
            list_head_insert(_data, 0);
        }
    }
}

void BIGUINT::rs (size_type n) {
    if (n == 0) {
        return;
    }
    else if (n >= list_length(_data)) {
        list_clear(_data);
        list_head_insert(_data, 0);
    }
    else {
        for (int i=0; i<n; ++i) {
            list_head_remove(_data);
        }
    }
}

// ARITHMETIC MEMBER OPERATORS
void BIGUINT::operator += (const BIGUINT & b) {
    if (b == 0) {
        return;
    }
    // determining the max size of the linked list we're working with
    // whichever linked list is bigger, + 1
    int size = 0;
    if (list_length(_data) >= list_length(b._data))
        size = list_length(_data) + 1;
    else
        size = list_length(b._data) + 1;

    // padding both linked lists with 0's - larger one gets one, smaller one gets enough to match larger one
    int data_size = 0;
    node * p;
    for (p = _data; data_size < list_length(_data)-1; p = p->link(), ++data_size)
        ;
    for (int i=list_length(_data); i<size; ++i, p = p->link())
        list_insert(p, 0);

    BIGUINT temp_b(b);
    int b_size = 0;
    node * q;
    for (q = temp_b._data; b_size < list_length(temp_b._data)-1; q = q->link(), ++b_size)
        ;
    for (int i=list_length(temp_b._data); i<size; ++i, q = q->link())
        list_insert(q, 0);

    // making a temp linked list to hold the sum
    BIGUINT temp(0);
    for (int i=1; i<size; ++i) {
        list_insert(temp._data, 0);
    }

    // performing the addition
    // x is an arbitrary variable to help keep track of how long the linked lists are
    int x = 0;
    int carryover = 0;
    for (node * D = _data, * B = temp_b._data, * T = temp._data; x < size; ++x, D = D->link(), B = B->link(), T = T->link()) {
        T->set_data(D->data() + B->data() + carryover);
        if (T->data() > 9) {
            carryover = 1;
            T->set_data(T->data() - 10);
        }
        else {
            carryover = 0;
        }
    }

    // putting the sum in *this
    *this = temp;

    // removing any extra padded 0's
    list_reverse(_data);
    node * DD = _data;
    while (DD->data() == 0) {
        list_head_remove(_data);
        DD = _data;
    }
    list_reverse(_data);

    // removing any extra padded 0's
    list_reverse(temp_b._data);
    node * BB = temp_b._data;
    while (BB->data() == 0) {
        list_head_remove(temp_b._data);
        BB = temp_b._data;
    }
    list_reverse(temp_b._data);
}

void BIGUINT::operator -= (const BIGUINT & b) {
    // if b is greater than or equal to *this, automatically becomes 0
    if (compare(b) <= 0) {
        *this = 0;
        return;
    }

    if (b == 0)
        return;

    // padding b with 0's if necessary (size guaranteed to be less than or equal to *this)    
    BIGUINT temp_b(b);
    int b_size = 0;
    node * q;
    for (q = temp_b._data; b_size < list_length(temp_b._data)-1; q = q->link(), ++b_size)
        ;
    for (int i=list_length(temp_b._data); i<list_length(_data); ++i, q = q->link())
        list_insert(q, 0);

    // performing the subtraction
    size_type borrow(0);
    for (node * D = _data, * B = temp_b._data; D != nullptr; D = D->link(), B = B->link()) {
        size_type t = borrow;
        if (D != nullptr)
            t += B->data();

        if (D->data() >= t) {
            D->set_data((D->data())-t);
            borrow = 0;
        }
        else {
            D->set_data((D->data())+10-t);
            borrow = 1;
        }
    }

    // removing any extra padded 0's
    list_reverse(_data);
    node * DD = _data;
    while (DD->data() == 0) {
        list_head_remove(_data);
        DD = _data;
    }
    list_reverse(_data);
}

void BIGUINT::operator *= (digit_type d) {
    assert (d <= 9 && d >= 0);

    // anything * 0 = 0, anything * 1 = itself
    if (d == 0) {
        *this = 0;
        return;
    }
    if (d == 1) {
        return;
    }

    // padding *this with 1 zero
    list_reverse(_data);
    list_head_insert(_data, 0);
    list_reverse(_data);

    // making a temporary linked list to store the product
    BIGUINT product(*this);

    // performing the multiplication
    size_type carry(0);
    for (node * D = _data, * P = product._data; D != nullptr; D = D->link(), P = P->link()) {
        size_type sum = carry + D->data() * d;
        P->set_data(sum % 10);
        carry = sum / 10;
    }

    // setting the product into *this
    list_clear(_data);
    *this = product;

    // removing any extra padded 0's
    list_reverse(_data);
    node * DD = _data;
    while (DD->data() == 0) {
        list_head_remove(_data);
        DD = _data;
    }
    list_reverse(_data);
}

void BIGUINT::operator *= (const BIGUINT & b) {
    // anything * 0 = 0
    BIGUINT zero(0);
    if (b == zero) {
        *this = 0;
        return;
    }
    // anything * 1 = itself
    BIGUINT one(1);
    if (b == one) {
        return;
    }

    // making a BIGUINT to store the answer
    // size is the two factor sizes combined
    int size = list_length(_data) + list_length(b._data);
    BIGUINT ans;
    for (int i=1; i<size; ++i)
        list_insert(ans._data, 0);

    // performing the multiplication
    // i is an int that keeps track of the place in _data
    // j is an int that keeps track of the place in b._data
    size_type carry(0);
    int i(0), j;
    for (node * D = _data; D != nullptr; D = D->link(), ++i) {
        node * B;
        carry = 0;
        j = 0;
        for (B = b._data; B != nullptr; B = B->link(), ++j) {
            size_type sum = carry + list_locate(ans._data, i+j+1)->data() + D->data() * B->data();
            list_locate(ans._data, i+j+1)->set_data(sum % 10);
            carry = sum / 10;
        }
        list_locate(ans._data, i+j+1)->set_data(carry);
    }

    // putting ans into *this
    list_clear(_data);
    *this = ans;

    // removing any extra padded 0's
    list_reverse(_data);
    node * DD = _data;
    while (DD->data() == 0) {
        list_head_remove(_data);
        DD = _data;
    }
    list_reverse(_data);
}

void BIGUINT::operator /= (const BIGUINT & b) {
    assert(b != 0);

    // if divisor is less than dividend, set quotient to 0
    if (compare(b) == -1) {
        *this = 0;
        return;
    }
    // if divisor is equal to dividend, set quotient to 1
    if (compare(b) == 0) {
        *this = 1;
        return;
    }

    BIGUINT low(0), high(*this), mid(0), quotient(0);

    while (low <= high) {
        // mid = (low + high) / 2
        mid = low + high;
        mid *= 5;
        mid.rs(1);

        if ((b * mid) <= *this) {
            quotient = mid;
            low = mid;
            ++low;
        }
        else {
            high = mid;
            --high;
        }
    }

    *this = quotient;
}

void BIGUINT::operator %= (const BIGUINT & b) {
    assert(b != 0);
    if (compare(b) == -1) {
        return;
    }
    if (compare(b) == 0) {
        *this = 0;
        return;
    }

    BIGUINT remainder(0), quotient(0);
    quotient = *this / b;
    remainder = *this - (quotient * b);
    *this = remainder;
}

BIGUINT BIGUINT::operator++() {
    *this += 1;
    return *this;
}
BIGUINT BIGUINT::operator--() {
    *this -= 1;
    return *this;
}

BIGUINT BIGUINT::operator++(int a) {
    BIGUINT temp(*this);
    *this += 1;
    return temp;
}
BIGUINT BIGUINT::operator--(int a) {
    BIGUINT temp(*this);
    *this -= 1;
    return temp;
}

// NONMEMBER INPUT/OUTPUT OPERATORS
std::ostream & operator << (std::ostream & os, const BIGUINT & b) {
    if (b == 0)
        os << 0;
    else {
        for (int i=0; i<=b.size()-1; ++i) {
            os << b[i];
        }
    }
    return os;
}
std::istream & operator >> (std::istream & is, BIGUINT & b) {
    std::string s;
    is >> s;
    b = BIGUINT(s);
    return is;
}

// NONMEMBER COMPARISON OPERATORS
bool operator < (const BIGUINT & a, const BIGUINT & b) {
    return (a.compare(b) == -1);
}
bool operator <= (const BIGUINT & a, const BIGUINT & b) {
    return (a.compare(b) <= 0);
}
bool operator == (const BIGUINT & a, const BIGUINT & b) {
    return (a.compare(b) == 0);
}
bool operator != (const BIGUINT & a, const BIGUINT & b) {
    return (a.compare(b) != 0);
}
bool operator >= (const BIGUINT & a, const BIGUINT & b) {
    return (a.compare(b) >= 0);
}
bool operator > (const BIGUINT & a, const BIGUINT & b) {
    return (a.compare(b) == 1);
}

// NONMEMBER SHIFT OPERATORS
BIGUINT operator << (const BIGUINT & a, unsigned int n) {
    BIGUINT ans(a);
    ans.ls(n);
    return ans;
}
BIGUINT operator >> (const BIGUINT & a, unsigned int n) {
    BIGUINT ans(a);
    ans.rs(n);
    return ans;
}

// NONMEMBER ARITHMETIC OPERATORS
BIGUINT operator + (const BIGUINT & a, const BIGUINT & b) {
    BIGUINT c = a;
    c += b;
    return c;
}
BIGUINT operator - (const BIGUINT & a, const BIGUINT & b) {
    BIGUINT c = a;
    c -= b;
    return c;
}
BIGUINT operator * (const BIGUINT & a, const BIGUINT & b) {
    BIGUINT c = a;
    c *= b;
    return c;
}
BIGUINT operator / (const BIGUINT & a, const BIGUINT & b) {
    BIGUINT c = a;
    c /= b;
    return c;
}
BIGUINT operator % (const BIGUINT & a, const BIGUINT & b) {
    BIGUINT c = a;
    c %= b;
    return c;
}

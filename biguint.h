#ifndef LINKED_BIGUINT_H
#define LINKED_BIGUINT_H

#include <cstdlib>
#include <string>
#include "node.h"

class BIGUINT
{
public:
    // TYPES and CONSTANTS
    typedef std::size_t size_type;
    typedef node::value_type digit_type;

    // CONSTRUCTORS & DESTRUCTOR

    // pre: none
    // post: creates a BIGUINT with inital value n (default value = 0)
    BIGUINT(std::size_t n = 0);

    // pre: s consists of decimal digits only
    // post: creates a BIGUINT whose digits are given in a string s
    //       rightmost digit of s corresponds to the least significant digit
    //       the capacity is the length of s
    BIGUINT (const std::string & s);

    // pre: none
    // post: creates a BIGUINT with the same value as b
    BIGUINT(const BIGUINT & b);

    // pre: none
    // post: returns dynamically allocated memory to the heap
    ~BIGUINT();

    // CONSTANT FUNCTIONS
    // pre: none
    // post: returns the (pos+1)^st digit from the right of this BIGUINT (most digits are 0)
    digit_type operator [](size_type pos) const;

    // pre: none
    // post: returns the number of digits in this BIGUINT (not counting leading zeros)
    size_type size() const;

    // pre: none
    // post: return 0 if this BIGUINT == n
    //             -1 if this BIGUINT < n
    //              1 if this BIGUINT > n
    int compare(const BIGUINT & n) const;


    // MODIFICATION FUNCTIONS

    // pre: none
    // post: this BIGUINT has been made a copy of source; old dynamically allocated memory has been returned to the heap
    void operator = (const BIGUINT & source);

    // pre: none
    // post: digits of this BIGUINT has been left shifted by n positions
    //       the new n least significiant digits are 0
    void ls (size_type n);

    // pre: none
    // post: digits of this BIGUINT has been right shifted by n positions; the n least significant digits are discarded
    void rs (size_type n);

    // ARITHMETIC member operators

    // pre: none
    // post: b has been added to this BIGUINT
    void operator +=(const BIGUINT &b);

    // pre: none
    // post: if b > this BIGUINT, then this BIGUINT is reset to 0
    //       else b is subtracted from this BIGUINT
    void operator -=(const BIGUINT & b);

    // pre: d represents a decimal digit
    // post: this BIGUINT has been multiplied by d
    void operator *= (digit_type d);

    // pre: none
    // post: this BIGUINT has been multiplied by b
    void operator *= (const BIGUINT & b);

    // pre: b != 0
    // post: this BIGUINT has been divided by b; the result is rounded down to the nearest integer
    void operator /= (const BIGUINT & b);

    // pre: b != 0
    // post: this BIGUINT has been modded by b;
    //       the new value is the remainder when dividing the original value by b
    void operator %= (const BIGUINT & b);

    // pre: none
    // post: this BIGUINT has been incremented/decremented by 1 (but capped below at 0)
    //       return value is the new value (pre)
    BIGUINT operator++();
    BIGUINT operator--();

    // pre: none
    // post: this BIGUINT has been incremented/decremented by 1 (but capped below at 0)
    //       return value is the original value (post)
    BIGUINT operator++(int);
    BIGUINT operator--(int);

    // pre: none
    // post: helper function that reverses the BIGUINT and removes any zeroes at the beginning
    BIGUINT get_reverse();

private:
    node * _data;

    // _data points to a linked list, each node containing a digit of this BIGUINT
    // the first node contains the LEAST significant digit

};

// NON-MEMBER OPERATORS

// I/O operators
std::ostream & operator <<(std::ostream & os, const BIGUINT &);
std::istream & operator >>(std::istream & is, BIGUINT &);

// ARITHMETIC operators
BIGUINT operator + (const BIGUINT &, const BIGUINT &);
BIGUINT operator - (const BIGUINT &, const BIGUINT &);
BIGUINT operator * (const BIGUINT &, const BIGUINT &);
BIGUINT operator / (const BIGUINT &, const BIGUINT &);
BIGUINT operator % (const BIGUINT &, const BIGUINT &);

// COMPARISON operators
bool operator <(const BIGUINT &, const BIGUINT &);
bool operator <=(const BIGUINT &, const BIGUINT &);
bool operator ==(const BIGUINT &, const BIGUINT &);
bool operator !=(const BIGUINT &, const BIGUINT &);
bool operator >=(const BIGUINT &, const BIGUINT &);
bool operator >(const BIGUINT &, const BIGUINT &);

// SHIFT operators
BIGUINT operator << (const BIGUINT &, unsigned int);
BIGUINT operator >> (const BIGUINT &, unsigned int);
#endif // LINKED_BIGUINT_H

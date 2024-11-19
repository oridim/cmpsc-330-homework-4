//---------------------------------------------------------------------
//
// Name: Ozge Selin Ak + Dimitri Orion Nearchos
// Email: osa5177@psu.edu + don5092@psu.edu
// Class: CMPSC 330
// Section: 001
//
// Assignment: Homework 4
// Due Date: November 19th, 2024
//
// Description:
//
//     * This file implements a collection of sequenced items container class.
//
// Acknowledgments:
//
//     1. I based my API off of the STL `vector` class referenced by:
//        https://cplusplus.com/reference/vector/vector/
//
//---------------------------------------------------------------------

#ifndef _SIMPLE_VECTOR_H_
#define _SIMPLE_VECTOR_H_

#include <algorithm>
#include <functional>
#include <string>

using namespace std;

// **TODO**: redo `SimpleVector` to utilize a `V **SimpleVector._elements` like
// `SimpleHashTable`. Otherwise, expensive operations like `SimpleVector.sort`
// will perform potentially expensive cloning reallocations instead of being able to
// just swap pointers.

// `SimpleVector<V>`
//
// Represents a container use to store sequences of items in a dynamically
// allocated array that can grow as capacity is exceeded.
template <typename V>
class SimpleVector
{
private:
    // `int SimpleVector._capacity`
    //
    // Represents the byte length of the internal `SimpleVector._elements`
    // dynamic array allocated on the heap.
    int _capacity;

    // `int SimpleVector._size`
    //
    // Represents the amount of element slots currently used in the internal
    // `SimpleVector._elements` dynamic array.
    int _size;

    // `T *SimpleVector._elements`
    //
    // Represents the internal dynamic array used to store every elemenet
    // pushed into the vector.
    V *_elements;

    // `void SimpleVector.reallocate_elements(int newCapacity)`
    //
    // If supplied a capacity that is greater than or equal to `SimpleVector._capacity`,
    // a new dynamic array is allocated to `SimpleVector._elements` with the
    // supplied capacity.
    //
    // Then, the old dynamic array's contents is copied over to the new one and
    // deleted afterwards.
    //
    // If the supplied that is less than the old capacity a `string` exception
    // is thrown since the internal dynamic array cannot be compressed when
    // active elements exist.
    void _reallocate_elements(int newCapacity)
    {
        if (newCapacity < this->_size)
        {
            throw string("bad argument #0 to 'SimpleVector._reallocate_elements' (new capacity '") + to_string(newCapacity) + string("' is cannot be less than or equal to the current size '") + to_string(this->_size) + string("')");
        }

        V *newElements = new V[newCapacity];

        for (int index = 0; index < this->_size; index++)
        {
            newElements[index] = this->_elements[index];
        }

        delete[] this->_elements;

        this->_capacity = newCapacity;
        this->_elements = newElements;
    }

public:
    SimpleVector()
    {
        this->_capacity = 0;
        this->_size = 0;

        this->_elements = new V[0];
    }

    SimpleVector(int size, int capacity = -1)
    {
        this->_capacity = (capacity > size) ? capacity : size;
        this->_size = size;

        this->_elements = new V[size];
    }

    SimpleVector(const SimpleVector &vector)
    {
        this->_capacity = vector._capacity;
        this->_size = vector._size;

        this->_elements = new V[this->_size];

        for (int index = 0; index < this->_size; index++)
        {
            this->_elements[index] = vector._elements[index];
        }
    }

    ~SimpleVector()
    {
        delete[] this->_elements;
    }

    bool operator==(const SimpleVector &rightHandVector) const
    {
        // Usually the convention in most OOP languages I have done equality checking
        // is done by default as nominal instances rather then structural values.
        //
        // So we will just compare pointers here for nominal instance checking.
        return this == &rightHandVector;
    }

    bool operator!=(const SimpleVector &rightHandVector) const
    {
        // See `SimpleVector::operator==` for reasoning.
        return this != &rightHandVector;
    }

    int capacity() const { return this->_capacity; }
    int size() const { return this->_size; }

    // `T &SimpleVector.at(int index)`
    //
    // Returns a reference to the element at the given `index`.
    V &at(int index)
    {
        if (index < 0 || index >= this->_size)
        {
            throw string("bad argument #0 to 'SimpleVector.at(int)' (index '") + to_string(index) + string("' not in vector range [0, ") + to_string(this->_size) + string("))");
        }

        return this->_elements[index];
    }

    // `int SimpleVector.find(T element)`
    //
    // Returns the index of the supplied `element`, if found, otherwise -1.
    int find(V element) const
    {
        for (int index = 0; index < this->_size; index++)
        {
            V &cachedElement = this->_elements[index];
            if (cachedElement == element)
            {
                return index;
            }
        }

        return -1;
    }

    // `int SimpleVector.find(function<bool(const V)> predicate)`
    //
    // Returns the index of the supplied `element`, if found, otherwise -1.
    int find(function<bool(const V)> predicate) const
    {
        for (int index = 0; index < this->_size; index++)
        {
            V &element = this->_elements[index];
            if (predicate(element))
            {
                return index;
            }
        }

        return -1;
    }

    // `const T &SimpleVector.get(int index)`
    //
    // Returns a const-reference to the element at the given `index`.
    const V &get(int index) const
    {
        if (index < 0 || index >= this->_size)
        {
            throw string("bad argument #0 to 'SimpleVector.get(int)' (index '") + to_string(index) + string("' not in vector range [0, ") + to_string(this->_size) + string("))");
        }

        return this->_elements[index];
    }

    // `bool SimpleVector.has(T element)`
    //
    // Returns `true` if the supplied `element` was found, otherwise `false`.
    bool has(V element) const
    {
        for (int index = 0; index < this->_size; index++)
        {
            V &cachedElement = this->_elements[index];
            if (cachedElement == element)
            {
                return true;
            }
        }

        return false;
    }

    int push_back(V element)
    {
        // If our size equates our capacity that means we need to reallocate
        // a bigger heap of memory to handle our internal array of elements.
        if (this->_size == this->_capacity)
        {
            // This allocation strategy is pretty naive... but doubling our
            // capacity per push will help to greatly reduce allocations as
            // needed.
            int newCapacity = max(this->_capacity * 2, 1);

            this->_reallocate_elements(newCapacity);
        }

        int pushedIndex = this->_size;
        this->_elements[pushedIndex] = element;

        this->_size += 1;
        return pushedIndex;
    }

    // `SimpleVector.remove(int index)`
    //
    // Removes the element at a given index and pulls every element ahead of
    // it back a slot.
    void remove(int index)
    {
        if (index < 0 || index >= this->_size)
        {
            throw string("bad argument #0 to 'SimpleVector.remove(int)' (index '") + to_string(index) + string("' not in vector range [0, ") + to_string(this->_size) + string("))");
        }

        for (int fallbackIndex = index; fallbackIndex < this->_size - 1; fallbackIndex++)
        {
            this->_elements[fallbackIndex] = this->_elements[fallbackIndex + 1];
        }

        this->_size -= 1;
    }

    // `SimpleVector.shrink_to_fit()`
    //
    // If `SimpleVector._size` is less than `SimpleVector._capacity`, then the
    // internal dynamic array, `SimpleVector._elements`, is reallocated to match
    // its capacity to `SimpleVector._size`.
    //
    // **NOTE**: This is for releasing unused allocated memory without fully deleting
    // the `SimpleVector` instance.
    void shrink_to_fit()
    {
        if (this->_size < this->_capacity)
        {
            this->_reallocate_elements(this->_size);
        }
    }

    // `void SimpleVector.sort(function<bool(const V)> comparator)`
    //
    // Returns the index of the supplied `element`, if found, otherwise -1.
    bool sort(function<int(const V, const V)> comparator)
    {
        bool didSort = false;

        for (int index = 0; index < this->_size - 1; index++)
        {
            V &a = this->_elements[index];
            V &b = this->_elements[index + 1];

            int delta = comparator(a, b);

            if (delta > 0)
            {
                V cache = b;

                b = a;
                a = cache;

                didSort = true;
            }
        }

        // If we sorted once, we need to do AT LEAST one final sort to make
        // sure everything is ordered properly.
        if (didSort)
        {
            this->sort(comparator);
        }

        return didSort;
    }
};

#endif
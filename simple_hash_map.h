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
//     * This file implements a collection of key-value pairs container class.
//
// Acknowledgments:
//
//     1. I based my API off of the STL `vector` class referenced by:
//        https://cplusplus.com/reference/unordered_map/unordered_map/
//
//---------------------------------------------------------------------

#ifndef _SIMPLE_HASH_MAP_H_
#define _SIMPLE_HASH_MAP_H_

#include <string>

#include "simple_vector.h"
#include "simple_hash_node.h"

using namespace std;

// `SimpleHashMap<K, V, elementsSize>
//
// Represents a container used to store key-value pairs into a fixed-size
// dynamically allocated block of memory.
template <typename K, typename V, int elementsSize>
class SimpleHashMap
{
private:
    // `SimpleHashMap::_hash(int key)`
    //
    // Returns the hash of the supplied `key` integer.
    static int _hash(const int key)
    {
        return key % elementsSize;
    }

private:
    SimpleHashNode<K, V> **_elements;

    // `SimpleHashMap::_locate_hash_node(int key, int &hash, SimpleHashNode<K, V> *&hashNode)`
    //
    // Loops through every element in the hashmap starting with the supplied `key`
    // that is first hashed.
    //
    // If there was a non-matching hashnode found at the hashed `key`, then the
    // next element is looked at.
    //
    // The results are stored in the suppled `hash` and `hashNode` references.
    void _locate_hash_node(int key, int &hash, SimpleHashNode<K, V> *&hashNode) const
    {
        SimpleHashNode<K, V> **elements = this->_elements;

        hash = this->_hash(key);
        hashNode = elements[hash];

        while (hashNode != nullptr && hashNode->key() != static_cast<K>(key))
        {
            hash = (hash + 1) % elementsSize;
            hashNode = elements[hash];
        }
    }

public:
    SimpleHashMap()
    {
        SimpleHashNode<K, V> **elements = new SimpleHashNode<K, V> *[elementsSize];

        for (int index = 0; index < elementsSize; index++)
        {
            elements[index] = nullptr;
        }

        this->_elements = elements;
    }

    SimpleHashMap(const SimpleHashMap<K, V, elementsSize> &hashMap)
    {
        SimpleHashNode<K, V> **elements = new SimpleHashNode<K, V> *[elementsSize];

        for (int index = 0; index < elementsSize; index++)
        {
            SimpleHashNode<K, V> *hashNode = hashMap._elements[index];

            if (hashNode != nullptr)
            {
                elements[index] = new SimpleHashNode<K, V>(*hashNode);
            }
        }

        this->_elements = elements;
    }

    ~SimpleHashMap()
    {
        SimpleHashNode<K, V> **elements = this->_elements;

        for (int index = 0; index < elementsSize; index++)
        {
            SimpleHashNode<K, V> *hashNode = elements[index];

            if (hashNode != nullptr)
            {
                delete hashNode;
            }
        }

        delete[] elements;
    }

    bool operator==(const SimpleHashMap &rightHandMap) const
    {
        // Usually the convention in most OOP languages I have done equality checking
        // is done by default as nominal instances rather then structural values.
        //
        // So we will just compare pointers here for nominal instance checking.
        return this == &rightHandMap;
    }

    bool operator!=(const SimpleHashMap &rightHandMap) const
    {
        // See `SimpleHashMap::operator==` for reasoning.
        return this != &rightHandMap;
    }

    // `T &SimpleHashMap.at(int key)`
    //
    // Returns a reference to the hashnode's value at the given `key`.
    V &at(int key)
    {
        SimpleHashNode<K, V> **elements = this->_elements;

        int hash;
        SimpleHashNode<K, V> *hashNode;

        this->_locate_hash_node(key, hash, hashNode);

        if (hashNode == nullptr)
        {
            hashNode = new SimpleHashNode<K, V>(key);
            elements[hash] = hashNode;
        }

        return hashNode->value();
    }

    // `const T &SimpleHashMap.get(int key)`
    //
    // Returns a const-reference to the hashnode's value at the given `key`.
    const V &get(int key) const
    {
        int hash;
        SimpleHashNode<K, V> *hashNode;

        this->_locate_hash_node(key, hash, hashNode);

        if (hashNode == nullptr)
        {
            throw string("bad argument #0 to 'SimpleHashMap.at(int)' (key '") + to_string(key) + string("' was not previously assigned)");
        }

        return hashNode->value();
    }

    // `bool SimpleHashMap.has(int key)`
    //
    // Returns `true` if the supplied `key` was found associated with a
    // hashnode in the hashmap.
    bool has(int key) const
    {
        int hash;
        SimpleHashNode<K, V> *hashNode;

        this->_locate_hash_node(key, hash, hashNode);

        return hashNode != nullptr;
    }

    // `SimpleVector<K> *SimpleHashMap.keys()`
    //
    // Returns a pointer to a new `SimpleVector<K>` instance that contains
    // all the initialized keys in the hashmap.
    SimpleVector<K> *keys() const
    {
        SimpleVector<K> *keys = new SimpleVector<K>();
        SimpleHashNode<K, V> **elements = this->_elements;

        for (int index = 0; index < elementsSize; index++)
        {
            SimpleHashNode<K, V> *hashNode = elements[index];

            if (hashNode != nullptr)
            {
                keys->push_back(hashNode->key());
            }
        }

        return keys;
    }

    // `void SimpleHashMap.remove(int key)`
    //
    // Removes the hashnode associated with the associated key if found
    // from the hashmap.
    void remove(int key)
    {
        SimpleHashNode<K, V> **elements = this->_elements;

        int hash;
        SimpleHashNode<K, V> *hashNode;

        this->_locate_hash_node(key, hash, hashNode);

        if (hashNode != nullptr)
        {
            delete hashNode;
            elements[hash] = nullptr;
        }
    }

    // `SimpleVector<K> *SimpleHashMap.values()`
    //
    // Returns a pointer to a new `SimpleVector<K>` instance that contains
    // all the initialized values in the hashmap.
    SimpleVector<V> *values() const
    {
        SimpleVector<V> *values = new SimpleVector<V>();
        SimpleHashNode<K, V> **elements = this->_elements;

        for (int index = 0; index < elementsSize; index++)
        {
            SimpleHashNode<K, V> *hashNode = elements[index];

            if (hashNode != nullptr)
            {
                values->push_back(hashNode->value());
            }
        }

        return values;
    }
};

#endif
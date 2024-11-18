#ifndef _SIMPLE_HASH_MAP_H_
#define _SIMPLE_HASH_MAP_H_

#include <algorithm>
#include <cstring>

#include "simple_vector.h"
#include "simple_hash_node.h"

using namespace std;

template <typename K, typename V, int elementsSize>
class SimpleHashMap
{
private:
    static int _hash(const int key)
    {
        return key % elementsSize;
    }

private:
    SimpleHashNode<K, V> **_elements;

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

    bool has(int key) const
    {
        int hash;
        SimpleHashNode<K, V> *hashNode;

        this->_locate_hash_node(key, hash, hashNode);

        return hashNode != nullptr;
    }

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
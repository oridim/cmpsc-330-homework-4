#ifndef _SIMPLE_HASH_MAP_H_
#define _SIMPLE_HASH_MAP_H_

#include <algorithm>
#include <cstring>

#include "simple_vector.h"
#include "simple_hash_node.h"

using namespace std;

template <typename K, typename V, size_t elementsSize>
class SimpleHashMap
{
private:
    static size_t _hash(const size_t key)
    {
        return key % elementsSize;
    }

    static size_t _key(const char *key)
    {
        size_t sum = 0;

        for (size_t index = 0; index < strlen(key); index++)
        {
            sum += key[index];
        }

        return sum;
    }

private:
    SimpleHashNode<K, V> **_elements;

    void _locate_hash_node(size_t key, size_t &hash, SimpleHashNode<K, V> *&hashNode) const
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

        for (size_t index = 0; index < elementsSize; index++)
        {
            elements[index] = nullptr;
        }

        this->_elements = elements;
    }

    SimpleHashMap(const SimpleHashMap<K, V, elementsSize> &hashMap)
    {
        SimpleHashNode<K, V> **elements = new SimpleHashNode<K, V> *[elementsSize];

        for (size_t index = 0; index < elementsSize; index++)
        {
            elements[index] = hashMap._elements[index];
        }

        this->_elements = elements;
    }

    ~SimpleHashMap()
    {
        SimpleHashNode<K, V> **elements = this->_elements;

        for (size_t index = 0; index < elementsSize; index++)
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

    V &at(size_t key)
    {
        SimpleHashNode<K, V> **elements = this->_elements;

        size_t hash;
        SimpleHashNode<K, V> *hashNode;

        this->_locate_hash_node(key, hash, hashNode);

        if (hashNode == nullptr)
        {
            hashNode = new SimpleHashNode<K, V>(key);
            elements[hash] = hashNode;
        }

        return hashNode->value();
    }

    V &at(int key)
    {
        return this->at(static_cast<size_t>(key));
    }

    V &at(const char *key)
    {
        size_t sum = this->_key(key);

        return this->at(sum);
    }

    const V &get(size_t key) const
    {
        size_t hash;
        SimpleHashNode<K, V> *hashNode;

        this->_locate_hash_node(key, hash, hashNode);

        if (hashNode == nullptr)
        {
            throw string("bad argument #0 to 'SimpleHashMap.at(int)' (key '") + to_string(key) + string("' was not previously assigned)");
        }

        return hashNode->value();
    }

    const V &get(int key) const
    {
        return this->get(static_cast<size_t>(key));
    }

    const V &get(const char *key) const
    {
        size_t sum = this->_key(key);

        return this->get(sum);
    }

    bool has(size_t key) const
    {
        size_t hash;
        SimpleHashNode<K, V> *hashNode;

        this->_locate_hash_node(key, hash, hashNode);

        return hashNode != nullptr;
    }

    bool has(int key) const
    {
        return this->has(static_cast<size_t>(key));
    }

    bool has(const char *key) const
    {
        size_t sum = this->_key(key);

        return this->has(sum);
    }

    SimpleVector<K> *keys() const
    {
        SimpleVector<K> *keys = new SimpleVector<K>();
        SimpleHashNode<K, V> **elements = this->_elements;

        for (size_t index = 0; index < elementsSize; index++)
        {
            SimpleHashNode<K, V> *hashNode = elements[index];

            if (hashNode != nullptr)
            {
                keys->push_back(hashNode->key());
            }
        }

        return keys;
    }

    void remove(size_t key)
    {
        SimpleHashNode<K, V> **elements = this->_elements;

        size_t hash;
        SimpleHashNode<K, V> *hashNode;

        this->_locate_hash_node(key, hash, hashNode);

        if (hashNode != nullptr)
        {
            delete hashNode;
            elements[hash] = nullptr;
        }
    }

    void remove(int key)
    {
        return this->remove(static_cast<size_t>(key));
    }

    void remove(const char *key)
    {
        size_t sum = this->_key(key);

        return this->remove(sum);
    }

    SimpleVector<V> *values() const
    {
        SimpleVector<V> *values = new SimpleVector<V>();
        SimpleHashNode<K, V> **elements = this->_elements;

        for (size_t index = 0; index < elementsSize; index++)
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
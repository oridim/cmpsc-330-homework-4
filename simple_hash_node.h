#ifndef _SIMPLE_HASH_NODE_H_
#define _SIMPLE_HASH_NODE_H_

// `SimpleHashNode<K, V>`
//
// Represents a node used by `SimpleHashMap` for storing key-value pairs.
template <typename K, typename V>
class SimpleHashNode
{
private:
    // `K SimpleHashNode._key`
    //
    // Represents the stored key of the key-value pair.
    K _key;

    // `V SimpleHashNode._value`
    //
    // Represents the stored value of the key-value pair.
    V _value;

public:
    SimpleHashNode(K key)
    {
        this->_key = key;
    }

    SimpleHashNode(const SimpleHashNode &hashNode)
    {
        this->_key = hashNode._key;
        this->_value = hashNode._value;
    }

    K &key() { return this->_key; }
    V &value() { return this->_value; }
};

#endif
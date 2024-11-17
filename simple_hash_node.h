#ifndef _SIMPLE_HASH_NODE_H_
#define _SIMPLE_HASH_NODE_H_

template <typename K, typename V>
class SimpleHashNode
{
private:
    K _key;

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
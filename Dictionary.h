#pragma once

#include "List.h"

template <typename K, typename V>
class Dictionary {
public:
	Dictionary() {}
	Dictionary(const Dictionary<K, V>&) = delete;
	void operator=(const Dictionary<K, V>&) = delete;
	virtual void insert(K key, V value) = 0;
	virtual V remove(K key) = 0;
	virtual V getValue(K key) = 0;
	virtual void setValue(K key, V value) = 0;
	virtual bool contains(K key) = 0;
	virtual bool isEmpty() = 0;
	virtual void clear() = 0;
	virtual List<K>* getKeys() = 0;
	virtual List<V>* getValues() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};


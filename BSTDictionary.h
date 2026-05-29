#pragma once

#include <stdexcept>
#include "Dictionary.h"
#include "BSTree.h"
#include "Pair.h"
#include "List.h"
#include "DLinkedList.h"

using namespace std;

template <typename K, typename V>
class BSTDictionary : public Dictionary<K, V>{
private:
	BSTree<Pair<K, V>> tree;
public:
	BSTDictionary() {}

	~BSTDictionary() {
		tree.clear(); 
	}

	void insert(K key, V value) {
		if (tree.contains(Pair<K, V>(key))) {
			throw runtime_error("Key already exists.");
		}
		tree.insert(Pair<K, V>(key, value));
	}

	V remove(K key) {
		if (!tree.contains(Pair<K, V>(key))) {
			throw runtime_error("Key not found.");
		}
		Pair<K, V> removed = tree.remove(Pair<K, V>(key));
		return removed.value;
	}

	V getValue(K key) {
		if (!tree.contains(Pair<K, V>(key))) {
			throw runtime_error("Key not found.");
		}
		Pair<K, V> p = tree.find(Pair<K, V>(key));
		return p.value;
	}

	void setValue(K key, V value) {
		if (!tree.contains(Pair<K, V>(key))) {
			throw runtime_error("Key not found.");
		}

	}

	bool contains(K key) {
		return tree.contains(Pair<K, V>(key));
	}

	bool isEmpty() {
		return tree.isEmpty();
	}

	void clear() {
		tree.clear();
	}

	List<K>* getKeys() {
		List<Pair<K, V>>* pairs = tree.getElements();
		List<K>* keys = new DLinkedList();

		for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
			keys->append(pairs->getElement.key);
		}
		delete pairs;
		return keys;
	}

	List<K>* getValues() {
		List<Pair<K, V>>* pairs = tree.getElements();
		List<V>* values = new DLinkedList();

		for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
			values->append(pairs->getElement.value);
		}
		delete pairs;
		return values;
	}

	int getSize() {
		return tree.getSize();
	}

	void print() {
		tree.print();
	}

	void update(Dictionary<K, V>* D) {

	}

	void zip(List<K>* keys, List<V>* values) {

	}

};


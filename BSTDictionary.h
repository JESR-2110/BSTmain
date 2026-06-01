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
		List<K>* keys = new DLinkedList<K>();

		for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
			keys->append(pairs->getElement().key);
		}
		delete pairs;
		return keys;
	}

	List<V>* getValues() {
		List<Pair<K, V>>* pairs = tree.getElements();
		List<V>* values = new DLinkedList<V>();

		for (pairs->goToStart(); !pairs->atEnd(); pairs->next()) {
			values->append(pairs->getElement().value);
		}
		delete pairs;
		return values;
	}

	int getSize() {
		return tree.getSize();
	}

	void print() {
		if (tree.isEmpty()) {
			cout << "  (vacio)" << endl;
			return;
		}
		List<Pair<K, V>>* pairs = tree.getElements();
		for (int i = 0; i < pairs->getSize(); i++) {
			pairs->goToPos(i);
			Pair<K, V> p = pairs->getElement();
			cout << "  [" << p.key << "] -> " << p.value << endl;
		}
		delete pairs;
	}

	void update(Dictionary<K, V>* D) {
		List<K>* keys = D->getKeys();
		keys->goToStart();
		while (keys->getSize() > 0 && !keys->atEnd()) {
			K key = keys->getElement();
			V val = D->getValue(key);

			if (this->contains(key)) {
				this->setValue(key, val);
			}
			else {
				this->insert(key, val);
			}
			keys->next();
		}

		if (keys->getSize() > 0) {
			K key = keys->getElement();
			V val = D->getValue(key);
			if (this->contains(key)) {
				this->setValue(key, val);
			}
			else {
				this->insert(key, val);
			}
		}

		delete keys;
	}

	void zip(List<K>* keys, List<V>* values) {
    keys->goToStart();
    values->goToStart();
    for (int i = 0; i < keys->getSize() && i < values->getSize(); i++) {
        keys->goToPos(i);
        values->goToPos(i);
        K key = keys->getElement();
        V val = values->getElement();
        if (this->contains(key)) {
            this->setValue(key, val);
        } else {
            this->insert(key, val);
        }
    }
}

};


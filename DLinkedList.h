#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class DLinkedList : public List<E> {
private:
	DNode<E>* head;
	DNode<E>* tail;
	DNode<E>* current;
	int size;

public:
	DLinkedList() {
		current = head = new DNode<E>(nullptr, nullptr);
		head->next = tail = new DNode<E>(nullptr, head);
		size = 0;
	}
	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}
	void insert(E element) {
		current->next = current->next->previous =
			new DNode<E>(element, current->next, current);
		size++;
	}
	void append(E element) {
		tail->previous = tail->previous->next =
			new DNode<E>(element, tail, tail->previous);
		size++;
	}
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		current->next->element = element;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		E result = current->next->element;
		current->next = current->next->next;
		delete current->next->previous;
		current->next->previous = current;
		size--;
		return result;
	}
	void clear() {
		while (head->next != tail) {
			current = head->next;
			head->next = current->next;
			delete current;
		}
		current = head;
		size = 0;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail->previous;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Invalid position.");
		current = head;
		for (int i = 0; i < pos; i++) {
			current = current->next;
		}
	}
	void next() {
		if (current != tail)
			current = current->next;
	}
	void previous() {
		if (current != head)
			current = current->previous;
	}
	bool atStart() {
		return current == head;
	}
	bool atEnd() {
		return current == tail->previous;
	}
	int getPos() {
		int pos = 0;
		DNode<E>* temp = head;
		while (temp != current) {
			temp = current->next;
			pos++;
		}
		return pos;
	}
	int getSize() {
		return size;
	}
	void print() {
		int i = 1;
		DNode<E>* temp = head->next;
		while (temp != tail) {
			cout << i << ". " << temp->element << endl;
			temp = temp->next;
			i++;
		}
		cout << endl;
	}
};


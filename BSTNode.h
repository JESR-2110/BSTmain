#pragma once

template <typename E>
class BSTNode{
public:
	E element;
	BSTNode<E>* left;
	BSTNode<E>* right;
	BSTNode(E element) {
		this->element = element;
		right = left = nullptr;
	}
	BSTNode(E element, BSTNode<E>* left, BSTNode<E>* right) {
		this->element = element;
		this->left = left;
		this->right = right;
	}
	int childrenCount() {
		return (left != nullptr ? 1 : 0) + (right != nullptr ? 1 : 0);
	}
	BSTNode<E>* onlyChild() {
		return (left == nullptr ? right : left);
	}
};


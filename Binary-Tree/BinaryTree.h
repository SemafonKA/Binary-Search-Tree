#pragma once
#include <iostream>

template <typename T>
class BinaryTree {
private:
	class TreeNode {
	public:
		T data{};
		TreeNode* right{ nullptr };
		TreeNode* left { nullptr };

		TreeNode(const T& _data) : data{ _data }  {};
	};

	TreeNode* m_root{ nullptr };

	TreeNode* _find(const T& _data) const {
		TreeNode* parentElem = _find_parent(_data);
		if (parentElem == nullptr)     return m_root;
		if (_data > parentElem->data)  return parentElem->right;
		if (_data < parentElem->data)  return parentElem->left;
	}

	TreeNode* _find_parent(const T& _data) const {
		TreeNode* parentElem  = nullptr;
		TreeNode* currentElem = m_root;
		while (currentElem != nullptr && _data != currentElem->data) {
			parentElem = currentElem;
			currentElem = _data > currentElem->data ? currentElem->right : currentElem->left;
		}
		return parentElem;
	}

	void _delete(TreeNode* _parent) {
		if (_parent->right != nullptr) _delete(_parent->right);
		if (_parent->left != nullptr)  _delete(_parent->left);
		delete _parent;
	}

	void _out(TreeNode* _parent) const {
		std::cout << _parent->data;
		if(!_isLeaf(_parent)) {
			std::cout << " (";
			if (_parent->left != nullptr) _out(_parent->left);
			if (_parent->right != nullptr) {
				if (_parent->left != nullptr) std::cout << ", ";
				_out(_parent->right);
			}
			std::cout << ")";
		}
	}

	bool _isLeaf(TreeNode* elem) const {
		if (elem != nullptr)
			return elem->right == nullptr && elem->left == nullptr;
		return false;
	}

public:
	~BinaryTree() {
		_delete(m_root);
	}

	void del() {
		_delete(m_root);
		m_root = nullptr;
	}

	bool isLeaf(const T& _data) const {
		TreeNode* elem = _find(_data);
		return _isLeaf(elem);
	}
	
	bool isEmpty() const { return m_root == nullptr; }

	BinaryTree& push(const T& _data) {
		TreeNode* newNode = new TreeNode(_data);
		if (m_root == nullptr) {
			m_root = newNode;
		}
		else {
			TreeNode* currentElem = _find_parent(_data);
			
			if (currentElem == nullptr) {}
			else if (_data > currentElem->data && currentElem->right == nullptr) {
				currentElem->right = newNode;
			}
			else if (_data < currentElem->data && currentElem->left == nullptr) {
				currentElem->left = newNode;
			}
			else {
				delete newNode;
			}
		}

		return *this;
	}

	/*int pop(const T& _data) {
		if (isEmpty()) return 0;

		return 1;
	}*/

	void out() const {
		_out(m_root);
		std::cout << std::endl;
	}
};
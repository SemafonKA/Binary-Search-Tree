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

	TreeNode* _find(const T& _data) {
		TreeNode* currentElem = m_root;
		while (_data != currentElem->data && currentElem != nullptr) {
			currentElem = _data > currentElem->data ? currentElem->right : currentElem->left;
		}
		return currentElem;
	}

	void _delete(TreeNode* _parent) {
		if (_parent->right != nullptr) _delete(_parent->right);
		if (_parent->left != nullptr)  _delete(_parent->left);
		delete _parent;
	}

	void _out(TreeNode* _parent) {
		std::cout << _parent->data << " (";
		if (_parent->left != nullptr) _out(_parent->left);
		if (_parent->right != nullptr) {
			if (_parent->left != nullptr) std::cout << ", ";
			_out(_parent->right);
		}
		std::cout << ")";
	}

public:
	~BinaryTree() {
		_delete(m_root);
	}

	void del() {
		_delete(m_root);
	}

	BinaryTree& push(const T& _data) {
		TreeNode* newNode = new TreeNode(_data);
		TreeNode* currentElem = m_root;
		if (currentElem == nullptr) {
			m_root = newNode;
			return (*this);
		}

		while (currentElem != newNode) {
			if (_data > currentElem->data) {
				if (currentElem->right == nullptr) {
					currentElem->right = newNode;
				}
				currentElem = currentElem->right;
			}
			else if (_data < currentElem->data) {
				if (currentElem->left == nullptr) {
					currentElem->left = newNode;
				}
				currentElem = currentElem->left;
			}
			else {
				delete newNode;
				break;
			}
		}

		return (*this);
	}

	void out() {
		_out(m_root);
		std::cout << std::endl;
	}
};
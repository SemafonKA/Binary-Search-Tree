#pragma once
#include <iostream>
#include <sstream>

int isOperator(char ch) {
	switch (ch) {
	case '+':
	case '-':
	case '*':
	case '/': return 1;
	default:  return 0;
	}
}

template <typename T>
class BinarySearchTree {
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

	/*
		Рекурсивное удаление всего поддерева вместе с родителем
	*/
	void _delete(TreeNode* _parent) {
		if (!_parent) return;
		if (_parent->right != nullptr) _delete(_parent->right);
		if (_parent->left != nullptr)  _delete(_parent->left);
		delete _parent;
	}

	/* 
		Рекурсивный вывод в формате левого списка, от родителя поддерева
	*/
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

	inline bool _isLeaf(TreeNode* elem) const {
		if (elem != nullptr)
			return elem->right == nullptr && elem->left == nullptr;
		return false;
	}

	/*
		Рекурсивный вывод в формате дерева, от родителя поддерева
	*/
	void _print_tree(TreeNode* p, int level = 0) const
	{
		if (p)
		{
			_print_tree(p->right, level + 1);
			for (int i = 0; i < level; i++) std::cout << "    ";
			std::cout << p->data << std::endl;
			_print_tree(p->left, level + 1);
		}
	}

	/* 
		Собирает в буфер строку в инфиксной форме 
	*/
	void _buf_infix(TreeNode* _parent, std::stringstream& buf) const {
		if (!_parent) return;
		if (_isLeaf(_parent)) {
			buf << _parent->data;
		}
		else {
			buf << " (";
			_buf_infix(_parent->left, buf);
			buf << ") " << _parent->data << " (";
			_buf_infix(_parent->right, buf);
			buf << ") ";
		}
	}

	bool _push_elem(TreeNode* _parent, T _data) {
		if (!_parent && !m_root) {
			m_root = new TreeNode(_data);
			return true;
		}
		else if (_parent && isOperator(_parent->data)) {
			if (!_parent->left) {
				_parent->left = new TreeNode(_data);
				return true;
			}
			
			if (_push_elem(_parent->left, _data)) {
				return true;
			}
			else {
				if (!_parent->right) {
					_parent->right = new TreeNode(_data);
					return true;
				}

				return _push_elem(_parent->right, _data);
			}
		}

		return false;
	}

public:
	~BinarySearchTree() {
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

	BinarySearchTree& push(const T& _data) {
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

	int pop(const T& _data) {
		/* Если дерево пустое */
		if (isEmpty()) return 0;

		TreeNode* deletingElem = _find(_data);
		TreeNode* parentElem = _find_parent(_data);
		bool isRight{ false };
		if (parentElem) {
			if (deletingElem == parentElem->right) isRight = true;
		}

		/* Если такого элемента нет */
		if (!deletingElem) return 0;
		/* Если удаляемый элемент - лист */
		else if (_isLeaf(deletingElem)) {
			if (!parentElem) m_root = nullptr;
			else {
				if (isRight) parentElem->right = deletingElem->left;
				else parentElem->left = deletingElem->left;
			}
		}
		/* Если у удаляемого элемента есть только левый потомок */
		else if (!deletingElem->right) {
			if (!parentElem) m_root = deletingElem->left;
			else {
				if (isRight) parentElem->right = deletingElem->left;
				else parentElem->left = deletingElem->left;
			}
		}
		/* Если у удаляемого элемента есть только правый потомок */
		else if (!deletingElem->left) {
			if (!parentElem) m_root = deletingElem->right;
			else {
				if (isRight) parentElem->right = deletingElem->right;
				else parentElem->left = deletingElem->right;
			}
		}
		/* Если есть оба потомка */
		else {
			TreeNode* parentNextElem = deletingElem;
			TreeNode* nextElem = deletingElem->right;

			/* Если от правого потомка нельзя пойти влево */
			if (!nextElem->left) {
				nextElem->left = deletingElem->left;
			}
			/* Если можно пойти влево */
			else {
				while (nextElem->left) {
					parentNextElem = nextElem;
					nextElem = nextElem->left;
				}
				parentNextElem->left = nextElem->right;
				nextElem->left = deletingElem->left;
				nextElem->right = deletingElem->right;
			}
			if (!parentElem) m_root = nextElem;
			else if (isRight) parentElem->right = nextElem;
			else parentElem->left = nextElem;
		}

		delete deletingElem;
		return 1;
	}

	void out() const {
		_out(m_root);
		std::cout << std::endl;
	}

	void out_tree () const {
		std::cout << std::endl;
		_print_tree(m_root);
		std::cout << std::endl;
	}

	void out_infix() const {
		std::stringstream buf;

		std::cout << std::endl;
		_buf_infix(m_root, buf);
		std::cout << buf.str() << std::endl;
	}

	std::stringstream buf_infix() const {
		std::stringstream buf;

		std::cout << std::endl;
		_buf_infix(m_root, buf);
		std::cout << std::endl;

		return buf;
	}

	void operator= (std::string _inputString) {
		del();
		for (auto elem : _inputString) {
			_push_elem(m_root, elem);
		}
	}
};
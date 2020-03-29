#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main() {
	system("chcp 65001"); system("cls");

	BinarySearchTree<int> tree;

	tree.push(5).push(2).push(3).push(8).push(2).push(7).push(10).push(9);
	tree.push(11).push(24).push(-3).push(18);
	tree.out();
	tree.out_tree();
	tree.pop(5);
	tree.out();
	tree.out_tree();

	cout << "Нажмите ввод, чтобы продолжить";
	cin.get();
	return 0;
}
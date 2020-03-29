#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main() {
	system("chcp 65001"); system("cls");

	BinarySearchTree<int> tree;

	tree.push(5).push(2).push(3).push(8).push(2).push(7).push(9);
	tree.out();

	/*tree.pop(5);
	tree.out();*/

	cout << "Нажмите ввод, чтобы продолжить";
	cin.get();
	return 0;
}
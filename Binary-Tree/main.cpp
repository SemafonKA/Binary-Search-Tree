#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main() {
	system("chcp 65001"); system("cls");

	BinaryTree<int> tree;

	for (int i = 0; i < 10; ++i) {
		tree.push(rand() % 10);
	}
	tree.out();

	cout << "Нажмите ввод, чтобы продолжить";
	cin.get();
	return 0;
}
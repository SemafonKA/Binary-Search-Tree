#include <iostream>
#include <string>
#include "BinarySearchTree.h"
#include "PostficsCalc.h"

using namespace std;

int main() {
	system("chcp 65001"); system("cls");

	BinarySearchTree<char> tree;

	string inputString;
	getline(cin, inputString);
	tree = inputString;

	PostficsCalc calc;
	cout << calc.fromNormal(tree.buf_infix().str()) << endl;

	cout << "Нажмите ввод, чтобы продолжить";
	cin.get();
	return 0;
}
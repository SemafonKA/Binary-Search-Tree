#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.h"
#include "PostficsCalc.h"

using namespace std;

int main() {
	system("chcp 65001"); system("cls");

	BinarySearchTree<char> tree;

	cout << "Введите числа строкой (либо введите 'F' чтобы загрузить с файла)" << endl;
	string inputString;
	getline(cin, inputString);
	if (inputString == "f" || inputString == "F") {
		ifstream inputFile("input.txt");
		inputString.clear();
		getline(inputFile, inputString);
		cout << inputString << endl;
	}
	tree = inputString;

	PostficsCalc calc;
	try {
		cout << calc.fromNormal(tree.buf_infix().str()) << endl;
	}
	catch (std::logic_error err) {
		cerr << err.what() << endl;
	}

	cout << "Нажмите ввод, чтобы продолжить";
	cin.get();
	return 0;
}
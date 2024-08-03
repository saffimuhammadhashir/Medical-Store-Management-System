#pragma once
#include "AVL.h"
class Category {
public:
	long long id;
	string name;
	AVLTree<Medicine> medicines;
	Category(long long id, string category, bool chk = true) :id(id), name(category) {
		if (chk) {
			appendToCatgoryFile();

		}
	}
	void display() {
		cout << "\n\n\n=>Category: " << name << endl << endl;
		medicines.display();
		cout << "|***********************************************|" << endl;
	}
	bool operator<(const Category& other) const {
		return id < other.id;
	}
	void appendToCatgoryFile() {

		ofstream outFile("categories.txt", ios::app);
		if (!outFile.is_open()) {
			cerr << "Error: Could not open file " << "categories.txt" << endl;
			return;
		}


		outFile << name << endl;


		outFile.close();
	}
	void displaysearched(string str) {
		medicines.printmatch(str);
	}
	Medicine* searchmedicine(string med) {

		if (medicines.search(hashing(med)) != nullptr) {
			return &medicines.search(hashing(med))->data;
		}
		return nullptr;
	}
};

AVLTree<Category> categories;


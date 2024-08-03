#pragma once
#include "AllHeaders.h"
#include <algorithm>

using namespace std;


class Medicine {
public:
	long long id;
	string name;
	string category;
	string manufacturer;
	string expiry_date;
	double price;
	int quantity;
	Medicine() {}
	void create() {
		cout << "Enter Name for Medicine: "; cin >> name;
		cout << "Enter Category for Medicine: "; cin >> category;
		cout << "Enter Manufacturer for Medicine: "; cin >> manufacturer;
		cout << "Enter Expiry Date for Medicine: "; cin >> expiry_date;
		cout << "Enter Price for Medicine: "; cin >> price;
		cout << "Enter Quantity for Medicine: "; cin >> quantity;
		id = hashing(category);
	}

	Medicine(long long id, string name, string category, string manufacturer, string expiry_date, double price, int quantity, bool chk = true)
		: id(id), name(name), category(category), manufacturer(manufacturer), expiry_date(expiry_date), price(price), quantity(quantity) {
		if (chk) {
			appendToMedicineFile();
		}
	}

	void truncToMedicineFile() {

		ofstream outFile("medicines.txt", ios::app);

		if (!outFile.is_open()) {
			cerr << "Error: Could not open file " << "medicines.txt" << endl;
			return;
		}

		cout << name << endl;

		outFile << name << ","
			<< category << ","
			<< manufacturer << ","
			<< expiry_date << ","
			<< quantity << ","
			<< price << endl;


		outFile.close();
	}

	void appendToMedicineFile() {

		ofstream outFile("medicines.txt", ios::app);

		if (!outFile.is_open()) {
			cerr << "Error: Could not open file " << "medicines.txt" << endl;
			return;
		}


		outFile << name << ","
			<< category << ","
			<< manufacturer << ","
			<< expiry_date << ","
			<< quantity << ","
			<< price << endl;


		outFile.close();
	}

	void displaysearched(string str) {
		if (str == name) {
			display();
		}
	}

	void display() const {
		cout << "----------------------------------" << endl;
		cout << "Id: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Category: " << category << endl;
		cout << "Manufacturer: " << manufacturer << endl;
		cout << "Expiry Date: " << expiry_date << endl;
		cout << "Quantity: " << quantity << endl;
		cout << "Price: $" << price << endl << endl << endl;
	}
	bool operator<(const Medicine& other) const {
		return id < other.id;
	}
};

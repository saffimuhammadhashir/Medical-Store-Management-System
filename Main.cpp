#include <iostream>
#include "Admin.h"
#include "CounterManager.h"
#include "Customer.h"
#include "User.h"
#include "LoginSignUP.h"
#include "Category.h"
#include "card_transaction.h"
void insertmedicine(Medicine med1) {

	AVLNode<Category>* val = categories.search(hashing(med1.category));
	if (val == nullptr) {
		Category cat(hashing(med1.category), med1.category);
		categories.insert(cat);
		val = categories.search(hashing(med1.category));
		val->data.medicines.insert(med1);
		cout << "Category created" << endl;
	}
	else {
		cout << "Medicine created" << endl;
		val->data.medicines.insert(med1);
	}
}
void loadMedicinesFromFile() {
	ifstream file("medicines.txt");
	if (!file.is_open()) {
		cerr << "Failed to open file: " << "medicines.txt" << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		istringstream ss(line);
		string quantityStr, name, category, manufacturer, expiryDate, priceStr;
		double price;
		int quantity;


		getline(ss, name, ',');
		getline(ss, category, ',');
		getline(ss, manufacturer, ',');
		getline(ss, expiryDate, ',');
		getline(ss, quantityStr, ',');
		getline(ss, priceStr, ',');

		try {
			price = stod(priceStr);
			quantity = stod(quantityStr);
		}
		catch (const invalid_argument& e) {
			cerr << "Invalid data format in file: "<<name<<" , "<< category<<"   " << e.what() << endl;
			continue;
		}
		AVLNode<Category>* val = categories.search(hashing(category));
		Medicine med(hashing(name), name, category, manufacturer, expiryDate, price, quantity, false);
		val->data.medicines.insert(med);
	}

	file.close();
}
void loadCategoriesFromFile() {
	ifstream file("categories.txt");
	if (!file.is_open()) {
		return;
	}

	string name;
	while (getline(file, name)) {
		if (!name.empty()) {
			Category cat(hashing(name), name, false);
			categories.insert(cat);
		}
	}

	file.close();
}
void loadData() {
	loadCategoriesFromFile();
	loadMedicinesFromFile();
	//categories.display();
}

void emptyFile(string filename) {
	std::ofstream ofs(filename, std::ofstream::out | std::ofstream::trunc);
	if (ofs.is_open()) {
		ofs.close();
		std::cout << "File " << filename << " has been emptied." << std::endl;
	}
	else {
		std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
	}
}

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

bool accessible() {

	int choice;
	do
	{
		cout << "=============================" << endl;
		cout << "  Medical Store Management System" << endl;
		cout << "          Login / Sign Up" << endl;
		cout << "=============================" << endl;
		cout << "1. Log In" << endl;
		cout << "2. Sign Up" << endl;
		cout << "3. Exit" << endl;
		cout << "=============================" << endl;
		cout << "Please choose an option (1-3): ";
		cin >> choice;
		if (choice == 1 && Login()) {
			return true;
		}
		else if (choice == 2) {
			SignUp();
			cout << "Signed up successfully!" << endl;
		}
		else if (choice == 3) {
			return false;
		}

	} while (choice > 2 || choice < 1);
	return false;
}

void loadTransactionsFromFile() {
	ifstream file("transactions.txt");
	string customername, medicine, category, custommanager;
	int totalbill;
	bool Billpaid;
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream ss(line);
			string billpaidStr;
			getline(ss, customername, ',');
			getline(ss, medicine, ',');
			getline(ss, category, ',');
			getline(ss, custommanager, ',');
			ss >> totalbill;
			getline(ss, billpaidStr, ',');
			Billpaid = (billpaidStr == "1");
			RequestNode<Request>* r = requestlist.requestholder(customername);
			transaction* t = new transaction(customername, medicine, category, custommanager, totalbill, true, false);
			countermanagerlist.updatebalance(custommanager, (countermanagerlist.getbalance(custommanager) + totalbill));
			if (r != nullptr) {
				r->data.insertinhistory(t);

			}
		}
		file.close();
	}
	else {
		cout << "Unable to open file for reading." << endl;
	}

}

void displayMainMenuadmin() {
	int choice = 0;
	do
	{
		cout << "=============================" << endl;
		cout << "  Medical Store Management System" << endl;
		cout << "=============================" << endl;
		cout << "1. View all admin details." << endl;
		cout << "2. View all Counter Manager details" << endl;
		cout << "3. View all Customer details" << endl;
		cout << "4. Display All Categories" << endl;
		cout << "5. Display All Medicines" << endl;
		cout << "6. Add New Medicine" << endl;
		cout << "7. Add New Category" << endl;
		cout << "8. Logout" << endl;
		cout << "9. Exit" << endl;
		cout << "=============================" << endl;
		cout << "Please choose an option (1-9): ";
		cin >> choice;
		Medicine* med = new Medicine;
		string category;
		cin.ignore();
		switch (choice) {
		case 1:
			adminlist.displayAdmin();
			break;
		case 2:
			countermanagerlist.displayCustomerManager();
			break;
		case 3:
			customerlist.displayCustomers();
			break;
		case 4:
			categories.displaytitles();
			break;
		case 5:
			categories.display();
			break;
		case 6:
			cout << "Add Medicine" << endl;
			med->create();
			insertmedicine(*med);
			break;
		case 7:
			cout << "Add new Category:" << endl;
			cout << "Enter the new Category: "; cin >> category;
			categories.insert(Category(hashing(category), category));
			break;
		case 8:
			return;
			break;
		case 9:
			exit(0);
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}

	} while (choice != 9);

}

void displayMainMenuCustomer() {
	int choice = 0;
	do
	{
		cout << "=============================" << endl;
		cout << "  Medical Store Management System" << endl;
		cout << "=============================" << endl;
		cout << "Balance: " << active.balance << endl;
		cout << "1. Request for Some Medicine." << endl;
		cout << "2. Recharge into your account." << endl;
		cout << "3. View my Previous orders" << endl;
		cout << "4. Logout" << endl;
		cout << "5. Exit" << endl;
		cout << "=============================" << endl;
		cout << "Please choose an option (1-5): ";
		cin >> choice;
		string str;
		Medicine* med;
		switch (choice) {
		case 1:
			cout << "Medicine Search" << endl;
			cout << "Input the name of medicine: "; cin >> str;
			cout << hashing(str) << endl;
			med = categories.printtitle(str);
			if (med != nullptr) {
				med->display();
				if (med->price != 0) {
					int quant = 0, count = 0;
					do
					{
						if (count) {
							cout << "Invalid Quantity!" << endl;
						}
						cout << "Enter Quantity or input zero to cancel order: "; cin >> quant;
					} while (quant > med->quantity || quant < 0 || quant*med->price>active.balance);
					if (quant > 0) {
						cout << "Total Bill is : " << quant * med->price << endl;
						int choice1 = 0;
						do
						{
							cout << "Do you want to pay now?\n 1. Yes\n 2.No\nInput the choice : "; cin >> choice1;
						} while (choice1 < 1 || choice1>2);
						if (choice1 == 1) {
							customerlist.updatebalance(active.username, active.password, active.balance - quant * med->price);
							active.balance = active.balance - quant * med->price;
							RequestNode<Request>* r = requestlist.requestholder(active.username);
							string manager_random = countermanagerlist.returnRandom()->manager->getUsername();
							countermanagerlist.updatebalance(manager_random, (countermanagerlist.getbalance(manager_random) + quant * med->price));
							transaction* t = new transaction(active.username, med->name, med->category, manager_random, quant * med->price, true, true);
							med->quantity -= quant;
								r->data.insertinhistory(t);
								customerlist.saveToFile("customer.txt");
								emptyFile("medicines.txt");
								categories.traversecat();

						}

					}
				}
				else {
					cout << "Medicine is out of stock, visit later." << endl;
				}
			}
			else {
				cout << "No such medicine in Database" << endl;
			}

			break;
		case 2:
			chargeMoney();
			customerlist.updatebalance(active.username, active.password, active.balance);
			customerlist.saveToFile("customer.txt");
			break;
		case 3:
			requestlist.printdetailsCustomer(active.username);
			break;
		case 4:
			return;
			break;
		case 5:

			exit(0);
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}

	} while (choice != 5);

}

void displayMainMenuCustomerManager() {
	int choice = 0;
	do
	{
		cout << "=============================" << endl;
		cout << "  Medical Store Management System" << endl;
		cout << "=============================" << endl;
		cout << "Current worth : " << active.balance << endl;
		cout << "1. View all my requests." << endl;
		cout << "2. Search for Medicine." << endl;
		cout << "3. Search for Category." << endl;
		cout << "4. Logout" << endl;
		cout << "5. Exit" << endl;
		cout << "=============================" << endl;
		cout << "Please choose an option (1-5): ";
		cin >> choice;
		string str;
		Medicine* med;
		switch (choice) {
		case 1:
			cout << "All transactions managed: " << endl;
			requestlist.printdetailsCounterManager(active.username);
			break;
		case 2:
			cout << "Medicine Search" << endl;
			cout << "Input the name of medicine: "; cin >> str;
			med = categories.printtitle(str);
			if (med != nullptr) {
				med->display();
			}
			else {
				cout << "No such Medicine in database" << endl;
			}
			break;
		case 3:
			cout << "Category Search" << endl;
			cout << "Input the name of category: "; cin >> str;
			categories.printmatch(str);

			break;
		case 4:
			return;
			break;
		case 5:
			exit(0);
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}



	} while (choice != 9);

}



int main() {
	loadTransactionsFromFile();
	loadData();
	do {
		//clearScreen();
		if (accessible()) {
			cout << "Welcome to the System, you logged in successfully." << endl;
			if (active.isadmin) {
				displayMainMenuadmin();
			}
			else if (active.iscountermanager) {
				displayMainMenuCustomerManager();
			}
			else if (active.iscustomer) {
				displayMainMenuCustomer();
			}
		}
		//clearScreen();
	} while (true);

	return 0;
}




//
//int main() {
//	loadTransactionsFromFile();
//	requestlist.printdetailsCustomer("hashir");
//
//	cout << "End customer" << endl;
//
//}
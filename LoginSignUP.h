#pragma once
#include "Admin.h"
#include "CounterManager.h"
#include "Customer.h"
#include "User.h"


string toLowerCase(const std::string& input) {
	string result = input;
	for (char& c : result) {
		if (c >= 'A' && c <= 'Z') {
			c += ('a' - 'A');
		}
	}
	return result;
}


bool Login() {
	string username, password, usertype;
	cout << "Enter Username : "; cin >> username;
	cout << "Enter Password : "; cin >> password;
	int a = 0;
	do {
		if (a != 0)
		{
			cout << endl << endl << endl << "Invalid User Type. Please try again!" << endl << endl;
		}
		a++;
		cout << "Enter the user type, \'Customer\', \'CustomerManager\' or \'Admin\' : "; cin >> usertype;
	} while (!(usertype != "customer" || usertype != "customermanager" || usertype != "admin"));
	usertype = toLowerCase(usertype);
	if (usertype == "customer") {

		if (customerlist.searchCustomerList(username, password)) {
			active.iscustomer = true;
			active.isadmin = false;
			active.iscountermanager = false;
			active.username = username;
			active.password = password;
			active.balance = customerlist.getbalance(username, password);
			return true;
		}
		return false;

	}
	else if (usertype == "customermanager") {

		if (countermanagerlist.searchCustomerManager(username, password)) {
			active.iscustomer = false;
			active.isadmin = false;
			active.iscountermanager = true;
			active.username = username;
			active.password = password;
			active.balance = countermanagerlist.getbalance(username);
			countermanagerlist.count++;
			return true;
		}
		return false;
	}
	else if (usertype == "admin") {

		if (adminlist.searchAdminList(username, password)) {
			active.iscustomer =false;
			active.isadmin = true;
			active.iscountermanager = false;
			active.username = username;
			active.password = password;
			return true;
		}
		return false;
	}

	return false;
}



void SignUp() {
	string username, password, usertype;
	int a = 0;
	cout << "Enter Username : "; cin >> username;
	cout << "Enter Password : "; cin >> password;
	do {
		if (a != 0)
		{
			cout << endl << endl << endl << "Invalid User Type. Please try again!" << endl << endl;
		}
		a++;
		cout << "Enter the user type, \'Customer\', \'CustomerManager\' or \'Admin\' : "; cin >> usertype;
	} while (!(usertype != "customer" || usertype != "customermanager" || usertype != "admin"));
	usertype = toLowerCase(usertype);
	if (usertype == "customer") {
		customerlist.addCustomer(new Customer(username,password ));
	}
	else if (usertype == "customermanager") {
		countermanagerlist.addCustomerManager(new CounterManager(username, password));
	}
	else if (usertype == "admin") {
		adminlist.addAdmin(new Admin(username, password));
	}


}
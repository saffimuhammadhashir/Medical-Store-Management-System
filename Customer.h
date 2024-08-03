#pragma once
#include "User.h"

class Customer : public User {
public:
    int balance=0;
    Customer(string uname, string pwd) : User(uname, pwd) {}
    void displayRole() override {
        cout << "Role: Customer" << endl;
    }
};
struct CustomerNode {
    Customer* customer;
    CustomerNode* next;
};

class CustomerList {
private:
    CustomerNode* head;
public:
    CustomerList() : head(nullptr) {
        loadFromFile();
    }

    void addCustomer(Customer* customer) {
        CustomerNode* newNode = new CustomerNode();
        newNode->customer = customer;
        newNode->next = head;
        head = newNode;
        saveToFile("customer.txt");
    }

    void displayCustomers() {
        CustomerNode* current = head;
        while (current != nullptr) {
            cout << "Username: " << current->customer->getUsername() << endl;
            current->customer->displayRole();
            current = current->next;
        }
    }

    bool searchCustomerList(string username, string password) {
        CustomerNode* current = head;
        while (current != nullptr) {
            if (current->customer->getUsername() == username && current->customer->getPassword() == password) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename, ios::trunc);
        if (file.is_open()) {
            CustomerNode* current = head;
            while (current != nullptr) {
                file << current->customer->getUsername() << " " << current->customer->getPassword()<<" "<<current->customer->balance << endl;
                current = current->next;
            }
            file.close();
        }
        else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    void loadFromFile() {
        ifstream file("customer.txt");

       head = nullptr;
        CustomerNode* tail = nullptr;

        string username, password,balance;

        while (file >> username >> password>>balance) {
            Customer* customer = new Customer(username, password);
            customer->balance = stoi(balance);
            CustomerNode* newNode = new CustomerNode();
            newNode->customer = customer;
            newNode->next = nullptr;
            Request* r = new Request(username);

            requestlist.insert(*r);
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }

        }

        file.close();
      
    }

    int getbalance(string username, string password) {
        CustomerNode* current = head;
        while (current != nullptr) {
            if (current->customer->getUsername() == username && current->customer->getPassword() == password) {
                return current->customer->balance;
            }
            current = current->next;
        }
        return 0;
    }
    void updatebalance(string username, string password,int balance) {
        CustomerNode* current = head;
        while (current != nullptr) {
            if (current->customer->getUsername() == username && current->customer->getPassword() == password) {
                 current->customer->balance=balance;
                 return;
            }
            current = current->next;
        }
        return;
    }
};
CustomerList customerlist;
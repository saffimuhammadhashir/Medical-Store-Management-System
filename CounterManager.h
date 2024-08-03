#pragma once
#include "User.h"
class CounterManager : public User {
public:
    CounterManager(string uname, string pwd) : User(uname, pwd) {}
    int balance = 0;
    void displayRole() override {
        cout << "Role: Customer" << endl;
    }
    string getPassword() {
        return password;
    }
};
struct CounterManagerNode {
    CounterManager* manager;
    CounterManagerNode* next;
};

class CounterManagerList {
private:
    CounterManagerNode* head;
public:
    int count = 0;
    CounterManagerList() : head(nullptr) {
        loadFromFile();
    }

    void addCustomerManager(CounterManager* manager) {
        CounterManagerNode* newNode = new CounterManagerNode();
        newNode->manager = manager;
        newNode->next = head;
        head = newNode;
        saveToFile("countermanager.txt");
    }
    CounterManagerNode* returnRandom() {
        int index = rand() % count + 1,i=0;
        CounterManagerNode* curr = head;
        while (curr->next!=nullptr)
        {
            if (index == i) {
                return curr;
            }
            i++;
            curr = curr->next;
        }

    }
    void displayCustomerManager() {
        CounterManagerNode* current = head;
        while (current != nullptr) {
            cout << "Username: " << current->manager->getUsername() << endl;
            current->manager->displayRole();
            current = current->next;
        }
    }
    bool searchCustomerManager(string username,string password) {
        CounterManagerNode* current = head;
        while (current != nullptr) {
            if (current->manager->getUsername() == username && current->manager->getPassword() == password) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename, ios::trunc);
        if (file.is_open()) {
            CounterManagerNode* current = head;
            while (current != nullptr) {
                file << current->manager->getUsername() << " " << current->manager->getPassword() << endl;
                current = current->next;
            }
            file.close();
        }
        else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    void loadFromFile() {
        ifstream file("countermanager.txt");

        head = nullptr;
        CounterManagerNode* tail = nullptr;

        string username, password;

        while (file >> username >> password) {
            CounterManager* customer = new CounterManager(username, password);

            CounterManagerNode* newNode = new CounterManagerNode();
            newNode->manager = customer;
            newNode->next = nullptr;

            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
            count++;
        }

        file.close();

    }
    int getbalance(string username) {
        CounterManagerNode* current = head;
        while (current != nullptr) {
            if (current->manager->getUsername() == username ) {
                return current->manager->balance;
            }
            current = current->next;
        }
        return 0;
    }
    void updatebalance(string username, int balance) {
        CounterManagerNode* current = head;
        while (current != nullptr) {
            if (current->manager->getUsername() == username ) {
                current->manager->balance = balance;
                return;
            }
            current = current->next;
        }
        return;
    }
};
CounterManagerList countermanagerlist;
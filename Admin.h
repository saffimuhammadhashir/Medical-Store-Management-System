#pragma once
#include "User.h"
class Admin : public User {
public:
    Admin(string uname, string pwd) : User(uname, pwd) {}
    void displayRole() override {
        cout << "Role: Customer" << endl;
    }
};
struct AdminNode {
    Admin* admin;
    AdminNode* next;
};

class AdminList {
private:
    AdminNode* head;
public:
    AdminList() : head(nullptr) {
        loadFromFile();
    }

    void addAdmin(Admin* customer) {
        AdminNode* newNode = new AdminNode();
        newNode->admin = customer;
        newNode->next = head;
        head = newNode;
        saveToFile("admin.txt");
    }

    void displayAdmin() {
        AdminNode* current = head;
        while (current != nullptr) {
            cout << "Username: " << current->admin->getUsername() << endl;
            current->admin->displayRole();
            current = current->next;
        }
    }


    bool searchAdminList(string username, string password) {
        AdminNode* current = head;
        while (current != nullptr) {
            if (current->admin->getUsername() == username && current->admin->getPassword() == password) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void saveToFile( string filename) {
        ofstream file(filename, ios::trunc);
        if (file.is_open()) {
            AdminNode* current = head;
            while (current != nullptr) {
                file << current->admin->getUsername() << " " << current->admin->getPassword() << endl;
                current = current->next;
            }
            file.close();
        }
        else {
            cout << "Unable to open file for writing." << endl;
        }
    }


    void loadFromFile() {
        ifstream file("admin.txt");

        head = nullptr;
        AdminNode* tail = nullptr;

        string username, password;

        while (file >> username >> password) {
            Admin* customer = new Admin(username, password);

            AdminNode* newNode = new AdminNode();
            newNode->admin = customer;
            newNode->next = nullptr;

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
};
AdminList adminlist;
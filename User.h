#pragma once
#include "AllHeaders.h"
#include "request.h"
class User {
protected:
    string username;
    string password;
public:
    User(string uname, string pwd) : username(uname), password(pwd) {}
    virtual void displayRole() = 0;
    string getUsername() { return username; }
    string getPassword() { return password; }
};


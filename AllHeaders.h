#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
using namespace std;
class activeuser {
public:
    string username;
    string password;
    int balance = 0;
    bool isadmin = false, iscountermanager = false, iscustomer = false;
    activeuser(){}

};
activeuser active;

long long hashing(const string& input) {
    const unsigned int prime = 31;
    long long hash = 0;

    for (char c : input) {
        hash = hash * prime + c;
    }

    return hash;
}

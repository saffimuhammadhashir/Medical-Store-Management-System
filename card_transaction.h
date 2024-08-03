#pragma once
#include "AllHeaders.h"
bool isValidCardNumber(const string& cardNumber) {
    return regex_match(cardNumber, regex(R"(\d{16})"));
}

bool isValidExpiryDate(const string& expiryDate) {
    return regex_match(expiryDate, regex(R"((0[1-9]|1[0-2])\/\d{2})"));
}

bool isValidCVV(const string& cvv) {
    return regex_match(cvv, regex(R"(\d{3})"));
}

bool isValidAmount(const string& amount) {
    return regex_match(amount, regex(R"(\d+(\.\d{1,2})?)"));
}

void getCardDetails(string& cardNumber, string& expiryDate, string& cvv) {
    cout << "Enter your card number (16 digits): ";
    cin >> cardNumber;
    while (!isValidCardNumber(cardNumber)) {
        cout << "Invalid card number. Please enter a 16-digit card number: ";
        cin >> cardNumber;
    }

    cout << "Enter expiry date (MM/YY): ";
    cin >> expiryDate;
    while (!isValidExpiryDate(expiryDate)) {
        cout << "Invalid expiry date. Please enter a valid expiry date (MM/YY): ";
        cin >> expiryDate;
    }

    cout << "Enter CVV (3 digits): ";
    cin >> cvv;
    while (!isValidCVV(cvv)) {
        cout << "Invalid CVV. Please enter a 3-digit CVV: ";
        cin >> cvv;
    }
}

void chargeMoney() {
    string cardNumber, expiryDate, cvv;
    getCardDetails(cardNumber, expiryDate, cvv);

    bool isValidCard = true;

    if (isValidCard) {
        string amount;
        cout << "Enter the amount to charge: ";
        cin >> amount;
        while (!isValidAmount(amount)) {
            cout << "Invalid amount. Please enter a valid amount (e.g., 100.00): ";
            cin >> amount;
        }

        cout << "Charging " << amount << " to card " << cardNumber
            << " with expiry date " << expiryDate << " and CVV " << cvv << "." << endl;
        active.balance = active.balance + stoi(amount);

    }
    else {
        cout << "Invalid card details. Please try again." << endl;
    }
}
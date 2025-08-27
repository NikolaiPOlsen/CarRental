#include "../h/addcustomer.h"
#include <iostream>

void addCustomer(SQLite::Database& db) {
    std::string GivenName, FamilyName, Email, Phonenumber;

    std::cout << "Fill inn the following information:\n";
    std::cout << "\n";

    std::cout << "Given name: ";
    std::cin >> GivenName;
    std::cout << "Family name: ";
    std::cin >> FamilyName;
    std::cout << "Email: ";
    std::cin >> Email;
    std::cout << "Phonenumber: ";
    std::cin >> Phonenumber;

    SQLite::Statement insert(db, "INSERT INTO customers (GivenName, FamilyName, Email, Phonenumber) VALUES (?, ?, ?, ?)");
    insert.bind(1, GivenName);
    insert.bind(2, FamilyName);
    insert.bind(3, Email);
    insert.bind(4, Phonenumber);
    insert.exec();

    std::cout << "Customer was succesfully added!\n";
}


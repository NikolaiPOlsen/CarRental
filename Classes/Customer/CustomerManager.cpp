#include <iostream>
#include "CustomerManager.h"

void CustomerManager::addCustomer(SQLite::Database& db) {
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

void CustomerManager::editCustomer(SQLite::Database& db) {

    std::string GivenName, FamilyName, Email, Phonenumber;
    int customerid;

    std::cout << "Enter customer id: ";
    std::cin >> customerid;

    std::cout << "Given name: ";
    std::cin >> GivenName;
    std::cout << "Family name: ";
    std::cin >> FamilyName;
    std::cout << "Email: ";
    std::cin >> Email;
    std::cout << "Phonenumber: ";
    std::cin >> Phonenumber;

    SQLite::Statement query(db, "UPDATE customers SET GivenName=?, FamilyName=?, Email=?, Phonenumber=? WHERE customerid=?");

    query.bind(1, GivenName);
    query.bind(2, FamilyName);
    query.bind(3, Email);
    query.bind(4, Phonenumber);
    query.bind(5, customerid);
    query.exec();

    std::cout << "Customer was succesfully updated!" << std::endl;
}

void CustomerManager::removeCustomer(SQLite::Database& db) {
    int customerid;

    std::cout << "Enter customer id: ";
    std::cin >> customerid;

    SQLite::Statement query(db, "DELETE from customers WHERE customerid=?");
    query.bind(1, customerid);
    query.exec();

    std::cout << "Customer was succesfully removed!" << std::endl;

}
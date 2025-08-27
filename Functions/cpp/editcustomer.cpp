#include "../h/editcustomer.h"
#include <iostream>

void editCustomer(SQLite::Database& db) {

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
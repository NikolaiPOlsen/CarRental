#include "../h/removecustomer.h"
#include <iostream>

void removeCustomer(SQLite::Database& db) {
    int customerid;

    std::cout << "Enter customer id: ";
    std::cin >> customerid;

    SQLite::Statement query(db, "DELETE from customers WHERE customerid=?");
    query.bind(1, customerid);
    query.exec();

    std::cout << "Customer was succesfully removed!" << std::endl;

}
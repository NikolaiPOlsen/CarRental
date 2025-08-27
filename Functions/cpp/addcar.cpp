#include "../h/addcar.h"
#include <iostream>
#include <SQlitecpp/SQLiteCpp.h>

void addCar(SQLite::Database& db) {
    std::string regnr, brand, model;
    int year, status;

    std::cout << "Fill inn the following information:\n";
    std::cout << "\n";

    std::cout << "Registration: ";
    std::cin >> regnr;
    std::cout << "Brand: ";
    std::cin >> brand;
    std::cout << "Model: ";
    std::cin >> model;
    std::cout << "Year: ";
    std::cin >> year;
    std::cout << "Status (Rented = 1, Not rented = 0): ";
    std::cin >> status;

    SQLite::Statement insert(db, "INSERT INTO Cars (regnr, brand, model, year, status) VALUES (?, ?, ?, ?, ?)");
    insert.bind(1, regnr);
    insert.bind(2, brand);
    insert.bind(3, model);
    insert.bind(4, year);
    insert.bind(5, status);
    insert.exec();

    std::cout << "Car was succesfully added!\n";
}

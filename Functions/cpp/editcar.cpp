#include "../h/editcar.h"
#include <iostream>

void editCar(SQLite::Database& db) {
    std::string regnr, brand, model;
    int carid, year;

    std::cout << "Enter car id: ";
    std::cin >> carid;
    std::cout << "Registration: ";
    std::cin >> regnr;
    std::cout << "Brand: ";
    std::cin >> brand;
    std::cout << "Model: ";
    std::cin >> model;
    std::cout << "Year: ";
    std::cin >> year;

    SQLite::Statement query(db, "UPDATE cars SET regnr=?, brand=?, model=?, year=? WHERE carid=?");

    query.bind(1, regnr);
    query.bind(2, brand);
    query.bind(3, model);
    query.bind(4, year);
    query.bind(5, carid);
    query.exec();

    std::cout << "Car was succesfully updated!" << std::endl;
}
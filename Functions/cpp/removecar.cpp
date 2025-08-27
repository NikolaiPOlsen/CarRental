#include "../h/removecar.h"
#include <iostream>

void removeCar(SQLite::Database& db) {
    int carid;

    std::cout << "Enter car id: ";
    std::cin >> carid;

    SQLite::Statement query(db, "DELETE from cars WHERE carid=?");
    query.bind(1, carid);
    query.exec();

    std::cout << "Car was succesfully removed!" << std::endl;
}

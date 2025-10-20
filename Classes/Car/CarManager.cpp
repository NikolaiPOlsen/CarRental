#include <iostream>
#include "CarManager.h"
#include "../Search/SearchEngineCar.h"

void CarManager::addCar(SQLite::Database& db) {
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

void CarManager::editCar(SQLite::Database& db) {
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

void CarManager::removeCar(SQLite::Database& db) {
    int carid;

    std::cout << "Enter car id: ";
    std::cin >> carid;

    SQLite::Statement query(db, "DELETE from cars WHERE carid=?");
    query.bind(1, carid);
    query.exec();

    std::cout << "Car was succesfully removed!" << std::endl;
}

void CarManager::assignCar(SQLite::Database& db) {
    int choice;
    SearchEngineCar se;

    while (true) {
        std::cout << "1. Search using car id: \n";
        std::cout << "2. Search using car brand: \n";
        std::cout << "3. Search using car registration number: \n";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                se.searchCarID(db);
                return;
            }
            case 2: {
                se.searchCarBrand(db);
                return;
            }
            case 3: {
                se.searchRegNr(db);
                return;
            }
            default: {
                std::cout << "Invalid choice!" << std::endl;
                break;
            }
        }
    }
}

void CarManager::unassignCar(SQLite::Database& db) {
    int car_id, customer_id;
    std::string start_date, end_date, regnr, GivenName;

    std::cout << "Enter the car id: ";
    std::cin >> car_id;

    SQLite::Statement s(db, "SELECT status FROM cars WHERE carid=?");
    s.bind(1, car_id);
    if (!s.executeStep()) {
        std::cout<<"Car could not be found\n";
    }
    int status = s.getColumn(0).getInt();
    if (status != 1){
        std::cout << "Car is not rented to a customer!";

    }
    else {
        SQLite::Statement rental(db, "DELETE FROM rentals WHERE car_id=?");
        rental.bind(1, car_id);
        rental.exec();

        SQLite::Statement s(db, "UPDATE cars SET status=? WHERE carid=?");
        int reset_status = 0;
        s.bind(1, reset_status);
        s.bind(2, car_id);
        s.exec();

        std::cout << "Car was successfully unassigned!\n";
    }

}
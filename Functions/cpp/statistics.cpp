#include "../h/statistics.h"
#include <iostream>

void statistics(SQLite::Database& db) {

    SQLite::Statement customers(db, "SELECT COUNT(*) FROM customers");
    customers.executeStep();
    int customerCount = customers.getColumn(0).getInt();
    std::cout << "Total customers: " << customerCount << std::endl;

    SQLite::Statement cars(db, "SELECT COUNT(*) FROM cars");
    cars.executeStep();
    int carCount = cars.getColumn(0).getInt();
    std::cout << "Total cars: " << carCount << std::endl;

    SQLite::Statement active_rentals(db, "SELECT COUNT(*) FROM rentals WHERE end_date >= date('now')");
    active_rentals.executeStep();
    int activeRentalCount = active_rentals.getColumn(0).getInt();
    std::cout << "Active rentals: " << activeRentalCount << std::endl;

    SQLite::Statement completed_rentals(db, "SELECT COUNT(*) FROM rentals WHERE end_date < date('now')");
    completed_rentals.executeStep();
    int completedRentalCount = completed_rentals.getColumn(0).getInt();
    std::cout << "Completed rentals: " << completedRentalCount << std::endl;

    std::cout << "\n" << std::endl;
}

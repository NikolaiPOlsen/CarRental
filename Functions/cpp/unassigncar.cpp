#include "../h/unassigncar.h"
#include <iostream>

void unassignCar(SQLite::Database& db) {
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
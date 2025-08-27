#include "../h/assigncar.h"
#include <iostream>

void assignCar(SQLite::Database& db) {
    int car_id, customer_id;
    std::string start_date, end_date, regnr, GivenName;

    std::cout << "Enter the car id: ";
    std::cin >> car_id;

    SQLite::Statement s(db, "SELECT status FROM cars WHERE carid=?");
    s.bind(1, car_id);
    if (!s.executeStep()) {
        std::cout<<"Car could not be found\n";
    }
    int statuscar = s.getColumn(0).getInt();

    if (statuscar == 1) {
        std::cout << "The car is already rented out!\n" << std::endl;
    }
    else {
        int status = s.getColumn(0).getInt();

        if (status != 1) {
            std::cout << "Enter the customer id: ";
            std::cin >> customer_id;

            int customerid = customer_id;
            SQLite::Statement customer(db, "SELECT 1 FROM customers WHERE customerid=?");
            customer.bind(1, customerid);
            bool customer_found = customer.executeStep();
            if (!customer_found) {
                std::cout << "Customer could not be found!\n";
            }
            else {
                SQLite::Statement check(db, "SELECT 1 FROM rentals WHERE customer_id=?");
                check.bind(1, customerid);
                if (check.executeStep()) {
                    std::cout << "This customer is already renting a vehicle!\n";
                }
                else {
                    std::cout << "Rental start: ";
                    std::cin >> start_date;

                    std::cout << "Rental end: ";
                    std::cin >> end_date;

                    SQLite::Statement insert(db, "INSERT into rentals (car_id, customer_id, start_date, end_date) VALUES (?, ?, ?, ?)");
                    insert.bind(1, car_id);
                    insert.bind(2, customer_id);
                    insert.bind(3, start_date);
                    insert.bind(4, end_date);
                    insert.exec();

                        SQLite::Statement query(db, "UPDATE cars SET status=1 WHERE carid=?");
                        query.bind(1, car_id);
                        query.exec();

                        std::cout << "The car has successfully been assigned to the customer!\n" << std::endl;
                }
            }
        }
    }

}
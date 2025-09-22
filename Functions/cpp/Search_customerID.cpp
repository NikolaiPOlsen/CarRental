#include "../h/Search_customerID.h"
#include <iostream>

void searchCustomerID(SQLite::Database& db, const int car_id) {
    int customer_id;
    std::string start_date, end_date, regnr, GivenName;

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

            if (end_date < start_date) {
                std::cout << "End date cannot be before start date!\n";
                std::cout << "Please enter the end date again!\n";
                std::cin >> end_date;
            }

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
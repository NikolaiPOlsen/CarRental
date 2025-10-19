#include "../h/search_name.h"
#include <iostream>

#include "SQLiteCpp/Database.h"

void searchCustomerName(SQLite::Database &db, const int car_id) {
    int customer_id;
    std::string start_date, end_date, regnr, GivenName;

    std::string name;
    std::cout << "Enter the name of the customer: ";
    std::cin >> name;
    std::string like = "%" + name + "%";

    int count = 0;
    std::string customer_name = name;
    SQLite::Statement customer(db, "SELECT COUNT(*) FROM customers WHERE GivenName=? OR GivenName LIKE ?");
    customer.bind(1, customer_name);
    customer.bind(2, like);
    if (customer.executeStep()) {
        count = customer.getColumn(0).getInt();
    }

    if (count == 0) {
        std::cout << "Customer could not be found!";
        return;
    }

    if (count > 1) {
        std::cout << "Multiple customers found with that name: " << std::endl;
        SQLite::Statement list(db, "SELECT customerid, GivenName, FamilyName FROM customers WHERE GivenName=? OR GivenName LIKE ?");
        list.bind(1, customer_name);
        list.bind(2, like);
        while (list.executeStep()) {
            std::cout << list.getColumn(0).getInt() << ", Name: " << list.getColumn(1).getString() << " " << list.getColumn(2).getString() << std::endl;
        }
        std::cout << "Please enter the customer you want to assign the car to: ";
        std::cin >> customer_id;
    }

    else {
        SQLite::Statement Customer(db, "SELECT customerid FROM customers WHERE GivenName=? or GivenName LIKE ?");
        Customer.bind(1, customer_name);
        Customer.bind(2, like);
        Customer.executeStep();
        customer_id = Customer.getColumn(0).getInt();

        SQLite::Statement list(db, "SELECT GivenName, FamilyName FROM customers WHERE customerid=?");
        list.bind(1, customer_id);
        list.executeStep();
        std::cout << "Customer selected -> " << "Name: " << list.getColumn(0).getString() << " " << list.getColumn(1).getString() << std::endl;
        }

        SQLite::Statement check(db, "SELECT 1 FROM rentals WHERE customer_id=?");
        check.bind(1, customer_id);
        if (check.executeStep()) {
            std::cout << "This customer is already renting a vehicle!\n";
        }

        else {
            std::cout << "Rental start (YYYY-MM-DD): ";
            std::cin >> start_date;

            std::cout << "Rental end (YYYY-MM-DD): ";
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
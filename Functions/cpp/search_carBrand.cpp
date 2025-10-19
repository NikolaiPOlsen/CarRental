#include "../h/search_carBrand.h"
#include "../h/search_customerID.h"
#include "../h/search_name.h"
#include <iostream>

void searchCarBrand(SQLite::Database& db) {
    std::string car_brand;
    int car_id;

    std::cout << "Enter car brand: ";
    std::cin.ignore();
    std::cin >> car_brand;
    std::string like = "%" + car_brand + "%";

    int count = 0;
    std::string brand = car_brand;
    SQLite::Statement c(db, "SELECT COUNT(*) FROM cars WHERE (brand=? OR brand LIKE ?) AND status != 1");
    c.bind(1, brand);
    c.bind(2, like);
    if (c.executeStep()) {
        count = c.getColumn(0).getInt();
    }

    if (count == 0) {
        std::cout << "Cars are all rented out or could not be found!\n";
        std::cout << "Returning to menu\n";
        return;
    }

    if (count > 1) {
        std::cout << "Multiple customers found with that name: " << std::endl;
        SQLite::Statement list(db, "SELECT carid, regnr, brand, model, year FROM cars WHERE (brand=? OR brand LIKE ?) AND status != 1");
        list.bind(1, brand);
        list.bind(2, like);
        while (list.executeStep()) {
                std::cout << list.getColumn(0).getInt() << ", Registration: " << list.getColumn(1).getString() << ", Brand: " << list.getColumn(2).getString() << ", Model: " << list.getColumn(3).getString() << ", Year: " << list.getColumn(4).getString() << std::endl;
        }
        std::cout << "Please enter the ID you want to assign a customer to: ";
        std::cin >> car_id;
        }

    else {
        SQLite::Statement car(db, "SELECT carid FROM cars WHERE (brand=? OR brand LIKE ?) AND status != 1");
        car.bind(1, brand);
        car.bind(2, like);
        car.executeStep();
        car_id = car.getColumn(0).getInt();

        SQLite::Statement list(db, "SELECT regnr, brand, model, year FROM cars WHERE carid=?");
        list.bind(1, car_id);
        list.executeStep();
        std::cout << "Car selected -> " << "Registration: " << list.getColumn(0).getString() << ", Brand: " << list.getColumn(1).getString() << ", Model: " << list.getColumn(2).getString() << ", Year: " << list.getColumn(3).getString() <<  std::endl;
    }

    SQLite::Statement s(db, "SELECT status FROM cars WHERE carid=?");
    s.bind(1, car_id);
    if (!s.executeStep()) {
        std::cout<<"Car could not be found\n";
        return;
    }

        int status = s.getColumn(0).getInt();

        if (status != 1) {
            int choice;
            while (true) {
                std::cout << "1. Search using customer id: \n";
                std::cout << "2. Search using customer name: \n";
                std::cin >> choice;

                switch (choice) {
                    case 1: {
                        searchCustomerID(db, car_id);
                        return;
                    }
                    case 2: {
                        searchCustomerName(db, car_id);
                        return;
                    }
                    default: {
                        std::cout<<"Invalid choice\n";
                        break;
                    }
                }
            }
        }
}
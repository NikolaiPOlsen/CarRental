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

    std::string brand = car_brand;
    SQLite::Statement c(db, "SELECT carid FROM cars WHERE brand=? OR brand LIKE ?");
    c.bind(1, brand);
    c.bind(2, like);
    bool car_found = c.executeStep();
    if (!car_found) {
        std::cout << "Car could not be found!\n";
        std::cout << "Returning to menu\n";
        return;
    }
    else {
        int count = c.getColumn(0);
        if (count > 1) {
            std::cout << "Multiple customers found with that name: " << std::endl;
            SQLite::Statement list(db, "SELECT carid, regnr, brand, model, year FROM cars WHERE brand=? OR brand LIKE ?");
            list.bind(1, brand);
            list.bind(2, like);
            while (list.executeStep()) {
                std::cout << list.getColumn(0).getInt() << ", Registration: " << list.getColumn(1).getString() << ", Brand: " << list.getColumn(2).getString() << ", Model: " << list.getColumn(3).getString() << ", Year: " << list.getColumn(4).getString() << std::endl;
                std::cout << "Please enter the id you want to assign a customer to: ";
                std::cin >> car_id;
            }
        }

        SQLite::Statement s(db, "SELECT status FROM cars WHERE carid=?");
        s.bind(1, car_id);
        if (!s.executeStep()) {
            std::cout<<"Car could not be found\n";
        }
        int statusCar = s.getColumn(0).getInt();

        if (statusCar == 1) {
            std::cout << "The car is already rented out!\n" << std::endl;
        }
        else {
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
    }
}
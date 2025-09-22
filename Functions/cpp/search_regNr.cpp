#include "../h/search_regNr.h"
#include "../h/search_customerID.h"
#include "../h/search_name.h"
#include <iostream>

void searchRegNr(SQLite::Database& db) {
     std::string regnumber;
    int car_id;

    std::cout << "Enter registration number: ";
    std::cin.ignore();
    std::cin >> regnumber;
    std::string like = "%" + regnumber + "%";

    std::string brand = regnumber;
    SQLite::Statement car(db, "SELECT carid FROM cars WHERE regnr=? OR regnr LIKE ?");
    car.bind(1, brand);
    car.bind(2, like);
    bool car_found = car.executeStep();
    while (!car_found) {
        std::cout << "Car could not be found!\n";
        std::cout << "Returning to menu\n";
        return;
    }

        int count = car.getColumn(0);
        if (count > 1) {
            std::cout << "Multiple customers found with that name: " << std::endl;
            SQLite::Statement list(db, "SELECT carid, regnr, brand, model, year FROM cars WHERE regnr=? OR regnr LIKE ?");
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
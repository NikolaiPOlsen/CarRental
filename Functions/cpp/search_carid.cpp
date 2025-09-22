#include "../h/search_carid.h"
#include "../h/search_customerid.h"
#include "../h/search_name.h"
#include <iostream>

void searchCarID(SQLite::Database& db) {
    int car_id;

    std::cout << "Enter the car id: ";
    std::cin >> car_id;

    SQLite::Statement s(db, "SELECT status FROM cars WHERE carid=?");
    s.bind(1, car_id);
    if (!s.executeStep()) {
        std::cout<<"Car could not be found\n";
        return;
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

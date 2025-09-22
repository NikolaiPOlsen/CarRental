#include "../h/assigncar.h"
#include "../h/search_carid.h"
#include "../h/search_carBrand.h"
#include "../h/search_regNr.h"
#include <iostream>

void assignCar(SQLite::Database& db) {
    int choice;
    while (true) {
        std::cout << "1. Search using car id: \n";
        std::cout << "2. Search using car brand: \n";
        std::cout << "3. Search using car registration number: \n";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                searchCarID(db);
                return;
            }
                case 2: {
                searchCarBrand(db);
                return;
            }
                case 3: {
                searchRegNr(db);
                return;
            }
            default: {
                std::cout << "Invalid choice!" << std::endl;
                break;
            }
        }
    }
}

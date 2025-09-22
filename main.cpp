#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include "Functions/h/addcar.h"
#include "Functions/h/addcustomer.h"
#include "Functions/h/assigncar.h"
#include "Functions/h/editcar.h"
#include "Functions/h/editcustomer.h"
#include "Functions/h/removecar.h"
#include "Functions/h/removecustomer.h"
#include "Functions/h/unassigncar.h"

int main() {
    SQLite::Database db("CarRental.sqlite", SQLite::OPEN_READWRITE);
    int choice;

    while (true) {
        std::cout << "Car rental v1.0:" << std::endl;
        std::cout << "1. Add car" << std::endl;
        std::cout << "2. Edit car" << std::endl;
        std::cout << "3. Remove car" << std::endl;
        std::cout << "4. Add customer" << std::endl;
        std::cout << "5. Edit customer" << std::endl;
        std::cout << "6. Remove customer" << std::endl;
        std::cout << "7. Assign car to customer" << std::endl;
        std::cout << "8. Unassign car to customer" << std::endl;
        std::cout << "9. Statistics" << std::endl;
        std::cout << "10. Export" << std::endl;
        std::cout << "11. Import" << std::endl;
        std::cout << "12. Exit" << std::endl;

        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Add car" << std::endl;
                addCar(db);
                break;
            }
            case 2: {
                std::cout << "Edit car" << std::endl;
                editCar(db);
                break;
            }
            case 3: {
                std::cout << "Remove car" << std::endl;
                removeCar(db);
                break;
            }
            case 4: {
                std::cout << "Add customer" << std::endl;
                addCustomer(db);
                break;
            }
            case 5: {
                std::cout << "Edit customer" << std::endl;
                editCustomer(db);
                break;
            }
            case 6: {
                std::cout << "Remove customer" << std::endl;
                removeCustomer(db);
                break;
            }
            case 7: {
                std::cout << "Assign car" << std::endl;
                assignCar(db);
                break;
            }
            case 8: {
                std::cout << "Unassign car" << std::endl;
                unassignCar(db);
                break;
            }
            case 9: {
                std::cout << "Statistics" << std::endl;
                break;
            }
            case 10: {
                std::cout << "Export" << std::endl;
                break;
            }
            case 11: {
                std::cout << "Import" << std::endl;
                break;
            }
            case 12: {
                std::cout << "Bye, see you soon!" << std::endl;
                exit(0);
            }
            default: {
                std::cout << "Invalid choice, program is now exiting!" << std::endl;
            }
        }
    }
}

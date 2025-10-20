#include "iostream"
#include "SearchEngineCar.h"
#include "SearchEngineCustomer.h"

SearchEngineCustomer secust;

void SearchEngineCar::searchCarID(SQLite::Database& db) {
    int car_id;

    std::cout << "Enter the car id: ";
    std::cin >> car_id;

    SQLite::Statement list(db, "SELECT regnr, brand, model, year FROM cars WHERE carid=?");
    list.bind(1, car_id);
    list.executeStep();
    std::cout << "Car selected -> " << "Registration: " << list.getColumn(0).getString() << ", Brand: " << list.getColumn(1).getString() << ", Model: " << list.getColumn(2).getString() << ", Year: " << list.getColumn(3).getString() <<  std::endl;

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
                        secust.searchCustomerID(db, car_id);
                        return;
                    }
                    case 2: {
                        secust.searchCustomerName(db, car_id);
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

void SearchEngineCar::searchCarBrand(SQLite::Database& db) {
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
                        secust.searchCustomerID(db, car_id);
                        return;
                    }
                    case 2: {
                        secust.searchCustomerName(db, car_id);
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

void SearchEngineCar::searchRegNr(SQLite::Database& db) {
    std::string regnumber;
    int car_id;

    std::cout << "Enter registration number: ";
    std::cin.ignore();
    std::cin >> regnumber;
    std::string like = "%" + regnumber + "%";

    int count = 0;
    std::string brand = regnumber;
    SQLite::Statement c(db, "SELECT COUNT(*) FROM cars WHERE (regnr=? OR regnr LIKE ?) AND status != 1");
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

    //Hvis det finnes flere biler meed samme registrering lister den dem opp og gir deg et valg om hvilken du onsker
    if (count > 1) {
        std::cout << "Multiple cars found with that registration: " << std::endl;
        SQLite::Statement list(db, "SELECT carid, regnr, brand, model, year FROM cars WHERE (regnr=? OR regnr LIKE ?) AND status != 1");
        list.bind(1, brand);
        list.bind(2, like);
        while (list.executeStep()) {
                std::cout << list.getColumn(0).getInt() << ", Registration: " << list.getColumn(1).getString() << ", Brand: " << list.getColumn(2).getString() << ", Model: " << list.getColumn(3).getString() << ", Year: " << list.getColumn(4).getString() << std::endl;
        }
        std::cout << "Please enter the ID you want to assign a customer to: ";
        std::cin >> car_id;
    }

    //Hvis kun en bil med lignende registrerings nummer runner denne delen og viser hvilken bil det gjelder.
    else {
        SQLite::Statement car(db, "SELECT carid FROM cars WHERE (regnr=? OR regnr LIKE ?) AND status != 1");
        car.bind(1, regnumber);
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

    //Sjekker om bilen finnes
    if (!s.executeStep()) {
        std::cout<<"Car could not be found\n";
        return;
    }

         int choice;
         while (true) {
              std::cout << "1. Search using customer id: \n";
              std::cout << "2. Search using customer name: \n";
              std::cin >> choice;

              switch (choice) {
                   case 1: {
                        secust.searchCustomerID(db, car_id);
                        return;
                   }
                   case 2: {
                        secust.searchCustomerName(db, car_id);
                        return;
                   }
                   default: {
                        std::cout<<"Invalid choice\n";
                        break;
                   }
              }
         }
}

#ifndef CAR_H
#define CAR_H
#include "SQLiteCpp/Database.h"

class CarManager {
private:

public:
    void addCar(SQLite::Database& db);
    void editCar(SQLite::Database& db);
    void removeCar(SQLite::Database& db);

    void assignCar(SQLite::Database& db);
    void unassignCar(SQLite::Database& db);
};



#endif

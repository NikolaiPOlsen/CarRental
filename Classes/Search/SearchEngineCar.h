#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "SQLiteCpp/SQLiteCpp.h"

class SearchEngineCar {
    private:

    public:
    void searchCarBrand(SQLite::Database& db);
    void searchCarID(SQLite::Database& db);
    void searchRegNr(SQLite::Database& db);
};



#endif //SEARCHENGINE_H

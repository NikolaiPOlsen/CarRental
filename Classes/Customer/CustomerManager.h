#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "SQLiteCpp/Database.h"

class CustomerManager {
    private:

    public:
    void addCustomer(SQLite::Database& db);
    void editCustomer(SQLite::Database& db);
    void removeCustomer(SQLite::Database& db);
};



#endif

#ifndef SEARCHENGINECUSTOMER_H
#define SEARCHENGINECUSTOMER_H
#include "SQLiteCpp/SQLiteCpp.h"



class SearchEngineCustomer {
    private:

    public:
    void searchCustomerID(SQLite::Database& db, const int car_id);
    void searchCustomerName(SQLite::Database &db, const int car_id);

};



#endif
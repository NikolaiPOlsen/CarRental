#ifndef CARRENTAL_SEARCH_CUSTOMERID_H
#define CARRENTAL_SEARCH_CUSTOMERID_H

#include "SQLiteCpp/Database.h"

void searchCustomerID(SQLite::Database& db, const int car_id);

#endif
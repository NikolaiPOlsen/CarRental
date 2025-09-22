#ifndef CARRENTAL_SEARCH_NAME_H
#define CARRENTAL_SEARCH_NAME_H

#include "SQLiteCpp/Database.h"

void searchCustomerName(SQLite::Database& db, const int car_id);

#endif
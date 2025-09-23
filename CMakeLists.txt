cmake_minimum_required(VERSION 3.30)
project(CarRental)

set(CMAKE_CXX_STANDARD 17)

add_library(sqlite3 sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC sqlite3)

add_library(sqlitecpp
        SQLiteCpp/src/Backup.cpp
        SQLiteCpp/src/Column.cpp
        SQLiteCpp/src/Database.cpp
        SQLiteCpp/src/Exception.cpp
        SQLiteCpp/src/Savepoint.cpp
        SQLiteCpp/src/Statement.cpp
        SQLiteCpp/src/Transaction.cpp
)

target_include_directories(sqlitecpp PUBLIC sqlitecpp/include)
target_link_libraries(sqlitecpp sqlite3)

# Hovedprogram
add_executable(CarRental
        main.cpp
        Functions/cpp/addcar.cpp
        Functions/cpp/editcar.cpp
        Functions/cpp/removecar.cpp
        Functions/cpp/addcustomer.cpp
        Functions/cpp/editcustomer.cpp
        Functions/cpp/removecustomer.cpp
        Functions/cpp/assigncar.cpp
        Functions/cpp/unassigncar.cpp
        Functions/cpp/search_carid.cpp
        Functions/cpp/Search_customerID.cpp
        Functions/cpp/search_name.cpp
        Functions/cpp/search_carBrand.cpp
        Functions/cpp/search_regNr.cpp
        Functions/cpp/statistics.cpp
        Functions/cpp/statistics.h
)

target_include_directories(CarRental PRIVATE sqlitecpp/include)
target_link_libraries(CarRental sqlite3 sqlitecpp)
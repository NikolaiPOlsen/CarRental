cmake_minimum_required(VERSION 3.10)
project(CarRental)

set(CMAKE_CXX_STANDARD 17)

# SQLite3 C-bibliotek
add_library(sqlite3 sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC sqlite3)

# SQLiteCpp C++-wrapper
add_library(sqlitecpp
        sqlitecpp/src/Backup.cpp
        sqlitecpp/src/Column.cpp
        sqlitecpp/src/Database.cpp
        sqlitecpp/src/Exception.cpp
        sqlitecpp/src/Savepoint.cpp
        sqlitecpp/src/Statement.cpp
        sqlitecpp/src/Transaction.cpp
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
)

target_link_libraries(CarRental sqlitecpp sqlite3)
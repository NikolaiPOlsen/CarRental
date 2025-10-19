// Functions/cpp/JsonImport.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <rapidjson/document.h>

using namespace std;

void JsonImport(SQLite::Database& db, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open " << filename << endl;
        return;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string jsonStr = buffer.str();
    file.close();

    rapidjson::Document doc;
    if (doc.Parse(jsonStr.c_str()).HasParseError()) {
        cout << "Error parsing JSON file.\n";
        return;
    }

    // Import cars
    if (doc.HasMember("cars") && doc["cars"].IsArray()) {
        SQLite::Statement insert(db, "INSERT OR REPLACE INTO cars (carid, regnr, brand, model, year, status) VALUES (?, ?, ?, ?, ?, ?)");
        for (auto& car : doc["cars"].GetArray()) {
            insert.bind(1, car["carid"].GetInt());
            insert.bind(2, car["regnr"].IsNull() ? nullptr : car["regnr"].GetString());
            insert.bind(3, car["brand"].IsNull() ? nullptr : car["brand"].GetString());
            insert.bind(4, car["model"].IsNull() ? nullptr : car["model"].GetString());
            if (car["year"].IsNull()) insert.bind(5); else insert.bind(5, car["year"].GetInt());
            if (car["status"].IsNull()) insert.bind(6); else insert.bind(6, car["status"].GetInt());
            insert.exec();
            insert.reset();
        }
    }

    // Import customers
    if (doc.HasMember("customers") && doc["customers"].IsArray()) {
        SQLite::Statement insert(db, "INSERT OR REPLACE INTO customers (customerid, GivenName, FamilyName, Email, Phonenumber) VALUES (?, ?, ?, ?, ?)");
        for (auto& cust : doc["customers"].GetArray()) {
            insert.bind(1, cust["customerid"].GetInt());
            insert.bind(2, cust["GivenName"].IsNull() ? nullptr : cust["GivenName"].GetString());
            insert.bind(3, cust["FamilyName"].IsNull() ? nullptr : cust["FamilyName"].GetString());
            insert.bind(4, cust["Email"].IsNull() ? nullptr : cust["Email"].GetString());
            insert.bind(5, cust["Phonenumber"].IsNull() ? nullptr : cust["Phonenumber"].GetString());
            insert.exec();
            insert.reset();
        }
    }

    // Import rentals
    if (doc.HasMember("rentals") && doc["rentals"].IsArray()) {
        SQLite::Statement insert(db, "INSERT OR REPLACE INTO rentals (rentalid, car_id, customer_id, start_date, end_date) VALUES (?, ?, ?, ?, ?)");
        for (auto& rent : doc["rentals"].GetArray()) {
            insert.bind(1, rent["rentalid"].GetInt());
            insert.bind(2, rent["car_id"].GetInt());
            insert.bind(3, rent["customer_id"].GetInt());
            insert.bind(4, rent["start_date"].IsNull() ? nullptr : rent["start_date"].GetString());
            insert.bind(5, rent["end_date"].IsNull() ? nullptr : rent["end_date"].GetString());
            insert.exec();
            insert.reset();
        }
    }

    cout << "Data imported successfully from " << filename << endl;
}

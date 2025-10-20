#include <iostream>
#include <fstream>
#include <sstream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include "DataManager.h"

void DataManager::statistics(SQLite::Database& db) {

    SQLite::Statement customers(db, "SELECT COUNT(*) FROM customers");
    customers.executeStep();
    int customerCount = customers.getColumn(0).getInt();
    std::cout << "Total customers: " << customerCount << std::endl;

    SQLite::Statement cars(db, "SELECT COUNT(*) FROM cars");
    cars.executeStep();
    int carCount = cars.getColumn(0).getInt();
    std::cout << "Total cars: " << carCount << std::endl;

    SQLite::Statement active_rentals(db, "SELECT COUNT(*) FROM rentals WHERE end_date >= date('now')");
    active_rentals.executeStep();
    int activeRentalCount = active_rentals.getColumn(0).getInt();
    std::cout << "Active rentals: " << activeRentalCount << std::endl;

    SQLite::Statement completed_rentals(db, "SELECT COUNT(*) FROM rentals WHERE end_date < date('now')");
    completed_rentals.executeStep();
    int completedRentalCount = completed_rentals.getColumn(0).getInt();
    std::cout << "Completed rentals: " << completedRentalCount << std::endl;

    std::cout << "\n" << std::endl;
}

void DataManager::JsonImport(SQLite::Database& db, const string& filename) {
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

void DataManager::JsonExport(SQLite::Database& db) {
    rapidjson::Document doc;
    doc.SetObject();
    auto& a = doc.GetAllocator();

    // Cuts repetition
    auto strOrNull = [&](const SQLite::Column& c) {
        rapidjson::Value v;
        if (c.isNull()) v.SetNull();
        else v.SetString(c.getText(), a);
        return v;
    };
    auto intOrNull = [&](const SQLite::Column& c) {
        rapidjson::Value v;
        if (c.isNull()) v.SetNull();
        else v.SetInt(c.getInt());
        return v;
    };

    // Export cars
    {
        rapidjson::Value cars(rapidjson::kArrayType);
        SQLite::Statement q(db, "SELECT carid, regnr, brand, model, year, status FROM cars");
        while (q.executeStep()) {
            rapidjson::Value car(rapidjson::kObjectType);
            car.AddMember("carid", q.getColumn(0).getInt(), a);
            car.AddMember("regnr",  strOrNull(q.getColumn(1)), a);
            car.AddMember("brand",  strOrNull(q.getColumn(2)), a);
            car.AddMember("model",  strOrNull(q.getColumn(3)), a);
            car.AddMember("year",   intOrNull(q.getColumn(4)), a);
            car.AddMember("status", intOrNull(q.getColumn(5)), a);
            cars.PushBack(car, a);
        }
        doc.AddMember("cars", cars, a);
    }

    // Export customers
    {
        rapidjson::Value customers(rapidjson::kArrayType);
        SQLite::Statement q(db, "SELECT customerid, GivenName, FamilyName, Email, Phonenumber FROM customers");
        while (q.executeStep()) {
            rapidjson::Value customer(rapidjson::kObjectType);
            customer.AddMember("customerid", q.getColumn(0).getInt(), a);
            customer.AddMember("GivenName",   strOrNull(q.getColumn(1)), a);
            customer.AddMember("FamilyName",  strOrNull(q.getColumn(2)), a);
            customer.AddMember("Email",       strOrNull(q.getColumn(3)), a);
            customer.AddMember("Phonenumber", strOrNull(q.getColumn(4)), a);
            customers.PushBack(customer, a);
        }
        doc.AddMember("customers", customers, a);
    }

    // Export rentals
    {
        rapidjson::Value rentals(rapidjson::kArrayType);
        SQLite::Statement q(db, "SELECT rentalid, car_id, customer_id, start_date, end_date FROM rentals");
        while (q.executeStep()) {
            rapidjson::Value rental(rapidjson::kObjectType);
            rental.AddMember("rentalid",    q.getColumn(0).getInt(), a);
            rental.AddMember("car_id",      q.getColumn(1).getInt(), a);
            rental.AddMember("customer_id", q.getColumn(2).getInt(), a);
            rental.AddMember("start_date",  strOrNull(q.getColumn(3)), a);
            rental.AddMember("end_date",    strOrNull(q.getColumn(4)), a);
            rentals.PushBack(rental, a);
        }
        doc.AddMember("rentals", rentals, a);
    }

    // Write to a file
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    writer.SetIndent(' ', 2);
    doc.Accept(writer);

    ofstream file("backup.json", ios::binary);
    if (!file) {
        cout << "Failed to create backup.json\n";
        return;
    }
    file.write(buffer.GetString(), static_cast<streamsize>(buffer.GetSize()));
    cout << "backup.json created successfully.\n";
}

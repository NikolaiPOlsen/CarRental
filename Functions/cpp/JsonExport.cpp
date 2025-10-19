#include <fstream>
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

using namespace std;

void JsonExport(SQLite::Database& db) {
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
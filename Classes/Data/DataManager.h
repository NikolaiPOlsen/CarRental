#ifndef DATAMANAGER_H
#define DATATMANAGER_H
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;

class DataManager {
    private:

    public:
    void JsonExport(SQLite::Database& db);
    void JsonImport(SQLite::Database& db, const string& filename);
    void statistics(SQLite::Database& db);

};



#endif

#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

void JsonImport(SQLite::Database& db, const std::string& filename);
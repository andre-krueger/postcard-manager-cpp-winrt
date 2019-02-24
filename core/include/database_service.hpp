#pragma once

#include "sqlite_connection.hpp"

class DatabaseService {
public:
    DatabaseService(const std::string& databasePath);
    SqliteConnection getConnection();
private:
    std::string _databasePath;
};
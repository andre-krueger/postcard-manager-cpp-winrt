#pragma once

#include "sqlite_connection.hpp"

class DatabaseService {
public:
    explicit DatabaseService(const std::string& databasePath) : m_databasePath(databasePath) {}
    SqliteConnection getConnection();
private:
    std::string m_databasePath;
};
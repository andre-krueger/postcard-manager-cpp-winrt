#pragma once

#include "sqlite_connection.hpp"

class DatabaseService {
public:
    SqliteConnection getConnection(const std::string connectionPath);
};
#include "pch.h"

#include "database_service.hpp"

DatabaseService::DatabaseService(const std::string& databasePath) : _databasePath(databasePath) {
    auto connection = SqliteConnection{ _databasePath };
    // Do migrations
}

SqliteConnection DatabaseService::getConnection()
{
    return SqliteConnection{ _databasePath };
}

#include "pch.h"
#include "database_service.hpp"

SqliteConnection DatabaseService::getConnection(const std::string connectionPath)
{
    return SqliteConnection{ connectionPath };
}

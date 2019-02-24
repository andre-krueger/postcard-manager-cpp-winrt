#include "pch.h"

#include "database_service.hpp"

SqliteConnection DatabaseService::getConnection()
{
    return SqliteConnection{ m_databasePath };
}
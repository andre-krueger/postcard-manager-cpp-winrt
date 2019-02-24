#include "pch.h"

#include "sqlite_connection.hpp"

SqliteConnection::SqliteConnection(const std::string& connectionPath) {
    sqlite3 *connection = nullptr;
    sqlite3_open(connectionPath.c_str(), &connection);
    m_connectionHandle = std::unique_ptr<sqlite3, sqlite_deleter>(connection);
}

#pragma once

#include "sqlite_connection.hpp"

namespace database {
    const static inline std::vector<std::string> migrations{
            "CREATE TABLE location (id INTEGER PRIMARY KEY, name TEXT UNIQUE NOT NULL);"
    };
    static inline const char* databaseName = "postcards.db";
};

class DatabaseService {
public:
    explicit DatabaseService(const std::string& databasePath) : m_databasePath(databasePath) {}
    SqliteConnection getConnection();
    std::variant<std::monostate, DatabaseError> commitOrRollback(SqliteConnection &connection, const std::string &query);
    std::variant<std::monostate, DatabaseError> migrate(std::vector<std::string> migrations);
private:
    std::string m_databasePath;
};
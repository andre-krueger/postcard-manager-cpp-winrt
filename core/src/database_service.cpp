#include "pch.h"

#include "database_service.hpp"

SqliteConnection DatabaseService::getConnection()
{
    return SqliteConnection{ m_databasePath };
}

std::variant<std::monostate, DatabaseError> DatabaseService::commitOrRollback(SqliteConnection &connection,
                                                                              const std::string &query) {
    connection.execute("BEGIN TRANSACTION;");
    auto result = connection.execute(query);
    if (!std::holds_alternative<DatabaseError>(result)) {
        connection.execute("COMMIT;");
        return std::monostate();
    }
    return std::get<DatabaseError>(result);
}

std::variant<std::monostate, DatabaseError> DatabaseService::migrate(std::vector<std::string> migrations) {
    auto connection = getConnection();
    auto userVersion = connection.execute("PRAGMA user_version;");
    std::variant<std::monostate, DatabaseError> result;
    if (std::holds_alternative<uint64_t>(userVersion)) {
        switch (std::get<uint64_t>(userVersion)) {
            case 0:
                result = commitOrRollback(connection, migrations.at(0));
                if (std::holds_alternative<DatabaseError>(result)) {
                    result = std::get<DatabaseError>(result);
                    break;
                }
                result = commitOrRollback(connection, migrations.at(1));
                if (std::holds_alternative<DatabaseError>(result)) {
                    result = std::get<DatabaseError>(result);
                    break;
                }
                commitOrRollback(connection, "PRAGMA user_version = 1;");
        }
    }
    return result;
}


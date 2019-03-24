#include "pch.h"

#include "location_repository.hpp"

std::variant<uint64_t, DatabaseError> LocationRepository::insert(const models::Location &location) {
    auto connection = m_databaseService.getConnection();
    auto result = connection.execute(
                    "INSERT INTO location (name) VALUES (@name);",
                    location.name);
    if (std::holds_alternative<DatabaseError>(result)) {
        return result;
    }
    return connection.execute("SELECT LAST_INSERT_ROWID();");
}

std::variant<uint64_t, DatabaseError> LocationRepository::update(const models::Location &location) {
    auto connection = m_databaseService.getConnection();
    return connection.execute(
        "UPDATE location SET name = @name WHERE id = @id;",
        location.name,
        location.id
    );
}

std::variant<uint64_t, DatabaseError> LocationRepository::remove(uint64_t id) {
    auto connection = m_databaseService.getConnection();
    return connection.execute(
        "DELETE FROM location WHERE id = @id;",
        id
    );
}

std::variant<std::vector<models::Location>, DatabaseError> LocationRepository::getAll() {
    auto connection = m_databaseService.getConnection();
    return connection.load<models::Location>("SELECT * FROM location;");
}

std::variant<std::vector<models::Location>, DatabaseError> LocationRepository::getById(uint64_t id) {
    auto connection = m_databaseService.getConnection();
    return connection.load<models::Location>(
        "SELECT * FROM location WHERE id = @id;",
        id
        );
}
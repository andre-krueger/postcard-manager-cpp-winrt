#include "pch.h"

#include "location_repository.hpp"

int64_t LocationRepository::insert(const models::Location& location) {
    auto connection = m_databaseService.getConnection();
    connection.execute(
        "INSERT INTO location (name) VALUES (@name);",
        location.name
    );
    return connection.execute("SELECT LAST_INSERT_ROWID();");
}

int64_t LocationRepository::update(const models::Location& location) {
    auto connection = m_databaseService.getConnection();
    return connection.execute(
        "UPDATE location SET name = @name WHERE id = @id;",
        location.name,
        location.id
    );
}

int64_t LocationRepository::remove(uint64_t id) {
    auto connection = m_databaseService.getConnection();
    return connection.execute(
        "DELETE FROM location WHERE id = @id;",
        id
    );
}

std::vector<models::Location> LocationRepository::getAll() {
    auto connection = m_databaseService.getConnection();
    return connection.load<models::Location>("SELECT * FROM location;");
}

std::vector<models::Location> LocationRepository::getById(uint64_t id) {
    auto connection = m_databaseService.getConnection();
    return connection.load<models::Location>(
        "SELECT * FROM location WHERE id = @id;",
        id
        );
}
#include "pch.h"

#include "location_repository.hpp"

LocationRepository::LocationRepository(const DatabaseService databaseService) : _databaseService(databaseService) {
}

int64_t LocationRepository::insert(const models::Location& location) {
    auto connection = _databaseService.getConnection();

    connection.execute(
        "INSERT INTO locations (name) VALUES (@name);",
        location
    );
    return connection.execute("SELECT LAST_INSERT_ROWID();");
    //connection.execute("INSERT into locations (name) VALUES ('test');");
    //connection.execute("INSERT into locations (name) VALUES ('test');");

    //return connection.execute("SELECT LAST_INSERT_ROWID();");
    // if sqlite_err return -1
    // otherwise return the primary key of the newly inserted entity
}

int64_t LocationRepository::update(const models::Location& location) {
    auto connection = _databaseService.getConnection();
    return connection.execute(
        "UPDATE locations SET name = @name WHERE id = @id",
        location
    );
}

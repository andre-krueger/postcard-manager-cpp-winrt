#include "pch.h"

#include "location_repository.hpp"

LocationRepository::LocationRepository(const DatabaseService databaseService) : _databaseService(databaseService) {
}

int64_t LocationRepository::insert(const models::Location& location) {
    auto connection = _databaseService.getConnection();
    connection.execute();
    return 0;
    // if sqlite_err return -1
    // otherwise return the primary key of the newly inserted entity
}

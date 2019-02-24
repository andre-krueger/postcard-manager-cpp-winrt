#include "pch.h"

#include "location_repository.hpp"

LocationRepository::LocationRepository(DatabaseService databaseService) : _databaseService(databaseService) {
}

int64_t LocationRepository::insert(models::Location& location) {
    auto connection = _databaseService.getConnection();

    return 0;
    // if sqlite_err return -1
    // otherwise return the primary key of the newly inserted entity
}

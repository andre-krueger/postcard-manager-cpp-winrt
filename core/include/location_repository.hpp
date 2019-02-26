#pragma once
#include "database_service.hpp"
#include "models.hpp"

class LocationRepository {
public:
    LocationRepository(const DatabaseService databaseService);
    int64_t insert(const models::Location& location);

private:
    DatabaseService _databaseService;
};
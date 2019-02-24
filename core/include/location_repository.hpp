#pragma once
#include "database_service.hpp"
#include "models.hpp"

class LocationRepository {
public:
    LocationRepository(DatabaseService databaseService);
    int64_t insert(models::Location& location);
private:
    DatabaseService _databaseService;
};
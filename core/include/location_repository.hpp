#pragma once
#include "database_service.hpp"
#include "models.hpp"

class LocationRepository {
public:
    LocationRepository(const DatabaseService databaseService);
    int64_t insert(const models::Location& location);
    int64_t update(const models::Location& location);
    std::vector<models::Location> getAll();

private:
    DatabaseService _databaseService;
};
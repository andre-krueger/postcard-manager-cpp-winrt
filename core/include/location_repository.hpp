#pragma once
#include "database_service.hpp"
#include "models.hpp"

class LocationRepository {
public:
    LocationRepository(const DatabaseService databaseService) : m_databaseService(databaseService) {}
    int64_t insert(const models::Location& location);
    // TODO: Generate a sql query which only contains the changing columns
    int64_t update(const models::Location& location);
    int64_t remove(uint64_t id);
    std::vector<models::Location> getAll();
    std::vector<models::Location> getById(uint64_t id);

private:
    DatabaseService m_databaseService;
};
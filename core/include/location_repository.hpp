#pragma once
#include "database_service.hpp"
#include "models.hpp"

class LocationRepository {
public:
    explicit LocationRepository(const DatabaseService databaseService) : m_databaseService(databaseService) {}
    std::variant<uint64_t, DatabaseError> insert(const models::Location &location);
    // TODO: Generate a sql query which only contains the changing columns
    std::variant<uint64_t, DatabaseError> update(const models::Location &location);
    std::variant<uint64_t, DatabaseError> remove(uint64_t id);
    std::variant<std::vector<models::Location>, DatabaseError> getAll();
    std::variant<std::vector<models::Location>, DatabaseError> getById(uint64_t id);

private:
    DatabaseService m_databaseService;
};
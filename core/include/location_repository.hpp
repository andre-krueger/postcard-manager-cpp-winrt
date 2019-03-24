#pragma once

#include "pch.h"
#include "database_service.hpp"
#include "repository_interface.hpp"
#include "models.hpp"

namespace location_repository {
    using ExecuteResult = std::variant<uint64_t, DatabaseError>;
    using LoadResult = std::variant<std::vector<models::Location>, DatabaseError>;
};

template <typename DatabaseService, typename Entity, typename ExecuteResult, typename LoadResult>
class LocationRepository : public RepositoryInterface<
        LocationRepository<DatabaseService, Entity, ExecuteResult, LoadResult>,
                DatabaseService, Entity, ExecuteResult, LoadResult
                > {
public:
    explicit LocationRepository(const DatabaseService databaseService) : m_databaseService(databaseService) {}
    location_repository::ExecuteResult insertImpl(const Entity& entity) {
        auto connection = m_databaseService.getConnection();
        auto result = connection.execute(
                "INSERT INTO location (name) VALUES (@name);",
                entity.name);
        if (std::holds_alternative<DatabaseError>(result)) {
            return result;
        }
        return connection.execute("SELECT LAST_INSERT_ROWID();");
    }
    location_repository::ExecuteResult updateImpl(const Entity& entity) {
        auto connection = m_databaseService.getConnection();
        return connection.execute(
                "UPDATE location SET name = @name WHERE id = @id;",
                entity.name,
                entity.id
        );
    }
    location_repository::ExecuteResult removeImpl(uint64_t id) {
        auto connection = m_databaseService.getConnection();
        return connection.execute(
                "DELETE FROM location WHERE id = @id;",
                id
        );
    }
    location_repository::LoadResult getAllImpl() {
        auto connection = m_databaseService.getConnection();
        return connection.template load<Entity>("SELECT * FROM location;");
    }
    location_repository::LoadResult getByIdImpl(uint64_t id) {
        auto connection = m_databaseService.getConnection();
        return connection.template load<Entity>(
                "SELECT * FROM location WHERE id = @id;",
                id
        );
    }
private:
    DatabaseService m_databaseService;
};

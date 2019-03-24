#pragma once

#include "pch.h"
#include "database_service.hpp"
#include "repository_interface.hpp"
#include "models.hpp"

namespace card_repository {
    using ExecuteResult = std::variant<uint64_t, DatabaseError>;
    using LoadResult = std::variant<std::vector<models::Card>, DatabaseError>;
};

template <typename DatabaseService, typename Entity, typename ExecuteResult, typename LoadResult>
class CardRepository : public RepositoryInterface<
        CardRepository<DatabaseService, Entity, ExecuteResult, LoadResult>,
        DatabaseService, Entity, ExecuteResult, LoadResult> {
public:
    explicit CardRepository(const DatabaseService databaseService) : m_databaseService(databaseService) {}
    card_repository::ExecuteResult insertImpl(const Entity& entity) {
        auto connection = m_databaseService.getConnection();
        connection.execute("PRAGMA foreign_keys = 1;");
        auto result = connection.execute(
                "INSERT INTO card (name, description, location_id) VALUES (@name, @description, @location_id);",
                entity.name,
                entity.description,
                entity.locationId);
        if (std::holds_alternative<DatabaseError>(result)) {
            return result;
        }
        return connection.execute("SELECT LAST_INSERT_ROWID();");
    }
    card_repository::ExecuteResult updateImpl(const Entity& entity) {
        auto connection = m_databaseService.getConnection();
        return connection.execute(
                "UPDATE card SET name = @name, description = @description WHERE id = @id;",
                entity.name,
                entity.description,
                entity.id
        );
    }
    card_repository::ExecuteResult removeImpl(uint64_t id) {
        auto connection = m_databaseService.getConnection();
        return connection.execute(
                "DELETE FROM card WHERE id = @id;",
                id
        );
    }
    card_repository::LoadResult getAllImpl() {
        auto connection = m_databaseService.getConnection();
        return connection.template load<Entity>("SELECT * FROM card;");
    }
    card_repository::LoadResult getByIdImpl(uint64_t id) {
        auto connection = m_databaseService.getConnection();
        return connection.template load<Entity>(
                "SELECT * FROM card WHERE id = @id;",
                id
        );
    }
    card_repository::LoadResult getAllByLocationID(uint64_t id) {
        auto connection = m_databaseService.getConnection();
        return connection.template load<Entity>(
                "SELECT * FROM card WHERE location_id = @location_id;",
                id
        );
    }
private:
    DatabaseService m_databaseService;
};
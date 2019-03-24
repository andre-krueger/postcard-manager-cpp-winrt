#include "pch.h"

#include "location_repository.hpp"

class LocationRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        databaseService.migrate(database::migrations);
    }

    void TearDown() override {
        std::remove(database::databaseName);
    }

    inline static DatabaseService databaseService{ database::databaseName };
    inline static LocationRepository locationRepository{ databaseService };
};

TEST_F(LocationRepositoryTest, testInsert) {
    auto location = models::Location{};
    location.name = "test";
    auto id = locationRepository.insert(location);
    ASSERT_EQ(std::get<uint64_t>(id), 1);
}

TEST_F(LocationRepositoryTest, testDuplicateInsert) {
    auto location = models::Location{};
    location.name = "test";
    locationRepository.insert(location);
    auto id = locationRepository.insert(location);
    ASSERT_EQ(std::get<DatabaseError>(id), DatabaseError::UniqueConstraintError);
}

TEST_F(LocationRepositoryTest, testGetByID) {
    auto location = models::Location{};
    location.name = "test";
    auto id = locationRepository.insert(location);
    auto results = std::get<std::vector<models::Location>>(locationRepository.getById(std::get<uint64_t>(id)));
    ASSERT_EQ(results.at(0).id, 1);
    ASSERT_EQ(results.at(0).name, "test");
}

TEST_F(LocationRepositoryTest, testGetAll) {
    auto location = models::Location{};
    location.name = "test";
    locationRepository.insert(location);
    location.name = "test2";
    locationRepository.insert(location);
    auto results = std::get<std::vector<models::Location>>(locationRepository.getAll());
    ASSERT_EQ(results.at(0).id, 1);
    ASSERT_EQ(results.at(0).name, "test");
    ASSERT_EQ(results.at(1).id, 2);
    ASSERT_EQ(results.at(1).name, "test2");
}

TEST_F(LocationRepositoryTest, testUpdate) {
    auto location = models::Location{};
    location.name = "test";
    auto id = locationRepository.insert(location);
    location.id = std::get<uint64_t>(id);
    location.name = "";
    locationRepository.update(location);
    auto results = std::get<std::vector<models::Location>>(locationRepository.getAll());
    ASSERT_EQ(results.at(0).name, "");
}

TEST_F(LocationRepositoryTest, testDuplicateUpdate) {
    auto location = models::Location{};
    location.name = "test";
    auto id = locationRepository.insert(location);
    location.name = "test2";
    id = locationRepository.insert(location);
    location.name = "test";
    location.id = std::get<uint64_t>(id);
    auto result = locationRepository.update(location);
    ASSERT_EQ(std::get<DatabaseError>(result), DatabaseError::UniqueConstraintError);
}

TEST_F(LocationRepositoryTest, testRemove) {
    auto location = models::Location{};
    location.name = "test";
    auto id = locationRepository.insert(location);
    locationRepository.remove(std::get<uint64_t>(id));
    auto results = std::get<std::vector<models::Location>>(locationRepository.getAll());
    ASSERT_EQ(results.size(), 0);
}
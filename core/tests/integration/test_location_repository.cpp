#include "pch.h"

#include "location_repository.hpp"

class LocationRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        databaseService.getConnection().execute("CREATE TABLE locations (id INTEGER PRIMARY KEY, name TEXT);");
    }

    void TearDown() override {
        std::remove("test.db");
    }

    inline static DatabaseService databaseService{ "test.db" };
    inline static LocationRepository locationRepository{ databaseService };
};

TEST_F(LocationRepositoryTest, testInsert) {
    auto location = models::Location{};
    location.name = "test";
    auto id = locationRepository.insert(location);
    ASSERT_EQ(id, 1);
}

TEST_F(LocationRepositoryTest, testUpdate) {
    auto location = models::Location{};
    location.name = "test";
    auto id = locationRepository.insert(location);
    location.id = id;
    location.name = "";
    locationRepository.update(location);
}

TEST_F(LocationRepositoryTest, testGetAll) {
    auto location = models::Location{};
    location.name = "test";
    locationRepository.insert(location);
    location.name = "test2";
    locationRepository.insert(location);
    auto results = locationRepository.getAll();
}
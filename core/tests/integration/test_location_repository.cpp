#include "pch.h"

#include "location_repository.hpp"

class LocationRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        databaseService.getConnection().execute("CREATE TABLE location (id INTEGER PRIMARY KEY, name TEXT UNIQUE NOT NULL);");
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

TEST_F(LocationRepositoryTest, testGetByID) {
    auto location = models::Location{};
    location.name = "test";
    auto id = locationRepository.insert(location);
    auto results = locationRepository.getById(id);
    ASSERT_EQ(results.at(0).id, 1);
    ASSERT_EQ(results.at(0).name, "test");
}

TEST_F(LocationRepositoryTest, testGetAll) {
    auto location = models::Location{};
    location.name = "test";
    locationRepository.insert(location);
    location.name = "test2";
    locationRepository.insert(location);
    auto results = locationRepository.getAll();
    ASSERT_EQ(results.at(0).id, 1);
    ASSERT_EQ(results.at(0).name, "test");
    ASSERT_EQ(results.at(1).id, 2);
    ASSERT_EQ(results.at(1).name, "test2");
}

TEST_F(LocationRepositoryTest, testUpdate) {
    auto location = models::Location{};
    location.name = "test";
    auto id = locationRepository.insert(location);
    location.id = id;
    location.name = "";
    locationRepository.update(location);
    auto results = locationRepository.getAll();
    ASSERT_EQ(results.at(0).name, "");
}

TEST_F(LocationRepositoryTest, testRemove) {
    auto location = models::Location{};
    location.name = "test";
    auto id = locationRepository.insert(location);
    locationRepository.remove(id);
    auto results = locationRepository.getAll();
    ASSERT_EQ(results.size(), 0);
}
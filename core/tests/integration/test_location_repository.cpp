#include "pch.h"

#include "location_repository.hpp"

class LocationRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto databaseService = DatabaseService{ "test.db" };
        //databaseService.getConnection().execute("CREATE table");
        locationRepository = new LocationRepository(databaseService);
    }

    void TearDown() override {
        delete locationRepository;
        std::remove("test.db");
    }

    LocationRepository *locationRepository;
};

TEST_F(LocationRepositoryTest, testInsert) {
    auto location = models::Location{ 1 };
    locationRepository->insert(location);
    ASSERT_TRUE(std::filesystem::exists("test.db"));
}
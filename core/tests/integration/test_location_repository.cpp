#include "pch.h"

#include "location_repository.hpp"

class LocationRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        //databaseService.getConnection().execute("CREATE table");
        //locationRepository = new LocationRepository(databaseService);
    }

    void TearDown() override {
        //delete locationRepository;
        std::remove("test.db");
    }

    inline static DatabaseService databaseService{ "test.db" };
    inline static LocationRepository locationRepository{ databaseService };
};

TEST_F(LocationRepositoryTest, testInsert) {
    auto location = models::Location{ 1 };
    locationRepository.insert(location);
    //auto numOfLocations = databaseService.getConnection().execute();
    ASSERT_TRUE(std::filesystem::exists("test.db"));
}
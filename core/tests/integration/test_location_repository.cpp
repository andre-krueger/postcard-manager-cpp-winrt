#include "pch.h"

#include "location_repository.hpp"

class LocationRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        databaseService.getConnection().execute("CREATE TABLE locations (id INTEGER PRIMARY KEY, name TEXT UNIQUE);");
    }

    void TearDown() override {
        //std::remove("test.db");
    }

    inline static DatabaseService databaseService{ "test.db" };
    inline static LocationRepository locationRepository{ databaseService };
};

//TEST_F(LocationRepositoryTest, testInsert) {
//    auto location = models::Location{};
//    location.name = "test";
//    auto id = locationRepository.insert(location);
//    ASSERT_EQ(id, 1);
//}
//
TEST_F(LocationRepositoryTest, testUpdate) {
    //auto location = models::Location{};
    //location.name = "test";
    //auto id = locationRepository.insert(location);
    //auto locationsUpdate = models::LocationsUpdate{};
    //locationRepository.update(locationsUpdate);
}

TEST_F(LocationRepositoryTest, testGet) {
    auto location = models::Location{};
    location.name = "test";
    locationRepository.insert(location);
    location.name = "test2";
    locationRepository.insert(location);

    auto locationsSelect = models::LocationsSelect{};
    auto locationsWhere = models::LocationsWhere{};
    locationsWhere.name = "test2";
    locationsSelect.where = locationsWhere;

    //auto results = locationRepository.get();
    auto filteredResults = locationRepository.get(locationsSelect);

    ASSERT_EQ(filteredResults.at(0).id, 2);
    ASSERT_EQ(filteredResults.at(0).name, "test2");
}
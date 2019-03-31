#include "pch.h"

#include "location_repository.hpp"
#include "card_repository.hpp"

class CardRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        databaseService.migrate(database::migrations);
    }

    void TearDown() override {
        std::remove(database::databaseName);
    }

    inline static DatabaseService databaseService{ database::databaseName };
    inline static LocationRepository
        <DatabaseService, models::Location,
        location_repository::ExecuteResult, location_repository::LoadResult> locationRepository{ databaseService };
    inline static CardRepository
        <DatabaseService, models::Card,
        card_repository::ExecuteResult, card_repository::LoadResult> cardRepository{ databaseService };
};

TEST_F(CardRepositoryTest, testInsertWithLocation) {
    auto location = models::Location{};
    location.name = "test";
    auto locationId = locationRepository.insert(location);
    auto card = models::Card{};
    card.name = "test";
    card.description = "test";
    card.locationId = std::get<uint64_t>(locationId);
    auto id = cardRepository.insert(card);
    ASSERT_EQ(std::get<uint64_t>(id), 1);
}


TEST_F(CardRepositoryTest, testInsertWithoutLocation) {
    auto card = models::Card{};
    card.name = "test";
    card.description = "test";
    auto id = cardRepository.insert(card);
    ASSERT_EQ(std::get<DatabaseError>(id), DatabaseError::ForeignKeyConstraintError);
}

TEST_F(CardRepositoryTest, testGetByID) {
    auto location = models::Location{};
    location.name = "location";
    auto locationId = locationRepository.insert(location);
    auto card = models::Card{};
    card.name = "card";
    card.description = "description";
    card.locationId = std::get<uint64_t>(locationId);
    auto id = cardRepository.insert(card);
    auto results = std::get<std::vector<models::Card>>(cardRepository.getById(std::get<uint64_t>(id)));
    ASSERT_EQ(results.at(0).id, 1);
    ASSERT_EQ(results.at(0).name, "card");
    ASSERT_EQ(results.at(0).description, "description");
}

TEST_F(CardRepositoryTest, testGetAll) {
    auto location = models::Location{};
    location.name = "location";
    auto locationId = locationRepository.insert(location);
    auto card = models::Card{};
    card.name = "card1";
    card.description = "description";
    card.locationId = std::get<uint64_t>(locationId);
    auto id = cardRepository.insert(card);
    card.name = "card2";
    cardRepository.insert(card);
    auto results = std::get<std::vector<models::Card>>(cardRepository.getAll());
    ASSERT_EQ(results.size(), 2);
    ASSERT_EQ(results.at(0).id, 1);
    ASSERT_EQ(results.at(0).name, "card1");
    ASSERT_EQ(results.at(0).description, "description");

    ASSERT_EQ(results.at(1).id, 2);
    ASSERT_EQ(results.at(1).name, "card2");
    ASSERT_EQ(results.at(1).description, "description");
}

TEST_F(CardRepositoryTest, testGetAllByLocationId) {
    auto firstLocation = models::Location{};
    firstLocation.name = "location1";
    auto firstLocationId = std::get<uint64_t>(locationRepository.insert(firstLocation));

    auto firstLocationCard = models::Card{};
    firstLocationCard.name = "card1";
    firstLocationCard.description = "description";
    firstLocationCard.locationId = firstLocationId;
    cardRepository.insert(firstLocationCard);
    firstLocationCard.name = "card2";
    cardRepository.insert(firstLocationCard);

    auto secondLocation = models::Location{};
    secondLocation.name = "location2";
    auto secondLocationId = std::get<uint64_t>(locationRepository.insert(secondLocation));

    auto secondLocationCard = models::Card{};
    secondLocationCard.name = "card3";
    secondLocationCard.locationId = secondLocationId;
    cardRepository.insert(secondLocationCard);

    auto firstLocationResults = std::get<std::vector<models::Card>>(cardRepository.getAllByLocationID(firstLocationId));
    auto secondLocationResults = std::get<std::vector<models::Card>>(cardRepository.getAllByLocationID(secondLocationId));

    ASSERT_EQ(firstLocationResults.at(0).name, "card1");
    ASSERT_EQ(firstLocationResults.at(0).description, "description");
    ASSERT_EQ(firstLocationResults.at(1).name, "card2");
    ASSERT_EQ(firstLocationResults.at(1).description, "description");

    ASSERT_EQ(secondLocationResults.at(0).name, "card3");
}

TEST_F(CardRepositoryTest, testUpdate) {
    auto location = models::Location{};
    location.name = "test";
    auto locationId = locationRepository.insert(location);
    auto card = models::Card{};
    card.name = "card1";
    card.description = "description";
    card.locationId = std::get<uint64_t>(locationId);
    auto id = cardRepository.insert(card);
    card.id = std::get<uint64_t>(id);
    card.name = "card";
    cardRepository.update(card);
    auto results = std::get<std::vector<models::Card>>(cardRepository.getAll());
    ASSERT_EQ(results.at(0).name, "card");
}

TEST_F(CardRepositoryTest, testRemove) {
    auto location = models::Location{};
    location.name = "test";
    auto locationId = locationRepository.insert(location);
    auto card = models::Card{};
    card.name = "card1";
    card.description = "description";
    card.locationId = std::get<uint64_t>(locationId);
    auto id = std::get<uint64_t>(cardRepository.insert(card));
    cardRepository.remove(id);
    auto results = std::get<std::vector<models::Card>>(cardRepository.getAll());
    ASSERT_EQ(results.size(), 0);
}
#include "pch.h"

#include "sqlite_connection.hpp"

class SqliteConnectionTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
        std::remove("test.db");
    }

    const static inline SqliteConnection connection{ "test.db" };
};

TEST_F(SqliteConnectionTest, testCreateDatabase) {
    ASSERT_TRUE(std::filesystem::exists("test.db"));
    //connection->load<models::Location>();
}
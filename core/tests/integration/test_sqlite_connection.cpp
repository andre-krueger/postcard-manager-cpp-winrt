#include "pch.h"

#include "database_service.hpp"
#include "sqlite_connection.hpp"

class SqliteConnectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        connection = new SqliteConnection{ database::databaseName };
    }

    void TearDown() override {
        delete connection;
        std::remove(database::databaseName);
    }

    SqliteConnection* connection;
};

TEST_F(SqliteConnectionTest, testCreateDatabase) {
    ASSERT_TRUE(std::filesystem::exists(database::databaseName));
}
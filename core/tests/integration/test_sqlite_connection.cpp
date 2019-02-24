#include "pch.h"

#include "sqlite_connection.hpp"

class SqliteConnectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        connection = new SqliteConnection{ "test.db" };
    }

    void TearDown() override {
        delete connection;
        std::remove("test.db");
    }

    SqliteConnection *connection;
};

TEST_F(SqliteConnectionTest, testCreateDatabase) {
    ASSERT_TRUE(std::filesystem::exists("test.db"));
}
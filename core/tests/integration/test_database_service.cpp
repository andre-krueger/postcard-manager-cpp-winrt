#include "pch.h"

#include "database_service.hpp"
#include "sqlite_connection.hpp"

class DatabaseServiceTest : public ::testing::Test {
protected:
    void TearDown() override {
        std::remove(database::databaseName);
    }

    inline static DatabaseService databaseService{ database::databaseName };
};

TEST_F(DatabaseServiceTest, testCommitOrRollback) {
    auto connection = databaseService.getConnection();
    databaseService.commitOrRollback(connection, "CREATE TABLE test (id INTEGER PRIMARY KEY, field1 TEXT UNIQUE);");
    auto pragmaResults = connection.load<std::string, std::vector<QueryResult>>("PRAGMA table_info(test);");

    std::stringstream result{ "", std::ios_base::app | std::ios_base::out };

    for (auto pragmaResult : std::get<std::vector<QueryResult>>(pragmaResults)) {
        result << std::get<0>(pragmaResult) << " ";
        result << std::get<1>(pragmaResult);
    }

    std::string expected =
        "cid 0"
        "name id"
        "type INTEGER"
        "notnull 0"
        "pk 1"
        "cid 1"
        "name field1"
        "type TEXT"
        "notnull 0"
        "pk 0";

    ASSERT_EQ(result.str(), expected);
}

TEST_F(DatabaseServiceTest, testCommitOrRollbackWithFaultyMigration) {
    auto connection = databaseService.getConnection();
    databaseService.commitOrRollback(connection, "CREATE TABLE test (id INTEGER PRIMARY KEY, field1 TEXT UNIQUE);");

    auto migrateResult = databaseService.commitOrRollback(connection, "CREATE TABLE test (id INTEGER PRIMARY KEY, field1 TEXT UNIQUE);");
    auto pragmaResults = connection.load<std::string, std::vector<QueryResult>>("PRAGMA table_info(test);");

    std::stringstream result{ "", std::ios_base::app | std::ios_base::out };

    for (auto pragmaResult : std::get<std::vector<QueryResult>>(pragmaResults)) {
        result << std::get<0>(pragmaResult) << " ";
        result << std::get<1>(pragmaResult);
    }

    std::string expected =
        "cid 0"
        "name id"
        "type INTEGER"
        "notnull 0"
        "pk 1"
        "cid 1"
        "name field1"
        "type TEXT"
        "notnull 0"
        "pk 0";

    ASSERT_EQ(result.str(), expected);
}

TEST_F(DatabaseServiceTest, testApplicationMigrate) {
    databaseService.migrate(database::migrations);
    auto pragmaResults = databaseService.getConnection()
        .load<std::string, std::vector<QueryResult>>("PRAGMA table_info(location);");
    auto userVersion = databaseService.getConnection().execute("PRAGMA user_version;");

    ASSERT_EQ(std::get<uint64_t>(userVersion), 1);

    std::stringstream result{ "", std::ios_base::app | std::ios_base::out };

    for (auto pragmaResult : std::get<std::vector<QueryResult>>(pragmaResults)) {
        result << std::get<0>(pragmaResult) << " ";
        result << std::get<1>(pragmaResult);
    }

    std::string expected =
        "cid 0"
        "name id"
        "type INTEGER"
        "notnull 0"
        "pk 1"
        "cid 1"
        "name name"
        "type TEXT"
        "notnull 1"
        "pk 0";

    ASSERT_EQ(result.str(), expected);
}

TEST_F(DatabaseServiceTest, testFaultyApplicationMigrate) {
    std::vector<std::string> migrations{ "CREATE TABLE test;" };

    auto migrationResult = databaseService.migrate(migrations);

    ASSERT_EQ(std::get<DatabaseError>(migrationResult), DatabaseError::GenericError);

    auto pragmaResults = databaseService.getConnection()
            .load<std::string, std::vector<QueryResult>>("PRAGMA table_info(test);");
    auto userVersion = databaseService.getConnection().execute("PRAGMA user_version;");

    ASSERT_EQ(std::get<uint64_t>(userVersion), 0);
    ASSERT_EQ(std::get<std::vector<QueryResult>>(pragmaResults).size(), 0);
}


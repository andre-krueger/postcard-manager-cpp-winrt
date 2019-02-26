#pragma once
#include "models.hpp"

struct sqlite_deleter {
    void operator()(sqlite3 *connection) const { sqlite3_close(connection); }
};

class SqliteConnection {
public:
    SqliteConnection(const std::string& connectionPath);

    int64_t execute();

    uint64_t lastInsertId();

    template <typename Entity>
    std::vector<Entity> load() {
        std::vector<Entity> results{};
        if (std::is_same_v<Entity, models::Location>) {
            std::cerr << "yes";
            models::Location t{ 1 };
            results.push_back(t);
        }
        return results;
    }

private:
    std::unique_ptr<sqlite3, sqlite_deleter> connectionHandle;
};


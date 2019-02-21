#pragma once

struct sqlite_deleter {
    void operator()(sqlite3 *connection) const { sqlite3_close(connection); }
};

class SqliteConnection {
public:
    SqliteConnection(const std::string connectionPath);

private:
    std::unique_ptr<sqlite3, sqlite_deleter> connectionHandle;
};

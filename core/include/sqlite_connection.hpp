#pragma once
#include "models.hpp"

struct sqlite_deleter {
    void operator()(sqlite3 *connection) const { sqlite3_close(connection); }
};

class SqliteConnection {
public:
    SqliteConnection(const std::string& connectionPath);

    template <typename T>
    void forEach(int index, sqlite3_stmt* stmt, T& value) {
        if constexpr (std::is_constructible_v<std::string, T>) {
            sqlite3_bind_text(stmt, index, value.c_str(), value.length(), SQLITE_STATIC);
        }
        else if constexpr (std::is_integral_v<T>) {
            sqlite3_bind_int64(stmt, index, value);
        }
    }

    template <typename Head, typename... Tail>
    void forEach(int index, sqlite3_stmt *stmt, Head firstValue, Tail... tail) {
        forEach(index, stmt, firstValue);
        forEach(index + 1, stmt, tail...);
    }

    template <typename... T>
    int64_t execute(const std::string& query, const T&... ts) {
        sqlite3_stmt* stmt = nullptr;
        sqlite3_prepare_v2(m_connectionHandle.get(), query.c_str(), -1, &stmt, nullptr);
        int64_t result = 0;
        if constexpr (sizeof... (T) > 0) {
            int index = 1;
            forEach(index, stmt, ts...);
        }
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            result = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
        return result;
    }

    template<typename Entity, typename... T>
    std::vector<Entity> load(const std::string& query, const T&... ts) {
        sqlite3_stmt* stmt = nullptr;
        sqlite3_prepare_v2(m_connectionHandle.get(), query.c_str(), -1, &stmt, nullptr);
        auto columnCount = sqlite3_column_count(stmt);
        std::vector<Entity> results{};
        if constexpr (sizeof ... (T) > 0) {
            int index = 1;
            forEach(index, stmt, ts...);
        }
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // TODO: Use reflection in the future
            Entity entity;
            for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
                if constexpr ((std::is_same_v<models::Location, Entity>)) {
                    if (sqlite3_column_type(stmt, columnIndex) == SQLITE_INTEGER) {
                        entity.id = sqlite3_column_int64(stmt, columnIndex);
                    }
                    else if (sqlite3_column_type(stmt, columnIndex) == SQLITE_TEXT) {
                        entity.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, columnIndex));
                    }
                }
            }
            results.push_back(entity);
        }
        sqlite3_finalize(stmt);
        return results;
    }

private:
    std::unique_ptr<sqlite3, sqlite_deleter> m_connectionHandle;
};
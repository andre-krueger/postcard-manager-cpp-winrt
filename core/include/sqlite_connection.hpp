#pragma once
#include "models.hpp"

struct sqlite_deleter {
    void operator()(sqlite3 *connection) const { sqlite3_close(connection); }
};

class SqliteConnection {
public:
    SqliteConnection(const std::string& connectionPath);

    // TODO: Use runtime reflection if it is natively supported in C++ in the future
    template <typename... T,
        typename = std::enable_if_t
        <(std::conjunction_v<std::is_same<std::vector<models::Location>, T>...> && sizeof...(T) <= 1)
        || (std::conjunction_v<std::is_same<models::Location, T>...> && sizeof...(T) <= 1)
        || (std::conjunction_v<std::is_same<models::LocationsUpdate, T>...> && sizeof...(T) <= 1)
        || (std::conjunction_v<std::is_same<models::LocationsDelete, T>...> && sizeof...(T) <= 1)
        >>
        int64_t execute(const std::string& query, const T&... ts) {
        std::tuple<T...> args{ ts... };
        if constexpr ((std::is_same_v<std::vector<models::Location>, T> || ...)) {
            // TODO: Do a batched insert
            return 0;
        }
        else if constexpr ((std::is_same_v<models::Location, T> || ...)) {
            auto location = std::get<0>(args);
            sqlite3_stmt* stmt = nullptr;
            sqlite3_prepare_v2(connectionHandle.get(), query.c_str(), -1, &stmt, nullptr);
            //if (!location.name.empty()) {
            int nameIndex = sqlite3_bind_parameter_index(stmt, "@name");
            sqlite3_bind_text(stmt, nameIndex, location.name.c_str(), location.name.length(), SQLITE_STATIC);
            //}
            //if (location.id != 0) {
            //int idIndex = sqlite3_bind_parameter_index(stmt, "@id");
            //sqlite3_bind_int64(stmt, idIndex, location.id);
            //}
            int64_t result = sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            return result;
        }
        else if constexpr ((std::is_same_v<models::LocationsUpdate, T> || ...)) {
            auto locationsUpdate = std::get<0>(args);
        }
        else if constexpr ((std::is_same_v<models::LocationsDelete, T> || ...)) {
            // Remove code
        }
        else {
            sqlite3_stmt* stmt = nullptr;
            sqlite3_prepare_v2(connectionHandle.get(), query.c_str(), -1, &stmt, nullptr);
            int64_t result = 0;
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                result = sqlite3_column_int(stmt, 0);
            }
            sqlite3_finalize(stmt);
            return result;
        }
    }

    template<typename Entity, typename... T,
        typename = std::enable_if_t<(std::conjunction_v<std::is_same<models::LocationsSelect, T>...> && sizeof...(T) <= 1)>>
        typename std::enable_if<std::is_same<models::Location, Entity>::value, std::vector<models::Location>>::type  load(const std::string& query, const T&... ts) {
        std::tuple<T...> args{ ts... };
        if constexpr ((std::is_same_v<models::LocationsSelect, T> || ...)) {
            auto locationsSelect = std::get<0>(args);
            std::vector<models::Location> results{};
            sqlite3_stmt* stmt = nullptr;
            sqlite3_prepare_v2(connectionHandle.get(), query.c_str(), -1, &stmt, nullptr);

            if (locationsSelect.where.id.has_value()) {
                int idIndex = sqlite3_bind_parameter_index(stmt, "@id");
                sqlite3_bind_int64(stmt, idIndex, locationsSelect.where.id.value());
            }
            if (locationsSelect.where.name.has_value()) {
                int nameIndex = sqlite3_bind_parameter_index(stmt, "@name");
                sqlite3_bind_text(stmt, nameIndex, locationsSelect.where.name.value().c_str(), locationsSelect.where.name.value().length(), SQLITE_STATIC);
            }

            int columnCount = sqlite3_column_count(stmt);
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                models::Location location{};
                //if (locationsSelect.columns.id.has_value()) {
                location.id = sqlite3_column_int(stmt, columnCount);
                // }
                 //if (locationsSelect.columns.name.has_value()) {
                location.name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, columnCount - 1)));
                //}
                results.push_back(location);
            }
            sqlite3_finalize(stmt);
            return results;
        }
        else if (std::is_same_v<Entity, models::Location>) {
            std::vector<models::Location> results{};
            sqlite3_stmt* stmt = nullptr;
            sqlite3_prepare_v2(connectionHandle.get(), query.c_str(), -1, &stmt, nullptr);
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                models::Location location{};
                location.id = sqlite3_column_int(stmt, 0);
                location.name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
                results.push_back(location);
            }
            sqlite3_finalize(stmt);
            return results;
        }
    }

private:
    std::unique_ptr<sqlite3, sqlite_deleter> connectionHandle;
};


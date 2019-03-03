#pragma once
#include "database_service.hpp"
#include "models.hpp"

class LocationRepository {
public:
    LocationRepository(const DatabaseService databaseService);
    int64_t insert(const models::Location& location);
    int64_t update(const models::Location& location);

    template <typename... T,
        typename = std::enable_if_t
        <(std::conjunction_v<std::is_same<models::LocationsSelect, T>...> && sizeof...(T) == 1)
        || (std::conjunction_v<std::is_same<models::LocationsUpdate, T>...> && sizeof...(T) == 1)
        || (std::conjunction_v<std::is_same<models::LocationsDelete, T>...> && sizeof...(T) == 1)
        >>
        std::string getQuery(const T&... ts) {
        std::tuple<T...> args{ ts... };
        if constexpr ((std::is_same_v<models::LocationsSelect, T> || ...)) {
            auto locationsSelect = std::get<0>(args);
            return "";
        }
        else {
            return "";
        }
    }

    template <typename... T,
        typename = std::enable_if_t
        <(std::conjunction_v<std::is_same<models::LocationsSelect, T>...> && sizeof...(T) <= 1)>>
        std::vector<models::Location> get(const T&... ts) {
        std::tuple<T...> args{ ts... };
        if constexpr ((std::is_same_v<models::LocationsSelect, T> || ...)) {
            //std::cout << " locationsSelect set ";
            auto connection = _databaseService.getConnection();
            auto locationsSelect = std::get<0>(args);
            auto query = getQuery(locationsSelect);
            return connection.load<models::Location>("SELECT * FROM locations", locationsSelect);
        }
        else {
            //std::cout << " locationsSelect not set ";
            auto connection = _databaseService.getConnection();
            return connection.load<models::Location>("SELECT * FROM locations;");
        }
    }

private:
    DatabaseService _databaseService;
};
#pragma once

namespace models {
    struct Location {
        uint64_t id;
        std::string name;
    };

    struct LocationsColumns {
        std::optional<uint64_t> id;
        std::optional<std::string> name;
    };

    struct LocationsWhere {
        std::optional<uint64_t> id;
        std::optional<std::string> name;
    };

    struct LocationsSelect {
        LocationsColumns columns;
        LocationsWhere where;
    };

    struct LocationsUpdate {
        LocationsWhere where;
        std::string name;
    };

    struct LocationsDelete {
        LocationsWhere where;
    };
}
#pragma once

namespace models {
    struct Location {
        uint64_t id;
        std::string name;
    };

    struct Card {
        uint64_t id;
        std::string name;
        std::string description;
        uint64_t locationId;
    };
}
#pragma once

#include <string>

struct Serializable {
    virtual auto serializeToString() const -> std::string = 0;

    virtual auto deserializeFromString(std::string const&) -> void = 0;
};

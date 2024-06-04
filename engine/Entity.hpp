#pragma once

#include "Serializable.hpp"

class Game;

class Entity : public Serializable {
    int id_;

    static inline auto currentId = 0;
protected:
    bool isAlive_ = true;
public:
    Entity();

    virtual ~Entity() = default;

    virtual auto update(Game&) -> void = 0;

    static auto generateNextId() -> int;

    auto isAlive() const -> bool { return isAlive_; }

    auto kill() -> void { isAlive_ = false; }

    template <typename Target>
    auto is() const -> bool {
        return dynamic_cast<Target const*>(this) != nullptr;
    }

    template <typename Target>
    auto as() -> Target& {
        return dynamic_cast<Target&>(*this);
    }

    template <typename Target>
    auto as() const -> Target const& {
        return dynamic_cast<Target const&>(*this);
    }
};
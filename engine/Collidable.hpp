#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "Entity.hpp"

struct Collidable : Entity {
    virtual auto getGlobalBounds() const -> sf::FloatRect = 0;

    virtual auto isCollidingWith(Collidable const& other) const -> bool {
        return getGlobalBounds().intersects(other.getGlobalBounds());
    }

    virtual auto onCollisionWith(Collidable& other) -> void { }
};
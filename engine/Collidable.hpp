#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "Entity.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

struct Collidable : Entity {
    virtual auto getGlobalBounds() const -> sf::FloatRect = 0;

    virtual auto isCollidingWith(Collidable const& other) const -> bool {
        return getGlobalBounds().intersects(other.getGlobalBounds());
    }

    virtual auto onCollisionWith(Collidable& other) -> void { }

protected:
    auto getOutline() const -> sf::RectangleShape {
        auto outline = sf::RectangleShape();
        auto bounds = getGlobalBounds();
        outline.setPosition(bounds.left, bounds.top);
        outline.setSize({bounds.width, bounds.height});
        outline.setFillColor(sf::Color::Transparent);
        outline.setOutlineColor(sf::Color::Red);
        outline.setOutlineThickness(2);
        return outline;
    }
};
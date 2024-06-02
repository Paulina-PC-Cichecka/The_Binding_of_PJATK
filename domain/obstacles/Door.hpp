#pragma once

#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Door : public Collidable, public sf::Drawable {
    sf::Sprite doorFrame_;
    sf::Sprite door_;
    sf::Sprite openDoor_;

    bool isOpen = false;

public:
    Door(sf::Texture const&, sf::Vector2f const);

    auto update(Game&) -> void override;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto onCollisionWith(Collidable& other) -> void override;
};
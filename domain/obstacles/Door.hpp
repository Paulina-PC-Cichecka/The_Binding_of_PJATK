#pragma once

#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Door : public Collidable, public sf::Drawable {
    sf::Sprite doorFrame_;
    sf::Sprite doorLeftPart_;
    sf::Sprite doorRightPart_;
    sf::Sprite openDoor_;

    bool isOpen_ = false;
public:
    Door(sf::Texture const&, sf::Vector2f const);

    auto update(Game&) -> void override;

    auto open() -> void;

    auto isOpen() -> bool {
        return isOpen_;
    }

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto onCollisionWith(Collidable& other) -> void override;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};
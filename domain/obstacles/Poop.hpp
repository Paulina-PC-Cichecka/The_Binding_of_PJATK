#pragma once
#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Poop : public Collidable, public sf::Drawable {
    sf::Sprite poop_;

public:
    Poop(sf::Texture const&, sf::Vector2f const);

    auto getPosition() const -> sf::Vector2f;

    auto setPosition(float, float) -> void;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto update(Game&) -> void override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};
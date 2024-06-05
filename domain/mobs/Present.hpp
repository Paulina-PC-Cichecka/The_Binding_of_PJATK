#pragma once

#include "../../engine/Collidable.hpp"

#include "SFML/Graphics/Sprite.hpp"

class Present : public Collidable, public sf::Drawable {
    sf::Sprite present_;
    sf::Vector2f direction_;

    static const inline auto velocity = 15.0f;

public:
    Present(sf::Texture const&, sf::Vector2f const, sf::Vector2f const);

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto update(Game&) -> void override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto onCollisionWith(Collidable& other) -> void override;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};
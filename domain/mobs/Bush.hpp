#pragma once

#include "../../engine/Collidable.hpp"

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Bush : public Collidable, public sf::Drawable {
    sf::Sprite bush_;
    sf::Vector2f direction_;

    static const inline auto velocity_ = 15.0f;

public:
    Bush(sf::Texture const&, sf::Vector2f const, sf::Vector2f const);

    auto update(Game&) -> void override;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto onCollisionWith(Collidable& other) -> void override;
};

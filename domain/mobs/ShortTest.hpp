#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include "../../engine/Collidable.hpp"

class ShortTest : public Collidable, public sf::Drawable {
    sf::Sprite shortTest_;
    sf::Vector2f direction_;

    static const inline auto velocity = 15.0f;

public:
    ShortTest(sf::Texture const&, sf::Vector2f const, sf::Vector2f const);

    auto draw(sf::RenderTarget&, sf::RenderStates) const -> void override;

    auto update(Game&) -> void override;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto onCollisionWith(Collidable& other) -> void override;
};
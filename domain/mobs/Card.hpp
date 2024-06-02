#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Card : public Collidable, public sf::Drawable {
    sf::Sprite card_;
    sf::Vector2f direction_;

    static const inline auto velocity_ = 10.0f;

public:
    Card(sf::Texture const&, sf::Vector2f const, sf::Vector2f const);

    auto update(Game&) -> void override;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto moveTowards(sf::Vector2f const, Game const&) -> void;

    auto onCollisionWith(Collidable& other) -> void override;
};

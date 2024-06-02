#pragma once
#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Boots : public Collidable, public  sf::Drawable {
    sf::Sprite boots_;


public:
    Boots(sf::Texture const&, sf::Vector2f const);

    auto update(Game&) -> void override;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto onCollisionWith(Collidable& other) -> void override;
};

#pragma once
#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Sushi : public Collidable, public sf::Drawable{
    sf::Sprite sushi_;

public:
    Sushi(sf::Texture const&, sf::Vector2f const);

    auto update(Game&) -> void override;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;
};

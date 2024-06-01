#pragma once
#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Poop : public Collidable, public sf::Drawable {
    sf::Sprite poop_;

public:
    Poop(sf::Texture const&, sf::Vector2f const);

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto update(Game&) -> void override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;
};

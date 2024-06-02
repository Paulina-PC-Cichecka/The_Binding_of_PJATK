#pragma once
#include "Upgrade.hpp"
#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Boots : public Upgrade {
    sf::Sprite boots_;


public:
    Boots(sf::Texture const&, sf::Vector2f const);

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto onCollisionWith(Collidable& other) -> void override;
};

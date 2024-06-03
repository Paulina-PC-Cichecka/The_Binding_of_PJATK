#pragma once
#include "Upgrade.hpp"
#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Drug : public Upgrade{
    sf::Sprite drug_;

public:
    Drug(sf::Texture const&, sf::Vector2f const);

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto onCollisionWith(Collidable& other) -> void override;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};
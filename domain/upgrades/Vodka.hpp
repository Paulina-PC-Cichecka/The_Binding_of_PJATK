#pragma once
#include "Upgrade.hpp"

#include "SFML/Graphics/Sprite.hpp"

class Vodka : public Upgrade{
    sf::Sprite vodka_;

public:
    Vodka(sf::Texture const&, sf::Vector2f const);

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto update(Game&) -> void override;

    auto onCollisionWith(Collidable& other) -> void override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};

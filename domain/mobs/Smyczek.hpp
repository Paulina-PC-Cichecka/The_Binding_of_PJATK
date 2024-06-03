#pragma once

#include "../../engine/Collidable.hpp"

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"

class Smyczek : public Collidable, public sf::Drawable {
    sf::Sprite smyczek_;
    float velocity_ = 4.0;
    int maxHp_ = 6;
    int currentHp_ = maxHp_;
    sf::Clock shootingClock_;
    double shootingCooldown_ = 1;

public:
    Smyczek(sf::Texture const&, sf::Vector2f const);

    auto moveTowards(sf::Vector2f const, Game const& game) -> void;

    auto getPosition() const -> sf::Vector2f;

    auto setPosition(float, float) -> void;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto getPosition() -> sf::Vector2f;

    auto update(Game&) -> void override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto canShoot() const -> bool;

    auto decreaseHp() -> void;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};
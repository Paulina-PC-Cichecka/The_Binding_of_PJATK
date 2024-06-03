#pragma once

#include "../../engine/Collidable.hpp"

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"

class Tomaszew : public Collidable, public sf::Drawable {
    sf::Sprite tomaszew_;
    float velocity_ = 5.0;
    int maxHp_ = 2;
    int currentHp_ = maxHp_;
    sf::Clock damageClock_;
    double damageCooldown_ = 1;

public:
    Tomaszew(sf::Texture const&, sf::Vector2f const);

    auto getPosition() const -> sf::Vector2f;

    auto setPosition(float, float) -> void;

    auto moveTowards(sf::Vector2f const, Game const&) -> void;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto onCollisionWith(Collidable& other) -> void override;

    auto update(Game&) -> void override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto decreaseHp() -> void;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};
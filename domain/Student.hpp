#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include "../engine/Collidable.hpp"
#include "../engine/Game.hpp"

class Student : public Collidable, public sf::Drawable {
    sf::Texture const& heart_;

    sf::Sprite head_;
    sf::Sprite body_;

    int maxHp_ = 6;
    int currentHp_ = maxHp_;
    float velocity_ = 8.0f;
    sf::Clock shootingClock_;
    double shootingCooldown_ = 0.8;

    sf::Vector2f scale_;

    bool movingLeft  = false;
    bool movingRight = false;
    bool movingUp    = false;
    bool movingDown  = false;
public:
    Student(sf::Texture const&, sf::Texture const&, sf::Vector2f);

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto getPosition() const -> sf::Vector2f;

    auto draw(sf::RenderTarget&, sf::RenderStates) const -> void override;

    auto update(Game&) -> void override;

    auto canShoot() const -> bool;

    auto startMovingLeft() -> void;

    auto startMovingRight() -> void;

    auto startMovingUp() -> void;

    auto startMovingDown() -> void;

    auto stopMovingLeft() -> void;

    auto stopMovingRight() -> void;

    auto stopMovingUp() -> void;

    auto stopMovingDown() -> void;

    auto decreaseHp() -> void;
};

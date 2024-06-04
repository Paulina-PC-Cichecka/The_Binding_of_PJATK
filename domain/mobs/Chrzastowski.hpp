#pragma once

#include "../../engine/Collidable.hpp"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"

class Chrzastowski : public Collidable, public sf::Drawable {

    sf::Sprite chrzastowski_;
    float velocity_ = 4.0;
    int maxHp_ = 20;
    int currentHp_ = maxHp_;
    sf::Clock shootingClockForPresent_;
    double shootingCooldownForPresent_ = 0.8;
    sf::Clock shootingClockForExam_;
    double shootingCooldownForExam_ = 1;

public:
    Chrzastowski(sf::Texture const&, sf::Vector2f const);

    auto moveTowards(sf::Vector2f const, Game const&) -> void;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto getPosition() const -> sf::Vector2f;

    auto setPosition(float, float ) -> void;

    auto canShootShortTest() const -> bool;

    auto decreaseHp(int const) -> void;

    auto update(Game&) -> void override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};

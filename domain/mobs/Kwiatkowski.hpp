#pragma once

#include "../../engine/Collidable.hpp"
#include "../../engine/Game.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"

class Kwiatkowski : public Collidable, public sf::Drawable {
    sf::Sprite kwiatkowski_;
    float velocity_ = 4.0;
    int maxHp_ = 10;
    int currentHp_ = maxHp_;
    sf::Clock shootingClockForShortTest_;
    double shootingCooldownForShortTest_ = 1;
    sf::Clock shootingClockForCard_;
    double shootingCooldownForCard_ = 2;

public:
    Kwiatkowski(sf::Texture const&);

    auto moveTowards(sf::Vector2f const, Game const&) -> void;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto getPosition() const -> sf::Vector2f;

    auto setPosition(float, float ) -> void;

    auto update(Game&) -> void override;

    auto draw(sf::RenderTarget& target, sf::RenderStates) const -> void override;

    auto decreaseHp(int const) -> void;

    auto canShootShortTest() const -> bool;

    auto canShootCard() const -> bool;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};
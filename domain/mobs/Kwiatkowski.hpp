#pragma once

#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"

class Kwiatkowski : public Collidable, public sf::Drawable {
    sf::Sprite kwiatkowski_;
    float velocity_ = 8.0;
    int maxHp_ = 10;
    int currentHp_ = maxHp_;
    sf::Clock shootingClock_;
    double shootingCooldown_ = 1;

public:
    Kwiatkowski(sf::Texture const&);

    auto moveTowards(sf::Vector2f const) -> void;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto getPosition() -> sf::Vector2f;

    auto update(Game&) -> void override;

    auto draw(sf::RenderTarget& target, sf::RenderStates) const -> void override;

    auto decreaseHp() -> void;

    auto canShoot() const -> bool;
};

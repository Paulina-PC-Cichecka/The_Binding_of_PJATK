#pragma once

#include "../../engine/Collidable.hpp"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"

class Exam : public Collidable, public sf::Drawable  {
    sf::Sprite exam_;
    sf::Vector2f direction_;
    sf::Clock lifespan_;
    double killExam_ = 5;

    static const inline auto velocity_ = 10.0f;

public:
    Exam(sf::Texture const&, sf::Vector2f const, sf::Vector2f const);

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto moveTowards(sf::Vector2f const, Game const&) -> void;

    auto update(Game&) -> void override;

    auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

    auto onCollisionWith(Collidable& other) -> void override;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};
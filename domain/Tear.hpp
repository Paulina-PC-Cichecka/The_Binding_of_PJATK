#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../engine/Collidable.hpp"

class Tear : public Collidable, public sf::Drawable {
    sf::Sprite tear_;
    sf::Vector2f direction_;
    float scale_;
    int damage_;

    static const inline auto velocity = 15.0f;

public:
    Tear(sf::Texture const&, sf::Vector2f const, sf::Vector2f const, float const, int const);

    auto draw(sf::RenderTarget&, sf::RenderStates) const -> void override;

    auto update(Game&) -> void override;

    auto getGlobalBounds() const -> sf::FloatRect override;

    auto onCollisionWith(Collidable& other) -> void override;

    auto serializeToString() const -> std::string override;

    auto deserializeFromString(const std::string&) -> void override;
};
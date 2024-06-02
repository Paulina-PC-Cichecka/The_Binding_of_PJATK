#include "Bush.hpp"

#include "../Student.hpp"
#include "../obstacles/Poop.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

Bush::Bush(sf::Texture const& texture, sf::Vector2f const startingPosition, sf::Vector2f const direction
) : direction_(direction * velocity_) {
    bush_.setTexture(texture);
    bush_.setTextureRect(sf::IntRect(0, 0, 56, 39));
    bush_.setScale(sf::Vector2f(2, 2));
    bush_.setOrigin(sf::Vector2f(56 / 2.0f, 39 / 2.0f));
    bush_.setPosition(startingPosition);
}

auto Bush::getGlobalBounds() const -> sf::FloatRect {
    auto originalBounds = bush_.getGlobalBounds();
    originalBounds.left += 10;
    originalBounds.top += 10;
    originalBounds.width -= 20;
    originalBounds.height -= 20;
    return originalBounds;
}

auto Bush::update(Game& game) -> void {
    bush_.move(direction_);
    // bush_.rotate(1);

    if (not game.movementSurface().contains(bush_.getPosition())) {
        isAlive_ = false;
    }
}

auto Bush::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(bush_);
}

auto Bush::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().decreaseHp();
        isAlive_ = false;
    }

    if (other.is<Poop>()) isAlive_ = false;
}
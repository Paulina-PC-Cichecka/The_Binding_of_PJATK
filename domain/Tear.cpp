#include "Tear.hpp"

#include "mobs/Kwiatkowski.hpp"
#include "obstacles/Poop.hpp"
#include "../engine/Game.hpp"
#include "../domain/Student.hpp"
#include "mobs/ShortTest.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

Tear::Tear(
    sf::Texture const& texture, sf::Vector2f startingPosition, sf::Vector2f direction
) : direction_(direction * velocity) {
    tear_.setTexture(texture);
    tear_.setTextureRect(sf::IntRect(0, 0, 127, 125));
    tear_.setScale(sf::Vector2f(0.5, 0.5));
    tear_.setOrigin(sf::Vector2f(127 / 2.0f, 125 / 2.0f));
    tear_.setPosition(startingPosition);
}

auto Tear::draw(sf::RenderTarget& target, sf::RenderStates) const -> void {
    target.draw(tear_);
}

auto Tear::update(Game& game) -> void {
    tear_.move(direction_);

    if (not game.movementSurface().contains(tear_.getPosition())) {
        isAlive_ = false;
    }
}

auto Tear::getGlobalBounds() const -> sf::FloatRect {
    return tear_.getGlobalBounds();
}

auto Tear::onCollisionWith(Collidable& other) -> void {
    if (other.is<Kwiatkowski>()) {
        other.as<Kwiatkowski>().decreaseHp();
        isAlive_ = false;
    }

    if (other.is<Poop>()) isAlive_ = false;
}
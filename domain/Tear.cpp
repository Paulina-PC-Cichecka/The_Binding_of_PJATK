#include <sstream>

#include "Tear.hpp"

#include "mobs/Kwiatkowski.hpp"
#include "obstacles/Poop.hpp"
#include "../engine/Game.hpp"
#include "../domain/Student.hpp"
#include "mobs/ShortTest.hpp"
#include "mobs/Smyczek.hpp"
#include "mobs/Tomaszew.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include <fmt/format.h>

Tear::Tear(
    sf::Texture const& texture, sf::Vector2f const startingPosition, sf::Vector2f const direction, float const scale
) : direction_(direction * velocity), scale_(scale) {
    tear_.setTexture(texture);
    tear_.setTextureRect(sf::IntRect(0, 0, 127, 125));
    tear_.setScale(sf::Vector2f(0.5, 0.5) * scale);
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

    if (other.is<Tomaszew>()) {
        other.as<Tomaszew>().decreaseHp();
        isAlive_ = false;
    }

    if (other.is<Smyczek>()) {
        other.as<Smyczek>().decreaseHp();
        isAlive_ = false;
    }

    if (other.is<Poop>()) isAlive_ = false;
}

auto Tear::serializeToString() const -> std::string {
    return fmt::format(
        "Tear {} {} {} {} {}",
        tear_.getPosition().x, tear_.getPosition().y,
        direction_.x, direction_.y,
        scale_
    );
}

auto Tear::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(5);
    auto stream = std::istringstream(withoutType);
    auto posX = float();
    auto posY = float();
    stream >> posX >> posY >> direction_.x >> direction_.y >> scale_;
    tear_.setPosition(posX, posY);
}

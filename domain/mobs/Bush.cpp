#include "Bush.hpp"

#include <sstream>

#include "../Student.hpp"
#include "../obstacles/Poop.hpp"
#include "fmt/xchar.h"

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

    auto const isOnValidMovementSurface = std::ranges::any_of(game.movementSurface(), [this](sf::FloatRect const rect) {
        return rect.contains(bush_.getPosition());
    });
    if (not isOnValidMovementSurface) {
        isAlive_ = false;
    }
}

auto Bush::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(bush_);
}

auto Bush::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().decreaseHp(1);
        isAlive_ = false;
    }

    if (other.is<Poop>()) isAlive_ = false;
}

auto Bush::serializeToString() const -> std::string {
    return fmt::format("Bush {} {} {} {}", getPosition().x, getPosition().y, direction_.x, direction_.y);
}

auto Bush::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(5);
    auto stream = std::istringstream(withoutType);
    auto x = float();
    auto y = float();
    stream >> x >> y >> direction_.x >> direction_.y;
    bush_.setPosition(x, y);
}

auto Bush::getPosition() const -> sf::Vector2f {
    return bush_.getPosition();
}
#include "ShortTest.hpp"

#include <sstream>

#include "Kwiatkowski.hpp"
#include "../obstacles/Poop.hpp"
#include "../Student.hpp"
#include "../Tear.hpp"
#include "../../engine/Game.hpp"
#include "../../engine/Utility.hpp"
#include "fmt/xchar.h"
#include "SFML/Graphics/RenderTarget.hpp"

ShortTest::ShortTest(
    sf::Texture const& texture,
    sf::Vector2f const startingPosition,
    sf::Vector2f const direction
) : direction_(direction * velocity) {
    shortTest_.setTexture(texture);
    shortTest_.setTextureRect(sf::IntRect(22, 45, 337, 269));
    shortTest_.setScale(0.3, 0.3);
    shortTest_.setOrigin(337 / 2.0f, 269 / 2.0f);
    shortTest_.setPosition(startingPosition);
}


auto ShortTest::draw(sf::RenderTarget& target, sf::RenderStates) const -> void {
    target.draw(shortTest_);
}

auto ShortTest::update(Game& game) -> void {
    shortTest_.move(direction_);
    shortTest_.rotate(2);

    auto const isOnValidMovementSurface = std::ranges::any_of(game.movementSurface(), [this](sf::FloatRect const rect) {
        return rect.contains(shortTest_.getPosition());
    });
    if (not isOnValidMovementSurface) {
        isAlive_ = false;
    }
}

auto ShortTest::getGlobalBounds() const -> sf::FloatRect {
    auto originalBounds = shortTest_.getGlobalBounds();
    originalBounds.left += 10;
    originalBounds.top += 10;
    originalBounds.width -= 20;
    originalBounds.height -= 20;
    return originalBounds;
}

auto ShortTest::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().decreaseHp(1);
        isAlive_ = false;
    }

    if (other.is<Poop>()) isAlive_ = false;
}

auto ShortTest::serializeToString() const -> std::string {
    return fmt::format("ShortTest {} {} {} {}", getPosition().x, getPosition().y, direction_.x, direction_.y);
}

auto ShortTest::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(10);
    auto stream = std::istringstream(withoutType);
    auto x = float();
    auto y = float();
    stream >> x >> y >> direction_.x >> direction_.y;
    shortTest_.setPosition(x, y);
}

auto ShortTest::getPosition() const -> sf::Vector2f {
    return shortTest_.getPosition();
}

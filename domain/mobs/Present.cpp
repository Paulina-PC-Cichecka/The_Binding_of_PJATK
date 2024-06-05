#include "Present.hpp"

#include <sstream>

#include "../../engine/Game.hpp"
#include "../Student.hpp"
#include "../obstacles/Poop.hpp"
#include "fmt/xchar.h"

#include "SFML/Graphics/RenderTarget.hpp"

Present::Present(sf::Texture const& presentTexture, sf::Vector2f const startingPosition, sf::Vector2f const direction
) : direction_((direction * velocity)) {
    present_.setTexture(presentTexture);
    present_.setTextureRect(sf::IntRect(573, 281, 169, 194));
    present_.setScale(sf::Vector2f(0.5, 0.5));
    present_.setOrigin(169 / 2.0f, 194 / 2.0f);
    present_.setPosition(startingPosition);
}

auto Present::getGlobalBounds() const -> sf::FloatRect {
    auto originalBounds = present_.getGlobalBounds();
    originalBounds.left += 10;
    originalBounds.top += 10;
    originalBounds.width -= 20;
    originalBounds.height -= 20;
    return originalBounds;
}



auto Present::update(Game& game) -> void {
    present_.move(direction_);
    present_.rotate(2);

    auto const isOnValidMovementSurface = std::ranges::any_of(game.movementSurface(), [this](sf::FloatRect const rect) {
        return rect.contains(present_.getPosition());
    });
    if (not isOnValidMovementSurface) {
        isAlive_ = false;
    }
}

auto Present::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(present_);
}

auto Present::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().decreaseHp(1);
        isAlive_ = false;
    }

    if (other.is<Poop>()) isAlive_ = false;
}

auto Present::serializeToString() const -> std::string {
    return fmt::format("Present {} {} {} {}", present_.getPosition().x, present_.getPosition().y,
                       direction_.x, direction_.y);
}

auto Present::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(8);
    auto stream = std::istringstream(withoutType);
    auto x = float();
    auto y = float();
    stream >> x >> y >> direction_.x >> direction_.y;
    present_.setPosition(x, y);
}
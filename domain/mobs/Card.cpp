#include "Card.hpp"

#include <sstream>

#include "../../engine/Game.hpp"
#include "../Student.hpp"
#include "../obstacles/Poop.hpp"
#include "../../engine/Utility.hpp"
#include "fmt/xchar.h"

#include "SFML/Graphics/RenderTarget.hpp"

Card::Card(sf::Texture const& texture, sf::Vector2f const startingPosition, sf::Vector2f const direction
) : direction_(direction * velocity_) {
    card_.setTexture(texture);
    card_.setTextureRect(sf::IntRect(39, 165, 20, 20));
    card_.setScale(5, 5);
    card_.setOrigin(20 / 2.0f, 20 / 2.0f);
    card_.setPosition(startingPosition);
}

auto Card::getGlobalBounds() const -> sf::FloatRect {
    auto originalBounds = card_.getGlobalBounds();
    originalBounds.left += 10;
    originalBounds.top += 10;
    originalBounds.width -= 20;
    originalBounds.height -= 20;
    return originalBounds;
}

auto Card::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(card_);
}

auto Card::moveTowards(sf::Vector2f const destination, Game const& game) -> void {
    auto const from = card_.getPosition();

    auto const direction = normalized(destination - from);

    card_.move(direction * velocity_);

    auto const objectWeCollidedWith = std::ranges::find_if(
        game.collidables(), [this](Collidable* c) {
            return c->getGlobalBounds().intersects(getGlobalBounds()) and c->is<Poop>();
        }
    );

    auto const weCollidedWhileMoving = objectWeCollidedWith != game.collidables().end();

    if (weCollidedWhileMoving) {
        // go back
        card_.setPosition(from);
        auto const moveOnlyUpOrDown = sf::Vector2f(0, direction.y > 0 ? velocity_ : -velocity_);
        card_.move(moveOnlyUpOrDown);

        auto const needToMoveLeftOrRightInstead =
                (*objectWeCollidedWith)->getGlobalBounds().intersects(getGlobalBounds());

        if (needToMoveLeftOrRightInstead) {
            card_.setPosition(from);
            auto const moveOnlyLeftOrRight = sf::Vector2f(direction.x > 0 ? velocity_ : -velocity_, 0);
            card_.move(moveOnlyLeftOrRight);
        }
    }
}

auto Card::update(Game& game) -> void {
    auto const& studentPtr = *std::ranges::find_if(game.entities(), [](std::unique_ptr<Entity> const& ptr) {
        return ptr->is<Student>();
    });

    auto const& student = studentPtr->as<Student>();
    moveTowards(student.getPosition(), game);
    card_.rotate(2);

    auto const isOnValidMovementSurface = std::ranges::any_of(game.movementSurface(), [this](sf::FloatRect const rect) {
        return rect.contains(card_.getPosition());
    });
    if (not isOnValidMovementSurface) {
        isAlive_ = false;
    }
}

auto Card::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().decreaseHp(1);
        isAlive_ = false;
    }

    if (other.is<Poop>()) isAlive_ = false;
}

auto Card::serializeToString() const -> std::string {
    return fmt::format("Card {} {} {} {}", getPosition().x, getPosition().y, direction_.x, direction_.y);
}

auto Card::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(5);
    auto stream = std::istringstream(withoutType);
    auto x = float();
    auto y = float();
    stream >> x >> y >> direction_.x >> direction_.y;
    card_.setPosition(x, y);
}

auto Card::getPosition() const -> sf::Vector2f {
    return card_.getPosition();
}
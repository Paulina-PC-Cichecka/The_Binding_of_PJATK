#include <algorithm>

#include "Kwiatkowski.hpp"

#include <sstream>

#include "../Student.hpp"
#include "../obstacles/Poop.hpp"
#include "../../engine/Utility.hpp"
#include "../../engine/Game.hpp"
#include "fmt/core.h"

Kwiatkowski::Kwiatkowski(sf::Texture const& body) {
    kwiatkowski_.setTexture(body);
    kwiatkowski_.setTextureRect(sf::IntRect(0, 0, 32, 40));
    kwiatkowski_.setScale(8, 8);
    kwiatkowski_.setOrigin(32 / 2.0f, 40 / 2.0f);
    kwiatkowski_.setPosition(600, 600);
}

auto Kwiatkowski::moveTowards(sf::Vector2f const destination, Game const& game) -> void {
    auto const from = kwiatkowski_.getPosition();

    auto const direction = normalized(destination - from);

    kwiatkowski_.move(direction * velocity_);

    auto const objectWeCollidedWith = std::ranges::find_if(
        game.collidables(), [this](Collidable* c) {
            return c->getGlobalBounds().intersects(getGlobalBounds()) and c->is<Poop>();
        }
    );

    auto const weCollidedWhileMoving = objectWeCollidedWith != game.collidables().end();

    if (weCollidedWhileMoving) {
        // go back
        kwiatkowski_.setPosition(from);
        auto const moveOnlyUpOrDown = sf::Vector2f(0, direction.y > 0 ? velocity_ : -velocity_);
        kwiatkowski_.move(moveOnlyUpOrDown);

        auto const needToMoveLeftOrRightInstead =
                (*objectWeCollidedWith)->getGlobalBounds().intersects(getGlobalBounds());

        if (needToMoveLeftOrRightInstead) {
            kwiatkowski_.setPosition(from);
            auto const moveOnlyLeftOrRight = sf::Vector2f(direction.x > 0 ? velocity_ : -velocity_, 0);
            kwiatkowski_.move(moveOnlyLeftOrRight);
        }
    }
}

auto Kwiatkowski::getGlobalBounds() const -> sf::FloatRect {
    auto defaultBounds = kwiatkowski_.getGlobalBounds();
    defaultBounds.left += 10;
    defaultBounds.top += 5;
    defaultBounds.width -= 20;
    defaultBounds.height -= 10;
    return defaultBounds;
}

auto Kwiatkowski::getPosition() const -> sf::Vector2f {
    return kwiatkowski_.getPosition();
}

auto Kwiatkowski::setPosition(float x, float y) -> void {
    kwiatkowski_.setPosition(x, y);
}


auto Kwiatkowski::update(Game& game) -> void {
    auto const& studentPtr = *std::ranges::find_if(game.entities(), [](std::unique_ptr<Entity> const& ptr) {
        return ptr->is<Student>();
    });

    auto const& student = studentPtr->as<Student>();
    moveTowards(student.getPosition(), game);

    auto direction = normalized(student.getPosition() - getPosition());

    auto const attemptToShootShortTest = currentHp_ > maxHp_ / 2;
    if (attemptToShootShortTest and canShootShortTest()) {
        game.spawnShootingShortTest(getPosition(), direction);
        shootingClockForShortTest_.restart();
    } else if (!attemptToShootShortTest and canShootCard()) {
        game.spawnShootingCard(getPosition(), direction);
        shootingClockForCard_.restart();
    }

    if (!isAlive_) {
        game.spawnVodkaIfNecessary();
    }

    if (currentHp_ <= maxHp_ / 2) {
        kwiatkowski_.setColor(sf::Color::Red);
    }
}

auto Kwiatkowski::draw(sf::RenderTarget& target, sf::RenderStates) const -> void {
    target.draw(kwiatkowski_);
}

auto Kwiatkowski::decreaseHp(int const damage) -> void {
    currentHp_ -= damage;
    if (currentHp_ <= 0) isAlive_ = false;
}

auto Kwiatkowski::canShootShortTest() const -> bool {
    return shootingClockForShortTest_.getElapsedTime().asSeconds() > shootingCooldownForShortTest_;
}

auto Kwiatkowski::canShootCard() const -> bool {
    return shootingClockForCard_.getElapsedTime().asSeconds() > shootingCooldownForCard_;
}

auto Kwiatkowski::serializeToString() const -> std::string {
    return fmt::format("Kwiatkowski {} {} {}", getPosition().x, getPosition().y, currentHp_);
}

auto Kwiatkowski::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(12);
    auto stream = std::istringstream(withoutType);
    float x = 0;
    float y = 0;
    stream >> x >> y >> currentHp_;
    setPosition(x, y);
}
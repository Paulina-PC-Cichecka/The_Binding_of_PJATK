#include "Chrzastowski.hpp"

#include <sstream>

#include "../../engine/Utility.hpp"
#include "../obstacles/Poop.hpp"
#include "../../engine/Game.hpp"
#include "../Student.hpp"
#include "fmt/color.h"

#include "SFML/Window/VideoMode.hpp"

Chrzastowski::Chrzastowski(sf::Texture const& body, sf::Vector2f const initialPosition) {
    chrzastowski_.setTexture(body);
    chrzastowski_.setTextureRect(sf::IntRect(0, 0, 41, 56));
    chrzastowski_.setScale(10, 10);
    chrzastowski_.setOrigin(41 / 2.0f, 56 / 2.0f);
    chrzastowski_.setPosition(initialPosition);
}

auto Chrzastowski::moveTowards(sf::Vector2f const destination, Game const& game) -> void {
    auto const from = chrzastowski_.getPosition();

    auto const direction = normalized(destination - from);

    chrzastowski_.move(direction * velocity_);

    auto const objectWeCollidedWith = std::ranges::find_if(
        game.collidables(), [this](Collidable* c) {
            return c->getGlobalBounds().intersects(getGlobalBounds()) and c->is<Poop>();
        }
    );

    auto const weCollidedWhileMoving = objectWeCollidedWith != game.collidables().end();

    if (weCollidedWhileMoving) {
        // go back
        chrzastowski_.setPosition(from);
        auto const moveOnlyUpOrDown = sf::Vector2f(0, direction.y > 0 ? velocity_ : -velocity_);
        chrzastowski_.move(moveOnlyUpOrDown);

        auto const needToMoveLeftOrRightInstead =
                (*objectWeCollidedWith)->getGlobalBounds().intersects(getGlobalBounds());

        if (needToMoveLeftOrRightInstead) {
            chrzastowski_.setPosition(from);
            auto const moveOnlyLeftOrRight = sf::Vector2f(direction.x > 0 ? velocity_ : -velocity_, 0);
            chrzastowski_.move(moveOnlyLeftOrRight);
        }
    }
}

auto Chrzastowski::getGlobalBounds() const -> sf::FloatRect {
    auto defaultBounds = chrzastowski_.getGlobalBounds();
    defaultBounds.left += 10;
    defaultBounds.top += 5;
    defaultBounds.width -= 20;
    defaultBounds.height -= 10;
    return defaultBounds;
}

auto Chrzastowski::getPosition() const -> sf::Vector2f {
    return chrzastowski_.getPosition();
}

auto Chrzastowski::setPosition(float x, float y) -> void {
    chrzastowski_.setPosition(x, y);
}

auto Chrzastowski::update(Game& game) -> void {
    auto const& studentPtr = *std::ranges::find_if(game.entities(), [](std::unique_ptr<Entity> const& ptr) {
        return ptr->is<Student>();
    });

    auto const& student = studentPtr->as<Student>();
    moveTowards(student.getPosition(), game);

    auto direction = normalized(student.getPosition() - getPosition());

    auto const attemptToShootPresent = currentHp_ > maxHp_ / 2;
    if (attemptToShootPresent and canShootPresent()) {
        game.spawnShootingPresent(getPosition(), direction);
        shootingClockForPresent_.restart();
    } else if (!attemptToShootPresent and canShootExam()) {
        game.spawnShootingExam(getPosition(), direction);
        shootingClockForExam_.restart();
    }

    if (!isAlive_) {
        game.displaySLAY();
    }

    if (currentHp_ <= maxHp_ / 2) {
        chrzastowski_.setColor(sf::Color::Red);
    }
}

auto Chrzastowski::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(chrzastowski_);
}

auto Chrzastowski::decreaseHp(int const damage) -> void {
    currentHp_ -= damage;
    if (currentHp_ <= 0) isAlive_ = false;
}

auto Chrzastowski::canShootPresent() const -> bool {
    return shootingClockForPresent_.getElapsedTime().asSeconds() > shootingCooldownForPresent_;
}

auto Chrzastowski::canShootExam() const -> bool {
    return shootingClockForExam_.getElapsedTime().asSeconds() > shootingCooldownForExam_;
}


auto Chrzastowski::serializeToString() const -> std::string {
    return fmt::format("Chrzastowski {} {} {}", getPosition().x, getPosition().y, currentHp_);
}

auto Chrzastowski::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(13);
    auto stream = std::istringstream(withoutType);
    float x = 0;
    float y = 0;
    stream >> x >> y >> currentHp_;
    setPosition(x, y);
}
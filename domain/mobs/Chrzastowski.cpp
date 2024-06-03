#include "Chrzastowski.hpp"

#include <sstream>

#include "../../engine/Utility.hpp"
#include "../obstacles/Poop.hpp"
#include "../../engine/Game.hpp"
#include "../Student.hpp"
#include "fmt/color.h"

#include "SFML/Window/VideoMode.hpp"

Chrzastowski::Chrzastowski(sf::Texture const& body) {
    chrzastowski_.setTexture(body);
    chrzastowski_.setTextureRect(sf::IntRect(12, 123, 71, 58));
    chrzastowski_.setScale(5, 5);
    chrzastowski_.setOrigin(71 / 2.0f, 58 / 2.0f);
    chrzastowski_.setPosition(sf::VideoMode::getDesktopMode().width / 2, 450);
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

    //TODO dodać strzelanie prezentami i egzaminami
}

auto Chrzastowski::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(chrzastowski_);
    target.draw(getOutline());
}

auto Chrzastowski::decreaseHp(int const damage) -> void {
    currentHp_ -= damage;
    if (currentHp_ <= 0) isAlive_ = false;
}

//TODO canShootPresent

//TODO canShootExams

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

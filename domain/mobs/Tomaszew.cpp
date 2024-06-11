#include "Tomaszew.hpp"

#include <sstream>

#include "../Student.hpp"
#include "../../engine/Utility.hpp"
#include "../obstacles/Poop.hpp"
#include "fmt/xchar.h"

#include "SFML/Graphics/RenderTarget.hpp"

Tomaszew::Tomaszew(sf::Texture const& body, sf::Vector2f const initialPosition) {
    tomaszew_.setTexture(body);
    tomaszew_.setTextureRect(sf::IntRect(1, 1, 25, 22));
    tomaszew_.setScale(6, 6);
    tomaszew_.setPosition(initialPosition);
}

auto Tomaszew::getPosition() const -> sf::Vector2f {
    return tomaszew_.getPosition();
}

auto Tomaszew::setPosition(float x, float y) -> void {
    tomaszew_.setPosition(x, y);
}

auto Tomaszew::moveTowards(sf::Vector2f const destination, Game const& game) -> void {
    auto from = tomaszew_.getPosition();

    auto direction = normalized(destination - from);

    tomaszew_.move(direction * velocity_);

    auto const objectWeCollidedWith = std::ranges::find_if(
        game.collidables(), [this](Collidable* c) {
            return c->getGlobalBounds().intersects(getGlobalBounds()) and c->is<Poop>();
        }
    );

    auto const weCollidedWhileMoving = objectWeCollidedWith != game.collidables().end();

    if (weCollidedWhileMoving) {
        // go back
        tomaszew_.setPosition(from);
        auto const moveOnlyUpOrDown = sf::Vector2f(0, direction.y > 0 ? velocity_ : -velocity_);
        tomaszew_.move(moveOnlyUpOrDown);

        auto const needToMoveLeftOrRightInstead =
                (*objectWeCollidedWith)->getGlobalBounds().intersects(getGlobalBounds());

        if (needToMoveLeftOrRightInstead) {
            tomaszew_.setPosition(from);
            auto const moveOnlyLeftOrRight = sf::Vector2f(direction.x > 0 ? velocity_ : -velocity_, 0);
            tomaszew_.move(moveOnlyLeftOrRight);
        }
    }
}


auto Tomaszew::getGlobalBounds() const -> sf::FloatRect {
    auto defaultBounds = tomaszew_.getGlobalBounds();
    defaultBounds.left += 10;
    defaultBounds.top += 5;
    defaultBounds.width -= 20;
    defaultBounds.height -= 10;
    return defaultBounds;
}

auto Tomaszew::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        if (damageClock_.getElapsedTime().asSeconds() > damageCooldown_) {
            other.as<Student>().decreaseHp(1);
            damageClock_.restart();
        }
    }
}

auto Tomaszew::update(Game& game) -> void {
    auto const& studentPtr = *std::ranges::find_if(
        game.entities(), [](std::unique_ptr<Entity> const& ptr) {
            return ptr->is<Student>();
        }
    );

    auto const& student = studentPtr->as<Student>();
    moveTowards(student.getPosition(), game);

    if (!isAlive_) {
        auto const allTomaszewsAreDead = std::ranges::none_of(
            game.entities(), [](std::unique_ptr<Entity> const& entity) {
                return entity->is<Tomaszew>() and entity->isAlive();
            }
        );
        if (allTomaszewsAreDead) {
            game.spawnSmyczkiIfNecessary();
        }
    }
}

auto Tomaszew::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(tomaszew_);
}

auto Tomaszew::decreaseHp(int const damage) -> void {
    currentHp_ -= damage;
    if (currentHp_ <= 0) isAlive_ = false;
}

auto Tomaszew::serializeToString() const -> std::string {
    return fmt::format("Tomaszewka {} {} {}", getPosition().x, getPosition().y, currentHp_);
}

auto Tomaszew::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(11);
    auto stream = std::istringstream(withoutType);
    auto x = float();
    auto y = float();
    stream >> x >> y >> currentHp_;
    setPosition(x, y);
}
#include "Smyczek.hpp"

#include <sstream>

#include "../../engine/Utility.hpp"
#include "../../engine/Game.hpp"
#include "../obstacles/Poop.hpp"
#include "../Student.hpp"
#include "fmt/xchar.h"

#include "SFML/Graphics/RenderTarget.hpp"

Smyczek::Smyczek(sf::Texture const& body, sf::Vector2f const initialPosition) {
    smyczek_.setTexture(body);
    smyczek_.setTextureRect(sf::IntRect(34, 20, 27, 43));
    smyczek_.setScale(5, 5);
    smyczek_.setOrigin(27 / 2.0f, 43 / 2.0f);
    smyczek_.setPosition(initialPosition);
}

auto Smyczek::getPosition() const -> sf::Vector2f {
    return smyczek_.getPosition();
}


auto Smyczek::moveTowards(sf::Vector2f const destination, Game const& game) -> void {
    auto const from = smyczek_.getPosition();

    auto const direction = normalized(destination - from);

    smyczek_.move(direction * velocity_);

    auto const objectWeCollidedWith = std::ranges::find_if(
        game.collidables(), [this](Collidable* c) {
            return c->getGlobalBounds().intersects(getGlobalBounds()) and c->is<Poop>();
        }
    );

    auto const weCollidedWhileMoving = objectWeCollidedWith != game.collidables().end();

    if (weCollidedWhileMoving) {
        // go back
        smyczek_.setPosition(from);
        auto const moveOnlyUpOrDown = sf::Vector2f(0, direction.y > 0 ? velocity_ : -velocity_);
        smyczek_.move(moveOnlyUpOrDown);

        auto const needToMoveLeftOrRightInstead =
                (*objectWeCollidedWith)->getGlobalBounds().intersects(getGlobalBounds());

        if (needToMoveLeftOrRightInstead) {
            smyczek_.setPosition(from);
            auto const moveOnlyLeftOrRight = sf::Vector2f(direction.x > 0 ? velocity_ : -velocity_, 0);
            smyczek_.move(moveOnlyLeftOrRight);
        }
    }
}


auto Smyczek::getGlobalBounds() const -> sf::FloatRect {
    auto defaultBounds = smyczek_.getGlobalBounds();
    defaultBounds.left += 10;
    defaultBounds.top += 5;
    defaultBounds.width -= 20;
    defaultBounds.height -= 10;
    return defaultBounds;
}

auto Smyczek::getPosition() -> sf::Vector2f {
    return smyczek_.getPosition();
}

auto Smyczek::setPosition(float x, float y) -> void {
    smyczek_.setPosition(x, y);
}


auto Smyczek::update(Game& game) -> void {
    auto const& studentPtr = *std::ranges::find_if(game.entities(), [](std::unique_ptr<Entity> const& ptr) {
            return ptr->is<Student>();
        });

    auto const& student = studentPtr->as<Student>();
    moveTowards(student.getPosition(), game);

    auto direction = normalized(student.getPosition() - getPosition());

    if (canShoot()) {
        game.spawnShootingBush(getPosition(), direction);
        shootingClock_.restart();
    }

    if (!isAlive_) {
        auto const allSmyczeksAreDead = std::ranges::none_of(
            game.entities(), [](std::unique_ptr<Entity> const& entity) {
                return entity->is<Smyczek>() and entity->isAlive();
            }
        );
        if (allSmyczeksAreDead) {
            game.spawnKwiatkowskiIfNecessary();
        }
    }
}

auto Smyczek::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(smyczek_);
}

auto Smyczek::canShoot() const -> bool {
    return shootingClock_.getElapsedTime().asSeconds() > shootingCooldown_;
}

auto Smyczek::decreaseHp(int const damage) -> void {
    currentHp_ -= damage;

    if (currentHp_ <= 0) isAlive_ = false;
}

auto Smyczek::serializeToString() const -> std::string {
    return fmt::format("Smyczek {} {} {}", getPosition().x, getPosition().y, currentHp_);
}

auto Smyczek::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(8);
    auto stream = std::istringstream(withoutType);
    auto x = float();
    auto y = float();
    stream >> x >> y >> currentHp_;
    setPosition(x, y);
}
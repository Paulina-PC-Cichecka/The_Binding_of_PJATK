#include <algorithm>

#include "Kwiatkowski.hpp"
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
    auto from = kwiatkowski_.getPosition();

    auto direction = normalized(destination - from);
    {
        kwiatkowski_.move(direction);

        auto objectWeCollidedWith = std::ranges::find_if(
            game.collidables(), [this](Collidable* c) {
                return c->getGlobalBounds().intersects(getGlobalBounds()) and c->is<Poop>();
            }
        );

        auto const weCollidedWhileMoving = objectWeCollidedWith != game.collidables().end();

        if (weCollidedWhileMoving) {
            fmt::println("about to collide!");
            // go back
            kwiatkowski_.setPosition(from);
            auto& obj = **objectWeCollidedWith;

            if (obj.getGlobalBounds().intersects(getGlobalBounds())) fmt::println("we went back and are STILL colliding... (1)");

            auto alteredDirection = direction;
            alteredDirection.x = -2; // TODO: ujemne czy dodatanie?
            alteredDirection.y = 1;
            kwiatkowski_.move(alteredDirection);
            if (obj.getGlobalBounds().intersects(getGlobalBounds())) {
                // still intersecting, go back and change `y` instead
                kwiatkowski_.setPosition(from);
                if (obj.getGlobalBounds().intersects(getGlobalBounds())) fmt::println("we went back and are STILL colliding... (2)");
            } else {
                alteredDirection = direction;
                alteredDirection.y = -2; // TODO: ujemne czy dodatnie?
                alteredDirection.x = 1;
                kwiatkowski_.move(alteredDirection);
                if (obj.getGlobalBounds().intersects(getGlobalBounds())) fmt::println("we went back and are STILL colliding... (3)");
            }
        } else {
            kwiatkowski_.move(direction);
        }
    }
    // auto const placeToMove = getPosition() + direction;
    // auto objectWeAreAboutToCollideWith = std::ranges::find_if(
    //     game.collidables(), [placeToMove](Collidable* c) {
    //         return c->getGlobalBounds().contains(placeToMove) and c->is<Poop>();
    //     }
    // );
    //
    // if (objectWeAreAboutToCollideWith != game.collidables().end()) {
    //     auto& obj = **objectWeAreAboutToCollideWith;
    //     auto alteredPlaceToMove = placeToMove;
    //     alteredPlaceToMove.x = 0;
    //     if (not obj.getGlobalBounds().contains(alteredPlaceToMove)) {
    //         kwiatkowski_.setPosition(alteredPlaceToMove);
    //     } else {
    //         alteredPlaceToMove = placeToMove;
    //         alteredPlaceToMove.y = 0;
    //         kwiatkowski_.setPosition(alteredPlaceToMove);
    //     }
    // } else {
    //     kwiatkowski_.move(direction);
    // }
}

auto Kwiatkowski::getGlobalBounds() const -> sf::FloatRect {
    return kwiatkowski_.getGlobalBounds();
}

auto Kwiatkowski::getPosition() -> sf::Vector2f {
    return kwiatkowski_.getPosition();
}

auto Kwiatkowski::update(Game& game) -> void {
    auto const& studentPtr = *std::ranges::find_if(game.entities(), [](std::unique_ptr<Entity> const& ptr) {
        return ptr->is<Student>();
    });

    auto const& student = studentPtr->as<Student>();
    moveTowards(student.getPosition(), game);

    auto direction = normalized(student.getPosition() - getPosition());

    if (canShoot()) {
        game.spawnShootingShortTest(getPosition(), direction);
        shootingClock_.restart();
    }
}

auto Kwiatkowski::draw(sf::RenderTarget& target, sf::RenderStates) const -> void {
    target.draw(kwiatkowski_);
}

auto Kwiatkowski::decreaseHp() -> void {
    currentHp_ -= 1;
    if (currentHp_ == 0) isAlive_ = false;
}

auto Kwiatkowski::canShoot() const -> bool {
    return shootingClock_.getElapsedTime().asSeconds() > shootingCooldown_;
}
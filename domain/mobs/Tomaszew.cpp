#include "Tomaszew.hpp"

#include "../Student.hpp"
#include "../../engine/Utility.hpp"
#include "../obstacles/Poop.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

Tomaszew::Tomaszew(sf::Texture const& body, sf::Vector2f const initialPosition) {
    tomaszew_.setTexture(body);
    tomaszew_.setTextureRect(sf::IntRect(2, 5, 27, 24));
    tomaszew_.setScale(5, 5);
    tomaszew_.setPosition(initialPosition);
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
    return tomaszew_.getGlobalBounds();
}

auto Tomaszew::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        if (damageClock_.getElapsedTime().asSeconds() > damageCooldown_) {
            other.as<Student>().decreaseHp();
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
}

auto Tomaszew::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(tomaszew_);
}

auto Tomaszew::decreaseHp() -> void {
    currentHp_ -= 1;
    if (currentHp_ == 0) isAlive_ = false;
}


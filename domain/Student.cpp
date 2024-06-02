#include <algorithm>
#include <iterator>

#include "Student.hpp"

#include "fmt/core.h"
#include "obstacles/Poop.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

Student::Student(
    sf::Texture const& bodyTexture, sf::Texture const& heartTexture, sf::Vector2f const initialPosition
) : scale_(5, 5), heart_(heartTexture) {
    head_.setTexture(bodyTexture);
    head_.setTextureRect(sf::IntRect(10, 25, 28, 24));
    head_.setScale(scale_);
    head_.setOrigin(28 / 2.0f, 24 / 2.0f);
    head_.setPosition(initialPosition);

    body_.setTexture(bodyTexture);
    body_.setTextureRect(sf::IntRect(15, 80, 18, 12));
    body_.setScale(scale_);
    body_.setOrigin(18 / 2.0f, 12 / 2.0f);
    body_.setPosition(initialPosition + sf::Vector2f(0, 14 * scale_.y));
}

auto Student::getGlobalBounds() const -> sf::FloatRect {
    auto topLeft = head_.getPosition();
    return sf::FloatRect(
        topLeft.x, topLeft.y,
        head_.getGlobalBounds().width,
        head_.getGlobalBounds().height + body_.getGlobalBounds().height
    );
}

auto Student::getPosition() const -> sf::Vector2f {
    return head_.getPosition();
}

auto Student::draw(sf::RenderTarget& target, sf::RenderStates) const -> void {
    target.draw(body_);
    target.draw(head_);

    auto spaceBetweenHearts = 70.0f;

    for (auto i = 0; i < currentHp_ / 2; ++i) {
        auto xPosition = i * spaceBetweenHearts;
        auto fullHeart = sf::Sprite();
        fullHeart.setTexture(heart_);
        fullHeart.setTextureRect(sf::IntRect(1, 1, 12, 11));
        fullHeart.setPosition(xPosition, 0);
        fullHeart.setScale(scale_);
        target.draw(fullHeart);
    }

    if (currentHp_ % 2 != 0) {
        auto halfHeart = sf::Sprite();
        halfHeart.setTexture(heart_);
        halfHeart.setTextureRect(sf::IntRect(17, 1, 12, 11));
        halfHeart.setPosition(currentHp_ / 2 * spaceBetweenHearts, 0);
        halfHeart.setScale(scale_);
        target.draw(halfHeart);
    }

}

auto Student::update(Game& game) -> void {
    auto xOffset = 0.0f;
    auto yOffset = 0.0f;

    if (movingLeft) xOffset -= velocity_;
    if (movingRight) xOffset += velocity_;
    if (movingUp) yOffset -= velocity_;
    if (movingDown) yOffset += velocity_;

    auto nextPosition = head_.getPosition() + sf::Vector2f(xOffset, yOffset);

    auto obstacles = std::vector<Collidable*>();
    std::ranges::copy_if(game.collidables(), std::back_inserter(obstacles), [](Collidable const* ptr) {
        return ptr->is<Poop>();
    });

    auto const willNotCollideWithAnyObstacles = std::ranges::none_of(obstacles, [nextPosition](Collidable const* ptr) {
        return ptr->getGlobalBounds().contains(nextPosition);
    });

    if (game.movementSurface().contains(nextPosition) and willNotCollideWithAnyObstacles) {
        head_.move(xOffset, yOffset);
        body_.move(xOffset, yOffset);
    }

    if (canShoot()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            game.spawnShootingTear(getPosition(), {1.0f, 0}, tearScale_);
            shootingClock_.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            game.spawnShootingTear(getPosition(), {-1.0f, 0}, tearScale_);
            shootingClock_.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            game.spawnShootingTear(getPosition(), {0, -1.0f}, tearScale_);
            shootingClock_.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            game.spawnShootingTear(getPosition(), {0, 1.0f}, tearScale_);
            shootingClock_.restart();
        }
    }
}

auto Student::canShoot() const -> bool {
    return shootingClock_.getElapsedTime().asSeconds() > shootingCooldown_;
}

auto Student::startMovingLeft() -> void { movingLeft = true; }

auto Student::startMovingRight() -> void { movingRight = true; }

auto Student::startMovingUp() -> void { movingUp = true; }

auto Student::startMovingDown() -> void { movingDown = true; }

auto Student::stopMovingLeft() -> void { movingLeft = false; }

auto Student::stopMovingRight() -> void { movingRight = false; }

auto Student::stopMovingUp() -> void { movingUp = false; }

auto Student::stopMovingDown() -> void { movingDown = false; }

auto Student::decreaseHp() -> void {
    currentHp_ -= 1;
    if (currentHp_ == 0) isAlive_ = false;
}

auto Student::makeTearsBigger() -> void {
    tearScale_ += 1;
}

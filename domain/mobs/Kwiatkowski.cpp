#include "Kwiatkowski.hpp"
#include "../Student.hpp"

#include "../../engine/Utility.hpp"
#include "../../engine/Game.hpp"

Kwiatkowski::Kwiatkowski(sf::Texture const& body) {
    kwiatkowski_.setTexture(body);
    kwiatkowski_.setTextureRect(sf::IntRect(0, 0, 32, 40));
    kwiatkowski_.setScale(8, 8);
    kwiatkowski_.setOrigin(32 / 2.0f, 40 / 2.0f);
    kwiatkowski_.setPosition(600, 600);
}

auto Kwiatkowski::moveTowards(sf::Vector2f const destination) -> void {
    auto from = kwiatkowski_.getPosition();

    auto direction = normalized(destination - from);

    kwiatkowski_.move(direction);
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
    moveTowards(student.getPosition());

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
#include "Exam.hpp"

#include <sstream>

#include "../Student.hpp"
#include "../obstacles/Poop.hpp"
#include "../../engine/Game.hpp"
#include "fmt/format.h"

#include "SFML/Graphics/RenderTarget.hpp"

Exam::Exam(
    sf::Texture const& examTexture,
    sf::Vector2f const startingPosition,
    sf::Vector2f const direction
) : direction_(direction * velocity_) {
    exam_.setTexture(examTexture);
    exam_.setTextureRect(sf::IntRect(0, 0, 1157, 314));
    exam_.setScale(0.1, 0.1);
    exam_.setOrigin(1157 / 2.0f, 314 / 2.0f);
    exam_.setPosition(startingPosition);
}

auto Exam::getGlobalBounds() const -> sf::FloatRect {
    auto originalBounds = exam_.getGlobalBounds();
    originalBounds.left += 10;
    originalBounds.top += 10;
    originalBounds.width -= 20;
    originalBounds.height -= 20;
    return originalBounds;
}

auto Exam::update(Game& game) -> void {
    exam_.move(direction_);
    exam_.rotate(2);

    auto const isOnValidMovementSurface = std::ranges::any_of(game.movementSurface(), [this](sf::FloatRect const rect) {
        return rect.contains(exam_.getPosition());
    });
    if (not isOnValidMovementSurface) {
        isAlive_ = false;
    }
}

auto Exam::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(exam_);
}

auto Exam::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().decreaseHp(2);
        isAlive_ = false;
    }
}

auto Exam::serializeToString() const -> std::string {
    return fmt::format("Exam {} {} {} {}", exam_.getPosition().x, exam_.getPosition().y, direction_.x, direction_.y);
}

auto Exam::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(5);
    auto stream = std::istringstream(withoutType);
    auto x = float();
    auto y = float();
    stream >> x >> y >> direction_.x >> direction_.y;
    exam_.setPosition(x, y);
}

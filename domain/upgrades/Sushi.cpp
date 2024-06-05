#include "Sushi.hpp"
#include "../Student.hpp"
#include "fmt/args.h"

#include "SFML/Graphics/RenderTarget.hpp"

Sushi::Sushi(sf::Texture const& sushiTexture, sf::Vector2f const initialPositon) {
    sushi_.setTexture(sushiTexture);
    sushi_.setTextureRect(sf::IntRect(52, 52, 429, 429));
    sushi_.setScale(0.2, 0.2);
    sushi_.setOrigin(429 / 2.0f, 429 / 2.0f);
    sushi_.setPosition(initialPositon);
}

auto Sushi::getGlobalBounds() const -> sf::FloatRect {
    auto defaultBounds = sushi_.getGlobalBounds();
    defaultBounds.left += 10;
    defaultBounds.top += 5;
    defaultBounds.width -= 20;
    defaultBounds.height -= 10;
    return defaultBounds;
}

auto Sushi::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(sushi_);
}

auto Sushi::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().increaseHp(4);
        isAlive_ = false;
    }
}

auto Sushi::serializeToString() const -> std::string {
    return "Sushi";
}

auto Sushi::deserializeFromString(const std::string&) -> void {

}


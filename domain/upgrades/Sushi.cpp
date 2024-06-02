#include "Sushi.hpp"
#include "../Student.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

Sushi::Sushi(sf::Texture const& sushiTexture, sf::Vector2f const initialPositon) {
    sushi_.setTexture(sushiTexture);
    sushi_.setTextureRect(sf::IntRect(13, 51, 607, 237));
    sushi_.setScale(0.2, 0.2);
    sushi_.setOrigin(607 / 2.0f, 237 / 2.0f);
    sushi_.setPosition(initialPositon);
}

auto Sushi::getGlobalBounds() const -> sf::FloatRect {
    return sushi_.getGlobalBounds();
}

auto Sushi::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(sushi_);
}

auto Sushi::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().increaseHp();
        isAlive_ = false;
    }
}

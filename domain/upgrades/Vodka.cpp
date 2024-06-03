#include "Vodka.hpp"

#include "../Student.hpp"

#include "SFML/Graphics/RenderTarget.hpp"


Vodka::Vodka(sf::Texture const& vodkaTexture, sf::Vector2f const initialPosition) {
    vodka_.setTexture(vodkaTexture);
    vodka_.setTextureRect(sf::IntRect(11, 251, 17, 26));
    vodka_.setScale(5, 5);
    vodka_.setOrigin(17 / 2.0f, 26 / 2.0f);
    vodka_.setPosition(initialPosition);
}

auto Vodka::getGlobalBounds() const -> sf::FloatRect {
    auto defaultBounds = vodka_.getGlobalBounds();
    defaultBounds.left += 10;
    defaultBounds.top += 5;
    defaultBounds.width -= 20;
    defaultBounds.height -= 10;
    return defaultBounds;
}

auto Vodka::update(Game& game) -> void {

}

auto Vodka::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(vodka_);
}

auto Vodka::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().increaseDamage();
        isAlive_ = false;
    }
}


auto Vodka::serializeToString() const -> std::string {
    return "Vodka";
}

auto Vodka::deserializeFromString(const std::string&) -> void {

}
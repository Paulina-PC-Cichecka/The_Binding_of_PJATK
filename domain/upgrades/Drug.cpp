#include "Drug.hpp"
#include "../Student.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

Drug::Drug(sf::Texture const& drugTexture, sf::Vector2f const initialPosition) {
    drug_.setTexture(drugTexture);
    drug_.setTextureRect(sf::IntRect(39, 37, 16, 16));
    drug_.setScale(5, 5);
    drug_.setOrigin(16 / 2.0f, 16 / 2.0f);
    drug_.setPosition(initialPosition);
}

auto Drug::getGlobalBounds() const -> sf::FloatRect {
    return drug_.getGlobalBounds();
}

auto Drug::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(drug_);
}

auto Drug::onCollisionWith(Collidable& other) -> void {

    if (other.is<Student>()) {
        other.as<Student>().makeTearsBigger();
        isAlive_ = false;
    }
}

auto Drug::serializeToString() const -> std::string {
    return "Drug";
}

auto Drug::deserializeFromString(const std::string&) -> void {

}


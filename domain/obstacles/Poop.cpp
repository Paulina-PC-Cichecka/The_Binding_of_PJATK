#include "Poop.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

Poop::Poop(sf::Texture const& poopTexture, sf::Vector2f const initialPosition) {
    poop_.setTexture(poopTexture);
    poop_.setTextureRect(sf::IntRect(168, 5, 29, 26));
    poop_.setScale(5, 5);
    poop_.setOrigin(27 / 2.0f, 26 / 2.0f);
    poop_.setPosition(initialPosition);
}

auto Poop::getGlobalBounds() const -> sf::FloatRect {
    return poop_.getGlobalBounds();
}

auto Poop::update(Game&) -> void {

}

auto Poop::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(poop_);
}
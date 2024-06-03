#include "Poop.hpp"

#include <sstream>

#include "fmt/xchar.h"
#include "SFML/Graphics/RenderTarget.hpp"

Poop::Poop(sf::Texture const& poopTexture, sf::Vector2f const initialPosition) {
    poop_.setTexture(poopTexture);
    poop_.setTextureRect(sf::IntRect(168, 5, 29, 26));
    poop_.setScale(5, 5);
    poop_.setOrigin(27 / 2.0f, 26 / 2.0f);
    poop_.setPosition(initialPosition);
}

auto Poop::getPosition() const -> sf::Vector2f {
    return poop_.getPosition();
}

auto Poop::setPosition(float x, float y) -> void {
    poop_.setPosition(x, y);
}


auto Poop::getGlobalBounds() const -> sf::FloatRect {
    return poop_.getGlobalBounds();
}

auto Poop::update(Game&) -> void {

}

auto Poop::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(poop_);
}

auto Poop::serializeToString() const -> std::string {
    return fmt::format("Poop {} {}", getPosition().x, getPosition().y);
}

auto Poop::deserializeFromString(const std::string& str) -> void {
    auto const withoutType = str.substr(5);
    auto stream = std::istringstream(withoutType);
    auto x = float();
    auto y = float();
    stream >> x >> y;
    setPosition(x, y);
}

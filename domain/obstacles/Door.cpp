#include "Door.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

Door::Door(sf::Texture const& doorTexture, sf::Vector2f const initialPosition) {
    openDoor_.setTexture(doorTexture);
    openDoor_.setTextureRect(sf::IntRect(611, 274, 24, 22));
    openDoor_.setScale(5, 5);
    openDoor_.setOrigin(24 / 2.0f, 22 / 2.0f);
    openDoor_.setPosition(initialPosition);
}

auto Door::getGlobalBounds() const -> sf::FloatRect {
    auto defaultBounds = openDoor_.getGlobalBounds();
    defaultBounds.left += 10;
    defaultBounds.top += 5;
    defaultBounds.width -= 20;
    defaultBounds.height -= 10;
    return defaultBounds;
}

auto Door::update(Game& game) -> void {

}

auto Door::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(openDoor_);
}

auto Door::onCollisionWith(Collidable& other) -> void {

}
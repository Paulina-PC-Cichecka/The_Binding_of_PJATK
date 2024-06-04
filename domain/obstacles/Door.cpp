#include "Door.hpp"

#include "../Student.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

Door::Door(sf::Texture const& doorTexture, sf::Vector2f const initialPosition) {
    openDoor_.setTexture(doorTexture);
    openDoor_.setTextureRect(sf::IntRect(611, 274, 24, 22));
    openDoor_.setScale(6.8, 5);
    openDoor_.setOrigin(24 / 2.0f, 22 / 2.0f);
    openDoor_.setPosition(initialPosition);

    doorLeftPart_.setTexture(doorTexture);
    doorLeftPart_.setTextureRect(sf::IntRect(545, 322, 14, 22));
    doorLeftPart_.setScale(5, 5);
    doorLeftPart_.setOrigin(14 / 2.0f, 22 / 2.0f);
    doorLeftPart_.setPosition(initialPosition + sf::Vector2f(-40, 0));

    doorRightPart_.setTexture(doorTexture);
    doorRightPart_.setTextureRect(sf::IntRect(623, 322, 15, 22));
    doorRightPart_.setScale(5, 5);
    doorRightPart_.setOrigin(15 / 2.0f, 22 / 2.0f);
    doorRightPart_.setPosition(initialPosition + sf::Vector2f(+32, 0));

    doorFrame_.setTexture(doorTexture);
    doorFrame_.setTextureRect(sf::IntRect(529, 261, 61, 38));
    doorFrame_.setScale(5, 5);
    doorFrame_.setOrigin(61 / 2.0f, 38 / 2.0f);
    doorFrame_.setPosition(initialPosition + sf::Vector2f(0, -30));
}

auto Door::getGlobalBounds() const -> sf::FloatRect {
    auto defaultBounds = doorFrame_.getGlobalBounds();
    defaultBounds.left += 10;
    defaultBounds.top += 5;
    defaultBounds.width -= 20;
    defaultBounds.height -= 10;
    return defaultBounds;
}

auto Door::update(Game& game) -> void {

}

auto Door::open() -> void {
    doorLeftPart_.setColor(sf::Color::Transparent);
    doorRightPart_.setColor(sf::Color::Transparent);

    isOpen_ = true;
}


auto Door::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(openDoor_);
    target.draw(doorLeftPart_);
    target.draw(doorRightPart_);
    target.draw(doorFrame_);
}

auto Door::onCollisionWith(Collidable& other) -> void {

}

auto Door::serializeToString() const -> std::string {
    return "Door";
}

auto Door::deserializeFromString(const std::string&) -> void {

}


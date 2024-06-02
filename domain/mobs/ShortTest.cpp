#include "ShortTest.hpp"

#include "Kwiatkowski.hpp"
#include "../obstacles/Poop.hpp"
#include "../Student.hpp"
#include "../Tear.hpp"
#include "../../engine/Game.hpp"
#include "../../engine/Utility.hpp"
#include "SFML/Graphics/RenderTarget.hpp"


ShortTest::ShortTest(sf::Texture const& texture, sf::Vector2f const startingPosition, sf::Vector2f const direction
    ) : direction_((direction * velocity)) {
    shortTest_.setTexture(texture);
    shortTest_.setTextureRect(sf::IntRect(22, 45, 337, 269));
    shortTest_.setScale(sf::Vector2f(0.3, 0.3));
    shortTest_.setOrigin(sf::Vector2f(337 / 2.0f, 269 / 2.0f));
    shortTest_.setPosition(startingPosition);
}


auto ShortTest::draw(sf::RenderTarget& target, sf::RenderStates) const -> void {
    target.draw(shortTest_);

}

auto ShortTest::update(Game& game) -> void {
    shortTest_.move(direction_);

    if (not game.movementSurface().contains(shortTest_.getPosition())) {
        isAlive_ = false;
    }
}

auto ShortTest::getGlobalBounds() const -> sf::FloatRect {
    return shortTest_.getGlobalBounds();
}

auto ShortTest::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().decreaseHp();
        isAlive_ = false;
    }

    if (other.is<Poop>()) isAlive_ = false;
}
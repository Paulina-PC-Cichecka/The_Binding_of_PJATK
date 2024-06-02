#include "Boots.hpp"

#include "../Student.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

Boots::Boots(sf::Texture const& bootsTexture, sf::Vector2f const initialPosition) {
    boots_.setTexture(bootsTexture);
    boots_.setTextureRect(sf::IntRect(0, 10, 159, 139));
    boots_.setScale(0.5, 0.5);
    boots_.setOrigin(159 / 2.0f, 139 / 2.0f);
    boots_.setPosition(initialPosition);
}

auto Boots::getGlobalBounds() const -> sf::FloatRect {
    return boots_.getGlobalBounds();
}

auto Boots::update(Game& game) -> void {

}

auto Boots::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(boots_);
}

auto Boots::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        other.as<Student>().becomeFAST();
        isAlive_ = false;
    }
}

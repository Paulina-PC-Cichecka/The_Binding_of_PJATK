#include "Vodka.hpp"

#include "../Student.hpp"
#include "../obstacles/Door.hpp"

#include "SFML/Graphics/RenderTarget.hpp"


Vodka::Vodka(sf::Texture const& vodkaTexture, sf::Vector2f const initialPosition) {
    vodka_.setTexture(vodkaTexture);
    vodka_.setTextureRect(sf::IntRect(153, 60, 177, 653));
    vodka_.setScale(0.3, 0.3);
    vodka_.setOrigin(177 / 2.0f, 653 / 2.0f);
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
    if (!isAlive_) {
        auto const& doorPtr = *std::ranges::find_if(
                game.entities(), [](std::unique_ptr<Entity> const& ptr) {
                    return ptr->is<Door>();
                }
            );

        auto& door = doorPtr->as<Door>();

        door.open();
    }
}

auto Vodka::draw(sf::RenderTarget& target, sf::RenderStates states) const -> void {
    target.draw(vodka_);
}

auto Vodka::onCollisionWith(Collidable& other) -> void {
    if (other.is<Student>()) {
        auto& student = other.as<Student>();
        student.increaseDamage();
        student.fullyHeal();
        isAlive_ = false;
    }
}


auto Vodka::serializeToString() const -> std::string {
    return "Vodka";
}

auto Vodka::deserializeFromString(const std::string&) -> void {

}
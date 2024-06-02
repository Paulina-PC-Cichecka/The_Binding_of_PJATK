#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Assets.hpp"
#include "Entity.hpp"
#include "Collidable.hpp"

class Student;

class Game {
    sf::RenderWindow& window_;

    std::vector<std::unique_ptr<Entity>> entities_;
    std::vector<Collidable*> collidables_;
    std::vector<sf::Drawable*> drawables_;

    std::vector<std::unique_ptr<Entity>> enqueuedEntities_;
    std::vector<Collidable*> enqueuedCollidables_;
    std::vector<sf::Drawable*> enqueuedDrawables_;

    Assets assets_;
    bool kwiatkowskiWasSpawned = false;

    sf::FloatRect movementSurface_;
public:
    explicit Game(sf::RenderWindow& window);
    Game(Game const&) = delete;

    auto spawnShootingTear(sf::Vector2f const, sf::Vector2f const, float const tearScale) -> void;

    auto spawnShootingShortTest(sf::Vector2f const, sf::Vector2f const) -> void;

    auto handleKeyPressed(sf::Event const event) -> void;

    auto handleKeyReleased(sf::Event const event) -> void;

    auto handleEvent(sf::Event const event) -> void;

    auto handleCollisions() -> void;

    auto addAllNewRegisteredEntities() -> void;

    auto performUpdates() -> void;

    auto renderFrame() -> void;

    auto pollAndHandleEvents() -> void;

    auto removeAllDeadElements() -> void;

    auto movementSurface() const -> sf::FloatRect {
        return movementSurface_;
    }

    auto entities() const -> std::vector<std::unique_ptr<Entity>> const& {
        return entities_;
    }

    auto collidables() const -> std::vector<Collidable*> const& {
        return collidables_;
    }

    auto drawables() const -> std::vector<sf::Drawable*> const& {
        return drawables_;
    }

    auto spawnKwiatkowskiIfNecessary() -> void;
};

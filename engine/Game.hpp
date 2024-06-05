#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Assets.hpp"
#include "Entity.hpp"
#include "Collidable.hpp"
#include "Utility.hpp"

class Student;

class Game {
    sf::RenderWindow& window_;
    bool on_ = true;

    std::vector<std::unique_ptr<Entity> > entities_;
    std::vector<Collidable*> collidables_;
    std::vector<sf::Drawable*> drawables_;

    std::vector<std::unique_ptr<Entity> > enqueuedEntities_;
    std::vector<Collidable*> enqueuedCollidables_;
    std::vector<sf::Drawable*> enqueuedDrawables_;

    Assets assets_;
    bool vodkaWasSpawned_ = false;
    bool kwiatkowskiWasSpawned_ = false;
    bool chrzastowskiWasSpawned_ = false;
    bool tomaszewkiWereSpawned_ = false;
    bool smyczkiWereSpawned_ = false;

    std::vector<sf::FloatRect> movementSurfaces_;

    std::string defaultSaveFilePath_ = "default.save";

    sf::Text slay_;

    sf::Sprite gameOver_;
    sf::Sprite gameOver2_;
    float scaleChange_ = -0.02;
    sf::Clock pulsatingClock_;
    double pulsatingClickInterval_ = 0.5;

    bool shouldDisplaySlay_ = false;
    bool shouldDisplayGameOver_ = false;

public:
    auto spawnSushi() -> Entity*;

    auto spawnPoop(sf::Vector2f const) -> Entity*;

    auto spawnBoots() -> Entity*;

    auto spawnDrug() -> Entity*;

    auto spawnVodka() -> Entity*;

    auto spawnChrzastowski() -> Entity*;

    auto spawnDoor() -> Entity*;

    auto window() -> sf::RenderWindow&;

    auto assets() -> Assets const&;

    auto stop() -> void;

    explicit Game(sf::RenderWindow& window);

    Game(Game const&) = delete;

    auto spawnStudent() -> Entity*;

    auto spawnShootingTear(sf::Vector2f const, sf::Vector2f const, float const,
                           int const) -> Entity*;

    auto spawnShootingShortTest(sf::Vector2f const, sf::Vector2f const) -> Entity*;

    auto spawnShootingPresent(sf::Vector2f const, sf::Vector2f const) -> Entity*;

    auto handleKeyPressed(sf::Event const event) -> void;

    auto handleKeyReleased(sf::Event const event) -> void;

    auto updateAllEntities() -> void;

    auto handleEvent(sf::Event const event) -> void;

    auto handleCollisions() -> void;

    auto addAllNewRegisteredEntities() -> void;

    auto reorderDrawables() -> void;

    auto performUpdates() -> void;

    auto renderFrame() -> void;

    auto pollAndHandleEvents() -> void;

    auto removeAllDeadElements() -> void;

    auto displaySLAY() -> void;

    auto movementSurface() const -> std::vector<sf::FloatRect> const& {
        return movementSurfaces_;
    }

    auto entities() const -> std::vector<std::unique_ptr<Entity> > const& {
        return entities_;
    }

    auto collidables() const -> std::vector<Collidable*> const& {
        return collidables_;
    }

    auto drawables() const -> std::vector<sf::Drawable*> const& {
        return drawables_;
    }

    auto spawnVodkaIfNecessary() -> void;

    auto spawnKwiatkowskiIfNecessary() -> void;

    auto spawnChrzastowskiIfNecessary() -> void;

    auto spawnTomaszewkiIfNecessary() -> void;

    auto spawnSmyczkiIfNecessary() -> void;

    auto spawnShootingCard(sf::Vector2f const, sf::Vector2f const) -> Entity*;

    auto spawnShootingExam(sf::Vector2f const, sf::Vector2f const) -> Entity*;

    auto spawnShootingBush(sf::Vector2f const, sf::Vector2f const) -> Entity*;

    auto saveAllEntitiesToFile(std::string const&) const -> void;

    auto loadAllEntitiesFromFile(std::string const&) -> void;

    auto createEntityUsingSerialization(const std::string&) -> void;

    auto clearAllEntities() -> void;

    auto displayGameOver() -> void;

private:
    // used for loading (in the future maybe used for delegation) - nothing else should call these unconditionally
    auto spawnTomaszewkaAt(float const = randomize(320, 2500),
                           float const = randomize(320, 1000)) -> Entity*;

    auto spawnSmyczekAt(float const = randomize(320, 2500),
                        float const = randomize(320, 1000)) -> Entity*;

    auto spawnKwiatkowski() -> Entity*;
};
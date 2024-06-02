#include <stdexcept>
#include <memory>
#include <utility>

#include "Game.hpp"

#include "../domain/mobs/Kwiatkowski.hpp"
#include "../domain/obstacles/Poop.hpp"
#include "../domain/Student.hpp"
#include "../domain/Tear.hpp"
#include "../domain/mobs/ShortTest.hpp"
#include "../domain/upgrates/Boots.hpp"
#include "../domain/upgrates/Drug.hpp"
#include "../domain/upgrates/Sushi.hpp"

Game::Game(sf::RenderWindow& window)
    : window_(window), movementSurface_(319.0f, 319.0f, 2241.0f, 1186.0f) {
    assets_.loadBasement();
    assets_.loadStudent();
    assets_.loadTear();
    assets_.loadHeart();
    assets_.loadKwiatkowski();
    assets_.loadShortTest();
    assets_.loadPoop();
    assets_.loadBoots();
    assets_.loadSushi();
    assets_.loadDrug();

    auto student = std::make_unique<Student>(
        assets_.textures()[Assets::Element::STUDENT],
        assets_.textures()[Assets::Element::HEART],
        sf::Vector2f(assets_.desktopMode().width / 2, assets_.desktopMode().height / 2)
    );

    drawables_.push_back(student.get());
    collidables_.push_back(student.get());
    entities_.push_back(std::move(student));

    auto kwiatkowski = std::make_unique<Kwiatkowski>(
        assets_.textures()[Assets::Element::KWIATKOWSKI]
    );

    drawables_.push_back(kwiatkowski.get());
    collidables_.push_back(kwiatkowski.get());
    entities_.push_back(std::move(kwiatkowski));

    auto poop1 = std::make_unique<Poop>(
        assets_.textures()[Assets::Element::POOP],
        sf::Vector2f(assets_.desktopMode().width / 2, 1280)
    );

    drawables_.push_back(poop1.get());
    collidables_.push_back(poop1.get());
    entities_.push_back(std::move(poop1));

    auto poop2 = std::make_unique<Poop>(
        assets_.textures()[Assets::Element::POOP],
        sf::Vector2f(assets_.desktopMode().width / 2 - 500, 1280)
    );

    drawables_.push_back(poop2.get());
    collidables_.push_back(poop2.get());
    entities_.push_back(std::move(poop2));

    auto poop3 = std::make_unique<Poop>(
        assets_.textures()[Assets::Element::POOP],
        sf::Vector2f(assets_.desktopMode().width / 2 + 500, 1280)
    );

    drawables_.push_back(poop3.get());
    collidables_.push_back(poop3.get());
    entities_.push_back(std::move(poop3));

    auto boots = std::make_unique<Boots>(
        assets_.textures()[Assets::Element::BOOTS],
        sf::Vector2f(assets_.desktopMode().width / 2 + 5, 1200)
    );

    drawables_.push_back(boots.get());
    collidables_.push_back(boots.get());
    entities_.push_back(std::move(boots));

    auto sushi = std::make_unique<Sushi>(
        assets_.textures()[Assets::Element::SUSHI],
        sf::Vector2f(assets_.desktopMode().width / 2 - 500, 1200)
    );

    drawables_.push_back(sushi.get());
    collidables_.push_back(sushi.get());
    entities_.push_back(std::move(sushi));

    auto drug = std::make_unique<Drug>(
        assets_.textures()[Assets::Element::DRUG],
        sf::Vector2f(assets_.desktopMode().width / 2 + 500, 1200)
    );

    drawables_.push_back(drug.get());
    collidables_.push_back(drug.get());
    entities_.push_back(std::move(drug));
}

auto Game::handleEvent(sf::Event const event) -> void {
    switch (event.type) {
        case sf::Event::Closed: window_.close();
            break;
        case sf::Event::KeyPressed: handleKeyPressed(event);
            break;
        case sf::Event::KeyReleased: handleKeyReleased(event);
            break;
        default: ;
    }
}

auto Game::handleKeyPressed(sf::Event const event) -> void {
    auto& studentPtr = *std::ranges::find_if(entities_, [](std::unique_ptr<Entity> const& ptr) {
        return ptr->is<Student>();
    });

    auto& student = studentPtr->as<Student>();

    switch (event.key.code) {
        case sf::Keyboard::A: student.startMovingLeft();
            break;
        case sf::Keyboard::D: student.startMovingRight();
            break;
        case sf::Keyboard::W: student.startMovingUp();
            break;
        case sf::Keyboard::S: student.startMovingDown();
            break;
        default: ;
    }
}

auto Game::spawnShootingTear(
    sf::Vector2f const initialPosition, sf::Vector2f const direction
) -> void {
    auto tear = std::make_unique<Tear>(
        assets_.textures()[Assets::Element::TEAR],
        initialPosition, direction
    );

    enqueuedDrawables_.push_back(tear.get());
    enqueuedCollidables_.push_back(tear.get());
    enqueuedEntities_.push_back(std::move(tear));
}

auto Game::spawnShootingShortTest(
    sf::Vector2f const initialPosition, sf::Vector2f const direction
) -> void {
    auto shortTest = std::make_unique<ShortTest>(
        assets_.textures()[Assets::Element::SHORTTEST],
        initialPosition, direction
    );

    enqueuedDrawables_.push_back(shortTest.get());
    enqueuedCollidables_.push_back(shortTest.get());
    enqueuedEntities_.push_back(std::move(shortTest));
}

auto Game::handleKeyReleased(sf::Event const event) -> void {
    auto& studentPtr = *std::ranges::find_if(entities_, [](std::unique_ptr<Entity> const& ptr) {
        return ptr->is <Student>();
    });

    auto& student = studentPtr->as <Student>();

    switch (event.key.code) {
        case sf::Keyboard::A:
            student.stopMovingLeft();
            break;
        case sf::Keyboard::D:
            student.stopMovingRight();
            break;
        case sf::Keyboard::W:
            student.stopMovingUp();
            break;
        case sf::Keyboard::S:
            student.stopMovingDown();
            break;
        default: ;
    }
}

auto Game::performUpdates() -> void {
    handleCollisions();
    for (auto const& entity: entities_) {
        entity->update(*this);
    }

    addAllNewRegisteredEntities();
}

auto Game::addAllNewRegisteredEntities() -> void {
    for (auto ptr: enqueuedCollidables_) {
        collidables_.push_back(ptr);
    }
    enqueuedCollidables_.clear();

    for (auto ptr: enqueuedDrawables_) {
        drawables_.push_back(ptr);
    }
    enqueuedDrawables_.clear();

    for (auto& ptr: enqueuedEntities_) {
        entities_.push_back(std::move(ptr));
    }
    enqueuedEntities_.clear();
}


auto Game::handleCollisions() -> void {
    for (auto a: collidables_) {
        for (auto b: collidables_) {
            if (a != b and a->isCollidingWith(*b)) {
                a->onCollisionWith(*b);
            }
        }
    }
}

auto Game::renderFrame() -> void {
    window_.clear(sf::Color::White);

    for (auto const& drawable: assets_.genericMapElements()) {
        window_.draw(drawable);
    }

    for (auto const& drawable: drawables_) {
        window_.draw(*drawable);
    }

    window_.display();
}

auto Game::pollAndHandleEvents() -> void {
    for (
        auto event = sf::Event();
        window_.pollEvent(event);
        handleEvent(event)
    );
}

auto Game::removeAllDeadElements() -> void { {
        auto toErase = std::ranges::remove_if(collidables_, [](Collidable const* el) {
            return not el->isAlive();
        });
        collidables_.erase(toErase.begin(), toErase.end());
    } {
        auto toErase = std::ranges::remove_if(drawables_, [](sf::Drawable const* el) {
            return not dynamic_cast<Entity const*>(el)->isAlive();
        });
        drawables_.erase(toErase.begin(), toErase.end());
    } {
        auto toErase = std::ranges::remove_if(entities_, [](std::unique_ptr<Entity> const& el) {
            return not el->isAlive();
        });
        entities_.erase(toErase.begin(), toErase.end());
    }
}
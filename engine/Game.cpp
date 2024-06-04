#include <fstream>
#include <memory>
#include <utility>
#include <sstream>

#include <fmt/ostream.h>

#include "Game.hpp"

#include "../domain/mobs/Kwiatkowski.hpp"
#include "../domain/obstacles/Poop.hpp"
#include "../domain/Student.hpp"
#include "../domain/Tear.hpp"
#include "../domain/mobs/Bush.hpp"
#include "../domain/mobs/ShortTest.hpp"
#include "../domain/mobs/Card.hpp"
#include "../domain/mobs/Chrzastowski.hpp"
#include "../domain/mobs/Exam.hpp"
#include "../domain/mobs/Present.hpp"
#include "../domain/mobs/Smyczek.hpp"
#include "../domain/mobs/Tomaszew.hpp"
#include "../domain/obstacles/Door.hpp"
#include "../domain/upgrades/Boots.hpp"
#include "../domain/upgrades/Drug.hpp"
#include "../domain/upgrades/Sushi.hpp"
#include "../domain/upgrades/Vodka.hpp"
#include "../engine/Utility.hpp"


auto Game::spawnSushi() -> Entity* {
    auto sushi = std::make_unique<Sushi>(
        assets_.textures()[Assets::Element::SUSHI],
        sf::Vector2f(assets_.desktopMode().width / 2 - 500, 1200)
    );

    drawables_.push_back(sushi.get());
    collidables_.push_back(sushi.get());
    entities_.push_back(std::move(sushi));

    return entities_.back().get();
}

auto Game::spawnPoop(sf::Vector2f const initialPosition) -> Entity* {
    auto poop1 = std::make_unique<Poop>(
        assets_.textures()[Assets::Element::POOP],
        initialPosition
    );

    drawables_.push_back(poop1.get());
    collidables_.push_back(poop1.get());
    entities_.push_back(std::move(poop1));

    return entities_.back().get();
}

auto Game::spawnBoots() -> Entity* {
    auto boots = std::make_unique<Boots>(
        assets_.textures()[Assets::Element::BOOTS],
        sf::Vector2f(assets_.desktopMode().width / 2 + 5, 1200)
    );

    drawables_.push_back(boots.get());
    collidables_.push_back(boots.get());
    entities_.push_back(std::move(boots));

    return entities_.back().get();
}

auto Game::spawnDrug() -> Entity* {
    auto drug = std::make_unique<Drug>(
        assets_.textures()[Assets::Element::DRUG],
        sf::Vector2f(assets_.desktopMode().width / 2 + 500, 1200)
    );

    drawables_.push_back(drug.get());
    collidables_.push_back(drug.get());
    entities_.push_back(std::move(drug));

    return entities_.back().get();
}

auto Game::spawnVodka() -> Entity* {
    auto vodka = std::make_unique<Vodka>(
        assets_.textures()[Assets::Element::VODKA],
        sf::Vector2f(assets_.desktopMode().width / 2, assets_.desktopMode().height / 2)
    );

    drawables_.push_back(vodka.get());
    collidables_.push_back(vodka.get());
    entities_.push_back(std::move(vodka));

    return entities_.back().get();
}

auto Game::spawnDoor() -> Entity* {
    auto door = std::make_unique<Door>(
        assets_.textures()[Assets::Element::DOOR],
        sf::Vector2f(assets_.desktopMode().width / 2, 262)
    );

    drawables_.push_back(door.get());
    collidables_.push_back(door.get());
    entities_.push_back(std::move(door));

    return entities_.back().get();
}

auto Game::window() -> sf::RenderWindow& {
    return window_;
}

auto Game::assets() -> Assets const& {
    return assets_;
}

Game::Game(sf::RenderWindow& window)
    : window_(window), movementSurfaces_{{319.0f, 319.0f, 2241.0f, 1186.0f}} {
    auto upperRoomSurface = movementSurfaces_.front();
    upperRoomSurface.top -= float(assets_.desktopMode().height);
    movementSurfaces_.push_back(upperRoomSurface);

    assets_.loadBasement();
    assets_.loadDoor();
    assets_.loadStudent();
    assets_.loadTear();
    assets_.loadHeart();
    assets_.loadKwiatkowski();
    assets_.loadShortTest();
    assets_.loadPoop();
    assets_.loadBoots();
    assets_.loadSushi();
    assets_.loadDrug();
    assets_.loadTomaszew();
    assets_.loadSmyczek();
    assets_.loadBush();
    assets_.loadCard();
    assets_.loadVodka();
    assets_.loadChrzastowski();
    assets_.loadPresent();
    assets_.loadExam();

    spawnStudent();

    spawnPoop(sf::Vector2f(assets_.desktopMode().width / 2, 1280));
    spawnPoop(sf::Vector2f(assets_.desktopMode().width / 2 - 500, 1280));
    spawnPoop(sf::Vector2f(assets_.desktopMode().width / 2 + 500, 1280));

    spawnBoots();
    spawnSushi();
    spawnDrug();
    spawnDoor();
}

auto Game::spawnStudent() -> Entity* {
    auto student = std::make_unique<Student>(
        assets_.textures()[Assets::Element::STUDENT],
        assets_.textures()[Assets::Element::HEART],
        sf::Vector2f(assets_.desktopMode().width / 2, assets_.desktopMode().height / 2)
    );

    drawables_.push_back(student.get());
    collidables_.push_back(student.get());
    entities_.push_back(std::move(student));

    return entities_.back().get();
}

auto Game::spawnTomaszewkaAt(float const x, float const y) -> Entity* {
    auto tomaszew = std::make_unique<Tomaszew>(
        assets_.textures()[Assets::Element::TOMASZEW],
        sf::Vector2f(x, y)
    );

    enqueuedDrawables_.push_back(tomaszew.get());
    enqueuedCollidables_.push_back(tomaszew.get());
    enqueuedEntities_.push_back(std::move(tomaszew));

    return enqueuedEntities_.back().get();
}

auto Game::spawnSmyczekAt(float const x, float const y) -> Entity* {
    auto smyczek = std::make_unique<Smyczek>(
        assets_.textures()[Assets::Element::SMYCZEK],
        sf::Vector2f(x, y)
    );

    enqueuedDrawables_.push_back(smyczek.get());
    enqueuedCollidables_.push_back(smyczek.get());
    enqueuedEntities_.push_back(std::move(smyczek));

    return enqueuedEntities_.back().get();
}

auto Game::spawnKwiatkowski() -> Entity* {
    auto kwiatkowski = std::make_unique<Kwiatkowski>(
        assets_.textures()[Assets::Element::KWIATKOWSKI]
    );

    enqueuedDrawables_.push_back(kwiatkowski.get());
    enqueuedCollidables_.push_back(kwiatkowski.get());
    enqueuedEntities_.push_back(std::move(kwiatkowski));

    return enqueuedEntities_.back().get();
}

auto Game::spawnChrzastowski() -> Entity* {
    auto chrzastowski = std::make_unique<Chrzastowski>(
        assets_.textures()[Assets::Element::CHRZASTOWSKI],
        sf::Vector2f(assets_.desktopMode().width / 2, -float(assets_.desktopMode().height) / 2)
    );

    enqueuedDrawables_.push_back(chrzastowski.get());
    enqueuedCollidables_.push_back(chrzastowski.get());
    enqueuedEntities_.push_back(std::move(chrzastowski));

    return enqueuedEntities_.back().get();
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
        case sf::Keyboard::S:
            if (event.key.control) {
                saveAllEntitiesToFile(defaultSaveFilePath_);
            } else {
                student.startMovingDown();
            }
            break;
        case sf::Keyboard::L:
            if (event.key.control) {
                loadAllEntitiesFromFile(defaultSaveFilePath_);
            }
        default: ;
    }
}

auto Game::spawnShootingTear(
    sf::Vector2f const initialPosition, sf::Vector2f const direction, float const tearScale,
    int const damage
) -> Entity* {
    auto tear = std::make_unique<Tear>(
        assets_.textures()[Assets::Element::TEAR],
        initialPosition, direction, tearScale, damage
    );

    enqueuedDrawables_.push_back(tear.get());
    enqueuedCollidables_.push_back(tear.get());
    enqueuedEntities_.push_back(std::move(tear));

    return enqueuedEntities_.back().get();
}

auto Game::spawnShootingShortTest(
    sf::Vector2f const initialPosition, sf::Vector2f const direction
) -> Entity* {
    auto shortTest = std::make_unique<ShortTest>(
        assets_.textures()[Assets::Element::SHORTTEST],
        initialPosition, direction
    );

    enqueuedDrawables_.push_back(shortTest.get());
    enqueuedCollidables_.push_back(shortTest.get());
    enqueuedEntities_.push_back(std::move(shortTest));

    return enqueuedEntities_.back().get();
}

auto Game::spawnShootingPresent(
    sf::Vector2f const initialPosition, sf::Vector2f const direction
) -> Entity* {
    auto present = std::make_unique<Present>(
        assets_.textures()[Assets::Element::PRESENT],
        initialPosition, direction
    );

    enqueuedDrawables_.push_back(present.get());
    enqueuedCollidables_.push_back(present.get());
    enqueuedEntities_.push_back(std::move(present));

    return enqueuedEntities_.back().get();
}

auto Game::spawnShootingCard(
    sf::Vector2f const initialPosition, sf::Vector2f const direction
) -> Entity* {
    auto card = std::make_unique<Card>(
        assets_.textures()[Assets::Element::CARD],
        initialPosition, direction
    );

    enqueuedDrawables_.push_back(card.get());
    enqueuedCollidables_.push_back(card.get());
    enqueuedEntities_.push_back(std::move(card));

    return enqueuedEntities_.back().get();
}

auto Game::spawnShootingExam(
    sf::Vector2f const initialPosition, sf::Vector2f const direction
) -> Entity* {
    auto exam = std::make_unique<Exam>(
        assets_.textures()[Assets::Element::EXAM],
        initialPosition, direction
    );

    enqueuedDrawables_.push_back(exam.get());
    enqueuedCollidables_.push_back(exam.get());
    enqueuedEntities_.push_back(std::move(exam));

    return enqueuedEntities_.back().get();
}

auto Game::spawnShootingBush(
    sf::Vector2f const initialPosition, sf::Vector2f const direction
) -> Entity* {
    auto bush = std::make_unique<Bush>(
        assets_.textures()[Assets::Element::BUSH],
        initialPosition, direction
    );

    enqueuedDrawables_.push_back(bush.get());
    enqueuedCollidables_.push_back(bush.get());
    enqueuedEntities_.push_back(std::move(bush));

    return enqueuedEntities_.back().get();
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

    updateAllEntities();

    addAllNewRegisteredEntities();

    reorderDrawables();
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

auto Game::updateAllEntities() -> void {
    for (auto const& entity : entities_) {
        entity->update(*this);
    }
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

auto Game::reorderDrawables() -> void {
    // things that are lower should be drawn on top of things that are higher
    std::ranges::sort(
        drawables_, {}, [](sf::Drawable const* d) {
            return dynamic_cast<Collidable const*>(d)->getGlobalBounds().top;
        }
    );

    // with exception for upgrades
    std::ranges::stable_partition(drawables_, [](sf::Drawable const* d) {
        return !dynamic_cast<Entity const*>(d)->is<Upgrade>();
    });
}

auto Game::renderFrame() -> void {
    window_.clear(sf::Color::White);

    for (auto const& drawable : assets_.genericMapElements()) {
        window_.draw(drawable);
    }

    for (auto const& drawable : drawables_) {
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

auto Game::removeAllDeadElements() -> void {
    {
        auto toErase = std::ranges::remove_if(collidables_, [](Collidable const* el) {
            return not el->isAlive();
        });
        collidables_.erase(toErase.begin(), toErase.end());
    }
    {
        auto toErase = std::ranges::remove_if(drawables_, [](sf::Drawable const* el) {
            return not dynamic_cast<Entity const*>(el)->isAlive();
        });
        drawables_.erase(toErase.begin(), toErase.end());
    }
    {
        auto toErase = std::ranges::remove_if(entities_, [](std::unique_ptr<Entity> const& el) {
            return not el->isAlive();
        });
        entities_.erase(toErase.begin(), toErase.end());
    }
}

auto Game::spawnVodkaIfNecessary() -> void {
    if (not vodkaWasSpawned_) {
        vodkaWasSpawned_ = true;
        auto vodka = std::make_unique<Vodka>(
            assets_.textures()[Assets::Element::VODKA],
            sf::Vector2f(assets_.desktopMode().width / 2, assets_.desktopMode().height / 2)
        );

        enqueuedDrawables_.push_back(vodka.get());
        enqueuedCollidables_.push_back(vodka.get());
        enqueuedEntities_.push_back(std::move(vodka));
    }
}


auto Game::spawnKwiatkowskiIfNecessary() -> void {
    if (not kwiatkowskiWasSpawned_) {
        kwiatkowskiWasSpawned_ = true;
        auto kwiatkowski = std::make_unique<Kwiatkowski>(
            assets_.textures()[Assets::Element::KWIATKOWSKI]
        );

        enqueuedDrawables_.push_back(kwiatkowski.get());
        enqueuedCollidables_.push_back(kwiatkowski.get());
        enqueuedEntities_.push_back(std::move(kwiatkowski));
    }
}

auto Game::spawnChrzastowskiIfNecessary() -> void {
    if (not chrzastowskiWasSpawned_) {
        chrzastowskiWasSpawned_ = true;
        auto chrzastowski = std::make_unique<Chrzastowski>(
            assets_.textures()[Assets::Element::CHRZASTOWSKI],
            sf::Vector2f(assets_.desktopMode().width / 2, -float(assets_.desktopMode().height) / 2)
        );

        enqueuedDrawables_.push_back(chrzastowski.get());
        enqueuedCollidables_.push_back(chrzastowski.get());
        enqueuedEntities_.push_back(std::move(chrzastowski));
    }
}

auto Game::spawnTomaszewkiIfNecessary() -> void {
    if (not tomaszewkiWereSpawned_) {
        tomaszewkiWereSpawned_ = true;
        auto const tomaszewsToSpawn = randomize(4, 8);
        for (auto i = 0; i < tomaszewsToSpawn; ++i) {
            auto tomaszew = std::make_unique<Tomaszew>(
                assets_.textures()[Assets::Element::TOMASZEW],
                sf::Vector2f(randomize(320, 2500), randomize(320, 1000))
            );

            enqueuedDrawables_.push_back(tomaszew.get());
            enqueuedCollidables_.push_back(tomaszew.get());
            enqueuedEntities_.push_back(std::move(tomaszew));
        }
    }
}

auto Game::spawnSmyczkiIfNecessary() -> void {
    if (not smyczkiWereSpawned_) {
        smyczkiWereSpawned_ = true;
        auto const smyczeksToSpawn = randomize(1, 3);
        for (auto i = 0; i < smyczeksToSpawn; ++i) {
            auto smyczek = std::make_unique<Smyczek>(
                assets_.textures()[Assets::Element::SMYCZEK],
                sf::Vector2f(randomize(320, 2500), randomize(320, 1000))
            );

            enqueuedDrawables_.push_back(smyczek.get());
            enqueuedCollidables_.push_back(smyczek.get());
            enqueuedEntities_.push_back(std::move(smyczek));
        }
    }
}

auto Game::saveAllEntitiesToFile(std::string const& path) const -> void {
    auto saveFile = std::ofstream(path, std::ios::trunc);
    for (auto const& entity : entities_) {
        fmt::println(saveFile, "{}", entity->serializeToString());
    }

    auto const viewCenter = window_.getView().getCenter();
    auto const viewSize   = window_.getView().getSize();
    fmt::println(
        saveFile, "view {} {} {} {}",
        viewCenter.x, viewCenter.y, viewSize.x, viewSize.y
    );
}

auto Game::loadAllEntitiesFromFile(std::string const& path) -> void {
    entities_.clear();
    drawables_.clear();
    collidables_.clear();

    enqueuedEntities_.clear();
    enqueuedDrawables_.clear();
    enqueuedCollidables_.clear();

    auto saveFile = std::ifstream(path);

    auto line = std::string();
    while (std::getline(saveFile, line) and !line.starts_with("view")) {
        createEntityUsingSerialization(line);
    }

    auto stream = std::istringstream(line.substr(5));
    auto viewCenter = sf::Vector2f();
    auto viewSize   = sf::Vector2f();
    stream >> viewCenter.x >> viewCenter.y >> viewSize.x >> viewSize.y;
    auto view = sf::View();
    view.setCenter(viewCenter);
    view.setSize(viewSize);
    window_.setView(view);
}

auto Game::createEntityUsingSerialization(const std::string& line) -> void {
    auto const type = line.substr(0, line.find(' '));
    auto createdEntity = static_cast<Entity*>(nullptr);

    if (type == "Tear") {
        createdEntity = spawnShootingTear({}, {}, 0.0f, 0);
    } else if (type == "Student") {
        createdEntity = spawnStudent();
    } else if (type == "Sushi") {
        tomaszewkiWereSpawned_ = false;
        createdEntity = spawnSushi();
    } else if (type == "Drug") {
        tomaszewkiWereSpawned_ = false;
        createdEntity = spawnDrug();
    } else if (type == "Boots") {
        tomaszewkiWereSpawned_ = false;
        createdEntity = spawnBoots();
    }  else if (type == "Poop") {
        createdEntity = spawnPoop({});
    } else if (type == "Door") {
        createdEntity = spawnDoor();
    } else if (type == "Tomaszewka") {
        smyczkiWereSpawned_ = false;
        createdEntity = spawnTomaszewkaAt();
    } else if (type == "Smyczek") {
        kwiatkowskiWasSpawned_ = false;
        createdEntity = spawnSmyczekAt();
    } else if (type == "Kwiatkowski") {
        createdEntity = spawnKwiatkowski();
    } else if (type == "Vodka") {
        createdEntity = spawnVodka();
    } else if (type == "Bush") {
        createdEntity = spawnShootingBush({}, {});
    } else if (type == "Card") {
        createdEntity = spawnShootingCard({}, {});
    } else if (type == "ShortTest") {
        createdEntity = spawnShootingShortTest({}, {});
    } else if (type == "Chrzastowski") {
        createdEntity = spawnChrzastowski();
    } else if (type == "Present") {
        createdEntity = spawnShootingPresent({}, {});
    } else if (type == "Exam") {
        createdEntity = spawnShootingExam({}, {});
    }

    if (!createdEntity) {
        throw std::logic_error("piździet jakiś nieznany typior...");
    }

    createdEntity->deserializeFromString(line);
}
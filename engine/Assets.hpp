#pragma once

#include <string>
#include <map>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "SFML/Graphics/Font.hpp"

class Assets {
public:
    enum class Element {
        BASEMENT, DOOR, STUDENT, TEAR, HEART, KWIATKOWSKI, SHORTTEST, CARD, POOP, BOOTS, SUSHI,
        DRUG, TOMASZEW, SMYCZEK, BUSH, VODKA, CHRZASTOWSKI, PRESENT, EXAM, GAMEOVER
    };

    enum class Font {
        SLAY
    };
private:
    std::map<Element, sf::Texture> storage_;
    std::map<Font, sf::Font> fonts_;
    std::vector<sf::Sprite> genericMapElements_;
    sf::VideoMode desktopMode_;
public:
    Assets();

    Assets(Assets const&) = delete;

    auto loadBasement() -> void;

    auto loadStudent() -> void;

    auto loadTear() -> void;

    auto loadHeart() -> void;

    auto loadKwiatkowski() -> void;

    auto loadShortTest() -> void;

    auto loadPoop() -> void;

    auto loadBoots() -> void;

    auto loadSushi() -> void;

    auto loadDrug() -> void;

    auto loadTomaszew() -> void;

    auto loadSmyczek() -> void;

    auto loadBush() -> void;

    auto loadCard() -> void;

    auto loadDoor() -> void;

    auto loadVodka() -> void;

    auto loadChrzastowski() -> void;

    auto loadPresent() -> void;

    auto loadExam() -> void;

    auto loadSlay() -> void;

    auto loadGameOver() -> void;

    auto genericMapElements() const -> std::vector<sf::Sprite> const& {
        return genericMapElements_;
    }

    auto textures() -> std::map<Element, sf::Texture>& {
        return storage_;
    }

    auto desktopMode() const -> sf::VideoMode {
        return desktopMode_;
    }

    auto fonts() -> std::map<Font, sf::Font>& {
        return fonts_;
    }
};
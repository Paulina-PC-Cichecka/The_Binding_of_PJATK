#pragma once

#include <string>
#include <map>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>

class Assets {
public:
    enum class Element {
        BASEMENT, STUDENT, TEAR, HEART, KWIATKOWSKI, SHORTTEST, CARD, POOP, BOOTS, SUSHI, DRUG, TOMASZEW,
        SMYCZEK, BUSH, CHRZASTOWSKI
    };
private:
    std::map<Element, sf::Texture> storage_;
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

    auto genericMapElements() const -> std::vector<sf::Sprite> const& {
        return genericMapElements_;
    }

    auto textures() -> std::map<Element, sf::Texture>& {
        return storage_;
    }

    auto desktopMode() const -> sf::VideoMode {
        return desktopMode_;
    }
};
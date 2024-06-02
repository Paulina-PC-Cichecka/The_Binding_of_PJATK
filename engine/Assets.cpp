#include "Assets.hpp"

#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/VideoMode.hpp"

Assets::Assets() : desktopMode_(sf::VideoMode::getDesktopMode()) { }


auto Assets::loadBasement() -> void {
    storage_[Element::BASEMENT].loadFromFile("../assets/Basement.png");

    auto topLeft = sf::Sprite();
    topLeft.setTexture(storage_[Element::BASEMENT]);
    topLeft.setTextureRect(sf::IntRect(0, 0, 234, 156));
    auto const widthScale = float(desktopMode_.width)
            / (float(topLeft.getTextureRect().width) * 2);
    auto const heightScale = float(desktopMode_.height)
            / (float(topLeft.getTextureRect().height) * 2);
    topLeft.scale(widthScale, heightScale);

    auto bottomRight = topLeft;
    bottomRight.setPosition(desktopMode_.width, desktopMode_.height);
    bottomRight.rotate(180);

    auto bottomLeft = topLeft;
    auto scale = bottomLeft.getScale();
    scale.y *= -1;
    bottomLeft.setScale(scale);
    bottomLeft.setPosition(0, desktopMode_.height);

    auto topRight = topLeft;
    scale = topRight.getScale();
    scale.x *= -1;
    topRight.setScale(scale);
    topRight.setPosition(desktopMode_.width, 0);

    genericMapElements_.push_back(topLeft);
    genericMapElements_.push_back(topRight);
    genericMapElements_.push_back(bottomLeft);
    genericMapElements_.push_back(bottomRight);
}

auto Assets::loadStudent() -> void {
    storage_[Element::STUDENT].loadFromFile("../assets/Student.png");
}

auto Assets::loadTear() -> void {
    storage_[Element::TEAR].loadFromFile("../assets/Tear.png");
}

auto Assets::loadHeart() -> void {
    storage_[Element::HEART].loadFromFile("../assets/Hearts.png");
}

auto Assets::loadKwiatkowski() -> void {
    storage_[Element::KWIATKOWSKI].loadFromFile("../assets/Kwiatkowski.png");
}

auto Assets::loadShortTest() -> void {
    storage_[Element::SHORTTEST].loadFromFile("../assets/ShortTest.png");
}

auto Assets::loadPoop() -> void {
    storage_[Element::POOP].loadFromFile("../assets/Poop.png");
}

auto Assets::loadBoots() -> void {
    storage_[Element::BOOTS].loadFromFile("../assets/HermesBoots.png");
}

auto Assets::loadSushi() -> void {
    storage_[Element::SUSHI].loadFromFile("../assets/Sushi.png");
}

auto Assets::loadDrug() -> void {
    storage_[Element::DRUG].loadFromFile("../assets/Drug.png");
}

auto Assets::loadTomaszew() -> void {
    storage_[Element::TOMASZEW].loadFromFile("../assets/NibyTomaszew.png");
}




#include <fmt/core.h>
#include <SFML/Graphics.hpp>

#include "engine/Game.hpp"

auto main() -> int {
    auto window = sf::RenderWindow(
        sf::VideoMode::getDesktopMode(), "The Binding of PJATK", sf::Style::Fullscreen
    );

    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    auto game = Game(window);

    while (window.isOpen()) {
        game.pollAndHandleEvents();
        game.performUpdates();
        game.renderFrame();
        game.removeAllDeadElements();
    }
}
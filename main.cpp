

#include <fmt/core.h>
#include <SFML/Graphics.hpp>

#include "engine/Game.hpp"

auto main() -> int {
    auto window = sf::RenderWindow(sf::VideoMode::getDesktopMode(),
                                   "The Binding of PJATK", sf::Style::Fullscreen);
    // window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    auto game = Game(window);

    while (window.isOpen()) {
        game.pollAndHandleEvents();
        game.performUpdates();
        game.renderFrame();
        game.removeAllDeadElements();
    }
}
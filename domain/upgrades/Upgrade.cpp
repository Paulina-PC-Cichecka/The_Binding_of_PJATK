#include "Upgrade.hpp"
#include "../../engine/Game.hpp"
#include "../../engine/Utility.hpp"

#include <fmt/core.h>

auto Upgrade::update(Game& game) -> void {
    if (!isAlive_) {
        for (auto const& e : game.entities()) {
            if (e->is<Upgrade>()) {
                e->kill();
            }
        }

        fmt::println("should spawn tomaszewkis");
        game.spawnTomaszewkiIfNecessary();
    }
}
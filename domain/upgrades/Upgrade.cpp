#include "Upgrade.hpp"
#include "../../engine/Game.hpp"
#include "../../engine/Utility.hpp"

auto Upgrade::update(Game& game) -> void {
    if (!isAlive_) {
        for (auto const& e : game.entities()) {
            if (e->is<Upgrade>()) {
                e->kill();
            }
        }

        game.spawnTomaszewkiIfNecessary();
    }
}
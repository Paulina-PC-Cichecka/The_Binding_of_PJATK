#pragma once
#include "../../engine/Collidable.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Upgrade : public Collidable, public sf::Drawable {

public:
    auto update(Game&) -> void override;

     ~Upgrade() override = 0;
};
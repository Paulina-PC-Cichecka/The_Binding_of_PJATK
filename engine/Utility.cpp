#include <cmath>

#include "Utility.hpp"

auto normalized(sf::Vector2f vec) -> sf::Vector2f{
    auto length = std::hypot(vec.x, vec.y);

    auto newVec = sf::Vector2f(vec.x / length, vec.y / length);
    return newVec;
}
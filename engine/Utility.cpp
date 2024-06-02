#include <cmath>
#include <random>

#include "Utility.hpp"

auto normalized(sf::Vector2f vec) -> sf::Vector2f{
    auto length = std::hypot(vec.x, vec.y);

    auto newVec = sf::Vector2f(vec.x / length, vec.y / length);
    return newVec;
}

// wiedza -> mr. Kwiatkowski :>
auto randomize(int const from, int const to) -> int {
    static auto device = std::random_device();
    static auto engine = std::default_random_engine(device());

    auto distribution = std::uniform_int_distribution(from, to);
    return distribution(engine);
}
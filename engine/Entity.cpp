#include "Entity.hpp"

Entity::Entity() : id_(generateNextId()) { }

auto Entity::generateNextId() -> int {
    return ++currentId;
}
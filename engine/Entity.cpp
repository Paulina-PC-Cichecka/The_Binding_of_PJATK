#include "Entity.hpp"

Entity::Entity() : id_(generateNextId()), isAlive_(true) { }

auto Entity::generateNextId() -> int {
    return ++currentId;
}
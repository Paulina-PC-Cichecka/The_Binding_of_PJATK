cmake_minimum_required(VERSION 3.28)
project(Game2D)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(fmt)

add_executable(Game2D
        main.cpp
        engine/Game.cpp
        engine/Entity.cpp
        engine/Assets.cpp
        engine/Utility.cpp
        domain/Student.cpp
        domain/Tear.cpp
        domain/mobs/Kwiatkowski.cpp
        domain/mobs/ShortTest.cpp
        domain/mobs/Card.cpp
        domain/mobs/Tomaszew.cpp
        domain/mobs/Smyczek.cpp
        domain/mobs/Bush.cpp
        domain/mobs/Chrzastowski.cpp
        domain/mobs/Present.cpp
        domain/mobs/Exam.cpp
        domain/obstacles/Poop.cpp
        domain/obstacles/Door.cpp
        domain/upgrades/Boots.cpp
        domain/upgrades/Sushi.cpp
        domain/upgrades/Drug.cpp
        domain/upgrades/Upgrade.cpp
        domain/upgrades/Vodka.cpp
)
target_link_libraries(Game2D fmt sfml-graphics)
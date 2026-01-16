cmake_minimum_required(VERSION 4.0)
project(MonkeyTyper)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 12.1.0
        GIT_SHALLOW ON
)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)

FetchContent_MakeAvailable(fmt SFML)

add_executable(MonkeyTyper
        main.cpp
        Class/Button.cpp
        Class/Button.hpp
        Sceneries/Menu.cpp
        Sceneries/Menu.hpp
        Sceneries/PreGame.cpp
        Sceneries/PreGame.hpp
        Sceneries/Game.cpp
        Sceneries/Game.hpp
        Sceneries/Settings.cpp
        Sceneries/Settings.hpp
        Sceneries/Author.cpp
        Sceneries/Author.hpp
        Enums.hpp
        Class/Font.cpp
        Class/Font.hpp
        Class/Banan.cpp
        Class/Banan.hpp
        Class/Text.cpp
        Class/Text.hpp
)
target_link_libraries(MonkeyTyper fmt::fmt SFML::Graphics)
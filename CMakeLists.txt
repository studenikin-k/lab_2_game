cmake_minimum_required(VERSION 3.20)
project(lab_2_game)

set(CMAKE_CXX_STANDARD 20)


find_package(SQLite3 REQUIRED)

file(GLOB MAIN_SOURCES
        "src/characters/*.cpp"
        "src/inventory/*.cpp"
        "src/inventory/bag/*.cpp"
        "src/inventory/coins/*.cpp"
        "src/inventory/equipment/*.cpp"
        "src/inventory/potion/*.cpp"
        "src/inventory/weapon/*.cpp"
        "src/shop/*.cpp"
        "include/utils/*.cpp"
        "src/main.cpp"
        "src/location/*.cpp"
        "src/location/map/*.cpp"
        "src/location/battle_location/*.cpp"
        "src/location/shop_location/*.cpp"
)

add_executable(main ${MAIN_SOURCES}
        src/characters/character.cpp
        include/characters/opponent/opponent.h
        include/characters/main_char/main_char.h
        src/characters/opponent/opponent.cpp
        src/characters/main_char/main_char.cpp
        src/characters/character.cpp
        include/characters/character.h
        src/location/location.cpp
        include/location/location.h
        src/location/map/map.cpp
        include/location/map/map.h
        src/location/shop_location/shop_location.cpp
        src/upload_system/upload_system.cpp
        include/game_mechanics/game_mechanics.h
        src/game_mechanics/game_mechanics.cpp
        src/save_system/save_game.cpp
        include/upload_system/upload_system.h
        include/start_game/start_game.h
        src/start_game/start_game.cpp
        src/features/clear_screen.cpp
        include/all_headers.h
)


target_link_libraries(main PRIVATE SQLite::SQLite3)

target_include_directories(main PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/characters
        ${CMAKE_CURRENT_SOURCE_DIR}/src/inventory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shop
        include/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/src/inventory/coins
        ${CMAKE_CURRENT_SOURCE_DIR}/src/location
        ${CMAKE_CURRENT_SOURCE_DIR}/src/location/battle_location
        ${CMAKE_CURRENT_SOURCE_DIR}/src/location/map
        ${CMAKE_CURRENT_SOURCE_DIR}/src/location/shop_location
)

add_definitions(-DPROJECT_ROOT_PATH_DEF="${CMAKE_SOURCE_DIR}")

cmake_minimum_required(VERSION 3.20)
project(lab_2_game)

set(CMAKE_CXX_STANDARD 20)

# ====================
# Find required packages
# ====================
find_package(SQLite3 REQUIRED)
find_package(GTest REQUIRED)

# ====================
# Include directories (рекурсивно по include/)
# ====================
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/characters
        ${CMAKE_CURRENT_SOURCE_DIR}/include/characters/main_char
        ${CMAKE_CURRENT_SOURCE_DIR}/include/characters/opponent
        ${CMAKE_CURRENT_SOURCE_DIR}/include/features
        ${CMAKE_CURRENT_SOURCE_DIR}/include/game_mechanics
        ${CMAKE_CURRENT_SOURCE_DIR}/include/inventory
        ${CMAKE_CURRENT_SOURCE_DIR}/include/inventory/bag
        ${CMAKE_CURRENT_SOURCE_DIR}/include/inventory/coins
        ${CMAKE_CURRENT_SOURCE_DIR}/include/inventory/equipment
        ${CMAKE_CURRENT_SOURCE_DIR}/include/inventory/potion
        ${CMAKE_CURRENT_SOURCE_DIR}/include/inventory/weapon
        ${CMAKE_CURRENT_SOURCE_DIR}/include/location
        ${CMAKE_CURRENT_SOURCE_DIR}/include/location/battle_location
        ${CMAKE_CURRENT_SOURCE_DIR}/include/location/map
        ${CMAKE_CURRENT_SOURCE_DIR}/include/location/shop_location
        ${CMAKE_CURRENT_SOURCE_DIR}/include/save_system
        ${CMAKE_CURRENT_SOURCE_DIR}/include/shop
        ${CMAKE_CURRENT_SOURCE_DIR}/include/start_game
        ${CMAKE_CURRENT_SOURCE_DIR}/include/upload_system
        ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
)

# ====================
# Source files for shared game library
# ====================
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
        src/characters/*.cpp
        src/features/*.cpp
        src/game_mechanics/*.cpp
        src/inventory/*.cpp
        src/inventory/bag/*.cpp
        src/inventory/coins/*.cpp
        src/inventory/equipment/*.cpp
        src/inventory/potion/*.cpp
        src/inventory/weapon/*.cpp
        src/location/*.cpp
        src/location/battle_location/*.cpp
        src/location/map/*.cpp
        src/location/shop_location/*.cpp
        src/save_system/*.cpp
        src/shop/*.cpp
        src/start_game/*.cpp
        src/upload_system/*.cpp
        include/utils/*.cpp
)

add_library(game_lib ${GAME_SOURCES})

target_include_directories(game_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(game_lib PUBLIC SQLite::SQLite3)

add_definitions(-DPROJECT_ROOT_PATH_DEF="${CMAKE_SOURCE_DIR}")

# ====================
# Executable for the game
# ====================
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE game_lib)

# ====================
# Tests
# ====================
enable_testing()

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        tests/*.cpp
)

add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests PRIVATE game_lib GTest::GTest GTest::Main)

include(GoogleTest)
gtest_discover_tests(run_tests)

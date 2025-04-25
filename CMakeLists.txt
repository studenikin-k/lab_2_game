cmake_minimum_required(VERSION 3.20)
project(lab_2_game)

set(CMAKE_CXX_STANDARD 20)


#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB MAIN_SOURCES
        "src/characters/*.cpp"
        "src/inventory/*.cpp"
        "src/inventory/bag/*.cpp"
        "src/inventory/coins/*.cpp"
        "src/inventory/equipment/*.cpp"
        "src/inventory/potion/*.cpp"
        "src/inventory/weapon/*.cpp"
        "src/shop/*.cpp"
        "src/utils/*.cpp"
        "src/main.cpp"
)


#file(GLOB TEST_SOURCES
 #       "tests/*.cpp"
#)


add_executable(main ${MAIN_SOURCES}
        src/characters/character.cpp
        src/characters/opponent.h
        src/characters/main_char.h
        src/characters/opponent.cpp
        src/characters/main_char.cpp
        src/characters/character.cpp
        src/characters/character.h
        src/location/location.cpp
        src/location/location.h)

#add_executable(tests ${TEST_SOURCES})


#target_link_libraries(tests PRIVATE
 #       ${GTEST_LIBRARIES}
  #      ${GTEST_MAIN_LIBRARIES}
#)


target_include_directories(main PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/characters
        ${CMAKE_CURRENT_SOURCE_DIR}/src/inventory
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shop
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/src/inventory/coins
)

#target_include_directories(tests PRIVATE
 #       ${CMAKE_CURRENT_SOURCE_DIR}/src
  #      ${CMAKE_CURRENT_SOURCE_DIR}/tests
#)
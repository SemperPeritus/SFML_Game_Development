cmake_minimum_required(VERSION 3.2)
project(SFML_Game_Development)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} src/Game.cpp src/Game.h)

# SFML Libraries
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
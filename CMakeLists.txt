cmake_minimum_required(VERSION 3.2)
project(SFML_Game_Development)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} src/Game.cpp src/Game.h src/Managers/ResourceHolder.inl src/Managers/ResourceHolder.h src/Entities/Entity.cpp src/Entities/Entity.h src/Entities/Aircraft.cpp src/Entities/Aircraft.h src/Entities/SceneNode.cpp src/Entities/SceneNode.h src/Managers/ResourceIdentifiers.h src/World.cpp src/World.h src/Entities/SpriteNode.cpp src/Entities/SpriteNode.h)

# SFML Libraries
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/img $<TARGET_FILE_DIR:${PROJECT_NAME}>/img)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts)

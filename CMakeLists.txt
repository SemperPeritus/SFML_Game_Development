cmake_minimum_required(VERSION 3.2)
project(SFML_Game_Development)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} src/Game.cpp src/Game.h src/ResourceHolder.inl src/ResourceHolder.h)

# SFML Libraries
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/img $<TARGET_FILE_DIR:${PROJECT_NAME}>/img)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts)

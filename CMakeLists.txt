cmake_minimum_required(VERSION 3.13)
project(cetris)

set(CMAKE_CXX_STAND 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17")

find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

add_executable(cetris main.cpp Board.cpp Board.hpp Structs.hpp Shape.cpp Shape.hpp Game.cpp Game.hpp ShapeGenerator.cpp ShapeGenerator.hpp InfoPanel.cpp InfoPanel.hpp StopPanel.cpp StopPanel.hpp Helpers.hpp StepManager.cpp StepManager.hpp)

target_link_libraries(cetris sfml-graphics sfml-audio)


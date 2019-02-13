cmake_minimum_required(VERSION 3.13)
project(cetris)

set(CMAKE_CXX_STAND 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17")

set(SFML_DIR "/usr/share/SFML/cmake/Modules")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" /usr/share/SFML/cmake/Modules)
find_package(SFML 2.3.2 COMPONENTS system window graphics REQUIRED)

add_executable(cetris main.cpp Board.cpp Board.hpp Structs.hpp Shape.cpp Shape.hpp Game.cpp Game.hpp)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(cetris ${SFML_LIBRARIES})


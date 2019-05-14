cmake_minimum_required(VERSION 3.10)
project(cetris)

set(CMAKE_CXX_STAND 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17")

find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

include_directories(BEFORE "header")
file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(cetris ${SRC})

target_link_libraries(cetris sfml-graphics sfml-audio stdc++fs)


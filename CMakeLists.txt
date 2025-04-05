cmake_minimum_required(VERSION 3.26)
project(snake C CXX)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

add_executable(snake)

include_directories(include)

target_sources(snake
PRIVATE
    src/main.c
)

target_link_libraries(snake SDL3::SDL3 SDL3_ttf::SDL3_ttf)

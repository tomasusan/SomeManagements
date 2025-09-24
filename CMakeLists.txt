cmake_minimum_required(VERSION 3.31)
project(EventManagement)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE PRIVATE_SOURCES "Private/*.cpp")

add_executable(EventManagement main.cpp
        ${PRIVATE_SOURCES}
)

target_include_directories(EventManagement
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Public
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Private
)


cmake_minimum_required(VERSION 3.24)
project(Kahraman)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(SFML GIT_REPOSITORY  https://github.com/SFML/SFML.git GIT_TAG 2.6.1)
FetchContent_MakeAvailable(SFML)
set(CMAKE_CXX_STANDARD 20)





add_executable(Kahraman main.cpp
        Text.cpp
        Text.h
)

target_link_libraries(Kahraman sfml-graphics)

cmake_minimum_required(VERSION 2.8)

project(markov)
set (CMAKE_CXX_STANDARD 14)


file(GLOB markov_SRC
    "*.h"
    "*.cpp"
)

add_executable(${PROJECT_NAME} ${markov_SRC})


